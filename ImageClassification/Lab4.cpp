#include "stdafx.h"
#include "Lab4.h"


Lab4::Lab4()
{

}


Lab4::~Lab4()
{

}


vector<DecisionFunction> Lab4::GetDecisionFunctions(vector<vector<SpacePoint>> decisiveSamples)
{
    int cCount = decisiveSamples.size();
    vector<DecisionFunctionWeightVector> decisionFunctionsWeights(cCount);
    vector<int> correctCounter(cCount);
    bool decisionFunctionCorrect;
    do
    {
        decisionFunctionCorrect = true;
        for (int i = 0; i < cCount; i++)
        {
            correctCounter[i] = 0;
            for (int j = 0; j < decisiveSamples[i].size(); j++)
            {
                int maxDecisionFunctionIndex = INT_MIN;
                int maxDecisionFunctionValue = INT_MIN;
                int value;
                for (int k = 0; k < cCount; k++)
                {
                    if ((value = decisionFunctionsWeights[k] * decisiveSamples[i][j]) >= maxDecisionFunctionValue)
                    {
                        maxDecisionFunctionValue = value;
                        maxDecisionFunctionIndex = k;
                    }
                }
                if (maxDecisionFunctionIndex == i)
                {
                    correctCounter[i]++;
                }
                else
                {
                    for (int k = 0; k < cCount; k++)
                    {
                        if (k != i)
                        {
                            decisionFunctionsWeights[k] -= decisiveSamples[i][j];
                        }
                        else
                        {
                            decisionFunctionsWeights[k] += decisiveSamples[i][j];
                        }
                    }
                }
            }
        }
        for (int i = 0; i < cCount; i++)
        {
            if (correctCounter[i] != decisiveSamples[i].size())
            {
                decisionFunctionCorrect = false;
                break;
            }
        }
    } while (!decisionFunctionCorrect);
    vector<DecisionFunction> decisionFunctions;
    for (int i = 0; i < cCount; i++)
    {
        decisionFunctions.push_back(DecisionFunction(decisionFunctionsWeights[i]));
    }
    return decisionFunctions;
}