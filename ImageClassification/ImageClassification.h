#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"
#include "Perceptron.h"

// CImageClassificationApp:
// See ImageClassification.cpp for the implementation of this class
//

class CImageClassificationApp : public CWinApp
{
public:
	CImageClassificationApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
    afx_msg void OnLab3();
    afx_msg void OnLab4();
    afx_msg void OnLab5();
    afx_msg void OnLab6();
    afx_msg void OnLab7();
    afx_msg void OnLab8();
    afx_msg void OnLab9();
	DECLARE_MESSAGE_MAP()
private:
    void PerceptronLab(Perceptron *perceptron);
};

extern CImageClassificationApp theApp;