#ifndef ADAPTERSLIST_H
#define ADAPTERSLIST_H
#include "FileExplorer.h"
#include "FileModel.h"

class AdaptersList : public Observer
{
private:
    FileModel* dataModel;
    QTableView* view;
public:
    explicit AdaptersList(QLayout* layout);
    ~AdaptersList();
    void update(QList<Data> data) const;
};
#endif // ADAPTERSLIST_H
