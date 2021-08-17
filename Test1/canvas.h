#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>

#include <memory>
#include <iostream>

#include "point.h"
#include "camera.h"

using namespace std;

#include "defines.h"

//#include "C:\GitRepositys\LandscapeTest\HeightsMap\heightsmap.h"
#include "heightsmap.h"
#include "heightsmappoints.h" //?
#include "zbufferalg.h"
#include "tripolmas.h"
//#include "zbuffer.h"
//#include "framebuffer.h"

int sign(double val);

//void print_mtrx(int x, int y, int mtrx[x][y]);

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void generateNewLandscape(int size);
    void cleanQtCanvas();
    void resetHeightsMap();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);

public:
    double heights_map[MAX_X][MAX_Y];
    unique_ptr<HeightsMap> heights_map2;
    shared_ptr<HeightsMapPoints> heights_map_points;

    shared_ptr<TriPolMas> tri_pol_mas;
    unique_ptr<ZBufferAlg> zbuffer_alg;
    shared_ptr<FrameBuffer> frame_buffer;

private:
    unique_ptr<QPainter> painter = nullptr;
    unique_ptr<QPixmap> my_pixmap = nullptr;
    unique_ptr<QImage> my_img = nullptr;

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
    void drawHeightsMap1();
    void drawHeightsMap2();
    void drawHeightsMap3();
    void drawHeightsMap4();
    void drawHeightsMap5();
    void drawHeightsMap6();
    void drawHeightsMap7();

    Point getProection(Point &_point, Point cameraPosition, Point angles);
    void plot(int x, int y);
    void plotX4(int x, int y);
    void plotX4Img(int x, int y, QColor c);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);

};

#endif // CANVAS_H
