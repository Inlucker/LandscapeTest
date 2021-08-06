#include "triangularpolygon.h"

TriangularPolygon::TriangularPolygon() : TriangularPolygon(Point(), Point(), Point())
{

}

TriangularPolygon::TriangularPolygon(Point new_p1, Point new_p2, Point new_p3) : p1(new_p1), p2(new_p2), p3(new_p3)
{
    /*points[0] = new_p1;
    points[1] = new_p2;
    points[2] = new_p3;*/
    calcRect();
    calcNormals();
}

void TriangularPolygon::calcRect()
{
    min_x = p1.getX();
    max_x = p1.getX();
    min_y = p1.getY();
    max_y = p1.getY();

    if (p2.getX() < min_x)
        min_x = p2.getX();
    if (p2.getX() > max_x)
        max_x = p2.getX();
    if (p2.getY() < min_y)
        min_y = p2.getY();
    if (p2.getY() > max_y)
        max_y = p2.getY();

    if (p3.getX() < min_x)
        min_x = p3.getX();
    if (p3.getX() > max_x)
        max_x = p3.getX();
    if (p3.getY() < min_y)
        min_y = p3.getY();
    if (p3.getY() > max_y)
        max_y = p3.getY();

    cout << "min_x = " << min_x << "; max_x = " << max_x << "; min_y = " << min_y << "; max_y = " << max_y << endl;

    /*min_x = points[0].getX();
    max_x = points[0].getX();
    min_y = points[0].getY();
    max_y = points[0].getY();
    for (int i = 1; i < 3; i++)
    {
        if (points[i].getX() < min_x)
            min_x = points[i].getX();
        if (points[i].getX() > max_x)
            max_x = points[i].getX();
        if (points[i].getY() < min_y)
            min_y = points[i].getY();
        if (points[i].getY() > max_y)
            max_y = points[i].getY();
    }*/
}

void TriangularPolygon::calcNormals()
{
    Vector vec1 = {p2.getX() - p1.getX(), p2.getY() - p1.getY()};
    Vector vec2 = {p3.getX() - p2.getX(), p3.getY() - p2.getY()};
    Vector vec3 = {p1.getX() - p3.getX(), p1.getY() - p3.getY()};
    cout << vec1 << vec2 << vec3 << endl;
    if (vec1[1] != 0)
    {
        norm_vec1 = {1, -vec1[0]/vec1[1]};
        //Зависит от того, идут ли точки по часовой, или против.
        if (norm_vec1 * vec2 < 0)
            norm_vec1 = norm_vec1*(-1.);
    }
    else
        norm_vec1 = {0, 1};

    if (vec2[1] != 0)
    {
        norm_vec2 = {1, -vec2[0]/vec2[1]};
        //Зависит от того, идут ли точки по часовой, или против.
        if (norm_vec2 * vec3 < 0)
            norm_vec2 = norm_vec2*(-1.);
    }
    else
        norm_vec2 = {0, 1};

    if (vec3[1] != 0)
    {
        norm_vec3 = {1, -vec3[0]/vec3[1]};
        //Зависит от того, идут ли точки по часовой, или против.
        if (norm_vec3 * vec1 < 0)
            norm_vec3 = norm_vec3*(-1.);
    }
    else
        norm_vec3 = {0, 1};

    cout << norm_vec1 << norm_vec2 << norm_vec3 << endl;
}
