#pragma once
#include "resource.h"


class CLab3InputDlg : public CDialogEx
{
public:
    CLab3InputDlg();
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_LAB3_INPUT };
#endif
    int GetN()
    {
        return _N;
    }
    float GetPC1()
    {
        return _PC1;
    }

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    afx_msg void OnClickOk();
    DECLARE_MESSAGE_MAP()

private:
    int _N;
    float _PC1;
};