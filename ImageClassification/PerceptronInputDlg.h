#pragma once
#include <vector>
#include <regex>
#include "resource.h"
#include "Perceptron.h"
#include "TwoDimensionalArray.h"
using namespace std;


class CPerceptronInputDlg
    : public CDialogEx
{
public:
    CPerceptronInputDlg();
    ~CPerceptronInputDlg();
    vector<Perceptron::SignVector> GetDecisiveSamples()
    {
        return _clSamples;
    }
    vector<Perceptron::SignVector> GetStartWeightCoeffValues()
    {
        return _weightCoefficients;
    }
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    afx_msg void OnClickContinue();
    DECLARE_MESSAGE_MAP()
private:
    enum class Step
    {
        FIRST,
        SECOND,
        THIRD
    };
    void FirstStep();
    void SecondStep();
    void ThirdStep();
    void ClearEdits();
    void SetHeader(CString header);
    void CreateClassesSamplesControls();
    bool ParseClassSamples(vector<Perceptron::SignVector>&);
private:
    Step _step;
    int _clCount;
    int _snCount;
    CStatic *_staticClSamples;
    TwoDimensionalArray<CEdit>* _editClSamples;
    vector<Perceptron::SignVector> _clSamples;
    vector<Perceptron::SignVector> _weightCoefficients;
};