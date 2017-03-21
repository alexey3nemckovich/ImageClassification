#include "stdafx.h"
#include "Lab9.h"


Lab9::Lab9()
{
}


Lab9::~Lab9()
{
}


void Lab9::CorrectCoefficients(
    int classIndex,
    const vector<double> &decFuncValues,
    const vector<Perceptron::SignVector> &decisiveSamples,
    vector<Perceptron::SignVector> &decFuncWeights,
    int maxClassFuncValueIndex/* = 0*/)
{
    decFuncWeights[classIndex] += 1 - decFuncValues[classIndex];
    decFuncWeights[maxClassFuncValueIndex] -= decFuncValues[maxClassFuncValueIndex];
}