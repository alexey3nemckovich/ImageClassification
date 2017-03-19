#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ImageClassification.h"
#include "MainFrm.h"
#include "AboutDlg.h"
#include "CoordinateSystem.h"
#include "LabsHeaders.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CImageClassificationApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CImageClassificationApp::OnAppAbout)
    ON_COMMAND(ID_FILE_LAB3, &CImageClassificationApp::OnLab3)
    ON_COMMAND(ID_FILE_LAB4, &CImageClassificationApp::OnLab4)
    ON_COMMAND(ID_FILE_LAB5, &CImageClassificationApp::OnLab5)
    ON_COMMAND(ID_FILE_LAB6, &CImageClassificationApp::OnLab6)
    ON_COMMAND(ID_FILE_LAB7, &CImageClassificationApp::OnLab7)
    ON_COMMAND(ID_FILE_LAB8, &CImageClassificationApp::OnLab8)
END_MESSAGE_MAP()


CImageClassificationApp::CImageClassificationApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ImageClassification.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CImageClassificationApp object

CImageClassificationApp theApp;


// CImageClassificationApp initialization

BOOL CImageClassificationApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);





	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CImageClassificationApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CImageClassificationApp message handlers
afx_msg void CImageClassificationApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}


afx_msg void CImageClassificationApp::OnLab3()
{
    CLab3InputDlg dlg;
    if (IDCANCEL != dlg.DoModal())
    {
        Lab3 lab3;
        auto plots = lab3.GeneratePlots(dlg.GetN(), dlg.GetPC1(), 0, 5);
        auto sc = StandardCoordinateSystem::GetInstance();
        sc->Clear();
        sc->SetLogicBounds(CRect(-1, 1, 5, -1));
        LogicPoint *lp;
        if (lp = plots.first.GetEqualPoint(plots.second))
        {
            sc->AdLogicPoint(*lp, RGB(255, 0, 0), true, true);
        }
        sc->AddPlot(plots.first);
        sc->AddPlot(plots.second);
        m_pMainWnd->InvalidateRect(NULL, TRUE);
    }
}


afx_msg void CImageClassificationApp::OnLab4()
{
    CLab4InputDlg dlg;
    if (IDCANCEL != dlg.DoModal())
    {
        Lab4 lab4;
        vector<DecisionFunction> desFunctions = lab4.GetDecisionFunctions(dlg.GetDecisiveSamples());
        CString res = "";
        CString tmp;
        for (int i = 0; i < desFunctions.size(); i++)
        {
            tmp.Format("d%d(x) = ", i + 1);
            res += tmp + desFunctions[i].ToString() + '\n';
        }
        MessageBox(m_pMainWnd->m_hWnd, res, "Answer Lab 4", NULL);
    }
}


afx_msg void CImageClassificationApp::OnLab5()
{
    static COLORREF redColor = RGB(255, 0, 0);
    static COLORREF blueColor = RGB(0,0, 255);
    CLab5InputDlg dlg;
    if (IDCANCEL != dlg.DoModal())
    {
        Lab5 lab5;
        Potential potential = lab5.GetPotentialFunction(dlg.GetC1Sample(), dlg.GetC2Sample());
        vector<LogicPoint> v;
        double dx = 0.5, x = -5;
        LogicPoint lp;
        while (x < 5)
        {
            lp.x = x;
            lp.y = potential.GetValue(x);
            v.push_back(lp);
            x += 0.01;
        }
        vector<LogicPoint> randPoints;
        lab5.PushNRandomLogicPointsToVector(randPoints, dlg.GetN(), -5, 5, -5, 5);
        Plot potentialFuncPlot(v, PS_SOLID, 1, redColor);
        auto sc = StandardCoordinateSystem::GetInstance();
        sc->Clear();
        sc->EnableGridRendering();
        sc->SetLogicBounds(CRect(-5, 5, 5, -5));
        sc->AddPlot(potentialFuncPlot);
        COLORREF pointColor;
        for (int i = 0; i < randPoints.size(); i++)
        {
            if (potential.GetValue(randPoints[i]) > 0)
            {
                pointColor = redColor;
            }
            else
            {
                pointColor = blueColor;
            }
            sc->AdLogicPoint(randPoints[i], false, pointColor);
        }
        m_pMainWnd->InvalidateRect(NULL, TRUE);
    }
}


afx_msg void CImageClassificationApp::OnLab6()
{
    CLab6InputDlg dlg;
    if (IDCANCEL != dlg.DoModal())
    {
        Lab6 lab6;
        HierarchyGroup::Ptr hierarchyHead = lab6.GetHierarchyGroup(dlg.GetObjectsCount());
        lab6.AddHierarchyGroupImageToCoordinateSystem(hierarchyHead, StandardCoordinateSystem::GetInstance());
        m_pMainWnd->InvalidateRect(NULL);
    }
}


afx_msg void CImageClassificationApp::OnLab7()
{
    CLab7InputDlg dlg;
    DWORD res;
    if (IDCANCEL != (res = dlg.DoModal()))
    {
        Lab7 lab;
        auto sc = StandardCoordinateSystem::GetInstance();
        sc->Clear();
        switch (res)
        {
        case IDC_BUTTON7_GEN:
        {
            sc->SetLogicBounds(CRect(-1, 5, 5, -1));
            vector<Plot> shape = lab.GenerateShape(0, 4, 0, 4);
            for (int i = 0; i < shape.size(); i++)
            {
                sc->AddPlot(shape[i]);
            }
            break;
        }
        case IDC_BUTTON7_CHECK:
            break;
        }
        m_pMainWnd->InvalidateRect(NULL, TRUE);
    }
}


afx_msg void CImageClassificationApp::OnLab8() 
{
    CLab8InputDlg dlg;
    if (IDCANCEL != dlg.DoModal())
    {
        Lab8 lab;
        auto grammar = lab.GetGrammar(dlg.GetLearningChains());
        auto chains = grammar.GenerateRandomChains(5);
        string res;
        for each(string chain in chains)
        {
            res += chain + '\n';
        }
        MessageBox(m_pMainWnd->m_hWnd, res.c_str(), "Answer Lab 8", NULL);
    }
}