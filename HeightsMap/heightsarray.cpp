#include "heightsarray.h"

#include "errors.h"
//#include "heightsmap.h"

HeightsArray::HeightsArray()
{
    elems_num = 0;
    //alloc_data();
}

HeightsArray::HeightsArray(int new_size)
{
    time_t t_time = time(NULL);
    if (new_size < 0)
        throw NegativeArraySizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_size == 0)
    {
        elems_num = 0;
        data_ptr.reset();
    }
    else
    {
        elems_num = new_size;
        alloc_data();

        for (auto &elem:*this)
            elem = 0;
    }
}

/*HeightsArray::HeightsArray(HeightsMap& map, int id)
{
    int new_size = map.getSize();
    time_t t_time = time(NULL);
    if (new_size < 0)
        throw NegativeMapSizeError("map.getSize() < 0", __FILE__, __LINE__, ctime(&t_time));

    if (new_size == 0)
    {
        elems_num = 0;
        data_ptr.reset();
    }
    else
    {
        elems_num = new_size;
        alloc_data();

        for (auto &elem:*this)
        {
            elem = 0;
        }
        Iterator<height_t> arr_it = begin();
        int i = 0;
        for (auto& elem : map)
        {
            if (i/elems_num == id)
            {
                *arr_it = elem;
                arr_it++;
            }
            i++;
        }
    }
}*/

/*HeightsArray::HeightsArray(const HeightsArray &arr)
{
    time_t t_time = time(NULL);
    if (arr.size() < 0)
        throw NegativeArraySizeError("arr elements_number < 0", __FILE__, __LINE__, ctime(&t_time));
    elems_num = arr.size();

    alloc_data();

    for (int i = 0; i < elems_num; i++)
        data_ptr[i] = arr[i];
}*/

bool HeightsArray::isEmpty() const noexcept
{
    return !elems_num;
}

int HeightsArray::size() const noexcept
{
    return elems_num;
}

Iterator<height_t> HeightsArray::begin() noexcept
{
    return Iterator<height_t>(data_ptr, elems_num, 0);
}

Iterator<height_t> HeightsArray::end() noexcept
{
    return Iterator<height_t>(data_ptr, elems_num, elems_num);
}

ConstIterator<height_t> HeightsArray::cbegin() const noexcept
{
    return ConstIterator<height_t>(data_ptr, elems_num, 0);
}

ConstIterator<height_t> HeightsArray::cend() const noexcept
{
    return ConstIterator<height_t>(data_ptr, elems_num, elems_num);
}

height_t &HeightsArray::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw HeightsArrayIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

const height_t& HeightsArray::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw HeightsArrayIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

height_t& HeightsArray::operator [](int id)
{
    return getElem(id);
}

const height_t &HeightsArray::operator [](int id) const
{
    return getElem(id);
}

void HeightsArray::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<height_t[]> new_ptr(new height_t[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw HeightsArrayAllocError("Allocationg data_ptr for HeightsArray error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}


ostream& operator <<(ostream& os, const HeightsArray& arr)
{
    if (arr.isEmpty())
    {
        os << "HeightsArr is empty." << endl;
        return os;
    }

    ConstIterator<height_t> It = arr.cbegin();
    os << '[' << *It++;
    for (; It != arr.cend(); It++)
        os << "; " << *It ;
    os << ']' << endl;

    return os;
}
