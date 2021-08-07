#ifndef ZBUFFERALG_H
#define ZBUFFERALG_H

#include <iostream>
#include <memory>

using namespace std;

class ZBuffer;
class FrameBuffer;
class TriPolMas;

class ZbufferAlg
{
public:
    ZbufferAlg() = delete;
    ZbufferAlg(int new_width, int new_height);
    ZbufferAlg(TriPolMas mas);

    shared_ptr<FrameBuffer> getFrameBuffer() const noexcept;
private:
    shared_ptr<ZBuffer> zbuffer;
    shared_ptr<FrameBuffer> frame_buffer;
};

#endif // ZBUFFERALG_H
