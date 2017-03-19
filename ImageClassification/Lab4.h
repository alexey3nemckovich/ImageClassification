#pragma once
#include "Lab.h"
#include "DecisionFunction.h"
#include <vector>
using namespace std;


#define LAB4 4


class Lab4
    : public Lab
{
public:
    Lab4()
    {
        Labs::GetInstance()->SetActive(GetNumber());
    }
    virtual ~Lab4();
    vector<DecisionFunction> GetDecisionFunctions(vector<vector<SpacePoint>> decisiveSamples);
    int GetNumber()
    {
        return LAB4;
    }
};