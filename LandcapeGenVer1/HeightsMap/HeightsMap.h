#ifndef HEIGHTSMAP_H
#define HEIGHTSMAP_H

#include <iostream>
#include <memory>

using namespace std;

template<typename Type>
class Iterator;
template<typename Type>
class ConstIterator;

#define RANGE (size-1)*0.75
#define LEVEL (size-1)

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

    void diamondSquare();
    void diamondSquare(float r, unsigned int l);

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

    //ToFigureOut and Understand how it works
    void diamondSquare(unsigned x1, unsigned y1, unsigned x2, unsigned y2, float range, unsigned level);
    double getRnd() const noexcept;

private:
    shared_ptr<height_t[]> data_ptr;
    int size = -1;
    int elems_num = -1;
};

ostream& operator <<(ostream& os, const HeightsMap& map);

#endif // HEIGHTSMAP_H
