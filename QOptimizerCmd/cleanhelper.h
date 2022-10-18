#ifndef CLEANHELPER_H
#define CLEANHELPER_H

#include <QStandardPaths>

class CleanHelper
{
public:
	// SYSTEM FOLDERS
	static QString System32Folder; // QStandardPaths::locate(Environment.SpecialFolder.System);
//			internal static readonly string TempFolder = Path.GetTempPath();
//			internal static readonly string ProfileAppDataRoaming = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
	static QString ProgramData; //Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData);
//			internal static readonly string ProfileAppDataLocal = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
//			//internal static readonly string ProfileAppDataLocalLow = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + "Low";
//			//internal static readonly string OSDrive = System32Folder.Substring(0, 3);
//			internal static readonly string OSDriveWindows = Environment.GetEnvironmentVariable("WINDIR", EnvironmentVariableTarget.Machine);

//			// INTERNET EXPLORER CACHE
//			static string[] ieCache =
//			{
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\INetCache\\IE"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WebCache.old")
//			};

//			// CHROME FOLDERS
//			static string chromeFolder = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "AppData\\Local\\Google\\Chrome\\User Data");
//			static string[] chromeUserDataCacheDirs = { "Default\\Cache", "Default\\Code Cache\\", "Default\\GPUCache\\", "ShaderCache", "Default\\Service Worker\\CacheStorage\\", "Default\\Service Worker\\ScriptCache\\", "GrShaderCache\\GPUCache\\", "Default\\File System\\", "Default\\JumpListIconsMostVisited\\", "Default\\JumpListIconsRecentClosed\\", "Default\\Service Worker\\Database" };
//			static string chromePasswordsDir = Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\Login Data");
//			static string[] chromeSessionDirs =
//			{
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\Sessions"),
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\Session Storage"),
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\Extension State"),
//			};
//			static string[] chromeCookiesDirs =
//			{
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\IndexedDB"),
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\Cookies"),
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\Cookies-journal")
//			};
//			static string[] chromeHistoryDirs =
//			{
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\History"),
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\History Provider Cache"),
//				Path.Combine(ProfileAppDataLocal, "Google\\Chrome\\User Data\\Default\\History-journal")
//			};

//			// FIREFOX FOLDERS
//			static string firefoxRoaming = Path.Combine(ProfileAppDataRoaming, "Mozilla\\Firefox\\Profiles");
//			static string firefoxLocal = Path.Combine(ProfileAppDataLocal, "Mozilla\\Firefox\\Profiles");

//			// EDGE FOLDERS
//			static string edgeHistory = Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\History");
//			static string[] edgeCookies =
//			{
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Cookies"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\IndexedDB")
//			};
//			static string[] edgeSession =
//			{
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Sessions"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Session Storage"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Extension State")
//			};
//			static string[] edgeCache =
//			{
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Cache"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Code Cache"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\GPUCache"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\ShaderCache"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Service Worker\\CacheStorage"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Service Worker\\ScriptCache"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\GrShaderCache\\GPUCache"),
//				Path.Combine(ProfileAppDataLocal, "Microsoft\\Edge\\User Data\\Default\\Service Worker\\Database"),
//			};

//			// BRAVE FOLDERS
//			static string braveFolder = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data");
//			static string[] braveUserDataCacheDirs = { "Default\\Cache", "Default\\Code Cache\\", "Default\\GPUCache\\", "ShaderCache", "Default\\Service Worker\\CacheStorage\\", "Default\\Service Worker\\ScriptCache\\", "GrShaderCache\\GPUCache\\", "Default\\File System\\", "Default\\JumpListIconsMostVisited\\", "Default\\JumpListIconsRecentClosed\\", "Default\\Service Worker\\Database" };
//			static string bravePasswordsDir = Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\Login Data");
//			static string[] braveSessionDirs =
//			{
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\Sessions"),
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\Session Storage"),
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\Extension State"),
//			};
//			static string[] braveCookiesDirs =
//			{
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\IndexedDB"),
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\Cookies"),
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\Cookies-journal")
//			};
//			static string[] braveHistoryDirs =
//			{
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\History"),
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\History Provider Cache"),
//				Path.Combine(ProfileAppDataLocal, "BraveSoftware\\Brave-Browser\\User Data\\Default\\History-journal")
//			};


//			internal static List<string> PreviewCleanList = new List<string>();

//			internal static ByteSize PreviewSizeToBeFreed = new ByteSize(0);

	static void previewFolder(const QString& path);
	static void clean();
	static void emptyRecycleBin();
	static void previewTemp();
	static void previewMinidumps();
	static void previewErrorReports();
	static qint64 calculateSize(const QString& fileOrFolder);
	static void previewEdgeClean(bool cache, bool cookies, bool seachHistory, bool session);
	static void previewInternetExplorerCache();
	static void previewFireFoxClean(bool cache, bool cookies, bool searchHistory);
	static void previewBraveClean(bool cache, bool cookies, bool searchHistory, bool session, bool passwords);
	static void previewChromeClean(bool cache, bool cookies, bool searchHistory, bool session, bool passwords);


private:
	CleanHelper() = default;
};

#endif // CLEANHELPER_H
