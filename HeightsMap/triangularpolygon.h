#ifndef TRIANGULARPOLYGON_H
#define TRIANGULARPOLYGON_H

#include "point.h"
#include "vector.hpp"

#include <QColor>

typedef QColor color_t;

class TriangularPolygon
{
public:
    TriangularPolygon();
    TriangularPolygon(Point new_p1, Point new_p2, Point new_p3) ;
    TriangularPolygon(Point new_p1, Point new_p2, Point new_p3, color_t c);
    ~TriangularPolygon() = default;

    double getZ(double x, double y) const;
    color_t getColor() const noexcept;

    bool isInRect(double x, double y) const noexcept;
    bool isInTriangle(double x, double y) const;

    double getMinX() const noexcept;
    double getMaxX() const noexcept;
    double getMinY() const noexcept;
    double getMaxY() const noexcept;

    void setPoints(Point new_p1, Point new_p2, Point new_p3);

private:
    void calcRect();
    void calcNormals();
    void calcSurface();
    void calcColor();

    friend ostream& operator <<(ostream& os, const TriangularPolygon& pol);

private:
    Point p1, p2, p3;
    double min_x, max_x, min_y, max_y;
    Vector<double> norm_vec1, norm_vec2, norm_vec3;
    double A, B, C, D;
    color_t color;
};

ostream& operator <<(ostream& os, const TriangularPolygon& pol);

#endif // TRIANGULARPOLYGON_H
