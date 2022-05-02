#include "CanvasBL.h"

CanvasBL::CanvasBL(string fn1, string fn2, string fn3)
{
    string res = strFromFile(fn1);
    heights_map = HeightsMap(res);
    res = strFromFile(fn2);
    heights_map_points = HeightsMapPoints(res);

    ifstream file(fn3); //NEED TO ADD EXCEPTION, WHEN NO SUCH FILE
    file >> red >> green >> blue;
    file.close();
}

/*CanvasBL::CanvasBL(string hm, string tpm)
{
    heights_map = HeightsMap(hm);
}*/

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
