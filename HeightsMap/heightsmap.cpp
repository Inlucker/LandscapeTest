#include "heightsmap.h"

#include <time.h>

//#include "errors.h"

HeightsMap::HeightsMap()
{
    size = 0;
    elems_num = 0;
    alloc_data();
}

HeightsMap::HeightsMap(int new_size)
{
    time_t t_time = time(NULL);
    if (new_size < 0)
        throw NegativeMapSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_size == 0)
    {
        size = 0;
        elems_num = 0;
        data_ptr.reset();
    }
    else
    {
        size = new_size;
        elems_num = size*size;
        alloc_data();

        //for each
        for (auto &elem:*this)
            elem = 0;
        /*for (Iterator<Type> It = this->begin(); It != this->end(); ++It)
            *It = 0;*/
    }
}

bool HeightsMap::isEmpty() const noexcept
{
    return !elems_num;
}

int HeightsMap::getSize() const noexcept
{
    return size;
}

Iterator<height_t> HeightsMap::begin() noexcept
{
    return Iterator<height_t>(data_ptr, elems_num, 0);
}

Iterator<height_t> HeightsMap::end() noexcept
{
    return Iterator<height_t>(data_ptr, elems_num, elems_num);
}

ConstIterator<height_t> HeightsMap::cbegin() const noexcept
{
    return ConstIterator<height_t>(data_ptr, elems_num, 0);
}

ConstIterator<height_t> HeightsMap::cend() const noexcept
{
    return ConstIterator<height_t>(data_ptr, elems_num, elems_num);
}

void HeightsMap::alloc_data()
{
    data_ptr.reset();
    if (size != 0)
    {
        shared_ptr<height_t[]> new_ptr(new height_t[size*size]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw HeightsMapAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}


ostream& operator <<(ostream& os, const HeightsMap& map)
{
    if (map.isEmpty())
    {
        os << "HeightsMap is empty.";
        return os;
    }

    ConstIterator<height_t> It = map.cbegin();
    while (It != map.cend())
    {
        os << '\n' << '(' << *It++;
        for (int i = 1; i < map.getSize() && It != map.cend(); It++, i++)
            os << ", " << *It ;
        os << ')';
    }
    cout << endl;

    return os;
}
