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

#include "qoptimizeproxymanager.h"

QOptimizeProxyManager::QOptimizeProxyManager(QObject *parent)
	: QObject(parent)
{

}

/*
QVariantList QOptimizeProxyManager::query()
{
	printf("TODO:QOptimizeProxyManager::query ");

	QVariantList list;

	list.append(QVariant());

	return list;
}
*/

/*
QList<QOptimizeProxyItem*> QOptimizeProxyManager::query()
{
	printf("TODO:QOptimizeProxyManager::query ");

	QList<QOptimizeProxyItem*> list;

	list.append(new QOptimizeProxyItem(this));

	return list;
}
*/



QList<QObject*> QOptimizeProxyManager::query()
{
	printf("TODO:QOptimizeProxyManager::query \n");

	QList<QObject*> list;

	list.append(new QOptimizeProxyItem(this));

	return list;
}

