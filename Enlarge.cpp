#include "Enlarge.h"

void Enlarge::getEnlarge(const QString& path, QMap<QString, qint64>& Enlarges)
{
    QDir dir(path);
    QDir::Filters filters = QDir::AllEntries| QDir::NoDotAndDotDot | QDir::Hidden;
    QDir::SortFlags types = QDir::Name | QDir::Type | QDir::Size;
    for (const auto ptr : dir.entryInfoList(filters, types))
    {
        if (ptr.isDir())
        {
            getEnlarge(ptr.absoluteFilePath(), Enlarges);
        }
         else
        {
            if (Enlarges.keys().contains(ptr.suffix().toLower()))
            {
                Enlarges[ptr.suffix()] += ptr.size();
            }
            else
            {
                Enlarges.insert(ptr.suffix().toLower(), ptr.size());
            }
        }
   }
}

QMap<QString, double> Enlarge::getPercent(qint64& size, QMap<QString, qint64>& Enlarges)
{
    QMap<QString, double> Percents;
    double percent;

    for (auto ptr = Enlarges.begin(); ptr != Enlarges.end(); ptr++)
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

void Enlarge::view(const QString& path)
{
    QList<Data> data;
    QList<QPair<double, QString>> Enlarge;
    QMap<QString, qint64> Enlarges;
    getEnlarge(path, Enlarges);
    auto SumSize = FileSize::getSumSize(Enlarges);
    auto percent = getPercent(SumSize, Enlarges);
    for (auto x : percent.keys())
    {
        Enlarge.append(QPair<double, QString>(percent[x], x));
    }
    for (auto x : Enlarge)
    {
    if (x.first == -10)
    {
        data.append(Data(x.second, QString::number(Enlarges.value(x.second)), QString("< 0.01 %"),(qreal)Enlarges.value(x.second)/ SumSize));
    }
    else
    {
        data.append(Data("." + x.second, QString::number(Enlarges.value(x.second)), QString::number(x.first, 'f', 2).append(" %"),(qreal)Enlarges.value(x.second)/ SumSize));
    }
    }
    OnFinish(QList<Data>(data));


}
