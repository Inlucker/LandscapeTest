#include <iostream>
#include <iterator>

using namespace std;

//#include "constiterator.h"
#include "heightsmap.h"

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

        zero_map.randomizeHeightsMap();
        cout << "randomizeHeightsMap: " << zero_map << endl;

        zero_map.smoothHeightsMap();
        cout << "smoothHeightsMap: " << zero_map << endl;

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
