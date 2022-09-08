
#include "utilities.h"

#include <QProcess>
#include <QThread>
#include <qt_windows.h>

#include "program.h"
#include "qtservice.h"
#include "errorlogger.h"


WindowsVersion Utilities::currentWindowsVersion = WindowsVersion::Unsupported;
Registry Utilities::_registry;

bool SIMULATE = true;

//internal static WindowsVersion CurrentWindowsVersion = WindowsVersion::Unsupported;

//        static string productName = string.Empty;
//        static string buildNumber = string.Empty;

/* FIXME
		internal delegate void SetControlPropertyThreadSafeDelegate(Control control, const QString& propertyName, object propertyValue);

void Utilities::SetControlPropertyThreadSafe(Control control, const QString& propertyName, object propertyValue)
		{
			if (control.InvokeRequired)
			{
				control.Invoke(new SetControlPropertyThreadSafeDelegate(SetControlPropertyThreadSafe), new object[] { control, propertyName, propertyValue });
			}
			else
			{
				control.GetType().InvokeMember(propertyName, BindingFlags.SetProperty, null, control, new object[] { propertyValue });
			}
		}
		*/

/* FIXME
		internal static IEnumerable<Control> GetSelfAndChildrenRecursive(Control parent)
		{
			List<Control> controls = new List<Control>();

			foreach (Control child in parent.Controls)
			{
				controls.AddRange(GetSelfAndChildrenRecursive(child));
			}

			controls.Add(parent);
			return controls;
		}
**/


/* FIXME
QColor toGrayScale(const QColor& originalColor)
{
	if (originalColor.Equals(Color.Transparent))
		return originalColor;

	int grayScale = (int)((originalColor.R * .299) + (originalColor.G * .587) + (originalColor.B * .114));
	return Color.FromArgb(grayScale, grayScale, grayScale);
}
*/

QString Utilities::getWindows10Build()
{
	return (QString)_registry.getValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ReleaseId", "");
}

QString Utilities::getOS()
{
	QString buildNumber;
	QString productName = (QString)_registry.getValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName", "");

	if (productName.contains("Windows 7")) {
		currentWindowsVersion = WindowsVersion::Windows7;
	}
	if ((productName.contains("Windows 8")) || (productName.contains("Windows 8.1"))) {
		currentWindowsVersion = WindowsVersion::Windows8;
	}
	if (productName.contains("Windows 10")) {
		buildNumber = (QString)_registry.getValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CurrentBuild", "");

		if (buildNumber.toInt() >= 22000) {
			productName = productName.replace("Windows 10", "Windows 11");
			currentWindowsVersion = WindowsVersion::Windows11;
		} else {
			currentWindowsVersion = WindowsVersion::Windows10;
		}
	}

	if (Program::UNSAFE_MODE) {
		if (productName.contains("Windows Server 2008")) {
			currentWindowsVersion = WindowsVersion::Windows7;
		}
		if (productName.contains("Windows Server 2012")) {
			currentWindowsVersion = WindowsVersion::Windows8;
		}
		if (productName.contains("Windows Server 2016") || productName.contains("Windows Server 2019") || productName.contains("Windows Server 2022")) {
			currentWindowsVersion = WindowsVersion::Windows10;
		}
	}

	return productName;
}

