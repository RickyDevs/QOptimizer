/****************************************************************************
**
** QOptimizer
** Copyright (C) 2022 by RickyDevs
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "program.h"

#include "mainmodel.h"

#define QUOTE(x) #x
#define TO_VERSION(x) QUOTE(x)


bool Program::UNSAFE_MODE = false;

Program::Program(QObject *parent)
	: QObject(parent)
{
	_wbemServices = new QWbemServices(this);

}

//Program::initServices()
//{

//}

QVariant Program::createModel(const QString& modelName) {

	if (modelName == "MainModel") {
		MainModel* model = new MainModel(_wbemServices, this);
		return QVariant::fromValue(model);
	}

	//	printf("%d %s", modelData.type(), modelData.typeName());


	//return "From c++ " + modelName;
	return QVariant();
}

QString Program::version()
{
	return QString::fromUtf8(TO_VERSION(QO_VERSION));
}

QString Program::buildDate()
{
	return QString::fromUtf8(__DATE__);
}
