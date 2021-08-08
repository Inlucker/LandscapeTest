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
 * 2) Check and Understand Diamond-Square alg
 * 3) Make interface to change params
 *    And transform Points
 *
 * */