/* FIXME
		internal static string GetBitness()
		{
			string bitness = string.Empty;

			if (Environment.Is64BitOperatingSystem)
			{
				bitness = "You are working with 64-bit";
			}
			else
			{
				bitness = "You are working with 32-bit";
			}

			return bitness;
		}
*/
bool Utilities::isAdmin()
{
	if (SIMULATE) {
		return true;
	}
	// Based on code from KB #Q118626, at http://support.microsoft.com/kb/118626
	BOOL   fReturn         = FALSE;
	DWORD  dwStatus        = 0;
	DWORD  dwAccessMask    = 0;
	DWORD  dwAccessDesired = 0;
	DWORD  dwACLSize       = 0;
	DWORD  dwStructureSize = sizeof(PRIVILEGE_SET);
	PACL   pACL            = NULL;
	PSID   psidAdmin       = NULL;

	HANDLE hToken              = NULL;
	HANDLE hImpersonationToken = NULL;

	PRIVILEGE_SET   ps = {0};
	GENERIC_MAPPING GenericMapping = {0};

	PSECURITY_DESCRIPTOR     psdAdmin           = NULL;
	SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY;

	// Determine if the current thread is running as a user that is a member
	// of the local admins group.  To do this, create a security descriptor
	// that has a DACL which has an ACE that allows only local administrators
	// access.  Then, call AccessCheck with the current thread's token and
	// the security descriptor.  It will say whether the user could access an
	// object if it had that security descriptor.  Note: you do not need to
	// actually create the object.  Just checking access against the
	// security descriptor alone will be sufficient.

	const DWORD ACCESS_READ  = 1;
	const DWORD ACCESS_WRITE = 2;


	// AccessCheck() requires an impersonation token.  We first get a
	// primary token and then create a duplicate impersonation token.
	// The impersonation token is not actually assigned to the thread, but
	// is used in the call to AccessCheck.  Thus, this function itself never
	// impersonates, but does use the identity of the thread.  If the thread
	// was impersonating already, this function uses that impersonation
	// context.
	if (!OpenThreadToken(GetCurrentThread(), TOKEN_DUPLICATE|TOKEN_QUERY, TRUE, &hToken))
	{
		if (GetLastError() != ERROR_NO_TOKEN) {
			goto Exit;
		}

		if (!OpenProcessToken(GetCurrentProcess(),
			TOKEN_DUPLICATE|TOKEN_QUERY, &hToken)) {
			goto Exit;
		}
	}

	if (!DuplicateToken (hToken, SecurityImpersonation, &hImpersonationToken)) {
		goto Exit;
	}

	// Create the binary representation of the well-known SID that
	// represents the local administrators group.  Then create the
	// security descriptor and DACL with an ACE that allows only local
	// admins access.  After that, perform the access check.  This will
	// determine whether the current user is a local admin.
	if (!AllocateAndInitializeSid(&SystemSidAuthority, 2,
		SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0, &psidAdmin)) {
		goto Exit;
	}

	psdAdmin = LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (psdAdmin == NULL) {
		goto Exit;
	}

	if (!InitializeSecurityDescriptor(psdAdmin, SECURITY_DESCRIPTOR_REVISION)) {
		goto Exit;
	}

	// Compute size needed for the ACL.
	dwACLSize = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) +
		GetLengthSid(psidAdmin) - sizeof(DWORD);

	pACL = (PACL)LocalAlloc(LPTR, dwACLSize);
	if (pACL == NULL) {
		goto Exit;
	}

	if (!InitializeAcl(pACL, dwACLSize, ACL_REVISION2)) {
		goto Exit;
	}

	dwAccessMask= ACCESS_READ | ACCESS_WRITE;

	if (!AddAccessAllowedAce(pACL, ACL_REVISION2, dwAccessMask, psidAdmin)) {
		goto Exit;
	}

	if (!SetSecurityDescriptorDacl(psdAdmin, TRUE, pACL, FALSE)) {
		goto Exit;
	}

	// AccessCheck validates a security descriptor somewhat; set the group
	// and owner so that enough of the security descriptor is filled out to
	// make AccessCheck happy.

	SetSecurityDescriptorGroup(psdAdmin, psidAdmin, FALSE);
	SetSecurityDescriptorOwner(psdAdmin, psidAdmin, FALSE);

	if (!IsValidSecurityDescriptor(psdAdmin)) {
		goto Exit;
	}

	dwAccessDesired = ACCESS_READ;

	// Initialize GenericMapping structure even though you
	// do not use generic rights.
	GenericMapping.GenericRead    = ACCESS_READ;
	GenericMapping.GenericWrite   = ACCESS_WRITE;
	GenericMapping.GenericExecute = 0;
	GenericMapping.GenericAll     = ACCESS_READ | ACCESS_WRITE;

	if (!AccessCheck(psdAdmin, hImpersonationToken, dwAccessDesired,
		&GenericMapping, &ps, &dwStructureSize, &dwStatus,
		&fReturn)) {
		fReturn = FALSE;
	}

