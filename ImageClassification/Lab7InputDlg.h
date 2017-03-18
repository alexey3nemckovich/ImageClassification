#pragma once
#include "resource.h"
using namespace std;


class CLab7InputDlg
    : public CDialogEx
{
public:
    CLab7InputDlg();
    ~CLab7InputDlg();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    afx_msg void OnGen()
    {
        EndDialog(IDC_BUTTON7_GEN);
    }
    afx_msg void OnCheck()
    {
        EndDialog(IDC_BUTTON7_CHECK);
    }
    DECLARE_MESSAGE_MAP()
};