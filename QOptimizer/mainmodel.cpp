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
	map["Icon"] = QVariant(icon);
	map["Type"] = QVariant(objType);
	return map;
}

Task makeWbemTask(const QString& query, const QStringList& fields, const QString& objType) {
	Task task;
	task.type = TaskType::Wbem;
	task.query = query;
	task.fields = fields;
	task.objType = objType;
	return task;
}

QString displayName(const QVariantMap& map) {
	QString type = map["Type"].toString();
	if (type == "MEMORY_ITEM") {
		return map["BankLabel"].toString();
	}
	if (type == "BOARD_ITEM") {
		return map["Manufacturer"].toString();
	}
	if (type == "DRIVE_ITEM") {
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
				 makeUiEntry("Processors", "qrc://processor.png", "PROCESSOR_HEADER"),
				 {
					 makeWbemTask("SELECT * FROM Win32_Processor",
					 {"Name", "L2CacheSize", "L3CacheSize", "NumberOfCores"},
					 "PROCESSOR_ITEM")
				 });
	addModelData(0,
				 makeUiEntry("Memory", "qrc://memory.png", "MEMORY_HEADER"),
				 {
					 // Testar em Win7 ou Virtual Box
					 makeWbemTask("SELECT * FROM Win32_PhysicalMemory",
					 {"Manufacturer", "BankLabel", "Capacity", "Speed", "MemoryType", "FormFactor"},
					 "MEMORY_ITEM")
				 });
	addModelData(0,
				 makeUiEntry("Motherboard", "qrc://motherboard.png", "BOARD_HEADER"),
				 {
					 makeWbemTask("SELECT * FROM Win32_BaseBoard",
					 {"Model", "Manufacturer", "Product", "Version"},
					 "BOARD_ITEM")
				 });
	addModelData(0,
				 makeUiEntry("Graphics", "qrc://graphics.png", "PROCESSOR_HEADER"),
				 {
					 makeWbemTask("SELECT * FROM Win32_VideoController",
					 {"Name", "AdapterRAM", "CurrentHorizontalResolution", "CurrentVerticalResolution", "CurrentRefreshRate", "AdapterDACType", "VideoMemoryType"},
					 "GRAPHIC_ITEM")
				 });
	addModelData(0,
				 makeUiEntry("Disk Drives", "qrc://disk_drive.png", HEADER_TAG(k_tagDiskDrive)),
				 {
					 makeWbemTask("SELECT * FROM Win32_DiskDrive",
					 {"Model", "BytesPerSector", "FirmwareRevision", "MediaType", "Size"},
					 "DRIVE_ITEM")
				 });
	addModelData(0,
				 makeUiEntry("Network Adapters", "qrc://network_adapters.png", HEADER_TAG(k_tagNetwork)),
				 {
					 makeWbemTask("SELECT * FROM Win32_NetworkAdapter",
					 {"AdapterType", "Manufacturer", "ProductName", "PhysicalAdapter", "MacAddress", "ServiceName"},
					 "NETWORK_ITEM")
				 });
	addModelData(0,
				 makeUiEntry("BIOS", "qrc://bios.png", "PROCESSOR_HEADER"),
				 {
					 makeWbemTask("SELECT * FROM Win32_BIOS",
					 {"Name", "Manufacturer", "Version", "BuildNumber"},
					 "PROCESSOR_HEADER")
				 });

	//wbem->query("SELECT * FROM Win32_Processor", {"Name"}, 6969);
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

	processTaskForItem(itemId);
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

void MainModel::processTaskForItem(int itemId) {
	auto& taskList = _modelData.at(itemId).taskList;
	if (!taskList.empty()) {
		Task task = taskList.front();
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

	int oldChildCount = _modelData.at(queryResult.resultData).childs.size();

	if (queryResult.resultList.size() > 0) {
		for (QVariant v : queryResult.resultList) {
			QVariantMap map = v.toMap();
			map["Type"] = QVariant(_taskQueue[queryResult.resultData].objType);
			QString displayNameStr = displayName(map);
			// TODO "Unknown" display name?
			if (displayNameStr != "") {
				map["DisplayName"] = QVariant(displayNameStr);
				addModelData(queryResult.resultData, map, {});
			}
		}
	}

	const auto& item = _modelData.at(queryResult.resultData);
	int newChildCount = item.childs.size();
	if (oldChildCount != newChildCount) {
		insertRows(oldChildCount, newChildCount - oldChildCount, createIndex(item.row, 0, queryResult.resultData));
	}
}


