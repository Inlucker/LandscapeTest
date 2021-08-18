#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Matrix/BaseMtrx.hpp"

#include <QColor>

typedef QColor color_t;

class FrameBuffer : public BaseMtrx<QColor>
{
public:
    using BaseType = BaseMtrx<QColor>;  //alias, will be useful someday
    FrameBuffer();
    FrameBuffer(int new_width, int new_height);

    virtual void reset() noexcept;
};

ostream& operator <<(ostream& os, const FrameBuffer& map);

#endif // FRAMEBUFFER_H
