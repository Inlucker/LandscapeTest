#include "framebuffer.h"

#include "iterator.hpp"
#include "constiterator.hpp"
#include "errors.h"

FrameBuffer::FrameBuffer()
{
    width = 0;
    height = 0;
    elems_num = 0;
}

FrameBuffer::FrameBuffer(int new_width, int new_height)
{
    time_t t_time = time(NULL);
    if (new_width < 0 || new_height < 0)
        throw FrameBufferNegativeSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

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
            elem = Qt::white;
    }
}

bool FrameBuffer::isEmpty() const noexcept
{
    return !elems_num;
}

int FrameBuffer::size() const noexcept
{
    return elems_num;
}

int FrameBuffer::getWidth() const noexcept
{
    return width;
}

int FrameBuffer::getHeight() const noexcept
{
    return height;
}

Iterator<color_t> FrameBuffer::begin() noexcept
{
    return Iterator<color_t>(data_ptr, elems_num, 0);
}

Iterator<color_t> FrameBuffer::end() noexcept
{
    return Iterator<color_t>(data_ptr, elems_num, elems_num);
}

ConstIterator<color_t> FrameBuffer::cbegin() const noexcept
{
    return ConstIterator<color_t>(data_ptr, elems_num, 0);
}

ConstIterator<color_t> FrameBuffer::cend() const noexcept
{
    return ConstIterator<color_t>(data_ptr, elems_num, elems_num);
}

color_t &FrameBuffer::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw FrameBufferIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

const color_t &FrameBuffer::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw FrameBufferIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

color_t &FrameBuffer::operator [](int id)
{
    return getElem(id);
}

const color_t &FrameBuffer::operator [](int id) const
{
    return getElem(id);
}

color_t &FrameBuffer::getElem(int i, int j)
{
    return getElem(i*width+j);
}

const color_t &FrameBuffer::getElem(int i, int j) const
{
    return getElem(i*width+j);
}

color_t &FrameBuffer::operator()(int i, int j)
{
    return getElem(i*width+j);
}

const color_t &FrameBuffer::operator()(const int &i, const int &j) const
{
    return getElem(i*width+j);
}

void FrameBuffer::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<color_t[]> new_ptr(new color_t[elems_num]);
        //shared_ptr<HeightsArray[]> new_ptr(new HeightsArray[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw FrameBufferAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}

ostream& operator <<(ostream& os, const FrameBuffer& buf)
{
    if (buf.isEmpty())
    {
        os << "FrameBuffer is empty.";
        return os;
    }

    os << "Width = " << buf.getWidth() << " Height = " << buf.getHeight();

    ConstIterator<color_t> It = buf.cbegin();
    for (int i = 0; i < buf.getHeight() && It != buf.cend(); i++)
    {
        float h, s, v;
        for (int j = 0; j < buf.getWidth() && It != buf.cend(); It++, j++)
        {
            It->getHsvF(&h, &s, &v);
            os << "In pixel (" << i << ", " << j << ") Hue = " << h << "; Saturation = " << s << "; Value = " << v << ";\n";
        }
        os << '\n';
    }
    os << endl;

    return os;
}
