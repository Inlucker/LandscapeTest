#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>
#include <memory>

using namespace std;

template<typename Type>
class Iterator;
template<typename Type>
class ConstIterator;

typedef int color_t;

class FrameBuffer
{
public:
    FrameBuffer();
    FrameBuffer(int new_width, int new_height);

    bool isEmpty() const noexcept;
    int size() const noexcept;
    bool getWidth() const noexcept;
    int getHeight() const noexcept;

    Iterator<color_t> begin() noexcept;
    Iterator<color_t> end() noexcept;
    ConstIterator<color_t> cbegin() const noexcept;
    ConstIterator<color_t> cend() const noexcept;

    color_t& getElem(int id);
    const color_t& getElem(int id) const;
    color_t& operator [](int id);
    const color_t& operator [](int id) const;

    color_t& getElem(int i, int j);
    const color_t& getElem(int i, int j) const;
    color_t& operator()(int i, int j);
    const color_t& operator()(const int &i, const int &j) const;

private:
    void alloc_data();

private:
    //FrameBuffer
    shared_ptr<color_t[]> data_ptr;
    int width;
    int height;
    int elems_num;
};

#endif // FRAMEBUFFER_H
