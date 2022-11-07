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

#include "mainmodel.h"

#include "qwbemservices.h"
#include "tagshelper.h"

QVariantMap makeUiEntry(const QString& name, const QString& icon, const char* objType) {
	QVariantMap map;
	map["DisplayName"] = QVariant(name);
	map["DisplayIcon"] = QVariant(icon);
	map["Type"] = QVariant(objType);
	return map;
}

class WbemTaskBuilder
{
public:
	WbemTaskBuilder(const QString& query, const QStringList& fields) {
		_task.type = TaskType::Wbem;
		_task.action = TaskAction::UpdateChilds;
		_task.query = query;
		_task.fields = fields;
		_task.defaultDataMap.clear();
	}
	operator Task() const { return std::move(_task); }

	WbemTaskBuilder& objType(const QString& objType) {
		// Swap to append new elements because updates shouldn't define Type
		_task.action = TaskAction::Append;
		_task.defaultDataMap["Type"] = QVariant(objType);
		return *this;
	}
	WbemTaskBuilder& icon(const QString& icon) {
		_task.defaultDataMap["DisplayIcon"] = QVariant(icon);
		return *this;
	}
	WbemTaskBuilder& byteSizeMask(const QString& byteSizeMask) {
		_task.defaultDataMap["ByteSizeMask"] = QVariant(byteSizeMask);
		return *this;
	}
	WbemTaskBuilder& priority(int priority) {
		Q_UNUSED(priority)
		// TODO.. maybe new name...
		//actions: mandatory? (must run at startup),
		//         secundary?? (on demand by user clicking on it, e.g fetching other fields)
		// ou TaskType::WbemCreate; + TaskType::WbemUpdate;
		return *this;
	}
private:
	Task _task;
};

QString displayName(const QVariantMap& map) {
	QString type = map["Type"].toString();
	if (type == "MEMORY_ITEM") {
		return map["BankLabel"].toString();
	}
	if (type == "BOARD_ITEM") {
		return map["Manufacturer"].toString();
	}
	if (type == ITEM_TAG(k_tagDiskDrive)) {
		return map["Model"].toString();
	}
	return map["Name"].toString();
}

MainModel::MainModel(QWbemServices* wbem, QObject *parent)
	: QAbstractItemModel(parent)
{
	connect(wbem, &QWbemServices::result, this, &MainModel::wbemResult);
	_wbem = wbem;

	MainModelItem root(-1, {});
	_modelData.emplace_back(root);

	addModelData(0,
				 makeUiEntry("Processors", "charcode:0xE950", HEADER_TAG(k_tagProcessor)),
				 {
					WbemTaskBuilder("SELECT * FROM Win32_Processor",
						{"Name", "L2CacheSize", "L3CacheSize", "NumberOfCores", "NumberOfLogicalProcessors", "Description", "Revision", "VirtualizationFirmwareEnabled"})
					.objType(ITEM_TAG(k_tagProcessor))
					.icon("charcode:0xE950")
					.byteSizeMask("L2CacheSize=k;L3CacheSize=k;")
				 });
	addModelData(0,
				 makeUiEntry("Memory", "qrc://memory.png", HEADER_TAG(k_tagMemory)),
				 {
					// Testar em Win7 ou Virtual Box
					WbemTaskBuilder("SELECT * FROM Win32_PhysicalMemory",
						{"Manufacturer", "BankLabel", "Capacity", "Speed", "MemoryType", "FormFactor"})
					.objType(ITEM_TAG(k_tagMemory))
					.byteSizeMask("Capacity=b;")
				 });
	addModelData(0,
				 makeUiEntry("Motherboard", "charcode:0xE964", HEADER_TAG(k_tagMotherboard)),
				 {
					 WbemTaskBuilder("SELECT * FROM Win32_BaseBoard",
						{"Model", "Manufacturer", "Product", "Version"})
					 .objType(ITEM_TAG(k_tagMotherboard))
					 .icon("charcode:0xE964")
				 });
	addModelData(0,
				 makeUiEntry("Graphics", "charcode:0xF211", HEADER_TAG(k_tagGraphics)),
				 {
					 WbemTaskBuilder("SELECT * FROM Win32_VideoController",
						{"Name", "AdapterRAM", "CurrentHorizontalResolution", "CurrentVerticalResolution", "CurrentRefreshRate", "AdapterDACType", "VideoMemoryType"})
					 .objType(ITEM_TAG(k_tagGraphics))
					 .icon("charcode:0xF211")
				 });
	addModelData(0,
				 makeUiEntry("Disk Drives", "charcode:0xEDA2", HEADER_TAG(k_tagDiskDrive)),
				 {
					 WbemTaskBuilder("SELECT * FROM Win32_DiskDrive",
						{"Model", "BytesPerSector", "FirmwareRevision", "MediaType", "Size"})
					 .objType(ITEM_TAG(k_tagDiskDrive))
					 .icon("charcode:0xEDA2")
					 .byteSizeMask("Size=b;")
				 });
	addModelData(0,
				 makeUiEntry("Network Adapters", "charcode:0xEDA3", HEADER_TAG(k_tagNetwork)),
				 {
					 WbemTaskBuilder("SELECT * FROM Win32_NetworkAdapter",
						{"AdapterType", "Manufacturer", "ProductName", "PhysicalAdapter", "MacAddress", "ServiceName"})
					 .objType(ITEM_TAG(k_tagNetwork))
					 .icon("charcode:0xEDA3")
				 });

	addModelData(0,
				 makeUiEntry("BIOS", "charcode:0xE964", HEADER_TAG(k_tagBIOS)),
				 {
					 WbemTaskBuilder("SELECT * FROM Win32_BIOS",
						{"Name", "Manufacturer", "Version", "BuildNumber"})
					.objType(ITEM_TAG(k_tagBIOS))
					.icon("charcode:0xE964"),
					 WbemTaskBuilder("SELECT ReleaseDate FROM Win32_BIOS",
						{"ReleaseDate"})
				 });
}


