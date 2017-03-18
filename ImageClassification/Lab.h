#pragma once


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