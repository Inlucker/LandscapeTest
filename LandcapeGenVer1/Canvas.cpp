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

    draw_alg = ZBUFFER_PARAM;
    mult = 1;
    scale = 16;

    my_img.reset();
    frame_buffer.reset();
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

    heights_map->diamondSquare(range, level);

    /*heights_map_points = heights_map->createPoints();
    heights_map_points->transform(Point(0, 0, 0), Point(SCALE, SCALE, SCALE), Point(0, 0, 0));*/
    heights_map_points = heights_map->createPoints(SCALE/MULT, SCALE/MULT, SCALE/MULT);

    tri_pol_mas = heights_map_points->createTriPolArray();

    const Point& c = heights_map_points->getCenter();
    heights_map_points->transform(Point(-c.getX() + (img_width/(2*MULT)), -c.getY() + (img_height/(2*MULT)), -c.getZ()), Point(1, 1, 1), Point(0, 0, 0));
    heights_map_points->transform(Point(0, 0, 0), Point(1, 1, 1), Point(0, 0, 180));

    //zbuffer_alg = make_unique<ZBufferAlg>(img_width/MULT, img_height/MULT);
    zbuffer_alg = make_unique<ZBufferAlg>(img_height/MULT, img_width/MULT); // fix width and height

    drawLandScape();

    update();
}

void Canvas::draw()
{
    drawLandScape();
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
    //zbuffer_alg = make_unique<ZBufferAlg>(img_width/MULT, img_height/MULT); //(500, 500);
    zbuffer_alg = make_unique<ZBufferAlg>(img_height/MULT, img_width/MULT); //(500, 500);
}

void Canvas::setScale(double new_scale)
{
    scale = new_scale;
}

void Canvas::setRange(float new_range)
{
    range = new_range;
}

void Canvas::setLevel(unsigned new_level)
{
    level = new_level;
}

void Canvas::setDrawAlg(DrawAlg alg)
{
    draw_alg = alg;
    drawLandScape();
}

void Canvas::setMult(int new_mult)
{
    const Point& c = heights_map_points->getCenter();
    heights_map_points->transform(Point(-c.getX() + (img_width/(2*new_mult)), -c.getY() + (img_height/(2*new_mult)), -c.getZ()), Point(1, 1, 1), Point(0, 0, 0));
    heights_map_points->transform(Point(0, 0, 0), Point(double(mult)/new_mult, double(mult)/new_mult, double(mult)/new_mult), Point(0, 0, 0));
    mult = new_mult;
    zbuffer_alg = make_unique<ZBufferAlg>(img_height/MULT, img_width/MULT);
    drawLandScape();
}

void Canvas::transform(Point move, Point scale, Point rotate)
{
    heights_map_points->transform(move, scale, rotate);
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
#define MOVE_SPEED mult

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

void Canvas::plotXImg(int x, int y, QColor c, int m)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if ((m*x)+i < img_width && (m*x)+i >= 0 && (m*y)+j < img_height && (m*y)+j >= 0)
            {
                my_img->setPixelColor((m*x)+i, (m*y)+j, c);
            }
}

void Canvas::DrawLineBrezenheimFloat(Point p1, Point p2)
{
    DrawLineBrezenheimFloat(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void Canvas::DrawLineBrezenheimFloat(double X_start, double Y_start, double X_end, double Y_end)
{
    int X1 = round(X_start), Y1 = round(Y_start), X2 = round(X_end), Y2 = round(Y_end);
    int X = X1, Y = Y1;
    int dX = X2 - X1, dY = Y2 - Y1;
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

    /*if (!(X >= img_width || X < 0 || Y >= img_height || Y < 0))
        plotImg(X, Y, Qt::black);*/
    plotXImg(X, Y, Qt::black, MULT);
    while (X != X2 || Y != Y2)
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
        /*if (!(X >= img_width || X < 0 || Y >= img_height || Y < 0))
            plotImg(X, Y, Qt::black);*/
        plotXImg(X, Y, Qt::black, MULT);
    }
}

void Canvas::drawLandScape()
{
    cleanQImage();
    switch (draw_alg)
    {
    case CARCAS:
        carcasDraw();
        break;
    case TRIANGULAR:
        triangularDraw();
        break;
    case ZBUFFER_PARAM:
        zbufferParamDraw();
        break;
    default:
        QMessageBox::information(this, "Error", "No such DrawAlg");//?
        break;
    }
    update();
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
    tri_pol_mas->updatePoints(*heights_map_points);
    for (auto &tri_pol : *tri_pol_mas)
    {
        DrawLineBrezenheimFloat(tri_pol.getP1(), tri_pol.getP2());
        DrawLineBrezenheimFloat(tri_pol.getP2(), tri_pol.getP3());
        DrawLineBrezenheimFloat(tri_pol.getP3(), tri_pol.getP1());
    }
}

void Canvas::zbufferParamDraw()
{
    //painter->setPen(Qt::black);
    //UPDATE POINTS
    clock_t start = clock();
    //tri_pol_mas = heights_map3->createTriPolMas();
    tri_pol_mas->updatePoints(*heights_map_points);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "updatePoints() time = " << seconds << " secs" << endl;

    //Z-BUFFER ALGORITHM
    start = clock();
    zbuffer_alg->execute(*tri_pol_mas);
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "zbuffer_alg->execute() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();
    //cout << *frame_buffer << endl;

    //PAINT
    start = clock();
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            //plotImg(i, j, (*frame_buffer)(i, j));
            plotXImg(i, j, (*frame_buffer)(i, j), MULT);
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "paint time = " << seconds << " secs" << endl;
}
