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

#include "groupnetworkservices.h"
#include "strategyoptimizeitem.h"
#include "tagshelper.h"

GroupNetworkServices::GroupNetworkServices()
{
}

QString GroupNetworkServices::name()
{
	return QString::fromLatin1("GroupNetworkServices");
}

QString GroupNetworkServices::description()
{
	return QString::fromLatin1("GroupNetworkServices description");
}


void GroupNetworkServices::loadItems()
{
	auto item = std::make_shared<StrategyOptimizeItem>("Copy/Move to options");
	item->setDetails("StrategyTest", "StrategyTest description");
	item->setTags(TAGS1(k_tagNetwork));
	item->setStrategyList(
		{
			RegistryBuilder(RegistryStrategy::classesRoot("AllFilesystemObjects\\shellex\\ContextMenuHandlers"))
					.activeValue({"", "{C2FBB630-2971-11D1-A18C-00C04FD75D13}", "Copy To"})
					.deactiveValue({"Copy To"}),
			RegistryBuilder(RegistryStrategy::classesRoot("AllFilesystemObjects\\shellex\\ContextMenuHandlers"))
					.activeValue({"", "{C2FBB631-2971-11D1-A18C-00C04FD75D13}", "Move To"})
					.deactiveValue({"Move To"})

		});

	_items.push_back(item);
}
