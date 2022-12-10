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

#include "groupperformancetweaks.h"
#include "optimizestdcalls.h"
#include "strategyoptimizeitem.h"
#include "tagshelper.h"

GroupPerformanceTweaks::GroupPerformanceTweaks()
	: OptimizeGroupItem("PerformanceTweaks")
{
}

QString GroupPerformanceTweaks::name()
{
	return QString::fromLatin1("Performance Tweaks");
}

QString GroupPerformanceTweaks::description()
{
	return QString::fromLatin1("Performance Tweaks description");
}

void GroupPerformanceTweaks::loadItems()
{
	//Q_ASSERT(false);

	// Builder class ??

	auto xxx = std::make_shared<OptimizeStdCalls>("AutoCompleteRunDialog");
	xxx->_name = "Enable auto-complete in Run Dialog";
	xxx->_description = "";
//	xxx->_tags = TAGS1(tags::k_windows);
	_items.push_back(xxx);

	xxx = std::make_shared<OptimizeStdCalls>("DumpFileSize");
	xxx->_name = "Reduce dump file size";
	xxx->_description = "TODO: Disk Drives";
	xxx->_tags = TAGS1(k_tagDiskDrive);
	_items.push_back(xxx);


	auto item = std::make_shared<StrategyOptimizeItem>("RemoteAssistance");
	item->setDetails("Disable Remote Assistance", "Disable Remote Assistance");
	item->setTags(TAGS2(k_tagNetwork, k_tagProcessor));
	item->setStrategyList(
		{
			RegistryBuilder(RegistryStrategy::localMachine("System\\CurrentControlSet\\Control\\Remote Assistance"))
					.activeValue({"fAllowToGetHelp", 0})
					.deactiveValue({"fAllowToGetHelp", 1})
		});

	_items.push_back(item);

	xxx = std::make_shared<OptimizeStdCalls>("ShakingAnimation");
	xxx->_name = "Disable shaking to minimize";
	xxx->_description = "";
//	xxx->_tags = TAGS1(tags::k_windows);
	_items.push_back(xxx);

	//StrategyOptimizeItem


}
