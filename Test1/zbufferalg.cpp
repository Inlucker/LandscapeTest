#include "zbufferalg.h"

//#include "zbuffer.h"
//#include "framebuffer.h"
#include "tripolmas.h"
#include "triangularpolygon.h"

#include <math.h>

ZBufferAlg::ZBufferAlg(int new_width, int new_height)
{
    zbuffer = make_shared<ZBuffer>(new_width, new_height);
    frame_buffer = make_shared<FrameBuffer>(new_width, new_height);
    width = new_width;
    height = new_height;
}

void ZBufferAlg::execute(TriPolMas &mas)
{
    zbuffer = make_shared<ZBuffer>(width, height); //make reset
    frame_buffer = make_shared<FrameBuffer>(width, height); //make reset
    for (auto& elem : mas)
    {
        for (int i = max(elem.getMinX(), 0.); i < min(elem.getMaxX(), double(height)); i++)
        {
            for (int j = max(elem.getMinY(), 0.); j < min(elem.getMaxY(), double(width)); j++)
            {
                    if (elem.isInTriangle(i, j))
                    {
                        if ((*zbuffer)(i, j) < elem.getZ(i, j))
                        {
                            (*zbuffer)(i, j) = elem.getZ(i, j);
                            (*frame_buffer)(i, j) = elem.getColor();//elem.getColor(x, y);
                        }
                    }
            }
        }
    }
    //cout << *frame_buffer << endl;
    //cout << *zbuffer << endl;

}

void ZBufferAlg::execute2(TriPolMas &mas)
{
    //HERE
    zbuffer = make_shared<ZBuffer>(width, height); //make reset
    frame_buffer = make_shared<FrameBuffer>(width, height); //make reset
    for (auto& elem : mas)
    {
        Point &p1 = elem.getP1();
        Point &p2 = elem.getP2();
        Point &p3 = elem.getP3();

        //Сортировка точек так, что y0 <= y1 <= y2
        if (p2.getY() < p1.getY())
            swap(p2, p1);
        if (p3.getY() < p1.getY())
            swap(p3, p1);
        if (p3.getY() < p2.getY())
            swap(p3, p2);

        int x0 = p1.getX(), x1 = p2.getX(), x2 = p3.getX();
        int y0 = p1.getY(), y1 = p2.getY(), y2 = p3.getY();
        int z0 = p1.getZ(), z1 = p2.getZ(), z2 = p3.getZ();

        //Вычисление координат x и значений h для рёбер треугольника
        vector<double> x01 = interpolate(y0, x0, y1, x1);
        vector<double> z01 = interpolate(y0, z0, y1, z1);

        x01.pop_back();
        vector<double> &x012 = x01;
        addInterpolate(x012, y1, x1, y2, x2); //vector<double> x12 = interpolate(y1, x1, y2, x2);
        z01.pop_back();
        vector<double> &z012 = z01;
        addInterpolate(z012, y1, z1, y2, z2); //vector<double> z12 = interpolate(y1, z1, y2, z2);

        vector<double> x02 = interpolate(y0, x0, y2, x2);
        vector<double> z02 = interpolate(y0, z0, y2, z2);

        //Конкатенация коротких сторон ^
        /*x01.pop_back();
        x012 = x01 + x12;

        z01.pop_back();
        z012 = z01 + z12;*/

        //Определяем, какая из сторон левая и правая
        size_t m = x012.size()/2;

        vector<double> &x_left = x02;
        vector<double> &x_right = x012;

        vector<double> &z_left = z02;
        vector<double> &z_right = z012;

        if (x02[m] < x012[m])
        {
            /*vector<double> &x_left = x02;
            vector<double> &x_right = x012;

            vector<double> &z_left = z02;
            vector<double> &z_right = z012;*/
        }
        else
        {
            x_left = x012;
            x_right = x02;

            z_left = z012;
            z_right = z02;
        }

        //Отрисовка горизонтальных отрезков
        for (int y = max(y0, 0); y < min(y2, width); y++)
        {
            double x_l = min(x_left[y - y0], double(height)); //x_left[y - y0];
            double x_r = min(x_right[y - y0], double(height)); //x_right[y - y0];


            vector<double> z_segment = interpolate(x_l, z_left[y - y0], x_r, z_right[y - y0]);
            for (int x = max(x_l, 0.); x < x_r; x++)
            {
                double z = z_segment[x - x_l];
                if ((*zbuffer)(x, y) < z)
                {
                    (*zbuffer)(x, y) = z;
                    (*frame_buffer)(x, y) = elem.getColor();
                }
            }
        }
    }

}

shared_ptr<FrameBuffer> ZBufferAlg::getFrameBuffer() const noexcept
{
    return frame_buffer;
}

//use Vector?
vector<double> ZBufferAlg::interpolate(double i0, double d0, double i1, double d1) const
{
    vector<double> values;
    if (i0 == i1)
    {
       values.push_back(d0);
       return values;
    }
    double a = (d1 - d0) / (i1 - i0);
    double d = d0;
    for (int i = i0; i <= i1; i++)
    {
        values.push_back(d);
        d = d + a;
    }
    return values;
}

void ZBufferAlg::addInterpolate(vector<double> &values, double i0, double d0, double i1, double d1) const
{
    if (i0 == i1)
    {
       values.push_back(d0);
       return;
    }
    double a = (d1 - d0) / (i1 - i0);
    double d = d0;
    for (int i = i0; i <= i1; i++)
    {
        values.push_back(d);
        d = d + a;
    }
}
