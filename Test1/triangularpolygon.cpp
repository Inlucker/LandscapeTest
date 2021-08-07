#include "triangularpolygon.h"

// Add Errors?

TriangularPolygon::TriangularPolygon() : TriangularPolygon(Point(), Point(), Point(), QColor())
{

}

TriangularPolygon::TriangularPolygon(Point new_p1, Point new_p2, Point new_p3) : p1(new_p1), p2(new_p2), p3(new_p3)
{
    //int c = rand()%128+64;
    //color = QColor(c, c, c);
    calcColor();
    calcRect();
    calcNormals();
    calcSurface();
}

TriangularPolygon::TriangularPolygon(Point new_p1, Point new_p2, Point new_p3, color_t c) : p1(new_p1), p2(new_p2), p3(new_p3), color(c)
{
    /*points[0] = new_p1;
    points[1] = new_p2;
    points[2] = new_p3;*/
    calcRect();
    calcNormals();
    calcSurface();
}

/*double TriangularPolygon::getZ(double x, double y) const
{
    //Ax+By+Cz+D=0 => Cz = -Ax-By-D => z = (-Ax-By-D)/C
    if (C != 0)
        return (-A*x-B*y-D)/C;
    else
    {
        return 0;//ToDo
    }
}*/

#define eps 50

bool TriangularPolygon::pointInBox(Point t, Point p1, Point p2) const
{
    return  (abs (t.getX() - min(p1.getX(), p2.getX())) <= eps || min(p1.getX(), p2.getX()) <= t.getX()) &&
            (abs (max(p1.getX(), p2.getX()) - t.getX()) <= eps || max(p1.getX(), p2.getX()) >= t.getX()) &&
            (abs (t.getY() - min(p1.getY(), p2.getY())) <= eps || min(p1.getY(), p2.getY()) <= t.getY()) &&
            (abs (max(p1.getY(), p2.getY()) - t.getY()) <= eps || max(p1.getY(), p2.getY()) >= t.getY());
}

bool TriangularPolygon::pointInSegment(Point t, Point p1, Point p2) const
{
    double a = p2.getY() - p1.getY();
    double b = p1.getX() - p2.getX();
    double c = - a * p1.getX() - b * p1.getY();
    if (abs(a * t.getX() + b * t.getY() + c) > eps) return false;

    return pointInBox (t, p1, p2);
}

bool TriangularPolygon::isInEdge(double x, double y, Point edge_p1, Point edge_p2) const
{
    Vector<double> tmp = {x, y};
    Vector<double> edge = {edge_p2.getX() - edge_p1.getX(), edge_p2.getY() - edge_p2.getY()};
    if (fabs(x*edge[1]-edge[0]*y) <= EPS && tmp * edge <= 0)
        return true;
    else
        return false;
}

color_t TriangularPolygon::getColor(double x, double y) const
{
    /*if (isInEdge(x, y, p1, p2))
        return 1;
    else if (isInEdge(x, y, p2, p3))
        return 1;
    else if (isInEdge(x, y, p3, p1))
        return 1;
    return 0;*/

    /*if (isInEdge(x, y, p1.getX(), p1.getX(), p2.getX(), p2.getY()))
        return 1;
    else if (isInEdge(x, y, p2.getX(), p2.getX(), p3.getX(), p3.getY()))
        return 1;
    else if (isInEdge(x, y, p3.getX(), p3.getX(), p1.getX(), p1.getY()))
        return 1;*/

    if (pointInSegment(Point(x, y, 0), p1, p2))
        return Qt::black;
    else if (pointInSegment(Point(x, y, 0), p2, p3))
        return Qt::black;
    else if (pointInSegment(Point(x, y, 0), p3, p1))
        return Qt::black;
    return Qt::white;
}

bool TriangularPolygon::isInRect(double x, double y) const
{
    return (x >= min_x && x <= max_x && y >= min_y && y <= max_y);
}

