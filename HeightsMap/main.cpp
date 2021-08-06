#include <iostream>
#include <iterator>

using namespace std;

//#include "constiterator.h"
#include "heightsmap.h"
#include "heightsmappoints.h"
#include "triangularpolygon.h"

int main()
{
    try
    {
        cout << "CONSTRUCTORS TESTS:" << endl;

        HeightsMap empty_map;
        cout << "empty_map: " << empty_map << endl;

        cout << endl;

        HeightsMap zero_map(4);
        cout << "zero_map: " << zero_map << endl;

        cout << "METHODS TESTS:" << endl;

        zero_map.randomizeHeightsMap();
        cout << "randomizeHeightsMap: " << zero_map << endl;

        zero_map.smoothHeightsMap();
        cout << "smoothHeightsMap: " << zero_map << endl;

        zero_map.diamondSquare();
        cout << "diamondSquare: " << zero_map << endl;

        //cout << endl;

        cout << "ITERATOR TESTS:" << endl;
        ConstIterator<height_t> it1 = zero_map.cbegin();
        ConstIterator<height_t> it2 = zero_map.cend();
        ConstIterator<height_t> it3;
        //Iterator<int> it3;
        it3 = it1;
        cout << "it3 = it1; *it3 = " << *it1 << endl;
        it3++;
        cout << "it3++; *it1 = " << *it1 << "; *it3 = " << *it3 << endl;

        cout << endl;

        cout << "OPERATORS TESTS:" << endl;
        cout << "zero_map[0] = " << zero_map[0] << endl;
        cout << "zero_map[6] = " << zero_map[6] << endl;

        cout << endl;

        cout << "zero_map(0, 0) = " << zero_map(0, 0) << endl;
        cout << "zero_map(1, 2) = " << zero_map(1, 2) << endl;
        //cout << "zero_map(3, 5) = " << zero_map(3, 5) << endl;
        zero_map(1, 2) = 50;
        cout << "zero_map(1, 2) = " << zero_map(1, 2)  << endl;

        cout << endl;

        const HeightsMap zero_map2(5);
        cout << "const zero_map2: " << zero_map2 << endl;
        cout << "const zero_map2(0, 0) = " << zero_map2(0, 0) << endl;
        cout << "const zero_map2(4, 4) = " << zero_map2(4, 4) << endl;
        //cout << "const zero_map2(4, 5) = " << zero_map2(4, 5) << endl;

        cout << endl;

        cout << "HEIGHTSMAPPOINTS TESTS:" << endl;

        HeightsMapPoints points1(4);
        cout << "points1: " << points1 << endl;

        shared_ptr<HeightsMapPoints> points2 = zero_map.createPoints();
        cout << "zero_map.createPoints(): " << (*points2) << endl;

        shared_ptr<HeightsMapPoints> points3 = zero_map.createPoints(15, 7, 15);
        cout << "zero_map.createPoints(15, 7, 15): " << (*points3) << endl;

        points3->transform(Point(100, 50, -50), Point(1, 1, 1), Point(0, 0, 0));
        cout << "points3 move(100, 50, -50): " << (*points3) << endl;

        points3->transform(Point(0, 0, 0), Point(1, 1, 1), Point(1244, 345, 537));
        cout << "points3 rotate(1244, 345, 537): " << (*points3)
             << "Works correctly only in Debug" << endl;

        /*cout << "zero_map[0][0] = " << zero_map[0][0] << endl;
        cout << "zero_map[1][2] = " << zero_map[1][2] << endl;
        cout << "zero_map[3][5] = " << zero_map[3][5]
             << " can't check if shared_ptr<height_t[]> out of range" << endl;

        cout << endl;

        const HeightsMap zero_map2(5);
        cout << "const zero_map2: " << zero_map2 << endl;
        cout << "const zero_map2[0][0] = " << zero_map2[0][0] << endl;
        cout << "const zero_map2[4][5] = " << zero_map2[4][5]
             << " can't check if shared_ptr<height_t[]> out of range" << endl;*/

        cout << endl;

        cout << "TRIANGULARPOLYGON TESTS:" << endl;

        TriangularPolygon tp1(Point(0, 0, 0), Point(0, 5, 0), Point(5, 0, 0));
        TriangularPolygon tp2(Point(5, 0, 0), Point(0, 5, 0), Point(0, 0, 0));
        TriangularPolygon tp3(Point(0, 0, 0), Point(0, 5, 5), Point(5, 5, 0));

        cout << endl;

        cout << "tp1.getZ(124, 25)" << tp1.getZ(124, 25) << endl;
        cout << "tp3.getZ(0, 1) = " << tp3.getZ(0, 1) << endl;
        cout << "tp3.getZ(1, 1) = "<< tp3.getZ(1, 1) << endl;
        cout << "tp3.getZ(1, 0) = "<< tp3.getZ(1, 0) << endl;

        cout << endl;

        cout << "tp3.isInRect(0, 0) = " << tp3.isInRect(0, 0) << endl;
        cout << "tp3.isInRect(5, 5) = " << tp3.isInRect(5, 5) << endl;
        cout << "tp3.isInRect(6, 5) = " << tp3.isInRect(6, 5) << endl;
        cout << "tp3.isInRect(3, 0) = " << tp3.isInRect(3, 0) << endl;

        cout << endl;

        cout << "tp3.isInTriangle(0, 0) = " << tp3.isInTriangle(0, 0) << endl;
        cout << "tp3.isInTriangle(5, 5) = " << tp3.isInTriangle(5, 5) << endl;
        cout << "tp3.isInTriangle(6, 5) = " << tp3.isInTriangle(6, 5) << endl;
        cout << "tp3.isInTriangle(3, 0) = " << tp3.isInTriangle(3, 0) << endl;

        tp3.getMaxX();
    }
    catch (BaseError& err)
    {
        cout << err.what() << endl;
    }
    catch (...)
    {
        cout << "Unexpected Error" << endl;
    }
    cout << "\n-------------------\nEverything is Ok!!!" << endl;
    return 0;
}
