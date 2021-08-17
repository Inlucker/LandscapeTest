#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
//#include <QImage>

#include <memory>
#include <iostream>

using namespace std;

#include "HeightsMap/heightsmap.h"

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void generateNewLandscape(int size);
    void cleanQImage();
    void resetHeightsMap();

protected:
    //virtual void mouseReleaseEvent(QMouseEvent *event);
    //virtual void mousePressEvent(QMouseEvent *event);
    //virtual void mouseMoveEvent(QMouseEvent *event);
    //virtual void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);

private:
    int img_width = 720;
    int img_height = 405;

    //unique_ptr<QPainter> painter = nullptr;
    unique_ptr<QImage> my_img = nullptr;

    bool LMB_is_pressed = false;
    bool RMB_is_pressed = false;
    int previous_x = 0, previous_y = 0;

    unique_ptr<HeightsMap> heights_map;
    //shared_ptr<HeightsMapPoints> heights_map_points;

    //shared_ptr<TriPolMas> tri_pol_mas;
    //unique_ptr<ZBufferAlg> zbuffer_alg;
    //shared_ptr<FrameBuffer> frame_buffer;
};

#endif // CANVAS_H
