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

#include "optimizebaseitem.h"
#include <QThread>

OptimizeBaseItem::OptimizeBaseItem(const char* identifier)
{
	Q_ASSERT(identifier != nullptr);
	_identifier = identifier;
}

QString OptimizeBaseItem::identifier()
{
	return QString::fromLocal8Bit(_identifier);
}

void OptimizeBaseItem::activate()
{
	printf("OptimizeBaseItem::Activate\n");
	QThread::msleep(100);

}

void OptimizeBaseItem::deactivate()
{
	printf("OptimizeBaseItem::deactivate\n");
	QThread::msleep(50);
}

bool OptimizeBaseItem::isActive()
{
	return false;
}

bool OptimizeBaseItem::isActiveFromOrigin()
{
	return false;
}


QString OptimizeBaseItem::name()
{
	return "";
}

QString OptimizeBaseItem::description()
{
	return "";
}

QString OptimizeBaseItem::tags() const
{
	return "";
}

QString OptimizeBaseItem::profiles() const
{
	return "";
}

void OptimizeBaseItem::checkOriginalStateImpl()
{
//TODO	Q_ASSERT(false);
	qDebug("TODO checkOriginalStateImpl %s", _identifier);
}

std::vector<std::shared_ptr<OptimizeBaseItem>> OptimizeBaseItem::items()
{
	static std::vector<std::shared_ptr<OptimizeBaseItem>> emptyVector;
	return emptyVector;
}