Exit:
	{
		// Clean up.
		if (pACL)
			LocalFree(pACL);
		if (psdAdmin)
			LocalFree(psdAdmin);
		if (psidAdmin)
			FreeSid(psidAdmin);
		if (hImpersonationToken)
			CloseHandle(hImpersonationToken);
		if (hToken)
			CloseHandle(hToken);
	}

	return fReturn;
}



bool Utilities::isCompatible()
{
	bool legit;
	QString os = getOS();

	if ((os.contains("XP")) || (os.contains("Vista")) || os.contains("Server 2003")) {
		legit = false;
	} else {
		legit = true;
	}
	return legit;
}

void Utilities::runBatchFile(const QString& batchFile)
{
	QProcess p;

	p.start("cmd.exe", QStringList() << "/C" << batchFile);
	p.waitForFinished();
	p.close();
}

void Utilities::importRegistryScript(const QString& scriptFile)
{
	QString path = "\"" + scriptFile + "\"";

	QProcess p;

	p.start("regedit.exe", QStringList() << "/s " << path);

	p.waitForFinished();

}

void Utilities::reboot()
{
	//FIXME Options.SaveSettings();
	QProcess::startDetached("shutdown /r /t 0");
}

void Utilities::disableHibernation()
{
	Utilities::runCommand("powercfg -h off");
	Utilities::runCommand("powercfg -h off");
}

void Utilities::enableHibernation()
{
	Utilities::runCommand("powercfg -h on");
	Utilities::runCommand("powercfg -h on");
}

/*
 * FIXME
void Utilities::ActivateMainForm()
		{
			Program._MainForm.Activate();
		}
		*/

bool Utilities::serviceExists(const QString& serviceName)
{
	QtServiceController controller(serviceName);
	return controller.isInstalled();
	//FIXME ServiceController.GetServices().Any(serviceController => serviceController.ServiceName.Equals(serviceName));
}

void Utilities::stopService(const QString& serviceName)
{
	if (serviceExists(serviceName)) {
		QtServiceController controller(serviceName);
		//if (controller.canStop) {
			controller.stop();
		//}
	}
}

void Utilities::startService(const QString& serviceName)
{
	if (serviceExists(serviceName)) {
		QtServiceController controller(serviceName);

		/*try
				{
					sc.Start();
				}
				catch (Exception ex)
				{
					ErrorLogger.LogError("Utilities.StartService", ex.Message, ex.StackTrace);
				}*/
		controller.start();
	}
}

void Utilities::enableFirewall()
{
	runCommand("netsh advfirewall set currentprofile state on");
}


void Utilities::enableCommandPrompt()
		{
			//using (RegistryKey key = Registry.CurrentUser.CreateSubKey("Software\\Policies\\Microsoft\\Windows\\System"))
			//{
			//	key.SetValue("DisableCMD", 0, RegistryValueKind.DWord);
			//}
		}

void Utilities::enableControlPanel()
		{
//			using (RegistryKey key = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"))
//			{
//				key.SetValue("NoControlPanel", 0, RegistryValueKind.DWord);
//			}
		}

void Utilities::enableFolderOptions()
		{
//			using (RegistryKey key = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"))
//			{
//				key.SetValue("NoFolderOptions", 0, RegistryValueKind.DWord);
//			}
		}

void Utilities::enableRunDialog()
		{
//			using (RegistryKey key = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"))
//			{
//				key.SetValue("NoRun", 0, RegistryValueKind.DWord);
//			}
		}

void Utilities::enableContextMenu()
		{
//			using (RegistryKey key = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"))
//			{
//				key.SetValue("NoViewContextMenu", 0, RegistryValueKind.DWord);
//			}
		}

