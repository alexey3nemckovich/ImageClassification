#include "stdafx.h"
#include "Lab6InputDlg.h"


BEGIN_MESSAGE_MAP(CLab6InputDlg, CDialogEx)
    ON_COMMAND(IDOK, CLab6InputDlg::OnClickOk)
END_MESSAGE_MAP()


CLab6InputDlg::CLab6InputDlg()
    :CDialogEx(IDD_LAB6_INPUT)
{

}


CLab6InputDlg::~CLab6InputDlg()
{

}


void CLab6InputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


afx_msg void CLab6InputDlg::OnClickOk()
{
    CString strObjCount;
    GetDlgItemText(IDC_EDIT6_OBJ_COUNT, strObjCount);
    int flag = _stscanf(strObjCount, "%d", &_n);
    if (!flag || _n < 1)
    {
        MessageBox("Incorrect input.", "Error", NULL);
    }
    else
    {
        if (IsDlgButtonChecked(IDC_RADIO_PERC_MIN_CRITERION))
        {
            _criterion = Lab6::Criterion::MIN;
        }
        else
        {
            _criterion = Lab6::Criterion::MAX;
        }
        EndDialog(IDOK);
    }
}