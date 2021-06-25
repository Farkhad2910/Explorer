#include "Model.h"
#include "ui_Model.h"

Model::Model(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Model),
    folder(new Folders()),
    enlarge(new Enlarge()),
    group(folder)
{
    ui->setupUi(this);
    listAdapter = new AdaptersList(ui->stackedWidget->layout());
    barchart = new BarChart(ui->stackedWidget->layout());
    piechart = new PieChart(ui->stackedWidget->layout());

    QString homePath = QDir::homePath();
    dirModel =  new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::Hidden | QDir::AllDirs);
    dirModel->setRootPath(homePath);

    fileview = listAdapter;
    group->Attach(fileview);

    ui->treeView->setModel(dirModel);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->displayBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Model::selectionDisplay);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Model::selectionStrategy);
    connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this,  &Model::selectionChangedSlot);
}

void Model::selectionDisplay(int index)
{
    switch(index)
    {
        case 0:
            fileview = listAdapter;
            break;
        case 1:
            fileview = barchart;
            break;
        case 2:
            fileview = piechart;
            break;
    }
    group->Attach(fileview);
    group->view(path);
    ui->stackedWidget->setCurrentIndex(index);
}

void Model::selectionStrategy(int index) // изменяется группировка в combobox
{
    switch (index)
    {
    case 0:
        group = folder;
        break;
    case 1:
        group = enlarge;
        break;
    }
    group->Attach(fileview);
    group->view(path);
}

void Model::selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndexList indexes = selected.indexes();
    path = dirModel->filePath(indexes[0]);
    group->view(path);
}

Model::~Model()
{
    delete ui;
    delete dirModel;
    delete listAdapter;
    delete barchart;
    delete piechart;
    delete folder;
    delete enlarge;
}
