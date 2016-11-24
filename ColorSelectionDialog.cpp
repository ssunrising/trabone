// ColorSelectionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Display.h"
#include "ColorSelectionDialog.h"
#include "TestGLView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorSelectionDialog dialog


CColorSelectionDialog::CColorSelectionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CColorSelectionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorSelectionDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CColorSelectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorSelectionDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_IS, m_wndIS);
	DDX_Control(pDX, IDC_SE, m_wndSE);
	DDX_Control(pDX, IDC_SS, m_wndSS);
	DDX_Control(pDX, IDC_SA, m_wndSA);
	DDX_Control(pDX, IDC_AI, m_wndAI);
	DDX_Control(pDX, IDC_AA, m_wndAA);
	DDX_Control(pDX, IDC_AE, m_wndAE);
	DDX_Control(pDX, IDC_IP, m_wndIP);
	DDX_Control(pDX, IDC_BK, m_wndBK);
	DDX_Control(pDX, IDC_EG, m_wndEG);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorSelectionDialog, CDialog)
	//{{AFX_MSG_MAP(CColorSelectionDialog)
	ON_BN_CLICKED(IDC_SURFACE_INNER, OnSurfaceInner)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SURFACE_EDGE, OnSurfaceEdge)
	ON_BN_CLICKED(IDC_SURFACE_SURFACE, OnSurfaceSurface)
	ON_BN_CLICKED(IDC_SURFACE_ARC, OnSurfaceArc)
	ON_BN_CLICKED(IDC_ARC_INNER, OnArcInner)
	ON_BN_CLICKED(IDC_ARC_END, OnArcEnd)
	ON_BN_CLICKED(IDC_ARC_ARC, OnArcArc)
	ON_BN_CLICKED(IDC_ISOLATED_POINT, OnIsolatedPoint)
	ON_BN_CLICKED(IDC_BACKGROUND, OnBackground)
	ON_BN_CLICKED(IDC_EDGE, OnEdge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorSelectionDialog message handlers

BOOL CColorSelectionDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CColorSelectionDialog::OnSurfaceInner() 
{
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fSIcolor[0] = a/255;
	m_Temp->m_fSIcolor[1] = b/255;
	m_Temp->m_fSIcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndIS.m_hWnd));

	RECT rc;
	m_wndIS.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
//	pDC->DeleteDC();
//	delete pDC;
}

void CColorSelectionDialog::OnSurfaceEdge() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fSEcolor[0] = a/255;
	m_Temp->m_fSEcolor[1] = b/255;
	m_Temp->m_fSEcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndSE.m_hWnd));

	RECT rc;
	m_wndIS.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
	
}





void CColorSelectionDialog::OnSurfaceSurface() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fSScolor[0] = a/255;
	m_Temp->m_fSScolor[1] = b/255;
	m_Temp->m_fSScolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndSS.m_hWnd));

	RECT rc;
	m_wndIS.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
}

void CColorSelectionDialog::OnSurfaceArc() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fSAcolor[0] = a/255;
	m_Temp->m_fSAcolor[1] = b/255;
	m_Temp->m_fSAcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndSA.m_hWnd));

	RECT rc;
	m_wndSA.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);

	
}

void CColorSelectionDialog::OnArcInner() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fAIcolor[0] = a/255;
	m_Temp->m_fAIcolor[1] = b/255;
	m_Temp->m_fAIcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndAI.m_hWnd));

	RECT rc;
	m_wndAI.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
	
}

void CColorSelectionDialog::OnArcEnd() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fAEcolor[0] = a/255;
	m_Temp->m_fAEcolor[1] = b/255;
	m_Temp->m_fAEcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndAE.m_hWnd));

	RECT rc;
	m_wndAE.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
	
}

void CColorSelectionDialog::OnArcArc() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fAAcolor[0] = a/255;
	m_Temp->m_fAAcolor[1] = b/255;
	m_Temp->m_fAAcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndAA.m_hWnd));

	RECT rc;
	m_wndAA.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
	
}

