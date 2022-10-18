#ifndef REQUIRED_H
#define REQUIRED_H

#include <QStringList>

#include "cleanhelper.h"

class Required
{
public:

//static const QString CoreFolder = CleanHelper::ProgramData + "\\Optimizer\\";
//static const QString ReadyMadeMenusFolder = CleanHelper::ProgramData + "\\Optimizer\\ReadyMadeMenus\\";
//static const QString ScriptsFolder = CleanHelper::ProgramData + "\\Optimizer\\Required\\";
//static const QString ExtractedIconsFolder = CleanHelper::ProgramData + "\\Optimizer\\ExtractedIcons\\";
//static const QString FavIconsFolder = CleanHelper::ProgramData + "\\Optimizer\\FavIcons\\";
//static const QString StartupItemsBackupFolder = CleanHelper::ProgramData + "\\Optimizer\\StartupBackup\\";

//static const QStringList readyMadeMenusItems =
//			{
//				ReadyMadeMenusFolder + "DesktopShortcuts.reg",
//				ReadyMadeMenusFolder + "SystemShortcuts.reg",
//				ReadyMadeMenusFolder + "PowerMenu.reg",
//				ReadyMadeMenusFolder + "SystemTools.reg",
//				ReadyMadeMenusFolder + "WindowsApps.reg",
//				ReadyMadeMenusFolder + "InstallTakeOwnership.reg",
//				ReadyMadeMenusFolder + "RemoveTakeOwnership.reg",
//			};

//static const QStringList readyMadeMenusFiles =
//			{
//				Properties.Resources.DesktopShortcuts,
//				Properties.Resources.SystemShortcuts,
//				Properties.Resources.PowerMenu,
//				Properties.Resources.SystemTools,
//				Properties.Resources.WindowsApps,
//				Properties.Resources.InstallTakeOwnership,
//				Properties.Resources.RemoveTakeOwnership
//			};

//static const QStringList scriptItems =
//			{
//				ScriptsFolder + "DisableOfficeTelemetryTasks.bat",
//				ScriptsFolder + "DisableOfficeTelemetryTasks.reg",
//				ScriptsFolder + "EnableOfficeTelemetryTasks.bat",
//				ScriptsFolder + "EnableOfficeTelemetryTasks.reg",
//				ScriptsFolder + "DisableTelemetryTasks.bat",
//				ScriptsFolder + "EnableTelemetryTasks.bat",
//				ScriptsFolder + "DisableXboxTasks.bat",
//				ScriptsFolder + "EnableXboxTasks.bat",
//				ScriptsFolder + "OneDrive_Uninstaller.cmd",
//				ScriptsFolder + "GPEditEnablerInHome.bat",
//				ScriptsFolder + "AddOpenWithCMD.reg"
//			};

//static const QStringList scriptFiles =
//			{
//				Properties.Resources.DisableOfficeTelemetryTasks,
//				Properties.Resources.DisableOfficeTelemetry,
//				Properties.Resources.EnableOfficeTelemetryTasks,
//				Properties.Resources.EnableOfficeTelemetry,
//				Properties.Resources.DisableTelemetryTasks,
//				Properties.Resources.EnableTelemetryTasks,
//				Properties.Resources.DisableXboxTasks,
//				Properties.Resources.EnableXboxTasks,
//				Encoding.UTF8.GetString(Properties.Resources.OneDrive_Uninstaller),
//				Properties.Resources.GPEditEnablerInHome,
//				Properties.Resources.AddOpenWithCMD
//			};


	void deploy();

private:
	Required() = default;
};

#endif // REQUIRED_H
