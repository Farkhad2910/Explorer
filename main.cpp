#include <iostream>
#include "Folders.h"
#include "Enlarge.h"
#include "Strategy.h"

QTextStream cin(stdin);
QTextStream cout(stdout);

int main()
{
    FileExplorer* ptr = new Folders();
    Strategy* str = new Strategy(ptr);

    QString path;
    cout << "Enter path: " << Qt::endl;
    path = cin.readLine();

    if(!path.isEmpty())
    {
        str->view(path);
        delete ptr;
        ptr = new Enlarge();
        str->setStrategy(ptr);
        str->view(path);
    }
    delete ptr;
    delete str;
    return 0;
}
