#ifndef HEIGHTSMAP_H
#define HEIGHTSMAP_H

#include <iostream>
#include <memory>

using namespace std;

#include "iterator.hpp"
#include "constiterator.hpp"
//#include "errors.h"

typedef double height_t;

//class HeightsArray;
//#include "heightsarray.h"

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
    double getHeight(int i, int j);

    //ToDo operator[][] (maybe reorganisate the shole structure of caontainer and make it container of container)
    height_t& getElem(int id);
    const height_t& getElem(int id) const;
    height_t& operator [](int id);
    const height_t& operator [](int id) const;

    //Done instead of operator[][]
    height_t& operator()(int i, int j);
    const height_t& operator()(const int &i, const int &j) const;

    /*shared_ptr<HeightsArray> getElem(int id);
    const shared_ptr<HeightsArray> getElem(int id) const;
    shared_ptr<HeightsArray> operator [](int id);
    const shared_ptr<HeightsArray> operator [](int id) const;*/

    //Done operator[][] (ToDo above)
    //This is bad, because of creating shared_ptr every time we use operator[]
    /*shared_ptr<height_t[]> getElem(int id);
    const shared_ptr<height_t[]> getElem(int id) const;
    shared_ptr<height_t[]> operator [](int id);
    const shared_ptr<height_t[]> operator [](int id) const;*/

    //void drawHeightsMap();

private:
    void alloc_data();

private:
    shared_ptr<height_t[]> data_ptr;
    //shared_ptr<HeightsArray[]> data_ptr;
    int size;
    int elems_num;
};

ostream& operator <<(ostream& os, const HeightsMap& map);

#endif // HEIGHTSMAP_H
