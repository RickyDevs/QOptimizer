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

#include "strategyoptimizeitem.h"

StrategyOptimizeItem::StrategyOptimizeItem(const char* identifier)
	: OptimizeBaseItem(identifier), _name(nullptr), _description(nullptr), _tags(nullptr)
{
}

QString StrategyOptimizeItem::name()
{
	return QString::fromLatin1(_name);
}

QString StrategyOptimizeItem::description()
{
	return QString::fromLatin1(_description);
}

QString StrategyOptimizeItem::tags() const
{
	return QString::fromLatin1(_tags);
}

void StrategyOptimizeItem::setDetails(const char* name, const char* description)
{
	_name = name;
	_description = description;
}

void StrategyOptimizeItem::setTags(const char* tags)
{
	_tags = tags;
}

void StrategyOptimizeItem::setStrategyList(const std::vector<RegistryStrategy> list)
{
	 _registryList = std::move(list);
}

void StrategyOptimizeItem::activate()
{
	Q_ASSERT_X(!isActiveFromOrigin(), "StrategyOptimizeItem::activate", "Dont activate an ActiveFromOrigin");

	for (auto& reg : _registryList) {
		reg.currentValue().setTo(reg.activeValue());
	}
}

void StrategyOptimizeItem::deactivate()
{
	for (auto regIt = _registryList.rbegin(); regIt != _registryList.rend(); regIt++) {
		auto reg = *regIt;
		reg.currentValue().setTo(reg.deactiveValue());
	}
}

bool StrategyOptimizeItem::isActive()
{
	auto& reg = _registryList.front();
	return reg.currentValue().equalsTo(reg.activeValue());
}

