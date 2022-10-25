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

#ifndef QWBEMSERVICES_H
#define QWBEMSERVICES_H

#include <QObject>
#include <memory>

#include <QList>
#include <QVariant>

struct QWbemQueryResult {
	int resultData;
	bool success;
	QVariantList resultList;

	QWbemQueryResult() = default;
	QWbemQueryResult(int data) : resultData(data), success(false) {}
};

Q_DECLARE_METATYPE(QWbemQueryResult)

class QWbemQueryResultPublisher : public QObject
{
	Q_OBJECT
public:
	explicit QWbemQueryResultPublisher(QObject *parent = 0) : QObject(parent) {}
	void sendResult(void* sink, QWbemQueryResult* queryResult) {
		emit sinkResult(sink, queryResult);
	}

signals:
	void sinkResult(void* sink, QWbemQueryResult* queryResult);
};

// ---

struct QWbemServicesPrivate;

class QWbemServices : public QObject
{
	Q_OBJECT
public:
	explicit QWbemServices(QObject *parent = 0);
	virtual ~QWbemServices();

	bool query(const QString& query, const QStringList& fieldList, int resultData);

public slots:
	void sinkResult(void* sink, QWbemQueryResult* queryResult);

signals:
	void initializationError();
	void result(const QWbemQueryResult& queryResult);

private:
	bool ensureConnected();

private:
	QWbemServicesPrivate* _q;
};

#endif // QWBEMSERVICES_H
