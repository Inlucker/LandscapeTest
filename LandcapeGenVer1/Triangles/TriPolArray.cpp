#include "TriPolArray.h"

#include "TriangularPolygon.h"
#include "HeightsMap/HeightsMapPoints.h"

TriPolArray::TriPolArray()
{

}

TriPolArray::TriPolArray(int new_size) : BaseType(new_size)
{

}

void TriPolArray::update()
{
    for (auto& tri_pol : *this)
        tri_pol.update();
}

/*void TriPolArray::updatePoints(HeightsMapPoints &map)
{
    Iterator<TriangularPolygon> mas_it = this->begin();
    for (int i = 0; i < (map.getSize()-1); i++)
    {
        for (int j = 0; j < (map.getSize()-1); j++)
        {
            if ((j+i) % 2 == 1)
            {
                mas_it->setPoints(map(i, j), map(i, j+1), map(i+1, j));
                mas_it++;
                mas_it->setPoints(map(i+1, j), map(i, j+1), map(i+1, j+1));
                mas_it++;
            }
            else
            {
                mas_it->setPoints(map(i, j), map(i+1, j+1), map(i, j+1));
                mas_it++;
                mas_it->setPoints(map(i, j), map(i+1, j), map(i+1, j+1));
                mas_it++;
            }
        }
    }
}*/
