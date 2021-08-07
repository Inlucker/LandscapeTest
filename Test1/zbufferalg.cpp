#include "zbufferalg.h"

//#include "zbuffer.h"
//#include "framebuffer.h"
#include "tripolmas.h"
#include "triangularpolygon.h"

#include <math.h>

ZBufferAlg::ZBufferAlg(int new_width, int new_height)
{
    zbuffer = make_shared<ZBuffer>(new_width, new_height);
    frame_buffer = make_shared<FrameBuffer>(new_width, new_height);
    width = new_width;
    height = new_height;
}

void ZBufferAlg::execute(TriPolMas &mas)
{
    //HERE
    zbuffer = make_shared<ZBuffer>(width, height);
    frame_buffer = make_shared<FrameBuffer>(width, height);
    for (auto& elem : mas)
    {
        for (int y = max(elem.getMinY(), 0.); y <= min(elem.getMaxY(), height); y++)
        {
            for (int x = max(elem.getMinX(), 0.); x <= min(elem.getMaxX(), width); x++)
            {
                if (elem.isInTriangle(x, y))
                {
                    if ((*zbuffer)(x, y) < elem.getZ(x, y))
                    {
                        (*zbuffer)(x, y) = elem.getZ(x, y);
                        (*frame_buffer)(x, y) = elem.getColor(x, y);//elem.getColor(x, y);
                    }
                }
            }
        }
    }

}

shared_ptr<FrameBuffer> ZBufferAlg::getFrameBuffer() const noexcept
{
    return frame_buffer;
}
