#pragma once


template<class T>
class TwoDimensionalArray
{
public:
    TwoDimensionalArray() = delete;
    TwoDimensionalArray(int dim1Size, int dim2Size)
    {   
        _dim1Size = dim1Size;
        _dim2Size = dim2Size;
        _array = new T*[dim1Size];
        for (int i = 0; i < dim1Size; i++)
        {
            _array[i] = new T[dim2Size];
        }
    }
    ~TwoDimensionalArray()
    {
        for (int i = 0; i < _dim1Size; i++)
        {
            delete[] _array[i];
        }
        delete[] _array;
    }
    T* operator[](int index)
    {
        return _array[index];
    }
    const T* operator[](int index) const
    {
        return _array[index];
    }
    int Size(bool firstDimension = true)
    {
        if (firstDimension)
        {
            return _dim1Size;
        }
        else
        {
            return _dim2Size;
        }
    }
private:
    int _dim1Size, _dim2Size;
    T** _array;
};