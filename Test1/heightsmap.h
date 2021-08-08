#ifndef HEIGHTSMAP_H
#define HEIGHTSMAP_H

#include <iostream>
#include <memory>

using namespace std;

template<typename Type>
class Iterator;
template<typename Type>
class ConstIterator;

#include "defines.h"

#define RAND (dRand(-5,5))

typedef double height_t;

class HeightsMapPoints;

class HeightsMap
{
public:
    HeightsMap();
    explicit HeightsMap(int new_size);

    bool isEmpty() const noexcept;
    int getSize() const noexcept;
    int elemsNum() const noexcept;

    Iterator<height_t> begin() noexcept;
    Iterator<height_t> end() noexcept;
    ConstIterator<height_t> cbegin() const noexcept;
    ConstIterator<height_t> cend() const noexcept;

    void resetHeightsmap() noexcept;
    void randomizeHeightsMap() noexcept;
    void smoothHeightsMap() noexcept;
    double getHeight(int i, int j);

    void diamondSquare();
    void diamondSquare1();
    void diamondSquare2();

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

    //variant1
    void diamondSquare(int left_x, int right_x, int bot_y, int top_y);
    void diamond(int lx, int ly, int rx, int ry);
    void square(int x, int y, int l);

    //variant2
    void squareStep(int sideLength, int halfSide);
    void diamondStep(int sideLength, int halfSide);
    double dRand(double d_min, double d_max);

    //variant3
    void DiamondSquare3(unsigned x1, unsigned y1, unsigned x2, unsigned y2, float range, unsigned level);
    double GetRnd() const noexcept;

private:
    shared_ptr<height_t[]> data_ptr;
    int size = -1;
    int elems_num = -1;

    //no need yet
    double roughness = -1;
    int iteration = -1;

    //for diamondSquare variant2
    int range;
    //int i;
};

ostream& operator <<(ostream& os, const HeightsMap& map);

#endif // HEIGHTSMAP_H
