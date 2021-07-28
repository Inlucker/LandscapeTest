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

        cout << endl;

        cout << "ITERATOR TESTS:" << endl;
        ConstIterator<height_t> it1 = zero_map.cbegin();
        ConstIterator<height_t> it2 = zero_map.cend();
        ConstIterator<height_t> it3;
        //Iterator<int> it3;
        it3 = it1;
        cout << "it3 = it1; *it3 = " << *it1 << endl;
        it3++;
        cout << "it3++; *it1 = " << *it1 << "; *it3 = " << *it3 << endl;
    }
    catch (BaseError& err)
    {
        cout << err.what() << endl;
    }
    catch (...)
    {
        cout << "Unexpected Error" << endl;
    }
    return 0;
}
