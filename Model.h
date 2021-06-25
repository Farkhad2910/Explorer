#ifndef MODEL_H
#define MODEL_H
#include <QFileSystemModel>
#include <QItemSelection>
#include "FileModel.h"
#include "Strategy.h"
#include "Folders.h"
#include "Enlarge.h"
#include "Chart.h"
#include "AdaptersList.h"
#include "FileExplorer.h"

#include <QMainWindow>

namespace Ui
{
class Model;
}

class Model : public QMainWindow
{
    Q_OBJECT
public:
    explicit Model(QMainWindow *parent = nullptr);
    ~Model();

private:
    Ui::Model *ui;
    QFileSystemModel* dirModel;
    FileModel* fileModel;
    QString path;
    Observer* fileview;
    Observer* listAdapter;
    Observer* barchart;
    Observer* piechart;
    FileExplorer* folder;
    FileExplorer* enlarge;
    FileExplorer* group;

protected slots:
    void selectionStrategy(int index);
    void selectionChangedSlot(const QItemSelection& selected, const QItemSelection& deselected);
    void selectionDisplay(int index);
};


#endif // MODEL_H