void Utilities::enableTaskManager()
		{
//			using (RegistryKey key = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"))
//			{
//				key.SetValue("DisableTaskMgr", 0, RegistryValueKind.DWord);
//			}
		}

void Utilities::enableRegistryEditor()
		{
//			using (RegistryKey key = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"))
//			{
//				key.SetValue("DisableRegistryTools", 0, RegistryValueKind.DWord);
//			}
		}

void Utilities::runCommand(const QString& command)
{
	QString errorMessage;

	if (SIMULATE) {
		errorMessage = "simulate - " + command;
	} else {

	}

	//			using (Process p = new Process())
	//			{
	//				p.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
	//				p.StartInfo.FileName = "cmd.exe";
	//				p.StartInfo.Arguments = "/C " + command;
	//				p.StartInfo.CreateNoWindow = true;

	//				try
	//				{
	//					p.Start();
	//					p.WaitForExit();
	//					p.Close();
	//				}
	//				catch (Exception ex)
	//				{

	if (!errorMessage.isEmpty()) {
		LOG_ERROR(errorMessage); //, ex.StackTrace);
	}
}

void Utilities::findFile(const QString& fileName)
		{
			//if (File.Exists(fileName)) Process.Start("explorer.exe", $"/select, \"{fileName}\"");
		}

void Utilities::findFolder(const QString& folder)
		{
			//if (Directory.Exists(folder)) RunCommand($"explorer.exe \"{folder}\"");
		}

QString Utilities::getShortcutTargetFile(const QString& shortcutFilename)
		{
//			string pathOnly = Path.GetDirectoryName(shortcutFilename);
//			string filenameOnly = Path.GetFileName(shortcutFilename);

//			Shell32.Shell shell = new Shell32.Shell();
//			Shell32.Folder folder = shell.NameSpace(pathOnly);
//			Shell32.FolderItem folderItem = folder.ParseName(filenameOnly);

//			if (folderItem != null)
//			{
//				Shell32.ShellLinkObject link = (Shell32.ShellLinkObject)folderItem.GetLink;
//				return link.Path;
//			}

			return "";
		}

void Utilities::restartExplorer()
		{
//			const string explorer = "explorer.exe";
//			string explorerPath = string.Format("{0}\\{1}", Environment.GetEnvironmentVariable("WINDIR"), explorer);

//			foreach (Process process in Process.GetProcesses())
//			{
//				try
//				{
//					if (string.Compare(process.MainModule.FileName, explorerPath, StringComparison.OrdinalIgnoreCase) == 0)
//					{
//						process.Kill();
//					}
//				}
//				catch (Exception ex)
//				{
//					ErrorLogger.LogError("Utilities.RestartExplorer", ex.Message, ex.StackTrace);
//				}
//			}

//			Thread.Sleep(TimeSpan.FromSeconds(1));
//			Process.Start(explorer);
		}

void Utilities::findKeyInRegistry(const QString& key)
		{
//			try
//			{
//				Registry.SetValue(@"HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Applets\Regedit", "LastKey", key);
//				Process.Start("regedit");
//			}
//			catch (Exception ex)
//			{
//				ErrorLogger.LogError("Utilities.FindKeyInRegistry", ex.Message, ex.StackTrace);
//			}
		}

void Utilities::resetConfiguration(bool withoutRestart)
		{
//			try
//			{
//				Directory.Delete(Required.CoreFolder, true);
//			}
//			catch (Exception ex)
//			{
//				ErrorLogger.LogError("Utilities.ResetConfiguration", ex.Message, ex.StackTrace);
//			}
//			finally
//			{
//				if (!withoutRestart)
//				{
//					// BYPASS SINGLE-INSTANCE MECHANISM
//					if (Program.MUTEX != null)
//					{
//						Program.MUTEX.ReleaseMutex();
//						Program.MUTEX.Dispose();
//						Program.MUTEX = null;
//					}

//					Application.Restart();
//				}
//			}
		}

