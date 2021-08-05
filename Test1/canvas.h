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

#define MAX_X 129//65//33//5//33
#define MAX_Y 129//65//33//5//33
#define SCALE_XZ 7//15//120//15
#define SCALE_Y 7//40//5//7

//#include "C:\GitRepositys\LandscapeTest\HeightsMap\heightsmap.h"
#include "heightsmap.h"
#include "heightsmappoints.h" //?

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
    unique_ptr<HeightsMap> heights_map2;
    shared_ptr<HeightsMapPoints> heights_map3;

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
    void drawHeightsMap2();
    void drawHeightsMap3();
    void drawHeightsMapWithoutInvisibleLines();

    Point getProection(Point &_point, Point cameraPosition, Point angles);
    void plot(int x, int y);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);

};

#endif // CANVAS_H
