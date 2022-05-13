#include "CanvasBL.h"

/*CanvasBL::CanvasBL(string fn1, string fn2, string fn3)
{
    string res = strFromFile(fn1);
    heights_map = HeightsMap(res);
    res = strFromFile(fn2);
    heights_map_points = HeightsMapPoints(res);

    ifstream file(fn3); //NEED TO ADD EXCEPTION, WHEN NO SUCH FILE
    file >> red >> green >> blue;
    file.close();
}*/


CanvasBL::CanvasBL(string &hm, string &tpa, string &c)
{
    heights_map = HeightsMap(hm);
    heights_map_points = HeightsMapPoints(tpa);

    int i = 0;
    string tmp = "";
    while (c[i] != ' ' && c[i] != '\n' && c[i] != '\0')
    {
        tmp += c[i++];
    }
    red = stoi(tmp);
    i++;
    tmp = "";

    while (c[i] != ' ' && c[i] != '\n' && c[i] != '\0')
    {
        tmp += c[i++];
    }
    green = stoi(tmp);
    i++;
    tmp = "";

    while (c[i] != ' ' && c[i] != '\n' && c[i] != '\0')
    {
        tmp += c[i++];
    }
    blue = stoi(tmp);
    i++;
    tmp = "";
}

CanvasBL::CanvasBL(HeightsMap &hm, HeightsMapPoints &hmp, int r, int g, int b)
{
    heights_map = hm;
    heights_map_points = hmp;
    red = r;
    green = g;
    blue = b;
}

bool CanvasBL::operator ==(CanvasBL &an_c)
{

    bool res = true;

    if (this->heights_map != an_c.heights_map ||
            this->heights_map_points != an_c.heights_map_points ||
            this->red != an_c.red ||
            this->green != an_c.green ||
            this->blue != an_c.blue)
        res = false;
    return res;
}

bool CanvasBL::operator !=(CanvasBL &an_c)
{
    return !(*this == an_c);
}

HeightsMap &CanvasBL::getHeightsMap()
{
    return heights_map;
}

HeightsMapPoints &CanvasBL::getHeightsMapPoints()
{
    return heights_map_points;
}

void CanvasBL::getColor(int &r, int &g, int &b) noexcept
{
    r = red;
    g = green;
    b = blue;
}

void CanvasBL::getColor(string &c) noexcept
{
    c = to_string(red) + " " + to_string(green) + " " + to_string(blue);
}

string CanvasBL::strFromFile(string file_name)
{
    string res = "";
    ifstream file(file_name); //NEED TO ADD EXCEPTION, WHEN NO SUCH FILE

    string tmp = "";
    while (file >> tmp)
        res += tmp + " ";
    file.close();
    return res;
}
