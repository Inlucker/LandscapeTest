#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <iostream>
#include <memory>

using namespace std;

template<typename Type>
class Iterator;
template<typename Type>
class ConstIterator;
//#include "iterator.hpp"
//#include "constiterator.hpp"

class TriPolMas;

class ZBuffer
{
public:
    ZBuffer() = delete;
    ZBuffer(TriPolMas mas);

private:
    shared_ptr<int[]> data_ptr;
    int width;
    int height;
    //CadrBuffer
    //ZBuffer
};

#endif // ZBUFFER_H
