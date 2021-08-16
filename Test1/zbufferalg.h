#ifndef ZBUFFERALG_H
#define ZBUFFERALG_H

#include <iostream>
#include <memory>

using namespace std;

//class ZBuffer;
//class FrameBuffer;
#include "zbuffer.h"
#include "framebuffer.h"
class TriPolMas;

class ZBufferAlg
{
public:
    ZBufferAlg() = delete;
    ZBufferAlg(int new_width, int new_height);

    void execute(TriPolMas &mas);
    void execute2(TriPolMas &mas);

    shared_ptr<FrameBuffer> getFrameBuffer() const noexcept;
private:
    vector<double> interpolate(double i0, double d0, double i1, double d1) const;
    void addInterpolate(vector<double> &values, double i0, double d0, double i1, double d1) const;

private:
    shared_ptr<ZBuffer> zbuffer;
    shared_ptr<FrameBuffer> frame_buffer;
    int width;
    int height;
};

#endif // ZBUFFERALG_H
