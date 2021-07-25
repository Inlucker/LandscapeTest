#include "canvas.h"

#include "random"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color:white;");

    reset_heights_map();
    print_heights_map();

    clean();
}

Canvas::~Canvas()
{
    if (painter->isActive())
        painter->end();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    //DrawLineBrezenheimFloat(0, 0, 100, 100);
    randomizeHeightsMap();
    print_heights_map();

    smoothHeightsMap();
    print_heights_map();

    update();
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
            heights_map[i][j] = rand() % 11;
}

double Canvas::checkIds(int i, int j)
{
    if (i >= 0 && i <= MAX_X && j >= 0 && j <= MAX_Y)
    {
        //cout << "+ " << heights_map[i][j] << " ";
        return heights_map[i][j];
    }
    else
        return -1;
}

void Canvas::smoothHeightsMap()
{
    for (int i = 0; i < MAX_X; i++)
        for (int j = 0; j < MAX_Y; j++)
        {
            double tmp_sum = 0;
            int tmp_n = 0;

            //cout << "(";
            double tmp = checkIds(i-1, j-1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = checkIds(i-1, j);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = checkIds(i-1, j+1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = checkIds(i, j-1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = checkIds(i, j);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = checkIds(i, j+1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = checkIds(i+1, j-1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = checkIds(i+1, j);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            tmp = checkIds(i+1, j+1);
            if (tmp >= 0)
            {
                tmp_sum += tmp;
                tmp_n++;
            }

            heights_map[i][j] = tmp_sum / tmp_n;
            //cout  << ")/" << tmp_n << " = "<< tmp_sum << "/" << tmp_n << " = " << heights_map[i][j] << endl;
        }
}

void Canvas::plot(int x, int y)
{
    //p->setPen(semiPen);
    painter->drawPoint(x, y);
}

void Canvas::clean()
{
    my_pixmap = make_unique<QPixmap>(2000, 2000);
    my_pixmap->fill(QColor(0, 0, 0, 0));

    painter = make_unique<QPainter>(&(*my_pixmap));
    painter->setPen(Qt::black);

    update();
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
