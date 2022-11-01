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

#ifndef OPTIMIZEBASEITEM_H
#define OPTIMIZEBASEITEM_H

#include <memory>
#include <QString>

enum class OptimizeType { // ???
	Enable
};

class OptimizeBaseItem
{
public:
	OptimizeBaseItem(const char* identifier);
	virtual ~OptimizeBaseItem() {}

	QString identifier();

	virtual void activate();
	virtual void deactivate();
	virtual bool isActive();
	virtual bool isActiveFromOrigin();

	virtual QString name();
	virtual QString description();
	virtual QString tags();
	virtual QString profiles();

	virtual std::vector<std::shared_ptr<OptimizeBaseItem>> items();

	virtual void checkOriginalStateImpl();
private:
	const char* _identifier;
};

#endif // OPTIMIZEBASEITEM_H
