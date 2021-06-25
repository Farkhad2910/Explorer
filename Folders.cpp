#include "Folders.h"

qint64 Folders::getSize_(const QString& path)
{
    qint64 size_ = 0;
    QDir dir(path);
    QDir::Filters filters = QDir::Files| QDir::NoDotAndDotDot | QDir::Hidden;
    QDir::SortFlags types = QDir::Name | QDir::Type;
    for (auto ptr : dir.entryInfoList(filters, types))
        size_ += ptr.size();
    return size_;
}

QMap<QString, qint64> Folders::getFolderSize(const QString& path)
{
    QFileInfo folderInfo(path);
    QMap<QString, qint64> FoldersSizes;
    auto path_ = folderInfo.absoluteFilePath();
    FoldersSizes.insert(path_, getSize_(path_));
    QDir::Filters filters = QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden;
    QDir::SortFlags types = QDir::Name | QDir::Type;
    for (auto ptr : QDir(path).entryInfoList(filters, types))
    {
        FoldersSizes.insert(ptr.absoluteFilePath(), FileSize::getSize(ptr.absoluteFilePath()));
    }
    return FoldersSizes;
}

QMap<QString, double> Folders::getPercents(qint64& size, QMap<QString, qint64>& FolderList) const
{
    QMap<QString, double> Percents;
    double percent;
    for (auto ptr = FolderList.begin(); ptr != FolderList.end(); ptr++)
    {
        if (ptr.value() == 0)
            percent = 0;
        else
        {
            percent = double(ptr.value() * 100) / size;
            if (percent < 0.01)
                percent = -1;
        }
        Percents.insert(ptr.key(), percent);
    }
    return Percents;
}

void Folders::view(const QString& path)
{
    QList<Data> data;
    QList<QPair<double, QString>> Percents;
    auto Folders = getFolderSize(path);
    auto SumSize = FileSize::getSumSize(Folders);
    auto percent = getPercents(SumSize, Folders);
    for (auto x : percent.keys())
    {
        Percents.append(QPair<double, QString>(percent[x], x));
    }
    for (auto x : Percents)
    {
        if (x.first == -10)
        {
            data.append(Data(x.second, QString::number(Folders.value(x.second)), QString("< 0.01 %"), (qreal)Folders.value(x.second)/ SumSize));
        } else
        {
            data.append(Data(x.second, QString::number(Folders.value(x.second)), QString::number(x.first, 'f', 2).append(" %"), (qreal)Folders.value(x.second)/ SumSize));
        }
    }
    OnFinish(QList<Data>(data));
}
