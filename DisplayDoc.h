// DisplayDoc.h : interface of the CDisplayDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYDOC_H__6228FAC6_462C_492E_A489_9FAC6CE8A48E__INCLUDED_)
#define AFX_DISPLAYDOC_H__6228FAC6_462C_492E_A489_9FAC6CE8A48E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDisplayDoc : public CDocument
{
protected: // create from serialization only
	CDisplayDoc();
	DECLARE_DYNCREATE(CDisplayDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDisplayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYDOC_H__6228FAC6_462C_492E_A489_9FAC6CE8A48E__INCLUDED_)
