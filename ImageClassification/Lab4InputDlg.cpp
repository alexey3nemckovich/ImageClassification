#include "stdafx.h"
#include "Lab4InputDlg.h"


BEGIN_MESSAGE_MAP(CLab4InputDlg, CDialogEx)
    ON_COMMAND(ID_CONTINUE, &CLab4InputDlg::OnClickContinue)
END_MESSAGE_MAP()


CLab4InputDlg::CLab4InputDlg()
    : CDialogEx(IDD_LAB4_INPUT)
{

}


CLab4InputDlg::~CLab4InputDlg()
{
    delete[] _staticClSamples;
    delete[] _editClSamples;
}


void CLab4InputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


afx_msg void CLab4InputDlg::OnClickContinue()
{
    if (_firstStep)
    {
        CString strClCount;
        GetDlgItemText(IDC_EDIT4_CL_COUNT, strClCount);
        int flag = _stscanf(strClCount, "%d", &_n);
        if (!flag)
        {
            MessageBox("Incorrect input.", "Error", NULL);
        }
        else
        {
            _clSamples = vector<vector<SpacePoint>>(_n);
            GetDlgItem(IDC_STATIC4_CL_COUNT)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT4_CL_COUNT)->ShowWindow(SW_HIDE);
            CreateClassesSamplesControls();
            _firstStep = false;
        }
    }
    else
    {
        CString str;
        bool err = false;
        for (int i = 0; i < _n; i++)
        {
            _editClSamples[i].GetWindowTextA(str);
            int flag = ParseClassesSample(string(str), _clSamples[i]);
            if (!flag) err = true;
        }
        if (err)
        {
            MessageBox("Incorrect input.", "Error", NULL);
        }
        else
        {
            EndDialog(IDOK);
        }
    }
}


void CLab4InputDlg::CreateClassesSamplesControls()
{
    srand(time(NULL));
    #define WIDTH 120
    #define HEIGHT 20
    #define MARGIN 20
    CRect editRect;
    CRect staticRect;
    staticRect.left = 20;
    staticRect.top = 50;
    staticRect.right = staticRect.left + WIDTH;
    staticRect.bottom = staticRect.top + HEIGHT;
    editRect.left = staticRect.left + MARGIN + WIDTH;
    editRect.right = staticRect.right + MARGIN + 2*WIDTH;
    editRect.bottom = staticRect.bottom;
    editRect.top = staticRect.top;
    _staticClSamples = new CStatic[_n];
    _editClSamples  = new CEdit[_n];
    int randInt;
    CString str;
    for (int i = 0; i < _n; i++)
    {
        randInt = rand() % USHORT_MAX;
        str.Format("Class %d sample:", i + 1);
        _staticClSamples[i].Create(str, WS_CHILD | WS_VISIBLE | SS_CENTER, staticRect, this, randInt);
        randInt = rand() % USHORT_MAX;
        _editClSamples[i].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, editRect, this, randInt);
        editRect.top = staticRect.top += HEIGHT + MARGIN;
        editRect.bottom = staticRect.bottom += HEIGHT + MARGIN;
        CRect wndRect;
        this->GetWindowRect(&wndRect);
        if ((editRect.bottom + MARGIN) > (wndRect.bottom - wndRect.top))
        {
            wndRect.bottom += MARGIN + HEIGHT;
            this->MoveWindow(wndRect);
        }
    }
}


int CLab4InputDlg::ParseClassesSample(string str, vector<SpacePoint> &v)
{
    v.clear();
    static regex classPointsSampleRegex{ R"(\([ ]*([\-\+]?\d+[ ]*)[ ]*,[ ]*([\-\+]?\d+)[ ]*)" };
    smatch m;
    SpacePoint p;
    size_t x, y, z;
    int countParsed = 0;
    while (regex_search(str, m, classPointsSampleRegex))
    {
        try
        {
            p.x = stoi(m[1].str());
            p.y = stoi(m[2].str());
            p.z = 1;
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