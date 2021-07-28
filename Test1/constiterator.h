#ifndef CONSTITERATOR_H
#define CONSTITERATOR_H

#include "baseiterator.hpp"

using namespace std;

template<class Type>
class Vector;

template<typename Type>
class ConstIterator:public BaseIterator<Type>
{
public:
    ConstIterator();
    virtual ~ConstIterator() = default;
    ConstIterator(const ConstIterator<Type>& it); //copy

    explicit ConstIterator(shared_ptr<Type[]> ptr, int num, int index = 0);
    //explicit ConstIterator(const Vector<Type>& vec, int index = 0); //init

protected:
    /*weak_ptr<Type[]> data_ptr;
    bool check_ptr(int line) const;
    Type& cur_elem() const;
    weak_ptr<Type[]> get_data_ptr() const;*/
};

#endif // CONSTITERATOR_H
