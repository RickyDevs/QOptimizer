#include "configops.h"

#include <QFile>
#include <QTextStream>

#include "jsonconvert.h"
#include "config.h"
#include "errorlogger.h"
#include "utilities.h"

Config* ConfigOps::parseConfigFile(const QString& file)
{
	//printf("cur dir %s\n", QDir::currentPath().toStdString().c_str());
	QFile f("../shared/conf/" + file);
	if (f.exists()) {
		f.open(QIODevice::ReadOnly);
		QTextStream in(&f);
		return JsonConvert::deserializeObject<Config>(in.readAll());
	} else {
		LOG_ERROR("Can't find file: " + file);
	}
	return nullptr;
}

bool isTrue(const QString& text) {
	return text == "true";
}

void ConfigOps::processConfigFile(const QString& file) {
	Config* pCfg = parseConfigFile(file);
	if (pCfg && pCfg->windowsVersion == 10) {
		printf("10\n");

		printf("%d", isTrue(pCfg->disableCloudClipboard));
	}
}
