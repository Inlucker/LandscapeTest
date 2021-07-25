#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    //Point(Point newPoint);
    Point(const double new_x, const double new_y, const double new_z);

    ~Point() = default;

    void transform(const Point moveK, const Point scaleK, const Point rotateK, const Point center);
    void transform(const Point moveK, const Point scaleK, const Point rotateK);

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double new_x);
    void setY(double new_y);
    void setZ(double new_z);
private:
    void move(const Point move);
    void scale(const Point scale, const Point center);

    void rotateX(const double angle, const Point center);
    void rotateY(const double angle, const Point center);
    void rotateZ(const double angle, const Point center);

    void rotateX(const double angle);
    void rotateY(const double angle);
    void rotateZ(const double angle);

    void rotate(const Point rotate, const Point center);

    void rotate(const Point rotate);

    double x, y, z;
};

#endif // POINT_H
