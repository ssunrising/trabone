#if !defined(AFX_COLORSELECTIONDIALOG_H__B23387FD_BC65_45F8_B00F_9EEF75F840A5__INCLUDED_)
#define AFX_COLORSELECTIONDIALOG_H__B23387FD_BC65_45F8_B00F_9EEF75F840A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorSelectionDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorSelectionDialog dialog

class CColorSelectionDialog : public CDialog
{
// Construction
public:
	CColorSelectionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CColorSelectionDialog)
	enum { IDD = IDD_CLASSIFY_COLOR };
		// NOTE: the ClassWizard will add data members here
	CStatic m_wndIS;
	CStatic m_wndSE;
	CStatic m_wndSS;
	CStatic m_wndSA;
	CStatic m_wndAI;
	CStatic m_wndAE;
	CStatic m_wndAA;
	CStatic m_wndIP;
	CStatic m_wndBK;
	CStatic m_wndEG;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSelectionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorSelectionDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSurfaceInner();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSurfaceEdge();
	afx_msg void OnSurfaceSurface();
	afx_msg void OnSurfaceArc();
	afx_msg void OnArcInner();
	afx_msg void OnArcEnd();
	afx_msg void OnArcArc();
	afx_msg void OnIsolatedPoint();
	afx_msg void OnBackground();
	afx_msg void OnEdgechange();
	afx_msg void OnEdge();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSELECTIONDIALOG_H__B23387FD_BC65_45F8_B00F_9EEF75F840A5__INCLUDED_)
