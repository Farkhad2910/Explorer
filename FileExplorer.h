#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QString>
#include <QVector>
#include "Data.h"
#include <QTableView>
#include <QLayout>
#include <QHeaderView>
#include <QAbstractTableModel>
#include <QList>
#include <QLocale>
#include <memory>

class Observer
{
public:
    Observer() {}
    virtual ~Observer() = default;
    virtual void update(QList<Data> data) const = 0;
};

class FileExplorer//абстрактный базовый класс
{
private:
    Observer* obs;
public:
    virtual void view(const QString& path) = 0;
    virtual ~FileExplorer() {}
    void Attach(Observer* observer)
    {
        if (observer)
            obs = observer;
    }

    void OnFinish(const QList<Data>& data) const
    {
        obs->update(data);
    }
};

namespace FileSize//пространство имен с функциями подсчета размера пути
{
    qint64 getSize(QString const& path);
    qint64 getSumSize(const QMap<QString, qint64> SizeSum);
};


#endif // FILEEXPLORER_H
