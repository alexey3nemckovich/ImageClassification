#pragma once
#include "resource.h"
#include <string>
#include <vector>
#include <regex>
using namespace std;


class CLab8InputDlg :
    public CDialogEx
{
public:
    CLab8InputDlg();
    virtual ~CLab8InputDlg();
    vector<string> GetLearningChains()
    {
        return _learningChains;
    }
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
protected:
    afx_msg void OnOk();
    DECLARE_MESSAGE_MAP()
private:
    vector<string> _learningChains;
    void ParseLearningChains(string str);
};