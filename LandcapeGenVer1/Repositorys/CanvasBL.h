#ifndef CANVASBL_H
#define CANVASBL_H

#include<fstream>

#include "HeightsMap/HeightsMap.h"
#include "HeightsMap/HeightsMapPoints.h"
#include "Triangles/TriangularPolygon.h"
#include "Triangles/TriPolArray.h"

class CanvasBL
{
public:
    CanvasBL() = delete;
    CanvasBL(string fn1, string fn2);
    //CanvasBL(string hm, string tpm);

    HeightsMap& getHeightsMap();
    TriPolArray& getTriPolArray();
private:
    string strFromFile(string file_name);

private:
    HeightsMap heights_map;
    TriPolArray tri_pol_mas;

};

#endif // CANVASBL_H
