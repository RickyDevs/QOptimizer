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
	explicit QOptimizeProxyItem(std::shared_ptr<OptimizeBaseItem> item, QObject* parent);

	Q_PROPERTY(QString identifier READ identifier CONSTANT)
	Q_PROPERTY(QString name READ name CONSTANT)
	Q_PROPERTY(QString description READ description CONSTANT)
	Q_PROPERTY(QString tags READ tags CONSTANT)
	Q_PROPERTY(QString profiles READ profiles CONSTANT)
	Q_PROPERTY(QList<QObject*> childItems READ childItems CONSTANT)

	Q_INVOKABLE bool isActive();
	Q_INVOKABLE bool isActiveFromOrigin();
	Q_INVOKABLE void activate();
	Q_INVOKABLE void deactivate();


	void addProxyItem(QOptimizeProxyItem* item);

signals:
	void activeChanged();

private:
	QString identifier();
	QString name();
	QString description();
	QString tags();
	QString profiles();
	QList<QObject*> childItems();

	std::shared_ptr<OptimizeBaseItem> _item;

	QList<QObject*> _proxyItems;
};

#endif // OPTIMIZEPROXYITEM_H
