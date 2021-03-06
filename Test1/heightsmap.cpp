#include "heightsmap.h"

#include <time.h>
#include <random>

#include "iterator.hpp"
#include "constiterator.hpp"
#include "errors.h"
#include "heightsmappoints.h"

HeightsMap::HeightsMap()
{
    size = 0;
    elems_num = 0;
    //alloc_data();
}

HeightsMap::HeightsMap(int new_size)
{
    time_t t_time = time(NULL);
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
        //elems_num = new_size;
        alloc_data();

        for (auto &elem:*this)
            elem = 0;
    }
}

bool HeightsMap::isEmpty() const noexcept
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
}

void HeightsMap::resetHeightsmap() noexcept
{
    for (auto &elem:*this)
        elem = 0;
}

void HeightsMap::randomizeHeightsMap() noexcept
{
    srand(time(NULL));
    for (auto &elem:*this)
        elem = (rand() % 100);
}

void HeightsMap::smoothHeightsMap() noexcept
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
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

            data_ptr[i*size+j] = tmp_sum / tmp_n;
            //cout  << ")/" << tmp_n << " = "<< tmp_sum << "/" << tmp_n << " = " << heights_map[i][j] << endl;
        }
}

double HeightsMap::getHeight(int i, int j)
{
    if (i >= 0 && i <= size && j >= 0 && j <= size)
    {
        return data_ptr[i*size+j];
    }
    else
        return -1;
}

void HeightsMap::diamondSquare()
{
    resetHeightsmap();

    (*this)(0, 0) = 0;
    (*this)(0, size - 1) = 0;
    (*this)(size - 1, 0) = 0;
    (*this)(size - 1, size - 1) = 0;

    DiamondSquare3(0, 0, size-1, size-1, RANGE, LEVEL);
}

void HeightsMap::diamondSquare1()
{
    resetHeightsmap();

    srand(time(0));
    (*this)(0, 0) = RAND;
    (*this)(0, size - 1) = RAND;
    (*this)(size - 1, 0) = RAND;
    (*this)(size - 1, size - 1) = RAND;
    diamondSquare(0, size - 1, 0, size - 1);
}

//#define START_VALUE dRand(0, 20)
#define START_VALUE 100

void HeightsMap::diamondSquare2()
{
    resetHeightsmap();

    (*this)(0, 0) = START_VALUE;
    (*this)(0, size - 1) = START_VALUE;
    (*this)(size - 1, 0) = START_VALUE;
    (*this)(size - 1, size - 1) = START_VALUE;
    //cout << (*this) << endl;

    srand(time(NULL));

    //roughness = dRand(0, 1);
    range = 5;
    //cout << "roughness = " << roughness << endl;
    //i = 1;
    for (int sideLength = size-1; sideLength >= 2; sideLength /= 2, range/2)
    {
        int halfSide = sideLength/2;

        squareStep(sideLength, halfSide);
        diamondStep(sideLength, halfSide);
    }
}

shared_ptr<HeightsMapPoints> HeightsMap::createPoints(int kx, int ky, int kz)
{
    shared_ptr<HeightsMapPoints> new_points_map = make_shared<HeightsMapPoints>(size);
    ConstIterator<height_t> map_it = this->cbegin();
    int i = 0;
    for (auto& points_it : *new_points_map)
    {
        points_it = Point((i/size) * kx, (*map_it) * ky, (i % size) * kz); // x <-> z
        map_it++;
        i++;
    }
    new_points_map->updateCenter();
    return new_points_map;
}

shared_ptr<HeightsMapPoints> HeightsMap::createPoints()
{
    return createPoints(1, 1, 1);
}

height_t& HeightsMap::getElem(int id)
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
}

void HeightsMap::diamondSquare(int left_x, int right_x, int bot_y, int top_y)
{
    //int mid = round(double(right_x - left_x) / 2);
    int mid = (right_x - left_x) / 2;
    if (mid > 0)
    {
        /*cout << "left_x = " << left_x << endl;
        cout << "right_x = " << right_x << endl;
        cout << "bot_y = " << bot_y << endl;
        cout << "top_y = " << top_y << endl;
        cout << "mid = " << mid << endl;
        cout << endl;*/

        diamond(left_x, bot_y, right_x, top_y);

        square(left_x, bot_y + mid, mid);
        square(left_x + mid, top_y, mid);
        square(right_x, bot_y + mid, mid);
        square(left_x + mid, bot_y, mid);

        diamondSquare(left_x, mid, bot_y, mid);
        diamondSquare(left_x + mid, right_x, bot_y, mid);
        diamondSquare(left_x, right_x - mid, bot_y + mid, top_y);
        diamondSquare(left_x + mid, right_x, bot_y + mid, top_y);
    }
}

