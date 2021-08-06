#ifndef TRIPOLMAS_H
#define TRIPOLMAS_H

#include <iostream>
#include <memory>

using namespace std;

#include "iterator.hpp"
#include "constiterator.hpp"

class TriangularPolygon;

class TriPolMas
{
public:
    TriPolMas();

private:
    void alloc_data();

private:
    shared_ptr<TriangularPolygon[]> data_ptr;
    //shared_ptr<HeightsArray[]> data_ptr;
    int size;
    int elems_num;
};

#endif // TRIPOLMAS_H
