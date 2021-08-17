#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>

#include <memory>
#include <iostream>

using namespace std;

#define MULT 1
#define SCALE 30//15//7//3

#include "HeightsMap/HeightsMap.h"
#include "HeightsMap/HeightsMapPoints.h"

enum DrawAlg //not good because of static cast?
{
    CARCAS = 0
};

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void generateNewLandscape(int size);
    void cleanQImage();
    void resetHeightsMap();

    void setDrawAlg(DrawAlg alg);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);

private:
    int img_width = 720;
    int img_height = 405;

    //unique_ptr<QPainter> painter = nullptr;
    unique_ptr<QImage> my_img = nullptr;

    bool LMB_is_pressed = false;
    bool RMB_is_pressed = false;
    int previous_x = 0, previous_y = 0;

    DrawAlg draw_alg = CARCAS;

    unique_ptr<HeightsMap> heights_map;
    shared_ptr<HeightsMapPoints> heights_map_points;

    //shared_ptr<TriPolMas> tri_pol_mas;
    //unique_ptr<ZBufferAlg> zbuffer_alg;
    //shared_ptr<FrameBuffer> frame_buffer;

private:
    int sign(double val);
    void plotImg(int x, int y, QColor c);
    void plotXImg(int x, int y, QColor c, int mult = 1);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);

    void drawLandScape();
    void carcasDraw();
};

#endif // CANVAS_H
