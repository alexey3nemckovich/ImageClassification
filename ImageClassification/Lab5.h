#pragma once
#include "Lab.h"
#include <vector>
#include "Potential.h"
using namespace std;


#define LAB5 5


class Lab5
    : public Lab
{
public:
    Lab5();
    virtual ~Lab5();
    Potential GetPotentialFunction(vector<CPoint> c1, vector<CPoint> c2);
    void PushNRandomLogicPointsToVector(vector<LogicPoint> &v, int n, int x1, int x2, int y1, int y2);
    int GetNumber()
    {
        return LAB5;
    }
private:
    typedef vector<CPoint> PointsList;
    typedef pair<PointsList, PointsList> ClassesPoints;
    bool ClassesPointsDeliveredRight(
        const PointsList& plView1,
        const PointsList& plView2,
        const int plView1ExpectedSign,
        const int plView2ExpectedSign,
        bool &pl1Ok,
        bool &pl2Ok,
        int viewpNumber,
        Potential *p
    );
    bool ClassPointsDeliveredRight(const vector<CPoint>& cPoints, int start, int end, int expectedSign, Potential *p);
    LogicPoint GetRandomLogicPoint(int x1, int x2, int y1, int y2);
};