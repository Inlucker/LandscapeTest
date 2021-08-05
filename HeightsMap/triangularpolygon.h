#ifndef TRIANGULARPOLYGON_H
#define TRIANGULARPOLYGON_H

#include "point.h"
#include "vector.hpp"

class TriangularPolygon
{
public:
    TriangularPolygon();
    ~TriangularPolygon() = default;

private:
    Point p1, p2, p3;
    Vector<double> norm_vec1, norm_vec2, norm_vec3;
};

#endif // TRIANGULARPOLYGON_H
