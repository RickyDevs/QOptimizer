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

bool match(OptimizeBaseItem& item, const QVariantMap& queryMap)
{
	bool found = false;
	QMapIterator<QString, QVariant> it(queryMap);
	while (it.hasNext()) {
		it.next();
		if (it.key() == "tag") {
			found = item.tags().split(' ', QString::SkipEmptyParts).contains(it.value().toString());
		}
	}
	if (!found) {
		for (std::shared_ptr<OptimizeBaseItem>& child : item.items()) {
			if (match(*child, queryMap)) {
				return true;
			}
		}
	}

	return found;
}

QOptimizeProxyManager::QOptimizeProxyManager(QObject *parent)
	: QObject(parent)
{
	_optimizeManager.reset(new OptimizeManager());
}

QList<QObject*> QOptimizeProxyManager::query(const QVariantMap& queryMap)
{
	QList<QObject*> list;
	auto result =_optimizeManager->items();
	for (std::shared_ptr<OptimizeBaseItem>& item : result) {
		if (!match(*item, queryMap)) {
			continue;
		}
		auto proxyItem = new QOptimizeProxyItem(item, this);

		for (std::shared_ptr<OptimizeBaseItem>& child : item->items()) {
			if (!match(*child, queryMap)) {
				continue;
			}
			proxyItem->addProxyItem(new QOptimizeProxyItem(child, this));
		}
		list.append(proxyItem);
	}
	return list;
}

