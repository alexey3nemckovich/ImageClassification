#include "stdafx.h"
#include "Perceptron.h"
#include <algorithm>


Perceptron::Perceptron()
{

}


Perceptron::~Perceptron()
{

}


vector<Perceptron::DecisionFunction> Perceptron::GetDecisionFunctions(vector<SignVector> decisiveSamples, vector<SignVector> decFuncWeights)
{
    int cCount = decisiveSamples.size();
    vector<double> decFuncValues(cCount);
    vector<bool> correctFlag(cCount);
    bool noCorrections;
    do
    {
        noCorrections = true;
        for (int i = 0; i < cCount; i++)
        {
            correctFlag[i] = true;
            bool singleMaxValue = true;
            int maxFuncValueIndex = 0;
            for (int k = 0; k < cCount; k++)
            {
                decFuncValues[k] = decFuncWeights[k] * decisiveSamples[i];
                if (decFuncValues[k] > decFuncValues[maxFuncValueIndex])
                {
                    maxFuncValueIndex = k;
                }
                else if (k != maxFuncValueIndex && decFuncValues[k] == decFuncValues[maxFuncValueIndex])
                {
                    singleMaxValue = false;
                }
            }
            if (i != maxFuncValueIndex || !singleMaxValue)
            {
                correctFlag[i] = false;
                CorrectCoefficients(i, decFuncValues, decisiveSamples, decFuncWeights, maxFuncValueIndex);
            }
        }
        noCorrections = AllCorrect(correctFlag);
    } while (!noCorrections);
    vector<DecisionFunction> decisionFunctions;
    for (int i = 0; i < cCount; i++)
    {
        decisionFunctions.push_back(DecisionFunction(decFuncWeights[i]));
    }
    return decisionFunctions;
}


bool Perceptron::AllCorrect(vector<bool> correctFlag)
{
    for (int i = 0; i < correctFlag.size(); i++)
    {
        if (!correctFlag[i])
        {
            return false;
        }
    }
    return true;
}


Perceptron::SignVector::SignVector(vector<double> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        push_back(v[i]);
    }
}


Perceptron::SignVector* Perceptron::SignVector::operator+=(const Perceptron::SignVector& other)
{
    for (int i = 0; i < other.size(); i++)
    {
        (*this)[i] += other[i];
    }
    return this;
}


Perceptron::SignVector* Perceptron::SignVector::operator-=(const Perceptron::SignVector& other)
{
    for (int i = 0; i < other.size(); i++)
    {
        (*this)[i] -= other[i];
    }
    return this;
}


Perceptron::SignVector* Perceptron::SignVector::operator+=(double value)
{
    for (int i = 0; i < size(); i++)
    {
        (*this)[i] += value;
    }
    return this;
}


Perceptron::SignVector* Perceptron::SignVector::operator-=(double value)
{
    for (int i = 0; i < size(); i++)
    {
        (*this)[i] -= value;
    }
    return this;
}


Perceptron::SignVector Perceptron::SignVector::operator=(const Perceptron::SignVector& other)
{
    clear();
    vector<double>::operator=(other);
    return *this;
}


double Perceptron::SignVector::operator*(const Perceptron::SignVector& other)
{
    double res = 0;
    for (int i = 0; i < other.size(); i++)
    {
        res += (*this)[i] * other[i];
    }
    return res;
}


Perceptron::DecisionFunction::DecisionFunction(SignVector signVector)
{
    _signVector = signVector;
}


CString Perceptron::DecisionFunction::ToString()
{
    CString res;
    for (int i = 0; i < _signVector.size(); i++)
    {
        if (_signVector.size() - 1 != i)
        {
            res.Format("%s(%.3lf)*x%d + ", res, _signVector[i], i);
        }
        else
        {
            res.Format("%s(%.3lf)*x%d", res, _signVector[i], i);
        }
    }
    return res;
}