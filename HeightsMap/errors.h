#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>

using namespace std;

class BaseError : public exception
{
public:
    BaseError(string info, string filename, int line, const char *time, string error = "Error")
    {
        err_info = "\nError: " + error;
        err_info = err_info + "\nTime: " + time;
        err_info += "File name: " + filename +"\nLine#: " + to_string(line);
        err_info += "\nWhat caused error: " + info;
    }
    virtual const char* what() const noexcept override
    {
        return err_info.c_str();
    }
protected:
    string err_info;
};

class HeightsArrayAllocError : public BaseError
{
public:
    HeightsArrayAllocError(string info, string filename, int line, const char *time, string error = "HeightsArray alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class NegativeArraySizeError : public BaseError
{
public:
    NegativeArraySizeError(string info, string filename, int line, const char *time, string error = "Trying to create HeightsArray with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsArrayIndexError : public BaseError
{
public:
    HeightsArrayIndexError(string info, string filename, int line, const char *time, string error = "HeightsArray index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsMapAllocError : public BaseError
{
public:
    HeightsMapAllocError(string info, string filename, int line, const char *time, string error = "HeightsMap alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class NegativeMapSizeError : public BaseError
{
public:
    NegativeMapSizeError(string info, string filename, int line, const char *time, string error = "Trying to create HeightsMap with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsMapIndexError : public BaseError
{
public:
    HeightsMapIndexError(string info, string filename, int line, const char *time, string error = "HeightsMap index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsMapPointsAllocError : public BaseError
{
public:
    HeightsMapPointsAllocError(string info, string filename, int line, const char *time, string error = "HeightsMapPoints alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class NegativeMapPointsSizeError : public BaseError
{
public:
    NegativeMapPointsSizeError(string info, string filename, int line, const char *time, string error = "Trying to create HeightsMapPoints with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class HeightsMapPointsIndexError : public BaseError
{
public:
    HeightsMapPointsIndexError(string info, string filename, int line, const char *time, string error = "HeightsMapPoints index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class IteratorWeakPtrError : public BaseError
{
public:
    IteratorWeakPtrError(string info, string filename, int line, const char *time, string error = "Iterator weak_ptr error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class IteratorIdError : public BaseError
{
public:
    IteratorIdError(string info, string filename, int line, const char *time, string error = "Iterator id out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

/*class EmptyError : public BaseError
{
public:
    EmptyError(string info, string filename, int line, const char *time, string error = "Trying to use empty vector")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class MemoryError : public BaseError
{
public:
    MemoryError(string info, string filename, int line, const char *time, string error = "Memory error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};


class DifSizeError : public BaseError
{
public:
    DifSizeError(string info, string filename, int line, const char *time, string error = "Opearation with different sized vectors")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class ZeroDivError : public BaseError
{
public:
    ZeroDivError(string info, string filename, int line, const char *time, string error = "Division on zero")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class SizeError : public BaseError
{
public:
    SizeError(string info, string filename, int line, const char *time, string error = "Wrong size for vector multiplicationg")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};*/

#endif // ERRORS_H
