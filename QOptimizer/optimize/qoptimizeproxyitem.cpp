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

#include "qoptimizeproxyitem.h"

QOptimizeProxyItem::QOptimizeProxyItem(QObject* parent)
	: QObject(parent)
{

}


void QOptimizeProxyItem::activate()
{
	printf("QOptimizeProxyItem::activate()\n");
}

void QOptimizeProxyItem::deactivate()
{

}

bool QOptimizeProxyItem::isActive()
{
	return false;
}

bool QOptimizeProxyItem::isActiveFromOrigin()
{
	return false;
}


QString QOptimizeProxyItem::name()
{
	return "";
}

QString QOptimizeProxyItem::description()
{
	return "";
}

QString QOptimizeProxyItem::tags()
{
	return "";
}

QString QOptimizeProxyItem::profiles()
{
	return "";
}

