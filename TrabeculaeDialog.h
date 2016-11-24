#if !defined(AFX_TRABECULAEDIALOG_H__2DC1BC3F_D2CB_4772_8250_491C6ED559E4__INCLUDED_)
#define AFX_TRABECULAEDIALOG_H__2DC1BC3F_D2CB_4772_8250_491C6ED559E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrabeculaeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrabeculaeDialog dialog

class CTrabeculaeDialog : public CDialog
{
// Construction
public:
	CTrabeculaeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTrabeculaeDialog)
	enum { IDD = IDD_TRABECULAE };
	int		m_Trabeculae;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrabeculaeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrabeculaeDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRABECULAEDIALOG_H__2DC1BC3F_D2CB_4772_8250_491C6ED559E4__INCLUDED_)
