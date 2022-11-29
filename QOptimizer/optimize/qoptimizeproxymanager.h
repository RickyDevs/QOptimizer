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

#ifndef QOPTIMIZEPROXYMANAGER_H
#define QOPTIMIZEPROXYMANAGER_H

#include <QObject>
#include <QVariant>
#include <QBasicTimer>
#include "qoptimizeproxyitem.h"
#include "optimizemanager.h"
#include "optimizeprocessingcontext.h"

class QOptimizeProxyManager : public QObject
{
	Q_OBJECT
public:
	explicit QOptimizeProxyManager(QObject *parent = 0);
	~QOptimizeProxyManager();

	Q_INVOKABLE bool isProcessing();
	Q_INVOKABLE QList<QObject*> query(const QVariantMap& queryMap);

signals:
	void processingEnded();

//public slots:
private:
	void timerEvent(QTimerEvent *event) override;
	std::unique_ptr<OptimizeManager> _optimizeManager;
	QBasicTimer _processingTimer;
	std::unique_ptr<OptimizeProcessingContext> _context;
};

#endif // QOPTIMIZEPROXYMANAGER_H
