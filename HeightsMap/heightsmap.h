#ifndef HEIGHTSMAP_H
#define HEIGHTSMAP_H

/*#include <memory>
#include <cmath>
#include <stdarg.h>
#include <iostream>
#include <time.h>

#include "basevector.h"
#include "iterator.hpp"
#include "constiterator.hpp"
#include "errors.h"

using namespace std;*/

#include <iostream>
#include <memory>

using namespace std;

//#include "constiterator.hpp"
#include "iterator.hpp"
#include "constiterator.hpp"
#include "errors.h"

typedef double height_t;

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

    height_t& getElem(int id);
    const height_t& getElem(int id) const;
    height_t& operator [](int id);
    const height_t& operator [](int id) const;

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
