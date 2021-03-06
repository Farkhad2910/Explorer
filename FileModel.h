#ifndef FILEMODEL_H
#define FILEMODEL_H
#include "FileExplorer.h"

class FileModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    enum NameColumn
    {
        NAME = 0,
        SIZE,
        PERCENT
    };
    QList<Data> dataModel;
public:
    FileModel() = default;
    ~FileModel() = default;
    FileModel(const QList<Data>& data, QObject* parent = nullptr);
    void setModel(const QList<Data>& data);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // FILEMODEL_H
