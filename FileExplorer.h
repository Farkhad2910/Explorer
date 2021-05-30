#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QString>
#include <QVector>

class FileExplorer
{
public:
    virtual void view(const QString& path) = 0;
    virtual ~FileExplorer() {}
};

namespace FileSize
{
    qint64 getSize(QString const& path);
    qint64 getSumSize(const QMap<QString, qint64> SizeSum);
};
#endif // FILEEXPLORER_H
