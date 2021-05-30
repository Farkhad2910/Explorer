#ifndef FOLDERS_H
#define FOLDERS_H
#include "FileExplorer.h"

class Folders : public FileExplorer
{
public:
    explicit Folders() {};
    virtual ~Folders() {};
    void view(const QString& path);
private:
    qint64 getSize_(const QString& path);
    QMap<QString, qint64> getFolderSize(const QString& path);
    QMap<QString, double> getPercents(qint64& size, QMap<QString, qint64>& Folders) const;
    void Print(const QMap<QString, qint64>& FolderType, const QMap<QString, double>& FolderPercent);
};


#endif // FOLDERS_H
