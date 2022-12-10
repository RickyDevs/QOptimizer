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

#include "optimizemanager.h"
#include "groupperformancetweaks.h"
#include "groupnetworkservices.h"
#include "groupwindowscustom.h"
#include "optimizemanager.h"

#include <QStringList>

OptimizeManager::OptimizeManager()
{
}

std::vector<std::shared_ptr<OptimizeBaseItem>> OptimizeManager::items()
{
	ensureLoaded();

	return _items;
}

void OptimizeManager::ensureLoaded()
{
	if (_items.size() == 0) {
		_items.push_back(std::make_shared<GroupPerformanceTweaks>());
		_items.push_back(std::make_shared<GroupNetworkServices>());
		_items.push_back(std::make_shared<GroupWindowsCustom>());
	}
}

QString OptimizeManager::groupByIdentifier(const QString& identifier)
{
	for (auto it1 = _items.begin(); it1 != _items.end();) {
		auto subItems = (*it1)->items();
		for (auto it2 = subItems.begin(); it2 != subItems.end();) {
			if ((*it2)->identifier() == identifier) {
				return (*it1)->identifier();
			}
			it2++;
		}
		it1++;
	}
	return QString();
}

QStringList OptimizeManager::allIdentifiersOfItem(const std::shared_ptr<OptimizeBaseItem>& itemPtr)
{
	QStringList list;
	list << itemPtr->identifier();
	auto max = itemPtr->items().size();
	for (int idx = 0; idx < max; idx++) {
		list << itemPtr->items().at(idx)->identifier();
	}
	return list;
}

std::shared_ptr<OptimizeBaseItem> OptimizeManager::itemByIdentifier(const QString &identifier)
{
	for (auto it1 = _items.begin(); it1 != _items.end();) {
		if ((*it1)->identifier() == identifier) {
			return *it1;
		}
		auto subItems = (*it1)->items();
		for (auto it2 = subItems.begin(); it2 != subItems.end();) {
			if ((*it2)->identifier() == identifier) {
				return (*it2);
			}
			it2++;
		}
		it1++;
	}

	return std::shared_ptr<OptimizeBaseItem>();
}

void OptimizeManager::registerImplementation()
{
	Singleton::registerImplementation([](){
		return new OptimizeManager();
	});
}

