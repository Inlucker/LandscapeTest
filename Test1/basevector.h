#ifndef BASEVECTOR_H
#define BASEVECTOR_H

class BaseVector
{
public:
    BaseVector();
    virtual ~BaseVector() = 0;

    virtual bool is_empty() const = 0;
    virtual int size() const = 0;
protected:
    int elems_num;
};

#endif // BASEVECTOR_H
