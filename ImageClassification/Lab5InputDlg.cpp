#include "stdafx.h"
#include "Lab5InputDlg.h"


BEGIN_MESSAGE_MAP(CLab5InputDlg, CDialogEx)
    ON_COMMAND(IDOK, &CLab5InputDlg::OnClickOk)
END_MESSAGE_MAP()


CLab5InputDlg::CLab5InputDlg() : CDialogEx(IDD_LAB5_INPUT)
{

}


void CLab5InputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


afx_msg void CLab5InputDlg::OnClickOk()
{
    CString strC1, strC2, strN;
    GetDlgItemText(IDC_EDIT5_NC1, strC1);
    GetDlgItemText(IDC_EDIT5_NC2, strC2);
    GetDlgItemText(IDC_EDIT5_N, strN);
    int flag1 = ParseClassesSample(string(strC1), _c1);
    int flag2 = ParseClassesSample(string(strC2), _c2);
    int flag3 = _stscanf(strN, "%d", &_n);
    if (!flag1 || !flag2 || !flag3 || _n < 1)
    {
        MessageBox("Incorrect input.", "Error", NULL);
    }
    else
    {
        EndDialog(IDOK);
    }
}


int CLab5InputDlg::ParseClassesSample(string str, vector<CPoint> &v)
{
    v.clear();
    static regex classPointsSampleRegex{ R"(\([ ]*([\-\+]?\d+[ ]*),[ ]*([\-\+]?\d+)[ ]*\))" };
    smatch m;
    CPoint p;
    size_t x, y;
    int countParsed = 0;
    while (regex_search(str, m, classPointsSampleRegex))
    {
        try
        {
            p.x = stoi(m[1].str());
            p.y = stoi(m[2].str());
        }
        catch (invalid_argument e)
        {
            return 0;
        }
        v.push_back(p);
        countParsed++;
        str = m.suffix();
    }
    return countParsed;
}