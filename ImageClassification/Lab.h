#pragma once
#include "Labs.h"


class Lab
{
public:
    Lab()
    {
        srand(time(NULL));
    }
    virtual ~Lab() = default;
    virtual int GetNumber() = 0;
};