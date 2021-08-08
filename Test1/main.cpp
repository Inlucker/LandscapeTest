#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*
 * ToDo:
 * 1) Boost time
 * 2) Fix different brightness (on bottom sides)
 * 3) Fix paint bug right after generation - DONE
 *
 * */
