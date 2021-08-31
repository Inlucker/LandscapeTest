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
 * 0) Убрать Scale из интерфейса, сделать начальное мастабирование автоматическим, в зависимости от размера окна, карты высот и максимальных минимальных значений этих высот
 * ?) Изменить буфер кадра, чтобы он хранил только интенсивность а не сам цвет
 * ?) Создать структуру из HeightsMapPoints и массива треугольников(номеров вершин которые они соединяют) вместо TriPolArray
 *
 *
 * */
