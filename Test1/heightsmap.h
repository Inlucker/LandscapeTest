#ifndef HEIGHTSMAP_H
#define HEIGHTSMAP_H

#include <iostream>
#include <memory>

using namespace std;

#include "iterator.hpp"
#include "constiterator.hpp"
//#include "errors.h"

typedef double height_t;

class HeightsMapPoints;

class HeightsMap
{
public:
    HeightsMap();
    HeightsMap(int new_size);

    bool isEmpty() const noexcept;
    int getSize() const noexcept;
    int elemsNum() const noexcept;

    Iterator<height_t> begin() noexcept;
    Iterator<height_t> end() noexcept;
    ConstIterator<height_t> cbegin() const noexcept;
    ConstIterator<height_t> cend() const noexcept;

    void resetHeightsmap();
    void randomizeHeightsMap();
    void smoothHeightsMap();
    void diamondSquare();
    double getHeight(int i, int j);

    shared_ptr<HeightsMapPoints> createPoints(int kx, int ky, int kz);
    shared_ptr<HeightsMapPoints> createPoints();

    height_t& getElem(int id);
    const height_t& getElem(int id) const;
    height_t& operator [](int id);
    const height_t& operator [](int id) const;

    //Done instead of operator[][]
    height_t& operator()(int i, int j);
    const height_t& operator()(const int &i, const int &j) const;

private:
    void alloc_data();

    void diamondSquare(int left_x, int right_x, int bot_y, int top_y);
    void diamond(int lx, int ly, int rx, int ry);
    void square(int x, int y, int l);

private:
    shared_ptr<height_t[]> data_ptr;
    int size;
    int elems_num;
};

ostream& operator <<(ostream& os, const HeightsMap& map);

#endif // HEIGHTSMAP_H
