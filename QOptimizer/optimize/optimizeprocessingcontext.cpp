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

#include "optimizeprocessingcontext.h"

#include "optimizemanager.h"

OptimizeProcessingContext::OptimizeProcessingContext()
{
	_index = 0;
	_ended = false;
	auto pThis = this;
	_itemsToProcessImpl = [pThis](int i) {
		pThis->_ended = true;
		return QStringList();
	};
	_processItemImpl = [](const QString& identifier) {
		Q_UNUSED(identifier);
	};
}

bool OptimizeProcessingContext::hasEnded()
{
	return _ended;
}

void OptimizeProcessingContext::processNext()
{
	QStringList itemIds = _itemsToProcessImpl(_index);

	for (QString identifier : itemIds) {
		if (_processedItemsList.contains(identifier)) {
			continue;
		}

		_processedItemsList.append(identifier);
		_processItemImpl(identifier);
	}
	_index++;
}

void OptimizeProcessingContext::ensureProcessed(const QString& identifier)
{
	if (_processedItemsList.contains(identifier)) {
		return;
	}

	// TODO
	_processedItemsList.append(identifier);
	_processItemImpl(identifier);
}


OptimizeProcessingContext* OptimizeProcessingContext::createActiveFromOriginProcessor(OptimizeManager* manager)
{
	auto context = new OptimizeProcessingContext();

	context->_itemsToProcessImpl = [context, manager](int i) {
		context->_ended = manager->items().size() <= i;
		if (context->_ended) {
			return QStringList();
		}
		auto item = manager->items().at(i);

		return OptimizeManager::allIdentifiersOfItem(item); //QStringList();
	};

	context->_processItemImpl = [manager](const QString& identifier) {
		auto item = manager->itemByIdentifier(identifier);

		if (item) {
			item->checkOriginalStateImpl();
		}
	};

	return context;
}
