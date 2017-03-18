#pragma once
#include <vector>
#include <limits>
using namespace std;


class StandardCoordinateSystem;
class Plot
{
private:
    int _maxX = INT_MIN;
    vector<LogicPoint> _points;
    int _penStyle;
    int _penWidth;
    COLORREF _penColor;
public:
    Plot() = delete;
    Plot(vector<LogicPoint> &points, int penStyle = PS_SOLID, int penWidth = 1, COLORREF penColor = RGB(0,0,0)) 
        : _penStyle(penStyle), _penWidth(penWidth), _penColor(penColor), _points(std::move(points))
    {
            
    }
    Plot(Plot &other)
    {
        _penStyle = other._penStyle;
        _penWidth = other._penWidth;
        _penColor = other._penColor;
        _points = other._points;
    }
    Plot(Plot&& other)
    {
        _penStyle = other._penStyle;
        _penWidth = other._penWidth;
        _penColor = other._penColor;
        _points = std::move(other._points);
    }
    ~Plot();
    void Render(const StandardCoordinateSystem*, CPaintDC *dc);
    LogicPoint* GetEqualPoint(const Plot &other);
    LogicPoint operator[](int index)
    {
        return _points[index];
    }
};