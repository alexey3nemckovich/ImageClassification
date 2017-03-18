#include "stdafx.h"
#include "DecisionFunction.h"


DecisionFunction::DecisionFunction(DecisionFunctionWeightVector weightVector)
{
    _weightVector = weightVector;
}


DecisionFunction::~DecisionFunction()
{

}


CString DecisionFunction::ToString()
{
    CString res;
    res.Format("(%d)*x1 + (%d)*x2 + (%d)", _weightVector.x, _weightVector.y, _weightVector.z);
    return res;
}