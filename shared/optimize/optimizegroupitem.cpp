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

#include "optimizegroupitem.h"

OptimizeGroupItem::OptimizeGroupItem(const char* identifier)
	: OptimizeBaseItem(identifier)
{
}

std::vector<std::shared_ptr<OptimizeBaseItem>> OptimizeGroupItem::items()
{
	if (_items.size() == 0) {
		loadItems();
	}
	return _items;
}

bool OptimizeGroupItem::isActiveFromOrigin()
{
	return false;
}

void OptimizeGroupItem::checkOriginalStateImpl()
{
	// no action
}

