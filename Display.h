// Display.h : main header file for the DISPLAY application
//

#if !defined(AFX_DISPLAY_H__E17FC586_1BBD_42E4_B0C0_6D5AEBF36377__INCLUDED_)
#define AFX_DISPLAY_H__E17FC586_1BBD_42E4_B0C0_6D5AEBF36377__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDisplayApp:
// See Display.cpp for the implementation of this class
//

class CDisplayApp : public CWinApp
{
public:
	CDisplayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDisplayApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAY_H__E17FC586_1BBD_42E4_B0C0_6D5AEBF36377__INCLUDED_)
