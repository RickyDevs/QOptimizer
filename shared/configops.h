#ifndef CONFIGOPS_H
#define CONFIGOPS_H

#include <QString>

class Config;

class ConfigOps
{
public:
	static Config* parseConfigFile(const QString& file);

	static void processConfigFile(const QString& file);

private:
	ConfigOps() = default;
};

#endif // CONFIGOPS_H