/* FIXME
		internal static Task RunAsync(this Process process)
		{
			var tcs = new TaskCompletionSource<object>();
			process.EnableRaisingEvents = true;
			process.Exited += (s, e) => tcs.TrySetResult(null);

			if (!process.Start()) tcs.SetException(new Exception("Failed to start process."));
			return tcs.Task;
		}*/

QString Utilities::sanitizeFileFolderName(const QString& fileName)
		{
			//char[] invalids = Path.GetInvalidFileNameChars();
			return ""; // string.Join("_", fileName.Split(invalids, StringSplitOptions.RemoveEmptyEntries)).TrimEnd('.');
		}


		// attempt to enable Local Group Policy Editor on Windows 10 Home editions
void Utilities::enableGPEDitor()
		{
			//FIXME Utilities::runBatchFile(Required.ScriptsFolder + "GPEditEnablerInHome.bat");
		}

void Utilities::tryDeleteRegistryValue(bool localMachine, const QString& path, const QString& valueName)
	{

//			if (localMachine) _registry.LocalMachine.OpenSubKey(path, true).DeleteValue(valueName, false);
//			if (!localMachine) _registry.CurrentUser.OpenSubKey(path, true).DeleteValue(valueName, false);
	}

void Utilities::tryDeleteRegistryValueDefaultUsers(const QString& path, const QString& valueName)
{
	//try
	//{
//FIXME		Registry.Users.OpenSubKey(path, true).DeleteValue(valueName, false);
	//}
	//catch { }
}

void Utilities::disableProtectedService(const QString& serviceName)
		{
			/*using (TokenPrivilege.TakeOwnership)
			{
				using (RegistryKey allServicesKey = Registry.LocalMachine.OpenSubKeyWritable(@"SYSTEM\CurrentControlSet\Services"))
				{
					allServicesKey.GrantFullControlOnSubKey(serviceName);
					using (RegistryKey serviceKey = allServicesKey.OpenSubKeyWritable(serviceName))
					{
						if (serviceKey == null) return;

						foreach (const QString& subkeyName in serviceKey.GetSubKeyNames())
						{
							serviceKey.TakeOwnershipOnSubKey(subkeyName);
							serviceKey.GrantFullControlOnSubKey(subkeyName);
						}
						serviceKey.SetValue("Start", "4", RegistryValueKind.DWord);
					}
				}
			}*/
		}

void Utilities::restoreWindowsPhotoViewer()
{
//	const string PHOTO_VIEWER_SHELL_COMMAND =
//		@"%SystemRoot%\System32\rundll32.exe ""%ProgramFiles%\Windows Photo Viewer\PhotoViewer.dll"", ImageView_Fullscreen %1";
//	const string PHOTO_VIEWER_CLSID = "{FFE2A43C-56B9-4bf5-9A79-CC6D4285608A}";

//	Registry.SetValue(@"HKEY_CLASSES_ROOT\Applications\photoviewer.dll\shell\open", "MuiVerb", "@photoviewer.dll,-3043");
//	Registry.SetValue(
//		@"HKEY_CLASSES_ROOT\Applications\photoviewer.dll\shell\open\command", valueName: null,
//		PHOTO_VIEWER_SHELL_COMMAND, RegistryValueKind.ExpandString
//	);
//	Registry.SetValue(@"HKEY_CLASSES_ROOT\Applications\photoviewer.dll\shell\open\DropTarget", "Clsid", PHOTO_VIEWER_CLSID);

//	string[] imageTypes = { "Paint.Picture", "giffile", "jpegfile", "pngfile" };
//	foreach (const QString& type in imageTypes)
//	{
//		Registry.SetValue(
//			$@"HKEY_CLASSES_ROOT\{type}\shell\open\command", valueName: null,
//			PHOTO_VIEWER_SHELL_COMMAND, RegistryValueKind.ExpandString
//		);
//		Registry.SetValue($@"HKEY_CLASSES_ROOT\{type}\shell\open\DropTarget", "Clsid", PHOTO_VIEWER_CLSID);
//	}
}

