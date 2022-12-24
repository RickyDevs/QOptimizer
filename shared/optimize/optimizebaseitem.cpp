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

#include "iactivefromorigin.h"
#include "optimizemanager.h"

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
	qWarning("OptimizeBaseItem::Activate? %s", _identifier);
	QThread::msleep(600);

}

void OptimizeBaseItem::deactivate()
{
	qWarning("OptimizeBaseItem::deactivate? %s", _identifier);
	QThread::msleep(250);
}

bool OptimizeBaseItem::isActive()
{
	return false;
}

bool OptimizeBaseItem::isActiveFromOrigin()
{
	QString currentGroup = IActiveFromOrigin::instance().group();
	QString itemGroup = OptimizeManager::instance().groupByIdentifier(_identifier);

	if (itemGroup != currentGroup) {
		IActiveFromOrigin::instance().endGroup();
		IActiveFromOrigin::instance().startGroup(qPrintable(itemGroup));
	}

	return IActiveFromOrigin::instance().isActive(_identifier);
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
	QString itemGroup = OptimizeManager::instance().groupByIdentifier(_identifier);
	QString currentGroup = IActiveFromOrigin::instance().group();

	if (itemGroup != currentGroup) {
		IActiveFromOrigin::instance().endGroup();
		IActiveFromOrigin::instance().startGroup(qPrintable(itemGroup));
	}

	if (IActiveFromOrigin::instance().exists(_identifier)) {
		return;
	}

	bool active = isActive();
	IActiveFromOrigin::instance().setActive(_identifier, active);
	qDebug("checkOriginalStateImpl %s : %s %d", qPrintable(itemGroup), _identifier, active);
}

std::vector<std::shared_ptr<OptimizeBaseItem>> OptimizeBaseItem::items()
{
	static std::vector<std::shared_ptr<OptimizeBaseItem>> emptyVector;
	return emptyVector;
}
