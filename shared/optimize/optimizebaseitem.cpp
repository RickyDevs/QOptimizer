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

OptimizeBaseItem::OptimizeBaseItem()
{
}

void OptimizeBaseItem::activate()
{

}

void OptimizeBaseItem::deactivate()
{

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

QString OptimizeBaseItem::tags()
{
	return "";
}

QString OptimizeBaseItem::profiles()
{
	return "";
}

void OptimizeBaseItem::checkOriginalStateImpl()
{
	Q_ASSERT(false);
}
