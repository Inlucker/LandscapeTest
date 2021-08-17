#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include "ConstIterator.h"

template<typename Type>
ConstIterator<Type>::ConstIterator()// : BaseIterator<Type>()
{
}

template<typename Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type> &it) : BaseIterator<Type>(it)
{
    /*this->id = it.id;
    this->elems_num = it.elems_num;
    this->data_ptr = it.data_ptr;*/
}

template<typename Type>
ConstIterator<Type>::ConstIterator(shared_ptr<Type[]> ptr, int num, int index) : BaseIterator<Type>(ptr, num, index)
{
}

/*template<typename Type>
ConstIterator<Type>::ConstIterator(const Vector<Type> &vec, int index) : BaseIterator<Type>(vec, index)
{
}*/

#endif // CONSTITERATOR_HPP
