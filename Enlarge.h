#ifndef ENLARGE_H
#define ENLARGE_H
#include "FileExplorer.h"

class Enlarge : public FileExplorer
{
public:
    explicit Enlarge() {};
    virtual ~Enlarge() {};
    void view(const QString& path);
private:
    void getEnlarge(const QString& path, QMap<QString, qint64>& Enlarges);
    QMap<QString, double> getPercent(qint64& size, QMap<QString, qint64>& Enlarges);
    void Print(const QMap<QString, qint64>& Enlarges, const QMap<QString, double>& EnlargePercent);
};

#endif // ENLARGE_H
