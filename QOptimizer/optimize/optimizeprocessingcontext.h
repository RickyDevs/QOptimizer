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

#ifndef OPTIMIZEPROCESSINGCONTEXT_H
#define OPTIMIZEPROCESSINGCONTEXT_H

#include <QString>
#include <QStringList>

#include <functional>

class OptimizeProcessingContext
{
public:
	bool hasEnded();
	void processNext();

	void ensureProcessed(const QString& identifier);

	static OptimizeProcessingContext* createActiveFromOriginProcessor();

private:
	OptimizeProcessingContext();

	int _index;
	QStringList _processedItemsList;
	bool _ended;

	std::function<QStringList(int i)> _itemsToProcessImpl;
	std::function<void(const QString&)> _processItemImpl;
};


#endif // OPTIMIZEPROCESSINGCONTEXT_H
