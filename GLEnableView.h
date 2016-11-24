#if !defined(AFX_GLEnableView_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
#define AFX_GLEnableView_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CGLEnableView.h : header file
//
#include "gl/gl.h"
#include "gl/glaux.h"
/////////////////////////////////////////////////////////////////////////////
// Global type definitions
	enum InfoField {VENDOR,RENDERER,VERSION,ACCELERATION,EXTENSIONS};
	enum ColorsNumber{INDEXED,THOUSANDS,MILLIONS,MILLIONS_WITH_TRANSPARENCY};
	enum ZAccuracy{NORMAL,ACCURATE};

/////////////////////////////////////////////////////////////////////////////
// CGLEnableView view

class CGLEnableView : public CView
{
protected:
	CGLEnableView();// protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGLEnableView)
/** CGLDispList
DESC:-this is an helper class which let you create "display list objects",
       use these objects to define the key elements in your scene (a disp.
	   list is faster than the corresponding GL commands).
      -Through the class members functions you have total control on a
       single display list.
      -An isolated display list save OGL parameters before execution
	   (so it's not affected by preceding transformations or settings).
*******/
	class CGLDispList
	{
	friend class CGLEnableView;
	private:
		BOOL m_bIsolated;
		int m_glListId;
	public:
		CGLDispList();  // constructor
		~CGLDispList(); // destructor
		void StartDef(BOOL bImmediateExec=FALSE);// enclose a disp.list def.
		void EndDef();
		void Draw();// execute disp list GL commands 
		void SetIsolation(BOOL bValue) {m_bIsolated=bValue;}; // set isolation property
	};


// Attributes
public:
	BOOL m_Clear;
// Operations
public:
/* Stock Display lists functions
DESC.: these display lists are internally organized in a vector (20 max),
       you have control on definition and redrawing only. 
       use them for background elements which are to be drawn everytime
       all together.
NOTE: between BeginStockDispList and EndStockDispList should be present OpenGL calls only (see documentation for which are allowed and how are them treated)
*/
	void StartStockDListDef();	// allocates a new stock display list entry and opens a display list definition
	void EndStockListDef();		// closes a stock display list definition
	void DrawStockDispLists();	// executes all the stock display lists
	void ClearStockDispLists(); // deletes all the stock display lists
// Information retrieval function
	const CString GetInformation(InfoField type);
// Mouse cursor function
	void SetMouseCursor(HCURSOR mcursor=NULL);
// Attribute retrieval function
	double GetAspectRatio() {return m_dAspectRatio;};
// Rendering Context switching
	void BeginGLCommands();// use to issue GL commands outside Overridables
	void EndGLCommands();// i.e: in menu event handlers, button events handler etc.
// Overridables
	virtual void OnCreateGL(); // override to set bg color, activate z-buffer, and other global settings
	virtual void OnSizeGL(int cx, int cy); // override to adapt the viewport to the window
	virtual void OnDrawGL(); // override to issue drawing functions
	virtual void VideoMode(ColorsNumber &c,ZAccuracy &z,BOOL &dbuf); // override to specify some video mode parameters

// Overrides
// NOTE: these have been declared private because they shouldn't be
//		 overridden, use the provided virtual functions instead.
private:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLEnableView)
	public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGLEnableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
// NOTE: these have been declared private because they shouldn't be
//		 overridden, use the provided virtual functions instead.
private:
	//{{AFX_MSG(CGLEnableView)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnDestroy();
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// member variables
private:
	CDC* m_pCDC;	// WinGDI Device Context
	HGLRC m_hRC;	// OpenGL Rendering Context
	HCURSOR m_hMouseCursor;	// mouse cursor handle for the view
	CPalette m_CurrentPalette; // palettes
	CPalette* m_pOldPalette;
	CRect m_ClientRect;    // client area size
	double m_dAspectRatio;    // aspect
	int m_DispListVector[20];	// Internal stock display list vector
	BOOL m_bInsideDispList;	// Disp List definition semaphore
	BOOL m_bExternGLCall;
	BOOL m_bExternDispListCall;
// initialization helper functions
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	void CreateRGBPalette();
	BOOL bSetupPixelFormat();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLEnableView_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
