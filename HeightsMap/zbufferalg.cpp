#include "zbufferalg.h"

#include "zbuffer.h"
#include "framebuffer.h"
#include "tripolmas.h"

ZbufferAlg::ZbufferAlg(TriPolMas mas)
{
    //HERE
}

shared_ptr<FrameBuffer> ZbufferAlg::getFrameBuffer() const noexcept
{
    return frame_buffer;
}
