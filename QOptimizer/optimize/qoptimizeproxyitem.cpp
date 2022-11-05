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

QOptimizeProxyItem::QOptimizeProxyItem(std::shared_ptr<OptimizeBaseItem> item, QObject* parent)
	: QObject(parent), _item(item)
{

}

void QOptimizeProxyItem::activate()
{
	if (_item) {
		_item->activate();
		emit activeChanged();
	}
}

void QOptimizeProxyItem::deactivate()
{
	if (_item) {
		_item->deactivate();
		emit activeChanged();
	}
}

bool QOptimizeProxyItem::isActive()
{
	if (_item) {
		return _item->isActive();
	}
	return false;
}

bool QOptimizeProxyItem::isActiveFromOrigin()
{
	if (_item) {
		return _item->isActiveFromOrigin();
	}
	return false;
}

QString QOptimizeProxyItem::identifier()
{
	if (_item) {
		return _item->identifier();
	}
	return "";
}

QString QOptimizeProxyItem::name()
{
	if (_item) {
		return _item->name();
	}
	return "";
}

QString QOptimizeProxyItem::description()
{
	if (_item) {
		return _item->description();
	}
	return "";
}

QString QOptimizeProxyItem::tags()
{
	if (_item) {
		return _item->tags();
	}
	return "";
}

QString QOptimizeProxyItem::profiles()
{
	if (_item) {
		return _item->profiles();
	}
	return "";
}

void QOptimizeProxyItem::addProxyItem(QOptimizeProxyItem *item)
{
	_proxyItems.append(item);
}

QList<QObject*> QOptimizeProxyItem::childItems()
{
	return _proxyItems;
}
