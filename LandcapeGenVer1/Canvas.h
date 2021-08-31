#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>

#include <memory>
#include <iostream>

using namespace std;

#define MULT mult
#define SCALE scale//30//15//7//3

#include "HeightsMap/HeightsMap.h"
#include "HeightsMap/HeightsMapPoints.h"
#include "Triangles/TriPolArray.h"
#include "Triangles/TriangularPolygon.h"
#include "ZBuffer/ZBufferAlg.h"

enum DrawAlg //not good because of static cast?
{
    CARCAS,
    TRIANGULAR,
    ZBUFFER_PARAM,
    ZBUFFER_INTERPOLATION,
};

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void generateNewLandscape(int size);
    void draw();
    void cleanQImage();
    void resetHeightsMap();
    void updateResolution();

    //Resolution setters
    void setWidth(int new_width);
    void setHeight(int new_height);

    //generating seters
    void setScale(double new_scale);
    void setRange(float new_range);
    //void setLevel(unsigned new_level);

    //drawing seters
    void setDrawAlg(DrawAlg alg);
    void setMult(int new_mult);

    //transforming
    void transform(Point move, Point scale, Point rotate);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);

private:
    //Resolution parametres
    int img_width = 720;
    int img_height = 405;

    //unique_ptr<QPainter> painter = nullptr;
    unique_ptr<QImage> my_img = nullptr;

    bool LMB_is_pressed = false;
    bool RMB_is_pressed = false;
    int previous_x = 0, previous_y = 0;

    //generating parametres
    double scale = 16;
    float range = 24.75;
    //unsigned level = 33;

    //drawing parametres
    DrawAlg draw_alg = ZBUFFER_PARAM;//CARCAS;
    int mult = 1;
    int red = 20;
    int green = 150;
    int blue = 20;
    //QColor landscapeColor;

    unique_ptr<HeightsMap> heights_map;
    shared_ptr<HeightsMapPoints> heights_map_points;

    shared_ptr<TriPolArray> tri_pol_mas;
    unique_ptr<ZBufferAlg> zbuffer_alg;
    shared_ptr<FrameBuffer> frame_buffer;

private:
    int sign(double val);
    void plotImg(int x, int y, QColor c);
    void plotXImg(int x, int y, QColor c, int m = 1);
    void DrawLineBrezenheimFloat(Point p1, Point p2);
    void DrawLineBrezenheimFloat(double X_start, double Y_start, double X_end, double Y_end);

    void drawLandScape();
    void carcasDraw();
    void triangularDraw();
    void zbufferParamDraw();
    void zbufferInterpolationDraw();
};

#endif // CANVAS_H
