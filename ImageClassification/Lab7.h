#pragma once
#include "Lab.h"
#include "SquareGrammar.h"


#define LAB7 7


class Lab7
    : public Lab
{
public:
    Lab7()
    {
        Labs::GetInstance()->SetActive(GetNumber());
    }
    virtual ~Lab7();
    vector<Plot> GenerateShape(double x1, double x2, double y1, double y2)
    {
        srand(time(NULL));
        return grammar.GenerateShape(x1, x2, y1, y2);
    }
    bool CheckShape(const vector<Token_value> &tokens)
    {
        return grammar.CorrectShape(tokens);
    }
    int GetNumber()
    {
        return LAB7;
    }
private:
    SquareGrammar grammar;
};