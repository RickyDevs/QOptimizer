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

#include "performancetweaks.h"
#include "optimizestdcalls.h"
#include "tagshelper.h"

PerformanceTweaks::PerformanceTweaks()
{

}

QString PerformanceTweaks::name()
{
	return QString::fromLatin1("Performance Tweaks");
}

QString PerformanceTweaks::description()
{
	return QString::fromLatin1("Performance Tweaks description");
}

#define concat(first, second) first " " second

void PerformanceTweaks::loadItems()
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


	xxx = std::make_shared<OptimizeStdCalls>("RemoteAssistance");
	xxx->_name = "Disable Remote Assistance";
	xxx->_description = "TODO: Network stuff";
	xxx->_tags = TAGS1(k_tagNetwork);
	_items.push_back(xxx);

	xxx = std::make_shared<OptimizeStdCalls>("ShakingAnimation");
	xxx->_name = "Disable shaking to minimize";
	xxx->_description = "";
//	xxx->_tags = TAGS1(tags::k_windows);
	_items.push_back(xxx);

	// SuperFetch -> memory
}
