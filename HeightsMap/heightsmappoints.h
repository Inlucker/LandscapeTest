#ifndef HEIGHTSMAPPOINTS_H
#define HEIGHTSMAPPOINTS_H

#include <iostream>
#include <memory>

using namespace std;

#include "iterator.hpp"
#include "constiterator.hpp"
#include "point.h"

typedef double height_t;

class HeightsMapPoints
{
public:
    HeightsMapPoints();
    HeightsMapPoints(int new_size);

    bool isEmpty() const noexcept;
    int getSize() const noexcept;
    int elemsNum() const noexcept;

    Iterator<Point> begin() noexcept;
    Iterator<Point> end() noexcept;
    ConstIterator<Point> cbegin() const noexcept;
    ConstIterator<Point> cend() const noexcept;

    Point& getElem(int id);
    const Point& getElem(int id) const;
    Point& operator [](int id);
    const Point& operator [](int id) const;

    Point& operator()(int i, int j);
    const Point& operator()(const int &i, const int &j) const;

    void transform(const Point moveK, const Point scaleK, const Point rotateK, const Point center);
    void transform(const Point moveK, const Point scaleK, const Point rotateK);

    void updateCenter();

private:
    void alloc_data();
    //void updateCenter();
    friend ostream& operator <<(ostream& os, const HeightsMapPoints& map);

private:
    shared_ptr<Point[]> data_ptr;
    int size;
    int elems_num;
    Point map_points_center;
};

ostream& operator <<(ostream& os, const HeightsMapPoints& map);

#endif // HEIGHTSMAPPOINTS_H