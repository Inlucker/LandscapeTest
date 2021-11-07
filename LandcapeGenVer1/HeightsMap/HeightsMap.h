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

    double getMaxHeight();

    void resetHeightsmap() noexcept;

    void diamondSquare();
    //void diamondSquare(float r);
    void diamondSquare(float r, bool smoothing = false);
    void simpleGen(double r = 16, int n = 1);

    void readFromFile(string file_name);

    shared_ptr<HeightsMapPoints> createPoints(double kx, double ky, double kz);
    shared_ptr<HeightsMapPoints> createPoints();

private:
    void changeSizes(int new_height, int new_width);

    //ToFigureOut and Understand how it works
    void diamondSquare(unsigned x1, unsigned y1, unsigned x2, unsigned y2, float range, unsigned level);
    void diamondSquare2(int x1, int y1, int x2, int y2, float range, unsigned level);
    double getRnd() const noexcept;

    void randomizeHeightsMap(int x1, int y1, int x2, int y2, double n = 16) noexcept;
    void smoothHeightsMap(int x1, int y1, int x2, int y2, int n = 1) noexcept;
    double getValue(int i, int j);

    void calcMaxHeight();

private:
    double max_height;
};

ostream& operator <<(ostream& os, const HeightsMap& map);

#endif // HEIGHTSMAP_H
