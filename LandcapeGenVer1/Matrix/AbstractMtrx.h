#ifndef ABSTRACTMTRX_H
#define ABSTRACTMTRX_H

class AbstractMtrx
{
public:
    AbstractMtrx();
    virtual ~AbstractMtrx() = 0;

    virtual bool isEmpty() const noexcept = 0;
    virtual int getSize() const noexcept = 0;
    virtual int elemsNum() const noexcept = 0;

protected:
    virtual void alloc_data() = 0;

protected:
    int size = -1;
    int elems_num = -1;
};

#endif // ABSTRACTMTRX_H
