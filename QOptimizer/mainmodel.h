#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QVariantList>

struct MainModelItem {
	int row;
	int parent;
	int sourceIdx;
	QHash<QString, QVariant> dataMap;
	std::vector<int> childs;
	bool pendingUpdate;

	MainModelItem(int _row, int _parent, int _sourceIdx) {
		row = _row;
		parent = _parent;
		sourceIdx = _sourceIdx;
		pendingUpdate = true;
	}
};


class MainModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit MainModel(const QVariantList& data, QObject *parent = nullptr);

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &child) const override;

	QHash<int, QByteArray> roleNames() const override;

private:
	void processItem(int idx);

	QVariantList _sourceData;
	int _processed;
	std::vector<MainModelItem> _processedData;
};

#endif // MAINMODEL_H