void HeightsMap::diamond(int left_x, int bot_y, int right_x, int top_y)
{
    srand(time(0));
    int mid_x = (left_x + right_x) / 2;
    int mid_y = (bot_y + top_y) / 2;

    height_t a = (*this)(left_x, bot_y);
    height_t b = (*this)(left_x, top_y);
    height_t c = (*this)(right_x, top_y);
    height_t d = (*this)(right_x, bot_y);

    //(*this)(mid_x, mid_y) = (a + b + c + d) / 4; //+random
    //(*this)(mid_x, mid_y) = (a + b + c + d) / 4 + (rand() % 3 - 1);
    (*this)(mid_x, mid_y) = (a + b + c + d) / 4 + RAND;
}

void HeightsMap::square(int x, int y, int l)
{
    srand(time(0));
    height_t a = 0;
    height_t b = 0;
    height_t c = 0;
    height_t d = 0;

    if (y - l >= 0)
        a = (*this)(x, y - l);

    if (x - l >= 0)
        b = (*this)(x - l, y);

    if (y + l <= 0)
        c = (*this)(x, y + l);

    if (x + l <= 0)
        d = (*this)(x + l, y);

    //(*this)(x, y) = (a + b + c + d) / 4; //+random
    //(*this)(x, y) = (a + b + c + d) / 4 + (rand() % 3 - 1);
    (*this)(x, y) = (a + b + c + d) / 4 + RAND;
}

void HeightsMap::squareStep(int sideLength, int halfSide)
{
    for (int x = 0; x < size-1; x += sideLength)
    {
        for (int y = 0; y < size-1; y += sideLength)
        {
            //double avg = map[x][y] + map[x+sideLength][y] + map[x][y+sideLength] + map[x+sideLength][y+sideLength];
            double avg = (*this)(x, y) +
                         (*this)(x+sideLength, y) +
                         (*this)(x, y+sideLength) +
                         (*this)(x+sideLength, y+sideLength);
            avg /= 4.0;
            (*this)(x+halfSide, y+halfSide) = avg + dRand(-range, range);
            //+ RAND;//dRand(-range, range);

            //cout << (*this) << endl;
        }
    }
}

void HeightsMap::diamondStep(int sideLength, int halfSide)
{
    for (int x = 0; x < size-1; x += halfSide)
    {
        for (int y = (x+halfSide)%sideLength; y < size -1; y +=sideLength)
        {
            double avg = (*this)((x-halfSide+size-1)%(size-1), y) +
                (*this)((x+halfSide)%(size-1), y) +
                (*this)(x, (y+halfSide)%(size-1)) +
                (*this)(x, (y-halfSide+size-1)%(size-1));
            avg /= 4.0;
            (*this)(x, y) = avg + dRand(-range, range);
            //+ RAND;//dRand(-range, range);

            if (x == 0)
                (*this)(size-1, y) = avg;
            if (y == 0)
                (*this)(x, size-1) = avg;

            //cout << (*this) << endl;
        }
    }
}

double HeightsMap::dRand(double d_min, double d_max)
{
    double d = (double)rand() / RAND_MAX;
    return d_min + d * (d_max - d_min);
}

//ToFigureOut and Understand how it works
void HeightsMap::DiamondSquare3(unsigned x1, unsigned y1, unsigned x2, unsigned y2, float range, unsigned level)
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
            float e = (*this)(i - level / 2, j - level / 2) = (a + b + c + d) / 4 + (GetRnd() * range);
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

            float f = (*this)(i - level, j - level / 2) = (a + c + e + (*this)(i - 3 * level / 2, j - level / 2)) / 4 + (GetRnd() * range);
            float g = (*this)(i - level / 2, j - level) = (a + b + e + (*this)(i - level / 2, j - 3 * level / 2)) / 4 + (GetRnd() * range);
        }

    DiamondSquare3(x1, y1, x2, y2, range / 2, level / 2);
}

double HeightsMap::GetRnd() const noexcept
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
