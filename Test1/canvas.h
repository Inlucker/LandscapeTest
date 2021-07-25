#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>

#include <memory>
#include <iostream>

#include "point.h"
#include "camera.h"

using namespace std;

#define MAX_X 20
#define MAX_Y 20

int sign(double val);

//void print_mtrx(int x, int y, int mtrx[x][y]);

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void generateNewLandscape();
    void clean();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public:
    double heights_map[MAX_X][MAX_Y];

private:
    unique_ptr<QPainter> painter = nullptr;
    unique_ptr<QPixmap> my_pixmap = nullptr;

    bool LMB_is_pressed = false;
    bool RMB_is_pressed = false;
    int previous_x = 0, previous_y = 0;

    unique_ptr<Camera> camera = nullptr;

private:
    void reset_heights_map();
    void print_heights_map();
    void randomizeHeightsMap();
    void smoothHeightsMap();
    double getHeight(int i, int j);

    void drawHeightsMap();

    Point getProection(Point &_point, Point cameraPosition, Point angles);
    void plot(int x, int y);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);

};

#endif // CANVAS_H
