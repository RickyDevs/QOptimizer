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
