#include "FileModel.h"

FileModel::FileModel(const QList<Data> &data, QObject *parent) : QAbstractTableModel(parent)
{
    dataModel = data;
}


void FileModel::setModel(const QList<Data> &data)
{
    beginResetModel();
    dataModel = data;
    endResetModel();
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return dataModel.count();
}

int FileModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return PERCENT + 1;
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Vertical)
    {
        return section;
    }

    switch (section)
    {
        case NAME:
            return QString::fromUtf8("Name");
        case NameColumn::SIZE:
            return QString::fromUtf8("Size");
        case PERCENT:
            return QString::fromUtf8("Percentage");
    }
    return QVariant();
}

QVariant FileModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || dataModel.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
        return QVariant();
    }

    if (index.column() == 0)
    {
        return dataModel[index.row()].name;
    }
    else if (index.column() == 1)
    {
        return dataModel[index.row()].size;
    }
    else if (index.column() == 2)
    {
        return dataModel[index.row()].percent;
    }
    else
        return QVariant();
}
