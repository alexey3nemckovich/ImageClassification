#pragma once
#include <climits>


class Labs
{
public:
    Labs(const Labs&) = delete;
    Labs(const Labs&&) = delete;
    static Labs* GetInstance()
    {
        static Labs labs;
        return &labs;
    }
    void SetActive(int labNumber)
    {
        _active = labNumber;
    }
    int GetActive()
    {
        return _active;
    }
private:
    Labs();
    int _active = INT_MIN;
};