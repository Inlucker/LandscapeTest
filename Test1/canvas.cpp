#include "canvas.h"

#include "constiterator.h"
#include "iterator.h"

#include "random"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color:white;");

    reset_heights_map();
    resetHeightsMap();
    //print_heights_map();

    camera = make_unique<Camera>(); // (Point(460, 400, -200), Point(-45, -45, 20));
    //camera = make_unique<Camera>(Point(460, 400, -200), Point(-45, -45, 20));

    painter.reset();
    my_pixmap.reset();
    my_img.reset();
    cleanQtCanvas();
}

Canvas::~Canvas()
{
    /*if (painter->isActive())
        painter->end();*/
}

void Canvas::generateNewLandscape(int size)
{
    cleanQtCanvas();
    heights_map2 = make_unique<HeightsMap>(size);
    //randomizeHeightsMap();
    heights_map2->randomizeHeightsMap();
    //print_heights_map();

    //smoothHeightsMap();
    heights_map2->smoothHeightsMap();
    //print_heights_map();

    heights_map2->diamondSquare();
    //cout << *heights_map2 << endl;

    heights_map_points = heights_map2->createPoints(SCALE_XZ, SCALE_Y, SCALE_XZ);

    zbuffer_alg = make_unique<ZBufferAlg>(720/MULT, 1040/MULT); //(500, 500);

    tri_pol_mas = heights_map_points->createTriPolMas();
    drawHeightsMap();

    update();
}

void Canvas::cleanQtCanvas()
{
    /*if (painter)
        painter->end();
    my_pixmap = make_unique<QPixmap>(1200, 1200);
    my_pixmap->fill(QColor(0, 0, 0, 0));
    painter = make_unique<QPainter>(&(*my_pixmap));
    painter->setPen(Qt::black);*/

    my_img = make_unique<QImage>(1200, 1200, QImage::Format_RGB32);
    my_img->fill(Qt::white);

    update();
}

void Canvas::resetHeightsMap()
{
    heights_map2 = make_unique<HeightsMap>(SIZE);
    heights_map_points = heights_map2->createPoints(SCALE_XZ, SCALE_Y, SCALE_XZ);
    zbuffer_alg = make_unique<ZBufferAlg>(720/MULT, 1040/MULT);
    tri_pol_mas = heights_map_points->createTriPolMas();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        LMB_is_pressed = false;
    }

    if (event->button() == Qt::RightButton)
    {
        RMB_is_pressed = false;
    }
    //cout << camera->getAngles().getX() << "; " << camera->getAngles().getY() << "; " << camera->getAngles().getZ() << endl;
    //cout << camera->getPosition().getX() << "; " << camera->getPosition().getY() << "; " << camera->getPosition().getZ() << endl;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    previous_x = event->position().x();
    previous_y = event->position().y();
    if (event->button() == Qt::LeftButton && !LMB_is_pressed && this->rect().contains(event->pos()))
    {
        LMB_is_pressed = true;
    }
    if (event->button() == Qt::RightButton && !RMB_is_pressed && this->rect().contains(event->pos()))
    {
        RMB_is_pressed = true;
    }
}

#define ROTATE_SPEED 5
#define MOVE_SPEED 2

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (LMB_is_pressed)
    {
        double x = double(previous_x - event->position().x()) / ROTATE_SPEED;
        double y = double(previous_y - event->position().y()) / ROTATE_SPEED;

        //camera->transform(Point(0, 0, 0), Point(1, 1, 1), Point(y, x, 0));
        heights_map_points->transform(Point(0, 0, 0), Point(1, 1, 1), Point(-y, -x, 0));
        //heights_map3->transform(Point(0, 0, 0), Point(1, 1, 1), Point(0, x, y));

        cleanQtCanvas();
        drawHeightsMap();
    }
    else if (RMB_is_pressed)
    {
        double x = double(previous_x - event->position().x()) / MOVE_SPEED;
        double y = double(previous_y - event->position().y()) / MOVE_SPEED;

        //camera->transform(Point(-x, -y, 0), Point(1, 1, 1), Point(0, 0, 0));
        heights_map_points->transform(Point(-x, -y, 0), Point(1, 1, 1), Point(0, 0, 0));

        cleanQtCanvas();
        drawHeightsMap();
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

    cleanQtCanvas();
    drawHeightsMap();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter pixmap_painter(this);

    //pixmap_painter.drawPixmap(0, 0, *my_pixmap);
    pixmap_painter.drawImage(0, 0, *my_img);
}

