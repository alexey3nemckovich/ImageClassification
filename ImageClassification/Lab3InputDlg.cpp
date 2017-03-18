#include "stdafx.h"
#include "Lab3InputDlg.h"


BEGIN_MESSAGE_MAP(CLab3InputDlg, CDialogEx)
    ON_COMMAND(IDOK, &CLab3InputDlg::OnClickOk)
END_MESSAGE_MAP()


CLab3InputDlg::CLab3InputDlg() : CDialogEx(IDD_LAB3_INPUT)
{
}


void CLab3InputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


afx_msg void CLab3InputDlg::OnClickOk()
{
    CString strN;
    CString strPC1;
    GetDlgItemText(IDC_EDIT_N, strN);
    GetDlgItemText(IDC_EDIT_PC1, strPC1);
    bool flag1 = _stscanf(strN, "%d", &_N);
    bool flag2 = _stscanf(strPC1, "%f", &_PC1);
    if (!flag1 || !flag2 || _PC1 > 1 || _N < 1)
    {
        MessageBox("Incorrect input.", "Error", NULL);
    }
    else
    {
        EndDialog(IDOK);
    }
}