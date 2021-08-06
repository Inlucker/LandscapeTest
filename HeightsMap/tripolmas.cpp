#include "tripolmas.h"

#include "iterator.hpp"
#include "constiterator.hpp"
#include "errors.h"
#include "triangularpolygon.h"

TriPolMas::TriPolMas()
{
    elems_num = 0;
}

TriPolMas::TriPolMas(int elements_number)
{
    time_t t_time = time(NULL);
    if (elements_number < 0)
        throw TriPolMasNegativeSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

    if (elements_number == 0)
    {
        elems_num = 0;
        data_ptr.reset();
    }
    else
    {
        elems_num = elements_number;
        alloc_data();
    }
}

bool TriPolMas::isEmpty() const noexcept
{
    return !elems_num;
}

int TriPolMas::size() const noexcept
{
    return elems_num;
}

Iterator<TriangularPolygon> TriPolMas::begin() noexcept
{
    return Iterator<TriangularPolygon>(data_ptr, elems_num, 0);
}

Iterator<TriangularPolygon> TriPolMas::end() noexcept
{
    return Iterator<TriangularPolygon>(data_ptr, elems_num, elems_num);
}

ConstIterator<TriangularPolygon> TriPolMas::cbegin() const noexcept
{
    return ConstIterator<TriangularPolygon>(data_ptr, elems_num, 0);
}

ConstIterator<TriangularPolygon> TriPolMas::cend() const noexcept
{
    return ConstIterator<TriangularPolygon>(data_ptr, elems_num, elems_num);
}

TriangularPolygon& TriPolMas::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw TriPolMasIndexError("id", __FILE__, __LINE__, ctime(&t_time));
    return data_ptr[id];
}

const TriangularPolygon& TriPolMas::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw TriPolMasIndexError("id", __FILE__, __LINE__, ctime(&t_time));
    return data_ptr[id];
}

TriangularPolygon& TriPolMas::operator [](int id)
{
    return getElem(id);
}

const TriangularPolygon& TriPolMas::operator [](int id) const
{
    return getElem(id);
}

void TriPolMas::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<TriangularPolygon[]> new_ptr(new TriangularPolygon[elems_num]);
        //shared_ptr<HeightsArray[]> new_ptr(new HeightsArray[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw TriPolMasAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}

ostream& operator <<(ostream& os, const TriPolMas& mas)
{
    if (mas.isEmpty())
    {
        os << "TriPolMas is empty." << endl;
        return os;
    }

    ConstIterator<TriangularPolygon> It = mas.cbegin();
    os << '[' << *It++;
    for (; It != mas.cend(); It++)
        os << "; \n" << *It ;
    os << ']' << endl;
    return os;
}
