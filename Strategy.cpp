#include "Strategy.h"


Strategy::Strategy(FileExplorer* strategy) :
    ptr(strategy)
{}

Strategy::~Strategy()
{}

void Strategy::view(const QString& path)
{
    if (ptr)
    ptr->view(path);
}

void Strategy::setStrategy(FileExplorer* strategy)
{
    ptr = strategy;
}

