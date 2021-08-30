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
 * 1) Изменить вычисление координаты z, без использования уиножения и деления в цикле
 * 2) Изменить буфер кадра, чтобы он хранил только интенсивность а не сам цвет?
 * 3) Сделать общий цвет для TriPolMas и отдельную интенсивность для каждого полигона?
 * ?) Создать структуру из HeightsMapPoints и массива треугольников(номеров вершин которые они соединяют) вместо TriPolArray
 *
 *
 * */
