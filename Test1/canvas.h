#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>

#include <memory>
#include <iostream>

using namespace std;

#define MAX_X 4
#define MAX_Y 4

int sign(double val);

//void print_mtrx(int x, int y, int mtrx[x][y]);

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void clean();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public:
    double heights_map[MAX_X][MAX_Y];

private:
    unique_ptr<QPainter> painter = nullptr;
    unique_ptr<QPixmap> my_pixmap = nullptr;

private:
    void reset_heights_map();
    void print_heights_map();
    void randomizeHeightsMap();
    void smoothHeightsMap();
    double checkIds(int i, int j);

    void plot(int x, int y);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);

};

#endif // CANVAS_H
