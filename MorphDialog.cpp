// MorphDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Display.h"
#include "MorphDialog.h"
#include "FormCommandView1.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMorphDialog dialog


CMorphDialog::CMorphDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMorphDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMorphDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_strMorph = _T("");
	//}}AFX_DATA_INIT
}


void CMorphDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMorphDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		DDX_Text(pDX, IDC_STATIC_MORPH, m_strMorph);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMorphDialog, CDialog)
	//{{AFX_MSG_MAP(CMorphDialog)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMorphDialog message handlers

int CMorphDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CFormCommandView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pFormView;
	m_strMorph.Format(_T("BVF = %.5f \nRod-Rod Junction No = %.0f \nRod-Plate Junction No = %.0f \nPlate-Plate Junction No = %.0f"), m_Temp->m_fBVF, m_Temp->m_fRRJNo, m_Temp->m_fRPJNo, m_Temp->m_fPPJNo);
	return 0;
}