bool TriangularPolygon::isInTriangle(double x, double y) const
{
    //Vector tmp1 = {x - p1.getX(), y - p1.getY()};
    //Vector tmp2 = {x - p2.getX(), y - p2.getY()};
    //Vector tmp3 = {x - p3.getX(), y - p3.getY()};

    //x1*x2+y1*y2
    if ((x - p1.getX())*norm_vec1[0] + (y - p1.getY())*norm_vec1[1] < 0 ||
        (x - p2.getX())*norm_vec2[0] + (y - p2.getY())*norm_vec2[1] < 0 ||
        (x - p3.getX())*norm_vec3[0] + (y - p3.getY())*norm_vec3[1] < 0)
        return false;
    else
        return true;;

}

void TriangularPolygon::setPoints(Point new_p1, Point new_p2, Point new_p3)
{
    p1 = new_p1;
    p2 = new_p2;
    p3 = new_p3;
    calcRect();
    calcNormals();
    calcSurface();
}

/*double TriangularPolygon::getMinX() const
{
    return min_x;
}

double TriangularPolygon::getMaxX() const
{
    return max_x;
}

double TriangularPolygon::getMinY() const
{
    return min_y;
}

double TriangularPolygon::getMaxY() const
{
    return max_y;
}*/

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

    //cout << "min_x = " << min_x << "; max_x = " << max_x << "; min_y = " << min_y << "; max_y = " << max_y << endl;

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
    // Пока что ?обязательно? по часовой, чтобы получить внутренние нормали
    Vector vec1 = {p2.getX() - p1.getX(), p2.getY() - p1.getY()};
    Vector vec2 = {p3.getX() - p2.getX(), p3.getY() - p2.getY()};
    Vector vec3 = {p1.getX() - p3.getX(), p1.getY() - p3.getY()};

    //cout << vec1 << vec2 << vec3 << endl;

    if (vec1[1] != 0)
        norm_vec1 = {1, -vec1[0]/vec1[1]};
    else
        norm_vec1 = {0, 1};
    //Зависит от того, идут ли точки по часовой, или против.
    if (norm_vec1 * vec2 < 0)
        norm_vec1 = norm_vec1*(-1.);

    if (vec2[1] != 0)
        norm_vec2 = {1, -vec2[0]/vec2[1]};
    else
        norm_vec2 = {0, 1};
    //Зависит от того, идут ли точки по часовой, или против.
    if (norm_vec2 * vec3 < 0)
        norm_vec2 = norm_vec2*(-1.);

    if (vec3[1] != 0)
        norm_vec3 = {1, -vec3[0]/vec3[1]};
    else
        norm_vec3 = {0, 1};
    //Зависит от того, идут ли точки по часовой, или против.
    if (norm_vec3 * vec1 < 0)
        norm_vec3 = norm_vec3*(-1.);

    //cout << norm_vec1 << norm_vec2 << norm_vec3 << endl;
}

void TriangularPolygon::calcSurface()
{
    //Here ToDo: Find A, B, C, D!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    double x1 = p1.getX(), y1 = p1.getY(), z1 = p1.getZ();
    double x2 = p2.getX(), y2 = p2.getY(), z2 = p2.getZ();
    double x3 = p3.getX(), y3 = p3.getY(), z3 = p3.getZ();
    A = y1 *(z2 - z3) + y2 *(z3 - z1) + y3* (z1 - z2) ;
    B = z1 *(x2 - x3) + z2 *(x3 - x1) + z3 *(x1 - x2);
    C = x1 *(y2 - y3) + x2 *(y3 - y1) + x3 *(y1 - y2) ;
    D = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));

    //cout << "A = " << A << "; B = " << B << "; C = " << C << "; D = " << D << endl;
}

void TriangularPolygon::calcColor()
{
    Vector<double> normal = {A, B, C};
    Vector<double> beam = {0, 1, 0};
    double cosinus = fabs((normal*beam)/(normal.len()*beam.len()));
    color = QColor(200, 200, 200);
    float h, s, l;
    color.getHslF(&h, &s, &l);
    //cout << h << "; " << s << "; " << l << endl;
    if (cosinus > 1)
    {
        cout << normal << endl;
        cout << beam << endl;
        cout << cosinus << endl;
    }
    color.setHslF(color.hslHueF(), color.hslSaturationF(), 0.25+float(cosinus/4)); //1? = lightness, 0? = drakness
}

ostream& operator <<(ostream& os, const TriangularPolygon& pol)
{
    os << pol.p1 << pol.p2 << pol.p3;
    return os;
}
