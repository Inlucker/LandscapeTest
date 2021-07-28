#ifndef ITERATOR_H
#define ITERATOR_H

#include "baseiterator.hpp"

using namespace std;

template<typename Type>
class Iterator:public BaseIterator<Type>
{
public:
    Iterator();
    virtual ~Iterator() = default;
    Iterator(const Iterator<Type>& it); //copy

    explicit Iterator(shared_ptr<Type[]> ptr, int num, int index = 0);
    //explicit Iterator(const Vector<Type>& vec, int index = 0); //init

    Type& operator *();

    Type& operator [](int index); //add const

    Type* operator ->();
protected:
    /*weak_ptr<Type[]> data_ptr;
    bool check_ptr(int line) const;
    Type& cur_elem() const;
    weak_ptr<Type[]> get_data_ptr() const;*/
};

#endif // ITERATOR_H
