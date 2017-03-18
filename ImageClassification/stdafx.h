
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


typedef struct LogicPoint {
    double x;
    double y;

    LogicPoint()
    {
        x = y = 0;
    }

    LogicPoint(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    LogicPoint(CPoint p)
    {
        this->x = p.x;
        this->y = p.y;
    }

    bool operator==(const LogicPoint &other) const
    {
        if (other.x == x && other.y == y)
        {
            return true;
        }
        return false;
    }
};


typedef struct SpacePoint {
    int x;
    int y;
    int z;

    SpacePoint()
    {
        x = y = z = 0;
    }

    SpacePoint(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    SpacePoint* operator+=(const SpacePoint& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return this;
    }
    
    SpacePoint* operator-=(const SpacePoint& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return this;
    }

    int operator*(SpacePoint other)
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }
};
typedef SpacePoint DecisionFunctionWeightVector;


double RandomDouble(double a, double b);
double RandomInt(int a, int b);