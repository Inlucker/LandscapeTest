#include "canvas.h"

#include "random"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color:white;");

    reset_heights_map();
    heights_map2 = make_unique<HeightsMap>(MAX_X);
    //print_heights_map();

    camera = make_unique<Camera>(); // (Point(460, 400, -200), Point(-45, -45, 20));
    //camera = make_unique<Camera>(Point(460, 400, -200), Point(-45, -45, 20));

    painter.reset();
    my_pixmap.reset();
    clean();
}

Canvas::~Canvas()
{
    if (painter->isActive())
        painter->end();
}

void Canvas::generateNewLandscape()
{
    clean();
    randomizeHeightsMap();
    heights_map2->randomizeHeightsMap();
    //print_heights_map();

    smoothHeightsMap();
    heights_map2->smoothHeightsMap();
    //print_heights_map();

    heights_map2->diamondSquare();
    //cout << *heights_map2 << endl;

    heights_map3 = heights_map2->createPoints(SCALE_XZ, SCALE_Y, SCALE_XZ);

    zbuffer_alg = make_unique<ZBufferAlg>(700, 1000);

    //drawHeightsMap();
    //drawHeightsMap2();
    //drawHeightsMap3();
    drawHeightsMap4();

    update();
}

void Canvas::clean()
{
    if (painter)
        painter->end();
    my_pixmap = make_unique<QPixmap>(2000, 2000);
    my_pixmap->fill(QColor(0, 0, 0, 0));
    painter = make_unique<QPainter>(&(*my_pixmap));
    painter->setPen(Qt::black);

    update();
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
        heights_map3->transform(Point(0, 0, 0), Point(1, 1, 1), Point(y, x, 0));
        //heights_map3->transform(Point(0, 0, 0), Point(1, 1, 1), Point(0, x, y));

        clean();
        //drawHeightsMap();
        //drawHeightsMap2();
        //drawHeightsMap3();
        drawHeightsMap4();
    }
    else if (RMB_is_pressed)
    {
        double x = double(previous_x - event->position().x()) / MOVE_SPEED;
        double y = double(previous_y - event->position().y()) / MOVE_SPEED;

        //camera->transform(Point(-x, -y, 0), Point(1, 1, 1), Point(0, 0, 0));
        heights_map3->transform(Point(-x, -y, 0), Point(1, 1, 1), Point(0, 0, 0));

        clean();
        //drawHeightsMap();
        //drawHeightsMap2();
        //drawHeightsMap3();
        drawHeightsMap4();
    }

    update();

    previous_x = event->position().x();
    previous_y = event->position().y();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter pixmap_painter(this);

    pixmap_painter.drawPixmap(0, 0, *my_pixmap);
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

//#define SCALE 25

void Canvas::drawHeightsMap()
{
    painter->setPen(Qt::red);
    for (int i = 0; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            Point tmp_point(i * SCALE_XZ, heights_map[i][j] * SCALE_Y, j * SCALE_XZ);
            tmp_point = getProection(tmp_point, camera->getPosition(), camera->getAngles());

            painter->drawEllipse(QPointF(tmp_point.getX(), tmp_point.getY()), 5, 5);
        }
    painter->setPen(Qt::black);
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
    painter->setPen(Qt::red);
    for (int i = 0; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            //Point tmp_point(i * SCALE, (*heights_map2)[i*heights_map2->getSize()+j] * SCALE, j * SCALE);
            Point tmp_point(i * SCALE_XZ, (*heights_map2)(i, j) * SCALE_Y, j * SCALE_XZ);
            tmp_point = getProection(tmp_point, camera->getPosition(), camera->getAngles());

            //painter->drawEllipse(QPointF(tmp_point.getX(), tmp_point.getY()), 5, 5);
        }
    painter->setPen(Qt::black);
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
    painter->setPen(Qt::black);
    for (int i = 0; i < MAX_X; i++)
        for (int j = 1; j < MAX_Y; j++)
        {
            Point tmp_point1 = (*heights_map3)(i, j-1);
            tmp_point1 = getProection(tmp_point1, camera->getPosition(), camera->getAngles());

            Point tmp_point2 = (*heights_map3)(i, j);
            tmp_point2 = getProection(tmp_point2, camera->getPosition(), camera->getAngles());

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
    for (int i = 1; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            Point tmp_point1 = (*heights_map3)(i-1, j);
            tmp_point1 = getProection(tmp_point1, camera->getPosition(), camera->getAngles());

            Point tmp_point2 = (*heights_map3)(i, j);
            tmp_point2 = getProection(tmp_point2, camera->getPosition(), camera->getAngles());

            DrawLineBrezenheimFloat(tmp_point1.getX(), tmp_point1.getY(), tmp_point2.getX(), tmp_point2.getY());
        }
}

void Canvas::drawHeightsMap4()
{
    painter->setPen(Qt::black);
    //Check time HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    clock_t start = clock();
    tri_pol_mas = heights_map3->createTriPolMas();
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
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            /*if ((*frame_buffer)(i, j) == 1)
            {
                painter->drawPoint(i, j);
            }*/
            int c = (*frame_buffer)(i, j);
            painter->setPen(QColor(255-c, 255-c, 255-c));
            painter->drawPoint(i, j);
            /*int c = (*frame_buffer)(i, j);
            painter->setPen(QColor(255 - c%255, 255 - (c*4)%255, 255 - (c*5)%255));
            painter->drawPoint(i, j);*/
        }
    } 
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "paint time = " << seconds << " secs" << endl;
}

void Canvas::drawHeightsMapWithoutInvisibleLines()
{
    // TODO
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
    painter->drawPoint(x, y);
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

    painter->drawPoint(X, Y);
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
        painter->drawPoint(X, Y);
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
