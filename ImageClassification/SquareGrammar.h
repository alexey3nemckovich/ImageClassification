#pragma once
#include "Plot.h"
#include <vector>
#include "Tokens.h"
using namespace std;


class SquareGrammar
{
public:
    SquareGrammar();
    ~SquareGrammar();
    vector<Plot> GenerateShape(double x1, double x2, double y1, double y2);
    bool CorrectShape(const vector<Token_value> &tokens);
private:
    bool S(vector<Token_value>::const_iterator &token, vector<Token_value>::const_iterator end);
    bool O1(vector<Token_value>::const_iterator &token, vector<Token_value>::const_iterator end);
    bool O2(vector<Token_value>::const_iterator &token, vector<Token_value>::const_iterator end);
    void S(vector<Plot> &shape, double x1, double x2, double y1, double y2);
    void O1(vector<Plot> &shape, double x1, double x2, double y1, double y2);
    void O2(vector<Plot> &shape, double x1, double x2, double y1, double y2);
};