#include "zbuffer.h"

#include "iterator.hpp"
#include "constiterator.hpp"
#include "errors.h"
#include "tripolmas.h"
#include "triangularpolygon.h"

ZBuffer::ZBuffer()
{
    width = 0;
    height = 0;
    elems_num = 0;
    data_ptr.reset();
}

ZBuffer::ZBuffer(int new_width, int new_height)
{
    time_t t_time = time(NULL);
    if (new_width < 0 || new_height < 0)
        throw ZBufferNegativeSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_width == 0 || new_width == 0)
    {
        width = 0;
        height = 0;
        elems_num = 0;
        data_ptr.reset();
    }
    else
    {
        width = new_width;
        height = new_height;
        elems_num = width * height;
        alloc_data();

        for (auto &elem:*this)
            elem = -100000;
    }
}

/*ZBuffer::ZBuffer(TriPolMas mas)
{
    //HERE

}*/

bool ZBuffer::isEmpty() const noexcept
{
    return !elems_num;
}

int ZBuffer::size() const noexcept
{
    return elems_num;
}

bool ZBuffer::getWidth() const noexcept
{
    return width;
}

int ZBuffer::getHeight() const noexcept
{
    return height;
}

Iterator<double> ZBuffer::begin() noexcept
{
    return Iterator<double>(data_ptr, elems_num, 0);
}

Iterator<double> ZBuffer::end() noexcept
{
    return Iterator<double>(data_ptr, elems_num, elems_num);
}

ConstIterator<double> ZBuffer::cbegin() const noexcept
{
    return ConstIterator<double>(data_ptr, elems_num, 0);
}

ConstIterator<double> ZBuffer::cend() const noexcept
{
    return ConstIterator<double>(data_ptr, elems_num, elems_num);
}

double &ZBuffer::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw ZBufferIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

const double &ZBuffer::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw ZBufferIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

double &ZBuffer::operator [](int id)
{
    return getElem(id);
}

const double &ZBuffer::operator [](int id) const
{
    return getElem(id);
}

double &ZBuffer::getElem(int i, int j)
{
    return getElem(i*width+j);
}

const double &ZBuffer::getElem(int i, int j) const
{
    return getElem(i*width+j);
}

double &ZBuffer::operator()(int i, int j)
{
    return getElem(i*width+j);
}

const double &ZBuffer::operator()(const int &i, const int &j) const
{
    return getElem(i*width+j);
}

void ZBuffer::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<double[]> new_ptr(new double[elems_num]);
        //shared_ptr<HeightsArray[]> new_ptr(new HeightsArray[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw ZBufferAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}
