#include "stdafx.h"
#include "Lab7InputDlg.h"


BEGIN_MESSAGE_MAP(CLab7InputDlg, CDialogEx)
    ON_COMMAND(IDC_BUTTON7_GEN, CLab7InputDlg::OnGen)
    ON_COMMAND(IDC_BUTTON7_CHECK, CLab7InputDlg::OnCheck)
END_MESSAGE_MAP()


CLab7InputDlg::CLab7InputDlg()
    :CDialogEx(IDD_LAB7_INPUT)
{

}


CLab7InputDlg::~CLab7InputDlg()
{

}


void CLab7InputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}