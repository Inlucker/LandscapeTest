#include "Canvas.h"

#include <QMessageBox>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    img_width = 960; //1280; //720;
    img_height = 540; //720; //405;
    setFixedSize(img_width+2, img_height+2);
    setStyleSheet("border-style: solid; border-width: 1px; border-color: black; background-color:white;");

    //painter = make_unique<QPainter>(this);

    resetHeightsMap();

    range = 24.75;
    smoothing = false;

    draw_alg = ZBUFFER_PARAM;
    mult = 1;
    scale_k = 16;

    red = 20;
    green = 150;
    blue = 20;

    my_img.reset();
    frame_buffer.reset();
    cleanQImage();

    threads_number = 8;
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

    heights_map->diamondSquare(range, smoothing); //DIAMOND SQUARE
    //heights_map->simpleGen(range, max(1, (size-1)/32)+1);

    //heights_map_points = heights_map->createPoints(SCALE/MULT, SCALE/MULT, SCALE/MULT);

    double max_h = heights_map->getMaxHeight();
    double k = min((0.9*img_height)/max_h, ((0.9*img_width)/heights_map->getSize()));
    heights_map_points = heights_map->createPoints(k/MULT, k/MULT, k/MULT);
    max_h *= k/MULT;

    //clock_t start = clock();
    tri_pol_mas = heights_map_points->createTriPolArray(red, green, blue);
    //clock_t end = clock();
    //double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "heights_map_points->createTriPolArray() time = " << seconds << " secs" << endl;


    Point c = heights_map_points->getCenter();
    //getCenter() IN THE MIDDLE
    heights_map_points->move(Point(-c.getX() + (img_width/(2*MULT)), -c.getY() + (img_height/(2*MULT)), -c.getZ()));
    heights_map_points->rotate(Point(0, 0, 180));

    //max_h/2 IN THE MIDDLE
    //heights_map_points->rotate(Point(0, 0, 180), Point(c.getX(), (max_h/2), c.getZ()));
    //heights_map_points->move(Point(-c.getX() + (img_width/(2*MULT)), -(max_h/2) + (img_height/(2*MULT)), -c.getZ()));


    //zbuffer_alg = make_unique<ZBufferAlg>(img_width/MULT, img_height/MULT);
    zbuffer_alg = make_unique<ZBufferAlg>(img_height/MULT, img_width/MULT); // fix width and height

    drawLandScape();

    update();
}

void Canvas::readFromFile(string file_name)
{
    cleanQImage();

    heights_map->readFromFile(file_name);
    double max_h = heights_map->getMaxHeight();
    double k = min((0.9*img_height)/max_h, ((0.9*img_width)/heights_map->getSize()));
    heights_map_points = heights_map->createPoints(k/MULT, k/MULT, k/MULT);
    max_h *= k/MULT;

    tri_pol_mas = heights_map_points->createTriPolArray(red, green, blue);


    Point c = heights_map_points->getCenter();
    //getCenter() IN THE MIDDLE
    //heights_map_points->move(Point(-c.getX() + (img_width/(2*MULT)), -c.getY() + (img_height/(2*MULT)), -c.getZ()));
    //heights_map_points->rotate(Point(0, 0, 180));

    //max_h/2 IN THE MIDDLE
    heights_map_points->rotate(Point(0, 0, 180), Point(c.getX(), (max_h/2), c.getZ()));
    heights_map_points->move(Point(-c.getX() + (img_width/(2*MULT)), -(max_h/2) + (img_height/(2*MULT)), -c.getZ()));


    zbuffer_alg = make_unique<ZBufferAlg>(img_height/MULT, img_width/MULT); // fix width and height

    drawLandScape();

    update();
}

void Canvas::writeToFile(string file_name)
{
    heights_map->writeToFile(file_name);
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
    heights_map_points = heights_map->createPoints(red, green, blue);
    tri_pol_mas = heights_map_points->createTriPolArray();
    //zbuffer_alg = make_unique<ZBufferAlg>(img_width/MULT, img_height/MULT); //(500, 500);
    zbuffer_alg = make_unique<ZBufferAlg>(img_height/MULT, img_width/MULT); //(500, 500);
}

