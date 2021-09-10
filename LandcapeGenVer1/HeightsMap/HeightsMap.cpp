#include "HeightsMap.h"

#include <time.h>
#include <random>

#include "Iterator/Iterator.hpp"
#include "Iterator/ConstIterator.hpp"
#include "Errors/HeightsMapErrors.h"
#include "HeightsMapPoints.h"

HeightsMap::HeightsMap()
{

}

HeightsMap::HeightsMap(int new_size) : BaseType(new_size)
{

}

void HeightsMap::resetHeightsmap() noexcept
{
    for (auto &elem:*this)
        elem = 0;
}

void HeightsMap::diamondSquare()
{
    diamondSquare(DS_RANGE);
}

void HeightsMap::diamondSquare(float r)
{
    resetHeightsmap();

    (*this)(0, 0) = 0;
    (*this)(0, size - 1) = 0;
    (*this)(size - 1, 0) = 0;
    (*this)(size - 1, size - 1) = 0;

    /*(*this)(0, 0) = (getRnd() * r);
    (*this)(0, size - 1) = (getRnd() * r);
    (*this)(size - 1, 0) = (getRnd() * r);
    (*this)(size - 1, size - 1) = (getRnd() * r);*/

    diamondSquare(0, 0, size-1, size-1, r, size-1); // size-1 || size
}

void HeightsMap::simpleGen(int r, int n)
{
    cout << n << endl;
    randomizeHeightsMap(1, 1, height-2, width-2, r);
    smoothHeightsMap(1, 1, height-1, width-1, n);
}

shared_ptr<HeightsMapPoints> HeightsMap::createPoints(double kx, double ky, double kz)
{
    shared_ptr<HeightsMapPoints> new_points_map = make_shared<HeightsMapPoints>(size);
    if (size > 0)
    {
        ConstIterator<height_t> map_it = this->cbegin();
        int i = 0;
        for (auto& points_it : *new_points_map)
        {
            points_it = make_shared<Point>(double(i/size) * kx, double(*map_it) * ky, double(i % size) * kz); // убрать создание объекта Point// x <-> z
            map_it++;
            i++;
        }
        new_points_map->updateCenter();
    }
    return new_points_map;
}

shared_ptr<HeightsMapPoints> HeightsMap::createPoints()
{
    return createPoints(1, 1, 1);
}

//ToFigureOut and Understand how it works
void HeightsMap::diamondSquare(unsigned x1, unsigned y1, unsigned x2, unsigned y2, float range, unsigned level)
{
    if (level < 1)
    {
        //cout << *this << endl;
        return;
    }

    //cout << "Range = " << range << endl;
    //cout << "Level = " << level << endl;

    // diamonds
    for (unsigned i = x1 + level; i < x2; i += level)
        for (unsigned j = y1 + level; j < y2; j += level)
        {
            float a = (*this)(i - level, j - level);
            //cout << "a = (" << i - level << ", " << j - level << ") = " << a << endl;
            float b = (*this)(i, j - level);
            //cout << "b = (" << i << ", " << j - level << ") = " << b << endl;
            float c = (*this)(i - level, j);
            //cout << "c = (" << i - level << ", " << j << ") = " << c << endl;
            float d = (*this)(i, j);
            //cout << "d = (" << i << ", " << j << ") = " << d << endl;
            float e = (*this)(i - level / 2, j - level / 2) = (a + b + c + d) / 4 + (getRnd() * range);
            //cout << "e = (" << i - level/2 << ", " << j - level/2 << ") = " << e << endl;
            //cout << *this << endl;
        }

    //cout << *this << endl;

    // squares
    for (unsigned i = x1 + 2 * level; i < x2; i += level)
        for (unsigned j = y1 + 2 * level; j < y2; j += level)
        {
            float a = (*this)(i - level, j - level);
            //cout << "a = (" << i - level << ", " << j - level << ") = " << a << endl;
            float b = (*this)(i, j - level);
            //cout << "b = (" << i << ", " << j - level << ") = " << b << endl;
            float c = (*this)(i - level, j);
            //cout << "c = (" << i - level << ", " << j << ") = " << c << endl;
            //float d = (*this)(i, j);
            float e = (*this)(i - level / 2, j - level / 2);
            //cout << "e = (" << i - level/2 << ", " << j - level/2 << ") = " << e << endl;


            //cout << "?1 = (" << i - 3 * level / 2 << ", " << j - level / 2 << ") = " << (*this)(i - 3 * level / 2, j - level / 2) << endl;
            float f = (*this)(i - level, j - level / 2) = (a + c + e + (*this)(i - 3 * level / 2, j - level / 2)) / 4 + (getRnd() * range);
            //cout << "f = (" << i - level << ", " << j - level/2 << ") = " << f << endl;
            //cout << *this << endl;
            //cout << "?2 = (" << i - 3 * level / 2 << ", " << j - level / 2 << ") = " << (*this)(i - 3 * level / 2, j - level / 2) << endl;
            float g = (*this)(i - level / 2, j - level) = (a + b + e + (*this)(i - level / 2, j - 3 * level / 2)) / 4 + (getRnd() * range);
            //cout << "g = (" << i - level/2 << ", " << j - level << ") = " << g << endl;
            //cout << *this << endl;
        }

    //cout << *this << endl;

    diamondSquare(x1, y1, x2, y2, range / 2, level / 2);
}

