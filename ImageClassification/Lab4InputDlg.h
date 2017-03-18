#pragma once
#include "resource.h"
#include <vector>
#include <regex>
using namespace std;


class CLab4InputDlg
    : public CDialogEx
{
public:
    CLab4InputDlg();
    ~CLab4InputDlg();
    vector<vector<SpacePoint>> GetDecisiveSamples()
    {
        return _clSamples;
    }
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    afx_msg void OnClickContinue();
    DECLARE_MESSAGE_MAP()
private:
    void CreateClassesSamplesControls();
    int ParseClassesSample(string str, vector<SpacePoint> &v);
private:
    bool _n;
    bool _firstStep = true;
    CStatic *_staticClSamples;
    CEdit   *_editClSamples;
    vector<vector<SpacePoint>> _clSamples;
};