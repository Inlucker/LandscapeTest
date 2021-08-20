#ifndef HEIGHTSMAPPOINTS_H
#define HEIGHTSMAPPOINTS_H

#include "Matrix/BaseMtrx.hpp"

#include "Point.h"
#include "HeightsMap.h"

class TriPolArray;

class HeightsMapPoints : public BaseMtrx<shared_ptr<Point>>
{
public:
    using BaseType = BaseMtrx<shared_ptr<Point>>;  //alias, will be useful someday
    HeightsMapPoints();
    explicit HeightsMapPoints(int new_size);

    shared_ptr<TriPolArray> createTriPolArray();

    //void transform(const Point moveK, const Point scaleK, const Point rotateK, const Point center); //no need?
    void transform(const Point &moveK, const Point &scaleK, const Point &rotateK);

    const Point& getCenter() const;

private:
    //void alloc_data();
    void updateCenter() noexcept;
    friend shared_ptr<HeightsMapPoints> HeightsMap::createPoints(double kx, double ky, double kz);
    friend ostream& operator <<(ostream& os, const HeightsMapPoints& map);

private:
    Point map_points_center;
};

ostream& operator <<(ostream& os, const HeightsMapPoints& map);

#endif // HEIGHTSMAPPOINTS_H
