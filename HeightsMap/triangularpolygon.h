#ifndef TRIANGULARPOLYGON_H
#define TRIANGULARPOLYGON_H

#include "point.h"
#include "vector.hpp"

class TriangularPolygon
{
public:
    TriangularPolygon();
    TriangularPolygon(Point new_p1, Point new_p2, Point new_p3);
    ~TriangularPolygon() = default;

    double getZ(double x, double y);

private:
    void calcRect();
    void calcNormals();

private:
    Point p1, p2, p3;
    //Point points[3];
    double min_x, max_x, min_y, max_y;
    Vector<double> norm_vec1, norm_vec2, norm_vec3;
};

#endif // TRIANGULARPOLYGON_H
