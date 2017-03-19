#include "stdafx.h"
#include "Lab5.h"


Lab5::~Lab5()
{

}


Potential Lab5::GetPotentialFunction(vector<CPoint> c1, vector<CPoint> c2)
{
    Potential::Ptr potential = Potential::Ptr(new Potential(c1[0]));
    int nc1 = c1.size(), nc2 = c2.size();
    int pNumber = 0;
    for (int i = 1; i < nc1 + nc2; i++)
    {
        bool ok = true;
        if (i < nc1)
        {
            ok = potential->GetValue(c1[i]) > 0;
            if (!ok)
            {
                *potential = *potential + Potential(c1[i]);
            }
        }
        else
        {
            ok = potential->GetValue(c2[i % nc2]) < 0;
            if (!ok)
            {
                *potential = *potential - Potential(c2[i % nc2]);
            }
        }
    }
    /*bool delivered = false;
    do
    {
        int viewpNumber = (pNumber + 1) % (nc1 + nc2);
        bool c1Ok = true, c2Ok = true;
        bool *vOk1, *vOk2;
        bool potentialsSumVOk1;
        if (viewpNumber < nc1)
        {
            vOk1 = &c2Ok;
            vOk2 = &c1Ok;
            potentialsSumVOk1 = false;
            delivered = ClassesPointsDeliveredRight(c1, c2, 1, -1, c1Ok, c2Ok, viewpNumber, potential.get());
        }
        else
        {
            vOk1 = &c1Ok;
            vOk2 = &c2Ok;
            potentialsSumVOk1 = true;
            delivered = ClassesPointsDeliveredRight(c2, c1, -1, 1, c2Ok, c1Ok, viewpNumber % nc2, potential.get());
        }
        if (!delivered)
        {
            pNumber = (pNumber + 1) % (nc1 + nc2);
            CPoint *p;
            if (pNumber < nc1) p = &c1[pNumber];
            else p = &c2[pNumber % nc2];

            if (!(*vOk1))
            {
                if (potentialsSumVOk1) *potential = *potential + Potential(*p);
                else *potential = *potential - Potential(*p);
            }
            else
            {
                if (!potentialsSumVOk1) *potential = *potential + Potential(*p);
                else *potential = *potential - Potential(*p);
            }
        }
    } while (!delivered);*/
    return *potential;
}


bool Lab5::ClassesPointsDeliveredRight(
    const PointsList& plView1,
    const PointsList& plView2,
    const int plView1ExpectedSign,
    const int plView2ExpectedSign,
    bool &pl1Ok,
    bool &pl2Ok,
    int viewpNumber,
    Potential *p
)
{
    pl1Ok = ClassPointsDeliveredRight(plView1, viewpNumber, plView1.size() - 1, plView1ExpectedSign, p);
    if (pl1Ok)
    {
        pl2Ok = ClassPointsDeliveredRight(plView2, 0, plView2.size() - 1, plView2ExpectedSign, p);
        if (viewpNumber)
        {
            pl1Ok = ClassPointsDeliveredRight(plView1, 0, viewpNumber - 1, plView1ExpectedSign, p);
        }
    }
    return pl1Ok && pl2Ok;
}


bool Lab5::ClassPointsDeliveredRight(const vector<CPoint>& cPoints, int start, int end, int expectedSign, Potential *p)
{
    int value = expectedSign;
    bool deliveredRight = true;
    for (int i = start; (deliveredRight = value / expectedSign > 0) && i <= end; i++)
    {
        value = p->GetValue(cPoints[i]);
    }
    return deliveredRight;
}


void Lab5::PushNRandomLogicPointsToVector(vector<LogicPoint> &v, int n, int x1, int x2, int y1, int y2)
{
    for (int i = 0; i < n; i++)
    {
        v.push_back(GetRandomLogicPoint(x1, x2, y1, y2));
    }
}


LogicPoint Lab5::GetRandomLogicPoint(int x1, int x2, int y1, int y2)
{
    double x = RandomDouble(x1, x2);
    double y = RandomDouble(y1, y2);
    return LogicPoint(x, y);
}