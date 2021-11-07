#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>

#include <memory>
#include <iostream>
#include <thread>

using namespace std;

#define MULT mult
//#define SCALE scale_k//30//15//7//3

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
    ZBUFFER_PARAM_THREADS
};

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void generateNewLandscape(int size);
    void readFromFile(string file_name);
    void writeToFile(string file_name);
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
    void setSmoothing(bool new_smoothing);

    //drawing seters
    void setDrawAlg(DrawAlg alg);
    void setMult(int new_mult);
    void setLandscapeColor(int r, int g, int b);

    //transforming
    void transform(const Point& move, const Point& scale, const Point& rotate);
    void move(const Point& move);
    void scale(const Point& scale);
    void rotate(const Point& rotate);

    QColor getColor();

    void setThreadsNumber(int n);

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
    double scale_k = 16; //DOES NOT USE ANYMORE
    float range = 24.75;
    bool smoothing = false;

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

    int threads_number = 1;

private:
    int sign(double val);
    void plotImg(int x, int y, QColor c);
    void plotXImg(int x, int y, QColor c, int m = 1);
    void drawImageFT(int i0, int i1);
    void DrawLineBrezenheimFloat(const Point &p1, const Point &p2, QColor c = Qt::black);
    void DrawLineBrezenheimFloat(double X_start, double Y_start, double X_end, double Y_end, QColor c = Qt::black);

    void drawLandScape();
    void carcasDraw();
    void triangularDraw();
    void zbufferParamDraw();
    void zbufferParamDrawWithThreads();
    void zbufferInterpolationDraw();
};

#endif // CANVAS_H