void HeightsMap::diamondSquare2(int x1, int y1, int x2, int y2, float range, unsigned level)
{
    if (level < 1)
    {
        //cout << *this << endl;
        return;
    }

    int half_level = level/2;

    // diamonds
    for (int x = x1; x < x2; x += level)
        for (int y = y1; y < y2; y += level)
        {
            float a = (*this)(x, y);
            float b = (*this)(x + level, y);
            float c = (*this)(x, y + level);
            float d = (*this)(x + level, y + level);


            if (x + half_level == x1 || x + half_level == x2|| y + half_level == y1 || y + half_level == y2)
                float e = (*this)(x + half_level, y + half_level) = 0;
            else
                float e = (*this)(x + half_level, y + half_level) = (a + b + c + d) / 4 + (getRnd() * range);

            //cout << *this << endl;
        }

    // squares
    bool flag = false;
    for (int x = 0; x <= x2-x1; x += max(half_level, 1))
    {
        flag = !flag;
        for (int y = y1; y <= y2; y += level)
        {
            if (flag && y == y1)
                y += half_level;

            float f = 0;
            float g = 0;
            float h = 0;
            float i = 0;

            if (x - half_level >= x1 && y - half_level >= y1 && x + half_level <= x2 && y + half_level <= y2)
            {
                f = (*this)(x - half_level, y);
                g = (*this)(x, y - half_level);
                h = (*this)(x + half_level, y);
                i = (*this)(x, y + half_level);
            }

            if (x == x1 || x == x2|| y == y1 || y == y2)
                float e = (*this)(x, y) = 0;
            else
                float e = (*this)(x, y) = (f + g + h + i) / 4 + (getRnd() * range);

            //cout << *this << endl;
        }
    }

    diamondSquare2(x1, y1, x2, y2, range / 2, level / 2);
}

double HeightsMap::getRnd() const noexcept
{
    return (double)rand() / RAND_MAX;
}

void HeightsMap::randomizeHeightsMap(int x1, int y1, int x2, int y2, int n) noexcept
{
    srand(time(0));
    for (int i = y1; i <= y2; i++)
        for (int j = x1; j <= x2; j++)
            (*this)(i, j) = (rand() % n);
}

void HeightsMap::smoothHeightsMap(int x1, int y1, int x2, int y2, int n) noexcept
{
    for (int k = 0; k < n; k++)
        for (int i = y1; i < y2; i++)
            for (int j = x1; j < x2; j++)
            {
                double tmp_sum = 0;
                int tmp_n = 0;

                //cout << "(";
                double tmp = getValue(i-1, j-1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i-1, j);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i-1, j+1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i, j-1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i, j);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i, j+1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i+1, j-1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i+1, j);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                tmp = getValue(i+1, j+1);
                if (tmp >= 0)
                {
                    tmp_sum += tmp;
                    tmp_n++;
                }

                data_ptr[i*size+j] = tmp_sum / tmp_n;
                //cout  << ")/" << tmp_n << " = "<< tmp_sum << "/" << tmp_n << " = " << heights_map[i][j] << endl;
            }
}

double HeightsMap::getValue(int i, int j)
{
    if (i >= 0 && i <= size && j >= 0 && j <= size)
    {
        return data_ptr[i*size+j];
    }
    else
        return -1;
}

ostream& operator <<(ostream& os, const HeightsMap& map)
{
    if (map.isEmpty())
    {
        os << "HeightsMap is empty.";
        return os;
    }

    ConstIterator<height_t> It = map.cbegin();
    while (It != map.cend())
    {
        os << '\n' << '[' << *It++;
        for (int i = 1; i < map.getSize() && It != map.cend(); It++, i++)
            os << "; " << *It ;
        os << ']';
    }
    cout << endl;

    return os;
}
