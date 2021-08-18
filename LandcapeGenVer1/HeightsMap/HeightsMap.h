#ifndef HEIGHTSMAP_H
#define HEIGHTSMAP_H

#include "Matrix/BaseMtrx.hpp"

#define DS_RANGE (size-1)*0.75
#define DS_LEVEL (size-1)

typedef double height_t;

class HeightsMapPoints;

class HeightsMap : public BaseMtrx<height_t>
{
public:
    using BaseType = BaseMtrx<height_t>;  //alias, will be useful someday
    HeightsMap();
    explicit HeightsMap(int new_size);

    void resetHeightsmap() noexcept;

    void diamondSquare();
    void diamondSquare(float r, unsigned int l);

    shared_ptr<HeightsMapPoints> createPoints(int kx, int ky, int kz);
    shared_ptr<HeightsMapPoints> createPoints();

private:
    //ToFigureOut and Understand how it works
    void diamondSquare(unsigned x1, unsigned y1, unsigned x2, unsigned y2, float range, unsigned level);
    double getRnd() const noexcept;
};

ostream& operator <<(ostream& os, const HeightsMap& map);

#endif // HEIGHTSMAP_H
