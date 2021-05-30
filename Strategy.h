#ifndef STRATEGY_H
#define STRATEGY_H
#include "FileExplorer.h"

class Strategy
{
public:
    explicit Strategy(FileExplorer* strategy);
    ~Strategy();
    void view(const QString& path);
    void setStrategy(FileExplorer* strategy);
private:
    FileExplorer *ptr;
};


#endif // STRATEGY_H
