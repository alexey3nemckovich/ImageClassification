#include "stdafx.h"
#include "ImageClassification.h"
#include "ChildView.h"
#include "CoordinateSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CChildView::CChildView()
{
}


CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}


afx_msg void CChildView::OnPaint()
{
    static auto sc = StandardCoordinateSystem::GetInstance();
	CPaintDC dc(this);
    sc->Render(&dc);
}


afx_msg void CChildView::OnMouseMove(UINT flags, CPoint point)
{
    static auto sc = StandardCoordinateSystem::GetInstance();
    switch (Labs::GetInstance()->GetActive())
    {
    case LAB7:
        if (isDrawing)
        {
            auto lastPlot = sc->LastPlot();
            LogicPoint startLp = (*lastPlot)[0];
            LogicPoint newLp = sc->PhysToLogicPoint(point);
            bool horzTerm = abs(newLp.x - startLp.x) > abs(newLp.y - startLp.y) ? true : false;
            if (horzTerm)
            {
                (*lastPlot)[1].y = startLp.y;
                (*lastPlot)[1].x = newLp.x;
            }
            else
            {
                (*lastPlot)[1].x = startLp.x;
                (*lastPlot)[1].y = newLp.y;
            }
            InvalidateRect(NULL, TRUE);
        }
        break;
    }
}


afx_msg void CChildView::OnLButtonUp(UINT flags, CPoint point)
{
    static auto sc = StandardCoordinateSystem::GetInstance();
    switch (Labs::GetInstance()->GetActive())
    {
    case LAB7:
        if (!isDrawing)
        {
            vector<LogicPoint> v;
            v.push_back(sc->PhysToLogicPoint(point));
            v.push_back(v[0]);
            sc->AddPlot(Plot(v));
        }
        isDrawing = !isDrawing;
        break;
    }
}


afx_msg void CChildView::OnRButtonUp(UINT flags, CPoint point)
{
    static auto sc = StandardCoordinateSystem::GetInstance();
    switch (Labs::GetInstance()->GetActive())
    {
    case LAB7:
        if (Lab7::GetInstance()->IsCheckingShape())
        {
            bool correctShape = Lab7::GetInstance()->CheckShape();
            if (correctShape)
            {
                MessageBox("Correct shape", "Answer Lab 8", NULL);
            }
            else
            {
                MessageBox("Wrong shape", "Answer Lab 8", NULL);
            }
        }
        break;
    }
}