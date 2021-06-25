#include "Strategy.h"


Strategy::Strategy(FileExplorer* strategy) :
    ptr(strategy)
{}

Strategy::~Strategy()
{
    if (ptr)
        delete ptr;
}

void Strategy::view(const QString& path)
{
    if (ptr)
    ptr->view(path);
}

void Strategy::setStrategy(FileExplorer* strategy)
{
    if (ptr)
        delete ptr;
    ptr = strategy;
}

