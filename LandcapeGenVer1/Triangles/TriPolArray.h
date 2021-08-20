#ifndef TRIPOLARRAY_H
#define TRIPOLARRAY_H

#include "Array/BaseArray.hpp"

class TriangularPolygon;
class HeightsMapPoints;

class TriPolArray : public BaseArray<TriangularPolygon>
{
public:
    using BaseType = BaseArray<TriangularPolygon>;  //alias, will be useful someday
    TriPolArray();
    explicit TriPolArray(int new_size);

    //void updatePoints(HeightsMapPoints &map);
    void update();
};

#endif // TRIPOLARRAY_H
