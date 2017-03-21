#pragma once
#include "Perceptron.h"


class DecisionFunction
{
public:
    DecisionFunction(DecisionFunctionWeightVector weightVector);
    ~DecisionFunction();
    CString ToString();
private:
    DecisionFunctionWeightVector _weightVector;
};