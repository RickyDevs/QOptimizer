#include "mainmodel.h"



MainModel::MainModel(const QVariantList& data, QObject *parent)
	: QAbstractItemModel(parent)
{
	//if (data.)
	_sourceData = data;
	_processed = 0;
	MainModelItem root(0, -1, -1);
	root.pendingUpdate = false;
	_processedData.emplace_back(root);
	processItem(0);
}

int MainModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0) {
		return 0;
	}
	if (!parent.isValid()) {
		return _processedData.at(0).childs.size();
	}
	int idx = parent.internalId();
	Q_ASSERT(_processedData.size() > idx);
	return _processedData.at(idx).childs.size();
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

	if (role > Qt::UserRole) { //Qt::DisplayRole) {
		QString roleName = roleNames()[role];
		if (roleName != "" && index.column() == 0 && index.row() < _sourceData.size()) {
			if (roleName == "object") {
				return _sourceData[index.row()];
			}

			QVariant ss = _sourceData[index.row()].toMap()[roleName];
			return ss;
		}
	}

	return QVariant();
}


QModelIndex MainModel::index(int row, int column, const QModelIndex& parent) const
{
	if (hasIndex(row, column, parent)) {
		quintptr idx = _processedData.at(parent.internalId()).childs.at(row);
		return createIndex(row, column, idx);
	}
	return QModelIndex();
}


QModelIndex MainModel::parent(const QModelIndex& child) const {
	/*if (child.isValid()) {
		return child.parent();
	}*/
	return QModelIndex();
}

QHash<int, QByteArray> MainModel::roleNames() const {
	static QHash<int, QByteArray> map;

	map[Qt::UserRole + 1] = "query";
	map[Qt::UserRole + 2] = "object";

	return map;
}


void MainModel::processItem(int idx) {

	// FIXME.. carregar todos os child.. e deixar 1 para processing..

	auto& item = _processedData[idx];

	// descubrir filhos..
	QVariantList childList;
	if (item.sourceIdx < 0) {
		childList = _sourceData;
	} else {
		Q_ASSERT_X(false, "processItem", "falta processar items");
		return;
	}

	int it = 0;
	for (QVariant v : childList) {
		QVariant value = v.toMap()["value"];
		if (value.isNull() && item.childs.size() == it) {
			// create pending child
			MainModelItem childItem(it, idx, 0);
			childItem.dataMap = v.toMap();
			item.childs.emplace_back(_processedData.size());
			_processedData.emplace_back(childItem);
			break;
		} else {
			Q_ASSERT_X(false, "processItem", "saltar child processed");
			it++;
		}
	}

	// processar filhos
	const auto& childs = _processedData.at(it).childs;
	for (int id0 : childs) {
		processItem(id0);
	}
/*	if (item.hasMoreChilds) {

	}*/
}
