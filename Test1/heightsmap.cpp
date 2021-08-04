#include "heightsmap.h"

#include <time.h>
#include <random>

#include "errors.h"
//#include "heightsarray.h"
#include "heightsmappoints.h"

#define RAND (rand() % 10)

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
        throw NegativeMapSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

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

void HeightsMap::resetHeightsmap()
{
    for (auto &elem:*this)
        elem = 0;
}

void HeightsMap::randomizeHeightsMap()
{
    srand(time(0));
    for (auto &elem:*this)
        elem = (rand() % 16);
}

void HeightsMap::smoothHeightsMap()
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

void HeightsMap::diamondSquare()
{
    resetHeightsmap();
    srand(time(0));
    (*this)(0, 0) = RAND;
    (*this)(0, size - 1) = RAND;
    (*this)(size - 1, 0) = RAND;
    (*this)(size - 1, size - 1) = RAND;
    diamondSquare(0, size - 1, 0, size - 1);
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
