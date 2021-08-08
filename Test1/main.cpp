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
 * 2) Fix different brightness
 * 3) QImage::setPixelColor: color is invalid?????
 *
 * */
