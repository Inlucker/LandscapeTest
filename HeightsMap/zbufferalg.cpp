#include "zbufferalg.h"

#include "zbuffer.h"
#include "framebuffer.h"
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
    zbuffer = make_shared<ZBuffer>(width, height); //reset
    frame_buffer = make_shared<FrameBuffer>(width, height); //reset
    for (auto& elem : mas)
    {
        for (int i = max(elem.getMinX(), 0.); i < min(elem.getMaxX(), double(height)); i++)
        {
            for (int j = max(elem.getMinY(), 0.); j < min(elem.getMaxY(), double(width)); j++)
            {
                    if (elem.isInTriangle(i, j))
                    {
                        if ((*zbuffer)(i, j) < elem.getZ(i, j))
                        {
                            (*zbuffer)(i, j) = elem.getZ(i, j);
                            (*frame_buffer)(i, j) = elem.getColor();//elem.getColor(x, y);
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
