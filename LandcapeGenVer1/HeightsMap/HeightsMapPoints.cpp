#include "HeightsMapPoints.h"

#include "Iterator/Iterator.hpp"
#include "Iterator/ConstIterator.hpp"
#include "Errors/HeightsMapPointsErrors.h"
#include "Triangles/TriPolArray.h"
#include "Triangles/TriangularPolygon.h"

HeightsMapPoints::HeightsMapPoints()
{
    map_points_center = Point();
}

HeightsMapPoints::HeightsMapPoints(int new_width, int new_height) : BaseType(new_width, new_height)
{
}

HeightsMapPoints::HeightsMapPoints(int new_size) : BaseType(new_size)//BaseMtrx<Point>(new_size)
{
}

shared_ptr<TriPolArray> HeightsMapPoints::createTriPolArray()
{
    shared_ptr<TriPolArray> new_tri_pol_mas = make_shared<TriPolArray>((size-1)*2*(size-1));
    Iterator<TriangularPolygon> mas_it = new_tri_pol_mas->begin();
    for (int i = 0; i < (size-1); i++)
    {
        for (int j = 0; j < (size-1); j++)
        {
            if ((j+i) % 2 == 1)
            {
                *mas_it = TriangularPolygon((*this)(i, j), (*this)(i, j+1), (*this)(i+1, j));
                mas_it++;
                *mas_it = TriangularPolygon((*this)(i+1, j), (*this)(i, j+1), (*this)(i+1, j+1));
                mas_it++;
            }
            else
            {
                *mas_it = TriangularPolygon((*this)(i, j), (*this)(i+1, j+1), (*this)(i, j+1));
                mas_it++;
                *mas_it = TriangularPolygon((*this)(i, j), (*this)(i+1, j), (*this)(i+1, j+1));
                mas_it++;
            }
        }
    }

    return new_tri_pol_mas;
}

shared_ptr<TriPolArray> HeightsMapPoints::createTriPolArray(int r, int g, int b)
{
    //shared_ptr<TriPolArray> new_tri_pol_mas = make_shared<TriPolArray>((size-1)*2*(size-1), r , g, b);
    shared_ptr<TriPolArray> new_tri_pol_mas = make_shared<TriPolArray>((width-1)*2*(height-1), r , g, b);
    Iterator<TriangularPolygon> mas_it = new_tri_pol_mas->begin();
    for (int i = 0; i < (height-1); i++)
    {
        for (int j = 0; j < (width-1); j++)
        {
            if ((j+i) % 2 == 1)
            {
                *mas_it = TriangularPolygon((*this)(i, j), (*this)(i, j+1), (*this)(i+1, j));
                mas_it++;
                *mas_it = TriangularPolygon((*this)(i+1, j), (*this)(i, j+1), (*this)(i+1, j+1));
                mas_it++;
            }
            else
            {
                *mas_it = TriangularPolygon((*this)(i, j), (*this)(i+1, j+1), (*this)(i, j+1));
                mas_it++;
                *mas_it = TriangularPolygon((*this)(i, j), (*this)(i+1, j), (*this)(i+1, j+1));
                mas_it++;
            }
        }
    }

    return new_tri_pol_mas;
}

void HeightsMapPoints::transform(const Point& moveK, const Point& scaleK, const Point& rotateK)
{
    if (!isEmpty())
    {
        //clock_t start = clock();

        for (auto& point : *this)
        {
            point->transform(moveK, scaleK, rotateK, map_points_center);
        }
        updateCenter();

        //clock_t end = clock();
        //double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        //cout << "HeightsMapPoints::transform() time = " << seconds << " secs" << endl;
    }
    else
    {
        //add error (exception)
    }
}

void HeightsMapPoints::move(const Point &moveK)
{
    if (!isEmpty())
    {
        for (auto& point : *this)
            point->move(moveK);
        updateCenter();
    }
    else
    {
        //add error (exception)
    }
}

void HeightsMapPoints::scale(const Point &scaleK)
{
    if (!isEmpty())
    {
        for (auto& point : *this)
            point->scale(scaleK, map_points_center);
        updateCenter();
    }
    else
    {
        //add error (exception)
    }
}

void HeightsMapPoints::rotate(const Point &rotateK)
{
    if (!isEmpty())
    {
        for (auto& point : *this)
            point->rotate(rotateK, map_points_center);
        updateCenter();
    }
    else
    {
        //add error (exception)
    }
}

void HeightsMapPoints::rotate(const Point &rotateK, const Point &rotate_center)
{
    if (!isEmpty())
    {
        for (auto& point : *this)
            point->rotate(rotateK, rotate_center);
        updateCenter();
    }
    else
    {
        //add error (exception)
    }
}

const Point &HeightsMapPoints::getCenter() const
{
    return map_points_center;
}

void HeightsMapPoints::updateCenter() noexcept
{
    int i = 0;
    Point rez(0, 0, 0);
    for (auto point : *this)
    {
        rez.setX(rez.getX() + point->getX());
        rez.setY(rez.getY() + point->getY());
        rez.setZ(rez.getZ() + point->getZ());
        i++;
    }
    rez.setX(rez.getX()/i);
    rez.setY(rez.getY()/i);
    rez.setZ(rez.getZ()/i);
    map_points_center = rez;
}

ostream& operator <<(ostream& os, const HeightsMapPoints& points_map)
{
    if (points_map.isEmpty())
    {
        os << "HeightsMapPoints is empty.";
        return os;
    }

    ConstIterator<shared_ptr<Point>> It = points_map.cbegin();
    while (It != points_map.cend())
    {
        os << '\n' << '[' << **It++;
        for (int i = 1; i < points_map.getSize() && It != points_map.cend(); It++, i++)
            os << "; " << **It ;
        os << ']';
    }
    os << endl;
    os << "Center = " << points_map.map_points_center << endl;

    return os;
}