void Canvas::reset_heights_map()
{
    for (int i = 0; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
            heights_map[i][j] = 0;
}

void Canvas::print_heights_map()
{
    //print_mtrx(MAX_X, MAX_Y, heights_map);

    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
            cout << heights_map[i][j] << "; ";
        cout << endl;
    }
    cout << endl;
}

void Canvas::randomizeHeightsMap()
{
    for (int i = 0; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
            heights_map[i][j] = (rand() % 16);
}

void Canvas::smoothHeightsMap()
{
    for (int i = 0; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            double tmp_sum = 0;
            int tmp_n = 0;

            //cout << "(";
            double tmp = getHeight(i-1, j-1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = getHeight(i-1, j);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = getHeight(i-1, j+1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = getHeight(i, j-1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = getHeight(i, j);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = getHeight(i, j+1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = getHeight(i+1, j-1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = getHeight(i+1, j);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = getHeight(i+1, j+1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            heights_map[i][j] = tmp_sum / tmp_n;
            //cout  << ")/" << tmp_n << " = "<< tmp_sum << "/" << tmp_n << " = " << heights_map[i][j] << endl;
        }
}

double Canvas::getHeight(int i, int j)
{
    if (i >= 0 && i <= MAX_X && j >= 0 && j <= MAX_Y)
    {
        //cout << "+ " << heights_map[i][j] << " ";
        return heights_map[i][j];
    }
    else
        return -1;
}

void Canvas::drawHeightsMap()
{
    drawHeightsMap5();
}

//#define SCALE 25

void Canvas::drawHeightsMap1()
{
    //painter->setPen(Qt::red);
    for (int i = 0; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            Point tmp_point(i * SCALE_XZ, heights_map[i][j] * SCALE_Y, j * SCALE_XZ);
            tmp_point = getProection(tmp_point, camera->getPosition(), camera->getAngles());

            //painter->drawEllipse(QPointF(tmp_point.getX(), tmp_point.getY()), 5, 5);
        }
    //painter->setPen(Qt::black);
    for (int i = 0; i < MAX_X; i++)
        for (int j = 1; j < MAX_Y; j++)
        {
            Point tmp_point1(i * SCALE_XZ, heights_map[i][j-1] * SCALE_Y, (j-1) * SCALE_XZ);
            tmp_point1 = getProection(tmp_point1, camera->getPosition(), camera->getAngles());

            Point tmp_point2(i * SCALE_XZ, heights_map[i][j] * SCALE_Y, j * SCALE_XZ);
            tmp_point2 = getProection(tmp_point2, camera->getPosition(), camera->getAngles());

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
    for (int i = 1; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            Point tmp_point1((i-1) * SCALE_XZ, heights_map[i-1][j] * SCALE_Y, j * SCALE_XZ);
            tmp_point1 = getProection(tmp_point1, camera->getPosition(), camera->getAngles());

            Point tmp_point2(i * SCALE_XZ, heights_map[i][j] * SCALE_Y, j * SCALE_XZ);
            tmp_point2 = getProection(tmp_point2, camera->getPosition(), camera->getAngles());

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
}

void Canvas::drawHeightsMap2()
{
    //painter->setPen(Qt::red);
    for (int i = 0; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            //Point tmp_point(i * SCALE, (*heights_map2)[i*heights_map2->getSize()+j] * SCALE, j * SCALE);
            Point tmp_point(i * SCALE_XZ, (*heights_map2)(i, j) * SCALE_Y, j * SCALE_XZ);
            tmp_point = getProection(tmp_point, camera->getPosition(), camera->getAngles());

            //painter->drawEllipse(QPointF(tmp_point.getX(), tmp_point.getY()), 5, 5);
        }
    //painter->setPen(Qt::black);
    for (int i = 0; i < MAX_X; i++)
        for (int j = 1; j < MAX_Y; j++)
        {
            //Point tmp_point1(i * SCALE, (*heights_map2)[i*heights_map2->getSize()+j-1] * SCALE, (j-1) * SCALE);
            Point tmp_point1(i * SCALE_XZ, (*heights_map2)(i, j-1) * SCALE_Y, (j-1) * SCALE_XZ);
            tmp_point1 = getProection(tmp_point1, camera->getPosition(), camera->getAngles());

            //Point tmp_point2(i * SCALE, (*heights_map2)[i*heights_map2->getSize()+j] * SCALE, j * SCALE);
            Point tmp_point2(i * SCALE_XZ, (*heights_map2)(i, j) * SCALE_Y, j * SCALE_XZ);
            tmp_point2 = getProection(tmp_point2, camera->getPosition(), camera->getAngles());

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
    for (int i = 1; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            //Point tmp_point1((i-1) * SCALE, (*heights_map2)[(i-1)*heights_map2->getSize()+j] * SCALE, j * SCALE);
            Point tmp_point1((i-1) * SCALE_XZ, (*heights_map2)(i-1, j) * SCALE_Y, j * SCALE_XZ);
            tmp_point1 = getProection(tmp_point1, camera->getPosition(), camera->getAngles());

            //Point tmp_point2(i * SCALE, (*heights_map2)[i*heights_map2->getSize()+j] * SCALE, j * SCALE);
            Point tmp_point2(i * SCALE_XZ, (*heights_map2)(i, j) * SCALE_Y, j * SCALE_XZ);
            tmp_point2 = getProection(tmp_point2, camera->getPosition(), camera->getAngles());

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
}

void Canvas::drawHeightsMap3()
{
    //painter->setPen(Qt::black);
    for (int i = 0; i < MAX_X; i++)
        for (int j = 1; j < MAX_Y; j++)
        {
            Point tmp_point1 = (*heights_map_points)(i, j-1);
            tmp_point1 = getProection(tmp_point1, camera->getPosition(), camera->getAngles());

            Point tmp_point2 = (*heights_map_points)(i, j);
            tmp_point2 = getProection(tmp_point2, camera->getPosition(), camera->getAngles());

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
    for (int i = 1; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            Point tmp_point1 = (*heights_map_points)(i-1, j);
            tmp_point1 = getProection(tmp_point1, camera->getPosition(), camera->getAngles());

            Point tmp_point2 = (*heights_map_points)(i, j);
            tmp_point2 = getProection(tmp_point2, camera->getPosition(), camera->getAngles());

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
}

//EdgeDraw
void Canvas::drawHeightsMap4()
{
    //painter->setPen(Qt::black);
    //Check time HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    clock_t start = clock();
    //tri_pol_mas = heights_map3->createTriPolMas();
    tri_pol_mas->updatePoints(*heights_map_points);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "createTriPolMas() time = " << seconds << " secs" << endl;

    start = clock();
    zbuffer_alg->execute(*tri_pol_mas);
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "zbuffer_alg->execute() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();

    start = clock();
    QColor cur = Qt::white;
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            if ((*frame_buffer)(i, j) != cur)
            {
                //painter->drawPoint(i, j);
                //plotX4(i, j);
                plotX4Img(i, j, Qt::black);
                cur = (*frame_buffer)(i, j);
            }
        }
    }

    cur = Qt::white;
    It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getWidth() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getHeight() && It != frame_buffer->cend(); It++, j++)
        {
            if ((*frame_buffer)(j, i) != cur)
            {
                //painter->drawPoint(j, i);
                //plotX4(j, i);
                plotX4Img(j, i, Qt::black);
                cur = (*frame_buffer)(j, i);
            }
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "paint time = " << seconds << " secs" << endl;
}

//FillDraw
void Canvas::drawHeightsMap5()
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

    //PAINT
    start = clock();
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            /*QColor c = (*frame_buffer)(i, j);
            painter->setPen(c);
            plotX4(i, j);*/
            plotX4Img(i, j, (*frame_buffer)(i, j));
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "paint time = " << seconds << " secs" << endl;
}

//EdgeDraw + FillDraw
void Canvas::drawHeightsMap6()
{
    clock_t start = clock();
    //tri_pol_mas = heights_map3->createTriPolMas();
    tri_pol_mas->updatePoints(*heights_map_points);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "updatePoints() time = " << seconds << " secs" << endl;

    start = clock();
    zbuffer_alg->execute(*tri_pol_mas);
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "zbuffer_alg->execute() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();

    start = clock();
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            /*QColor c = (*frame_buffer)(i, j);
            painter->setPen(c);
            plotX4(i, j);*/
            plotX4Img(i, j, (*frame_buffer)(i, j));
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "paint time = " << seconds << " secs" << endl;

    //painter->setPen(Qt::black);

    start = clock();
    QColor cur = Qt::white;
    It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            if ((*frame_buffer)(i, j) != cur)
            {
                //painter->drawPoint(i, j);
                //plotX4(i, j);
                plotX4Img(i, j, Qt::black);
                cur = (*frame_buffer)(i, j);
            }
        }
    }

    cur = Qt::white;
    It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getWidth() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getHeight() && It != frame_buffer->cend(); It++, j++)
        {
            if ((*frame_buffer)(j, i) != cur)
            {
                //painter->drawPoint(j, i);
                //plotX4(j, i);
                plotX4Img(j, i, Qt::black);
                cur = (*frame_buffer)(j, i);
            }
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "paint time = " << seconds << " secs" << endl;
}


//FillDraw with interpolateion
void Canvas::drawHeightsMap7()
{
    //UPDATE POINTS
    clock_t start = clock();
    //tri_pol_mas = heights_map3->createTriPolMas();
    tri_pol_mas->updatePoints(*heights_map_points);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "updatePoints() time = " << seconds << " secs" << endl;

    //Z-BUFFER ALGORITHM
    start = clock();
    zbuffer_alg->execute2(*tri_pol_mas);
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "zbuffer_alg->execute() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();

    //PAINT
    start = clock();
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            plotX4Img(i, j, (*frame_buffer)(i, j));
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "paint time = " << seconds << " secs" << endl;
}

Point Canvas::getProection(Point &_point, Point cameraPosition, Point angles)
{
    Point proection(_point);
    proection.transform(cameraPosition, Point(1, 1, 1), Point(0, 0, 0));

    proection.transform(Point(0, 0, 0), Point(1, 1, 1), Point(-angles.getX(), -angles.getY(), -angles.getZ()));

    return proection;
}

void Canvas::plot(int x, int y)
{
    //p->setPen(semiPen);
    //painter->drawPoint(x, y);
    //my_img->setPixelColor(x, y, Qt::black);
}

void Canvas::plotX4(int x, int y)
{
    //painter->drawPoint(MULT*x, MULT*y);
    for (int i = 0; i <= MULT; i++)
    {
        for (int j = 0; j <= MULT; j++)
        {
            //painter->drawPoint((MULT*x)+i, (MULT*y)+j);
        }
    }
}

void Canvas::plotX4Img(int x, int y, QColor c)
{
    for (int i = 0; i <= MULT; i++)
        for (int j = 0; j <= MULT; j++)
            my_img->setPixelColor((MULT*x)+i, (MULT*y)+j, c);
}

int sign(double val)
{
  if (val > 0)
      return 1;
  if (val < 0)
      return -1;
  else
      return 0;
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

    //QPainter painter(&my_pixmap);
    //painter.setPen(pen);

    //painter->drawPoint(X, Y);
    my_img->setPixelColor(X, Y, Qt::black);
    while (X != X_end || Y != Y_end)
    {
        if (er >= 0)
        {
            if (steep == 1) // dy >= dx
                X += SX;
            else // dy < dx
                Y += SY;
            er -= 1; // отличие от целого
            //stairs.append(st)
            //st = 0
        }
        if (er <= 0)
        {
            if (steep == 0) // dy < dx
                X += SX;
            else // dy >= dx
                Y += SY;
            //st += 1
            er += tg; // отличие от целого
        }
        //painter->drawPoint(X, Y);
        my_img->setPixelColor(X, Y, Qt::black);
    }
}

/*void print_mtrx(int x, int y, int mtrx[x][y])
{
    for (int i = 0; i <= x; i++)
    {
        for (int j = 0; j <= y; j++)
            cout << mtrx[i][j] << "; ";
        cout << endl;
    }
}*/