void Canvas::updateResolution()
{
    setFixedSize(img_width+2, img_height+2);
    zbuffer_alg = make_unique<ZBufferAlg>(img_height/MULT, img_width/MULT);
    const Point& c = heights_map_points->getCenter();
    heights_map_points->transform(Point(-c.getX() + (img_width/(2*MULT)), -c.getY() + (img_height/(2*MULT)), -c.getZ()), Point(1, 1, 1), Point(0, 0, 0));
    drawLandScape();
    //update();
}

void Canvas::setWidth(int new_width)
{
    img_width = new_width;
}

void Canvas::setHeight(int new_height)
{
    img_height = new_height;
}

void Canvas::setScale(double new_scale)
{
    scale_k = new_scale;
}

void Canvas::setRange(float new_range)
{
    range = new_range;
}

void Canvas::setSmoothing(bool new_smoothing)
{
    smoothing = new_smoothing;
}

void Canvas::setDrawAlg(DrawAlg alg)
{
    draw_alg = alg;
    drawLandScape();
}

void Canvas::setMult(int new_mult)
{
    const Point& c = heights_map_points->getCenter();
    //heights_map_points->transform(Point(-c.getX() + (img_width/(2*new_mult)), -c.getY() + (img_height/(2*new_mult)), -c.getZ()), Point(1, 1, 1), Point(0, 0, 0));
    move(Point(-c.getX() + (img_width/(2*new_mult)), -c.getY() + (img_height/(2*new_mult)), -c.getZ()));
    //heights_map_points->transform(Point(0, 0, 0), Point(double(mult)/new_mult, double(mult)/new_mult, double(mult)/new_mult), Point(0, 0, 0));
    scale(Point(double(mult)/new_mult, double(mult)/new_mult, double(mult)/new_mult));
    mult = new_mult;
    zbuffer_alg = make_unique<ZBufferAlg>(img_height/MULT, img_width/MULT);
    drawLandScape();
}

void Canvas::setLandscapeColor(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
    tri_pol_mas->setColor(r, g, b);
    drawLandScape();
}

void Canvas::transform(const Point &move, const Point &scale, const Point &rotate)
{
    heights_map_points->transform(move, scale, rotate);
}

void Canvas::move(const Point &move)
{
    heights_map_points->move(move);
}

void Canvas::scale(const Point &scale)
{
    heights_map_points->scale(scale);
}

void Canvas::rotate(const Point &rotate)
{
    heights_map_points->rotate(rotate);
}

QColor Canvas::getColor()
{
    return QColor(red, green, blue);
}

void Canvas::setThreadsNumber(int n)
{
    threads_number = n;
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

        //heights_map_points->transform(Point(0, 0, 0), Point(1, 1, 1), Point(-y, -x, 0));
        rotate(Point(-y, -x, 0));

        cleanQImage();
        drawLandScape();
    }
    else if (RMB_is_pressed)
    {
        double x = double(previous_x - event->position().x()) / MOVE_SPEED;
        double y = double(previous_y - event->position().y()) / MOVE_SPEED;

        //heights_map_points->transform(Point(-x, -y, 0), Point(1, 1, 1), Point(0, 0, 0));
        move(Point(-x, -y, 0));

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

    //heights_map_points->transform(Point(0, 0, 0), Point(ky, ky, ky), Point(0, 0, 0));
    scale(Point(ky, ky, ky));

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

void Canvas::DrawLineBrezenheimFloat(const Point& p1, const Point& p2, QColor c)
{
    DrawLineBrezenheimFloat(p1.getX(), p1.getY(), p2.getX(), p2.getY(), c);
}

void Canvas::DrawLineBrezenheimFloat(double X_start, double Y_start, double X_end, double Y_end, QColor c)
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
    plotXImg(X, Y, c, MULT);
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
        plotXImg(X, Y, c, MULT);
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
    case ZBUFFER_INTERPOLATION:
        zbufferInterpolationDraw();
        break;
    case ZBUFFER_PARAM_THREADS:
        zbufferParamDrawWithThreads();
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
    //int HMPsize = heights_map_points->getSize();
    int HMPwidth = heights_map_points->getWidth();
    int HMPheights = heights_map_points->getHeight();
    for (int i = 0; i < HMPheights; i++)
        for (int j = 1; j < HMPwidth; j++)
        {
            shared_ptr<Point> tmp_point1 = (*heights_map_points)(i, j-1);

            shared_ptr<Point> tmp_point2 = (*heights_map_points)(i, j);

            DrawLineBrezenheimFloat(tmp_point1->getX(), tmp_point1->getY(), tmp_point2->getX(), tmp_point2->getY(), QColor(red, green, blue));
        }
    for (int i = 1; i < HMPheights; i++)
        for (int j = 0; j < HMPwidth; j++)
        {
            shared_ptr<Point> tmp_point1 = (*heights_map_points)(i-1, j);

            shared_ptr<Point> tmp_point2 = (*heights_map_points)(i, j);

            DrawLineBrezenheimFloat(tmp_point1->getX(), tmp_point1->getY(), tmp_point2->getX(), tmp_point2->getY(), QColor(red, green, blue));
        }
}

