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

//HeightsArray
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

class HeightsArrayNegativeSizeError : public BaseError
{
public:
    HeightsArrayNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create HeightsArray with negative size")
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

//HeightsMap
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

class HeightsMapNegativeSizeError : public BaseError
{
public:
    HeightsMapNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create HeightsMap with negative size")
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

//HeightsMapPoints
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

class HeightsMapPointsNegativeSizeError : public BaseError
{
public:
    HeightsMapPointsNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create HeightsMapPoints with negative size")
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

//ITERATOR
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

//VECTOR
class VectorEmptyError : public BaseError
{
public:
    VectorEmptyError(string info, string filename, int line, const char *time, string error = "Trying to use empty vector")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorNegativeSizeError : public BaseError
{
public:
    VectorNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create vector with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorMemoryError : public BaseError
{
public:
    VectorMemoryError(string info, string filename, int line, const char *time, string error = "Memory error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorIndexError : public BaseError
{
public:
    VectorIndexError(string info, string filename, int line, const char *time, string error = "Index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorDifSizeError : public BaseError
{
public:
    VectorDifSizeError(string info, string filename, int line, const char *time, string error = "Opearation with different sized vectors")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorZeroDivError : public BaseError
{
public:
    VectorZeroDivError(string info, string filename, int line, const char *time, string error = "Division on zero")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class VectorSizeError : public BaseError
{
public:
    VectorSizeError(string info, string filename, int line, const char *time, string error = "Wrong size for vector multiplicationg")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

//TriPolMas
class TriPolMasAllocError : public BaseError
{
public:
    TriPolMasAllocError(string info, string filename, int line, const char *time, string error = "TriPolMas alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class TriPolMasNegativeSizeError : public BaseError
{
public:
    TriPolMasNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create TriPolMas with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class TriPolMasIndexError : public BaseError
{
public:
    TriPolMasIndexError(string info, string filename, int line, const char *time, string error = "HeightsMapPoints index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

//ZBuffer
class ZBufferAllocError : public BaseError
{
public:
    ZBufferAllocError(string info, string filename, int line, const char *time, string error = "ZBuffer alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class ZBufferNegativeSizeError : public BaseError
{
public:
    ZBufferNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create ZBuffer with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class ZBufferIndexError : public BaseError
{
public:
    ZBufferIndexError(string info, string filename, int line, const char *time, string error = "ZBuffer index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

//FrameBuffer
class FrameBufferAllocError : public BaseError
{
public:
    FrameBufferAllocError(string info, string filename, int line, const char *time, string error = "FrameBuffer alloc error")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class FrameBufferNegativeSizeError : public BaseError
{
public:
    FrameBufferNegativeSizeError(string info, string filename, int line, const char *time, string error = "Trying to create FrameBuffer with negative size")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

class FrameBufferIndexError : public BaseError
{
public:
    FrameBufferIndexError(string info, string filename, int line, const char *time, string error = "FrameBuffer index out of range")
        : BaseError(info, filename, line, time, error) {};
    virtual const char* what() const noexcept
    {
        return err_info.c_str();
    }
};

#endif // ERRORS_H