void Utilities::enableProtectedService(const QString& serviceName)
		{
//			using (TokenPrivilege.TakeOwnership)
//			{
//				using (RegistryKey allServicesKey = Registry.LocalMachine.OpenSubKeyWritable(@"SYSTEM\CurrentControlSet\Services"))
//				{
//					allServicesKey.GrantFullControlOnSubKey(serviceName);
//					using (RegistryKey serviceKey = allServicesKey.OpenSubKeyWritable(serviceName))
//					{
//						if (serviceKey == null) return;

//						foreach (const QString& subkeyName in serviceKey.GetSubKeyNames())
//						{
//							serviceKey.TakeOwnershipOnSubKey(subkeyName);
//							serviceKey.GrantFullControlOnSubKey(subkeyName);
//						}
//						serviceKey.SetValue("Start", "2", RegistryValueKind.DWord);
//					}
//				}
//			}
		}

/** FIXME
RegistryKey Utilities::openSubKeyWritable(this RegistryKey registryKey, const QString& subkeyName, RegistryRights? rights = null)
		{
			RegistryKey subKey = null;

			if (rights == null)
				subKey = registryKey.OpenSubKey(subkeyName, RegistryKeyPermissionCheck.ReadWriteSubTree, RegistryRights.FullControl);
			else
				subKey = registryKey.OpenSubKey(subkeyName, RegistryKeyPermissionCheck.ReadWriteSubTree, rights.Value);

			if (subKey == null)
			{
				ErrorLogger.LogError("Utilities.OpenSubKeyWritable", $"Subkey {subkeyName} not found.", "-");
			}

			return subKey;
		}

		*/


/** fixme
		internal static SecurityIdentifier RetrieveCurrentUserIdentifier()
			=> WindowsIdentity.GetCurrent().User ?? throw new Exception("Unable to retrieve current user SID.");
*/

void Utilities::grantFullControlOnSubKey(const RegistryKey& registryKey, const QString& subkeyName)
		{
//			using (RegistryKey subKey = registryKey.OpenSubKeyWritable(subkeyName,
//				RegistryRights.TakeOwnership | RegistryRights.ChangePermissions
//			))
//			{
//				RegistrySecurity accessRules = subKey.GetAccessControl();
//				SecurityIdentifier currentUser = RetrieveCurrentUserIdentifier();
//				accessRules.SetOwner(currentUser);
//				accessRules.ResetAccessRule(
//					new RegistryAccessRule(
//						currentUser,
//						RegistryRights.FullControl,
//						InheritanceFlags.ContainerInherit | InheritanceFlags.ObjectInherit,
//						PropagationFlags.None,
//						AccessControlType.Allow
//					)
//				);
//				subKey.SetAccessControl(accessRules);
//			}
		}

void Utilities::takeOwnershipOnSubKey(const RegistryKey& registryKey, const QString& subkeyName)
		{
//			using (RegistryKey subKey = registryKey.OpenSubKeyWritable(subkeyName, RegistryRights.TakeOwnership))
//			{
//				RegistrySecurity accessRules = subKey.GetAccessControl();
//				accessRules.SetOwner(RetrieveCurrentUserIdentifier());
//				subKey.SetAccessControl(accessRules);
//			}
		}

/* fixme
		internal static string GetNETFramework()
		{
			string subkey = @"SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full\";
			int netRelease;

			using (RegistryKey ndpKey = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry32).OpenSubKey(subkey))
			{
				if (ndpKey != null && ndpKey.GetValue("Release") != null)
				{
					netRelease = (int)ndpKey.GetValue("Release");
				}
				else
				{
					return "4.0";
				}
			}

			if (netRelease >= 528040)
				return "4.8";
			if (netRelease >= 461808)
				return "4.7.2";
			if (netRelease >= 461308)
				return "4.7.1";
			if (netRelease >= 460798)
				return "4.7";
			if (netRelease >= 394802)
				return "4.6.2";
			if (netRelease >= 394254)
				return "4.6.1";
			if (netRelease >= 393295)
				return "4.6";
			if (netRelease >= 379893)
				return "4.5.2";
			if (netRelease >= 378675)
				return "4.5.1";
			if (netRelease >= 378389)
				return "4.5";

			return "4.0";
		}
*/

