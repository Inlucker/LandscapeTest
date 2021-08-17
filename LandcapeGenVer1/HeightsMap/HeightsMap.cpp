#include "HeightsMap.h"

#include <time.h>
#include <random>

#include "Iterator/Iterator.hpp"
#include "Iterator/ConstIterator.hpp"
#include "Errors/HeightsMapErrors.h"
#include "HeightsMapPoints.h"

HeightsMap::HeightsMap()
{
    /*size = 0;
    elems_num = 0;
    data_ptr.reset();*/
}

HeightsMap::HeightsMap(int new_size) : BaseType(new_size)//BaseMtrx<height_t>(new_size)
{
    /*time_t t_time = time(NULL);
    if (new_size < 0)
        throw HeightsMapNegativeSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_size == 0)
    {
        size = 0;
        elems_num = 0;
        data_ptr.reset();
    }
    else
    {
        size = new_size;
        elems_num = size*size;
        alloc_data();

        for (auto &elem:*this)
            elem = 0;
    }*/
}

/*bool HeightsMap::isEmpty() const noexcept
{
    return !elems_num;
}

int HeightsMap::getSize() const noexcept
{
    return size;
}

int HeightsMap::elemsNum() const noexcept
{
    return elems_num;
}

Iterator<height_t> HeightsMap::begin() noexcept
{
    return Iterator<height_t>(data_ptr, elems_num, 0);
}

Iterator<height_t> HeightsMap::end() noexcept
{
    return Iterator<height_t>(data_ptr, elems_num, elems_num);
}

ConstIterator<height_t> HeightsMap::cbegin() const noexcept
{
    return ConstIterator<height_t>(data_ptr, elems_num, 0);
}

ConstIterator<height_t> HeightsMap::cend() const noexcept
{
    return ConstIterator<height_t>(data_ptr, elems_num, elems_num);
}*/

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

shared_ptr<HeightsMapPoints> HeightsMap::createPoints(int kx, int ky, int kz)
{
    shared_ptr<HeightsMapPoints> new_points_map = make_shared<HeightsMapPoints>(size);
    if (size > 0)
    {
        ConstIterator<height_t> map_it = this->cbegin();
        int i = 0;
        for (auto& points_it : *new_points_map)
        {
            points_it = Point((i/size) * kx, (*map_it) * ky, (i % size) * kz); // x <-> z
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

/*height_t& HeightsMap::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw HeightsMapIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

const height_t& HeightsMap::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw HeightsMapIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

height_t& HeightsMap::operator [](int id)
{
    return getElem(id);
}

const height_t& HeightsMap::operator [](int id) const
{
    return getElem(id);
}

height_t &HeightsMap::operator()(int i, int j)
{
    return getElem(i*size+j);
}

const height_t &HeightsMap::operator()(const int &i, const int &j) const
{
    return getElem(i*size+j);
}

void HeightsMap::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<height_t[]> new_ptr(new height_t[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw HeightsMapAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}*/

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
