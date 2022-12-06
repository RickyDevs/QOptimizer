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

#ifndef STRATEGYOPTIMIZEITEM_H
#define STRATEGYOPTIMIZEITEM_H

#include "optimizebaseitem.h"
#include "registrystrategy.h"
#include <vector>

enum class OptimizeActionType { // ???
	Registry,
	Command
};

struct OptimizeAction {
	OptimizeActionType type;
	RegistryStrategy registry;
};

class StrategyOptimizeItem : public OptimizeBaseItem
{
public:
	StrategyOptimizeItem(const char* identifier);

	QString name() override;
	QString description() override;
	QString tags() const override;

	void setDetails(const char* name, const char* description);
	void setTags(const char* tags);
	void setStrategyList(const std::vector<RegistryStrategy> list);

	void activate() override;
	void deactivate() override;
	bool isActive() override;

private:
	std::vector<RegistryStrategy> _registryList;
	const char* _name;
	const char* _description;
	const char* _tags;
};

#endif // STRATEGYOPTIMIZEITEM_H
