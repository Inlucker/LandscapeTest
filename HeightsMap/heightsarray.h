#ifndef HEIGHTSARRAY_H
#define HEIGHTSARRAY_H

#include <iostream>
#include <memory>

using namespace std;

#include "iterator.hpp"
#include "constiterator.hpp"

typedef double height_t;

//class HeightsMap;

class HeightsArray
{
public:
    HeightsArray();
    HeightsArray(int new_size);
    //HeightsArray(HeightsMap& map, int id);

    //explicit HeightsArray(const HeightsArray& arr); //copy
    //HeightsArray& operator =(const HeightsArray& arr);
    //HeightsArray(HeightsArray&& arr) noexcept; //Перенеос
    //HeightsArray& operator =(HeightsArray&& arr) noexcept;

    bool isEmpty() const noexcept;
    int size() const noexcept;

    Iterator<height_t> begin() noexcept;
    Iterator<height_t> end() noexcept;
    ConstIterator<height_t> cbegin() const noexcept;
    ConstIterator<height_t> cend() const noexcept;

    //void resetHeightsArray();
    //void randomizeHeightsArray();
    //void smoothHeightsArray();
    //double getHeight(int i, int j);

    height_t& getElem(int id);
    const height_t& getElem(int id) const;
    height_t& operator [](int id);
    const height_t& operator [](int id) const;

private:
    void alloc_data();

private:
    shared_ptr<height_t[]> data_ptr;
    int elems_num;
};

ostream& operator <<(ostream& os, const HeightsArray& arr);

#endif // HEIGHTSARRAY_H
