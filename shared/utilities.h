#ifndef UTILITIES_H
#define UTILITIES_H


#include <QString>

#include "enums.h"
#include "registry.h"

class Utilities
{
public:
	static WindowsVersion currentWindowsVersion;

	static QString getWindows10Build();
	static QString getOS();

	static bool isAdmin();
	static bool isCompatible();
	static void runBatchFile(const QString& batchFile);
	static void importRegistryScript(const QString& scriptFile);
	static void reboot();
	static void disableHibernation();
	static void enableHibernation();
	static bool serviceExists(const QString& serviceName);
	static void stopService(const QString& serviceName);
	static void startService(const QString& serviceName);
	static void enableFirewall();
	static void enableCommandPrompt();
	static void enableControlPanel();
	static void enableFolderOptions();
	static void enableRunDialog();
	static void enableContextMenu();
	static void enableTaskManager();
	static void enableRegistryEditor();
	static void runCommand(const QString& command);
	static void findFile(const QString& fileName);
	static void findFolder(const QString& folder);
	static QString getShortcutTargetFile(const QString& shortcutFilename);
	static void restartExplorer();
	static void findKeyInRegistry(const QString& key);
	static void resetConfiguration(bool withoutRestart = false);
	static QString sanitizeFileFolderName(const QString& fileName);
	static void enableGPEDitor();
	static void tryDeleteRegistryValue(bool localMachine, const QString& path, const QString& valueName);
	static void tryDeleteRegistryValueDefaultUsers(const QString& path, const QString& valueName);
	static void disableProtectedService(const QString& serviceName);
	static void restoreWindowsPhotoViewer();
	static void enableProtectedService(const QString& serviceName);
	static void grantFullControlOnSubKey(const RegistryKey& registryKey, const QString& subkeyName);
	static void takeOwnershipOnSubKey(const RegistryKey& registryKey, const QString& subkeyName);
	static void searchWith(const QString& term, bool ddg);
	static void unlockAllCores();
	static void disableHPET();
	static void enableHPET();
	static void addToStartup();
	static void deleteFromStartup();
	static void preventProcessFromRunning(const QString& pName);

	static QString getAlternativeCpuName();
private:
	Utilities() = default;

	static Registry _registry;
};

#endif // UTILITIES_H
