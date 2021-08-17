#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    int img_width = 720;
    int img_height = 405;
    setFixedSize(img_width+2, img_height+2);
    setStyleSheet("border-style: solid; border-width: 1px; border-color: black; background-color:white;");
    //setStyleSheet("background-color:white;");

    //painter = make_unique<QPainter>(this);

    //resetHeightsMap();

    //my_img.reset();
    cleanQImage();
}

Canvas::~Canvas()
{
    /*if (painter->isActive())
        painter->end();*/
}

void Canvas::generateNewLandscape(int size)
{

}

void Canvas::cleanQImage()
{
    cout << "Canvas Width = "<< width() << "; Canvas Height = " << height() << endl;
    my_img = make_unique<QImage>(img_width, img_height, QImage::Format_RGB32);
    my_img->fill(Qt::white);

    update();
}

void Canvas::resetHeightsMap()
{

}

void Canvas::paintEvent(QPaintEvent *)
{
    //painter->drawImage(0, 0, *my_img);
    QPainter pixmap_painter(this);

    pixmap_painter.drawImage(1, 1, *my_img);
}
