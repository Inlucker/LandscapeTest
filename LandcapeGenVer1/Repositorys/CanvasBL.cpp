#include "CanvasBL.h"

CanvasBL::CanvasBL(string fn1, string fn2)
{
    string tmp = strFromFile(fn1);
    heights_map = HeightsMap(tmp);
    tmp = strFromFile(fn2);
    HeightsMapPoints hmp(tmp);
    tri_pol_mas = *hmp.createTriPolArray();
}

/*CanvasBL::CanvasBL(string hm, string tpm)
{
    heights_map = HeightsMap(hm);
}*/

HeightsMap &CanvasBL::getHeightsMap()
{
    return heights_map;
}

TriPolArray &CanvasBL::getTriPolArray()
{
    return tri_pol_mas;
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
