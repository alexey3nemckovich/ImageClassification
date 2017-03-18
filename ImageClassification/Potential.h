#pragma once
#include <memory>
using namespace std;


class Potential
{
public:
    typedef shared_ptr<Potential> Ptr;
    Potential(CPoint p, bool initVaue = false);
    ~Potential();
    int GetValue(CPoint p);
    double GetValue(LogicPoint p);
    double GetValue(double x);
    Potential operator+(const Potential& other)
    {
        Potential sum(_cf, _initValue);
        sum._cf[0] = _cf[0] + other._cf[0];
        sum._cf[1] = _cf[1] + other._cf[1];
        sum._cf[2] = _cf[2] + other._cf[2];
        sum._cf[3] = _cf[3] + other._cf[3];
        return sum;
    }
    Potential operator-(const Potential& other)
    {
        Potential sum(_cf, _initValue);
        sum._cf[0] = _cf[0] - other._cf[0];
        sum._cf[1] = _cf[1] - other._cf[1];
        sum._cf[2] = _cf[2] - other._cf[2];
        sum._cf[3] = _cf[3] - other._cf[3];
        return sum;
    }
private:
    Potential(int *cf, bool initValue = false);
    void SetCoefficients(CPoint p);
    bool _initValue;
    int _cf[4];
};