void Utilities::searchWith(const QString& term, bool ddg)
		{
//			try
//			{
//				if (ddg) Process.Start(string.Format("https://duckduckgo.com/?q={0}", term));
//				if (!ddg) Process.Start(string.Format("https://www.google.com/search?q={0}", term));
//			}
//			catch { }
		}

		// [!!!]
void Utilities::unlockAllCores()
		{
//			try
//			{
//				Registry.SetValue(@"HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Power\PowerSettings\54533251-82be-4824-96c1-47b60b740d00\0cc5b647-c1df-4637-891a-dec35c318583", "ValueMax", 0, RegistryValueKind.DWord);
//				Registry.SetValue(@"HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Power\PowerSettings\54533251-82be-4824-96c1-47b60b740d00\0cc5b647-c1df-4637-891a-dec35c318583", "ValueMin", 0, RegistryValueKind.DWord);
//			}
//			catch { }
		}

void Utilities::disableHPET()
{
	Utilities::runCommand("bcdedit /deletevalue useplatformclock");
	QThread::msleep(500);
	Utilities::runCommand("bcdedit /set disabledynamictick yes");
}

void Utilities::enableHPET()
{
	Utilities::runCommand("bcdedit /set useplatformclock true");
	QThread::msleep(500);
	Utilities::runCommand("bcdedit /set disabledynamictick no");
}

		// [!!!]
		//internal static void ChangeNumberOfSvcHostByRAM(const QString& ram)
		//{
		//    try
		//    {
		//        float kbs = float.Parse(ram);
		//        Registry.SetValue(@"HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control", "SvcHostSplitThresholdInKB", kbs * 1024 * 1024, RegistryValueKind.DWord);
		//    }
		//    catch { }
		//}

void Utilities::addToStartup()
		{
//			try
//			{
//				using (RegistryKey k = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true))
//				{
//					k.SetValue("Optimizer", Assembly.GetEntryAssembly().Location);
//				}
//			}
//			catch (Exception ex)
//			{
//				ErrorLogger.LogError("Utilities.AddToStartup", ex.Message, ex.StackTrace);
//			}
		}

void Utilities::deleteFromStartup()
		{
//			try
//			{
//				using (RegistryKey k = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true))
//				{
//					k.DeleteValue("Optimizer", false);
//				}
//			}
//			catch (Exception ex)
//			{
//				ErrorLogger.LogError("Utilities.DeleteFromStartup", ex.Message, ex.StackTrace);
//			}
		}

void Utilities::preventProcessFromRunning(const QString& pName)
		{
//			try
//			{
//				using (RegistryKey ifeo = Registry.LocalMachine.OpenSubKeyWritable(@"SOFTWARE\Microsoft\Windows NT\CurrentVersion", RegistryRights.FullControl))
//				{
//					if (ifeo == null) return;

//					ifeo.GrantFullControlOnSubKey("Image File Execution Options");

//					using (RegistryKey k = ifeo.OpenSubKeyWritable("Image File Execution Options", RegistryRights.FullControl))
//					{
//						if (k == null) return;

//						k.CreateSubKey(pName);
//						k.GrantFullControlOnSubKey(pName);

//						using (RegistryKey f = k.OpenSubKeyWritable(pName, RegistryRights.FullControl))
//						{
//							if (f == null) return;

//							f.SetValue("Debugger", @"%windir%\System32\taskkill.exe");
//						}
//					}
//				}
//			}
//			catch (Exception ex)
//			{
//				ErrorLogger.LogError("Utilities.PreventProcessFromRunning", ex.Message, ex.StackTrace);
//			}
//		}
	}