void CColorSelectionDialog::OnIsolatedPoint() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fIPcolor[0] = a/255;
	m_Temp->m_fIPcolor[1] = b/255;
	m_Temp->m_fIPcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndIP.m_hWnd));

	RECT rc;
	m_wndIP.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
	
}

void CColorSelectionDialog::OnBackground() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fBKcolor[0] = a/255;
	m_Temp->m_fBKcolor[1] = b/255;
	m_Temp->m_fBKcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndBK.m_hWnd));

	RECT rc;
	m_wndBK.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
	
}

void CColorSelectionDialog::OnEdge() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=  CC_FULLOPEN |CC_RGBINIT;

	dlg.DoModal();

	COLORREF color = dlg.GetColor();

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	float a = float(GetRValue(color));
	float b = float(GetGValue(color));
	float c = float(GetBValue(color));

	m_Temp->m_fEGcolor[0] = a/255;
	m_Temp->m_fEGcolor[1] = b/255;
	m_Temp->m_fEGcolor[2] = c/255;

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndEG.m_hWnd));

	RECT rc;
	m_wndEG.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	m_Temp->Invalidate(TRUE);
}

void CColorSelectionDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;

	COLORREF color = RGB(255*(m_Temp->m_fSIcolor[0]), 255*(m_Temp->m_fSIcolor[1]), 255*(m_Temp->m_fSIcolor[2]));

	CDC* pDC;
	pDC = CDC::FromHandle(::GetDC(m_wndIS.m_hWnd));
	RECT rc;
	m_wndIS.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
//	pDC->DeleteDC();
//	delete pDC;

	color = RGB(255*(m_Temp->m_fSEcolor[0]), 255*(m_Temp->m_fSEcolor[1]), 255*(m_Temp->m_fSEcolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndSE.m_hWnd));
	m_wndSE.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));

	color = RGB(255*(m_Temp->m_fSScolor[0]), 255*(m_Temp->m_fSScolor[1]), 255*(m_Temp->m_fSScolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndSS.m_hWnd));
	m_wndSS.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));
	
	color = RGB(255*(m_Temp->m_fSAcolor[0]), 255*(m_Temp->m_fSAcolor[1]), 255*(m_Temp->m_fSAcolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndSA.m_hWnd));
	m_wndSA.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));

	color = RGB(255*(m_Temp->m_fAIcolor[0]), 255*(m_Temp->m_fAIcolor[1]), 255*(m_Temp->m_fAIcolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndAI.m_hWnd));
	m_wndAI.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));

	color = RGB(255*(m_Temp->m_fAEcolor[0]), 255*(m_Temp->m_fAEcolor[1]), 255*(m_Temp->m_fAEcolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndAE.m_hWnd));
	m_wndAE.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));

	color = RGB(255*(m_Temp->m_fAAcolor[0]), 255*(m_Temp->m_fAAcolor[1]), 255*(m_Temp->m_fAAcolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndAA.m_hWnd));
	m_wndAA.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));

	color = RGB(255*(m_Temp->m_fIPcolor[0]), 255*(m_Temp->m_fIPcolor[1]), 255*(m_Temp->m_fIPcolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndIP.m_hWnd));
	m_wndIP.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));

	color = RGB(255*(m_Temp->m_fBKcolor[0]), 255*(m_Temp->m_fBKcolor[1]), 255*(m_Temp->m_fBKcolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndBK.m_hWnd));
	m_wndBK.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));

	color = RGB(255*(m_Temp->m_fEGcolor[0]), 255*(m_Temp->m_fEGcolor[1]), 255*(m_Temp->m_fEGcolor[2]));
	pDC = CDC::FromHandle(::GetDC(m_wndEG.m_hWnd));
	m_wndEG.GetClientRect(&rc);
	pDC->FillRect(&rc, &CBrush(color));

	// Do not call CDialog::OnPaint() for painting messages
}



