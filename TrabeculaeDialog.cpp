// TrabeculaeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Display.h"
#include "TrabeculaeDialog.h"
#include "FormCommandView1.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrabeculaeDialog dialog


CTrabeculaeDialog::CTrabeculaeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTrabeculaeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrabeculaeDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_Trabeculae = 1;
	//}}AFX_DATA_INIT
}


void CTrabeculaeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrabeculaeDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_EDIT1, m_Trabeculae);
	//DDV_MinMaxInt(pDX, m_Trabeculae, 1, 200);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrabeculaeDialog, CDialog)
	//{{AFX_MSG_MAP(CTrabeculaeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrabeculaeDialog message handlers

void CTrabeculaeDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CFormCommandView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pFormView;
	m_Temp->m_iTraSelect = m_Trabeculae;

	CDialog::OnOK();
}
