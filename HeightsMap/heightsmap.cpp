#include "heightsmap.h"

#include <time.h>
#include <random>

#include "errors.h"
//#include "heightsarray.h"

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

double HeightsMap::getHeight(int i, int j)
{
    if (i >= 0 && i <= size && j >= 0 && j <= size)
    {
        return data_ptr[i*size+j];
    }
    else
        return -1;
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
}*/

/*shared_ptr<HeightsArray> HeightsMap::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw HeightsMapIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return make_shared<HeightsArray>(*this, id);
}

shared_ptr<HeightsArray> HeightsMap::operator [](int id)
{
    return getElem(id);
}*/

shared_ptr<height_t[]> HeightsMap::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= size)
        throw HeightsMapIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    shared_ptr<height_t[]> height_arr(new height_t[elems_num]);

    int j = 0;
    int i = 0;
    for (auto& elem : *this)
    {
        if (i/size == id)
        {
            height_arr[j] = elem;
            j++;
        }
        i++;
    }

    return height_arr;
}

const shared_ptr<height_t[]> HeightsMap::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= size)
        throw HeightsMapIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    shared_ptr<height_t[]> height_arr(new height_t[elems_num]);

    int j = 0;
    int i = 0;
    for (ConstIterator<height_t> It = this->cbegin(); It != this->cend(); ++It)
    {
        if (i/size == id)
        {
            height_arr[j] = *It;
            j++;
        }
        i++;
    }

    return height_arr;
    //return getElem(id);
}

shared_ptr<height_t[]> HeightsMap::operator [](int id)
{
    return getElem(id);
}

const shared_ptr<height_t[]> HeightsMap::operator [](int id) const
{
    return getElem(id);
}

void HeightsMap::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<height_t[]> new_ptr(new height_t[elems_num]);
        //shared_ptr<HeightsArray[]> new_ptr(new HeightsArray[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw HeightsMapAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
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

    /*ConstIterator<HeightsArray> map_it = map.cbegin();
    cout << endl;
    for (; map_it != map.cend(); map_it++)
    {
        //ConstIterator<height_t> arr_it = map_it->cbegin();
        cout << *map_it;
    }
    cout << endl;*/

    return os;
}
