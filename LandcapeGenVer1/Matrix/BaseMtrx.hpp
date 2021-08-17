#ifndef BASEMTRX_HPP
#define BASEMTRX_HPP

#include "BaseMtrx.h"

template<typename Type>
BaseMtrx<Type>::BaseMtrx()
{
    size = 0;
    elems_num = 0;
    alloc_data();
}

template<typename Type>
BaseMtrx<Type>::BaseMtrx(int new_size)
{
    time_t t_time = time(NULL);
    if (new_size < 0)
        throw MtrxNegativeSizeError("new_size < 0", __FILE__, __LINE__, ctime(&t_time));

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

        for (auto &elem:*this)
            elem = Type();
    }
}

template<typename Type>
bool BaseMtrx<Type>::isEmpty() const noexcept
{
    return !elems_num;
}

template<typename Type>
int BaseMtrx<Type>::getSize() const noexcept
{
    return size;
}

template<typename Type>
int BaseMtrx<Type>::elemsNum() const noexcept
{
    return elems_num;
}

template<typename Type>
Iterator<Type> BaseMtrx<Type>::begin() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
Iterator<Type> BaseMtrx<Type>::end() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> BaseMtrx<Type>::cbegin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> BaseMtrx<Type>::cend() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> BaseMtrx<Type>::begin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> BaseMtrx<Type>::end() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
Type &BaseMtrx<Type>::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw MtrxIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
const Type &BaseMtrx<Type>::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw MtrxIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
Type &BaseMtrx<Type>::operator [](int id)
{
    return getElem(id);
}

template<typename Type>
const Type &BaseMtrx<Type>::operator [](int id) const
{
    return getElem(id);
}

template<typename Type>
Type &BaseMtrx<Type>::getElem(int i, int j)
{
    return getElem(i*size+j);
}

template<typename Type>
const Type &BaseMtrx<Type>::getElem(int i, int j) const
{
    return getElem(i*size+j);
}

template<typename Type>
Type &BaseMtrx<Type>::operator()(int i, int j)
{
    return getElem(i*size+j);
}

template<typename Type>
const Type &BaseMtrx<Type>::operator()(const int &i, const int &j) const
{
    return getElem(i*size+j);
}

template<typename Type>
void BaseMtrx<Type>::alloc_data()
{
    data_ptr.reset();
    if (elems_num != 0)
    {
        shared_ptr<Type[]> new_ptr(new Type[elems_num]);

        time_t t_time = time(NULL);
        if (!new_ptr)
            throw MtrxAllocError("Allocationg data_ptr error", __FILE__, __LINE__, ctime(&t_time));

        data_ptr = new_ptr;
    }
}

#endif // BASEMTRX_HPP
