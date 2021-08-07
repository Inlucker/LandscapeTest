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
    TriangularPolygon(Point new_p1, Point new_p2, Point new_p3, color_t c);
    ~TriangularPolygon() = default;

    double getZ(double x, double y) const;
    color_t getColor(double x, double y) const;
    color_t getColor() const;

    bool isInRect(double x, double y) const;
    bool isInTriangle(double x, double y) const;

    double getMinX() const;
    double getMaxX() const;
    double getMinY() const;
    double getMaxY() const;

    void setPoints(Point new_p1, Point new_p2, Point new_p3);

private:
    void calcRect();
    void calcNormals();
    void calcSurface();

    bool pointInBox(Point t, Point p1, Point p2) const;
    bool pointInSegment(Point t, Point p1, Point p2) const;
    bool isInEdge(double x, double y, Point edge_p1, Point edge_p2) const;

    bool isInEdge(double x, double y, double x1, double y1, double x2, double y2) const;

    friend ostream& operator <<(ostream& os, const TriangularPolygon& pol);

private:
    Point p1, p2, p3;
    //Point points[3];
    double min_x, max_x, min_y, max_y;
    //double max_z;
    Vector<double> norm_vec1, norm_vec2, norm_vec3;
    double A, B, C, D;
    color_t color;
};

inline double TriangularPolygon::getZ(double x, double y) const
{
    //Ax+By+Cz+D=0 => Cz = -Ax-By-D => z = (-Ax-By-D)/C
    if (C != 0)
        return (-A*x-B*y-D)/C;
    else
    {
        return 0;//ToDo
    }
}

inline color_t TriangularPolygon::getColor() const
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

inline bool TriangularPolygon::isInEdge(double x, double y, double x1, double y1, double x2, double y2) const
{
    //M(x, y) - P1(x1, y1), P2(x2, y2)
    //a(x1, y1), b(x2, y2) то косое произведение [a, b] = x1y2 — x2y1
    //[P1P2, P1M] = 0 – косое произведение (точка лежит на прямой) {x2-x1,y2-y1} X {x-x1,y-y1}
    //(MP1,MP2) ≤ 0 – скалярное произведение (точка лежит между P1 и P2) = x1*x2+y1*y2  {x1-x,y1-y} * {x2-x,y2-y}
    return ((fabs((x2-x1)*(y-y1)-(x-x1)*(y2-y1)) <= EPS) && (((x1-x)*(x2-x)+(y1-y)*(y2-y)) <= 0));
}

ostream& operator <<(ostream& os, const TriangularPolygon& pol);

#endif // TRIANGULARPOLYGON_H
