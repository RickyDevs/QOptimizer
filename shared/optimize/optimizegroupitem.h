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

#ifndef OPTZIMIZEGROUPITEM_H
#define OPTZIMIZEGROUPITEM_H

#include "optimizebaseitem.h"

class OptimizeGroupItem : public OptimizeBaseItem
{
public:
	OptimizeGroupItem(const char* identifier);

	virtual std::vector<std::shared_ptr<OptimizeBaseItem>> items() override;

	virtual void activate() override;
	virtual void deactivate() override;

	virtual bool isActiveFromOrigin() override;
	virtual void checkOriginalStateImpl() override;

protected:
	virtual void loadItems() = 0;

	std::vector<std::shared_ptr<OptimizeBaseItem>> _items;
};

#endif // OPTZIMIZEGROUPITEM_H
