#include "stdafx.h"
#include "Lab3.h"
#include <random>
#include <ctime>


double CalcSigma(vector<double>, double mu);
double CalcMu(vector<double>);


Lab3::~Lab3()
{
}


pair<Plot, Plot> Lab3::GeneratePlots(int N, double PC1, int x1, int x2)
{
    Plot plot1 = GeneratePlot(N, PC1, x1, x2);
    Plot plot2 = GeneratePlot(N, 1- PC1, x1, x2);
    pair<Plot, Plot> plots(plot1, plot2);
    return plots;
}


Plot Lab3::GeneratePlot(int N, double PC, int x1, int x2)
{
    #define dx 0.01
    #define BAD_CONST 10
    vector<double> x(N);
    vector<LogicPoint> points;
    int tmp = 0;
    _mu = 0;
    _sigma = 0;
    do
    {
        do
        {
            tmp = rand() % BAD_CONST;
        } while (tmp < 1);
        for (int i = 0; i < N; i++)
        {
            x[i] = RandomDouble(0, tmp);
        }
        InitParameters(x);
    }while (_sigma > 1 || _sigma < 0.2);
    /*///
    _mu = 2;
    _sigma = 1;
    ///*/
    double vx = x1;
    LogicPoint tp;
    tp.x = x1;
    while (tp.x < (double)x2)
    {
        tp.y = PC * CalcY(tp.x);
        points.push_back(tp);
        tp.x += dx;
    }
    return Plot(points, PS_SOLID, 1, RGB(255, 0, 0));
}


double Lab3::CalcY(double x)
{
    double denominator = 1 / (_sigma * sqrt(2*3.14));
    return denominator * exp(-0.5 * pow((x - _mu)/_sigma, 2));
}


void Lab3::InitParameters(vector<double> x)
{
    _mu = CalcMu(x);
    _sigma = CalcSigma(x, _mu);
}


double CalcSigma(vector<double> x, double mu)
{
    double sum = 0;
    double c = x.size();
    for (int i = 0; i < c; i++)
    {
        sum += pow(x[i] - mu, 2);
    }
    return sqrt(sum / c);
}


double CalcMu(vector<double> x)
{
    double sum = 0;
    double c = x.size();
    for (int i = 0; i < c; i++)
    {
        sum += x[i];
    }
    return sum / c;
}