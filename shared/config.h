#ifndef SILENTCONFIG_H
#define SILENTCONFIG_H

#include <QObject>

class Config : public QObject
{
	Q_OBJECT
public:
	explicit Config(QObject *parent = 0);

	Q_PROPERTY(int WindowsVersion MEMBER windowsVersion)
	Q_PROPERTY(QString EnablePerformanceTweaks MEMBER enablePerformanceTweaks)
	Q_PROPERTY(QString DisableNetworkThrottling MEMBER disableNetworkThrottling)
	Q_PROPERTY(QString DisableWindowsDefender MEMBER disableWindowsDefender)
	Q_PROPERTY(QString DisableSystemRestore MEMBER disableSystemRestore)
	Q_PROPERTY(QString DisablePrintService MEMBER disablePrintService)
	Q_PROPERTY(QString DisableMediaPlayerSharing MEMBER disableMediaPlayerSharing)
	Q_PROPERTY(QString DisableErrorReporting MEMBER disableErrorReporting)
	Q_PROPERTY(QString DisableHomeGroup MEMBER disableHomeGroup)
	Q_PROPERTY(QString DisableSuperfetch MEMBER disableSuperfetch)
	Q_PROPERTY(QString DisableTelemetryTasks MEMBER disableTelemetryTasks)
	Q_PROPERTY(QString DisableCompatibilityAssistant MEMBER disableCompatibilityAssistant)
	Q_PROPERTY(QString DisableFaxService MEMBER disableFaxService)
	Q_PROPERTY(QString DisableSmartScreen MEMBER disableSmartScreen)
	Q_PROPERTY(QString DisableCloudClipboard MEMBER disableCloudClipboard)
	Q_PROPERTY(QString DisableStickyKeys MEMBER disableStickyKeys)
	Q_PROPERTY(QString DisableHibernation MEMBER disableHibernation)
	Q_PROPERTY(QString DisableSMB1 MEMBER disableSMB1)
	Q_PROPERTY(QString DisableSMB2 MEMBER disableSMB2)
	Q_PROPERTY(QString DisableNTFSTimeStamp MEMBER disableNTFSTimeStamp)




	int windowsVersion;
	QString enablePerformanceTweaks;
	QString disableNetworkThrottling;
	QString disableWindowsDefender;
	QString disableSystemRestore;
	QString disablePrintService;
	QString disableMediaPlayerSharing;
	QString disableErrorReporting;
	QString disableHomeGroup;
	QString disableSuperfetch;
	QString disableTelemetryTasks;
	QString disableCompatibilityAssistant;
	QString disableFaxService;
	QString disableSmartScreen;
	QString disableCloudClipboard;
	QString disableStickyKeys;
	QString disableHibernation;
	QString disableSMB1;
	QString disableSMB2;
	QString disableNTFSTimeStamp;
};

#endif // SILENTCONFIG_H
