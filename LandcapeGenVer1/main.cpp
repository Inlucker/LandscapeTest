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
 * ToDo list:
 * 1) Сделать интерфейс чтобы Canvas растягивался
 * 2) Создать структуру из HeightsMapPoints и массива треугольников(номеров вершин которые они соединяют) вместо TriPolArray
 *
 *
 * */
