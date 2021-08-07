#ifndef TRIANGULARPOLYGON_H
#define TRIANGULARPOLYGON_H

#include "point.h"
#include "vector.hpp"

typedef int color_t;

class TriangularPolygon
{
public:
    TriangularPolygon();
    TriangularPolygon(Point new_p1, Point new_p2, Point new_p3);
    ~TriangularPolygon() = default;

    double getZ(double x, double y) const;
    color_t getColor(double x, double y) const;

    bool isInRect(double x, double y) const;
    bool isInTriangle(double x, double y) const;

    double getMinX() const;
    double getMaxX() const;
    double getMinY() const;
    double getMaxY() const;

private:
    void calcRect();
    void calcNormals();
    void calcSurface();

    bool isInEdge(double x, double y, Point edge_p1, Point edge_p2) const;

    friend ostream& operator <<(ostream& os, const TriangularPolygon& pol);

private:
    Point p1, p2, p3;
    //Point points[3];
    double min_x, max_x, min_y, max_y;
    //double max_z;
    Vector<double> norm_vec1, norm_vec2, norm_vec3;
    double A, B, C, D;
};

ostream& operator <<(ostream& os, const TriangularPolygon& pol);

#endif // TRIANGULARPOLYGON_H
