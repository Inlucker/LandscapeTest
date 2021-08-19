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
    diamondSquare(DS_RANGE, DS_LEVEL);
}

void HeightsMap::diamondSquare(float r, unsigned int l)
{
    resetHeightsmap();

    (*this)(0, 0) = 0;
    (*this)(0, size - 1) = 0;
    (*this)(size - 1, 0) = 0;
    (*this)(size - 1, size - 1) = 0;

    diamondSquare(0, 0, size-1, size-1, r, l);
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
            points_it = Point(double(i/size) * kx, double(*map_it) * ky, double(i % size) * kz); // x <-> z
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
    if (level < 1) return;

    // diamonds
    for (unsigned i = x1 + level; i < x2; i += level)
        for (unsigned j = y1 + level; j < y2; j += level)
        {
            float a = (*this)(i - level, j - level);
            float b = (*this)(i, j - level);
            float c = (*this)(i - level, j);
            float d = (*this)(i, j);
            float e = (*this)(i - level / 2, j - level / 2) = (a + b + c + d) / 4 + (getRnd() * range);
        }

    // squares
    for (unsigned i = x1 + 2 * level; i < x2; i += level)
        for (unsigned j = y1 + 2 * level; j < y2; j += level)
        {
            float a = (*this)(i - level, j - level);
            float b = (*this)(i, j - level);
            float c = (*this)(i - level, j);
            float d = (*this)(i, j);
            float e = (*this)(i - level / 2, j - level / 2);

            float f = (*this)(i - level, j - level / 2) = (a + c + e + (*this)(i - 3 * level / 2, j - level / 2)) / 4 + (getRnd() * range);
            float g = (*this)(i - level / 2, j - level) = (a + b + e + (*this)(i - level / 2, j - 3 * level / 2)) / 4 + (getRnd() * range);
        }

    diamondSquare(x1, y1, x2, y2, range / 2, level / 2);
}

double HeightsMap::getRnd() const noexcept
{
    return (double)rand() / RAND_MAX;
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
