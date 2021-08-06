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

    bool isInRect(double x, double y);
    bool isInTriangle(double x, double y);

private:
    void calcRect();
    void calcNormals();
    void calcSurface();

private:
    Point p1, p2, p3;
    //Point points[3];
    double min_x, max_x, min_y, max_y;
    //double max_z;
    Vector<double> norm_vec1, norm_vec2, norm_vec3;
    double A, B, C, D;
};

#endif // TRIANGULARPOLYGON_H
