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
 * 0) Убрать Level из интерфейса, всегда = size-1 или просто size
 * 2) Добавить в интерфейс выбор цвета ландшафта.
 * 3) Изменить вычисление координаты z, без использования уиножения и деления в цикле
 * 4) Изменить буфер кадра, чтобы он хранил только интенсивность а не сам цвет?
 * 5) Сделать общий цвет для TriPolMas и отдельную интенсивность для каждого полигона?
 * ?) Создать структуру из HeightsMapPoints и массива треугольников(номеров вершин которые они соединяют) вместо TriPolArray
 *
 *
 * */
