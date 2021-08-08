#ifndef ZBUFFERALG_H
#define ZBUFFERALG_H

#include <iostream>
#include <memory>

using namespace std;

#include "zbuffer.h"
#include "framebuffer.h"
class TriPolMas;

class ZBufferAlg
{
public:
    ZBufferAlg() = delete;
    ZBufferAlg(int new_width, int new_height);

    void execute(TriPolMas &mas);

    shared_ptr<FrameBuffer> getFrameBuffer() const noexcept;
private:
    shared_ptr<ZBuffer> zbuffer;
    shared_ptr<FrameBuffer> frame_buffer;
    int width;
    int height;
};

#endif // ZBUFFERALG_H
