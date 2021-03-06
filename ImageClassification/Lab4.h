#pragma once
#include <vector>
#include <algorithm>
#include "Lab.h"
#include "Perceptron.h"
using namespace std;


#define LAB4 4


class Lab4
    : public Lab, public Perceptron
{
public:
    Lab4()
    {
        Labs::GetInstance()->SetActive(GetNumber());
    }
    virtual ~Lab4();
    virtual void CorrectCoefficients(
        int classIndex,
        const vector<double> &decFuncValues,
        const vector<SignVector> &decisiveSamples,
        vector<SignVector> &decFuncWeights,
        int maxClassFuncValueIndex = 0) override;
    int GetNumber()
    {
        return LAB4;
    }
};