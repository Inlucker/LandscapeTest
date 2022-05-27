//#include "mainwindow.h"
#include "BaseWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    BaseWindow w;
    w.show();
    return a.exec();
}

/*
 * ToDo list:
 *
 *
 * */
