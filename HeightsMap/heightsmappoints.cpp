#include "heightsmappoints.h"

HeightsMapPoints::HeightsMapPoints()
{
    size = 0;
    elems_num = 0;
}

HeightsMapPoints::HeightsMapPoints(int new_size)
{
    time_t t_time = time(NULL);
    if (new_size < 0)
        throw NegativeMapPointsSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

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
    }
}

bool HeightsMapPoints::isEmpty() const noexcept
{
    return !elems_num;
}

int HeightsMapPoints::getSize() const noexcept
{
    return size;
}

int HeightsMapPoints::elemsNum() const noexcept
{
    return elems_num;
}

Iterator<Point> HeightsMapPoints::begin() noexcept
{
    return Iterator<Point>(data_ptr, elems_num, 0);
}

Iterator<Point> HeightsMapPoints::end() noexcept
{
    return Iterator<Point>(data_ptr, elems_num, elems_num);
}

ConstIterator<Point> HeightsMapPoints::cbegin() const noexcept
{
    return ConstIterator<Point>(data_ptr, elems_num, 0);
}

ConstIterator<Point> HeightsMapPoints::cend() const noexcept
{
    return ConstIterator<Point>(data_ptr, elems_num, elems_num);
}

Point &HeightsMapPoints::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw HeightsMapPointsIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

const Point &HeightsMapPoints::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw HeightsMapIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

Point &HeightsMapPoints::operator [](int id)
{
    return getElem(id);
}

const Point &HeightsMapPoints::operator [](int id) const
{
    return getElem(id);
}

Point &HeightsMapPoints::operator()(int i, int j)
{
    return getElem(i*size+j);
}

const Point &HeightsMapPoints::operator()(const int &i, const int &j) const
{
    return getElem(i*size+j);
}

void HeightsMapPoints::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<Point[]> new_ptr(new Point[elems_num]);
        //shared_ptr<HeightsArray[]> new_ptr(new HeightsArray[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw HeightsMapPointsAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}

ostream& operator <<(ostream& os, const HeightsMapPoints& points_map)
{
    if (points_map.isEmpty())
    {
        os << "HeightsMapPoints is empty.";
        return os;
    }

    ConstIterator<Point> It = points_map.cbegin();
    while (It != points_map.cend())
    {
        os << '\n' << '[' << *It++;
        for (int i = 1; i < points_map.getSize() && It != points_map.cend(); It++, i++)
            os << "; " << *It ;
        os << ']';
    }
    cout << endl;

    return os;
}
