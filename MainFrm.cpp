// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Display.h"

#include "MainFrm.h"
#include "FormCommandView1.h"
#include "TestGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2, WS_CHILD|WS_VISIBLE))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

  // Second splitter pane
	if (!m_wndSplitter.CreateView(0, 1,
      RUNTIME_CLASS(CTestGLView), CSize(1000,1000), pContext))
	{
		TRACE("Failed to create preview pane\n");
		return FALSE;
	}
	m_pImageView = DYNAMIC_DOWNCAST (CTestGLView, m_wndSplitter.GetPane (0, 1));

	  // First splitter pane
	if (!m_wndSplitter.CreateView(0, 0,
      RUNTIME_CLASS(CFormCommandView), CSize(300,200), pContext))
	{
		TRACE("Failed to create command view pane\n");
		return FALSE;
	}
	m_pFormView = DYNAMIC_DOWNCAST (CFormCommandView, m_wndSplitter.GetPane (0, 0));


	/*return m_wndSplitter.Create(this,
		2, 2,               // TODO: adjust the number of rows, columns
		CSize(10, 10),      // TODO: adjust the minimum pane size
		pContext);*/
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	int i, j;
	CFormCommandView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pFormView;


	if(m_Temp->m_bLoad == TRUE)
	{
		for(i=0; i<m_Temp->m_iSize[0]+4; i++) 
			for(j=0; j<m_Temp->m_iSize[1]+4; j++)
				free(m_Temp->m_iMatrix[i][j]);
	
		for(i=0; i<m_Temp->m_iSize[0]+4; i++)
			free(m_Temp->m_iMatrix[i]);
		
		free(m_Temp->m_iMatrix);

		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				free(m_Temp->m_iTemp[i][j]);
		
		for(i=0; i<3; i++)
			free(m_Temp->m_iTemp[i]);

		free(m_Temp->m_iTemp);

		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				free(m_Temp->m_fTemp[i][j]);
		
		for(i=0; i<3; i++)
			free(m_Temp->m_fTemp[i]);

		free(m_Temp->m_fTemp);

		free(m_Temp->m_iSize);
	}

	if(m_Temp->m_bThinned == TRUE)
	{
		
		for(i=0; i<m_Temp->m_iSize[0]+4; i++)
			for(j=0; j<m_Temp->m_iSize[1]+4; j++)
				free(m_Temp->m_iPtType[i][j]);

		for(i=0; i<m_Temp->m_iSize[0]+4; i++)
			free(m_Temp->m_iPtType[i]);
		
		free(m_Temp->m_iPtType);
	}

	if(m_Temp->m_bClassified == TRUE)
	{
		for(i=0; i<m_Temp->m_iSize[0]+4; i++) 
			for(j=0; j<m_Temp->m_iSize[1]+4; j++)
				free(m_Temp->m_iCrPnts[i][j]);
	
		for(i=0; i<m_Temp->m_iSize[0]+4; i++)
			free(m_Temp->m_iCrPnts[i]);
		
		free(m_Temp->m_iCrPnts);
	}
		
	/*	if(m_Temp->m_bCurveMeshed == TRUE)
	{
		for(i=0; i<1000; i++)
			free(m_Temp->m_iNodelist[i]);
		
		free(m_Temp->m_iNodelist);

		
		free(m_Temp->m_fCurvethickness);
	}*/

	if(m_Temp->m_bPClustered == TRUE)
	{
		for(i=0; i<=m_Temp->m_iClusterNo; i++)
			free(m_Temp->m_iCluster[i]);

		free(m_Temp->m_iCluster);

		for(i=0; i<=m_Temp->m_iTraNo; i++)
			free(m_Temp->m_iConnection[i]);

		free(m_Temp->m_iConnection);

		for(i=0; i<m_Temp->m_iNodelistSize; i++)
			free(m_Temp->m_iNodelist[i]);

		free(m_Temp->m_iNodelist);

	}

	if(m_Temp->m_bRecovered == TRUE)
	{
		for(i=0; i<=m_Temp->m_iTraNo; i++)
		{
			free(m_Temp->m_fNorm[i]);
		}
		free(m_Temp->m_fNorm);

		for(i=0; i<=m_Temp->m_iTraNo; i++)
		{
			free(m_Temp->m_fTh[i]);
		}
		free(m_Temp->m_fTh);
	}

	if(m_Temp->m_bStepShow == TRUE)
	{
		for(i=0; i<=m_Temp->m_iTraNo; i++)
		{
			free(m_Temp->m_iStepFailure[i]);
		}
		free(m_Temp->m_iStepFailure);
	}

	if(m_Temp->m_bBklLoad == TRUE)
	{
		for(i=0; i<m_Temp->m_iSize[0]+4; i++) 
			for(j=0; j<m_Temp->m_iSize[1]+4; j++)
				free(m_Temp->m_iLabel[i][j]);
	
		for(i=0; i<m_Temp->m_iSize[0]+4; i++)
			free(m_Temp->m_iLabel[i]);

		free(m_Temp->m_iLabel);

		for(i=0; i<=m_Temp->m_iTotalNo; i++) 
			for(j=0; j<6; j++)
				free(m_Temp->m_fStrain[i][j]);
	
		for(i=0; i<=m_Temp->m_iTotalNo; i++)
			free(m_Temp->m_fStrain[i]);

		free(m_Temp->m_fStrain);

		for(i=0; i<=m_Temp->m_iTotalNo; i++) 
			for(j=0; j<6; j++)
				free(m_Temp->m_fStress[i][j]);
	
		for(i=0; i<=m_Temp->m_iTotalNo; i++)
			free(m_Temp->m_fStress[i]);

		free(m_Temp->m_fStress);

		free(m_Temp->m_iFail);

		for(i=0; i<=m_Temp->m_iTotalNo; i++)
		{
			free(m_Temp->m_iStepCT[i]);
		}
		free(m_Temp->m_iStepCT);
	}
	return CFrameWnd::DestroyWindow();

}

