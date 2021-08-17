#ifndef MTRX_H
#define MTRX_H

#include <memory>
#include <iostream>
#include <time.h>

using namespace std;

#include "AbstractMtrx.h"
#include "Iterator/Iterator.hpp"
#include "Iterator/ConstIterator.hpp"
#include "Errors/MtrxErrors.h"

template<typename Type>
class Mtrx : public AbstractMtrx
{
public:
    Mtrx();
    explicit Mtrx(int new_size);

    virtual ~AbstractMtrx() = default;

    virtual bool isEmpty() const noexcept;
    virtual int getSize() const noexcept;
    virtual int elemsNum() const noexcept;

    Iterator<Type> begin() noexcept;
    Iterator<Type> end() noexcept;
    ConstIterator<Type> cbegin() const noexcept;
    ConstIterator<Type> cend() const noexcept;
    ConstIterator<Type> begin() const noexcept;
    ConstIterator<Type> end() const noexcept;

    Type& getElem(int id);
    const Type& getElem(int id) const;
    Type& operator [](int id);
    const Type& operator [](int id) const;

    //Done instead of operator[][]
    Type& getElem(int i, int j);
    const Type& getElem(int i, int j) const;
    Type& operator()(int i, int j);
    const Type& operator()(const int &i, const int &j) const;

protected:
    virtual void alloc_data();

protected:
    shared_ptr<Type[]> data_ptr;
};

template<typename Type>
Mtrx<Type>::Mtrx()
{
    size = 0;
    elems_num = 0;
    alloc_data();
}

template<typename Type>
Mtrx<Type>::Mtrx(int new_size)
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
            elem = 0;
    }
}

template<typename Type>
bool Mtrx<Type>::isEmpty() const noexcept
{
    return !elems_num;
}

template<typename Type>
int Mtrx<Type>::getSize() const noexcept
{
    return size;
}

template<typename Type>
int Mtrx<Type>::elemsNum() const noexcept
{
    return elems_num;
}

template<typename Type>
Iterator<Type> Mtrx<Type>::begin() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
Iterator<Type> Mtrx<Type>::end() noexcept
{
    return Iterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> Mtrx<Type>::cbegin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> Mtrx<Type>::cend() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
ConstIterator<Type> Mtrx<Type>::begin() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, 0);
}

template<typename Type>
ConstIterator<Type> Mtrx<Type>::end() const noexcept
{
    return ConstIterator<Type>(data_ptr, elems_num, elems_num);
}

template<typename Type>
Type &Mtrx<Type>::getElem(int id)
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw MtrxIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
const Type &Mtrx<Type>::getElem(int id) const
{
    time_t t_time = time(NULL);
    if (id < 0 || id >= elems_num)
        throw MtrxIndexError("id", __FILE__, __LINE__, ctime(&t_time));

    return data_ptr[id];
}

template<typename Type>
Type &Mtrx<Type>::operator [](int id)
{
    return getElem(id);
}

template<typename Type>
const Type &Mtrx<Type>::operator [](int id) const
{
    return getElem(id);
}

template<typename Type>
Type &Mtrx<Type>::getElem(int i, int j)
{
    return getElem(i*size+j);
}

template<typename Type>
const Type &Mtrx<Type>::getElem(int i, int j) const
{
    return getElem(i*size+j);
}

template<typename Type>
Type &Mtrx<Type>::operator()(int i, int j)
{
    return getElem(i*size+j);
}

template<typename Type>
const Type &Mtrx<Type>::operator()(const int &i, const int &j) const
{
    return getElem(i*size+j);
}

template<typename Type>
void Mtrx<Type>::alloc_data()
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

#endif // MTRX_H
