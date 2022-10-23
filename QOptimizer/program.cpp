#include "program.h"

#include "mainmodel.h"

bool Program::UNSAFE_MODE = false;

Program::Program(QObject *parent)
	: QObject(parent)
{
	wbemServices = new QWbemServices(this);
}

//Program::initServices()
//{

//}

QVariant Program::createModel(const QString& modelName, const QVariantList& modelData) {

	MainModel* model = new MainModel(modelData, this);

//	printf("%d %s", modelData.type(), modelData.typeName());

	return QVariant::fromValue(model);

	//return "From c++ " + modelName;
}
