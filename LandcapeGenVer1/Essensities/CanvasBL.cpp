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


CanvasBL::CanvasBL(string hm, string tpa, string c)
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
