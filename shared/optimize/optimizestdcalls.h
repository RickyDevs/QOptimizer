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

#ifndef OPTIMIZESTDCALLS_H
#define OPTIMIZESTDCALLS_H

#include "optimizebaseitem.h"

#include <functional>

class OptimizeStdCalls : public OptimizeBaseItem
{
public:
	OptimizeStdCalls(const char* identifier);
	virtual ~OptimizeStdCalls() {}


	QString name() override;
	QString description() override;
	QString tags() const override;

	const char* _name;
	const char* _description;
	const char* _tags;

	std::function<void()> _activateCall;
};

#endif // OPTIMIZESTDCALLS_H
