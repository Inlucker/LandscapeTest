#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <iostream>
#include <memory>

using namespace std;

template<typename Type>
class Iterator;
template<typename Type>
class ConstIterator;

class TriPolMas;

class ZBuffer
{
public:
    ZBuffer();
    ZBuffer(int new_width, int new_height);

    bool isEmpty() const noexcept;
    int size() const noexcept;
    int getWidth() const noexcept;
    int getHeight() const noexcept;

    Iterator<double> begin() noexcept;
    Iterator<double> end() noexcept;
    ConstIterator<double> cbegin() const noexcept;
    ConstIterator<double> cend() const noexcept;

    double& getElem(int id);
    const double& getElem(int id) const;
    double& operator [](int id);
    const double& operator [](int id) const;

    double& getElem(int i, int j);
    const double& getElem(int i, int j) const;
    double& operator()(int i, int j);
    const double& operator()(const int &i, const int &j) const;

private:
    void alloc_data();

private:
    //ZBuffer
    shared_ptr<double[]> data_ptr;
    int width;
    int height;
    int elems_num;
};

ostream& operator <<(ostream& os, const ZBuffer& buf);

#endif // ZBUFFER_H