void MainModel::addModelData(int parentId, const QVariantMap& map, const std::vector<Task>& taskList) {
	int row = 0;
	if (parentId >= 0) {
		row = _modelData.at(parentId).childs.size();
	}
	MainModelItem item(parentId, taskList);
	item.dataMap = map;
	item.row = row;
	int itemId = _modelData.size();
	_modelData[parentId].childs.emplace_back(itemId);
	_modelData.emplace_back(item);

	processTaskForItem(itemId, TaskAction::Append);
}

int MainModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0) {
		return 0;
	}
	if (!parent.isValid()) {
		return _modelData.at(0).childs.size();
	}
	int idx = parent.internalId();
	Q_ASSERT(_modelData.size() > (size_t)idx);
	return _modelData.at(idx).childs.size();
}

int MainModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

QVariant MainModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	if (role > Qt::UserRole) {
		QString roleName = roleNames()[role];
		if (roleName != "" && index.column() == 0
				&& index.internalId() > 0 && index.internalId() < _modelData.size()) {
			Q_ASSERT_X( _modelData[index.internalId()].row == index.row(), "data", "Model data row invalid");
			if (roleName == "object") {
				return _modelData[index.internalId()].dataMap;
			}

			QVariant ss = _modelData[index.internalId()].dataMap[roleName];
			return ss;
		}
	}

	return QVariant();
}

QModelIndex MainModel::index(int row, int column, const QModelIndex& parent) const
{
	if (hasIndex(row, column, parent)) {
		quintptr idx = _modelData.at(parent.internalId()).childs.at(row);
		return createIndex(row, column, idx);
	}
	return QModelIndex();
}


QModelIndex MainModel::parent(const QModelIndex& child) const {
	return QModelIndex();
}

QHash<int, QByteArray> MainModel::roleNames() const {
	static QHash<int, QByteArray> map;

	map[Qt::UserRole + 1] = "query";
	map[Qt::UserRole + 2] = "object";

	return map;
}

void MainModel::checkForPendingUpdates(const QModelIndex &index)
{
	int itemId = index.internalId();
	if (_taskQueue.find(itemId) != _taskQueue.cend()) {
		return;
	}
	processTaskForItem(itemId, TaskAction::UpdateChilds);
}

void MainModel::processTaskForItem(int itemId, TaskAction actionFilter)
{
	auto& taskList = _modelData.at(itemId).taskList;
	if (!taskList.empty()) {
		Task task = taskList.front();
		if (task.action != actionFilter) {
			_taskQueue.erase(_taskQueue.find(itemId));
			return;
		}
		taskList.erase(taskList.begin());
		_taskQueue[itemId] = task;

		if (task.type == TaskType::Wbem) {
			_wbem->query(task.query, task.fields, itemId);
		}
	}
}

void MainModel::wbemResult(const QWbemQueryResult& queryResult) {

	printf("%d ---- this %d\n", queryResult.resultData, (int)this);
	if (!queryResult.success) {
		printf("wbem query fail");
		return;
	}
	int itemId = queryResult.resultData;
	int oldChildCount = _modelData.at(itemId).childs.size();
	const Task& task = _taskQueue[queryResult.resultData];

	if (queryResult.resultList.size() > 0) {
		if (task.action == TaskAction::Append) {
			wbemResultAppend(queryResult);
		} else {
			wbemResultUpdateChilds(queryResult);
		}
	}

	const auto& item = _modelData.at(queryResult.resultData);
	int newChildCount = item.childs.size();
	if (oldChildCount != newChildCount) {
		insertRows(oldChildCount, newChildCount - oldChildCount, createIndex(item.row, 0, queryResult.resultData));
	}

	processTaskForItem(itemId, task.action);
}


void MainModel::wbemResultAppend(const QWbemQueryResult& queryResult) {
	for (QVariant v : queryResult.resultList) {
		QVariantMap map = v.toMap();
		//map["Type"] = QVariant(_taskQueue[queryResult.resultData].objType);
		//QString byteSizeMask = _taskQueue[queryResult.resultData].byteSizeMask;
		//if (byteSizeMask != "") {
		//	map["ByteSizeMask"] = QVariant(byteSizeMask);
		//}
		map.unite(_taskQueue[queryResult.resultData].defaultDataMap);
		QString displayNameStr = displayName(map);
		// TODO "Unknown" display name?
		if (displayNameStr != "") {
			map["DisplayName"] = QVariant(displayNameStr);
			addModelData(queryResult.resultData, map, {});
		}
	}
}

void MainModel::wbemResultUpdateChilds(const QWbemQueryResult& queryResult) {
	int itemId = queryResult.resultData;
	const auto& childs = _modelData.at(itemId).childs;
	for (QVariant v : queryResult.resultList) {
		QVariantMap map = v.toMap();
		for (int childId : childs) {
			_modelData.at(childId).dataMap.unite(map);
		}
	}
}
