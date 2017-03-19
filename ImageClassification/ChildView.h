#pragma once
#include "Labs.h"
#include "Lab7.h"
#include "CoordinateSystem.h"


class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT flags, CPoint point);
    afx_msg void OnLButtonUp(UINT flags, CPoint point);
    afx_msg void OnRButtonUp(UINT flags, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
    bool isDrawing = false;
};