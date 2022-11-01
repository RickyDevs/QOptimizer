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

#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <QVariant>
#include "qwbemservices.h"

class Program : public QObject
{
	Q_OBJECT
public:
	explicit Program(QObject *parent = 0);

	Q_PROPERTY(QString version READ version CONSTANT)
	Q_PROPERTY(QString buildDate READ buildDate CONSTANT)

	Q_INVOKABLE QVariant createModel(const QString& modelName);

public:
	static bool UNSAFE_MODE;

//public slots:
//	 void initServices();
	QString version();
	QString buildDate();

private:
	QWbemServices* _wbemServices;
};

#endif // PROGRAM_H
