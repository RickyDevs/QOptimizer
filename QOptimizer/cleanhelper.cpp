#include "cleanhelper.h"

QString CleanHelper::System32Folder;


QString CleanHelper::ProgramData;


void CleanHelper::previewFolder(const QString& path)
{
//	try
//	{
//		if (File.Exists(path))
//		{
//			PreviewCleanList.Add(path);
//			return;
//		}

//		DirectoryInfo di = new DirectoryInfo(path);

//		foreach (FileInfo file in di.GetFiles("*", SearchOption.AllDirectories))
//		{
//			try
//			{
//				PreviewCleanList.Add(file.FullName);
//			}
//			catch { }
//		}

//		foreach (DirectoryInfo dir in di.GetDirectories("*", SearchOption.AllDirectories))
//		{
//			try
//			{
//				PreviewCleanList.Add(dir.FullName);
//			}
//			catch { }
//		}
//	}
//	catch { }
}

void CleanHelper::clean()
{
//	foreach (string x in PreviewCleanList)
//	{
//		try
//		{
//			if (Directory.Exists(x)) Directory.Delete(x);
//			if (File.Exists(x)) File.Delete(x);
//		}
//		catch { }
//	}
}

void CleanHelper::emptyRecycleBin()
{
	//SHEmptyRecycleBin(IntPtr.Zero, null, RecycleFlag.SHERB_NOSOUND | RecycleFlag.SHERB_NOCONFIRMATION);
}

void CleanHelper::previewTemp()
{
//	PreviewFolder(TempFolder);
//	PreviewSizeToBeFreed += CalculateSize(TempFolder);
}

void CleanHelper::previewMinidumps()
{
//	PreviewFolder(Path.Combine(OSDriveWindows, "Minidump"));
//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(OSDriveWindows, "Minidump"));
}

void CleanHelper::previewErrorReports()
{
//	PreviewFolder(Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WER\\ReportArchive"));
//	PreviewFolder(Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WER\\ReportQueue"));
//	PreviewFolder(Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WER\\Temp"));
//	PreviewFolder(Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WER\\ERC"));
//	PreviewFolder(Path.Combine(ProgramData, "Microsoft\\Windows\\WER\\ReportArchive"));
//	PreviewFolder(Path.Combine(ProgramData, "Microsoft\\Windows\\WER\\ReportQueue"));
//	PreviewFolder(Path.Combine(ProgramData, "Microsoft\\Windows\\WER\\Temp"));
//	PreviewFolder(Path.Combine(ProgramData, "Microsoft\\Windows\\WER\\ERC"));

//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WER\\ReportArchive"));
//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WER\\ReportQueue"));
//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WER\\Temp"));
//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(ProfileAppDataLocal, "Microsoft\\Windows\\WER\\ERC"));
//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(ProgramData, "Microsoft\\Windows\\WER\\ReportArchive"));
//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(ProgramData, "Microsoft\\Windows\\WER\\ReportQueue"));
//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(ProgramData, "Microsoft\\Windows\\WER\\Temp"));
//	PreviewSizeToBeFreed += CalculateSize(Path.Combine(ProgramData, "Microsoft\\Windows\\WER\\ERC"));
}

qint64 CleanHelper::calculateSize(const QString& fileOrFolder)
{
	qint64 totalSize = 0;
//	bool isFolder = Directory.Exists(fileOrFolder);

//	try
//	{
//		if (isFolder)
//		{
//			DirectoryInfo dir = new DirectoryInfo(fileOrFolder);
//			totalSize += totalSize.AddBytes(dir.EnumerateFiles("*", SearchOption.AllDirectories).Sum(file => file.Length));
//		}
//		else
//		{
//			FileInfo file = new FileInfo(fileOrFolder);
//			totalSize = totalSize.AddBytes(file.Length);
//		}
//	}
//	catch { }

	return totalSize;
}

