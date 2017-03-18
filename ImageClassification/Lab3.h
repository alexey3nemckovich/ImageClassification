#pragma once
#include "Lab.h"
#include "Plot.h"
#include <vector>
using namespace std;


#define LAB3 3


class Lab3
    : public Lab
{
public:
    Lab3();
    virtual ~Lab3();
    pair<Plot, Plot> GeneratePlots(int N, double PC1, int x1, int x2);
    int GetNumber()
    {
        return LAB3;
    }
private:
    double _sigma;
    double _mu;
    Plot GeneratePlot(int N, double PC, int x1, int x2);
    void InitParameters(vector<double> x);
    double CalcY(double x);
};