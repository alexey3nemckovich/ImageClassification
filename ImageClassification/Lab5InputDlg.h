#pragma once
#include "resource.h"
#include <string>
#include <regex>
#include <vector>
using namespace std;


class CLab5InputDlg : public CDialogEx
{
public:
    CLab5InputDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif
    int GetN()
    {
        return _n;
    }
    vector<CPoint> GetC1Sample()
    {
        return _c1;
    }
    vector<CPoint> GetC2Sample()
    {
        return _c2;
    }

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    afx_msg void OnClickOk();
    DECLARE_MESSAGE_MAP()
private:
    int ParseClassesSample(string str, vector<CPoint> &v);
private:
    int _n;
    vector<CPoint> _c1, _c2;
};