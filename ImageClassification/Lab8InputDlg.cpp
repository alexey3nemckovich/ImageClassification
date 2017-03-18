#include "stdafx.h"
#include "Lab8InputDlg.h"


BEGIN_MESSAGE_MAP(CLab8InputDlg, CDialogEx)
    ON_COMMAND(IDOK, CLab8InputDlg::OnOk)
END_MESSAGE_MAP()


CLab8InputDlg::CLab8InputDlg()
    :CDialogEx(IDD_LAB8_INPUT)
{
}


CLab8InputDlg::~CLab8InputDlg()
{
}


void CLab8InputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


afx_msg void CLab8InputDlg::OnOk()
{
    CString strChains;
    GetDlgItemText(IDC_EDIT8_CHAINS, strChains);
    ParseLearningChains(string(strChains));
    EndDialog(IDOK);
}


void CLab8InputDlg::ParseLearningChains(string str)
{
    static regex chainRegex{ R"(\w+)" };
    smatch m;
    while (regex_search(str, m, chainRegex))
    {
        _learningChains.push_back(m[0].str());
        str = m.suffix();
    }
}