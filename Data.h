#ifndef DATA_H
#define DATA_H
#include <QString>

class Data
{
public:
QString name;
QString size;
QString percent;
qreal part;
Data(const QString name_, const QString size_, const QString percent_, qreal part_)
{
    name = name_;
    size = size_;
    percent = percent_;
    part = part_;
}
};

#endif // DATA_H
