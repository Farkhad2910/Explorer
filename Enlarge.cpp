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


void Enlarge::Print(const QMap<QString, qint64>& Enlarges, const QMap<QString, double>& EnlargePercent)
{
    QTextStream cout(stdout);

    foreach(QString path, EnlargePercent.keys())
    {
        double percent = EnlargePercent.value(path);
        cout << qSetFieldWidth(30) << "." + path << qSetFieldWidth(10) << Enlarges.value(path) / 1024 << qSetFieldWidth(10) << "KB";
        if (percent == -1)
        {
            cout << qSetFieldWidth(10) << "< 0.01 %" << Qt::endl;
        }
        else
            cout << qSetFieldWidth(10) << QString::number(percent, 'f', 2).append(" %") << Qt::endl;
    }
}

void Enlarge::view(const QString& path)
{
    QMap<QString, qint64> Enlarges;
    getEnlarge(path, Enlarges);
    auto SumSize = FileSize::getSumSize(Enlarges);
    auto percent = getPercent(SumSize, Enlarges);
    Print(Enlarges, percent);
}