void CleanHelper::previewEdgeClean(bool cache, bool cookies, bool seachHistory, bool session)
{
//	if (cache)
//	{
//		foreach (string x in edgeCache)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}

//	if (cookies)
//	{
//		foreach (string x in edgeCookies)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}

//	if (seachHistory)
//	{
//		PreviewFolder(edgeHistory);
//		PreviewSizeToBeFreed += CalculateSize(edgeHistory);
//	}

//	if (session)
//	{
//		foreach (string x in edgeSession)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}
}

void CleanHelper::previewInternetExplorerCache()
{
//	foreach (string x in ieCache)
//	{
//		PreviewFolder(x);
//		PreviewSizeToBeFreed += CalculateSize(x);
//	}
}

void CleanHelper::previewFireFoxClean(bool cache, bool cookies, bool searchHistory)
{
//	foreach (string x in Directory.EnumerateDirectories(firefoxRoaming))
//	{
//		if (x.ToLowerInvariant().Contains("release"))
//		{
//			if (cookies)
//			{
//				PreviewFolder(Path.Combine(x, "cookies.sqlite"));
//				PreviewSizeToBeFreed += CalculateSize(Path.Combine(x, "cookies.sqlite"));
//			}

//			if (searchHistory)
//			{
//				PreviewFolder(Path.Combine(x, "places.sqlite"));
//				PreviewSizeToBeFreed += CalculateSize(Path.Combine(x, "places.sqlite"));
//			}

//			if (cache)
//			{
//				PreviewFolder(Path.Combine(x, "shader-cache"));
//				PreviewSizeToBeFreed += CalculateSize(Path.Combine(x, "shader-cache"));
//			}
//		}
//	}

//	if (cache)
//	{
//		foreach (string x in Directory.EnumerateDirectories(firefoxLocal))
//		{
//			if (x.ToLowerInvariant().Contains("release"))
//			{
//				PreviewFolder(Path.Combine(x, "cache2"));
//				PreviewSizeToBeFreed += CalculateSize(Path.Combine(x, "cache2"));
//			}
//		}
//	}
}

void CleanHelper::previewBraveClean(bool cache, bool cookies, bool searchHistory, bool session, bool passwords)
{
//	if (cache)
//	{
//		foreach (string x in braveUserDataCacheDirs)
//		{
//			PreviewFolder(Path.Combine(braveFolder, x));
//			PreviewSizeToBeFreed += CalculateSize(Path.Combine(braveFolder, x));
//		}
//	}

//	if (session)
//	{
//		foreach (string x in braveSessionDirs)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}

//	if (cookies)
//	{
//		foreach (string x in braveCookiesDirs)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}

//	if (searchHistory)
//	{
//		foreach (string x in braveHistoryDirs)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}

//	if (passwords)
//	{
//		PreviewFolder(bravePasswordsDir);
//		PreviewSizeToBeFreed += CalculateSize(bravePasswordsDir);
//	}
}

void CleanHelper::previewChromeClean(bool cache, bool cookies, bool searchHistory, bool session, bool passwords)
{
//	if (cache)
//	{
//		foreach (string x in chromeUserDataCacheDirs)
//		{
//			PreviewFolder(Path.Combine(chromeFolder, x));
//			PreviewSizeToBeFreed += CalculateSize(Path.Combine(chromeFolder, x));
//		}
//	}

//	if (session)
//	{
//		foreach (string x in chromeSessionDirs)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}

//	if (cookies)
//	{
//		foreach (string x in chromeCookiesDirs)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}

//	if (searchHistory)
//	{
//		foreach (string x in chromeHistoryDirs)
//		{
//			PreviewFolder(x);
//			PreviewSizeToBeFreed += CalculateSize(x);
//		}
//	}

//	if (passwords)
//	{
//		PreviewFolder(chromePasswordsDir);
//		PreviewSizeToBeFreed += CalculateSize(chromePasswordsDir);
//	}
}

