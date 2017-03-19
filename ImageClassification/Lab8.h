#pragma once
#include "Lab.h"
#include "ChainGrammar.h"


#define LAB8 8


class Lab8
    : public Lab
{
public:
    Lab8()
    {
        Labs::GetInstance()->SetActive(GetNumber());
    }
    virtual ~Lab8() = default;
    int GetNumber()
    {
        return LAB8;
    }
    ChainGrammar GetGrammar(vector<string> chains)
    {
        return ChainGrammar(chains);
    }
};