#pragma once
#include <vector>
using namespace std;


class Perceptron
{
public:
    //inner classes
    class SignVector
        : public vector<double>
    {
    public:
        SignVector(int len) : vector<double>(len) {};
        SignVector() : vector<double>() {};
        SignVector(vector<double>);
    public:
        //operators
        SignVector* operator+=(const SignVector &other);
        SignVector* operator-=(const SignVector &other);
        SignVector* operator+=(double);
        SignVector* operator-=(double);
        SignVector  operator=(const SignVector &other);
        double      operator*(const SignVector &other);
    };
    class DecisionFunction
    {
    public:
        DecisionFunction(SignVector signVector);
        ~DecisionFunction() = default;
        CString ToString();
    private:
        SignVector _signVector;
    };
public:
    //main interface
    Perceptron();
    virtual ~Perceptron();
    vector<DecisionFunction> GetDecisionFunctions(vector<SignVector> decisiveSamples, vector<SignVector> weightCoefficients);
protected:
    virtual void CorrectCoefficients(
        int classIndex,
        const vector<double> &decisionFunctionsValues,
        const vector<SignVector> &decisiveSamples,
        vector<SignVector> &desicionFunctionsWeights,
        int maxClassFuncValueIndex = 0) = 0;
private:
    bool AllCorrect(vector<bool> correctFlag);
};