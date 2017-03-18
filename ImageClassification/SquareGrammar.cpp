#include "stdafx.h"
#include "SquareGrammar.h"


SquareGrammar::SquareGrammar()
{

}


SquareGrammar::~SquareGrammar()
{

}


vector<Plot> SquareGrammar::GenerateShape(double x1, double x2, double y1, double y2)
{
    vector<Plot> shape;
    S(shape, x1, x2, y1, y2);
    return shape;
}


bool SquareGrammar::CorrectShape(const vector<Token_value> &tokens)
{
    return tokens.size() == 4 && S(tokens.begin());
}


bool SquareGrammar::S(vector<Token_value>::const_iterator token)
{
    if (Token_value::a1 != *token)
    {
        return false;
    }
    else
    {
        return O2(token++);
    }
}


bool SquareGrammar::O1(vector<Token_value>::const_iterator token)
{
    if (Token_value::a2 != *token++)
    {
        return false;
    }
    else
    {
        return Token_value::a2 != *token++;
    }
}


bool SquareGrammar::O2(vector<Token_value>::const_iterator token)
{
    if (!O1(token))
    {
        return false;
    }
    else
    {
        return Token_value::a1 == *token;
    }
}


void SquareGrammar::S(vector<Plot> &shape, double x1, double x2, double y1, double y2)
{
    vector<LogicPoint> points;
    double rx1 = RandomDouble(x1, x2);
    double rx2 = RandomDouble(x1, x2);
    double ry = RandomDouble(y1, y2);
    points.push_back(LogicPoint(rx1, ry));
    points.push_back(LogicPoint(rx2, ry));
    shape.push_back(Plot(points, 0, 2, RGB(255, 0, 0)));
    O2(shape, x1, x2, y1, y2);
}


void SquareGrammar::O1(vector<Plot> &shape, double x1, double x2, double y1, double y2)
{
    vector<LogicPoint> points1;
    vector<LogicPoint> points2;
    double rx1 = RandomDouble(x1, x2);
    double rx2 = RandomDouble(x1, x2);
    double ry1 = RandomDouble(y1, shape[0][0].y);
    double ry2 = RandomDouble(y1, shape[0][0].y);
    double ry3 = RandomDouble(y1, shape[0][0].y);
    double ry4 = RandomDouble(y1, shape[0][0].y);
    points1.push_back(LogicPoint(rx1, ry1));
    points1.push_back(LogicPoint(rx1, ry2));
    points2.push_back(LogicPoint(rx2, ry3));
    points2.push_back(LogicPoint(rx2, ry4));
    shape.push_back(Plot(points1, 0, 2, RGB(255, 0, 0)));
    shape.push_back(Plot(points2, 0, 2, RGB(255, 0, 0)));
}


void SquareGrammar::O2(vector<Plot> &shape, double x1, double x2, double y1, double y2)
{
    O1(shape, x1, x2, y1, y2);
    vector<LogicPoint> points;
    double rx1 = RandomDouble(x1, x2);
    double rx2 = RandomDouble(x1, x2);
    double ry = RandomDouble(
        y1,
        min(
            min(shape[1][0].y, shape[1][1].y),
            min(shape[2][0].y, shape[2][1].y),
        ) 
    );
    points.push_back(LogicPoint(rx1, ry));
    points.push_back(LogicPoint(rx2, ry));
    shape.push_back(Plot(points, 0, 2, RGB(255, 0, 0)));
}