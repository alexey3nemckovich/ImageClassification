#pragma once
#include <algorithm>
#include "Perceptron.h"
#include "Lab.h"
using namespace std;


#define LAB9 9


class Lab9
    : public Lab, public Perceptron
{
public:
    Lab9();
    ~Lab9();
    virtual void CorrectCoefficients(
        int classIndex,
        const vector<double> &decFuncValues,
        const vector<SignVector> &decisiveSamples,
        vector<SignVector> &decFuncWeights,
        int maxClassFuncValueIndex = 0) override;
    virtual int GetNumber() override
    {
        return LAB9;
    }
};