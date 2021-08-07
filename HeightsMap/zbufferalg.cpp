#include "zbufferalg.h"

#include "zbuffer.h"
#include "framebuffer.h"
#include "tripolmas.h"
#include "triangularpolygon.h"

ZbufferAlg::ZbufferAlg(int new_width, int new_height)
{
    zbuffer = make_shared<ZBuffer>(new_width, new_height);
    frame_buffer = make_shared<FrameBuffer>(new_width, new_height);
}

void ZbufferAlg::execute(TriPolMas mas)
{
    //HERE
    for (auto& elem : mas)
    {
        for (int y = elem.getMinY(); y <= elem.getMaxY(); y++)
        {
            for (int x = elem.getMinX(); x <= elem.getMaxX(); x++)
            {
                if (elem.isInTriangle(x, y))
                {
                    if ((*zbuffer)(x, y) < elem.getZ(x, y))
                    {
                        (*zbuffer)(x, y) = elem.getZ(x, y);
                        //(*frame_buffer)(x, y) = elem.getColor(x, y); ToDo
                    }
                }
            }
        }
    }

}

shared_ptr<FrameBuffer> ZbufferAlg::getFrameBuffer() const noexcept
{
    return frame_buffer;
}
