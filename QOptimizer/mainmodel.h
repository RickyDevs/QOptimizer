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

#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QVariantMap>

#include "qwbemservices.h"

enum class TaskType {
	Wbem,
	Operations
};

struct Task {
	TaskType type;
	QString query;
	QStringList fields;
	QString objType;
	QString byteSizeMask;

};

struct MainModelItem {
	int row;
	int parent;
	int sourceIdx;
	QVariantMap dataMap;
	std::vector<Task> taskList;
	std::vector<int> childs;

	MainModelItem(int _parent, const std::vector<Task>& _taskList) {
		row = -1;
		parent = _parent;
		taskList = _taskList;
	}
};


class MainModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit MainModel(QWbemServices* wbem, QObject* parent = nullptr);

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &child) const override;

	QHash<int, QByteArray> roleNames() const override;

public slots:
	void wbemResult(const QWbemQueryResult& queryResult);

private:
	void addModelData(int parentId, const QVariantMap& map, const std::vector<Task>& taskList);
	void processTaskForItem(int itemId);

	std::vector<MainModelItem> _modelData;
	std::map<int, Task> _taskQueue;
	QWbemServices* _wbem;
};

#endif // MAINMODEL_H
