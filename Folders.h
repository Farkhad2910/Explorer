#ifndef FOLDERS_H
#define FOLDERS_H
#include "FileExplorer.h"

class Folders : public FileExplorer
{
public:
    explicit Folders() {};
    virtual ~Folders() {};
    void view(const QString& path);//переопределение функции view
private:
    qint64 getSize_(const QString& path);//подсчет размера текущей директории
    QMap<QString, qint64> getFolderSize(const QString& path);
    QMap<QString, double> getPercents(qint64& size, QMap<QString, qint64>& Folders) const;
};


#endif // FOLDERS_H
