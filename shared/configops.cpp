#include "configops.h"

#include <QFile>
#include <QTextStream>
#include <QVector>
#include <memory>

#include "jsonconvert.h"
#include "config.h"
#include "errorlogger.h"
#include "utilities.h"



Config* ConfigOps::parseConfigFile(const QString& file, QObject* parent)
{
	//printf("cur dir %s\n", QDir::currentPath().toStdString().c_str());
	QFile f("../shared/conf/" + file);
	if (f.exists()) {
		f.open(QIODevice::ReadOnly);
		QTextStream in(&f);
		//return JsonConvert::deserializeObject<Config>(in.readAll());



		std::unique_ptr<QVector<Config*>> xxx(JsonConvert::deserializeObject<QVector<Config*>>(in.readAll(), parent));

		printf("%d", xxx->size());
		return Q_NULLPTR;

	} else {
		LOG_ERROR("Can't find file: " + file);
	}
	return Q_NULLPTR;
}

bool isTrue(const QString& text) {
	return text == "true";
}

void ConfigOps::processConfigFile(const QString& file, QObject* parent) {
	Config* pCfg = parseConfigFile(file, parent);
	if (pCfg && pCfg->windowsVersion == 10) {
		printf("10\n");

		printf("%d", isTrue(pCfg->disableCloudClipboard));
	}
}
