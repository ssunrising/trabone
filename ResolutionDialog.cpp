// ResolutionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Display.h"
#include "ResolutionDialog.h"
#include "FormCommandView1.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResolutionDialog dialog


CResolutionDialog::CResolutionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CResolutionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResolutionDialog)
	m_resolution[0] = 68.5;
	m_resolution[1] = 68.5;
	m_resolution[2] = 102.5;
	//}}AFX_DATA_INIT
}


void CResolutionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResolutionDialog)
	DDX_Text(pDX, IDC_EDIT1, m_resolution[0]);
	DDX_Text(pDX, IDC_EDIT2, m_resolution[1]);
	DDX_Text(pDX, IDC_EDIT3, m_resolution[2]);
	DDV_MinMaxFloat(pDX, m_resolution[0], 1, 200);
	DDV_MinMaxFloat(pDX, m_resolution[1], 1, 200);
	DDV_MinMaxFloat(pDX, m_resolution[2], 1, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResolutionDialog, CDialog)
	//{{AFX_MSG_MAP(CResolutionDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResolutionDialog message handlers

void CResolutionDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CFormCommandView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pFormView;
	m_Temp->m_resolution[0] = m_resolution[0];
	m_Temp->m_resolution[1] = m_resolution[1];
	m_Temp->m_resolution[2] = m_resolution[2];

	CDialog::OnOK();
}
