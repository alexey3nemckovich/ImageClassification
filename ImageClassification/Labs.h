#pragma once


#include "Lab3.h"
#include "Lab4.h"
#include "Lab5.h"
#include "Lab6.h"
#include "Lab7.h"
#include "Lab8.h"
#include "Lab3InputDlg.h"
#include "Lab4InputDlg.h"
#include "Lab5InputDlg.h"
#include "Lab6InputDlg.h"
#include "Lab7InputDlg.h"
#include "Lab8InputDlg.h"


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