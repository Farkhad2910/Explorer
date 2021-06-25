#include <iostream>
#include "Folders.h"
#include "Enlarge.h"
#include "Strategy.h"
#include "Model.h"
#include <QApplication>

QTextStream cin(stdin);
QTextStream cout(stdout);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model w;
    w.show();

    return a.exec();
}

