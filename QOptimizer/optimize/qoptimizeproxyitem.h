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

#ifndef QOPTIMIZEPROXYITEM_H
#define QOPTIMIZEPROXYITEM_H

#include <memory>
#include <QObject>
#include "optimizebaseitem.h"

class QOptimizeProxyItem : public QObject
{
	Q_OBJECT
public:
	explicit QOptimizeProxyItem(QObject* parent);

	Q_INVOKABLE void activate();
	Q_INVOKABLE void deactivate();
	Q_INVOKABLE bool isActive();
	Q_INVOKABLE bool isActiveFromOrigin();

	Q_INVOKABLE QString name();
	Q_INVOKABLE QString description();
	Q_INVOKABLE QString tags();
	Q_INVOKABLE QString profiles();

private:
	std::shared_ptr<OptimizeBaseItem> _item;
};

#endif // OPTIMIZEPROXYITEM_H
