#pragma once
#include "resource.h"
using namespace std;


class CLab6InputDlg :
    public CDialogEx
{
public:
    CLab6InputDlg();
    virtual ~CLab6InputDlg();
    int GetObjectsCount()
    {
        return _n;
    }
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    afx_msg void OnClickOk();
    DECLARE_MESSAGE_MAP()
private:
    int _n;
};