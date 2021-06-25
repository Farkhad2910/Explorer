#include "AdaptersList.h"

AdaptersList::AdaptersList(QLayout* layout)
{
    dataModel = new FileModel();
    view = new QTableView();
    view->setModel(dataModel);
    layout->addWidget(view);
}

void AdaptersList::update(QList<Data> data) const
{
    dataModel->setModel(data);
}

AdaptersList::~AdaptersList()
{
    delete dataModel;
    delete view;
}
