#if !defined(AFX_RESOLUTIONDIALOG_H__0E9FC703_B738_427C_B4AC_ED24C0DC0EB1__INCLUDED_)
#define AFX_RESOLUTIONDIALOG_H__0E9FC703_B738_427C_B4AC_ED24C0DC0EB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResolutionDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResolutionDialog dialog

class CResolutionDialog : public CDialog
{
// Construction
public:
	CResolutionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResolutionDialog)
	enum { IDD = IDD_RESOLUTION };
	float	m_resolution[3];
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResolutionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResolutionDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESOLUTIONDIALOG_H__0E9FC703_B738_427C_B4AC_ED24C0DC0EB1__INCLUDED_)
