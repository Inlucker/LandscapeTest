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

    tri_pol_mas = heights_map_points->createTriPolArray();

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
    tri_pol_mas = heights_map_points->createTriPolArray();
    //zbuffer_alg = make_unique<ZBufferAlg>(720/MULT, 1040/MULT);
}

void Canvas::setDrawAlg(DrawAlg alg)
{
    draw_alg = alg;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        LMB_is_pressed = false;

    if (event->button() == Qt::RightButton)
        RMB_is_pressed = false;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    previous_x = event->position().x();
    previous_y = event->position().y();
    if (event->button() == Qt::LeftButton && !LMB_is_pressed && this->rect().contains(event->pos()))
        LMB_is_pressed = true;

    if (event->button() == Qt::RightButton && !RMB_is_pressed && this->rect().contains(event->pos()))
        RMB_is_pressed = true;
}

#define ROTATE_SPEED 5
#define MOVE_SPEED 2

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (LMB_is_pressed)
    {
        double x = double(previous_x - event->position().x()) / ROTATE_SPEED;
        double y = double(previous_y - event->position().y()) / ROTATE_SPEED;

        heights_map_points->transform(Point(0, 0, 0), Point(1, 1, 1), Point(-y, -x, 0));

        cleanQImage();
        drawLandScape();
    }
    else if (RMB_is_pressed)
    {
        double x = double(previous_x - event->position().x()) / MOVE_SPEED;
        double y = double(previous_y - event->position().y()) / MOVE_SPEED;

        heights_map_points->transform(Point(-x, -y, 0), Point(1, 1, 1), Point(0, 0, 0));

        cleanQImage();
        drawLandScape();
    }

    update();

    previous_x = event->position().x();
    previous_y = event->position().y();
}

#define SCALE_SPEED 10

void Canvas::wheelEvent(QWheelEvent *event)
{

    QPoint numDegrees = event->angleDelta() / 120;
    double ky = 1 + double(numDegrees.y()) / SCALE_SPEED;

    heights_map_points->transform(Point(0, 0, 0), Point(ky, ky, ky), Point(0, 0, 0));

    cleanQImage();
    drawLandScape();
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

void Canvas::DrawLineBrezenheimFloat(Point p1, Point p2)
{
    DrawLineBrezenheimFloat(p1.getX(), p1.getY(), p2.getX(), p2.getY());
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
{
    switch (draw_alg)
    {
        case CARCAS:
            carcasDraw();
            break;
        case TRIANGULAR:
            triangularDraw();
            break;
        default:
            QMessageBox::information(this, "Error", "No such DrawAlg");//?
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

void Canvas::triangularDraw()
{
    tri_pol_mas = heights_map_points->createTriPolArray();
    for (auto &tri_pol : *tri_pol_mas)
    {
        DrawLineBrezenheimFloat(tri_pol.getP1(), tri_pol.getP2());
        DrawLineBrezenheimFloat(tri_pol.getP2(), tri_pol.getP3());
        DrawLineBrezenheimFloat(tri_pol.getP3(), tri_pol.getP1());
    }
}
