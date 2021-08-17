#include "Canvas.h"

#include <QMessageBox>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    int img_width = 720;
    int img_height = 405;
    setFixedSize(img_width+2, img_height+2);
    setStyleSheet("border-style: solid; border-width: 1px; border-color: black; background-color:white;");

    //painter = make_unique<QPainter>(this);

    resetHeightsMap();

    my_img.reset();
    cleanQImage();
}

Canvas::~Canvas()
{
    /*if (painter->isActive())
        painter->end();*/
}

void Canvas::generateNewLandscape(int size)
{
    cleanQImage();
    heights_map = make_unique<HeightsMap>(size);

    heights_map->diamondSquare();

    heights_map_points = heights_map->createPoints(SCALE, SCALE, SCALE);

    drawLandScape();

    update();
}

void Canvas::cleanQImage()
{
    //cout << "Canvas Width = "<< width() << "; Canvas Height = " << height() << endl;
    my_img = make_unique<QImage>(img_width, img_height, QImage::Format_RGB32);
    my_img->fill(Qt::white);

    update();
}

void Canvas::resetHeightsMap()
{
    heights_map = make_unique<HeightsMap>();
    heights_map_points = heights_map->createPoints();
}

void Canvas::setDrawAlg(int id)
{
    draw_alg = static_cast<DrawAlg>(id);
    /*switch (id)
    {
        case 0:
            drawAlgId = CARCAS;
            break;
        default:
            //???
            break;
    }*/
}

void Canvas::setDrawAlg(DrawAlg alg)
{
    draw_alg = alg;
}

void Canvas::paintEvent(QPaintEvent *)
{
    //painter->drawImage(1, 1, *my_img);
    QPainter pixmap_painter(this);

    pixmap_painter.drawImage(1, 1, *my_img);
}

int Canvas::sign(double val)
{
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    else
        return 0;
}

void Canvas::plotImg(int x, int y, QColor c)
{
    my_img->setPixelColor(x, y, c);
}

void Canvas::plotXImg(int x, int y, QColor c, int mult)
{
    for (int i = 0; i <= mult; i++)
        for (int j = 0; j <= mult; j++)
            my_img->setPixelColor((mult*x)+i, (mult*y)+j, c);
}

void Canvas::DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end)
{
    int X = X_start, Y = Y_start;
    int dX = X_end - X_start, dY = Y_end - Y_start;
    int SX = sign(dX), SY = sign(dY);
    dX = abs(dX), dY = abs(dY);

    int steep;
    if (dY >= dX)
    {
        //dX, dY = dY, dX;
        int tmp = dX;
        dX = dY;
        dY = tmp;
        steep = 1; // шагаем по y
    }
    else
        steep = 0;

    double tg = double(dY) / double(dX) ; // tангенс угла наклона
    double er = tg - 0.5; // начальное значение ошибки

    if (X >= img_width || X < 0 || Y >= img_height || Y < 0)
        return;
    plotImg(X, Y, Qt::black);
    while (X != X_end || Y != Y_end)
    {
        if (er >= 0)
        {
            if (steep == 1) // dy >= dx
                X += SX;
            else // dy < dx
                Y += SY;
            er -= 1; // отличие от целого
        }
        if (er <= 0)
        {
            if (steep == 0) // dy < dx
                X += SX;
            else // dy >= dx
                Y += SY;
            er += tg; // отличие от целого
        }
        if (X >= img_width || X < 0 || Y >= img_height || Y < 0)
            return;
        plotImg(X, Y, Qt::black);
    }
}

void Canvas::drawLandScape()
//QMessageBox::information(this, "Error", "No such AlgId");
{
    switch (draw_alg)
    {
        case CARCAS:
            carcasDraw();
            break;
        default:
            //QMessageBox::information(this, "Error", "No such AlgId");//?
            cout << "No such AlgId" << endl; //?
            break;
    }
}

void Canvas::carcasDraw()
{
    //painter->setPen(Qt::black);
    int HMPsize = heights_map_points->getSize();
    for (int i = 0; i < HMPsize; i++)
        for (int j = 1; j < HMPsize; j++)
        {
            Point tmp_point1 = (*heights_map_points)(i, j-1);

            Point tmp_point2 = (*heights_map_points)(i, j);

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
    for (int i = 1; i < HMPsize; i++)
        for (int j = 0; j < HMPsize; j++)
        {
            Point tmp_point1 = (*heights_map_points)(i-1, j);

            Point tmp_point2 = (*heights_map_points)(i, j);

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
}
