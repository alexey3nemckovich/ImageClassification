#include "stdafx.h"
#include "Lab4.h"


Lab4::~Lab4()
{

}


void Lab4::CorrectCoefficients(
    int classIndex,
    const vector<double> &decFuncValues,
    const vector<Perceptron::SignVector> &decisiveSamples,
    vector<Perceptron::SignVector> &decFuncWeights,
    int maxClassFuncValueIndex/* = 0*/)
{
    for (int i = 0; i < decFuncWeights.size(); i++)
    {
        if (classIndex != i)
        {
            decFuncWeights[i] -= decisiveSamples[classIndex];
        }
        else
        {
            decFuncWeights[i] += decisiveSamples[classIndex];
        }
    }
}