void Canvas::triangularDraw()
{
    //tri_pol_mas->updatePoints(*heights_map_points);
    for (auto &tri_pol : *tri_pol_mas)
    {
        DrawLineBrezenheimFloat(tri_pol.getP1(), tri_pol.getP2(), QColor(red, green, blue));
        DrawLineBrezenheimFloat(tri_pol.getP2(), tri_pol.getP3(), QColor(red, green, blue));
        DrawLineBrezenheimFloat(tri_pol.getP3(), tri_pol.getP1(), QColor(red, green, blue));
    }
}

void Canvas::drawImageFT(int i0, int i1)
{
    for (int i = i0; i <= i1; i++)
        for (int j = 0; j < frame_buffer->getWidth();  j++)
            plotXImg(i, j, (*frame_buffer)(i, j), MULT);
}

void Canvas::zbufferParamDraw()
{
    //UPDATE POINTS
    clock_t start = clock();
    //tri_pol_mas = heights_map3->createTriPolMas();
    //tri_pol_mas->updatePoints(*heights_map_points);
    tri_pol_mas->update();
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "tri_pol_mas->update() time = " << seconds << " secs" << endl;

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
            plotXImg(i, j, (*frame_buffer)(i, j), MULT);
            //double intensity = (*frame_buffer)(i, j);
            //plotXImg(i, j, QColor(red * intensity, green * intensity, blue * intensity), MULT);
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "paint time = " << seconds << " secs" << endl;
}

void Canvas::zbufferParamDrawWithThreads()
{
    //UPDATE POINTS
    clock_t start = clock();
    tri_pol_mas->update2(threads_number); //WITH THREADS
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "tri_pol_mas->update() time = " << seconds << " secs" << endl;

    //Z-BUFFER ALGORITHM
    start = clock();
    zbuffer_alg->executeWithThreads(*tri_pol_mas, threads_number); //WITH THREADS
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "zbuffer_alg->execute() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();
    //cout << *frame_buffer << endl;

    //PAINT
    start = clock();

    int threadsN = threads_number;
    int x[threadsN];
    int dx = frame_buffer->getHeight()/threadsN;
    x[0] = 0;
    for (int i = 1; i < threadsN; i++)
    {
        x[i] = x[i-1] + dx;
    }

    std::thread *th = new std::thread[threadsN];
    for (int i = 0; i < threadsN-1; i++)
    {
        th[i] = std::thread(&Canvas::drawImageFT, this, x[i], x[i+1]);
    }
    th[threadsN-1] = std::thread(&Canvas::drawImageFT, this, x[threadsN-1], frame_buffer->getHeight() - 1);

    for (int i = 0; i < threadsN; i++)
    {
        th[i].join();
    }
    delete[] th;

    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "paint time = " << seconds << " secs" << endl;
}

void Canvas::zbufferInterpolationDraw()
{
    //Z-BUFFER ALGORITHM
    clock_t start = clock();
    zbuffer_alg->execute2(*tri_pol_mas);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "zbuffer_alg->execute2() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();

    //PAINT
    start = clock();
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            plotXImg(i, j, (*frame_buffer)(i, j), MULT);
            //double intensity = (*frame_buffer)(i, j);
            //plotXImg(i, j, QColor(red * intensity, green * intensity, blue * intensity), MULT);
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "paint time = " << seconds << " secs" << endl;
}
