#ifndef CONFIGOPS_H
#define CONFIGOPS_H

#include <QString>
#include <QObject>

class Config;

class ConfigOps
{
public:
	static Config* parseConfigFile(const QString& file, QObject* parent);

	static void processConfigFile(const QString& file, QObject* parent);
private:
	ConfigOps() = default;
};

#endif // CONFIGOPS_H

