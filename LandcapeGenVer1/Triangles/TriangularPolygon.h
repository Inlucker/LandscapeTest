#ifndef TRIANGULARPOLYGON_H
#define TRIANGULARPOLYGON_H

#include "HeightsMap/Point.h"
#include "Vector/Vector.hpp"

#include <QColor>

typedef QColor color_t;

class TriangularPolygon
{
public:
    TriangularPolygon();
    TriangularPolygon(Point new_p1, Point new_p2, Point new_p3);
    TriangularPolygon(Point new_p1, Point new_p2, Point new_p3, color_t c);
    ~TriangularPolygon() = default;

    double getZ(double x, double y) const;

    color_t &getColor();

    bool isInRect(double x, double y) const;
    bool isInTriangle(double x, double y) const;

    double getMinX() const;
    double getMaxX() const;
    double getMinY() const;
    double getMaxY() const;

    const Point &getP1() const;
    const Point& getP2() const;
    const Point &getP3() const;
    /*int getP1() const;
    int getP2() const;
    int getP3() const;*/

    void setPoints(Point new_p1, Point new_p2, Point new_p3);

private:
    void calcRect();
    void calcNormals();
    void calcSurface();
    void calcColor();

    void swap(Point &p1, Point &p2);

    friend ostream& operator <<(ostream& os, const TriangularPolygon& pol);

private:
    Point p1, p2, p3;
    //int p1, p2, p3;
    double min_x, max_x, min_y, max_y;
    Vector<double> norm_vec1, norm_vec2, norm_vec3;
    double A, B, C, D;
    color_t color;
};


inline color_t &TriangularPolygon::getColor()
{
    return color;
}

inline double TriangularPolygon::getMinX() const
{
    return min_x;
}

inline double TriangularPolygon::getMaxX() const
{
    return max_x;
}

inline double TriangularPolygon::getMinY() const
{
    return min_y;
}

inline double TriangularPolygon::getMaxY() const
{
    return max_y;
}

ostream& operator <<(ostream& os, const TriangularPolygon& pol);

#endif // TRIANGULARPOLYGON_H
