#include "FileExplorer.h"

qint64 FileSize::getSize(QString const& path)
{
    qint64 size = 0;
    QDir::Filters filters = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden;
    QDir::SortFlags types = QDir::Name | QDir::Type | QDir::Size;

    QDir dir(path);

    for (const auto& ptr : dir.entryInfoList(filters, types))
    if (ptr.isDir())
    {
        size += getSize(ptr.absoluteFilePath());
    }
    else size += ptr.size();
    return size;
}

qint64 FileSize::getSumSize(const QMap<QString, qint64> SizeSum) {
    qint64 size_ = 0;
    foreach(qint64 size, SizeSum.values())
        size_ += size;
    return size_;
}
