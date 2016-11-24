// TestGLView.h : interface of the CTestGLView class
//
///////////////////////////////////////////////////////////////////////////
#if !defined(AFX_TESTGLVIEW_H__59CED136_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
#define AFX_TESTGLVIEW_H__59CED136_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GLEnableView.h"
#include "DisplayDoc.h"

class CTestGLView : public CGLEnableView
{
protected: // create from serialization only
	CTestGLView();
	DECLARE_DYNCREATE(CTestGLView)

// Attributes
public:
	CDisplayDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGLView)
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnCreateGL();
	void OnDrawGL();
	void OnCreateDispList();
	int mymax(int a, int b, int c);
	
	virtual ~CTestGLView();

	BOOL m_Clear;
	float m_fSIcolor[3];
	float m_fSEcolor[3];
	float m_fSScolor[3];
	float m_fSAcolor[3];
	float m_fAEcolor[3];
	float m_fAIcolor[3];
	float m_fAAcolor[3];
	float m_fIPcolor[3];
	float m_fBKcolor[3];
	float m_fEGcolor[3];

	float m_fScolor[3];
	float m_fS2color[3];

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void VideoMode(ColorsNumber &c,ZAccuracy &z,BOOL &dbuf);
	//{{AFX_MSG(CTestGLView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHelpOglinfo();
	afx_msg void OnEnvirFlat();
	afx_msg void OnEnvirLighting();
	afx_msg void OnImageSmooth();
	afx_msg void OnImageCull();
	afx_msg void OnImageColor();
	afx_msg void OnImageEnlarge();
	afx_msg void OnImageShrink();
	afx_msg void OnUpdateEnvirLighting(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnvirFlat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImageSmooth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImageCull(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	GLenum quadricNormals;
	GLenum quadricDwStyle;
	GLenum quadricOrientation;
	void BuildQuadrDispList();
	CGLDispList quadric;
	int sceneselect;
	void BuildTessDispList();
	BOOL TessFilling;
	CGLDispList tessPolygon;
	GLdouble TessWindRule;

	CGLDispList Surface_inner;
	CGLDispList Surface_edge;
	CGLDispList Surface_surface;
	CGLDispList Surface_arc;
	CGLDispList Arc_end;
	CGLDispList Arc_inner;
	CGLDispList Arc_arc;
	CGLDispList Isolated_point;
	CGLDispList Special_point;
	CGLDispList Special_point2;

	CGLDispList Transparent_plate;
	CGLDispList Transparent_rod;

	CPoint MouseDownPoint;
	double X_Angle;
	double Y_Angle;
	double X_Distance;
	double Y_Distance;
	float m_fSize;

};

#ifndef _DEBUG  // debug version in TestGLView.cpp
//inline CTestGLDoc* CTestGLView::GetDocument()
//   { return (CTestGLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGLVIEW_H__59CED136_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
