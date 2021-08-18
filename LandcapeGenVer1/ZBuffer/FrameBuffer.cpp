#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
    alloc_data();
}

FrameBuffer::FrameBuffer(int new_width, int new_height) : BaseType(new_width, new_height)
{

}

void FrameBuffer::reset() noexcept
{
    for (auto &elem:*this)
        elem = Qt::white;
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
        int r, g, b;
        for (int j = 0; j < buf.getWidth() && It != buf.cend(); It++, j++)
        {
            It->getRgb(&r, &g, &b);
            os << "In pixel (" << i << ", " << j << ") Red = " << r << "; Green = " << g << "; Blue = " << b << ";\n";
        }
        os << '\n';
    }
    os << endl;

    return os;
}
