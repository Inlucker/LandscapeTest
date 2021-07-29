#ifndef HEIGHTSMAP_H
#define HEIGHTSMAP_H

#include <iostream>
#include <memory>

using namespace std;

#include "iterator.hpp"
#include "constiterator.hpp"
#include "errors.h"

typedef double height_t;

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
    //HeightsArray& operator [](int id);

    void drawHeightsMap();

private:
    void alloc_data();

private:
    shared_ptr<height_t[]> data_ptr;
    int size;
    int elems_num;
};

ostream& operator <<(ostream& os, const HeightsMap& map);

#endif // HEIGHTSMAP_H
