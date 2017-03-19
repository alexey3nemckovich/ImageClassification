#pragma once
#include "Lab.h"
#include "SquareGrammar.h"
#include "CoordinateSystem.h"


#define LAB7 7


class Lab7
    : public Lab
{
public:
    static Lab7* GetInstance()
    {
        static Lab7 lab7 = Lab7();
        Labs::GetInstance()->SetActive(lab7.GetNumber());
        return &lab7;
        return NULL;
    }
    virtual ~Lab7();
    vector<Plot> GenerateShape(double x1, double x2, double y1, double y2)
    {
        srand(time(NULL));
        return grammar.GenerateShape(x1, x2, y1, y2);
    }
    bool CheckShape();
    int GetNumber()
    {
        return LAB7;
    }
    void SetMode(bool checkingShape)
    {
        _checkingShape = checkingShape;
    }
    bool IsCheckingShape()
    {
        return _checkingShape;
    }
private:
    Lab7() = default;
    vector<Token_value> GetShapeTokens(vector<Plot>&);
    bool PlotsHasIntersections(vector<Plot>, vector<Token_value>);
private:
    bool _checkingShape = false;
    SquareGrammar grammar;
};