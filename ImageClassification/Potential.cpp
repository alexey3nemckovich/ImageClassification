#include "stdafx.h"
#include "Potential.h"


Potential::Potential(CPoint p, bool initVaue/* = false*/)
{
    SetCoefficients(p);
    _initValue = initVaue;
}


Potential::Potential(int *cf, bool initValue/* = false*/)
{
    _cf[0] = cf[0];
    _cf[1] = cf[1];
    _cf[2] = cf[2];
    _cf[3] = cf[3];
    _initValue = initValue;
}


Potential::~Potential()
{
}


int Potential::GetValue(CPoint p)
{
    if (_initValue)
    {
        return 0;
    }
    else
    {
        return _cf[0] + _cf[1] * p.x + _cf[2] * p.y + _cf[3] * p.x * p.y;
    }
}


double Potential::GetValue(LogicPoint lp)
{
    if (_initValue)
    {
        return 0;
    }
    else
    {
        return _cf[0] + _cf[1] * lp.x + _cf[2] * lp.y + _cf[3] * lp.x * lp.y;
    }
}


double Potential::GetValue(double x)
{
    return (-_cf[1] * x - _cf[0])/(_cf[2] + _cf[3] * x);
}


void Potential::SetCoefficients(CPoint p)
{
    _cf[0] = 1;
    _cf[1] = 4 * p.x;
    _cf[2] = 4 * p.y;
    _cf[3] = 16 * p.x * p.y;
}