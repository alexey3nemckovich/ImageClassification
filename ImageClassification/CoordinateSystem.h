#pragma once
#include <vector>
#include "Plot.h"
using namespace std;


class StandardCoordinateSystem
{
//const definitions
private:
    #define DEFAULT_LLEFT_BOUND     -5
    #define DEFAULT_LRIGHT_BOUND     5
    #define DEFAULT_LTOP_BOUND       5
    #define DEFAULT_LBOTTOM_BOUND   -5
    #define DIVISION_HALF_LEN        5
    #define AXIS_INDENT              2
//type definitions
private:
    typedef struct ColorLogicPoint
    {
        LogicPoint logicPoint;
        COLORREF color;
        ColorLogicPoint(LogicPoint p, COLORREF cl)
        {
            this->logicPoint = p;
            this->color = cl;
        }
        bool operator==(const ColorLogicPoint& other)
        {
            return logicPoint == other.logicPoint && color == other.color;
        }
    };
    typedef struct DetectLogicPoint
        : ColorLogicPoint
    {
        bool horzDetect;
        bool vertDetect;
        bool horzDetectLine;
        bool vertDetectLine;
        DetectLogicPoint(LogicPoint p, COLORREF cl, bool horzDetect, bool vertDetect, bool horzDetectLine = true, bool vertDetectLine = true)
            : ColorLogicPoint(p, cl)
        {
            this->vertDetect = vertDetect;
            this->horzDetect = horzDetect;
            this->horzDetectLine = horzDetectLine;
            this->vertDetectLine = vertDetectLine;
        }
        bool operator==(const DetectLogicPoint& other)
        {
            return horzDetect == other.horzDetect && vertDetect == other.vertDetect && ColorLogicPoint::operator==(other);
        }
    };
    typedef struct Text
    {
        LogicPoint point;
        CString text;
        Text(LogicPoint p, CString text)
        {
            this->point = p;
            this->text = text;
        }
    };
    enum SIDE{LEFT, RIGHT, TOP, BOTTOM};
    enum class AXIS {VERT, HORZ};
//data
private:
    CPen _axisPen;
    CPen _gridPen;
    double _horzScale;
    double _vertScale;
    CPoint _physOrigin;
    CRect _logicRect;
    CRect _physRect;
    CString _horzAxisName;
    CString _vertAxisName;
    vector<ColorLogicPoint> _points;
    vector<DetectLogicPoint> _detectPoints;
    vector<Plot> _plots;
    bool _gridRender = false;
private:
    void RenderArrow(CPaintDC *dc, SIDE type);
    void CheckHorzBounds(int x);
    void CheckVertBounds(int y);
    void InitSystemParameters(CPaintDC *dc);
    void RenderAxis(CPaintDC *dc);
    virtual void RenderVertAxis(CPaintDC *dc);
    virtual void RenderHorzAxis(CPaintDC *dc);
    void RenderColorPoint(CPaintDC *dc, const ColorLogicPoint &logiLogicPoint);
    void RenderDetectPoint(CPaintDC *dc, const DetectLogicPoint &logiLogicPoint);
    void RenderDivision(CPaintDC *dc, AXIS axis, int value);
    void RenderDivision(CPaintDC *dc, AXIS axis, double value);
    void RenderTextOnAxis(CPaintDC *dc, AXIS axis, double value, CString text);
    void RenderText(CPaintDC *dc, CPoint p, CString text);
    StandardCoordinateSystem(
        CString horzAxisName = "x",
        CString vertAxisName = "y",
        COLORREF axisColor = RGB(0, 0, 0),
        COLORREF gridColor = RGB(0, 0, 0)
    );
//main interface
public:
    static StandardCoordinateSystem *GetInstance();
    virtual ~StandardCoordinateSystem();
    void Render(CPaintDC *dc);
    void Clear();
    void AddText(LogicPoint p, CString text);
    void AddLogicPoint(LogicPoint point, COLORREF cl = RGB(0, 0, 0), bool detectHorz = false, bool detectVert = false, bool horzDetectLine = true, bool vertDetectLine = true);
    void AddLogicPoint(double x, double y, COLORREF cl = RGB(0, 0, 0), bool detectHorz = false, bool detectVert = false, bool horzDetectLine = true, bool vertDetectLine = true);
    void AddPlot(Plot &plot, COLORREF color = RGB(0,0,0))
    {
        _plots.push_back(std::move(plot));
    }
    Plot* LastPlot()
    {
        if (_plots.size())
        {
            return  &_plots[_plots.size() -1];
        }
    }
//getters
public:
    vector<Plot> GetPlots()
    {
        return _plots;
    }
//setters
public:
    void SetLogicBounds(const CRect& rect)
    {
        _logicRect = rect;
    }
    void SetHorizontalAxisName(CString newName)
    {
        _horzAxisName = newName;
    }
    void SetVerticalAxisName(CString newName)
    {
        _vertAxisName = newName;
    }
    void EnableGridRendering()
    {
        _gridRender = true;
    }
    void DisableGridRendering()
    {
        _gridRender = false;
    }
//converts
public:
    CPoint LogicToPhysPoint(const LogicPoint& point) const;
    LogicPoint PhysToLogicPoint(const CPoint& point) const;
    int LogicToPhysX(double x) const;
    double PhysToLogicX(double x) const;
    int LogicToPhysY(double x) const;
    double PhysToLogicY(double y) const;
};