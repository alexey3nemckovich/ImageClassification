#include "stdafx.h"
#include "Lab7.h"


Lab7::~Lab7()
{
}


bool Lab7::CheckShape()
{
    auto sc = StandardCoordinateSystem::GetInstance();
    auto shapeLines = sc->GetPlots();
    auto tokens = GetShapeTokens(shapeLines);
    if (!PlotsHasIntersections(shapeLines, tokens))
    {
        return grammar.CorrectShape(tokens);
    }
    else
    {
        return false;
    }
}


bool Lab7::PlotsHasIntersections(vector<Plot> lines, vector<Token_value> tokens)
{
    int len = lines.size();
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (tokens[i] != tokens[j])
            {
                if (tokens[i] == Token_value::a1)
                {
                    if (lines[i][0].y < max(lines[j][0].y, lines[j][1].y))
                    {
                        return true;
                    }
                }
                else
                {
                    if (min(lines[i][0].y, lines[i][1].y) < lines[j][0].y)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void sort(vector<Plot> &lines)
{
    for (int i = lines.size() - 1; i > 0; i--)
    {
        for (int j = i; j > 0; j--)
        {
            if ((lines[j][0].y + lines[j][1].y) > (lines[j-1][0].y + lines[j-1][1].y))
            {
                auto tmp = lines[j];
                lines[j] = lines[j - 1];
                lines[j - 1] = tmp;
            }
        }
    }
}


vector<Token_value> Lab7::GetShapeTokens(vector<Plot>& lines)
{
    vector<Token_value> v;
    sort(lines);
    for each(Plot line in lines)
    {
        if (line[0].x == line[1].x)
        {
            v.push_back(Token_value::a2);
        }
        else
        {
            v.push_back(Token_value::a1);
        }
    }
    return v;
}