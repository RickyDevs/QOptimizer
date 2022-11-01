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
#include "performancetweaks.h"

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


		//static std::vector<std::shared_ptr<OptimizeBaseItem>> emptyVector;



		//std::shared_ptr<OptimizeStdCalls> xxx  = std::make_shared<OptimizeStdCalls>();

		//xxx->_name = "4.96 MB -- reduce dump file size";
		//xxx->_description = "27/07/2022 -- reduce dump file size";

		_items.push_back(std::make_shared<PerformanceTweaks>());


		//if (result.size() > 0) {
			//return result;
		//

		//return emptyVector;
	}
}
