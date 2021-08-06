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
    explicit TriPolMas(int elements_number);

    bool isEmpty() const noexcept;
    int size() const noexcept;

    Iterator<TriangularPolygon> begin() noexcept;
    Iterator<TriangularPolygon> end() noexcept;
    ConstIterator<TriangularPolygon> cbegin() const noexcept;
    ConstIterator<TriangularPolygon> cend() const noexcept;

    //HERE
    void zBuffer();

    TriangularPolygon& getElem(int id);
    const TriangularPolygon& getElem(int id) const;
    TriangularPolygon& operator [](int id);
    const TriangularPolygon& operator [](int id) const;

private:
    void alloc_data();

private:
    shared_ptr<TriangularPolygon[]> data_ptr;
    int elems_num;
};

ostream& operator <<(ostream& os, const TriPolMas& pol);

#endif // TRIPOLMAS_H
