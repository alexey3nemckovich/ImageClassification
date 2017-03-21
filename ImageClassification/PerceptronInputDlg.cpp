#include "stdafx.h"
#include "PerceptronInputDlg.h"


BEGIN_MESSAGE_MAP(CPerceptronInputDlg, CDialogEx)
    ON_COMMAND(ID_CONTINUE, &CPerceptronInputDlg::OnClickContinue)
END_MESSAGE_MAP()


CPerceptronInputDlg::CPerceptronInputDlg()
    : CDialogEx(IDD_PERCEPTRON_INPUT)
{
    _step = Step::FIRST;
}


CPerceptronInputDlg::~CPerceptronInputDlg()
{
    delete[] _staticClSamples;
    delete _editClSamples;
}


void CPerceptronInputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


afx_msg void CPerceptronInputDlg::OnClickContinue()
{
    switch (_step)
    {
    case Step::FIRST:
        FirstStep();
        break;
    case Step::SECOND:
        SecondStep();
        break;
    case Step::THIRD:
        ThirdStep();
        break;
    }
}


void CPerceptronInputDlg::FirstStep()
{
    CString strClCount;
    CString strSnCount;
    GetDlgItemText(IDC_PERCEPTRON_CL_COUNT, strClCount);
    GetDlgItemText(IDC_PERCEPTRON_SIGN_COUNT, strSnCount);
    int flag1 = _stscanf(strClCount, "%d", &_clCount);
    int flag2 = _stscanf(strSnCount, "%d", &_snCount);
    if (!flag1 || !flag2)
    {
        MessageBox("Incorrect input.", "Error", NULL);
    }
    else
    {
        _weightCoefficients = vector<Perceptron::SignVector>(_clCount);
        _clSamples = vector<Perceptron::SignVector>(_clCount);
        for (int i = 0; i < _clCount; i++)
        {
            _weightCoefficients[i] = _clSamples[i] = Perceptron::SignVector(_snCount);
        }
        GetDlgItem(IDC_PERCEPTRON_CL_COUNT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_PERCEPTRON_SIGN_COUNT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PERC_CL_COUNT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PERC_SIGN_COUNT)->ShowWindow(SW_HIDE);
        CreateClassesSamplesControls();
        SetHeader("Input start weights coefficients values");
        ClearEdits();
        _step = Step::SECOND;
    }
}


void CPerceptronInputDlg::SecondStep()
{
    if (ParseClassSamples(_weightCoefficients))
    {
        ClearEdits();
        SetHeader("Input class samples");
        _step = Step::THIRD;
    }
    else
    {
        MessageBox("Incorrect input.", "Error", NULL);
    }
}


void CPerceptronInputDlg::ThirdStep()
{
    if (ParseClassSamples(_clSamples))
    {
        EndDialog(IDOK);
    }
    else
    {
        MessageBox("Incorrect input.", "Error", NULL);
    }
}


bool CPerceptronInputDlg::ParseClassSamples(vector<Perceptron::SignVector> &arr)
{
    CString str;
    int signValue;
    for (int i = 0; i < _clCount; i++)
    {
        for (int j = 0; j < _snCount; j++)
        {
            (*_editClSamples)[i][j].GetWindowTextA(str);
            double tmp;
            int flag = _stscanf(str, "%lf", &arr[i][j]);
            if (!flag)
            {
                return false;
            }
        }
    }
    return true;
}


void CPerceptronInputDlg::CreateClassesSamplesControls()
{
    srand(time(NULL));
    #define TEXT_WIDTH  120
    #define SIGN_WIDTH  40
    #define HEIGHT      20
    #define MARGIN      10
    CRect editRect;
    CRect staticRect;
    staticRect.left = 20;
    staticRect.top = 50;
    staticRect.right = staticRect.left + TEXT_WIDTH;
    staticRect.bottom = staticRect.top + HEIGHT;
    editRect.bottom = staticRect.bottom;
    editRect.top = staticRect.top;
    _staticClSamples = new CStatic[_clCount];
    _editClSamples  = new TwoDimensionalArray<CEdit>(_clCount, _snCount);
    int randInt;
    CString str;
    for (int i = 0; i < _clCount; i++)
    {
        editRect.left = staticRect.right + MARGIN;
        editRect.right = editRect.left + SIGN_WIDTH;
        randInt = rand() % USHORT_MAX;
        str.Format("Class %d sample:", i + 1);
        _staticClSamples[i].Create(str, WS_CHILD | WS_VISIBLE | SS_CENTER, staticRect, this, randInt);
        for (int j = 0; j < _snCount; j++)
        {
            randInt = rand() % USHORT_MAX;
            (*_editClSamples)[i][j].Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, editRect, this, randInt);
            editRect.left += MARGIN + SIGN_WIDTH;
            editRect.right = editRect.left + SIGN_WIDTH;
        }
        CRect wndRect;
        this->GetWindowRect(&wndRect);
        if ((editRect.right + MARGIN) >(wndRect.right - wndRect.left))
        {
            wndRect.right += MARGIN + SIGN_WIDTH;
            this->MoveWindow(wndRect);
        }
        editRect.top = staticRect.top += HEIGHT + MARGIN;
        editRect.bottom = staticRect.bottom += HEIGHT + MARGIN;
        if ((editRect.bottom + MARGIN) > (wndRect.bottom - wndRect.top))
        {
            wndRect.bottom += MARGIN + HEIGHT;
            this->MoveWindow(wndRect);
        }
    }
}


void CPerceptronInputDlg::SetHeader(CString header)
{
    SetDlgItemText(IDC_STATIC_PERC_HEADER, header);
}


void CPerceptronInputDlg::ClearEdits()
{
    for (int i = 0; i < _clCount; i++)
    {
        for (int j = 0; j < _snCount; j++)
        {
            (*_editClSamples)[i][j].SetWindowTextA("0");
        }
    }
}