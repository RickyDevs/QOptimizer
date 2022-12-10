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

#ifndef OPTIMIZEMANAGER_H
#define OPTIMIZEMANAGER_H

#include "optimizebaseitem.h"
#include "singleton.h"
#include <vector>

class OptimizeManager : public Singleton<OptimizeManager>
{
public:
	//~OptimizeManager() {}

	std::vector<std::shared_ptr<OptimizeBaseItem>> items();

	std::shared_ptr<OptimizeBaseItem> itemByIdentifier(const QString& identifier);

	QString groupByIdentifier(const QString& identifier);

	static QStringList allIdentifiersOfItem(const std::shared_ptr<OptimizeBaseItem>& itemPtr);

	static void registerImplementation();

private:
	OptimizeManager();

	void ensureLoaded();

	std::vector<std::shared_ptr<OptimizeBaseItem>> _items;
};

#endif // OPTIMIZEMANAGER_H
