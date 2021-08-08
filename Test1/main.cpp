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
 * 1) Boost time (on 0.1 sec by using QImage instead of QPainter with QPixmap)
 * 2) Fix different brightness - DONE
 * 3) QImage::setPixelColor: color is invalid????? - DONE
 *
 * */
