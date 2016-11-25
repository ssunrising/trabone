// FormCommandView1.cpp : implementation file
//

#include "stdafx.h"
#include "Display.h"
#include "FormCommandView1.h"
#include "TestGLView.h"
#include "MainFrm.h"

#include "Primary_Thinning.h"
#include "Shape_Point.h"
#include "Simple_Point.h"
#include "Final_Thinning.h"
#include "Initial_Type.h"
#include "Final_Type.h"
#include "Arc_Thinning.h"
#include "ResolutionDialog.h"
#include "TrabeculaeDialog.h"
#include "Recover.h"
#include "Cluster.h"
#include "MorphDialog.h"
#include "EigenSystem.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXNUM 9999
#define THINLAYER 0
#define	SSlength 0
#define	SClength 0
#define	CClength 0

#define WRITEINPUT
//for debug mode
int Debug_ith = 0;
int Debug_thr = -MAXNUM;
int Debug_change = 1;

//#define DEBUG_THINNING
int tab3b[16],
	tab4a[16],
    tab4b[128],
	tab5[4096],
	tab6[4096][2];

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView

IMPLEMENT_DYNCREATE(CFormCommandView, CFormView)

CFormCommandView::CFormCommandView()
	: CFormView(CFormCommandView::IDD)
{
	//{{AFX_DATA_INIT(CFormCommandView)
		// NOTE: the ClassWizard will add member initialization here
		m_bLoad = FALSE;
		m_bBklLoad = FALSE;
		m_bStepShow = FALSE;
		m_bClassified = FALSE;
		m_bRecovered = FALSE;
		m_bPClustered = FALSE;
		m_bThinned = FALSE;
		m_bArcThinned = FALSE;
		m_bDebugmode = FALSE;
		m_bDebugProcess = FALSE;
		m_bCurveMeshed = FALSE;
		m_bTrasep = FALSE;
		m_bMesh = FALSE;
		m_strSize = _T("");
		m_strDisp = _T("");
		m_strDisp = _T("");
		m_iTraSelect = 1;
		m_iStepSelect = 0;
		m_fBVF = 0;		//BV/TV
		m_fPBVF = 0;		//Plate volume/TV
		m_fRBVF = 0;		//Rod volume/TV
		m_fPThickness = 0;	//Plate Thickness(mm)
		m_fRDiameter = 0;	//Rod radius(mm)
		m_fPSurface = 0;	//Plate length(mm)
		m_fRLength = 0;	//Rod length(mm)
		m_fJuncNo = 0;		//Total Junction No/TV (1/mm^3)
		m_fRRJNo = 0;			//Rod-Rod Junction No/TV(1/mm^3)
		m_fRPJNo = 0;			//Rod-Plate Junction No/TV(1/mm^3)
		m_fPNo = 0;			//Plate No/TV(1/mm^3)
		m_fRNo = 0;			//Rod No/TV(1/mm^3)

		m_fPBVF_s = 0;	//pBV/TV of simplified model
		m_fRBVF_s = 0;	//rBV/TV of simplified model
	//}}AFX_DATA_INIT
}

CFormCommandView::~CFormCommandView()
{
}

void CFormCommandView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormCommandView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		//DDV_MinMaxInt(pDX, m_iTraSelect, 1, 300);
		DDX_Text(pDX, IDC_DISPLAYSIZE, m_strSize);
		DDX_Text(pDX, IDC_DISPLAY, m_strDisp);
		DDX_Text(pDX, IDC_STATIC_DEBUG, m_strDebug);
		DDX_Text(pDX, IDC_TRANUMBER, m_iTraSelect);
		DDX_Text(pDX, IDC_STEPNUMBER, m_iStepSelect);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFormCommandView, CFormView)
	//{{AFX_MSG_MAP(CFormCommandView)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_THINNING, OnThinning)
	ON_BN_CLICKED(IDC_CLASSIFY, OnClassify)
	ON_BN_CLICKED(IDC_ARCTHINNING, OnArcthinning)
	ON_BN_CLICKED(IDC_PRIMARY, OnPrimary)
	ON_BN_CLICKED(IDC_FINAL, OnFinal)
	ON_BN_CLICKED(IDC_DEBUGSTART, OnDebugstart)
	ON_BN_CLICKED(IDC_DEBUGEND, OnDebugend)
	ON_BN_CLICKED(IDC_RECORD_CLASSIFY, OnRecordClassify)
	ON_BN_CLICKED(IDC_CLUSTER, OnCluster)
	ON_BN_CLICKED(IDC_RECOVER, OnRecover)
	ON_BN_CLICKED(IDC_RECOVER2, OnRecoverPlate)
	ON_BN_CLICKED(IDC_RECOVER3, OnRecoverRod)
	ON_BN_CLICKED(IDC_PLATECLUSTER, OnPlatecluster)
	ON_BN_CLICKED(IDC_ARC_CLASSIFY, OnArcClassify)
	ON_COMMAND(ID_TOOL_TRASEP, OnToolTrasep)
	ON_UPDATE_COMMAND_UI(ID_TOOL_TRASEP, OnUpdateToolTrasep)
	ON_COMMAND(ID_TOOL_PARAMETER, OnToolParameter)
	ON_UPDATE_COMMAND_UI(ID_TOOL_PARAMETER, OnUpdateToolParameter)
	ON_BN_CLICKED(IDC_INCREASE, OnIncrease)
	ON_BN_CLICKED(IDC_DECREASE, OnDecrease)
	ON_COMMAND(ID_TOOL_MORPH, OnToolMorph)
	ON_UPDATE_COMMAND_UI(ID_TOOL_MORPH, OnUpdateToolMorph)
	ON_COMMAND(ID_TOOL_SAVEBINARY, OnToolSavebinary)
	ON_UPDATE_COMMAND_UI(ID_TOOL_SAVEBINARY, OnUpdateToolSavebinary)
	ON_BN_CLICKED(IDC_ARCPRIMARY, OnArcprimary)
	ON_BN_CLICKED(IDC_ARCFINAL, OnArcfinal)
	ON_COMMAND(ID_TOOL_BKLDATA, OnToolBkldata)
	ON_COMMAND(ID_TOOL_STRESS, OnToolStress)
	ON_UPDATE_COMMAND_UI(ID_TOOL_STRESS, OnUpdateToolStress)
	ON_BN_CLICKED(IDC_STEPINCREASE, OnStepincrease)
	ON_BN_CLICKED(IDC_STEPDECREASE, OnStepdecrease)
	ON_COMMAND(ID_TOOL_BINARY, OnToolBinary)
	ON_COMMAND(ID_TOOL_PFCAL, OnToolPfcal)
	ON_COMMAND(IDC_TOOL_MULTISELECT, OnToolMultiselect)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDOK, OnOK)
	ON_COMMAND(IDC_TOOL_MESH, OnToolMesh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView diagnostics

#ifdef _DEBUG
void CFormCommandView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormCommandView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView message handlers

void CFormCommandView::OnLoad() 
{
	// TODO: Add your control notification handler code here
	
//	if(m_bDebugmode == TRUE)
//	{
//		MessageBox(_T(" Please quit debugging mode first! "));
//		return;
//	}
	int i,j,k;
	int	 rc=0;
	unsigned char m_char;

	CFile m_file;

	
	if(m_bLoad == FALSE)
	{
		/**** loading the look_up_table from Saha's table ****/
		FILE *fp;
		unsigned char a,b;

		if((fp = fopen ("tab3b", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
			tab3b[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab4a", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab4a[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab4b", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab4b[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab5", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab5[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab6", "r")) != NULL)
		{
			i=0;
			while (fscanf(fp, "%d %d\n", &a, &b) == 2) 
			{
				tab6[i][0] = a;
				tab6[i][1] = b;
				i = i + 1;
			}
			fclose(fp);
		}

		/*m_iTemp is for storing the 27 points configuration(0/1) in simple point detection and classification*/
		m_iTemp = (int ***)calloc(3, sizeof(int**));
		for(i=0; i<=2; i++)
		{
			m_iTemp[i] = (int **)calloc(3, sizeof(int*));
		}
		for(i=0; i<=2; i++)
		{
			for(j=0; j<=2; j++)
			{
				m_iTemp[i][j] = (int *)calloc(3, sizeof(int));
			}
		}

		for(i=0; i<=2; i++)
			for(j=0; j<=2; j++)
				for(k=0; k<=2; k++)
					m_iTemp[i][j][k] = 0;

		m_iSize = (int*)malloc(sizeof(int) * 3);
	}

	m_resolution[0] = 82;
	m_resolution[1] = 82;
	m_resolution[2] = 82;
	//CResolutionDialog Rdlg;
	//Rdlg.DoModal();

	m_file.Abort();

	CFileDialog fPartDlg(TRUE, NULL, NULL);
	fPartDlg.DoModal();
	rc = m_file.Open(fPartDlg.GetPathName().GetBuffer(0), CFile::modeRead);
	m_strPath = fPartDlg.GetFileName();
	int NLength = m_strPath.GetLength();
	m_strPath = fPartDlg.GetPathName();
	int PLength = m_strPath.GetLength();
	m_strPath.Delete(PLength-NLength, NLength);
	m_strPath.Insert(m_strPath.GetLength(), fPartDlg.GetFileTitle());
	
	/*rc = m_file.Open(m_strPath.GetBuffer(0), CFile::modeRead);
		
	if(rc == 0)
	{
		MessageBox(TEXT("Invalid Pathname!"), MB_OK, NULL);
		return;
	}

	int Length = m_strPath.GetLength();
	m_strPath.Delete(Length-4, 4);*/
	
	if(m_bLoad == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++) 
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iMatrix[i][j]);
	
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iMatrix[i]);
		
		free(m_iMatrix);

		m_fBVF = 0;		//BV/TV
		m_fPBVF = 0;		//Plate volume/TV
		m_fRBVF = 0;		//Rod volume/TV
		m_fPThickness = 0;	//Plate Thickness(mm)
		m_fRDiameter = 0;	//Rod radius(mm)
		m_fPSurface = 0;	//Plate length(mm)
		m_fRLength = 0;	//Rod length(mm)
		m_fJuncNo = 0;		//Total Junction No/TV (1/mm^3)
		m_fRRJNo = 0;			//Rod-Rod Junction No/TV(1/mm^3)
		m_fRPJNo = 0;			//Rod-Plate Junction No/TV(1/mm^3)
		m_fPNo = 0;			//Plate No/TV(1/mm^3)
		m_fRNo = 0;			//Rod No/TV(1/mm^3)
		m_fPBVF_s = 0;	//pBV/TV of simplified model
		m_fRBVF_s = 0;	//rBV/TV of simplified model
	}

	if(m_bThinned == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++)
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iPtType[i][j]);
		
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iPtType[i]);

		free(m_iPtType);
	}

	if(m_bClassified == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++)
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iCrPnts[i][j]);
		
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iCrPnts[i]);

		free(m_iCrPnts);
	}		

	/*if(m_bCurveMeshed == TRUE)
	{
		for(i=0; i<1000; i++)
			free(m_iNodelist[i]);

		free(m_iNodelist);

		for(i=0; i<1000; i++)
			free(m_iCurvelist[i]);

		free(m_iCurvelist);
	}*/

	if(m_bPClustered == TRUE)
	{
		for(i=0; i <= m_iClusterNo; i++)
			free(m_iCluster[i]);

		for(i=0; i < m_iNodelistSize; i++)
			free(m_iNodelist[i]);

		for(i=0; i <= m_iTraNo; i++)
			free(m_iConnection[i]);

		free(m_iCluster);
		free(m_iNodelist);
		free(m_iConnection);
	}

	if(m_bRecovered == TRUE)
	{
		for(i=0; i<=m_iTraNo; i++)
		{
			free(m_fNorm[i]);
		}
		free(m_fNorm);

		for(i=0; i<=m_iTraNo; i++)
		{
			free(m_fTh[i]);
		}
		free(m_fTh);
	}

	if(m_bStepShow == TRUE)
	{
		for(i=0; i<=m_iTraNo; i++)
		{
			free(m_iStepFailure[i]);
		}
		free(m_iStepFailure);
	}
	if(m_bBklLoad == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++) 
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iLabel[i][j]);
	
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iLabel[i]);

		free(m_iLabel);

		for(i=0; i<=m_iTotalNo; i++) 
			for(j=0; j<6; j++)
				free(m_fStrain[i][j]);
	
		for(i=0; i<=m_iTotalNo; i++)
			free(m_fStrain[i]);

		free(m_fStrain);

		for(i=0; i<=m_iTotalNo; i++) 
			for(j=0; j<6; j++)
				free(m_fStress[i][j]);
	
		for(i=0; i<=m_iTotalNo; i++)
			free(m_fStress[i]);

		free(m_fStress);

		free(m_iFail);

		for(i=0; i<=m_iTotalNo; i++)
		{
			free(m_iStepCT[i]);
		}
		free(m_iStepCT);
	}
		

	m_bBklLoad = FALSE;
	m_bStepShow = FALSE;
	m_bThinned = FALSE;
	m_bArcThinned = FALSE;
	m_bClassified = FALSE;
	m_bDebugmode = FALSE;
	m_bRecovered = FALSE;
	m_bPClustered = FALSE;
	m_bCurveMeshed = FALSE;
	m_bTrasep = FALSE;
	m_bMesh = FALSE;

	/**************** Begin loading data *******************/
	m_strDisp.Format(_T("Start Loading Data"));
	UpdateData( FALSE );

	m_bLoad = TRUE;

/*	m_file.Seek(160, CFile::begin);
	m_file.Read(&m_char, 1);
	m_iSize[0] = (int)m_char;
//	m_file.Read(&m_char, 1);
//	m_iSize[0] = (int)m_char+256*m_iSize[0];

	m_file.Seek(164, CFile::begin);
	m_file.Read(&m_char, 1);
	m_iSize[1] = (int)m_char;
//	m_file.Read(&m_char, 1);
//	m_iSize[1] = (int)m_char+256*m_iSize[1];

	m_file.Seek(168, CFile::begin);
	m_file.Read(&m_char, 1);
	m_iSize[2] = (int)m_char;
//	m_file.Read(&m_char, 1);
//	m_iSize[2] = (int)m_char+256*m_iSize[2];*/

	m_iSize[0] = 52;
	m_iSize[1] = 51;
	m_iSize[2] = 23;

	m_data = std::vector<std::vector<std::vector<int> > >(52 + 4, std::vector<std::vector<int> >(51 + 4, std::vector<int>(23 + 4)));

	m_iMatrix = (int ***)calloc(m_iSize[0]+4, sizeof(int**));
	for(i=0; i<m_iSize[0]+4; i++)
	{
		m_iMatrix[i] = (int **)calloc(m_iSize[1]+4, sizeof(int*));
	}
	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			m_iMatrix[i][j] = (int *)calloc(m_iSize[2]+4, sizeof(int));
		}
	}

//	m_file.Seek(192, CFile::begin);

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				m_file.Read(&m_char,1);
				m_iMatrix[i][j][k] = (int)m_char;
				m_data[i][j][k] = (int)m_char;
				if(m_iMatrix[i][j][k]>0)
					m_iMatrix[i][j][k] = m_iMatrix[i][j][k];
//				m_file.Read(&m_char,1);
//				m_iMatrix[i][j][k] = m_iMatrix[i][j][k]*256+(int)m_char;
			
				m_iMatrix[i][j][k] = !!(int)m_char;
			}
		}
	}

	int temp=0;

	for(k=2; k<m_iSize[2]+2; k++)
	{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k]> 0)
						temp++;
				}
			}
	}

	hoshen_kopelman2(m_iMatrix, m_iSize);

	/*for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
				if(i < 2+5 || j < 2+5 || k < 2+5 || i > m_iSize[0] + 1 -5 || j > m_iSize[1] + 1-5 || k > m_iSize[2] + 1-5)
					m_iMatrix[i][j][k] = 0;*/

	OnCluster();


	temp=0;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]> 0)
					temp++;
			}
		}
	}

	m_fBVF = float(float(temp)/float(m_iSize[0])/float(m_iSize[1])/float(m_iSize[2]));

	m_strDisp.Format(_T("Data Loading Sucessfully!"));
	m_strSize.Format(_T("The Image Size is   x=%d,   y=%d,   z=%d"), m_iSize[0], m_iSize[1], m_iSize[2]);
	m_strDebug.Format(_T(""));
	UpdateData( FALSE );

	CFormCommandView::OnToolMesh();

/******************** End of Loading Data *************************/
}

void CFormCommandView::OnThinning() 
{
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bThinned == TRUE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bDebugmode == TRUE)
	{
		MessageBox(_T(" Please quit debugging mode first! "));
		return;
	}

	m_bThinned = TRUE;

	/******************************************************************
	*      primary thinning --3 scans in each iteration               *
	*******************************************************************/	

	bool change =1;  		/*if any pt is deleted in the last iteration, change =1*/
	int ith=0;			/*ith is the iteration time*/
	int thr = - MAXNUM;

	int i,j,k;

	//malloc the memory space for point type
	m_iPtType = (int ***)calloc(m_iSize[0]+4, sizeof(int**));

	for(i=0; i<m_iSize[0]+4; i++)
	{
		m_iPtType[i] = (int **)calloc(m_iSize[1]+4, sizeof(int*));
	}

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			m_iPtType[i][j] = (int *)calloc(m_iSize[2]+4, sizeof(int));
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				//initiate the data
				m_iPtType[i][j][k] = 0;
			}
		}
	}

	m_strDisp.Format(_T("Start Thinning!"));
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				//initiate the data
				if(m_iMatrix[i][j][k] == 0)
				{
					m_iMatrix[i][j][k] = -MAXNUM;
				}
				else if(m_iMatrix[i][j][k] >= 1)
				{
					m_iMatrix[i][j][k] = 0;
				}

			}
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
					m_iMatrix[i][j][k] = -MAXNUM;
			}


	//iteration_while = 0;
	while (change == 1) 
	{ 
		//iteration_while ++;
		change = 0;
		ith++;
		thr++;	/*threshold value for this iteration*/
		m_iLayer = ith;
		/*First Scan for S-Open Point Begins*/
		for (k=2; k<m_iSize[2]+2; k++)
		{
			for (j=2; j<m_iSize[1]+2; j++)
			{
				for (i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k]==0)  /*the first scan is just for unmarked s point*/
					{
						if(Is_sopen_pt(m_iMatrix, i, j, k, thr))   //before iteration
						{
							if(Shape_Point(m_iMatrix, i, j, k, thr) == 0)   //before iteration
							{
								if(Simple_Point(m_iMatrix, m_iTemp, i ,j, k)==0) 	//current version
								{
									m_iMatrix[i][j][k] = thr; //delete
									change=1;
								}
							}
							else
								m_iMatrix[i][j][k] = ith;  //mark
						}
					}
				}
			}
		}


		/*Second Scan for E-Open Point Begins*/
		for (k=2; k<m_iSize[2]+2; k++)
		{
			for (j=2; j<m_iSize[1]+2; j++)
			{
				for (i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k]==0)  //the second scan is just for unmarked s point
					{
						if(Is_eopen_pt(m_iMatrix, i, j, k, thr))   //before iteration
						{
							if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0) //simple point detection is on current version
							{
								if(Is_cond3(m_iMatrix, m_iTemp, i, j, k, thr)==1)  
								{
									m_iMatrix[i][j][k] = thr;
									change=1;
								}
							}
							
						}
					}
				}	
			}
		}	

		/*Third Scan for V-Open Point Begins*/
		/*for (k=2; k<m_iSize[2]+2; k++)
		{
			for (j=2; j<m_iSize[1]+2; j++)
			{	
				for (i=2; i<m_iSize[0]+2; i++)
				{
					if(!m_iMatrix[i][j][k]==0)
					{
						if(Is_vopen_pt(m_iMatrix, i, j, k, thr))
						{
							if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)
							{
								m_iMatrix[i][j][k] = thr;
								change=1;
							}
						}
					}
				}
			}	
		}*/

	} /*while ends here*/	

	/************************************************************************************************
	* 	final thinning										*
	*	in final thinning, erodable points are removed from a primary skeleton			*
	*	this is a single iteration procedure and the iteration consists of single scan		*
	************************************************************************************************/

	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] >=0 && Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)	//all the computations are done only on black points
				{
	/************************************************************************************************
	*	erodable points										*
	*	during an iteration a black point is an erodable point if it is a simple and satisfies	*
	*	any of the condition 4,5 or 6									*
	************************************************************************************************/
					if(Is_cond4(m_iMatrix, m_iTemp, i, j, k, thr)==1 || Is_cond5(m_iMatrix, m_iTemp, i, j, k, thr)==1 || Is_cond6(m_iMatrix, m_iTemp, i, j, k, thr)==1 ) 
					{
						m_iMatrix[i][j][k] = thr;
					}
				}
			}
		}
	}	
	
	m_iThr = thr;

	m_strDisp.Format(_T("Finish Thinning!"));

	for (k=0; k<m_iSize[2]+4; k++)
	{
		for (j=0; j<m_iSize[1]+4; j++)
		{
			for (i=0; i<m_iSize[0]+4; i++)
			{
				if(m_iMatrix[i][j][k] >= 0)
				{
					m_iMatrix[i][j][k] = 1;		//m_iMatrix stores the regular skeleton
				}
				
				else if(m_iMatrix[i][j][k] < 0)
				{
					m_iPtType[i][j][k] = m_iMatrix[i][j][k];	//m_iPtType stores all the "depth" layer
					m_iMatrix[i][j][k] = 0;		
				}
			}
		}
	}
	for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
					m_iMatrix[i][j][k] = 0;
			}

	UpdateData( FALSE );	
}

void CFormCommandView::OnCancel() 
{
	// TODO: Add your control notification handler code here
	int i,j,k;
	
	if(m_bLoad == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++) 
			for(j=0; j<m_iSize[1]+4; j++)
				for(k=0; k<m_iSize[2]+4; k++)
					m_iMatrix[i][j][k] = 0;
	

		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				for(k=0; k<3; k++)
					m_iTemp[i][j][k] = 0;


		for(i=0; i<3; i++)
			m_iSize[i] = 0;

		m_fBVF = 0;		//BV/TV
		m_fPBVF = 0;		//Plate volume/TV
		m_fRBVF = 0;		//Rod volume/TV
		m_fPThickness = 0;	//Plate Thickness(mm)
		m_fRDiameter = 0;	//Rod radius(mm)
		m_fPSurface = 0;	//Plate length(mm)
		m_fRLength = 0;	//Rod length(mm)
		m_fJuncNo = 0;		//Total Junction No/TV (1/mm^3)
		m_fRRJNo = 0;			//Rod-Rod Junction No/TV(1/mm^3)
		m_fRPJNo = 0;			//Rod-Plate Junction No/TV(1/mm^3)
		m_fPNo = 0;			//Plate No/TV(1/mm^3)
		m_fRNo = 0;			//Rod No/TV(1/mm^3)
		m_fPBVF_s = 0;	//pBV/TV of simplified model
		m_fRBVF_s = 0;	//rBV/TV of simplified model
	}

	if(m_bThinned == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++)
			for(j=0; j<m_iSize[1]+4; j++)
				for(k=0; k<m_iSize[2]+4; k++)
					m_iPtType[i][j][k] = 0;

	}

/*	if(m_bCurveMeshed == TRUE)
	{
		for(i=0; i<1000; i++)
			for(j=0; j<3; j++)
				m_iNodelist[i][j] = -1;

		for(i=0; i<1000; i++)
			for(j=0; j<3; j++)
				m_iCurvelist[i][j] = -1;
	}*/

	if(m_bPClustered == TRUE)
	{
		for(i=0; i<=m_iClusterNo; i++)
		{
			for(j=0; j<3; j++)
			{
				m_iCluster[i][j] = 0;
			}
		}

		for(i=0; i<=m_iTraNo; i++)
		{
			for(j=0; j<26; j++)
			{
				m_iConnection[i][j] = 0;
			}
		}


		for(i=0; i<m_iNodelistSize; i++)
		{
			for(j=0; j<3; j++)
			{
				m_iNodelist[i][j] = 0;
			}
		}
	}

	m_strDisp.Format(_T(""));
	m_strSize.Format(_T(""));
	m_strDebug.Format(_T(""));
	UpdateData( FALSE );

	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	m_Temp->m_Clear = FALSE;
	m_Temp->Invalidate();
}

void CFormCommandView::OnOK() 
{
	// TODO: Add your control notification handler code here
	if(m_bPClustered && m_bRecovered)
	{
		UpdateData(TRUE);
	}

	if(m_bLoad == TRUE)
	{
		CTestGLView* m_Temp;
		m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
		m_Temp->m_Clear = TRUE;
		m_Temp->Invalidate(TRUE);
	}
}

void CFormCommandView::OnClassify() 
{
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bClassified == TRUE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bDebugmode == TRUE)
	{
		MessageBox(_T(" Please quit debugging mode first! "));
		return;
	}

	m_bClassified = TRUE;

	//Begin initial type decision
	m_strDisp.Format(_T("Begin Initial Decision!"));
	UpdateData( FALSE );

	int i,j,k,a,b,c;

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] == 1) 
				{
					Initial_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
				}
			}
		}
	}

	//Begin final type decision
	m_strDisp.Format(_T("Begin Final Decision!"));
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]==1) 
				{
					Final_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k]==16) 
				{
					m_iPtType[i][j][k]=6;
				}
				else if(m_iPtType[i][j][k]==17) 
				{
					m_iPtType[i][j][k]=7;
				}
			}
		}
	}

	m_iThr++;
	int t = 0;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					t++;
				}
			}
		}
	}

	//Deletion of single or double voxel-width curve
	BOOL Spt = TRUE;
	int count = 0 ;

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				Spt = TRUE;
				count = 0;
				if(m_iPtType[i][j][k] == 1)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(a!=1 || b!=1 || c!=1)
								{
									count += m_iMatrix[i-1+a][j-1+b][k-1+c];
									if(m_iPtType[i-1+a][j-1+b][k-1+c] == 2)
										Spt = FALSE;	
								}
							}
						}
					}
					if(Spt == TRUE)
					{
						for(a=0; a<=2; a++)
						{
							for(b=0; b<=2; b++)
							{
								for(c=0; c<=2; c++)
								{
									m_iMatrix[i-1+a][j-1+b][k-1+c] = (m_iMatrix[i-1+a][j-1+b][k-1+c]>0 ? 0:-1);

								}
							}
						}
						if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0 && count > 1)
						{
							m_iMatrix[i][j][k] = -MAXNUM-1;
							m_iPtType[i][j][k] = m_iThr;
						}
						
						for(a=0; a<=2; a++)
						{
							for(b=0; b<=2; b++)
							{
								for(c=0; c<=2; c++)
								{
									m_iMatrix[i-1+a][j-1+b][k-1+c] = (m_iMatrix[i-1+a][j-1+b][k-1+c]==0 ? 1:0);

								}
							}
						}
					}

				}
			}
		}
	}


	//Begin initial type decision
	m_strDisp.Format(_T("Begin Initial Decision!"));
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]==1) 
				{
					Initial_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
				}
			}
		}
	}

	//Begin final type decision
	m_strDisp.Format(_T("Begin Final Decision!"));
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]==1) 
				{
					Final_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
				}
			}
		}
	}
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k]==16) 
				{
					m_iPtType[i][j][k]=6;
				}
				else if(m_iPtType[i][j][k]==17) 
				{
					m_iPtType[i][j][k]=7;
				}
			}
		}
	}


	//Surface-Curve connection point detection
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]==1) 
				{
					Is_SCType(m_iPtType, i, j, k);
				}
			}
		}
	}

	//Detection for Curve-curve point
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] == 6 && Neighbor_CC(i,j,k)>=3)
				{
					m_iPtType[i][j][k] = 7;
				}
			}
		}
	}


	//Delete unnecessary curve end point which is connected with a curve-curve point	2-23-06

	m_iThr++;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] == 7)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(m_iPtType[i-1+a][j-1+b][k-1+c] == 5 && (a!=1 || b!=1 || c!=1))
								{
									m_iMatrix[i-1+a][j-1+b][k-1+c] = -MAXNUM-1;
									m_iPtType[i-1+a][j-1+b][k-1+c] = m_iThr;
								}
							}
						}
					}
				}
			}
		}
	}

	//Delete unnecessary curve end point which is connected with a surface-curve point	2-23-06

	m_iThr++;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] == 4)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(m_iPtType[i-1+a][j-1+b][k-1+c] == 5 && (a!=1 || b!=1 || c!=1))
								{
									m_iMatrix[i-1+a][j-1+b][k-1+c] = -MAXNUM-1;
									m_iPtType[i-1+a][j-1+b][k-1+c] = m_iThr;
									//m_iPtType[i][j][k] = 1;
								}
							}
						}
					}
				}
			}
		}
	}
	
	m_iThr++;
	//redetection of CC points
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] == 7)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								m_iMatrix[i-1+a][j-1+b][k-1+c] = (m_iMatrix[i-1+a][j-1+b][k-1+c]>0 ? 0:-1);
							}
						}
					}
					if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)
					{
						m_iMatrix[i][j][k] = -MAXNUM-1;
						m_iPtType[i][j][k] = m_iThr;
					}
					
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								m_iMatrix[i-1+a][j-1+b][k-1+c] = (m_iMatrix[i-1+a][j-1+b][k-1+c]==0 ? 1:0);
							}
						}
					}	
					//if(m_iMatrix[i][j][k] == 1 && Neighbor_CC(i,j,k)<3)
					//{
					//	m_iPtType[i][j][k] = 6;
					//}
				}
			}
		}
	}


	//redetection of SC points  2-23-06
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] == 4)
				{
					m_iPtType[i][j][k] = 1;
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(m_iPtType[i-1+a][j-1+b][k-1+c] == 5 ||m_iPtType[i-1+a][j-1+b][k-1+c] == 6||m_iPtType[i-1+a][j-1+b][k-1+c] == 7)
									m_iPtType[i][j][k] = 4;
							}
						}
					}

				}
				else if(m_iPtType[i][j][k] == 7 && Neighbor_CC(i,j,k)<3)
				{
					m_iPtType[i][j][k] = 6;
				}

			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && m_iPtType[i][j][k] == 7)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(!(a==1 && b==1 && c==1) && (m_iPtType[i-1+a][j-1+b][k-1+c] == 6 || m_iPtType[i-1+a][j-1+b][k-1+c] == 5))
								{
									if(Neighbor(i-1+a, j-1+b, k-1+c, 4, 5, 6, 6) >=2)
									{
										m_iPtType[i-1+a][j-1+b][k-1+c] = 7;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//debug for the inner surface edge points
/*	int scpt = 0;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				scpt = 0;
				if(m_iPtType[i][j][k] == 1)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(a!=1 || b!=1 || c!=1)
								{
									if(m_iPtType[i-1+a][j-1+b][k-1+c] == 1)
										scpt = 1;	
								}
							}
						}
					}
					if(scpt == 0)
					{
						scpt = 0;
					}
				}
			}
		}
	}*/
	m_iPlateThr = m_iThr;

	m_iCrPnts = (int ***)calloc(m_iSize[0]+4, sizeof(int**));
	for(i=0; i<m_iSize[0]+4; i++)
	{
		m_iCrPnts[i] = (int **)calloc(m_iSize[1]+4, sizeof(int*));
	}
	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			m_iCrPnts[i][j] = (int *)calloc(m_iSize[2]+4, sizeof(int));
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
		for(j=2; j<m_iSize[1]+2; j++)
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] >0)
				{
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];	//m_iMatrix stores all the skeleton voxels with indication of topological class
					m_iCrPnts[i][j][k] = m_iMatrix[i][j][k];
				}												
				else
				{
					m_iMatrix[i][j][k] = 0;
				}
			}

	m_strDisp.Format(_T("Finish Final Decision!"));
	UpdateData( FALSE );

}

int CFormCommandView::Neighbor_CC(int i, int j, int k)
{
	int a,b,c;
	int num = 0;
	for(a=-1; a<=1; a++)
	{
		for(b=-1; b<=1; b++)
		{
			for(c=-1; c<=1; c++)
			{
				if(!(a==0 && b==0 && c==0)) 
				{
					if(m_iPtType[i+a][j+b][k+c]==4 || m_iPtType[i+a][j+b][k+c]==5 || m_iPtType[i+a][j+b][k+c]==6 || m_iPtType[i+a][j+b][k+c]==7)
					{
						num++;
					}
				}
			}
		}
	}
	return num;
}

void CFormCommandView::OnArcthinning() 
{
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bDebugmode == TRUE)
	{
		MessageBox(_T(" Please quit debugging mode first! "));
		return;
	}

	m_bDebugmode = FALSE;
	
	int i,j,k;

	/******************************************************************
	*      primary arc thinning --2 scans in each iteration               *
	*******************************************************************/	

	bool change =1;  		//if any pt is deleted in the last iteration, change =1
	int ith=0;			//ith is the iteration time
	int thr = m_iThr;

	m_strDisp.Format(_T("Start Arc Thinning!"));
	UpdateData( FALSE );

	m_bArcThinned = TRUE;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				//initiate the data
				if(m_iMatrix[i][j][k] == 0)
				{
					m_iMatrix[i][j][k] = -MAXNUM;
				}
				else if(m_iMatrix[i][j][k] == 1 || m_iMatrix[i][j][k] == 2)
				{
					m_iMatrix[i][j][k] = 0;
				}
				else if(m_iMatrix[i][j][k] == 4)
					m_iMatrix[i][j][k] = MAXNUM;
				else if(m_iMatrix[i][j][k] > 0)
				{
					m_iMatrix[i][j][k] = -MAXNUM;
				}
			}
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
					m_iMatrix[i][j][k] = -MAXNUM;
			}

	//Two layer's thinning, for reducing the noise due to the very slender plate and tiny plate pieces		
	int templayer = 0;
	while (templayer<THINLAYER)
	{ 
		templayer ++;
		change = 0;
		ith++;
		thr++;	//threshold value for this iteration
		
		//First Scan for S-Open-Surface Point Begins
		for (k=2; k<m_iSize[2]+2; k++)
		{
			for (j=2; j<m_iSize[1]+2; j++)
			{
				for (i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k]==0)  //the first scan is just for unmarked s point
					{
						if(Is_sopen_surface_pt(m_iMatrix, i, j, k, thr))   //before iteration
						{
							if(Arc_Shape_Point(m_iMatrix, i, j, k, thr) == 0)   //before iteration
							{
								if(Simple_Point(m_iMatrix, m_iTemp, i ,j, k)==0) 	//current version
								{
									m_iMatrix[i][j][k] = thr; //delete
									change=1;
								}
								else
									m_iMatrix[i][j][k] = 0; //unmark
							}
							//else
								//m_iMatrix[i][j][k] = ith;  //mark
						}
					}
				}
			}
		}


		//Second Scan for E-Open-Surface Point Begins
		for (k=2; k<m_iSize[2]+2; k++)
		{
			for (j=2; j<m_iSize[1]+2; j++)
			{
				for (i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k]==0)  //the second scan is just for unmarked e point
					{
						if(Is_eopen_surface_pt(m_iMatrix, i, j, k, thr))   //before iteration
						{
							if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)		//simple point detection is on current version
							{
								m_iMatrix[i][j][k] = thr;	//deletet
								change=1;
							}
							else
								m_iMatrix[i][j][k] = 0; //unmark
						}
					}
				}	
			}
		}	

	} //while ends here	

	for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
					m_iMatrix[i][j][k] = 0;
			}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				//initiate the data
				if(m_iMatrix[i][j][k] < 0 && (m_iPtType[i][j][k] ==1 || m_iPtType[i][j][k] == 2))
				{
					m_iPtType[i][j][k] = m_iMatrix[i][j][k];
					m_iMatrix[i][j][k] = 0;
				}
				else if(m_iMatrix[i][j][k] < 0)
					m_iMatrix[i][j][k] = 0;
				else if(m_iMatrix[i][j][k] == MAXNUM)
				{
					m_iMatrix[i][j][k] = 0;
					m_iPtType[i][j][k] = 4;
				}
				else if(m_iMatrix[i][j][k] >= 0)
					m_iMatrix[i][j][k] = 1;
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)// && (m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] == 2)) 
					Initial_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
			}
		}
	}

	//Begin final type decision
	m_strDisp.Format(_T("Begin Final Decision!"));
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)// && (m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] == 2)) 
				{
					Final_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
				}
			}
		}
	}
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k]==16) 
				{
					m_iPtType[i][j][k]=6;
				}
				else if(m_iPtType[i][j][k]==17) 
				{
					m_iPtType[i][j][k]=7;
				}
			}
		}
	}

/*	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] >0 || m_iPtType[i][j][k] == 4)
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];
			}
		}
	}

	return;*/

	//Deletion of single or double voxel-width curve
	thr++;
	BOOL Spt = TRUE;
	int count = 0 ;
	int a, b,c;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				Spt = TRUE;
				count = 0;
				if(m_iPtType[i][j][k] == 1)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(a!=1 || b!=1 || c!=1)
								{
									count += m_iMatrix[i-1+a][j-1+b][k-1+c];
									if(m_iPtType[i-1+a][j-1+b][k-1+c] == 2)
										Spt = FALSE;	
								}
							}
						}
					}
					if(Spt == TRUE)
					{
						for(a=0; a<=2; a++)
						{
							for(b=0; b<=2; b++)
							{
								for(c=0; c<=2; c++)
								{
									m_iMatrix[i-1+a][j-1+b][k-1+c] = (m_iMatrix[i-1+a][j-1+b][k-1+c]>0 ? 0:-1);
									if(m_iPtType[i-1+a][j-1+b][k-1+c] == 4)
										m_iMatrix[i-1+a][j-1+b][k-1+c] = 0;

								}
							}
						}
						if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0 && count > 1)
						{
							m_iMatrix[i][j][k] = -MAXNUM-1;
							m_iPtType[i][j][k] = thr;
						}
						
						for(a=0; a<=2; a++)
						{
							for(b=0; b<=2; b++)
							{
								for(c=0; c<=2; c++)
								{
									m_iMatrix[i-1+a][j-1+b][k-1+c] = (m_iMatrix[i-1+a][j-1+b][k-1+c]==0 ? 1:0);
									if(m_iPtType[i-1+a][j-1+b][k-1+c] == 4)
										m_iMatrix[i-1+a][j-1+b][k-1+c] = 0;

								}
							}
						}
					}

				}
			}
		}
	}


	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] >0)
					m_iMatrix[i][j][k] = 1;
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)// && (m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] == 2)) 
					Initial_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
			}
		}
	}

	//Begin final type decision
	m_strDisp.Format(_T("Begin Final Decision!"));
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)// && (m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] == 2)) 
				{
					Final_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
				}
			}
		}
	}
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k]==16) 
				{
					m_iPtType[i][j][k]=6;
				}
				else if(m_iPtType[i][j][k]==17) 
				{
					m_iPtType[i][j][k]=7;
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]>0)
					m_iMatrix[i][j][k] = 1;
			}
		}
	}

	//return;

	//clustering the surface points(without SC,CC,SS points)
	int iClusterNo = HKcluster4S(m_iMatrix, m_iSize);

	int *iClusterCurve = (int *)calloc(iClusterNo+1, sizeof(int));
	for(i=1; i<iClusterNo+1; i++)
		iClusterCurve[i] = 0;

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && (m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] ==2) )
					iClusterCurve[m_iMatrix[i][j][k]] = 1;
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && iClusterCurve[m_iMatrix[i][j][k]] == 0)
				{
					if(m_iPtType[i][j][k] == 8)
					{
						m_iPtType[i][j][k] = 6;
						m_iMatrix[i][j][k] = 6;
					}
					else
					{
						m_iPtType[i][j][k] = 6;
						m_iMatrix[i][j][k] = m_iPtType[i][j][k];
					}
				}
				else if(m_iMatrix[i][j][k]> 0)
				{
					m_iMatrix[i][j][k] = 1;
					m_iPtType[i][j][k] = 1;
				}
				else if(m_iMatrix[i][j][k] == 0 && m_iPtType[i][j][k] ==4)
					m_iMatrix[i][j][k] = 4;
					

			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				//initiate the data
				if(m_iMatrix[i][j][k] == 0)
				{
					m_iMatrix[i][j][k] = -MAXNUM;
				}
				else if(m_iMatrix[i][j][k] == 1 || m_iMatrix[i][j][k] == 2)
				{
					m_iMatrix[i][j][k] = 0;
				}
				else if(m_iMatrix[i][j][k] == 4)
					m_iMatrix[i][j][k] = MAXNUM;
				else if(m_iMatrix[i][j][k] > 0)
				{
					m_iMatrix[i][j][k] = -MAXNUM;
				}
			}
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
					m_iMatrix[i][j][k] = -MAXNUM;
			}
	
	while (change == 1) 
	{ 
		change = 0;
		ith++;
		thr++;	//threshold value for this iteration
		
		//First Scan for S-Open-Surface Point Begins
		for (k=2; k<m_iSize[2]+2; k++)
		{
			for (j=2; j<m_iSize[1]+2; j++)
			{
				for (i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k]==0)  //the first scan is just for unmarked s point
					{
						if(Is_sopen_surface_pt(m_iMatrix, i, j, k, thr))   //before iteration
						{
							if(Arc_Shape_Point(m_iMatrix, i, j, k, thr) == 0)   //before iteration
							{
								if(Simple_Point(m_iMatrix, m_iTemp, i ,j, k)==0) 	//current version
								{
									m_iMatrix[i][j][k] = thr; //delete
									change=1;
								}
								else
									m_iMatrix[i][j][k] = 0; //unmark
							}
							//else
								//m_iMatrix[i][j][k] = ith;  //mark
						}
					}
				}
			}
		}


		//Second Scan for E-Open-Surface Point Begins
		for (k=2; k<m_iSize[2]+2; k++)
		{
			for (j=2; j<m_iSize[1]+2; j++)
			{
				for (i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k]==0)  //the second scan is just for unmarked e point
					{
						if(Is_eopen_surface_pt(m_iMatrix, i, j, k, thr))   //before iteration
						{
							if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)		//simple point detection is on current version
							{
								m_iMatrix[i][j][k] = thr;	//deletet
								change=1;
							}
							else
								m_iMatrix[i][j][k] = 0; //unmark
						}
					}
				}	
			}
		}	

	} //while ends here	

	/************************************************************************************************
	* 	final arc thinning																			*
	*	in final thinning, arc erodable points are removed from a primary skeleton					*
	*	this is a single iteration procedure and the iteration consists of single scan				*
	************************************************************************************************/

	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] >=0 && Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0) //all the computations are done only on black points
				{
	/************************************************************************************************
	*	erodable points										*
	*	during an iteration a black point is an erodable point if it is a simple point and satisfies	*
	*	definition 10									*
	************************************************************************************************/
					if(Arc_Erodable_Point(m_iMatrix, i, j, k)==1) 
					{
						m_iMatrix[i][j][k] = thr;
					}
				}
			}
		}
	}	

	m_strDisp.Format(_T("Finish Thinning!"));

	m_iThr = thr;

	for (k=0; k<m_iSize[2]+4; k++)
	{
		for (j=0; j<m_iSize[1]+4; j++)
		{
			for (i=0; i<m_iSize[0]+4; i++)
			{
				if(m_iMatrix[i][j][k] == MAXNUM)
				{
					m_iMatrix[i][j][k] = 4;
					m_iPtType[i][j][k] = 4;
				}
				else if(m_iMatrix[i][j][k] >= 0)
				{
					m_iMatrix[i][j][k] = 1;
					m_iPtType[i][j][k] = 1;
				}
				else if(m_iPtType[i][j][k] == 4 || m_iPtType[i][j][k] == 5 || m_iPtType[i][j][k] == 6 || m_iPtType[i][j][k] == 7)
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];
				else if(m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] == 2 || m_iPtType[i][j][k] == 3)
				{
					m_iPtType[i][j][k] = m_iMatrix[i][j][k];
					m_iMatrix[i][j][k] = 0;
				}
				else
					m_iMatrix[i][j][k] = 0;
			}
		}
	}
	for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
					m_iMatrix[i][j][k] = 0;
			}

	int temp = 0;
	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] == 4)
				{
					temp = 0;
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(!(a==1 && b==1 && c==1) && m_iPtType[i-1+a][j-1+b][k-1+c] == 1)
								{
									temp = 1;
									a=3;
									b=3;
									c=3;
								}
							}
						}
					}
					if(temp == 0)
						m_iMatrix[i][j][k] = 6;
				}
			}
		}
	}

	free(iClusterCurve);
	UpdateData( FALSE );		
}

void CFormCommandView::OnArcClassify() 
{
	// TODO: Add your control notification handler code here
	if(m_bArcThinned == FALSE)
	{
		MessageBox(_T("Please Arc Thinning first!"));
		return;
	}
	//Begin initial type decision
	m_strDisp.Format(_T("Begin Initial Decision!"));
	UpdateData( FALSE );

	int i,j,k,a,b,c;

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)// && (m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] == 2)) 
					Initial_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
			}
		}
	}

	//Begin final type decision
	m_strDisp.Format(_T("Begin Final Decision!"));
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)// && (m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] == 2)) 
				{
					Final_Type(m_iMatrix, m_iTemp, m_iPtType, i, j, k);
				}
			}
		}
	}
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k]==16) 
				{
					m_iPtType[i][j][k]=6;
				}
				else if(m_iPtType[i][j][k]==17) 
				{
					m_iPtType[i][j][k]=7;
				}
			}
		}
	}
	m_iThr++;

	//Detection for Curve-curve point
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] == 6 && Neighbor_CC(i,j,k)>=3)
				{
					m_iPtType[i][j][k] = 7;
				}
			}
		}
	}

	//In arcthinned version: [2]plate; [3]plate-plate arc junction; [4]surface-arc junction; [5]arc end; [6]arc inner
	//[7]arc-arc junction; [8]plate arc end;

	for(k=2; k<m_iSize[2]+2; k++)
		for(j=2; j<m_iSize[1]+2; j++)
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if((m_iMatrix[i][j][k] == 1 || m_iMatrix[i][j][k] == 2) && m_iPtType[i][j][k] == 7)
					m_iMatrix[i][j][k] = 3;
				else if((m_iMatrix[i][j][k] == 1 || m_iMatrix[i][j][k] == 2) && m_iPtType[i][j][k] == 5)
					m_iMatrix[i][j][k] = 8;
				else if((m_iMatrix[i][j][k] == 1 || m_iMatrix[i][j][k] == 2) && m_iPtType[i][j][k] != 4 && m_iPtType[i][j][k] != 5 && m_iPtType[i][j][k] != 7)// && m_iMatrix[i][j][k] == 1)
					m_iMatrix[i][j][k] = 2;
				else if(m_iMatrix[i][j][k] != 4 && m_iMatrix[i][j][k] > 0 && m_iPtType[i][j][k] != 1 && m_iPtType[i][j][k] != 2)
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];
				else if(m_iMatrix[i][j][k] != 4 && m_iMatrix[i][j][k] > 0 && (m_iPtType[i][j][k] = 1 || m_iPtType[i][j][k] == 2))
				{
					m_iMatrix[i][j][k] = MAXNUM;
					m_iPtType[i][j][k] = MAXNUM;
				}
				else if(m_iMatrix[i][j][k] != MAXNUM && m_iMatrix[i][j][k] != 4) 
					m_iMatrix[i][j][k] = 0;

				if(m_iMatrix[i][j][k] > 0 && m_iMatrix[i][j][k] != MAXNUM)
					m_iPtType[i][j][k] = m_iMatrix[i][j][k];
			}
	
	int iChange = 1;
	while (iChange)
	{
		iChange = 0;
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
				//if(m_iPtType[i][j][k] > 0)
				//	m_iMatrix[i][j][k] = m_iPtType[i][j][k];
					if(m_iMatrix[i][j][k] == MAXNUM)
					{
						for(a=0; a<=2; a++)
						{
							for(b=0; b<=2; b++)
							{
								for(c=0; c<=2; c++)
								{
									m_iMatrix[i-1+a][j-1+b][k-1+c] = (m_iMatrix[i-1+a][j-1+b][k-1+c]>0 ? 0:-1);

								}
							}
						}
						if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)
						{
							m_iMatrix[i][j][k] = -MAXNUM-1;
							m_iPtType[i][j][k] = m_iThr;
							iChange = 1;
						}
						else
							m_iMatrix[i][j][k] = 0;
						
						for(a=0; a<=2; a++)
						{
							for(b=0; b<=2; b++)
							{
								for(c=0; c<=2; c++)
								{
									m_iMatrix[i-1+a][j-1+b][k-1+c] = (m_iMatrix[i-1+a][j-1+b][k-1+c]==0 ? m_iPtType[i-1+a][j-1+b][k-1+c]:0);

								}
							}
						}
					}
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && m_iPtType[i][j][k] == 7)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(!(a==1 && b==1 && c==1) && (m_iMatrix[i-1+a][j-1+b][k-1+c] == 6 || m_iMatrix[i-1+a][j-1+b][k-1+c] == 5))
								{
									if(Neighbor(i-1+a, j-1+b, k-1+c, 4, 5, 6, 6) >=2)
									{
										m_iMatrix[i-1+a][j-1+b][k-1+c] = 7;
										m_iPtType[i-1+a][j-1+b][k-1+c] = 7;
									}
								}
							}
						}
					}
				}

				else if(m_iMatrix[i][j][k] > 0 && m_iPtType[i][j][k] == 3)
				{
					for(a=0; a<=2; a++)
					{
						for(b=0; b<=2; b++)
						{
							for(c=0; c<=2; c++)
							{
								if(!(a==1 && b==1 && c==1) && (m_iMatrix[i-1+a][j-1+b][k-1+c] == 8 || m_iMatrix[i-1+a][j-1+b][k-1+c] == 2))
								{
									if(Neighbor(i-1+a, j-1+b, k-1+c, 2, 2, 8, 4) >=2)
									{
										m_iMatrix[i-1+a][j-1+b][k-1+c] = 3;
										m_iPtType[i-1+a][j-1+b][k-1+c] = 3;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
					m_iPtType[i][j][k] = m_iMatrix[i][j][k];
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] != 7)
					m_iMatrix[i][j][k] = 0;
				else
					m_iMatrix[i][j][k] = 7;
			}
		}
	}

	m_fRRJNo = HKcluster4S(m_iMatrix, m_iSize);

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] != 4)
					m_iMatrix[i][j][k] = 0;
				else
					m_iMatrix[i][j][k] = 4;
			}
		}
	}

	m_fRPJNo = HKcluster4S(m_iMatrix, m_iSize);

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] != 3)
					m_iMatrix[i][j][k] = 0;
				else
					m_iMatrix[i][j][k] = 3;
			}
		}
	}

	m_fPPJNo = HKcluster4S(m_iMatrix, m_iSize);

//	CMorphDialog Rdlg;
//	Rdlg.DoModal();

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] > 0)
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];
				//else if(m_iCrPnts[i][j][k] == 1)
					//m_iMatrix[i][j][k] = m_iCrPnts[i][j][k];
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
		for(j=2; j<m_iSize[1]+2; j++)
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] == 3 || m_iMatrix[i][j][k] == 5 || m_iMatrix[i][j][k] == 6 ||m_iMatrix[i][j][k] == 7)
				{
					m_iCrPnts[i][j][k] = m_iMatrix[i][j][k];	//m_iCrPnts stores the newly thinned curves and original surfaces
				}												
			}
	m_strDisp.Format(_T("Finish Final Decision!"));
	UpdateData( FALSE );
}

int CFormCommandView::Neighbor(int i, int j, int k, int type1, int type2, int type3, int type4)
{
	int a,b,c;
	int num = 0;
	for(a=-1; a<=1; a++)
	{
		for(b=-1; b<=1; b++)
		{
			for(c=-1; c<=1; c++)
			{
				if(!(a==0 && b==0 && c==0)) 
				{
					if(m_iPtType[i+a][j+b][k+c]==type1 || m_iPtType[i+a][j+b][k+c]==type2 || m_iPtType[i+a][j+b][k+c] == type3 || m_iPtType[i+a][j+b][k+c] == type4 )
					{
						num++;
					}
				}
			}
		}
	}
	return num;
}

void CFormCommandView::OnPrimary() 
{
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	int i,j,k;

	while(Debug_change == 0)
	{
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] >= 0)
						m_iMatrix[i][j][k] = 0;
				}
			}
		}
		CTestGLView* m_Temp;
		m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
		m_Temp->m_Clear = TRUE;
		m_Temp->Invalidate(TRUE);
		return;
	}

	CTestGLView* m_Temp;

	Debug_change = 0;

	Debug_ith++;
	Debug_thr++;	//threshold value for this iteration
	
	m_strDisp.Format(_T("Start Thinning!"));
	UpdateData( FALSE );

	if(m_bDebugProcess == FALSE)
	{
		m_bDebugProcess = TRUE;
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					//initiate the data
					if(m_iMatrix[i][j][k] == 0)
					{
						m_iMatrix[i][j][k] = -MAXNUM;
					}
					else if(m_iMatrix[i][j][k] >= 1)
					{
						m_iMatrix[i][j][k] = 0;
					}

				}
			}
		}

		for(i=0; i<m_iSize[0]+4; i++)
			for(j=0; j<m_iSize[1]+4; j++)
				for(k=0; k<m_iSize[2]+4; k++)
				{
					if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
						m_iMatrix[i][j][k] = 0;//-MAXNUM;
				}
	}

	
	//First Scan for S-Open Point Begins
	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]==0)  //the first scan is just for unmarked s point
				{
					if(Is_sopen_pt(m_iMatrix, i, j, k, Debug_thr))   //before iteration
					{
						if(Shape_Point(m_iMatrix, i, j, k, Debug_thr) == 0)   //before iteration
						{
							if(Simple_Point(m_iMatrix, m_iTemp, i ,j, k)==0)// &&  	//current version
							{
								m_iMatrix[i][j][k] = Debug_thr; //delete
								Debug_change=1;
								m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
								m_Temp->m_Clear = TRUE;
								m_Temp->Invalidate(TRUE);
								
								//MessageBox(_T("!"),NULL, MB_OK);
							}
						}
						else
						{
							m_iMatrix[i][j][k] = Debug_ith;  //mark
						}
					}
				}
			}
		}
	}


	//Second Scan for E-Open Point Begins
	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]==0)  //the second scan is just for unmarked s point
				{
					if(Is_eopen_pt(m_iMatrix, i, j, k, Debug_thr))   //before iteration
					{
						if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0) //simple point detection is on current version
						{
							if(Is_cond3(m_iMatrix, m_iTemp, i, j, k, Debug_thr)==1)  
							{
								m_iMatrix[i][j][k] = Debug_thr;
								Debug_change=1;
							}
						}
						
					}
				}
			}	
		}
	}	

	//Third Scan for v-Open Point Begins
	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{	
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(!m_iMatrix[i][j][k]==0)
				{
					if(Is_vopen_pt(m_iMatrix, i, j, k, Debug_thr) ==1)
					{
						if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)
						{
							m_iMatrix[i][j][k] = Debug_thr;
							Debug_change=1;
						}
					}
				}
			}
		}	
	}

	//display
//	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	m_Temp->m_Clear = TRUE;
	m_Temp->Invalidate(TRUE);
}


void CFormCommandView::OnFinal() 
{

	// TODO: Add your control notification handler code here
	int i,j,k;
	Debug_ith++;
	Debug_thr++;	//threshold value for this iteration

	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}
	if(m_bDebugProcess == FALSE)
	{
		MessageBox(_T(" Please process primary thinning first! "));
		return;
	}
		
	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] >=0 && Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)	//all the computations are done only on black points
				{
	/************************************************************************************************
	*	erodable points										*
	*	during an iteration a black point is an erodable point if it is a simple and satisfies	*
	*	any of the condition 4,5 or 6									*
	************************************************************************************************/
					if(Is_cond4(m_iMatrix, m_iTemp, i, j, k, Debug_thr)==1 || Is_cond5(m_iMatrix, m_iTemp, i, j, k, Debug_thr)==1 || Is_cond6(m_iMatrix, m_iTemp, i, j, k, Debug_thr)==1 ) 
					{
						m_iMatrix[i][j][k] = Debug_thr;
					}
				}
			}
		}
	}	
	//display
	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	m_Temp->m_Clear = TRUE;
	m_Temp->Invalidate(TRUE);
	
	Debug_change = 1;
}

void CFormCommandView::OnArcprimary() 
{
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	int i,j,k;
	while(Debug_change == 0)
	{
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] >= 0)
						m_iMatrix[i][j][k] = 0;
				}
			}
		}
		CTestGLView* m_Temp;
		m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
		m_Temp->m_Clear = TRUE;
		m_Temp->Invalidate(TRUE);
		return;
	}
	/******************************************************************
	*      primary arc thinning --2 scans in each iteration               *
	*******************************************************************/	


	m_strDisp.Format(_T("Start Arc Thinning!"));
	UpdateData( FALSE );

	Debug_change = 0;
	Debug_ith++;
	Debug_thr++;	//threshold value for this iteration
	
	//First Scan for S-Open-Surface Point Begins
	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(k==10)
					k=10;
				if(m_iMatrix[i][j][k]==0)  //the first scan is just for unmarked s point
				{
					if(Is_sopen_surface_pt(m_iMatrix, i, j, k, Debug_thr))   //before iteration
					{
						if(Arc_Shape_Point(m_iMatrix, i, j, k, Debug_thr) == 0)   //before iteration
						{
							if(Simple_Point(m_iMatrix, m_iTemp, i ,j, k)==0) 	//current version
							{
								m_iMatrix[i][j][k] = Debug_thr; //delete
								Debug_change=1;
							}
							else
								m_iMatrix[i][j][k] = 0; //unmark
						}
						//else
						//{
						//	m_iMatrix[i][j][k] = Debug_ith;  //mark
						//}
					}
				}
			}
		}
	}


	//Second Scan for E-Open-Surface Point Begins
	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]==0)  //the second scan is just for unmarked e point
				{
					if(Is_eopen_surface_pt(m_iMatrix, i, j, k, Debug_thr))   //before iteration
					{
						if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0)		//simple point detection is on current version
						{
							m_iMatrix[i][j][k] = Debug_thr;	//deletet
							Debug_change=1;
						}
						else
							m_iMatrix[i][j][k] = 0; //unmark
					}
				}
			}	
		}
	}	
	
	while(Debug_change == 0)
	{
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] >= 0)
						m_iMatrix[i][j][k] = 0;
				}
			}
		}
		CTestGLView* m_Temp;
		m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
		m_Temp->m_Clear = TRUE;
		m_Temp->Invalidate(TRUE);
		return;
	}
	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	m_Temp->m_Clear = TRUE;
	m_Temp->Invalidate(TRUE);
}

void CFormCommandView::OnArcfinal() 
{
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}
	if(m_bDebugProcess == FALSE)
	{
		MessageBox(_T(" Please process primary thinning first! "));
		return;
	}

	int i, j, k;

	for (k=2; k<m_iSize[2]+2; k++)
	{
		for (j=2; j<m_iSize[1]+2; j++)
		{
			for (i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] >=0)
				{
					if(Simple_Point(m_iMatrix, m_iTemp, i, j, k)==0) //all the computations are done only on black points
					{

	/************************************************************************************************
	*	erodable points										*
	*	during an iteration a black point is an erodable point if it is a simple point and satisfies	*
	*	definition 10									*
	************************************************************************************************/
						if(Arc_Erodable_Point(m_iMatrix, i, j, k)==1) 
						{
							m_iMatrix[i][j][k] = Debug_thr;
						}
					}
				}
			}
		}
	}
	CTestGLView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
	m_Temp->m_Clear = TRUE;
	m_Temp->Invalidate(TRUE);

}

void CFormCommandView::OnDebugstart() 
{
	// TODO: Add your control notification handler code here
	m_bDebugmode = TRUE;
	m_strDebug.Format(_T("In the debug mode"));
	UpdateData(FALSE);

	
}

void CFormCommandView::OnDebugend() 
{
	// TODO: Add your control notification handler code here
	m_bDebugmode = FALSE;
	m_bDebugProcess = FALSE;

	m_strDebug.Format(_T(""));
	UpdateData(FALSE);
	Debug_thr = -MAXNUM;
	Debug_ith = 0;
	Debug_change = 0;

}

void CFormCommandView::OnRecordClassify() 
{
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}
	CResolutionDialog Rdlg;
	Rdlg.DoModal();

	CFile cfSave;
	CFileDialog fSaveDlg(FALSE, _T("mct"), _T("*.mct"));
	int rc=1;
	int i, j, k;
	int count;
	char cTemp[12], cTemp2, cTemp3[5];
	fSaveDlg.DoModal();
	rc = cfSave.Open(fSaveDlg.GetPathName().GetBuffer(0), CFile::modeWrite|CFile::modeCreate);

	if(rc == 0)
	{
		MessageBox(TEXT("Invalid Pathname!"), MB_OK, NULL);
		return;
	}

	m_strDisp.Format(_T("Start Recording Data!"));
	UpdateData( FALSE );

	
	_itoa(m_iSize[0]-10,cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}

	cfSave.Write(cTemp, 12);

	_itoa(m_iSize[1]-10,cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}

	cfSave.Write(cTemp, 12);

	_itoa(m_iSize[2]-10,cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	_itoa((m_iSize[0]-10)*m_resolution[0],cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	_itoa((m_iSize[1]-10)*m_resolution[1],cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	_itoa((m_iSize[2]-10)*m_resolution[2],cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	cTemp2 = 13;
	cfSave.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave.Write(&cTemp2,1);

	_itoa(-1,cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	cTemp2 = 13;
	cfSave.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave.Write(&cTemp2,1);

	_itoa(1,cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	_itoa((m_iSize[0]-10),cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	_itoa(1,cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	_itoa((m_iSize[1]-10),cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	_itoa(1,cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	_itoa(m_iSize[2]-10,cTemp,10);
	j=12;
	for (i=1; i<=12; i++)
	{
		if(cTemp[i] == 0)
			j=i;
		if(i>=j)
			cTemp[i] = 32;
	}
	cfSave.Write(cTemp, 12);

	
	for(i=2+5; i<m_iSize[0]+2-5; i++)
	{
		for(j=2+5; j<m_iSize[1]+2-5; j++)
		{
			if(count != 0)
			{
				cTemp2 = 13;
				cfSave.Write(&cTemp2,1);
				cTemp2 = 10;
				cfSave.Write(&cTemp2,1);
			}

			
			count = 0;
			for(k=2+5; k<m_iSize[2]+2-5; k++)
			{
				cTemp2 = 32;
				cfSave.Write(&cTemp2, 1);
				cfSave.Write(&cTemp2, 1);

				if(m_iMatrix[i][j][k]>0)
					cTemp2 = '9';
				else
					cTemp2 = '0';

/*				if(m_iMatrix[i][j][k]>0)
					cTemp2 = '1';
				else if(m_iMatrix[i][j][k]==0)
					cTemp2 = '2';
				else if(m_iMatrix[i][j][k]<0)
					cTemp2 = '0';*/
				cfSave.Write(&cTemp2, 1);
				count++;

				if(count == 20)
				{
					cTemp2 = 13;
					cfSave.Write(&cTemp2,1);
					cTemp2 = 10;
					cfSave.Write(&cTemp2,1);
					count = 0;
				}

			}
		}
	}

	CFile cfSave2;
	LPCTSTR BASED_CODE szFilter = L"mhs Files (*.mhs)";
	CFileDialog fSaveDlg2(FALSE, _T("mhs"), _T("*.mhs"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	fSaveDlg2.DoModal();
	rc = cfSave2.Open(fSaveDlg2.GetPathName().GetBuffer(0), CFile::modeWrite|CFile::modeCreate);

	if(rc == 0)
	{
		MessageBox(_T("Invalid Pathname!"), MB_OK, NULL);
		return;
	}

    CString filename = cfSave2.GetFileTitle();
	LPTSTR lpsz = new TCHAR[filename.GetLength()+1];
	_tcscpy(lpsz, filename);

	cfSave2.Write(lpsz,6);
	cTemp2 = 13;
	cfSave2.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave2.Write(&cTemp2,1);


	_itoa(1,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	_itoa(m_iSize[0]-10,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	_itoa(1,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	_itoa(m_iSize[1]-10,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	_itoa(1,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	_itoa(m_iSize[2]-10,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	cTemp2 = 13;
	cfSave2.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave2.Write(&cTemp2,1);

	_itoa(2,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	cTemp2 = 13;
	cfSave2.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave2.Write(&cTemp2,1);

	_itoa(255,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	cTemp2 = 13;
	cfSave2.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave2.Write(&cTemp2,1);

	_itoa(5,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	cTemp2 = 13;
	cfSave2.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave2.Write(&cTemp2,1);

	_itoa(1,cTemp3,10);
	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	cTemp2 = 13;
	cfSave2.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave2.Write(&cTemp2,1);

	cTemp3[0] = '1';
	cTemp3[1] = '8';
	cTemp3[2] = 'e';
	cTemp3[3] = '3';
	cTemp3[4] = 32;

	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);

	cTemp2 = 13;
	cfSave2.Write(&cTemp2,1);
	cTemp2 = 10;
	cfSave2.Write(&cTemp2,1);

	cTemp3[0] = '.';
	cTemp3[1] = '3';
	cTemp3[2] = 32;
	cTemp3[3] = 32;
	cTemp3[4] = 32;

	j=5;
	for (i=1; i<=5; i++)
	{
		if(cTemp3[i] == 0)
			j=i;
		if(i>=j)
			cTemp3[i] = 32;
	}
	cfSave2.Write(cTemp3, 5);


	m_strDisp.Format(_T("Finish Recording Data!"));
	UpdateData( FALSE );

}

void CFormCommandView::OnCluster() 
{
	// TODO: Add your control notification handler code here
	int i,j,k;
	int iPlate = 0;
	int iRod = 0;

	m_strDisp.Format(_T("Begin Clustering!"));
	UpdateData( FALSE );

	hoshen_kopelman (m_iMatrix, m_iSize, m_bDebugmode);

	for (i=2+5; i<m_iSize[0]+2-5; i++)
	{
		for (j=2+5; j<m_iSize[1]+2-5; j++)
		{
			for (k=2+5; k<m_iSize[2]+2-5; k++)
			{
				if(m_iMatrix[i][j][k] == 1)
				{
					if(m_bClassified == TRUE && m_bRecovered == FALSE)
					{
						m_iMatrix[i][j][k] = m_iPtType[i][j][k];
						if(m_iPtType[i][j][k] == 1 || m_iPtType[i][j][k] == 2 || m_iPtType[i][j][k] == 3)
						{
							iPlate++;
						}
						else if(m_iPtType[i][j][k] == 4 || m_iPtType[i][j][k] == 5 || m_iPtType[i][j][k] == 6 || m_iPtType[i][j][k] == 7)
						{
							iRod++;
						}
					}

					if(m_bRecovered == TRUE && m_bPClustered == FALSE)
					{
						if(m_iPtType[i][j][k] < 1.5)
						{
							m_iMatrix[i][j][k] = 1;
							iPlate++;
						}
						else
						{
							m_iMatrix[i][j][k] = 2;
							iRod++;
						}
					}
				}
			}
		}
	}
		
	m_strDisp.Format(_T("Finish Clustering!"));
	//m_strSize.Format("The Image Size is   x=%d,   y=%d,   z=%d", m_iSize[0]-10, m_iSize[1]-10, m_iSize[2]-10);

	if(m_bRecovered == TRUE || m_bClassified == TRUE)
	{
		m_strSize.Format(_T("The Image Size is   x=%d,   y=%d,   z=%d"), m_iSize[0] - 10, m_iSize[1] - 10, m_iSize[2] - 10);
		m_strDebug.Format(_T("Total Voxels: %d \nplate: %d \nRod: %d"), iPlate + iRod, iPlate, iRod);
	}
	
	UpdateData( FALSE );

}

void CFormCommandView::OnRecover() 
{
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bClassified == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bDebugmode == TRUE)
	{
		MessageBox(_T(" Please quit debugging mode first! "));
		return;
	}

	m_bRecovered = TRUE;

	int i,j,k,l,m;
	int a,b,c;
	int temp, temp1, temp2, temp3;
	float ftemp;

	int iPlate = 0;
	int iRod = 0;
	int iTotal = 0;
	m_strDisp.Format(_T("Begin Recover!"));
	UpdateData( FALSE );

	int **pro;
	pro = (int **)calloc(27, sizeof(int*));
	
	for(i=0; i<27; i++)
	{
		pro[i] = (int *)calloc(2, sizeof(int));
	}
	
	for(i=0; i<27; i++)
	{
		for(j=0; j<2; j++)
		{
			pro[i][j] = 0;
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{				
				if(m_iPtType[i][j][k] > 0)
					m_iPtType[i][j][k] = m_iThr+1;
				if(m_iMatrix[i][j][k] <= 0)
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];
				else
					m_iPtType[i][j][k] = m_iMatrix[i][j][k];
			}
		}
	}

	m_fNorm = (float **)calloc(m_iTraNo+1, sizeof(float*));
	for(i=0; i<=m_iTraNo; i++)
	{
		m_fNorm[i] = (float *)calloc(12, sizeof(float));
	}

	m_fTh = (float **)calloc(m_iTraNo+1, sizeof(float*));
	for(i=0; i<=m_iTraNo; i++)
	{
		m_fTh[i] = (float *)calloc(4, sizeof(float));
	}

	for(i=0; i<=m_iTraNo; i++)
	{
		for(j=0; j<4; j++)
		{
			m_fTh[i][j] = 0;
		}
		for(j=0; j<12; j++)
		{
			m_fNorm[i][j] = 0;
		}
	}

	int iTra;
	int iChange = 0;
	int iEnd = 0;
	for(l=m_iThr+1; l>=m_iPlateThr; l--)
	{
		iEnd = 1;
		while(iEnd)
		{
			iEnd = 0;
			for(k=m_iSize[2]+1; k>1; k--)
			{
				for(j=m_iSize[1]+1; j>1; j--)
				{
					for(i=m_iSize[0]+1; i>1; i--)
					{
						if((int)m_iPtType[i][j][k]==l)
						{
							iTra = PrimaryRecover(m_iPtType, m_iMatrix, i, j, k, l);
							//if(iTra == MAXNUM+1)
							//	m_iPtType[i][j][k] = -MAXNUM-1;
							if(iTra == MAXNUM)
							{
								iEnd = 1;
							}
							else if(iTra > 0)
							{
								m_iPtType[i][j][k] = iTra;
								//m_iMatrix[i][j][k] = iTra;
							}
							else if(iTra == 0)
							{
								//m_iMatrix[i][j][k] = -MAXNUM-1;
							}
						}
					}
				}
			}
			for(k=2; k<m_iSize[2]+2; k++)
			{
				for(j=2; j<m_iSize[1]+2; j++)
				{
					for(i=2; i<m_iSize[0]+2; i++)
					{
						if(m_iPtType[i][j][k] > 0 )
							m_iMatrix[i][j][k] = m_iPtType[i][j][k] ;
					}
				}
			}

			if(iEnd == 1)
			{
				for(k=m_iSize[2]+1; k>1; k--)
				{
					for(j=m_iSize[1]+1; j>1; j--)
					{
						for(i=m_iSize[0]+1; i>1; i--)
						{
							if((int)m_iPtType[i][j][k]>=l && (int)m_iPtType[i][j][k] < 0)
							{
								iTra = (int)RecoverConnection(m_iPtType, m_iMatrix, i, j, k);
								if(iTra == 0)
								{
									iEnd = 1;
								}
								else
								{
									m_iPtType[i][j][k] = iTra;
									//m_iMatrix[i][j][k] = iTra;
								}
							}
						}
					}
				}
				if(iEnd == 1)
				{
					for(k=m_iSize[2]+1; k>1; k--)
					{
						for(j=m_iSize[1]+1; j>1; j--)
						{
							for(i=m_iSize[0]+1; i>1; i--)
							{
								if((int)m_iPtType[i][j][k]==-MAXNUM-1 || ((int)m_iPtType[i][j][k] >= l && (int)m_iPtType[i][j][k] < 0))
								{
									iTra = (int)RecoverConnection(m_iPtType, m_iMatrix, i, j, k);
									if(iTra == 0)
									{
										iEnd = 1;
									}
									else
									{
										m_iPtType[i][j][k] = iTra;
										m_iMatrix[i][j][k] = iTra;
									}
								}
							}
						}
					}
				}

				for(k=2; k<m_iSize[2]+2; k++)
				{
					for(j=2; j<m_iSize[1]+2; j++)
					{
						for(i=2; i<m_iSize[0]+2; i++)
						{
							if(m_iPtType[i][j][k] > 0 )
								m_iMatrix[i][j][k] = m_iPtType[i][j][k];
						}
					}
				}
			}
		}
	}

	for(k=m_iSize[2]+1; k>1; k--)
	{
		for(j=m_iSize[1]+1; j>1; j--)
		{
			for(i=m_iSize[0]+1; i>1; i--)
			{
				if((int)m_iPtType[i][j][k]==-MAXNUM-1 || ((int)m_iPtType[i][j][k] >= m_iPlateThr && (int)m_iPtType[i][j][k] < 0))
				{
					iTra = (int)RecoverConnection(m_iPtType, m_iMatrix, i, j, k);
					if(iTra == 0)
					{
						iEnd = 1;
					}
					else
					{
						m_iPtType[i][j][k] = iTra;
						m_iMatrix[i][j][k] = iTra;
					}
				}
			}
		}
	}

	m_strDisp.Format(_T("Finish Recover!"));

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iCrPnts[i][j][k] == 4 )
					{
						if(IsSC(i, j, k, m_iMatrix))
						{
							m_iMatrix[i][j][k] = MAXNUM*2+1;	//MAXNUM*2+1 represents SC points
						}
					}
					else if(m_iCrPnts[i][j][k] == 1 & m_iCluster[m_iMatrix[i][j][k]][1] == 1)
					{
						m_iMatrix[i][j][k] = MAXNUM*2;		//MAXNUM*2 represents SE points
					}
					else if(m_iCrPnts[i][j][k] == 7)
						m_iMatrix[i][j][k] = MAXNUM*2+4;		//MAXNUM*2+4 represents CC points
					else if(m_iCrPnts[i][j][k] == 5)
						m_iMatrix[i][j][k] = MAXNUM*2+5;	//MAXNUM*2+5 represents CE points
					else if(m_iCluster[m_iMatrix[i][j][k]][1] == 2 && (m_iCrPnts[i][j][k] == 1 || m_iCrPnts[i][j][k] == 2))
					{
						m_iMatrix[i][j][k] = 0;
					}
				}
				
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] == MAXNUM*2 && IsSE_TR(i, j, k, m_iMatrix))
					m_iMatrix[i][j][k] = MAXNUM*2+2;		//MAXNUM*2+2 represents SE points for meshing (intersection of more than two shell, at surface edge)
				else if(m_iMatrix[i][j][k] > 0 && IsSI_TR(i, j, k, m_iMatrix))//m_iCrPnts[i][j][k] == 3 
				{
					m_iMatrix[i][j][k] = MAXNUM*2+3;		//MAXNUM*2+3 represents SI points for meshing (intersection of more than three shell, not at surface edge)
				}
			}
		}
	}

	//return;

	for(i=1; i<=m_iTraNo; i++)
	{
		m_iCluster[i][2] = 0;
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && m_iMatrix[i][j][k] < 2*MAXNUM)
				{
					m_iCluster[(int)m_iMatrix[i][j][k]][2]++;
				}
			}
		}
	}

	//Initialize m_iMatrix for clustering analyses of all the nodes
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				m_iCrPnts[i][j][k] = m_iMatrix[i][j][k];
				if(m_iMatrix[i][j][k] <= 2*MAXNUM)
					m_iMatrix[i][j][k] = 0;
				else
					m_iMatrix[i][j][k] = 1;
			}
		}
	}

	m_iNodeSize = HKcluster4S(m_iMatrix, m_iSize)*2;

	//malloc the memory space for m_iNode
	m_iNode = (int **)calloc(m_iNodeSize, sizeof(int*));

	for(i=0; i<m_iNodeSize; i++)
	{
		m_iNode[i] = (int *)calloc(100, sizeof(int));
	}

	for(i=0; i<m_iNodeSize; i++)
		for(j=0; j<100; j++)
			m_iNode[i][j] = 0;

	m_iClusterNode = (int **)calloc(m_iTraNo+1, sizeof(int*));


	for(i=0; i<m_iTraNo+1; i++)
	{
		m_iClusterNode[i] = (int *)calloc(100, sizeof(int));
	}

	for(i=0; i<m_iTraNo+1; i++)
		for(j=0; j<100; j++)
			m_iClusterNode[i][j] = 0;

	//Summarize all the information for each node
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] == 0)
						m_iNode[m_iMatrix[i][j][k]][0] = m_iCrPnts[i][j][k]-2*MAXNUM;
					else if(m_iCrPnts[i][j][k]-2*MAXNUM < m_iNode[m_iMatrix[i][j][k]][0])
						m_iNode[m_iMatrix[i][j][k]][0] = m_iCrPnts[i][j][k]-2*MAXNUM;
					Node_Conn(i, j, k, m_iCrPnts, m_iMatrix, m_iPtType, m_iNode);
				}
			}
		}
	}

	int count = 5;
	for(i=1; i<m_iNodeSize; i++)
	{
		count = 5;
		while(m_iNode[i][count]!=0)
		{
			count++;
			m_iNode[i][4]++;
		}
	}

	//Summarize node information for each individual trabecula
	for(i=1; i<m_iNodeSize; i++)
	{
		count = 5;
		while(m_iNode[i][count] != 0)
		{
			m_iClusterNode[m_iNode[i][count]][0]++;
			m_iClusterNode[m_iNode[i][count]][m_iClusterNode[m_iNode[i][count]][0]] = i;
			count++;
		}
	}

	//if a rod branch has only one node, delete the cluster
	temp = 0;
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 2 && m_iClusterNode[i][0]==1)
		{
			count = 5;
			while(count != 0)
			{
				if(m_iNode[m_iClusterNode[i][1]][count] == i)
				{
					if(count == 4+m_iNode[m_iClusterNode[i][1]][4])
						m_iNode[m_iClusterNode[i][1]][count] = 0;
					else if(count < 4+m_iNode[m_iClusterNode[i][1]][4])
						m_iNode[m_iClusterNode[i][1]][count] = m_iNode[m_iClusterNode[i][1]][4+m_iNode[m_iClusterNode[i][1]][4]];
					else
						MessageBox(_T("mistake1!"), NULL, MB_OK);

					count = 0;
				}
				else if(count-4>m_iNode[m_iClusterNode[i][1]][4])
				{
					MessageBox(_T("mistake!"), NULL, MB_OK);
					count = 0;
				}
				else
					count++;
			}

			m_iNode[m_iClusterNode[i][1]][4]--;

			for(j=0; j<100; j++)
				m_iClusterNode[i][j] = 0;
			m_iCluster[i][2] = 0;
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iCrPnts[i][j][k]> 0 && m_iCrPnts[i][j][k]< 2*MAXNUM)
				{
					if(m_iClusterNode[m_iCrPnts[i][j][k]][0] != 0)
					{
						if(m_iCluster[m_iCrPnts[i][j][k]][2]<=2 && m_iCluster[m_iCrPnts[i][j][k]][1] == 2)
						{
							//First step, search for all the small branches which have CE as one of the nodes.
							if(m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][1]][0] ==5 || m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][2]][0] == 5)
							{
								//Set the other voxel which also belongs to this small branch (if there is any) as zero
								for(a=0; a<=2; a++)
								{
									for(b=0; b<=2; b++)
									{
										for(c=0; c<=2; c++)
										{
											if(m_iCrPnts[i-1+a][j-1+b][k-1+c] == m_iCrPnts[i][j][k] && !(a==1 && b==1 && c==1))
											{
												m_iCrPnts[i-1+a][j-1+b][k-1+c] = 0;
											}
										}
									}
								}

								//The CE voxel which connect with the small branch is marked as zero in the node type ([0] of m_iNode)
								if(m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][1]][0] ==5)
								{	
									temp2 = m_iClusterNode[m_iCrPnts[i][j][k]][1];
									temp1 = m_iClusterNode[m_iCrPnts[i][j][k]][2];
								}
								else if (m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][2]][0] ==5)
								{
									temp1 = m_iClusterNode[m_iCrPnts[i][j][k]][1];
									temp2 = m_iClusterNode[m_iCrPnts[i][j][k]][2];
								}

								m_iNode[temp2][0] = 0;

								//The CC or SC voxel which connect with the small branch is processed: the total number of connected cluster decreases by one, the small branch is deleted from the connected cluster list
								if(m_iNode[temp1][0] ==4 || m_iNode[temp1][0] ==1 || m_iNode[temp1][0] == 2 || m_iNode[temp1][0] == 3)
								{
									count = 5;
									while(count != 0)
									{
										if(m_iNode[temp1][count] == m_iCrPnts[i][j][k])
										{
											if(count == 4+m_iNode[temp1][4])
												m_iNode[temp1][count] = 0;
											else if(count < 4+m_iNode[temp1][4])
												m_iNode[temp1][count] = m_iNode[temp1][4+m_iNode[temp1][4]];
											else
												MessageBox(_T("mistake1!"), NULL, MB_OK);

											count = 0;
										}
										else if(count-4>m_iNode[temp1][4])
										{
											MessageBox(_T("mistake!"), NULL, MB_OK);
											count = 0;
										}
										else
											count++;
									}
									m_iNode[temp1][4]--;
								}
								else 
									MessageBox(_T("mistake2!"), NULL, MB_OK);

								//the total node of the small branch is set to be zero
								m_iClusterNode[m_iCrPnts[i][j][k]][0] = 0;
								m_iClusterNode[m_iCrPnts[i][j][k]][1] = 0;
								m_iCluster[m_iCrPnts[i][j][k]][2] = 0;
								//the voxel belonging to the small branch is set to be zero in m_iCrPnts
								m_iCrPnts[i][j][k] = 0;
							}
						}
					}
				}
			}
		}
	}

	//connect the two branches sharing the same C-C point which only has two connection
	for(i=1; i<m_iNodeSize; i++)
	{
		if(m_iNode[i][0] == 4 && m_iNode[i][4] == 2)
		{
			if(m_iClusterNode[m_iNode[i][5]][0] == 2 && m_iClusterNode[m_iNode[i][6]][0] ==2)
			{
				if(m_iClusterNode[m_iNode[i][6]][1] != i)
					temp = m_iClusterNode[m_iNode[i][6]][1];
				else if (m_iClusterNode[m_iNode[i][6]][1] == i)
					temp = m_iClusterNode[m_iNode[i][6]][2];
				else
					MessageBox(_T("mistake6!"), NULL, MB_OK);

				if(m_iClusterNode[m_iNode[i][5]][1] == i)
					m_iClusterNode[m_iNode[i][5]][1] = temp;
				else if(m_iClusterNode[m_iNode[i][5]][2] == i)
					m_iClusterNode[m_iNode[i][5]][2] = temp;
				else
					MessageBox(_T("mistake7!"), NULL, MB_OK);

				count = 5;
				while(count != 0)
				{
					if(m_iNode[temp][count] == m_iNode[i][6])
					{
						m_iNode[temp][count] = m_iNode[i][5];
						count = 0;
					}
					else if(count-4>m_iNode[temp][4])
					{
						MessageBox(_T("mistake!"), NULL, MB_OK);
						count = 0;
					}
					else
						count++;
				}
				
				m_iNode[i][0] = 0;
				m_iNode[i][1] = m_iNode[i][5];

				m_iClusterNode[m_iNode[i][6]][0] = 0;
				m_iClusterNode[m_iNode[i][6]][1] = m_iNode[i][5];

				m_iCluster[m_iNode[i][5]][2] += m_iCluster[m_iNode[i][6]][2];
				m_iCluster[m_iNode[i][6]][2] = 0;
			}
		}
	}


	//reevaluate m_iCrPnts and m_iMatrix
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iCrPnts[i][j][k] > m_iTraNo && m_iCrPnts[i][j][k]<2*MAXNUM)
					i=i;
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] == 0)
					{
						if(m_iNode[m_iMatrix[i][j][k]][1] != 0)
						{
							m_iCrPnts[i][j][k] = m_iNode[m_iMatrix[i][j][k]][1];
						}
						else
							m_iCrPnts[i][j][k] = 0;
					}
				}
				else if(m_iCrPnts[i][j][k] > 0 && m_iCrPnts[i][j][k] < MAXNUM*2 && m_iCluster[m_iCrPnts[i][j][k]][2] == 0)
					m_iCrPnts[i][j][k] =  m_iClusterNode[m_iCrPnts[i][j][k]][1];

				if(m_iCrPnts[i][j][k] > m_iTraNo && m_iCrPnts[i][j][k]<2*MAXNUM)
				{
					m_iCrPnts[i][j][k] = 0;
				}
			}
		}
	}
/*	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				m_iMatrix[i][j][k] = m_iCrPnts[i][j][k];
			}
		}
	}

	return;
*/

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iCrPnts[i][j][k]> 0 && m_iCrPnts[i][j][k]< 2*MAXNUM)
				{
					if(m_iClusterNode[m_iCrPnts[i][j][k]][0] != 0)
					{
						if(m_iCluster[m_iCrPnts[i][j][k]][2]<=2 && m_iCluster[m_iCrPnts[i][j][k]][1] == 2)
						{
							//Second step, search for all the small branches which have CC as one of the nodes.
							if((m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][1]][0] !=5 && m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][2]][0] !=5) 
								&& (m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][1]][0] ==4 || m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][2]][0] == 4))
							{
								if(m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][1]][0] <= m_iNode[m_iClusterNode[m_iCrPnts[i][j][k]][2]][0])
								{
									temp1 = m_iClusterNode[m_iCrPnts[i][j][k]][1];
									temp2 = m_iClusterNode[m_iCrPnts[i][j][k]][2];
								}
								else
								{
									temp2 = m_iClusterNode[m_iCrPnts[i][j][k]][1];
									temp1 = m_iClusterNode[m_iCrPnts[i][j][k]][2];
								}

								//Set the other voxel which also belongs to this small branch (if there is any) as CC or SC 
								for(a=0; a<=2; a++)
								{
									for(b=0; b<=2; b++)
									{
										for(c=0; c<=2; c++)
										{
											if(m_iCrPnts[i-1+a][j-1+b][k-1+c] == m_iCrPnts[i][j][k] && !(a==1 && b==1 && c==1))
											{
												m_iCrPnts[i-1+a][j-1+b][k-1+c] = 2*MAXNUM + m_iNode[temp1][0];
											}
										}
									}
								}

								for(a=5; a<5+m_iNode[temp2][4]; a++)
								{
									count = 1;
									while(count != 0)
									{
										if(m_iNode[temp2][a] == m_iCrPnts[i][j][k])
											count = 0;
										else if(m_iClusterNode[m_iNode[temp2][a]][count] == temp2)
										{
											m_iClusterNode[m_iNode[temp2][a]][count] = temp1;
											count = 0;
										}
										else if(count > m_iClusterNode[m_iNode[temp2][a]][0])
											MessageBox(_T("mistake5!"), NULL, MB_OK);
										else
											count++;
									}
								}

								temp = m_iNode[temp1][4];
								for(a=5; a<5+m_iNode[temp2][4]; a++)
								{
									count = 0;
									for(b=5; b<5+temp; b++)
									{
										if(m_iNode[temp2][a]==m_iNode[temp1][b])
											count =1;
									}
									if(count == 0)
									{
										m_iNode[temp1][5+m_iNode[temp1][4]] = m_iNode[temp2][a];
										m_iNode[temp1][4]++;
									}
								}

								//the total node of the small branch is set to be zero
								m_iClusterNode[m_iCrPnts[i][j][k]][0] = 0;
								m_iCluster[m_iCrPnts[i][j][k]][2] = 0;
								//the voxel belonging to the small branch is set to be CC or SC in m_iCrPnts
								m_iCrPnts[i][j][k] = 2*MAXNUM + m_iNode[temp1][0];

								m_iNode[temp2][0] = 0;
								m_iNode[temp2][1] = 0;
							}
							else
								temp = temp;
						}
					}
				}
			}
		}
	}

/*	//combine the Surface-Inner nodes which have the same neighborhood
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] == 0 && m_iNode[m_iMatrix[i][j][k]][1] != 0)
						m_iMatrix[i][j][k] = m_iNode[m_iMatrix[i][j][k]][1];
					else if(m_iNode[m_iMatrix[i][j][k]][0] == 3)
					{
						for(a=0; a<=4; a++)
						{
							for(b=0; b<=4; b++)
							{
								for(c=0; c<=4; c++)
								{
									if(m_iMatrix[i-2+a][j-2+b][k-2+c] > 0 && m_iNode[m_iMatrix[i-2+a][j-2+b][k-2+c]][0] == 0 && m_iNode[m_iMatrix[i-2+a][j-2+b][k-2+c]][1] != 0)
										m_iMatrix[i-2+a][j-2+b][k-2+c] = m_iNode[m_iMatrix[i-2+a][j-2+b][k-2+c]][1];
									if(m_iMatrix[i-2+a][j-2+b][k-2+c] > 0 && m_iMatrix[i-2+a][j-2+b][k-2+c] != m_iMatrix[i][j][k] && !(a==2 && b==2 && c==2))
									{
										CompareNode(m_iMatrix[i][j][k], m_iMatrix[i-2+a][j-2+b][k-2+c], m_iClusterNode, m_iNode);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//reevaluate m_iMatrix
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] == 0)
					{
						if(m_iNode[m_iMatrix[i][j][k]][1] != 0)
						{
							m_iCrPnts[i][j][k] = m_iNode[m_iMatrix[i][j][k]][1];
							m_iMatrix[i][j][k] = m_iCrPnts[i][j][k] ;
						}
						else
							m_iCrPnts[i][j][k] = 0;
					}
				}
			}
		}
	}*/

	//malloc the memory space for iNodeTemp
	int** iNodeTemp = (int **)calloc(m_iNodeSize, sizeof(int*));
	for(i=0; i<m_iNodeSize; i++)
	{
		iNodeTemp[i] = (int *)calloc(4, sizeof(int));
	}

	for(i=0; i<m_iNodeSize; i++)
	{
		iNodeTemp[i][0] = 0;
		for(j=1; j<=3; j++)
		{
			m_iNode[i][j] = 0;
			iNodeTemp[i][j] = 0;
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					iNodeTemp[m_iMatrix[i][j][k]][0]++;
					iNodeTemp[m_iMatrix[i][j][k]][1] += i;
					iNodeTemp[m_iMatrix[i][j][k]][2] += j;
					iNodeTemp[m_iMatrix[i][j][k]][3] += k;
				}
			}
		}
	}	
	
	for(i=0; i<m_iNodeSize; i++)
	{
		if(iNodeTemp[i][0] > 0)
		{
			iNodeTemp[i][1] /= iNodeTemp[i][0];
			iNodeTemp[i][2] /= iNodeTemp[i][0];
			iNodeTemp[i][3] /= iNodeTemp[i][0];
		}
		iNodeTemp[i][0] = MAXNUM;
	}

	//Determine the coordinate of node
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					temp = m_iMatrix[i][j][k];
					temp1 = sqrtf(float((iNodeTemp[temp][1]-i)*(iNodeTemp[temp][1]-i)+(iNodeTemp[temp][2]-j)*(iNodeTemp[temp][2]-j)+(iNodeTemp[temp][3]-k)*(iNodeTemp[temp][3]-k)));
					if(iNodeTemp[temp][0] > temp1)
					{
						iNodeTemp[temp][0] = temp1;
						m_iNode[temp][1] = i;
						m_iNode[temp][2] = j;
						m_iNode[temp][3] = k;
					}
				}
			}
		}
	}

	for(i=0; i<m_iNodeSize; i++)
	{
		free(iNodeTemp[i]);
	}
	free(iNodeTemp);

	//***********************************************************************
	//further programming on constructing beam element should be added here//
	//***********************************************************************

	//Add one node point to the edge of surface cluster which only have two nodes
	float MaxLength;

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_iCluster[i][2] > 0)
		{
			if(m_iClusterNode[i][0] <= 1)
			{
				//MessageBox(_T("mistake8!"), NULL, MB_OK);
				m_iCluster[i][2] = 0;
			}
			else if(m_iClusterNode[i][0] == 2)
			{
				MaxLength = 0;
				for(c=2; c<m_iSize[2]+2; c++)
				{
					for(b=2; b<m_iSize[1]+2; b++)
					{
						for(a=2; a<m_iSize[0]+2; a++)
						{
							if(m_iPtType[a][b][c] == i && m_iCrPnts[a][b][c] == MAXNUM*2)
							{
								if(MaxLength < (sqrtf(float((a-m_iNode[m_iClusterNode[i][1]][1])*(a-m_iNode[m_iClusterNode[i][1]][1])+(b-m_iNode[m_iClusterNode[i][1]][2])*(b-m_iNode[m_iClusterNode[i][1]][2])+(c-m_iNode[m_iClusterNode[i][1]][3])*(c-m_iNode[m_iClusterNode[i][1]][3])))
											  +	sqrtf(float((a-m_iNode[m_iClusterNode[i][2]][1])*(a-m_iNode[m_iClusterNode[i][2]][1])+(b-m_iNode[m_iClusterNode[i][2]][2])*(b-m_iNode[m_iClusterNode[i][2]][2])+(c-m_iNode[m_iClusterNode[i][2]][3])*(c-m_iNode[m_iClusterNode[i][2]][3])))))
								{
									temp1 = a;
									temp2 = b;
									temp3 = c;
									MaxLength = sqrtf(float((a-m_iNode[m_iClusterNode[i][1]][1])*(a-m_iNode[m_iClusterNode[i][1]][1])+(b-m_iNode[m_iClusterNode[i][1]][2])*(b-m_iNode[m_iClusterNode[i][1]][2])+(c-m_iNode[m_iClusterNode[i][1]][3])*(c-m_iNode[m_iClusterNode[i][1]][3])))
											  +	sqrtf(float((a-m_iNode[m_iClusterNode[i][2]][1])*(a-m_iNode[m_iClusterNode[i][2]][1])+(b-m_iNode[m_iClusterNode[i][2]][2])*(b-m_iNode[m_iClusterNode[i][2]][2])+(c-m_iNode[m_iClusterNode[i][2]][3])*(c-m_iNode[m_iClusterNode[i][2]][3])));
								}
							}
						}
					}
				}
				if(MaxLength == 0)
					m_iCluster[i][1] = 2;
				else
				{
					m_iCrPnts[temp1][temp2][temp3] = 2*MAXNUM + 6;
					count = 1;
					while(count != 0 )
					{
						if(m_iNode[count][0] == 0)
						{
							m_iNode[count][0] = 6;			//SE mesh point which only have one cluster neightbor
							m_iNode[count][1] = temp1;
							m_iNode[count][2] = temp2;
							m_iNode[count][3] = temp3;
							m_iNode[count][4] = 1;
							m_iNode[count][5] = i;
							m_iClusterNode[i][0] = 3;
							m_iClusterNode[i][3] = count;
							m_iMatrix[temp1][temp2][temp3] = count;
							count = 0;
						}
						else if(count<m_iNodeSize-1)
							count++;
						else
							MessageBox(_T("Node Size out of bound!"), NULL, MB_OK);
					}
				}
			}
		}
	}

	//***********************************************************************
	//********************Start evaluation of orientation********************
	//***********************************************************************
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iCrPnts[i][j][k] < 2*MAXNUM)
					m_iMatrix[i][j][k] = m_iCrPnts[i][j][k];
				else if(m_iCrPnts[i][j][k] == 2*MAXNUM)
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];
				else
					m_iMatrix[i][j][k] = 0;

			}
		}
	}	

	//co:[0]x^2 [1]y^2 [2]z^2 [3]x*y [4]y*z [5]x*z [6]x [7]y [8]z
	float **co;
	co = (float **)calloc(m_iTraNo+1, sizeof(float*));
	
	for(i=0; i<=m_iTraNo; i++)
	{
		co[i] = (float *)calloc(9, sizeof(float));
	}
	
	for(i=0; i<=m_iTraNo; i++)
	{
		for(j=0; j<9; j++)
		{
			co[i][j] = 0;
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		m_iCluster[i][0] = 0;
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]> 0)
				{
					co[m_iMatrix[i][j][k]][6] += i;
					co[m_iMatrix[i][j][k]][7] += j;
					co[m_iMatrix[i][j][k]][8] += k;
					m_iCluster[m_iMatrix[i][j][k]][0]++;
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 2)
		{
			co[i][6] = co[i][6]/(float)m_iCluster[i][0];
			co[i][7] = co[i][7]/(float)m_iCluster[i][0];
			co[i][8] = co[i][8]/(float)m_iCluster[i][0];
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && m_iCluster[m_iMatrix[i][j][k]][1] == 2)
				{
					co[m_iMatrix[i][j][k]][0] += (i-co[m_iMatrix[i][j][k]][6])*(i-co[m_iMatrix[i][j][k]][6]);
					co[m_iMatrix[i][j][k]][1] += (j-co[m_iMatrix[i][j][k]][7])*(j-co[m_iMatrix[i][j][k]][7]);
					co[m_iMatrix[i][j][k]][2] += (k-co[m_iMatrix[i][j][k]][8])*(k-co[m_iMatrix[i][j][k]][8]);
					co[m_iMatrix[i][j][k]][3] += (i-co[m_iMatrix[i][j][k]][6])*(j-co[m_iMatrix[i][j][k]][7]);
					co[m_iMatrix[i][j][k]][4] += (j-co[m_iMatrix[i][j][k]][7])*(k-co[m_iMatrix[i][j][k]][8]);
					co[m_iMatrix[i][j][k]][5] += (k-co[m_iMatrix[i][j][k]][8])*(i-co[m_iMatrix[i][j][k]][6]);
				}
			}
		}
	}

	float **A;
	A = (float **)calloc(4, sizeof(float*));
	
	for(i=0; i<4; i++)
	{
		A[i] = (float *)calloc(5, sizeof(float));
	}
	
	for(i=0; i<4; i++)
	{
		for(j=0; j<5; j++)
		{
			A[i][j] = 0;
		}
	}//only use A[1-3][1-4]

	float *Diagonal;
	Diagonal = (float *)calloc(4, sizeof(float));
	for(i=0; i<4; i++)
		Diagonal[i] = 0;

	float *SubDiagonal;
	SubDiagonal = (float *)calloc(4, sizeof(float));
	for(i=0; i<4; i++)
		SubDiagonal[i] = 0;	

	float total;
	//co:[0]x^2 [1]y^2 [2]z^2 [3]x*y [4]y*z [5]x*z [6]x [7]y [8]z

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 2 && m_iCluster[i][2] > 0 && m_iClusterNode[i][0]>=2)	//getting rod orientation
		{
			/*A[1][1] = co[i][0];
			A[1][2] = co[i][3];
			A[1][3] = co[i][5];
			A[2][1] = co[i][3];
			A[2][2] = co[i][1];
			A[2][3] = co[i][4];
			A[3][1] = co[i][5];
			A[3][2] = co[i][4];
			A[3][3] = co[i][2];
			//GetOri(A, m_fNorm, i);
			tred2(A, 3, Diagonal, SubDiagonal);
			tqli(Diagonal, SubDiagonal, 3, A);
			int tempmax=0;
			Diagonal[0] =0;
			for(j=1; j<=3; j++)
			{
				if(Diagonal[j]>Diagonal[tempmax])
					tempmax=j;
			}

			m_fNorm[i][0] = A[1][tempmax];
			m_fNorm[i][1] = A[2][tempmax];
			m_fNorm[i][2] = A[3][tempmax];
			m_fNorm[i][3] = m_fNorm[i][0];
			m_fNorm[i][4] = m_fNorm[i][1];
			m_fNorm[i][5] = m_fNorm[i][2];

			if(m_fNorm[i][0] == 0 && m_fNorm[i][1] == 0 && m_fNorm[i][2] == 0)
			{*/
				m_fNorm[i][0] = float(m_iNode[m_iClusterNode[i][1]][1]-m_iNode[m_iClusterNode[i][2]][1])/
					sqrtf(powf(float(m_iNode[m_iClusterNode[i][1]][1]-m_iNode[m_iClusterNode[i][2]][1]), 2.0) + powf(float(m_iNode[m_iClusterNode[i][1]][2]-m_iNode[m_iClusterNode[i][2]][2]), 2.0) + powf(float(m_iNode[m_iClusterNode[i][1]][3]-m_iNode[m_iClusterNode[i][2]][3]), 2.0));
				m_fNorm[i][1] = float(m_iNode[m_iClusterNode[i][1]][2]-m_iNode[m_iClusterNode[i][2]][2])/
					sqrtf(powf(float(m_iNode[m_iClusterNode[i][1]][1]-m_iNode[m_iClusterNode[i][2]][1]), 2.0) + powf(float(m_iNode[m_iClusterNode[i][1]][2]-m_iNode[m_iClusterNode[i][2]][2]), 2.0) + powf(float(m_iNode[m_iClusterNode[i][1]][3]-m_iNode[m_iClusterNode[i][2]][3]), 2.0));
				m_fNorm[i][2] = float(m_iNode[m_iClusterNode[i][1]][3]-m_iNode[m_iClusterNode[i][2]][3])/
					sqrtf(powf(float(m_iNode[m_iClusterNode[i][1]][1]-m_iNode[m_iClusterNode[i][2]][1]), 2.0) + powf(float(m_iNode[m_iClusterNode[i][1]][2]-m_iNode[m_iClusterNode[i][2]][2]), 2.0) + powf(float(m_iNode[m_iClusterNode[i][1]][3]-m_iNode[m_iClusterNode[i][2]][3]), 2.0));
				m_fNorm[i][3] = m_fNorm[i][0];
				m_fNorm[i][4] = m_fNorm[i][1];
				m_fNorm[i][5] = m_fNorm[i][2];
			//}
		}
	}

	//Getting normal for each plate cluster
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_iCluster[i][2] > 0)
		{
			temp = GetPlateNormal(i, m_iClusterNode, m_iNode, m_fNorm);
			if(temp == 0)
			{
				m_iCluster[i][2] = 0;
				i=i;//MessageBox(_T("mistake9!"), NULL, MB_OK);
			}
		}
	}

	//get thickness for trabecular rod
	float fa, fb, fc;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0  && m_iCluster[m_iMatrix[i][j][k]][1] == 2 && m_iCluster[m_iMatrix[i][j][k]][2]>0 && m_fTh[m_iMatrix[i][j][k]][3] != MAXNUM)
				{
					fa=m_fNorm[m_iMatrix[i][j][k]][3];
					fb=m_fNorm[m_iMatrix[i][j][k]][4];
					fc=m_fNorm[m_iMatrix[i][j][k]][5];
					if(fa!=0 && fb!=0 && fc!=0)	//general case
					{
						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = fc/sqrtf(fb*fb+fc*fc);
						m_fNorm[m_iMatrix[i][j][k]][2] = -1*fb/sqrtf(fb*fb+fc*fc);
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
						
						m_fNorm[m_iMatrix[i][j][k]][0] = fc/sqrtf(fa*fa+fc*fc);
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = -1*fa/sqrtf(fa*fa+fc*fc);
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = fb/sqrtf(fb*fb+fa*fa);
						m_fNorm[m_iMatrix[i][j][k]][1] = -1*fa/sqrtf(fb*fb+fa*fa);
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
					}
					else if(fa!=0 && fb!=0 && fc==0)	//special case 1
					{
						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = 1;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
						
						m_fNorm[m_iMatrix[i][j][k]][0] = sqrtf(2)*fb/sqrtf(fb*fb+fa*fa)/2;
						m_fNorm[m_iMatrix[i][j][k]][1] = -1*sqrtf(2)*fa/sqrtf(fb*fb+fa*fa)/2;
						m_fNorm[m_iMatrix[i][j][k]][2] = sqrt(2.0)/2;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = fb/sqrtf(fb*fb+fa*fa);
						m_fNorm[m_iMatrix[i][j][k]][1] = -1*fa/sqrtf(fb*fb+fa*fa);
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
					}
					else if(fa!=0 && fb==0 && fc!=0)
					{
						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = 1;
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
						
						m_fNorm[m_iMatrix[i][j][k]][0] = sqrtf(2)*fc/sqrtf(fc*fc+fa*fa)/2;
						m_fNorm[m_iMatrix[i][j][k]][1] = sqrtf(2)/2;
						m_fNorm[m_iMatrix[i][j][k]][2] = -1*sqrtf(2)*fa/sqrtf(fc*fc+fa*fa)/2;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = fc/sqrtf(fc*fc+fa*fa);
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = -1*fa/sqrtf(fc*fc+fa*fa);
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
					}
					else if(fa==0 && fb!=0 && fc!=0)
					{
						m_fNorm[m_iMatrix[i][j][k]][0] = 1;
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
						
						m_fNorm[m_iMatrix[i][j][k]][0] = sqrtf(2)/2;
						m_fNorm[m_iMatrix[i][j][k]][1] = sqrtf(2)*fc/sqrtf(fc*fc+fb*fb)/2;
						m_fNorm[m_iMatrix[i][j][k]][2] = -1*sqrtf(2)*fb/sqrtf(fc*fc+fb*fb)/2;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = fc/sqrtf(fc*fc+fb*fb);
						m_fNorm[m_iMatrix[i][j][k]][2] = -1*fb/sqrtf(fc*fc+fb*fb);
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
					}
					else if(fa==0 && fb==0 && (fc==1 || fc==-1))	//special case 3
					{
						m_fNorm[m_iMatrix[i][j][k]][0] = 1;
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = 1;
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = sqrtf(2)/2;
						m_fNorm[m_iMatrix[i][j][k]][1] = sqrtf(2)/2;
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
					}
					else if(fa==0 && (fb==1 || fb==-1) && fc==0)
					{
						m_fNorm[m_iMatrix[i][j][k]][0] = 1;
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = 1;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = sqrtf(2)/2;
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = sqrtf(2)/2;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
					}
					else if((fa==1 ||fa==-1) && fb==0 && fc==0)
					{
						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = 1;
						m_fNorm[m_iMatrix[i][j][k]][2] = 0;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = 0;
						m_fNorm[m_iMatrix[i][j][k]][2] = 1;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);

						m_fNorm[m_iMatrix[i][j][k]][0] = 0;
						m_fNorm[m_iMatrix[i][j][k]][1] = sqrtf(2)/2;
						m_fNorm[m_iMatrix[i][j][k]][2] = sqrtf(2)/2;
						GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
					}
				}
				else if(m_iMatrix[i][j][k] > 0  && m_iCluster[m_iMatrix[i][j][k]][1] == 1 && m_iCluster[m_iMatrix[i][j][k]][2] > 0)
				{
					GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_iCluster[i][2]!=0)
		{
			if(m_fTh[i][0] != MAXNUM)
				m_fTh[i][0] = m_fTh[i][0]/((float)m_iCluster[i][2]);
			else
			{
				m_fTh[i][0] = 1;
				MessageBox(_T("plate thickness out of bound!"), NULL, MB_OK);
			}
		}
		else if(m_iCluster[i][1] == 2 && m_iCluster[i][2]!= 0)
		{
			if(m_fTh[i][0] != MAXNUM)
			{
				m_fTh[i][0] /= (3*(float)m_iCluster[i][2]);
				m_fNorm[i][0] = m_fNorm[i][3];
				m_fNorm[i][1] = m_fNorm[i][4];
				m_fNorm[i][2] = m_fNorm[i][5];
			}
			else
			{
				m_fTh[i][0] = 1;
				m_fNorm[i][0] = m_fNorm[i][3];
				m_fNorm[i][1] = m_fNorm[i][4];
				m_fNorm[i][2] = m_fNorm[i][5];
			}
		}
	}
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 2 && m_iCluster[i][2]!= 0)
		{
			fa=m_fNorm[i][0];
			fb=m_fNorm[i][1];
			fc=m_fNorm[i][2];
			if(fa!=0 && fb!=0 && fc!=0)	//general case
			{
				m_fNorm[i][3] = 0;
				m_fNorm[i][4] = fc/sqrtf(fb*fb+fc*fc);
				m_fNorm[i][5] = -1*fb/sqrtf(fb*fb+fc*fc);
			}
			else if(fa!=0 && fb!=0 && fc==0)	//special case 1
			{
				m_fNorm[i][3] = 0;
				m_fNorm[i][4] = 0;
				m_fNorm[i][5] = 1;
			}
			else if(fa!=0 && fb==0 && fc!=0)
			{
				m_fNorm[i][3] = 0;
				m_fNorm[i][4] = 1;
				m_fNorm[i][5] = 0;
			}
			else if(fa==0 && fb!=0 && fc!=0)
			{
				m_fNorm[i][3] = 1;
				m_fNorm[i][4] = 0;
				m_fNorm[i][5] = 0;
			}
			else if(fa==0 && fb==0 && (fc==1 || fc==-1))	//special case 3
			{
				m_fNorm[i][3] = 1;
				m_fNorm[i][4] = 0;
				m_fNorm[i][5] = 0;
			}
			else if(fa==0 && (fb==1 ||fb==-1) && fc==0)
			{
				m_fNorm[i][3] = 1;
				m_fNorm[i][4] = 0;
				m_fNorm[i][5] = 0;
			}
			else if((fa==1 || fa==-1) && fb==0 && fc==0)
			{
				m_fNorm[i][3] = 0;
				m_fNorm[i][4] = 1;
				m_fNorm[i][5] = 0;
			}
		}
	}
	//***********************************************************************
	//********************Start of Delaunay Triangulation**********************
	//***********************************************************************
	m_strDisp.Format(_T("Begin Triangulation!"));

	m_iTriangle = (int **)calloc(m_iNodeSize*10, sizeof(int*));
	for(i=0; i<=m_iNodeSize*10; i++)
	{
		m_iTriangle[i] = (int *)calloc(4, sizeof(int));
		for(j=0; j<=3; j++)
			m_iTriangle[i][j] = 0;
	}
	m_iTriPointer = 1;
	
	float TempSize;
	float TempLength;
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_iClusterNode[i][0] >= 3)
		{
			if(fabs(m_fNorm[i][2])<sqrtf(2)/2.0)
				TempSize = float(m_iCluster[i][2])/sqrtf(1.0-m_fNorm[i][2]*m_fNorm[i][2]);
			else
				TempSize = float(m_iCluster[i][2])/m_fNorm[i][2];

			temp = Delaunay(i, m_iClusterNode[i], m_iNode, m_fNorm[i], TempSize, 0, m_iTriPointer, m_iTriangle);

			if(temp == 0)
			{
				MaxLength = 0;
				for(c=2; c<m_iSize[2]+2; c++)
				{
					for(b=2; b<m_iSize[1]+2; b++)
					{
						for(a=2; a<m_iSize[0]+2; a++)
						{
							if(m_iPtType[a][b][c] == i && m_iCrPnts[a][b][c] == MAXNUM*2)
							{
								TempLength = GetDistance(a, b, c, m_iClusterNode[i], m_iNode);
								if(MaxLength < TempLength)
								{
									temp1 = a;
									temp2 = b;
									temp3 = c;
									MaxLength = TempLength;
								}
							}
						}
					}
				}

				if(MaxLength != 0)
				{
					m_iCrPnts[temp1][temp2][temp3] = 2*MAXNUM + 6;

					count = 1;
					while(count != 0 )
					{
						if(m_iNode[count][0] == 0)
						{
							m_iNode[count][0] = 6;			//SE mesh point which only have one cluster neightbor
							m_iNode[count][1] = temp1;
							m_iNode[count][2] = temp2;
							m_iNode[count][3] = temp3;
							m_iNode[count][4] = 1;
							m_iNode[count][5] = i;
							m_iClusterNode[i][0] ++;
							m_iClusterNode[i][m_iClusterNode[i][0]] = count;
							count = 0;
						}
						else if(count<m_iNodeSize-1)
							count++;
						else
							MessageBox(_T("Node Size out of bound!"), NULL, MB_OK);
					}

					m_iTriPointer = Delaunay(i, m_iClusterNode[i], m_iNode, m_fNorm[i], TempSize, 1, m_iTriPointer, m_iTriangle);
				}
				else
					m_iTriPointer = Delaunay(i, m_iClusterNode[i], m_iNode, m_fNorm[i], TempSize, 1, m_iTriPointer, m_iTriangle);

			}
			else
				m_iTriPointer = temp;
		}
	}
	m_strDisp.Format(_T("Finish Triangulation!"));

	//************************************************************************
	temp=0;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iCrPnts[i][j][k] > 2*MAXNUM)
				{
					m_iMatrix[i][j][k] = m_iCrPnts[i][j][k];
					temp++;
				}
				else
					m_iMatrix[i][j][k] = 0;

				//m_iMatrix[i][j][k] = m_iCrPnts[i][j][k];

				/*m_iMatrix[i][j][k] = m_iCrPnts[i][j][k];
				if(m_iMatrix[i][j][k]> 0 && m_iMatrix[i][j][k] < MAXNUM*2)
				{
					if(m_iCluster[m_iMatrix[i][j][k]][1] == 2)
						m_iMatrix[i][j][k] = 0;
				}*/
			}
		}
	}	
	m_strDisp.Format(_T("Begin Writing Abaqus Input File!"));

	AbaqusInput();

	m_strDisp.Format(_T("Finish Writing Abaqus Input File!"));

	m_bMesh = TRUE;
	return;

/*	//************************************************************************
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]> 0)
				{
					m_iMatrix[i][j][k] += 2*MAXNUM;
				}
			}
		}
	}	
	
	//recover fPtType to original volume
	iEnd = 0;
	for(l=m_iPlateThr+1; l>-MAXNUM; l--)	
	{
		iEnd = 1;
		while(iEnd)
		{
			iEnd = 0;
			for(k=m_iSize[2]+1; k>1; k--)
			{
				for(j=m_iSize[1]+1; j>1; j--)
				{
					for(i=m_iSize[0]+1; i>1; i--)
					{
						if((int)m_iPtType[i][j][k]==l)
						{
							iTra = PrimaryRecover(m_iPtType, m_iMatrix, i, j, k, l);
							if(iTra == MAXNUM)
							{
								iEnd = 1;
							}
							else if(iTra > 0)
							{
								m_iPtType[i][j][k] = iTra;
							}
						}
					}
				}
			}
			for(k=2; k<m_iSize[2]+2; k++)
			{
				for(j=2; j<m_iSize[1]+2; j++)
				{
					for(i=2; i<m_iSize[0]+2; i++)
					{
						if(m_iPtType[i][j][k] > 0 && m_iMatrix[i][j][k]< 2*MAXNUM)
							m_iMatrix[i][j][k] = m_iPtType[i][j][k];
					}
				}
			}

			if(iEnd == 1)
			{
				for(k=m_iSize[2]+1; k>1; k--)
				{
					for(j=m_iSize[1]+1; j>1; j--)
					{
						for(i=m_iSize[0]+1; i>1; i--)
						{
							if((int)m_iPtType[i][j][k]>=l && (int)m_iPtType[i][j][k] < 0)
							{
								iTra = (int)RecoverConnection(m_iPtType, m_iMatrix, i, j, k);
								if(iTra == 0)
								{
									iEnd = 1;
								}
								else
								{
									m_iPtType[i][j][k] = iTra;
								}
							}
						}
					}
				}
				for(k=2; k<m_iSize[2]+2; k++)
				{
					for(j=2; j<m_iSize[1]+2; j++)
					{
						for(i=2; i<m_iSize[0]+2; i++)
						{
							if(m_iPtType[i][j][k] > 0 && m_iMatrix[i][j][k]< 2*MAXNUM )
								m_iMatrix[i][j][k] = m_iPtType[i][j][k];
						}
					}
				}
			}
		}
	}

	for(k=m_iSize[2]+1; k>1; k--)
	{
		for(j=m_iSize[1]+1; j>1; j--)
		{
			for(i=m_iSize[0]+1; i>1; i--)
			{
				if((int)m_iPtType[i][j][k]==-MAXNUM-1 || ((int)m_iPtType[i][j][k] > -MAXNUM && (int)m_iPtType[i][j][k] < 0))
				{
					iTra = (int)RecoverConnection(m_iPtType, m_iMatrix, i, j, k);
					if(iTra == 0)
					{
						iEnd = 1;
					}
					else
					{
						m_iPtType[i][j][k] = iTra;
						m_iMatrix[i][j][k] = iTra;
					}
				}
			}
		}
	}

	int tt=0;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]> 0)
				{
					tt++;
					if(m_iMatrix[i][j][k] > 2*MAXNUM)
						m_iMatrix[i][j][k] -= 2*MAXNUM;
					else
						m_iMatrix[i][j][k] += 2*MAXNUM;
				}
			}
		}
	}


	//get thickness from the normal(x-axis)
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] < 2*MAXNUM && m_iMatrix[i][j][k] > 0 && m_iCluster[m_iMatrix[i][j][k]][1] == 1 && m_fTh[m_iMatrix[i][j][k]][1] != MAXNUM)
				{
					m_fNorm[m_iMatrix[i][j][k]][0] = m_fNorm[m_iMatrix[i][j][k]][3];
					m_fNorm[m_iMatrix[i][j][k]][1] = m_fNorm[m_iMatrix[i][j][k]][4];
					m_fNorm[m_iMatrix[i][j][k]][2] = m_fNorm[m_iMatrix[i][j][k]][5];
					GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_fTh[i][1] != MAXNUM)
		{
			m_fTh[i][1] = m_fTh[i][0]/((float)m_iCluster[i][0]);
			m_fTh[i][0] = 0;
		}
	}

	//get thickness from the normal(y-axis)
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] < 2*MAXNUM && m_iMatrix[i][j][k] > 0 && m_iCluster[m_iMatrix[i][j][k]][1] == 1 && m_fTh[m_iMatrix[i][j][k]][2] != MAXNUM)
				{
					m_fNorm[m_iMatrix[i][j][k]][0] = m_fNorm[m_iMatrix[i][j][k]][6];
					m_fNorm[m_iMatrix[i][j][k]][1] = m_fNorm[m_iMatrix[i][j][k]][7];
					m_fNorm[m_iMatrix[i][j][k]][2] = m_fNorm[m_iMatrix[i][j][k]][8];
					GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_fTh[i][2] != MAXNUM)
		{
			m_fTh[i][2] = m_fTh[i][0]/((float)m_iCluster[i][0]);
			m_fTh[i][0] = 0;
		}
	}

	//get thickness from the normal(z-axis)
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] < 2*MAXNUM && m_iMatrix[i][j][k] > 0  && m_iCluster[m_iMatrix[i][j][k]][1] == 1 && m_fTh[m_iMatrix[i][j][k]][3] != MAXNUM)
				{
					m_fNorm[m_iMatrix[i][j][k]][0] = m_fNorm[m_iMatrix[i][j][k]][9];
					m_fNorm[m_iMatrix[i][j][k]][1] = m_fNorm[m_iMatrix[i][j][k]][10];
					m_fNorm[m_iMatrix[i][j][k]][2] = m_fNorm[m_iMatrix[i][j][k]][11];
					GetTh(m_iMatrix, m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_fTh[i][3] != MAXNUM)
		{
			m_fTh[i][3] = m_fTh[i][0]/((float)m_iCluster[i][0]);
			m_fTh[i][0] = 0;
		}
	}*/


	//*****************************************************************************
	int end;
	BYTE cha1=' ';
	char cha10[10];
	
	//save voxel number array
	//CFileDialog fSaveDlg3(FALSE,NULL,NULL);
	//fSaveDlg3.m_ofn.lpstrTitle = _T("Save voxel number array");
	CFile crfile;
	//fSaveDlg3.DoModal();
    CString str;
	str = m_strPath;
	str.Insert(m_strPath.GetLength(), _T(".voxelno"));
	crfile.Open(str.GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	for(i=1; i<=m_iTraNo; i++)
	{
		_gcvt(m_iCluster[i][0], 10, cha10);
		for(k=0; k<10; k++)
		{
			if(cha10[k]==46)
			{
				cha10[k] = 13;
				cha10[k+1] = 10;
				end = k+2;
				k = 10;
			}
		}
		crfile.Write(&cha10, end);
		for(k=0; k<10; k++)
			cha10[k]=0;
	}

	//save rod/plate array
	//CFileDialog fSaveDlg4(FALSE,NULL,NULL);
	//fSaveDlg4.m_ofn.lpstrTitle = _T("Save rod/plate array");
	CFile crfile2;
	//fSaveDlg4.DoModal();
	str = m_strPath;
	str.Insert(m_strPath.GetLength(), _T(".type"));
	crfile2.Open(str.GetBuffer(0),CFile::modeWrite|CFile::modeCreate);
	
	for(i=1; i<=m_iTraNo; i++)
	{
		_gcvt(m_iCluster[i][1], 10, cha10);
		for(k=0; k<10; k++)
		{
			if(cha10[k]==46)
			{
				cha10[k] = 13;
				cha10[k+1] = 10;
				end = k+2;
				k = 10;
			}
		}
		crfile2.Write(&cha10, end);
		for(k=0; k<10; k++)
			cha10[k]=0;
	}

	//save orientation
	//CFileDialog fSaveDlg(FALSE,NULL,NULL);
	//fSaveDlg.m_ofn.lpstrTitle = _T("Save orientation");
	CFile crfile3;
	crfile3.Abort();
	//fSaveDlg.DoModal();
	str = m_strPath;
	str.Insert(m_strPath.GetLength(), _T(".ori"));
	crfile3.Open(str.GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	char cha16[16];
	end=16;

	for(i=1; i<=m_iTraNo; i++)
	{
		sprintf(cha16, "%.5f\n", m_fNorm[i][0]);
		end=16;
		for(a=1;a<16;a++)
		{	
			if(cha16[a] == 10)
			{
				cha16[a] = 13;
				cha16[a+1] = 10;
				end=a+2;
				a=16;
			}
		}
		crfile3.Write(cha16, end);
		for(a=0; a<16; a++)
			cha16[a] = 0;
	}
	for(i=1; i<=m_iTraNo; i++)
	{
		sprintf(cha16, "%.5f\n", m_fNorm[i][1]);
		end=16;
		for(a=1;a<16;a++)
		{	
			if(cha16[a] == 10)
			{
				cha16[a] = 13;
				cha16[a+1] = 10;
				end=a+2;
				a=16;
			}
		}
		crfile3.Write(cha16, end);
		for(a=0; a<16; a++)
			cha16[a] = 0;
	}
	for(i=1; i<=m_iTraNo; i++)
	{
		sprintf(cha16, "%.5f\n", m_fNorm[i][2]);
		end=16;
		for(a=1;a<16;a++)
		{	
			if(cha16[a] == 10)
			{
				cha16[a] = 13;
				cha16[a+1] = 10;
				end=a+2;
				a=16;
			}
		}
		crfile3.Write(cha16, end);
		for(a=0; a<16; a++)
			cha16[a] = 0;
	}
	
	//save tra thickness
	//CFileDialog fSaveDlg3(FALSE,NULL,NULL);
	//fSaveDlg.m_ofn.lpstrTitle = _T("Save thicness");
	CFile crfile4;
	crfile4.Abort();
//	fSaveDlg3.DoModal();
	str = m_strPath;
	str.Insert(m_strPath.GetLength(), _T(".th"));
	crfile4.Open(str.GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	for(i=1; i<=m_iTraNo; i++)
	{
		sprintf(cha16, "%.5f\n", m_fTh[i][0]);
		end=16;
		for(a=1;a<16;a++)
		{	
			if(cha16[a] == 10)
			{
				cha16[a] = 13;
				cha16[a+1] = 10;
				end=a+2;
				a=16;
			}
		}
		crfile4.Write(cha16, end);
		for(a=0; a<16; a++)
			cha16[a] = 0;
	}

	for(i=0; i<27; i++)
	{
		free(pro[i]);
	}

	free(pro);

	for(i=0; i<=m_iTraNo; i++)
	{
		free(co[i]);
	}
	free(co);

	for(i=0; i<4; i++)
	{
		free(A[i]);
	}
	free(A);

	free(Diagonal);
	free(SubDiagonal);
}

float CFormCommandView::GetTh(int ***matrix, int ***type, float **norm, int i, int j, int k, int tra, float **th)
{
	float f = 0.1;
	float x1,y1,z1,x2,y2,z2;
	
	x1 = (float)i;
	y1 = (float)j;
	z1 = (float)k;

	while(type[(int)(x1+0.5)][(int)(y1+0.5)][(int)(z1+0.5)] != -MAXNUM && (x1+0.5) >= 2 && (x1-0.5) <= m_iSize[0]+1 && (y1+0.5) >= 2 && (y1-0.5) <= m_iSize[1]+1 && (z1+0.5) >= 2 && (z1-0.5) <= m_iSize[2]+1)
	{
		x1 += f*norm[tra][0];
		y1 += f*norm[tra][1];
		z1 += f*norm[tra][2];
	}

	while(type[(int)(x1+0.5)][(int)(y1+0.5)][(int)(z1+0.5)] == -MAXNUM && (x1+0.5) >= 2 && (x1-0.5) <= m_iSize[0]+1 && (y1+0.5) >= 2 && (y1-0.5) <= m_iSize[1]+1 && (z1+0.5) >= 2 && (z1-0.5) <= m_iSize[2]+1)
	{
		x1 -= 0.1*f*norm[tra][0];
		y1 -= 0.1*f*norm[tra][1];
		z1 -= 0.1*f*norm[tra][2];
	}

	x2 = (float)i;
	y2 = (float)j; 
	z2 = (float)k;

	while(type[(int)(x2+0.5)][(int)(y2+0.5)][(int)(z2+0.5)] != -MAXNUM && (x2+0.5) >= 2 && (x2-0.5) <= m_iSize[0]+1 && (y2+0.5) >= 2 && (y2-0.5) <= m_iSize[1]+1 && (z2+0.5) >= 2 && (z2-0.5) <= m_iSize[2]+1)
	{
		x2 -= f*norm[tra][0];
		y2 -= f*norm[tra][1];
		z2 -= f*norm[tra][2];
	}

	while(type[(int)(x2+0.5)][(int)(y2+0.5)][(int)(z2+0.5)] == -MAXNUM && (x2+0.5) >= 2 && (x2-0.5) <= m_iSize[0]+1 && (y2+0.5) >= 2 && (y2-0.5) <= m_iSize[1]+1 && (z2+0.5) >= 2 && (z2-0.5) <= m_iSize[2]+1)
	{
		x2 += 0.1*f*norm[tra][0];
		y2 += 0.1*f*norm[tra][1];
		z2 += 0.1*f*norm[tra][2];
	}

	th[tra][0] += sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));

	return th[tra][0];
}

int CFormCommandView::GetNorm(float **A, float **norm, int tra)
{
	int i,j,k, ipvt_temp;
	float pvt;
	int pivot[3];
	float temp[5];
	int n=3;

	for(j=1; j<=n-1; j++)
	{
		pvt = fabs(A[j][j]);
		pivot[j] = j;
		ipvt_temp = j;

		for(i=j+1; i<=n; i++)
		{
			if(fabs(A[i][j]) > pvt)
			{
				pvt = fabs(A[i][j]);
				ipvt_temp = i;
			}
		}

		if(pivot[j] != ipvt_temp)
		{
			for(k=1; k<=4; k++)
			{
				temp[k] = A[pivot[j]][k];
				A[pivot[j]][k] = A[ipvt_temp][k];
				A[ipvt_temp][k] = temp[k];
			}
		}

		for(i=j+1; i<=n; i++)
		{
			A[i][j] = A[i][j]/A[j][j];
		}

		for(i=j+1; i<=n; i++)
		{
			for(k=j+1; k<=n+1; k++)
			{
				A[i][k] = A[i][k] - A[i][j]*A[j][k];
			}
		}
	}
	
	//note: m_fNorm[tra][] is from 0 to n-1
	if(A[n][n] == 0)
		return 0;
	m_fNorm[tra][n-1] = A[n][n+1]/A[n][n];
	for(j=n-1; j>=1; j--)
	{
		m_fNorm[tra][j-1] = A[j][n+1];
		for(k=n; k>=j+1; k--)
		{
			m_fNorm[tra][j-1] = m_fNorm[tra][j-1] - m_fNorm[tra][k-1]*A[j][k];
		}
		m_fNorm[tra][j-1] = m_fNorm[tra][j-1]/A[j][j];
	}
	
/*	m_fNorm[tra][2] = m_fNorm[tra][1];
	m_fNorm[tra][1] = m_fNorm[tra][0];
	m_fNorm[tra][0] = -1;

	m_fNorm[tra][2] = m_fNorm[tra][1];
	m_fNorm[tra][1] = -1;

	float total = sqrt(m_fNorm[tra][0]*m_fNorm[tra][0] + m_fNorm[tra][1]*m_fNorm[tra][1] + m_fNorm[tra][2]*m_fNorm[tra][2]);
	for(i=0; i<3; i++)
	{
		m_fNorm[tra][i] = m_fNorm[tra][i]/total;
	}*/
	
	if(m_fNorm[tra][0] == 0 && m_fNorm[tra][1] == 0 && m_fNorm[tra][2] == 0)
		return 0;
	else
		return 1;
}

int CFormCommandView::GetOri(float **A, float **norm, int tra)
{
	int i,j,k;
	int max_iter = 500;
	float errmax = 0.001;
	float u1=0;
	float u2=0;

	m_fNorm[tra][0] = 1;
	m_fNorm[tra][1] = 1;
	m_fNorm[tra][2] = 1;

	float err;
	float temp[4];
	
	for(i=1; i<=max_iter; i++)
	{
		for(j=1; j<=3; j++)
		{
			temp[j] = 0;
			for(k=1; k<=3; k++)
			{
				temp[j] += A[j][k]*m_fNorm[tra][k-1];
			}
		}

		u1=u2;
		u2=0;
		for(j=1; j<=3; j++)
		{
			if(fabs(temp[j]) > fabs(u2))
				u2 = temp[j];
		}

		for(j=1; j<=3; j++)
			m_fNorm[tra][j-1] = temp[j]/u2;

		err = fabs((u2-u1)/u2);

		if(err<errmax)
		{
			float total = sqrt(m_fNorm[tra][0]*m_fNorm[tra][0] + m_fNorm[tra][1]*m_fNorm[tra][1] + m_fNorm[tra][2]*m_fNorm[tra][2]);
			
			//prevent the denominator to be zero
			if(total == 0)
				total = 1;

			for(j=0; j<3; j++)
			{
				m_fNorm[tra][j] = m_fNorm[tra][j]/total;
			}
			return 1;
		}
	}
	
	float total = sqrt(m_fNorm[tra][0]*m_fNorm[tra][0] + m_fNorm[tra][1]*m_fNorm[tra][1] + m_fNorm[tra][2]*m_fNorm[tra][2]);
	if(total == 0)
		return 0;
	for(j=0; j<3; j++)
	{
		m_fNorm[tra][j] = m_fNorm[tra][j]/total;
	}
	return 1;
}

void CFormCommandView::OnRecoverPlate() 
{
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bClassified == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bDebugmode == TRUE)
	{
		MessageBox(_T(" Please quit debugging mode first! "));
		return;
	}



	int i,j,k,l,m,a;
/*	for(m=1; m<=m_iTraNo; m++)
	{
		//if(m_iCluster[m][1] == 2)
		//{
			for(k=((m_iDimension[m][2]-7) > 0 ? (m_iDimension[m][2]-7): 0); k<=((m_iDimension[m][5]+7) < (m_iSize[2]+3) ? (m_iDimension[m][5]+7): (m_iSize[2]+3)); k++)
			{
				for(j=((m_iDimension[m][1]-7) > 0 ? (m_iDimension[m][1]-7): 0); j<=((m_iDimension[m][4]+7) < (m_iSize[1]+3) ? (m_iDimension[m][4]+7): (m_iSize[1]+3)); j++)
				{
					for(i=((m_iDimension[m][0]-7) > 0 ? (m_iDimension[m][0]-7): 0); i<=((m_iDimension[m][3]+7) < (m_iSize[0]+3) ? (m_iDimension[m][3]+7): (m_iSize[0]+3)); i++)
					{					
						m_iPtType[i][j][k] = m_iMatrix[i][j][k]; 

						if(m_iMatrix[i][j][k] > 0 && m_iMatrix[i][j][k] == m)
						{
							m_iPtType[i][j][k] = 1;
						}
						else if(m_iMatrix[i][j][k] > 0 && m_iMatrix[i][j][k] > m)
						{
							m_iPtType[i][j][k] = 2;
						}
						else if(m_iMatrix[i][j][k] > 0 && m_iMatrix[i][j][k] < m)
						{
							m_iPtType[i][j][k] = -MAXNUM;
						}
					}
				}
			}

			for(l=m_iPlateThr-1; l>-MAXNUM; l--)
			{
				for(k=m_iDimension[m][2]; k<=m_iDimension[m][5]; k++)
				{
					for(j=m_iDimension[m][1]; j<=m_iDimension[m][4]; j++)
					{
						for(i=m_iDimension[m][0]; i<=m_iDimension[m][3]; i++)
						{
							if(m_iPtType[i][j][k] == l)
							{
								Recover(m_iTemp, m_iPtType, i, j, k, m_iSize);
							}
						}
					}
				}
			}

			for(k=((m_iDimension[m][2]-7) > 0 ? (m_iDimension[m][2]-7): 0); k<=((m_iDimension[m][5]+7) < (m_iSize[2]+3) ? (m_iDimension[m][5]+7): (m_iSize[2]+3)); k++)
			{
				for(j=((m_iDimension[m][1]-7) > 0 ? (m_iDimension[m][1]-7): 0); j<=((m_iDimension[m][4]+7) < (m_iSize[1]+3) ? (m_iDimension[m][4]+7): (m_iSize[1]+3)); j++)
				{
					for(i=((m_iDimension[m][0]-7) > 0 ? (m_iDimension[m][0]-7): 0); i<=((m_iDimension[m][3]+7) < (m_iSize[0]+3) ? (m_iDimension[m][3]+7): (m_iSize[0]+3)); i++)
					{					
						if(m_iPtType[i][j][k] >= 1 && m_iPtType[i][j][k] <= 1.5)
						{
							//temp = m_iMatrix[i][j][k];
							m_iMatrix[i][j][k] = m;
							//m_iPtType[i][j][k] = temp;
						}
						else
							m_iPtType[i][j][k] = m_iMatrix[i][j][k];
					}
				}
			}
		//}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] == -MAXNUM-1)
				{
					m_iPtType[i][j][k] = RecoverConnection(m_iMatrix, i, j, k);
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];
				}
			}
		}
	}

					
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					m_iCluster[m_iMatrix[i][j][k]][0]++;
					//m_fBVF++;
				}

			}
		}
	}
		
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 2)
		{
			m_fTh[i][0] = sqrtf(((float)m_iCluster[i][0])/((float)m_iCluster[i][2])/3.1415927);
		}
	}
*/
	
	//save orientation

	CFileDialog fSaveDlg(FALSE,NULL,NULL);
	fSaveDlg.m_ofn.lpstrTitle = _T("Save orientation");
	CFile crfile;
	crfile.Abort();
	fSaveDlg.DoModal();
	crfile.Open(fSaveDlg.GetPathName().GetBuffer(0),CFile::modeWrite|CFile::modeCreate);
	char cha3[16];
	int end=16;

	for(i=1; i<=m_iTraNo; i++)
	{
		sprintf(cha3, "%.5f\n", m_fNorm[i][0]);
		end=16;
		for(a=1;a<16;a++)
		{	
			if(cha3[a] == 10)
			{
				cha3[a] = 13;
				cha3[a+1] = 10;
				end=a+2;
				a=16;
			}
		}
		crfile.Write(cha3, end);
		for(a=0; a<16; a++)
			cha3[a] = 0;
	}
	for(i=1; i<=m_iTraNo; i++)
	{
		sprintf(cha3, "%.5f\n", m_fNorm[i][1]);
		end=16;
		for(a=1;a<16;a++)
		{	
			if(cha3[a] == 10)
			{
				cha3[a] = 13;
				cha3[a+1] = 10;
				end=a+2;
				a=16;
			}
		}
		crfile.Write(cha3, end);
		for(a=0; a<16; a++)
			cha3[a] = 0;
	}	for(i=1; i<=m_iTraNo; i++)
	{
		sprintf(cha3, "%.5f\n", m_fNorm[i][2]);
		end=16;
		for(a=1;a<16;a++)
		{	
			if(cha3[a] == 10)
			{
				cha3[a] = 13;
				cha3[a+1] = 10;
				end=a+2;
				a=16;
			}
		}
		crfile.Write(cha3, end);
		for(a=0; a<16; a++)
			cha3[a] = 0;
	}
	//save tra thickness
	CFileDialog fSaveDlg3(FALSE,NULL,NULL);
	fSaveDlg.m_ofn.lpstrTitle = _T("Save thicness");
	CFile crfile3;
	crfile3.Abort();
	fSaveDlg3.DoModal();
	crfile3.Open(fSaveDlg3.GetPathName().GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	for(i=1; i<=m_iTraNo; i++)
	{
		sprintf(cha3, "%.5f\n", m_fTh[i][0]);
		end=16;
		for(a=1;a<16;a++)
		{	
			if(cha3[a] == 10)
			{
				cha3[a] = 13;
				cha3[a+1] = 10;
				end=a+2;
				a=16;
			}
		}
		crfile3.Write(cha3, end);
		for(a=0; a<16; a++)
			cha3[a] = 0;
	}

	m_strDisp.Format(_T("Finish Recover!"));
	UpdateData( FALSE );


	//m_fBVF /= (m_iSize[0]*m_iSize[1]*m_iSize[2]);
	

//old
/*
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bClassified == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bDebugmode == TRUE)
	{
		MessageBox(_T(" Please quit debugging mode first! "));
		return;
	}

	if(m_bRecovered == TRUE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	m_bRecovered = TRUE;

	int i,j,k,l;
	int iPlate = 0;
	int iRod = 0;
	int iTotal = 0;

	m_strDisp.Format("Begin Recover!");
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] ==1 ||m_iPtType[i][j][k] ==2 ||m_iPtType[i][j][k] ==3)
				{
					m_iPtType[i][j][k] = 1;
				}
				else if(m_iPtType[i][j][k] ==5 ||m_iPtType[i][j][k] ==6 ||m_iPtType[i][j][k] ==7)
				{
					m_iPtType[i][j][k] = 2;
				}
				else if(m_iPtType[i][j][k] ==4)
				{
					m_iPtType[i][j][k] = 1.5;
				}
				else if(m_iPtType[i][j][k] ==8)
				{
					m_iPtType[i][j][k] = -MAXNUM;
				}

			}
		}
	}

	for(l=m_iThr+1; l>-MAXNUM; l--)
	{
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2;i<m_iSize[0]+2; i++)
				{
					if(m_iPtType[i][j][k] == l)
					{
						Recover(m_iTemp, m_iPtType, i, j, k);
					}
					
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] > 1.5 && m_iPtType[i][j][k] <= 2.0 && m_iMatrix[i][j][k] < 1)
				{
					m_iPtType[i][j][k] = 0;
				}

				m_iMatrix[i][j][k] = 0;
				if(m_iPtType[i][j][k] <= 2 && m_iPtType[i][j][k] >=1)
				{
					m_iMatrix[i][j][k] = 1;
					if(m_iPtType[i][j][k] < 1.5)
					{
						iPlate++;
					}
					else
					{
						iRod++;
					}
				}
				
			}
		}
	}

	iTotal = iPlate + iRod;

	m_strDisp.Format("Finish Plate Recover!");
	m_strDebug.Format("Total Voxels: %d \nplate: %d \nRod: %d", iTotal, iPlate, iRod);
	UpdateData( FALSE );*/
}

void CFormCommandView::OnRecoverRod() 
{
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bClassified == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bDebugmode == TRUE)
	{
		MessageBox(_T(" Please quit debugging mode first! "));
		return;
	}

	m_bRecovered = TRUE;

	int i,j,k,l,m;
	int a,b,c;
//	int temp;
	int iPlate = 0;
	int iRod = 0;
	int iTotal = 0;
	m_strDisp.Format(_T("Begin Recover!"));
	UpdateData( FALSE );

/*	int **pro;
	pro = (int **)calloc(27, sizeof(int*));
	
	for(i=0; i<27; i++)
	{
		pro[i] = (int *)calloc(2, sizeof(int));
	}
	
	for(i=0; i<27; i++)
	{
		for(j=0; j<2; j++)
		{
			pro[i][j] = 0;
		}
	}
*/
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{					
				if(m_iMatrix[i][j][k] <= 0)
					m_iMatrix[i][j][k] = m_iPtType[i][j][k];
			}
		}
	}

	/*for(i=1; i<=m_iTraNo; i++)
	{
		for(j=0; j<3; j++)
		{
			m_iDimension[i][j] -= MAXNUM + m_iThr +1;
			if(m_iDimension[i][j]< 2)
				m_iDimension[i][j] = 2;
			m_iDimension[i][j+3] += MAXNUM + m_iThr +1;
			if(m_iDimension[i][j+3] > m_iSize[j]+1)
				m_iDimension[i][j+3] = m_iSize[j]+1;
		}
	}*/

	int iTra;
	for(l=m_iThr+1; l>-MAXNUM; l--)//m_iPlateThr; l--)
	{
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iPtType[i][j][k]==l)
					{
						iTra = PrimaryRecover(m_iPtType, m_iMatrix, i, j, k, l);
						if(iTra > 0)
							m_iMatrix[i][j][k] = iTra;
					}
				}
			}
		}
	}
						



/*	for(m=1; m<=m_iTraNo; m++)//m_iTraNo; m++)
	{
		for(k=((m_iDimension[m][2]-7) > 0 ? (m_iDimension[m][2]-7): 0); k<=((m_iDimension[m][5]+7) < (m_iSize[2]+3) ? (m_iDimension[m][5]+7): (m_iSize[2]+3)); k++)
		{
			for(j=((m_iDimension[m][1]-7) > 0 ? (m_iDimension[m][1]-7): 0); j<=((m_iDimension[m][4]+7) < (m_iSize[1]+3) ? (m_iDimension[m][4]+7): (m_iSize[1]+3)); j++)
			{
				for(i=((m_iDimension[m][0]-7) > 0 ? (m_iDimension[m][0]-7): 0); i<=((m_iDimension[m][3]+7) < (m_iSize[0]+3) ? (m_iDimension[m][3]+7): (m_iSize[0]+3)); i++)
				{					
					m_iPtType[i][j][k] = m_iMatrix[i][j][k]; 
					
					if(m_iMatrix[i][j][k] > 0 && m_iMatrix[i][j][k] == m)
					{
						m_iPtType[i][j][k] = 1;
					}
					else if(m_iMatrix[i][j][k] > 0 && m_iMatrix[i][j][k] > m)
					{
						m_iPtType[i][j][k] = 2;
					}
					else if(m_iMatrix[i][j][k] > 0 && m_iMatrix[i][j][k] < m)
					{
						m_iPtType[i][j][k] = -MAXNUM;
					}
				}
			}
		}

		for(l=m_iThr+1; l>=m_iPlateThr; l--)
		{
			for(k=m_iDimension[m][2]; k<=m_iDimension[m][5]; k++)
			{
				for(j=m_iDimension[m][1]; j<=m_iDimension[m][4]; j++)
				{
					for(i=m_iDimension[m][0]; i<=m_iDimension[m][3]; i++)
					{
						if(m_iPtType[i][j][k] == l)
						{
							Recover(m_iTemp, m_iPtType, i, j, k, m_iSize);
						}
					}
				}
			}
		}

		for(k=((m_iDimension[m][2]-7) > 0 ? (m_iDimension[m][2]-7): 0); k<=((m_iDimension[m][5]+7) < (m_iSize[2]+3) ? (m_iDimension[m][5]+7): (m_iSize[2]+3)); k++)
		{
			for(j=((m_iDimension[m][1]-7) > 0 ? (m_iDimension[m][1]-7): 0); j<=((m_iDimension[m][4]+7) < (m_iSize[1]+3) ? (m_iDimension[m][4]+7): (m_iSize[1]+3)); j++)
			{
				for(i=((m_iDimension[m][0]-7) > 0 ? (m_iDimension[m][0]-7): 0); i<=((m_iDimension[m][3]+7) < (m_iSize[0]+3) ? (m_iDimension[m][3]+7): (m_iSize[0]+3)); i++)
				{					
					if(m_iPtType[i][j][k] >= 1 && m_iPtType[i][j][k] <= 1.5)
					{
						//temp = m_iMatrix[i][j][k];
						m_iMatrix[i][j][k] = m;
						//m_iPtType[i][j][k] = temp;
					}
					else
						m_iPtType[i][j][k] = m_iMatrix[i][j][k];
				}
			}
		}
	}
*/
/*	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{	
				if(m_iPtType[i][j][k]>=m_iPlateThr && m_iPtType[i][j][k]<0)
					m_iPtType[i][j][k]=m_iPtType[i][j][k];
			}
		}
	}*/
	for(i=1; i<=m_iTraNo; i++)
	{
		m_iCluster[i][2] = 0;
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					m_iCluster[m_iMatrix[i][j][k]][2]++;
				}
			}
		}
	}

	//co:[0]x^2 [1]y^2 [2]z^2 [3]x*y [4]y*z [5]x*z [6]x [7]y [8]z
/*	float **co;
	co = (float **)calloc(m_iTraNo+1, sizeof(float*));
	
	for(i=0; i<=m_iTraNo; i++)
	{
		co[i] = (float *)calloc(9, sizeof(float));
	}
	
	for(i=0; i<=m_iTraNo; i++)
	{
		for(j=0; j<9; j++)
		{
			co[i][j] = 0;
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		m_iCluster[i][0] = 0;
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]> 0)
				{
					co[m_iMatrix[i][j][k]][6] += i;
					co[m_iMatrix[i][j][k]][7] += j;
					co[m_iMatrix[i][j][k]][8] += k;
					m_iCluster[m_iMatrix[i][j][k]][0]++;
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 2)
		{
			co[i][6] = co[i][6]/(float)m_iCluster[i][0];
			co[i][7] = co[i][7]/(float)m_iCluster[i][0];
			co[i][8] = co[i][8]/(float)m_iCluster[i][0];
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && m_iCluster[m_iMatrix[i][j][k]][1] == 2)
				{
					co[m_iMatrix[i][j][k]][0] += (i-co[m_iMatrix[i][j][k]][6])*(i-co[m_iMatrix[i][j][k]][6]);
					co[m_iMatrix[i][j][k]][1] += (j-co[m_iMatrix[i][j][k]][7])*(j-co[m_iMatrix[i][j][k]][7]);
					co[m_iMatrix[i][j][k]][2] += (k-co[m_iMatrix[i][j][k]][8])*(k-co[m_iMatrix[i][j][k]][8]);
					co[m_iMatrix[i][j][k]][3] += (i-co[m_iMatrix[i][j][k]][6])*(j-co[m_iMatrix[i][j][k]][7]);
					co[m_iMatrix[i][j][k]][4] += (j-co[m_iMatrix[i][j][k]][7])*(k-co[m_iMatrix[i][j][k]][8]);
					co[m_iMatrix[i][j][k]][5] += (k-co[m_iMatrix[i][j][k]][8])*(i-co[m_iMatrix[i][j][k]][6]);
				}
				else if(m_iMatrix[i][j][k] > 0 && m_iCluster[m_iMatrix[i][j][k]][1] == 1)
				{
					co[m_iMatrix[i][j][k]][0] += i*i;
					co[m_iMatrix[i][j][k]][1] += j*j;
					co[m_iMatrix[i][j][k]][2] += k*k;
					co[m_iMatrix[i][j][k]][3] += i*j;
					co[m_iMatrix[i][j][k]][4] += j*k;
					co[m_iMatrix[i][j][k]][5] += k*i;
				}
			}
		}
	}

	float **A;
	A = (float **)calloc(4, sizeof(float*));
	
	for(i=0; i<4; i++)
	{
		A[i] = (float *)calloc(5, sizeof(float));
	}
	
	for(i=0; i<4; i++)
	{
		for(j=0; j<5; j++)
		{
			A[i][j] = 0;
		}
	}//only use A[1-3][1-4]
	
	m_fNorm = (float **)calloc(m_iTraNo+1, sizeof(float*));
	for(i=0; i<=m_iTraNo; i++)
	{
		m_fNorm[i] = (float *)calloc(6, sizeof(float));
	}

	m_fTh = (float **)calloc(m_iTraNo+1, sizeof(float*));
	for(i=0; i<=m_iTraNo; i++)
	{
		m_fTh[i] = (float *)calloc(2, sizeof(float));
	}

	for(i=0; i<=m_iTraNo; i++)
	{
		m_fTh[i][0] = 0;
		m_fTh[i][1] = 0;
		for(j=0; j<6; j++)
		{
			m_fNorm[i][j] = 0;
		}
	}

	float total;

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1)
		{
			/*A[1][1] = co[i][0];
			A[1][2] = co[i][3];
			A[1][3] = co[i][5];
			A[2][1] = co[i][3];
			A[2][2] = co[i][1];
			A[2][3] = co[i][4];
			A[3][1] = co[i][5];
			A[3][2] = co[i][4];
			A[3][3] = co[i][2];
			A[1][4] = -co[i][6];
			A[2][4] = -co[i][7];
			A[3][4] = -co[i][8];*/  //7-5-2005 notebook

			//least square: residual in y-axis
/*			A[1][1] = co[i][0];
			A[1][2] = co[i][5];
			A[1][3] = co[i][6];
			A[2][1] = co[i][5];
			A[2][2] = co[i][2];
			A[2][3] = co[i][8];
			A[3][1] = co[i][6];
			A[3][2] = co[i][8];
			A[3][3] = (float)m_iCluster[i][0];
			A[1][4] = co[i][3];
			A[2][4] = co[i][4];
			A[3][4] = co[i][7];
			GetNorm(A, m_fNorm, i);
			m_fNorm[i][2] = m_fNorm[i][1];
			m_fNorm[i][1] = -1;

			total = sqrt(m_fNorm[i][0]*m_fNorm[i][0] + m_fNorm[i][1]*m_fNorm[i][1] + m_fNorm[i][2]*m_fNorm[i][2]);
			
			for(j=0; j<3; j++)
			{
				m_fNorm[i][j+3] = m_fNorm[i][j]/total;
			}

			//least square: residual in x-axis
			A[1][1] = co[i][1];
			A[1][2] = co[i][4];
			A[1][3] = co[i][7];
			A[2][1] = co[i][4];
			A[2][2] = co[i][2];
			A[2][3] = co[i][8];
			A[3][1] = co[i][7];
			A[3][2] = co[i][8];
			A[3][3] = (float)m_iCluster[i][0];
			A[1][4] = co[i][3];
			A[2][4] = co[i][5];
			A[3][4] = co[i][6];
			GetNorm(A, m_fNorm, i);
			m_fNorm[i][2] = m_fNorm[i][1];
			m_fNorm[i][1] = m_fNorm[i][0];
			m_fNorm[i][0] = -1;
			
			total = sqrt(m_fNorm[i][0]*m_fNorm[i][0] + m_fNorm[i][1]*m_fNorm[i][1] + m_fNorm[i][2]*m_fNorm[i][2]);
			
			for(j=0; j<3; j++)
			{
				m_fNorm[i][j] = m_fNorm[i][j]/total;
			}
		}
		else
		{
			A[1][1] = co[i][0];
			A[1][2] = co[i][3];
			A[1][3] = co[i][5];
			A[2][1] = co[i][3];
			A[2][2] = co[i][1];
			A[2][3] = co[i][4];
			A[3][1] = co[i][5];
			A[3][2] = co[i][4];
			A[3][3] = co[i][2];

			GetOri(A, m_fNorm, i);
		}
	}

	//get thickness from the normal(x-axis)
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && m_iCluster[m_iMatrix[i][j][k]][1] == 1)
				{
					GetTh(m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1)
			m_fTh[i][0] = m_fTh[i][0]/((float)m_iCluster[i][0]);
	}

	float tempnorm[3];
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1)
		{
			for(j=0; j<3; j++)
			{
				tempnorm[j] = m_fNorm[i][j+3];
				m_fNorm[i][j+3] = m_fNorm[i][j];
				m_fNorm[i][j] = tempnorm[j];
			}
			m_fTh[i][1] = m_fTh[i][0];
			m_fTh[i][0] = 0;
		}
	}

	//get thickness from the normal(y-axis)
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && m_iCluster[m_iMatrix[i][j][k]][1] == 1)
				{
					GetTh(m_iPtType, m_fNorm, i, j, k, m_iMatrix[i][j][k], m_fTh);
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1)
			m_fTh[i][0] = m_fTh[i][0]/((float)m_iCluster[i][0]);
	}

	float tempth;
	//Compare two thickness, choose the smaller one and the corresponding normal
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1)
		{
			if(m_fTh[i][1]<=m_fTh[i][0])
			{
				tempth = m_fTh[i][0];
				m_fTh[i][0] = m_fTh[i][1];
				m_fTh[i][1] = tempth;
				for(j=0; j<3; j++)
				{
					tempnorm[j] = m_fNorm[i][j+3];
					m_fNorm[i][j+3] = m_fNorm[i][j];
					m_fNorm[i][j] = tempnorm[j];
				}
			}
		}
	}

	for(i=0; i<27; i++)
	{
		free(pro[i]);
	}

	free(pro);

	for(i=0; i<=m_iTraNo; i++)
	{
		free(co[i]);
	}
	free(co);

	for(i=0; i<4; i++)
	{
		free(A[i]);
	}
	free(A);
/*
	// TODO: Add your control notification handler code here
	if(m_bLoad == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bClassified == FALSE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	if(m_bDebugmode == TRUE)
	{
		MessageBox(_T(" Please quit debugging mode first! "));
		return;
	}

	if(m_bRecovered == TRUE)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}

	m_bRecovered = TRUE;

	int i,j,k,l;
	int iPlate = 0;
	int iRod = 0;
	int iTotal = 0;

	m_strDisp.Format("Begin Recover!");
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] ==1 ||m_iPtType[i][j][k] ==2 ||m_iPtType[i][j][k] ==3)
				{
					m_iPtType[i][j][k] = 1;
				}
				else if(m_iPtType[i][j][k] ==5 ||m_iPtType[i][j][k] ==6 ||m_iPtType[i][j][k] ==7)
				{
					m_iPtType[i][j][k] = 2;
				}
				else if(m_iPtType[i][j][k] ==4)
				{
					m_iPtType[i][j][k] = 1.5;
				}
				else if(m_iPtType[i][j][k] ==8)
				{
					m_iPtType[i][j][k] = -MAXNUM;
				}

			}
		}
	}

	for(l=m_iThr+1; l>-MAXNUM; l--)
	{
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2;i<m_iSize[0]+2; i++)
				{
					if(m_iPtType[i][j][k] == l)
					{
						Recover(m_iTemp, m_iPtType, i, j, k);
					}
					
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] >= 1 && m_iPtType[i][j][k] < 1.5 && m_iMatrix[i][j][k] < 1)
				{
					m_iPtType[i][j][k] = 0;
				}

				m_iMatrix[i][j][k] = 0;
				if(m_iPtType[i][j][k] <= 2 && m_iPtType[i][j][k] >=1)
				{
					m_iMatrix[i][j][k] = 1;
					if(m_iPtType[i][j][k] < 1.5)
					{
						iPlate++;
					}
					else
					{
						iRod++;
					}
				}
			}
		}
	}
	iTotal = iPlate + iRod;

	m_strDisp.Format("Finish Rod Recover!");
	m_strDebug.Format("Total Voxels: %d \nplate: %d \nRod: %d", iTotal, iPlate, iRod);
	UpdateData( FALSE );*/

}


void CFormCommandView::OnPlatecluster() 
{
	// TODO: Add your control notification handler code here
	m_strDisp.Format(_T("Begin Plate Clustering!"));
	UpdateData( FALSE );

	m_bRecovered = TRUE;
	m_bPClustered = TRUE;
	int i, j, k;
	int a, b, c;
	int temp1;
	//int temp2;

	int iSCNo = 0;
	int iCCNo = 0;
	int iSSNo = 0;
	int iNodeNo = 0;
	int iClusterNo = 0;
	int iChange = 0;

	int iNeighbor[26];
	int temp[26];
	int iNeighborNo;

	//the threshold to combine small pieces
/*	int SSlength = 0;
	int SClength = 0;
	int CClength = 0;

	if(m_bBklLoad == TRUE)
	{
		SSlength = 2;
		SClength = 2;
		CClength = 2;
	}
	else 
	{
		SSlength = 4;
		SClength = 4;
		CClength = 4;
	}*/
	for(i=0; i<26; i++)
		iNeighbor[i] = 0;
	
	m_iSCSize = 0;
	m_iCCSize = 0;
	m_iSSSize = 0;

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{				
				if(m_iMatrix[i][j][k] > 0)
				{
					m_iPtType[i][j][k] = m_iMatrix[i][j][k];
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{				
				if(m_iMatrix[i][j][k] > 0)
				{
					m_iPtType[i][j][k] = m_iMatrix[i][j][k];

					if(m_iPtType[i][j][k] == 4) 
					{
						/*for(a=0; a<3; a++)
						{
							for(b=0; b<3; b++)
							{
								for(c=0; c<3; c++)
								{
									if(!(a==1 && b==1 && c==1) && (m_iPtType[i-1+a][j-1+b][k-1+c] == 4))
									{
										m_iMatrix[i-1+a][j-1+b][k-1+c] = 2;
										m_iPtType[i-1+a][j-1+b][k-1+c] = 2;
									}
								}
							}
						}*/
						m_iSCSize++;
					}
					else if(m_iPtType[i][j][k] == 7)
					{
						m_iCCSize++;
					}
					else if(m_iPtType[i][j][k] == 3)
					{
						m_iSSSize++;
					}
				}
			}
		}
	}

	m_iNodelistSize = m_iCCSize + m_iSCSize + m_iSSSize;

	m_iNodelist = (int **)calloc(m_iNodelistSize, sizeof(int*));

	for(i=0; i<m_iNodelistSize; i++)
	{
		m_iNodelist[i] = (int *)calloc(3, sizeof(int));
	}

	//save all the labels of curve-curve junction and curve-surface junction
	for(i=2; i<m_iSize[0]+2; i++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(k=2; k<m_iSize[2]+2; k++)
			{
				if(m_iPtType[i][j][k] == 7)
				{
					m_iNodelist[iCCNo][0] = i;
					m_iNodelist[iCCNo][1] = j;
					m_iNodelist[iCCNo][2] = k;
					iCCNo++;
				}
				else if(m_iPtType[i][j][k] == 4)
				{
					m_iNodelist[m_iCCSize+iSCNo][0] = i;
					m_iNodelist[m_iCCSize+iSCNo][1] = j;
					m_iNodelist[m_iCCSize+iSCNo][2] = k;
					iSCNo++;
				}
				else if(m_iPtType[i][j][k] == 3)
				{
					m_iNodelist[m_iCCSize+m_iSCSize+iSSNo][0] = i;
					m_iNodelist[m_iCCSize+m_iSCSize+iSSNo][1] = j;
					m_iNodelist[m_iCCSize+m_iSCSize+iSSNo][2] = k;
					iSSNo++;
				}
			}
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] == 4 || m_iMatrix[i][j][k] == 7 || m_iMatrix[i][j][k] == 3)
				{
					m_iMatrix[i][j][k] = 0;
				}
			}
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
				{
					m_iMatrix[i][j][k] = 0;
					m_iPtType[i][j][k] = 0;
				}
			}
		}
	}


	//clustering the surface points(without SC,CC,SS points)
	m_iClusterNo = HKcluster4S(m_iMatrix, m_iSize);

	m_iCluster = (int **)calloc((m_iClusterNo+1), sizeof(int*));

	m_iTraNo = m_iClusterNo;
	for(i=0; i<=m_iClusterNo; i++)
	{
		m_iCluster[i] = (int *)calloc(3, sizeof(int));
	}

	for(i=0; i<=m_iClusterNo; i++)
	{
		for(j=0; j<3; j++)
		{
			m_iCluster[i][j] = 0;
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					m_iCluster[m_iMatrix[i][j][k]][0] ++;
					m_iCluster[m_iMatrix[i][j][k]][2] = m_iMatrix[i][j][k];
				
					if(m_iPtType[i][j][k] == 2 || m_iPtType[i][j][k] == 8)
						m_iCluster[m_iMatrix[i][j][k]][1] = 1;
					else if(m_iPtType[i][j][k] == 5 || m_iPtType[i][j][k] == 6)
						m_iCluster[m_iMatrix[i][j][k]][1] = 2;
				}
			}
		}
	}	

/*	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iCluster[m_iMatrix[i][j][k]][0]<=3 && m_iCluster[m_iMatrix[i][j][k]][1] == 1)
					{
						m_iPtType[i][j][k] = 3;
						m_iCrPnts[i][j][k] = 3;
						m_iMatrix[i][j][k] = 0;
					}
				}
			}
		}
	}*/

	int iJunc = 1;
/*	//detection for CC junction point
	while (iJunc)
	{
		iJunc = 0;
		for(i=0; i<m_iCCSize; i++)
		{
			if(m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] == 7)
			{
				iNeighborNo = 0;
				for(a=0; a<3; a++)
				{
					for(b=0; b<3; b++)
					{
						for(c=0; c<3; c++)
						{
							if(!(a==1 && b==1 && c==1) 
								&& (m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 5 ||
									m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 6	||
									m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 2 ||
									m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 8 ))
							{
								iNeighbor[iNeighborNo] = m_iMatrix[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1];
								iNeighborNo++;
							}
						}
					}
				}

			
				//iChange = iNeighborNo;
				temp[0] = m_iCluster[iNeighbor[0]][2];
				iChange = 1;
				for(j=1; j<iNeighborNo; j++)
				{
					for(k=0; k<iChange; k++)
					{
						if(m_iCluster[iNeighbor[j]][2] == temp[k])
						{
							k=iChange;
						}
					}
					if(k==iChange)
					{
						temp[iChange] = m_iCluster[iNeighbor[j]][2];
						iChange++;
					}
				}
				
				if(iNeighborNo != 0)
					iNeighborNo = iChange;

				while(iChange > 1)
				{
					for(j=1; j<iChange; j++)
					{
						if(m_iCluster[temp[j]][0] < m_iCluster[temp[j-1]][0])
						{
							k = temp[j-1];
							temp[j-1] = temp[j];
							temp[j] = k;
						}
					}
					iChange--;
				}


				iChange = 0;
				if(iNeighborNo == 0)
					iJunc = 1;
				else if(iNeighborNo == 1)
				{
					m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = m_iCluster[temp[0]][2];
					m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = 6;
					m_iCluster[temp[0]][0]++; 
					iChange = 1;
				}
				else
				{
					for(j=0; j<iNeighborNo-1; j++)
					{
						if(m_iCluster[temp[j]][0] <= CClength)
						{
							if(iChange == 0)
							{
								m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = m_iCluster[temp[j+1]][2];
								m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = 6;
								m_iCluster[temp[j+1]][0] += (1 + m_iCluster[temp[j]][0]);
							}
							else
								m_iCluster[temp[j+1]][0] += m_iCluster[temp[j]][0];

							m_iCluster[temp[j]][0] = m_iCluster[temp[j+1]][0];
							
							m_iCluster[temp[j]][2] = m_iCluster[temp[j+1]][2];
							iChange = 1;
						}
					}
				}

				if(iChange == 0)
				{
					m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = -MAXNUM-1;//m_iCluster[temp[0]][2];
					m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = -MAXNUM-1;//6;
				}
			}
		}
	}

	//detection for SC junction point
	for(i=m_iCCSize; i < m_iCCSize + m_iSCSize; i++)
	{
		iNeighborNo = 0;
		for(a=0; a<3; a++)
		{
			for(b=0; b<3; b++)
			{
				for(c=0; c<3; c++)
				{
					if(!(a==1 && b==1 && c==1) 
						&& (m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 8 ||
						    m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 2 ||
						    m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 5 ||
						    m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 6	))
					{
						iNeighbor[iNeighborNo] = m_iMatrix[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1];
						iNeighborNo++;
					}
				}
			}
		}

		//iChange = iNeighborNo;
		temp[0] = m_iCluster[iNeighbor[0]][2];
		iChange = 1;
		for(j=1; j<iNeighborNo; j++)
		{
			for(k=0; k<iChange; k++)
			{
				if(m_iCluster[iNeighbor[j]][2] == temp[k])
				{
					k=iChange;
				}
			}
			if(k==iChange)
			{
				temp[iChange] = m_iCluster[iNeighbor[j]][2];
				iChange++;
			}
		}

		if(iNeighborNo != 0)
			iNeighborNo = iChange;

		while(iChange > 1)
		{
			for(j=1; j<iChange; j++)
			{
				if(m_iCluster[temp[j]][0] < m_iCluster[temp[j-1]][0])
				{
					k = temp[j-1];
					temp[j-1] = temp[j];
					temp[j] = k;
				}
			}
			iChange--;
		}

		iChange = 0;

		if(iNeighborNo == 1)
		{
			m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = m_iCluster[temp[0]][2];
			if(m_iCluster[temp[0]][1] == 1)
				m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = 2;
			else
				m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = 6;
			m_iCluster[temp[0]][0]++; 
			iChange = 1;
		}

		for(j=0; j<iNeighborNo-1; j++)
		{
			if(m_iCluster[temp[j]][0] <= SClength)
			{
				if(iChange == 0)
				{
					m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = m_iCluster[temp[j+1]][2];
					if(m_iCluster[temp[j]][1] == 1)
						m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = 2;
					else
						m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = 6;
					m_iCluster[temp[j+1]][0] += (1 + m_iCluster[temp[j]][0]);
				}
				else
					m_iCluster[temp[j+1]][0] += m_iCluster[temp[j]][0];

				m_iCluster[temp[j]][0] = m_iCluster[temp[j+1]][0];
				
				m_iCluster[temp[j]][2] = m_iCluster[temp[j+1]][2];
				iChange = 1;
			}
		}
		if(iChange == 0)
		{
			m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = -MAXNUM-1;//m_iCluster[temp[0]][2];
			m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = -MAXNUM-1;//2;
		}
	}*/

	//detection for SSArc junction point
	iJunc = 1;
	int tempcount = 0;
	while(iJunc)
	{
		tempcount++;
		iJunc = 0;
		for(i=m_iCCSize + m_iSCSize ; i<m_iCCSize + m_iSCSize + m_iSSSize; i++)
		{
			if(m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] == 3)
			{
				iNeighborNo = 0;

				for(a=0; a<3; a++)
				{
					for(b=0; b<3; b++)
					{
						for(c=0; c<3; c++)
						{
							if(!(a==1 && b==1 && c==1) 
								&& (m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 8 ||
									m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 2 ||
									m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 5 ||
									m_iPtType[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1] == 6 ))
							{
								iNeighbor[iNeighborNo] = m_iMatrix[m_iNodelist[i][0]+a-1][m_iNodelist[i][1]+b-1][m_iNodelist[i][2]+c-1];
								iNeighborNo++;
							}
						}
					}
				}

				temp[0] = m_iCluster[iNeighbor[0]][2];
				iChange = 1;
				for(j=1; j<iNeighborNo; j++)
				{
					for(k=0; k<iChange; k++)
					{
						if(m_iCluster[iNeighbor[j]][2] == temp[k])
						{
							k=iChange;
						}
					}
					if(k==iChange)
					{
						temp[iChange] = m_iCluster[iNeighbor[j]][2];
						iChange++;
					}
				}
				
				if(iNeighborNo != 0)
					iNeighborNo = iChange;

				while(iChange > 1)
				{
					for(j=1; j<iChange; j++)
					{
						if(m_iCluster[temp[j]][0] < m_iCluster[temp[j-1]][0])
						{
							k = temp[j-1];
							temp[j-1] = temp[j];
							temp[j] = k;
						}
					}
					iChange--;
				}

				iChange = 0;
				if(iNeighborNo == 0 && tempcount <1000)
					iJunc = 1;
				else if(iNeighborNo == 0 && tempcount >=1000)
				{
					m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = -MAXNUM-1;
					m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = -MAXNUM-1;
				}
				else if(iNeighborNo == 1)
				{
					m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = m_iCluster[temp[0]][2];
					m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = 2;
					m_iCluster[temp[0]][0]++; 
					iChange = 1;
				}
				else
				{
					for(j=0; j<iNeighborNo-1; j++)
					{
						if(m_iCluster[m_iCluster[temp[j]][2]][0] <= SSlength)
						{
							if(iChange == 0)
							{
								m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = m_iCluster[temp[j+1]][2];
								m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = 2;
								m_iCluster[temp[j+1]][0] += (1 + m_iCluster[temp[j]][0]);
							}
							else
								m_iCluster[temp[j+1]][0] += m_iCluster[temp[j]][0];

							m_iCluster[temp[j]][2] = m_iCluster[temp[j+1]][2];
							m_iCluster[temp[j]][0] = m_iCluster[temp[j+1]][0];
							iChange = 1;
						}
					}
					if(iChange == 0)
					{
						m_iMatrix[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = -MAXNUM-1;//m_iCluster[temp[0]][2];
						m_iPtType[m_iNodelist[i][0]][m_iNodelist[i][1]][m_iNodelist[i][2]] = -MAXNUM-1;//2;
					}
				}
			}
		}
	}


	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					while(m_iMatrix[i][j][k] != m_iCluster[m_iMatrix[i][j][k]][2])
					{
						m_iMatrix[i][j][k] = m_iCluster[m_iMatrix[i][j][k]][2];
					}
				}
			}
		}
	}	

	
	//renumber the clusters by the voxel number

	//recount the voxel number for each label
	for(i=0; i <= m_iClusterNo; i++)
		m_iCluster[i][0] = 0;

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					m_iCluster[m_iMatrix[i][j][k]][0]++;
				}
			}
		}
	}
	
	//renumber the cluster number
	j=0;
	for(i=1; i<=m_iClusterNo; i++)
	{
		if(m_iCluster[i][0]>0)
		{
			j++;
		}
	}

	m_iTraNo = j;
	
	m_iConnection = (int **)calloc((m_iTraNo+1), sizeof(int*));

	for(i=0; i<=m_iTraNo; i++)
	{
		m_iConnection[i] = (int *)calloc(26, sizeof(int));
	}

	for(i=0; i<=m_iTraNo; i++)
	{
		for(j=0; j<26; j++)
		{
			m_iConnection[i][j] = 0;
		}
	}

	j=1;
	for(i=1; i<=m_iClusterNo; i++)
	{
		if(m_iCluster[i][0]>0)
		{
			m_iConnection[j][0] = i;
			j++;
		}
	}	
		
	iChange = m_iTraNo;
	while(iChange > 1)
	{
		for(j = 2; j <= iChange; j++)
		{
			if(m_iCluster[m_iConnection[j-1][0]][0] < m_iCluster[m_iConnection[j][0]][0])
			{
				k = m_iConnection[j][0];
				m_iConnection[j][0] = m_iConnection[j-1][0];
				m_iConnection[j-1][0] = k;
			}
		}
		iChange--;
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		for(j=0; j<=m_iClusterNo; j++)
		{
			if(m_iConnection[i][0] == j)
			{
				m_iCluster[j][2] = i;
				m_iConnection[i][1] = m_iCluster[j][0];
				m_iConnection[i][2] = m_iCluster[j][1];
			}
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					m_iMatrix[i][j][k] = m_iCluster[m_iMatrix[i][j][k]][2];
					m_iCluster[m_iMatrix[i][j][k]][0] = m_iConnection[m_iMatrix[i][j][k]][1];	//voxel number in cluster skeleton
					m_iCluster[m_iMatrix[i][j][k]][1] = m_iConnection[m_iMatrix[i][j][k]][2];	//rod or plate type
				}
			}
		}
	}

/*	m_iDimension = (int **)calloc((m_iTraNo+1), sizeof(int*));

	for(i=0; i<=m_iTraNo; i++)
	{
		m_iDimension[i] = (int *)calloc(6, sizeof(int));
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		m_iCluster[i][2] = m_iCluster[i][0];
		for(j=0; j<3; j++)
		{
			m_iDimension[i][j] = m_iSize[j]+1;
			m_iDimension[i][j+3] = 2;
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					SetDimension(i, j, k);
				}
			}
		}
	}*/


	m_strDisp.Format(_T("Finish Plate Clustering!"));
	m_strDebug.Format(_T("There are %d pieces in total "), m_iTraNo);
	UpdateData( FALSE );

}

/*void CFormCommandView::SetDimension(int i, int j, int k)
{
	if(i<m_iDimension[m_iMatrix[i][j][k]][0])
		m_iDimension[m_iMatrix[i][j][k]][0] = i;
	if(i>m_iDimension[m_iMatrix[i][j][k]][3])
		m_iDimension[m_iMatrix[i][j][k]][3] = i;
	if(j<m_iDimension[m_iMatrix[i][j][k]][1])
		m_iDimension[m_iMatrix[i][j][k]][1] = j;
	if(j>m_iDimension[m_iMatrix[i][j][k]][4])
		m_iDimension[m_iMatrix[i][j][k]][4] = j;
	if(k<m_iDimension[m_iMatrix[i][j][k]][2])
		m_iDimension[m_iMatrix[i][j][k]][2] = k;
	if(k>m_iDimension[m_iMatrix[i][j][k]][5])
		m_iDimension[m_iMatrix[i][j][k]][5] = k;

}*/

void CFormCommandView::FindConnection(int i, int j, int k, int a, int b, int c)
{
	int m;
	
	if(m_iConnection[m_iMatrix[i][j][k]][0] == 0)
		m_iConnection[m_iMatrix[i][j][k]][0] = m_iMatrix[a][b][c];
	else
	{
		for(m = 0; m < 26; m++)
		{
			if(m_iMatrix[a][b][c] == m_iConnection[m_iMatrix[i][j][k]][m])
				return;
		}

		for(m = 0; m < 26; m++)
		{
			if(m_iConnection[m_iMatrix[i][j][k]][m] == 0)
			{
				m_iConnection[m_iMatrix[i][j][k]][m] = m_iMatrix[a][b][c];
				m = 26;
			}
		}
	}
	
/*	for(m=0; m<3; m++)
	{
		for(n=0; n<3; n++)
		{
			for(l=0; l<3; l++)
			{
				if(!(m==1 && n==1 && l==1) && !(a-1+m == i && b-1+n == j && c-1+l == k) && (m_iMatrix[a-1+m][b-1+n][c-1+l] != m_iMatrix[a][b][c]) && (m_iMatrix[a-1+m][b-1+n][c-1+l] > 0))
				{
					for(p = 0; p < 26; p++)
					{
						if(m_iMatrix[a-1+m][b-1+n][c-1+l] == m_iConnection[m_iMatrix[i][j][k]][p])
						{
							p=26;
						}
						else if(m_iConnection[m_iMatrix[i][j][k]][p] == 0)
						{
							m_iConnection[m_iMatrix[i][j][k]][p] = m_iMatrix[a-1+m][b-1+n][c-1+l];
							p=26;
						}
					}
				}
			}
		}
	}*/

	return;
}

void CFormCommandView::Curvemesh() 
{

}

int CFormCommandView::NeighborC(int i, int j, int k)
{
	int a,b,c;
	int num = 0;
	for(a=-1; a<=1; a++)
	{
		for(b=-1; b<=1; b++)
		{
			for(c=-1; c<=1; c++)
			{
				if(!(a==0 && b==0 && c==0)) 
				{
					if(m_iMatrix[i+a][j+b][k+c]==4 || m_iMatrix[i+a][j+b][k+c]==5 || m_iMatrix[i+a][j+b][k+c]==6 || m_iMatrix[i+a][j+b][k+c]==7)
					{
						num++;
					}
				}
			}
		}
	}
	return num;
}

/*int CFormCommandView::LookforCC(int i, int a, int b, int c)
{
	int j;
	int cr = -1;
	for(j=i+1; j<m_iCCSize; j++)
	{
		if(m_iNodelist[j][0] == a && m_iNodelist[j][1] == b && m_iNodelist[j][2] == c)
		{
			cr = j;
			j = m_iCCSize;
		}
	}
	return cr;
}
		
int CFormCommandView::LookforSC(int i, int j, int k)
{
	int a;
	int cr = -1;
	for(a=m_iCCSize; a<m_iCCSize+m_iSCSize; a++)
	{
		if(m_iNodelist[a][0] == i && m_iNodelist[a][1] == j && m_iNodelist[a][2] == k)
		{
			cr = a;
			a = m_iCCSize + m_iSCSize;
		}
	}
	return cr;
}

int CFormCommandView::LookforCE(int i, int j, int k)
{
	int a;
	int cr = -1;
	for(a=m_iCCSize+m_iSCSize; a<m_iCCSize+m_iSCSize+m_iCESize; a++)
	{
		if(m_iNodelist[a][0] == i && m_iNodelist[a][1] == j && m_iNodelist[a][2] == k)
		{
			cr = a;
			a = m_iCCSize + m_iSCSize + m_iCESize;
		}
	}
	return cr;
}*/

void CFormCommandView::OnToolTrasep() 
{
	// TODO: Add your command handler code here
	m_bTrasep = TRUE;
	CTrabeculaeDialog Rdlg;
	Rdlg.DoModal();

	if(m_bLoad == TRUE)
	{
		CTestGLView* m_Temp;
		m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
		m_Temp->m_Clear = TRUE;
		m_Temp->Invalidate(TRUE);
	}


}

void CFormCommandView::OnUpdateToolTrasep(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bPClustered && m_bRecovered)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);	
	
}

void CFormCommandView::OnToolParameter() 
{
	// TODO: Add your command handler code here
	/*m_iTemp is for storing the 27 points type in classification*/
	int i,j,k;
	float **fTemp;
	fTemp = (float **)calloc(m_iTraNo, sizeof(float*));
	for(i=0; i<m_iTraNo; i++)
	{
		fTemp[i] = (float *)calloc(9, sizeof(float));
	}

	for(i=0; i<m_iTraNo; i++)
		for(j=0; j<9; j++)
			fTemp[i][j] = 0;

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					fTemp[m_iMatrix[i][j][k]-1][6] += i;
					fTemp[m_iMatrix[i][j][k]-1][7] += j;
					fTemp[m_iMatrix[i][j][k]-1][8] += k;

				}
			}
		}
	}

	for(i=0; i<m_iTraNo; i++)
	{
		fTemp[i][6] = fTemp[i][6]/m_iCluster[i+1][0];
		fTemp[i][7] = fTemp[i][7]/m_iCluster[i+1][0];
		fTemp[i][8] = fTemp[i][8]/m_iCluster[i+1][0];
	}

	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			for(k=0; k<m_iSize[2]+4; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{

				/*	fTemp[m_iMatrix[i][j][k]-1][0] += (i-fTemp[m_iMatrix[i][j][k]-1][6])*(i-fTemp[m_iMatrix[i][j][k]-1][6]);
					fTemp[m_iMatrix[i][j][k]-1][1] += (i-fTemp[m_iMatrix[i][j][k]-1][6])*(j-fTemp[m_iMatrix[i][j][k]-1][7]);
					fTemp[m_iMatrix[i][j][k]-1][2] += (i-fTemp[m_iMatrix[i][j][k]-1][6])*(k-fTemp[m_iMatrix[i][j][k]-1][8]);
					fTemp[m_iMatrix[i][j][k]-1][3] += (j-fTemp[m_iMatrix[i][j][k]-1][7])*(j-fTemp[m_iMatrix[i][j][k]-1][7]);
					fTemp[m_iMatrix[i][j][k]-1][4] += (j-fTemp[m_iMatrix[i][j][k]-1][7])*(k-fTemp[m_iMatrix[i][j][k]-1][8]);
					fTemp[m_iMatrix[i][j][k]-1][5] += (k-fTemp[m_iMatrix[i][j][k]-1][8])*(k-fTemp[m_iMatrix[i][j][k]-1][8]);
*/
					fTemp[m_iMatrix[i][j][k]-1][0] += ((j-fTemp[m_iMatrix[i][j][k]-1][7])*(j-fTemp[m_iMatrix[i][j][k]-1][7])+(k-fTemp[m_iMatrix[i][j][k]-1][8])*(k-fTemp[m_iMatrix[i][j][k]-1][8]));
					fTemp[m_iMatrix[i][j][k]-1][1] += -(i-fTemp[m_iMatrix[i][j][k]-1][6])*(j-fTemp[m_iMatrix[i][j][k]-1][7]);
					fTemp[m_iMatrix[i][j][k]-1][2] += -(i-fTemp[m_iMatrix[i][j][k]-1][6])*(k-fTemp[m_iMatrix[i][j][k]-1][8]);
					fTemp[m_iMatrix[i][j][k]-1][3] += ((i-fTemp[m_iMatrix[i][j][k]-1][6])*(i-fTemp[m_iMatrix[i][j][k]-1][6])+(k-fTemp[m_iMatrix[i][j][k]-1][8])*(k-fTemp[m_iMatrix[i][j][k]-1][8]));
					fTemp[m_iMatrix[i][j][k]-1][4] += -(j-fTemp[m_iMatrix[i][j][k]-1][7])*(k-fTemp[m_iMatrix[i][j][k]-1][8]);
					fTemp[m_iMatrix[i][j][k]-1][5] += ((i-fTemp[m_iMatrix[i][j][k]-1][6])*(i-fTemp[m_iMatrix[i][j][k]-1][6])+(j-fTemp[m_iMatrix[i][j][k]-1][7])*(j-fTemp[m_iMatrix[i][j][k]-1][7]));

				}
			}
		}
	}

	//save the matrix for principal direction
	int end;
	BYTE cha1=' ';
	char cha3[10];
/*	CFileDialog fSaveDlg(FALSE,NULL,NULL);
	CFile crfile;
	fSaveDlg.DoModal();
	crfile.Open(fSaveDlg.GetPathName().GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	for(i=0; i<m_iTraNo; i++)
	{
		for(j=0; j<8; j++)
		{
			_gcvt(fTemp[i][j], 10, cha3);
			for(k=0; k<10; k++)
			{
				if(cha3[k]==46)
				{
					cha3[k]=' ';
					end=k+1;
					k=10;
				}
			}
			crfile.Write(&cha3, end);
			for(k=0; k<10; k++)
				cha3[k]=0;
		}
		
		_gcvt(fTemp[i][8], 10, cha3);
		for(k=0; k<10; k++)
		{
			if(cha3[k]==46)
			{
				cha3[k] = 13;
				cha3[k+1] = 10;
				end = k+2;
				k = 10;
			}
		}
		crfile.Write(&cha3, end);
		for(k=0; k<10; k++)
			cha3[k]=0;
	}
	for(i=0; i<m_iTraNo; i++)
		free(fTemp[i]);

	free(m_iTemp);

	//save the connection matrix
	CFileDialog fSaveDlg2(FALSE,NULL,NULL);
	CFile crfile2;
	fSaveDlg2.DoModal();
	crfile2.Open(fSaveDlg2.GetPathName().GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	for(i=1; i<=m_iTraNo; i++)
	{
		for(j=0; j<=10; j++)
		{
			_gcvt(m_iConnection[i][j], 10, cha3);
			for(k=0; k<10; k++)
			{
				if(cha3[k]==46)
				{
					cha3[k]=' ';
					end=k+1;
					k=10;
				}
			}
			crfile2.Write(&cha3, end);
			for(k=0; k<10; k++)
				cha3[k]=0;
		}
		
		_gcvt(m_iConnection[i][10], 10, cha3);
		for(k=0; k<10; k++)
		{
			if(cha3[k]==46)
			{
				cha3[k] = 13;
				cha3[k+1] = 10;
				end = k+2;
				k = 10;
			}
		}
		crfile2.Write(&cha3, end);
		for(k=0; k<10; k++)
			cha3[k]=0;
	}
*/
}

void CFormCommandView::OnUpdateToolParameter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bPClustered && m_bRecovered)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);	
	
}

void CFormCommandView::OnIncrease() 
{
	// TODO: Add your control notification handler code here
	//if(m_bPClustered && m_bRecovered)
	//{
		m_bTrasep = TRUE;

		if(m_iTraSelect < m_iTraNo)
			m_iTraSelect ++;
		if(m_bLoad == TRUE)
		{
			CTestGLView* m_Temp;
			m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
			m_Temp->m_Clear = TRUE;
			m_Temp->Invalidate(TRUE);
		}
		m_strDebug.Format(_T("This is piece No. %d, the cosine of normal is %.3f, the thickness is %.3f"), m_iTraSelect, m_fNorm[m_iTraSelect][2], m_fTh[m_iTraSelect][0]);
		UpdateData( FALSE );

	//}
}

void CFormCommandView::OnDecrease() 
{
	// TODO: Add your control notification handler code here
	//if(m_bPClustered && m_bRecovered)
	//{
		m_bTrasep = TRUE;
		if(m_iTraSelect > 1)
			m_iTraSelect --;
		if(m_bLoad == TRUE)
		{
			CTestGLView* m_Temp;
			m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
			m_Temp->m_Clear = TRUE;
			m_Temp->Invalidate(TRUE);
		}
		m_strDebug.Format(_T("This is piece No. %d, the cosine of normal is %.3f, the thickness is %.3f"), m_iTraSelect, m_fNorm[m_iTraSelect][2], m_fTh[m_iTraSelect][0]);
		UpdateData( FALSE );

	//}
	
}

void CFormCommandView::OnToolMorph() 
{
	// TODO: Add your command handler code here

//	CFormCommandView::OnCluster();
	CFormCommandView::OnThinning();
	CFormCommandView::OnClassify();
	CFormCommandView::OnArcthinning();
	CFormCommandView::OnArcClassify();
	CFormCommandView::OnPlatecluster();
	CFormCommandView::OnRecover();
	CFormCommandView::OnToolSavebinary();

	int i,j;
	float A[3][3];
	CFile m_file;
	m_file.Abort();
	CString str = m_strPath;

	//CFileDialog fPartDlg(TRUE, NULL, NULL);
	//fPartDlg.m_ofn.lpstrTitle = _T("open tensor file");
	//fPartDlg.DoModal();
	//int rc = m_file.Open(fPartDlg.GetPathName().GetBuffer(0), CFile::modeRead);
/*	char chr[7];

	str.Insert(m_strPath.GetLength(), ".ten");
	m_file.Open(str.GetBuffer(0),CFile::modeRead);
	m_file.Seek(0, CFile::begin);

	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			m_file.Seek(3,CFile::current);
			m_file.Read(chr, 7);
			A[i][j] = atof(chr);
		}
		m_file.Seek(2,CFile::current);
	}

	if(rc == 0)
	{
		MessageBox(TEXT("Mechanics Tensor will be the same as image tensor"), MB_OK, NULL);
	}
	else
	{*/
		A[0][0] = 1;
		A[0][1] = 0;
		A[0][2] = 0;
		A[1][0] = 0;
		A[1][1] = 1;
		A[1][2] = 0;
		A[2][0] = 0;
		A[2][1] = 0;
		A[2][2] = 1;
//	}
	m_fPf = 0;		//plate fraction
	m_fRf = 0;		//rod fraction
	m_fPBVF = 0;		//Plate volume/TV
	m_fRBVF = 0;		//Rod volume/TV
	m_fPThickness = 0;	//Plate Thickness(mm)
	m_fRDiameter = 0;	//Rod diameter(mm)
	m_fPSurface = 0;	//Plate surface(mm^2)
	m_fRLength = 0;	//Rod length(mm)
	m_fPNo = 0;			//Plate No/TV(1/mm^3)
	m_fRNo = 0;			//Rod No/TV(1/mm^3)
	
	m_fxlf = 0;
	m_fxhf = 0;
	m_fylf = 0;
	m_fyhf = 0;
	m_fzlf = 0;
	m_fzhf = 0;

	m_fxlpf = 0;
	m_fxhrf = 0;
	m_fylpf = 0;
	m_fyhrf = 0;
	m_fzlpf = 0;
	m_fzhrf = 0;

	float rP=0;
	float rR=0;

	for(i=1; i<=m_iTraNo; i++)
	{
		m_fTh[i][0] = m_fTh[i][0]*sqrtf((m_fNorm[i][0]*m_resolution[0])*(m_fNorm[i][0]*m_resolution[0])+(m_fNorm[i][1]*m_resolution[1])*(m_fNorm[i][1]*m_resolution[1])+(m_fNorm[i][2]*m_resolution[2])*(m_fNorm[i][2]*m_resolution[2]));
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_fTh[i][0] != 0)
		{
			if(m_iCluster[i][1] == 1)
			{
				m_fPf += (float)m_iCluster[i][0];
				rP += (float)m_iCluster[i][0];
				m_fPThickness += (float)m_iCluster[i][0]/m_fTh[i][0];
				m_fPSurface += (float)m_iCluster[i][0]*m_resolution[0]*m_resolution[1]*m_resolution[2]/m_fTh[i][0];
				m_fPNo++;
				if(fabs(A[0][0]*m_fNorm[i][0]+A[0][1]*m_fNorm[i][1]+A[0][2]*m_fNorm[i][2])< 0.5)
				{
					m_fxlpf += (float)m_iCluster[i][0];
					m_fxlf += (float)m_iCluster[i][0];
				}
				else if(fabs(A[0][0]*m_fNorm[i][0]+A[0][1]*m_fNorm[i][1]+A[0][2]*m_fNorm[i][2]) >= sqrtf(3.0)/2.0)
				{
					m_fxhf += (float)m_iCluster[i][0];
				}
				if(fabs(A[1][0]*m_fNorm[i][0]+A[1][1]*m_fNorm[i][1]+A[1][2]*m_fNorm[i][2])< 0.5)
				{
					m_fylpf += (float)m_iCluster[i][0];
					m_fylf += (float)m_iCluster[i][0];
				}
				else if(fabs(A[1][0]*m_fNorm[i][0]+A[1][1]*m_fNorm[i][1]+A[1][2]*m_fNorm[i][2]) >= sqrtf(3.0)/2.0)
				{
					m_fyhf += (float)m_iCluster[i][0];
				}
				if(fabs(A[2][0]*m_fNorm[i][0]+A[2][1]*m_fNorm[i][1]+A[2][2]*m_fNorm[i][2])< 0.5)
				{
					m_fzlpf += (float)m_iCluster[i][0];
					m_fzlf += (float)m_iCluster[i][0];
				}
				else if(fabs(A[2][0]*m_fNorm[i][0]+A[2][1]*m_fNorm[i][1]+A[2][2]*m_fNorm[i][2]) >= sqrtf(3.0)/2.0)
				{
					m_fzhf += (float)m_iCluster[i][0];
				}
			}
			else
			{
				m_fRf += (float)m_iCluster[i][0];
				rR += (float)m_iCluster[i][0];
				m_fRDiameter += 4*(float)m_iCluster[i][0]*m_resolution[0]*m_resolution[1]*m_resolution[2]/3.1415927/m_fTh[i][0];
				m_fRLength += 4*(float)m_iCluster[i][0]*m_resolution[0]*m_resolution[1]*m_resolution[2]/3.1415927/m_fTh[i][0]/m_fTh[i][0];
				m_fRNo++;
				if(fabs(A[0][0]*m_fNorm[i][0]+A[0][1]*m_fNorm[i][1]+A[0][2]*m_fNorm[i][2])< 0.5)
				{
					m_fxhrf += (float)m_iCluster[i][0];
					m_fxhf += (float)m_iCluster[i][0];
				}
				else if(fabs(A[0][0]*m_fNorm[i][0]+A[0][1]*m_fNorm[i][1]+A[0][2]*m_fNorm[i][2]) >= sqrtf(3.0)/2.0)
				{
					m_fxlf += (float)m_iCluster[i][0];
				}
				if(fabs(A[1][0]*m_fNorm[i][0]+A[1][1]*m_fNorm[i][1]+A[1][2]*m_fNorm[i][2])< 0.5)
				{
					m_fyhrf += (float)m_iCluster[i][0];
					m_fyhf += (float)m_iCluster[i][0];
				}
				else if(fabs(A[1][0]*m_fNorm[i][0]+A[1][1]*m_fNorm[i][1]+A[1][2]*m_fNorm[i][2]) >= sqrtf(3.0)/2.0)
				{
					m_fylf += (float)m_iCluster[i][0];
				}
				if(fabs(A[2][0]*m_fNorm[i][0]+A[2][1]*m_fNorm[i][1]+A[2][2]*m_fNorm[i][2]) < 0.5)
				{
					m_fzhrf += (float)m_iCluster[i][0];
					m_fzhf += (float)m_iCluster[i][0];
				}
				else if(fabs(A[2][0]*m_fNorm[i][0]+A[2][1]*m_fNorm[i][1]+A[2][2]*m_fNorm[i][2]) >= sqrtf(3.0)/2.0)
				{
					m_fzlf += (float)m_iCluster[i][0];
				}
			}
		}
		else
		{
			if(m_iCluster[i][1] == 1)
				m_fPf += (float)m_iCluster[i][0];
			else
				m_fRf += (float)m_iCluster[i][0];
		}
	}

	m_fxlf /= (rP+rR);
	m_fxhf /= (rP+rR);
	m_fylf /= (rP+rR);
	m_fyhf /= (rP+rR);
	m_fzlf /= (rP+rR);
	m_fzhf /= (rP+rR);

	m_fxlpf /= (rP+rR);
	m_fxhrf /= (rP+rR);
	m_fylpf /= (rP+rR);
	m_fyhrf /= (rP+rR);
	m_fzlpf /= (rP+rR);
	m_fzhrf /= (rP+rR);

	m_fPThickness = m_fPf/m_fPThickness;
	m_fPSurface = m_fPSurface/m_fPNo;
	m_fPf = m_fPf/(m_fPf+m_fRf);
	m_fPBVF = m_fBVF*m_fPf;
	m_fPNo = powf(m_fPNo/(float)m_iSize[0]/(float)m_iSize[1]/(float)m_iSize[2]/m_resolution[0]/m_resolution[1]/m_resolution[2], 1.0/3.0)*1000;

	m_fRDiameter = m_fRDiameter/m_fRLength;
	m_fRLength = m_fRLength/m_fRNo;
	m_fRf = 1-m_fPf;
	m_fRBVF = m_fBVF*m_fRf;
	m_fRNo = powf(m_fRNo/(float)m_iSize[0]/(float)m_iSize[1]/(float)m_iSize[2]/m_resolution[0]/m_resolution[1]/m_resolution[2], 1.0/3.0)*1000;

	m_fRRJNo = m_fRRJNo/(float)m_iSize[0]/(float)m_iSize[1]/(float)m_iSize[2]/m_resolution[0]/m_resolution[1]/m_resolution[2]*powf(10,9);
	m_fRPJNo = m_fRPJNo/(float)m_iSize[0]/(float)m_iSize[1]/(float)m_iSize[2]/m_resolution[0]/m_resolution[1]/m_resolution[2]*powf(10,9);
	m_fPPJNo = m_fPPJNo/(float)m_iSize[0]/(float)m_iSize[1]/(float)m_iSize[2]/m_resolution[0]/m_resolution[1]/m_resolution[2]*powf(10,9);


	

	CFileDialog fSaveDlg(FALSE,NULL,NULL);
	CFile crfile;
	str = m_strPath;
	str.Insert(m_strPath.GetLength(), _T(".par"));
	crfile.Open(str.GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	char cha3[50];
	int end=16;

	int a;
	
	sprintf(cha3, "%.5f", m_fBVF);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3, "%.5f", m_fPf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3, "%.5f", m_fRf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3, "%.5f", m_fPNo);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3, "%.5f", m_fRNo);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;
	
	sprintf(cha3, "%.5f", m_fPThickness);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3, "%.5f", m_fRDiameter);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3, "%.5f", m_fPSurface);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;


	sprintf(cha3, "%.5f", m_fRLength);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3, "%.5f", m_fxlf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3, "%.5f", m_fxhf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fylf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fyhf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fzlf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fzhf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fxlpf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fxhrf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fylpf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fyhrf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fzlpf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fzhrf);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fPBVF);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fRBVF);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fRRJNo);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fRPJNo);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;

	sprintf(cha3,"%.5f", m_fPPJNo);
	for(a=5;a<50;a++)
	{	
		if(cha3[a]==0)
		{
			cha3[a]=13;
			cha3[a+1]=10;
			end=a+1;
			a=50;
		}
	}
	crfile.Write(cha3, end+1);
	for(a=0; a<50; a++)
		cha3[a] = 0;
}

void CFormCommandView::OnUpdateToolMorph(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bLoad)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);	
	
}

void CFormCommandView::OnToolSavebinary() 
{
	// TODO: Add your command handler code here
	CFile cfSave;
	//CFileDialog fSaveDlg(FALSE, "bin", "*.bin");
	int rc=1;
	int i, j, k, m;
	int count;
	char cTemp[2];
	//fSaveDlg.DoModal();
	//rc = cfSave.Open(fSaveDlg.GetPathName().GetBuffer(0), CFile::modeWrite|CFile::modeCreate);
	CString str = m_strPath;
	str.Insert(m_strPath.GetLength(), _T(".seg"));
	cfSave.Open(str.GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	if(rc == 0)
	{
		MessageBox(TEXT("Invalid Pathname!"), MB_OK, NULL);
		return;
	}

	m_strDisp.Format(_T("Start Recording Data!"));
	UpdateData( FALSE );

	int remain;
	
	for (j=0; j<3; j++)
	{
		remain = m_iSize[j];
		for (i=1; i>=0; i--)
		{
			cTemp[i] = remain % 256;
			remain = (int)(remain/256);
		}

		cfSave.Write(cTemp, 2);
	}

	remain = m_iTraNo;
	for(i=1; i>=0; i--)
	{
		cTemp[i] = remain % 256;
		remain = (int)(remain/256);
	}
	cfSave.Write(cTemp,2);

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]>0)
				{
					remain = m_iMatrix[i][j][k];
					for (m=1; m>=0; m--)
					{
						cTemp[m] = remain % 256;
						remain = (int)(remain/256);
					}

					cfSave.Write(cTemp, 2);
				}
				else
				{
					cTemp[1] = 0;
					cTemp[0] = 0;
					cfSave.Write(cTemp,2);
				}
			}
		}
	}



/*	char cTemp;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k]>0)
				{
					cTemp = 3;

					cfSave.Write(&cTemp, 1);
				}
				else
				{
					cTemp = 0;
					cfSave.Write(&cTemp, 1);
				}
			}
		}
	}*/
	m_strDisp.Format(_T("Finish Recording Data!"));
	UpdateData( FALSE );			
}

void CFormCommandView::OnUpdateToolSavebinary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bLoad)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);	
	
}



void CFormCommandView::OnToolBkldata() 
{
	// TODO: Add your command handler code here
	int i,j,k;
	int	 rc=0;
	unsigned char m_char;
	
	CFile m_file;

	
	if(m_bLoad == FALSE)
	{
		/**** loading the look_up_table from Saha's table ****/
		FILE *fp;
		unsigned char a,b;

		if((fp = fopen ("tab3b", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
			tab3b[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab4a", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab4a[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab4b", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab4b[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab5", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab5[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab6", "r")) != NULL)
		{
			i=0;
			while (fscanf(fp, "%d %d\n", &a, &b) == 2) 
			{
				tab6[i][0] = a;
				tab6[i][1] = b;
				i = i + 1;
			}
			fclose(fp);
		}

		/*m_iTemp is for storing the 27 points configuration(0/1) in simple point detection*/
		m_iTemp = (int ***)calloc(3, sizeof(int**));
		for(i=0; i<=2; i++)
		{
			m_iTemp[i] = (int **)calloc(3, sizeof(int*));
		}
		for(i=0; i<=2; i++)
		{
			for(j=0; j<=2; j++)
			{
				m_iTemp[i][j] = (int *)calloc(3, sizeof(int));
			}
		}

		for(i=0; i<=2; i++)
			for(j=0; j<=2; j++)
				for(k=0; k<=2; k++)
					m_iTemp[i][j][k] = 0;

		m_iSize = (int*)malloc(sizeof(int) * 3);
	}


	m_file.Abort();

	CFileDialog fPartDlg(TRUE, NULL, NULL);
	//fPartDlg.m_ofn.lpstrTitle = _T("open data file");
	fPartDlg.DoModal();
	rc = m_file.Open(fPartDlg.GetPathName().GetBuffer(0), CFile::modeRead);
	if(rc == 0)
	{
		MessageBox(TEXT("Invalid Pathname!"), MB_OK, NULL);
		return;
	}
	
	if(m_bLoad == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++) 
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iMatrix[i][j]);
	
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iMatrix[i]);
		
		free(m_iMatrix);
	}

	if(m_bBklLoad == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++) 
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iLabel[i][j]);
	
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iLabel[i]);

		free(m_iLabel);

		for(i=0; i<=m_iTotalNo; i++) 
			for(j=0; j<6; j++)
				free(m_fStrain[i][j]);
	
		for(i=0; i<=m_iTotalNo; i++)
			free(m_fStrain[i]);

		free(m_fStrain);

		for(i=0; i<=m_iTotalNo; i++) 
			for(j=0; j<6; j++)
				free(m_fStress[i][j]);
	
		for(i=0; i<=m_iTotalNo; i++)
			free(m_fStress[i]);

		free(m_fStress);

		free(m_iFail);

		for(i=0; i<=m_iTotalNo; i++)
		{
			free(m_iStepCT[i]);
		}
		free(m_iStepCT);
	}

	if(m_bStepShow == TRUE)
	{
		for(i=0; i<=m_iTraNo; i++)
		{
			free(m_iStepFailure[i]);
		}
		free(m_iStepFailure);
	}
	
	if(m_bThinned == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++)
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iPtType[i][j]);
		
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iPtType[i]);

		free(m_iPtType);
	}

	if(m_bRecovered == TRUE)
	{
		for(i=0; i<=m_iTraNo; i++)
		{
			free(m_fNorm[i]);
		}
		free(m_fNorm);

		for(i=0; i<=m_iTraNo; i++)
		{
			free(m_fTh[i]);
		}
		free(m_fTh);
	}

	if(m_bPClustered == TRUE)
	{
		for(i=0; i <= m_iClusterNo; i++)
			free(m_iCluster[i]);

		for(i=0; i < m_iNodelistSize; i++)
			free(m_iNodelist[i]);

		for(i=0; i <= m_iTraNo; i++)
			free(m_iConnection[i]);

		free(m_iCluster);
		free(m_iNodelist);
		free(m_iConnection);
	}

	m_bThinned = FALSE;
	m_bArcThinned = FALSE;
	m_bClassified = FALSE;
	m_bDebugmode = FALSE;
	m_bRecovered = FALSE;
	m_bPClustered = FALSE;
	m_bCurveMeshed = FALSE;
	m_bTrasep = FALSE;

	/**************** Begin loading data *******************/
	m_strDisp.Format(_T("Start Loading Data"));
	UpdateData( FALSE );

	m_bLoad = TRUE;
	m_bBklLoad = TRUE;
	m_iSize[0] = 119;
	m_iSize[1] = 119;
	m_iSize[2] = 114;

	m_iMatrix = (int ***)calloc(m_iSize[0]+4, sizeof(int**));
	for(i=0; i<m_iSize[0]+4; i++)
	{
		m_iMatrix[i] = (int **)calloc(m_iSize[1]+4, sizeof(int*));
	}
	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			m_iMatrix[i][j] = (int *)calloc(m_iSize[2]+4, sizeof(int));
		}
	}

	m_iLabel = (int ***)calloc(m_iSize[0]+4, sizeof(int**));
	for(i=0; i<m_iSize[0]+4; i++)
	{
		m_iLabel[i] = (int **)calloc(m_iSize[1]+4, sizeof(int*));
	}
	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			m_iLabel[i][j] = (int *)calloc(m_iSize[2]+4, sizeof(int));
		}
	}

	m_iTotalNo = 0;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				m_file.Read(&m_char,1);
				m_iMatrix[i][j][k] = !!(int)m_char;
				m_iLabel[i][j][k] = 0;
				if(m_iMatrix[i][j][k] > 0)
					m_iTotalNo++;
			}
		}
	}

	hoshen_kopelman2(m_iMatrix, m_iSize);

	for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
					m_iMatrix[i][j][k] = 0;


	m_strDisp.Format(_T("Bone Data Loading Sucessfully!"));
	m_strSize.Format(_T("The Image Size is   x=%d,   y=%d,   z=%d"), m_iSize[0], m_iSize[1], m_iSize[2]);
	m_strDebug.Format(_T(""));
	UpdateData( FALSE );

	m_fStrain = (float ***)calloc(m_iTotalNo+1, sizeof(float**));
	for(i=0; i<=m_iTotalNo; i++)
	{
		m_fStrain[i] = (float **)calloc(6, sizeof(float*));
	}
	for(i=0; i<=m_iTotalNo; i++)
	{
		for(j=0; j<6; j++)
		{
			m_fStrain[i][j] = (float *)calloc(10, sizeof(float));
		}
	}

	m_fStress = (float ***)calloc(m_iTotalNo+1, sizeof(float**));
	for(i=0; i<=m_iTotalNo; i++)
	{
		m_fStress[i] = (float **)calloc(6, sizeof(float*));
	}
	for(i=0; i<=m_iTotalNo; i++)
	{
		for(j=0; j<6; j++)
		{
			m_fStress[i][j] = (float *)calloc(10, sizeof(float));
		}
	}


	CFile m_file0;
	m_file0.Abort();

	CFileDialog fPartDlg2(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_ALLOWMULTISELECT );
	fPartDlg2.m_ofn.lpstrTitle = _T("Open the Strain/Stress Data File");
	fPartDlg2.DoModal();
	
	POSITION pos = fPartDlg2.GetStartPosition();
    CString str;
	int column = 0;
	//int offset = 0;
	int x,y,z;
	char chr1;
	char chr3[2];
	char chr[5];
	char chr2[11];
	float temp;
	int itemp;
	int count=0;
	int tag = 0;
	
	m_iFail = (int *)calloc(m_iTotalNo+1, sizeof(int));
	for(i=0; i<=m_iTotalNo; i++)
		m_iFail[i] = 0;

	m_iStepCT = (int **)calloc(m_iTotalNo+1, sizeof(int*));
	for(i=0; i<=m_iTotalNo; i++)
	{
		m_iStepCT[i] = (int *)calloc(10, sizeof(int));
	}

	for(i=0; i<=m_iTotalNo; i++)
	{
		for(j=0; j<10; j++)
		{
			m_iStepCT[i][j] = 0;
		}
	}

	while(pos)
    {
		//count++;
        // add the file paths to the list
		tag++;
        m_file0.Abort();
		str = fPartDlg2.GetNextPathName(pos);
		count = str.GetLength();
		chr1 = str.GetAt(count-1);
		count = atoi(&chr1);
		if(count == 0)
			count = 10;
		rc = m_file0.Open(str, CFile::modeRead);
		if(rc == 0)
		{
			MessageBox(TEXT("Invalid Pathname!"), MB_OK, NULL);
			return;
		}

		//m_file0.Read(&chr1,1);
		//count = atoi(&chr1);
		column = 102422;
		//m_file0.Seek(1, CFile::current);

		for(j=1; j<=column; j++)
		{
			if(tag==1)
			{
				m_file0.Seek(7, CFile::current);
				m_file0.Read(chr, 5);
				temp = atof(chr)/0.044+1.5;
				x=int(temp);
				if((float)x-temp<-0.5)
				x++;
				m_file0.Seek(4, CFile::current);
				m_file0.Read(chr, 5);
				temp = atof(chr)/0.044+1.5;
				y=int(temp);
				if((float)y-temp<-0.5)
				y++;
				m_file0.Seek(4, CFile::current);
				m_file0.Read(chr, 5);
				temp = atof(chr)/0.044+1.5;
				z=int(temp);
				if((float)z-temp<-0.5)
					z++;
				m_iLabel[x][y][z] = j;//count;//
			}
			else
			{
				m_file0.Seek(30, CFile::current);
			}

			for(k=0; k<6; k++)
			{
				m_file0.Seek(1, CFile::current);
				m_file0.Read(chr2, 11);
				temp = atof(chr2);
				m_fStress[j][k][count-1] = atof(chr2);
			}

			m_file0.Seek(11, CFile::current);
			m_file0.Read(chr3, 2);
			itemp = atoi(chr3);

			m_iStepCT[j][count-1] = itemp;

			if((itemp==-1) && (abs(m_iFail[j]) > count || m_iFail[j] == 0 ) )
				m_iFail[j] = (-1)*count;
			else if((itemp==1) && (abs(m_iFail[j]) > count || m_iFail[j] == 0 ))
				m_iFail[j] = count;

			m_file0.Seek(18, CFile::current);

			for(k=0; k<6; k++)
			{
				m_file0.Seek(1, CFile::current);
				m_file0.Read(chr2, 11);
				m_fStrain[j][k][count-1] = atof(chr2);
			}
			m_file0.Seek(1, CFile::current);

		}
   }
	m_strDisp.Format(_T("Stree/Strain Loading Sucessfully!"));
	m_strSize.Format(_T("The Image Size is   x=%d,   y=%d,   z=%d"), m_iSize[0], m_iSize[1], m_iSize[2]);
	m_strDebug.Format(_T(""));
	UpdateData( FALSE );

/******************** End of Loading Data *************************/

}

void CFormCommandView::OnToolStress() 
{
	// TODO: Add your command handler code here
	int i,j,k;
	int a,b,c;
	float ***fTemp;
	fTemp = (float ***)calloc(m_iTraNo, sizeof(float**));
	for(i=0; i<m_iTraNo; i++)
	{
		fTemp[i] = (float **)calloc(6, sizeof(float*));
	}

	for(i=0; i<m_iTraNo; i++)
	{
		for(j=0; j<6; j++)
		{
			fTemp[i][j] = (float*)calloc(20, sizeof(float));
		}
	}

	for(i=0; i<m_iTraNo; i++)
	{
		for(j=0; j<6; j++)
		{
			for(k=0; k<20; k++)
			{
				fTemp[i][j][k] = 0;
			}
		}
	}

	int *iFail;
	iFail = (int *)calloc(m_iTraNo+1, sizeof(int));
	for(i=0; i<=m_iTraNo; i++)
	{
		iFail[i] = 0;
	}

	int **iStep;
	iStep = (int **)calloc(m_iTraNo+1, sizeof(int*));
	for(i=0; i<=m_iTraNo; i++)
	{
		iStep[i] = (int*)calloc(20, sizeof(int));
	}
	for(i=0; i<=m_iTraNo; i++)
	{
		for(j=0; j<20; j++)
		{
			iStep[i][j] = 0;
		}
	}

	m_iStepFailure = (int **)calloc(m_iTraNo+1, sizeof(int*));
	for(i=0; i<=m_iTraNo; i++)
	{
		m_iStepFailure[i] = (int*)calloc(10, sizeof(int));
	}
	for(i=0; i<=m_iTraNo; i++)
	{
		for(j=0; j<10; j++)
		{
			m_iStepFailure[i][j] = 0;
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0 && m_iLabel[i][j][k] == 0)
					m_iMatrix[i][j][k] = 0;
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(abs(m_iFail[m_iLabel[i][j][k]])<abs(iFail[m_iMatrix[i][j][k]]) && m_iFail[m_iLabel[i][j][k]] != 0 || (m_iFail[m_iLabel[i][j][k]]!= 0 && iFail[m_iMatrix[i][j][k]] == 0))
					{
						iFail[m_iMatrix[i][j][k]] = m_iFail[m_iLabel[i][j][k]];
					}
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					for(a=0; a<6; a++)
					{
						for(b=0; b<10; b++)
						{
							fTemp[m_iMatrix[i][j][k]-1][a][b] += m_fStrain[m_iLabel[i][j][k]][a][b];
							fTemp[m_iMatrix[i][j][k]-1][a][b+10] += m_fStress[m_iLabel[i][j][k]][a][b];
						}
					}
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					for(a=0; a<10; a++)
					{
						if(m_iStepCT[m_iLabel[i][j][k]][a] == 1)
							iStep[m_iMatrix[i][j][k]][a]++;
						else if(m_iStepCT[m_iLabel[i][j][k]][a] == -1)
							iStep[m_iMatrix[i][j][k]][a+10]++;
					}
				}
			}
		}
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		for (j=0; j<10; j++)
		{
			if(iStep[i][j] == 0 && iStep[i][j+10] == 0)
				m_iStepFailure[i][j] = 0;
			else
				m_iStepFailure[i][j] = 1;
		}
	}

	//save stress and strain
	CFileDialog fSaveDlg(FALSE,NULL,NULL);
	CFile crfile;
	crfile.Abort();
	fSaveDlg.DoModal();
	crfile.Open(fSaveDlg.GetPathName().GetBuffer(0),CFile::modeWrite|CFile::modeCreate);
	char cha3[16];
	int end=16;

	for(i=0; i<m_iTraNo; i++)
	{
		for(j=0; j<6; j++)
		{
			for(k=0; k<19; k++)
			{
				sprintf(cha3,"%.5f ", fTemp[i][j][k]);
				end=16;
				for(a=5;a<16;a++)
				{	
					if(cha3[a]==32)
					{
						end=a+1;
						a=16;
					}
				}
				crfile.Write(cha3, end);
				for(a=0; a<16; a++)
					cha3[a] = 0;

			}
			sprintf(cha3,"%.5f\n", fTemp[i][j][19]);
			end = 16;
			for(a=1;a<16;a++)
			{	
				if(cha3[a] == 10)
				{
					cha3[a] = 13;
					cha3[a+1] = 10;
					end=a+2;
					a=16;
				}
			}
			crfile.Write(cha3, end);	
			for(a=0; a<16; a++)
				cha3[a] = 0;

		}
	}

	//save failure step and failure mode
	CFileDialog fSaveDlg3(FALSE,NULL,NULL);
	CFile crfile3;
	crfile3.Abort();
	fSaveDlg3.DoModal();
	crfile3.Open(fSaveDlg3.GetPathName().GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	for(i=1; i<=m_iTraNo; i++)
	{
		_gcvt(iFail[i], 10, cha3);
		for(k=0; k<10; k++)
		{
			if(cha3[k]==46)
			{
				cha3[k] = 13;
				cha3[k+1] = 10;
				end = k+2;
				k = 10;
			}
		}
		crfile3.Write(&cha3, end);
		for(k=0; k<10; k++)
			cha3[k]=0;
	}

	//save failure voxel number and failure mode
	CFileDialog fSaveDlg2(FALSE,NULL,NULL);
	CFile crfile2;
	crfile2.Abort();
	fSaveDlg2.DoModal();
	crfile2.Open(fSaveDlg2.GetPathName().GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	for(i=1; i<=m_iTraNo; i++)
	{
		for(j=0; j<19; j++)
		{
			_gcvt(iStep[i][j], 10, cha3);
			for(k=0; k<10; k++)
			{
				if(cha3[k]==46)
				{
					cha3[k]=' ';
					end=k+1;
					k = 10;
				}
			}
			crfile2.Write(&cha3, end);
			for(k=0; k<10; k++)
				cha3[k]=0;
		}
		
		_gcvt(iStep[i][19], 10, cha3);
		for(k=0; k<10; k++)
		{
			if(cha3[k]==46)
			{
				cha3[k] = 13;
				cha3[k+1] = 10;
				end = k+2;
				k = 10;
			}
		}
		crfile2.Write(&cha3, end);
		for(k=0; k<10; k++)
			cha3[k]=0;
	}

	for(i=0; i<m_iTraNo; i++)
	{
		for(j=0; j<6; j++)
		{
			free(fTemp[i][j]);
		}
	}

	for(i=0; i<m_iTraNo; i++)
	{
		free(fTemp[i]);
	}

	free(fTemp);
	free(iFail);

	for(i=0; i<=m_iTraNo; i++)
	{
		free(iStep[i]);
	}

	free(iStep);	
}

void CFormCommandView::OnUpdateToolStress(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bPClustered && m_bRecovered && m_bBklLoad)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);		
}

void CFormCommandView::OnStepincrease() 
{
	// TODO: Add your control notification handler code here
	if(m_bBklLoad == FALSE || m_bRecovered == FALSE || m_iStepSelect == 9)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}
	if(m_bStepShow == 0)
	{
		int i,j,k;
		int a,b,c;
		float ***fTemp;
		fTemp = (float ***)calloc(m_iTraNo, sizeof(float**));
		for(i=0; i<m_iTraNo; i++)
		{
			fTemp[i] = (float **)calloc(6, sizeof(float*));
		}

		for(i=0; i<m_iTraNo; i++)
		{
			for(j=0; j<6; j++)
			{
				fTemp[i][j] = (float*)calloc(20, sizeof(float));
			}
		}

		for(i=0; i<m_iTraNo; i++)
		{
			for(j=0; j<6; j++)
			{
				for(k=0; k<20; k++)
				{
					fTemp[i][j][k] = 0;
				}
			}
		}

		int *iFail;
		iFail = (int *)calloc(m_iTraNo+1, sizeof(int));
		for(i=0; i<=m_iTraNo; i++)
		{
			iFail[i] = 0;
		}

		int **iStep;
		iStep = (int **)calloc(m_iTraNo+1, sizeof(int*));
		for(i=0; i<=m_iTraNo; i++)
		{
			iStep[i] = (int*)calloc(20, sizeof(int));
		}
		for(i=0; i<=m_iTraNo; i++)
		{
			for(j=0; j<20; j++)
			{
				iStep[i][j] = 0;
			}
		}

		m_iStepFailure = (int **)calloc(m_iTraNo+1, sizeof(int*));
		for(i=0; i<=m_iTraNo; i++)
		{
			m_iStepFailure[i] = (int*)calloc(10, sizeof(int));
		}
		for(i=0; i<=m_iTraNo; i++)
		{
			for(j=0; j<10; j++)
			{
				m_iStepFailure[i][j] = 0;
			}
		}

		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] > 0)
					{
						if(abs(m_iFail[m_iLabel[i][j][k]])<abs(iFail[m_iMatrix[i][j][k]]) && m_iFail[m_iLabel[i][j][k]] != 0 || (m_iFail[m_iLabel[i][j][k]]!= 0 && iFail[m_iMatrix[i][j][k]] == 0))
						{
							iFail[m_iMatrix[i][j][k]] = m_iFail[m_iLabel[i][j][k]];
						}
					}
				}
			}
		}

		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] > 0)
					{
						for(a=0; a<6; a++)
						{
							for(b=0; b<10; b++)
							{
								fTemp[m_iMatrix[i][j][k]-1][a][b] += m_fStrain[m_iLabel[i][j][k]][a][b];
								fTemp[m_iMatrix[i][j][k]-1][a][b+10] += m_fStress[m_iLabel[i][j][k]][a][b];
							}
						}
					}
				}
			}
		}

		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] > 0)
					{
						for(a=0; a<10; a++)
						{
							if(m_iStepCT[m_iLabel[i][j][k]][a] == 1)
								iStep[m_iMatrix[i][j][k]][a]++;
							else if(m_iStepCT[m_iLabel[i][j][k]][a] == -1)
								iStep[m_iMatrix[i][j][k]][a+10]++;
						}
					}
				}
			}
		}

		for(i=1; i<=m_iTraNo; i++)
		{
			for (j=0; j<10; j++)
			{
				if(iStep[i][j] == 0 && iStep[i][j+10] == 0)
					m_iStepFailure[i][j] = 0;
				else
					m_iStepFailure[i][j] = 1;
			}
		}
		for(i=0; i<m_iTraNo; i++)
		{
			for(j=0; j<6; j++)
			{
				free(fTemp[i][j]);
			}
		}

		for(i=0; i<m_iTraNo; i++)
		{
			free(fTemp[i]);
		}

		free(fTemp);
		free(iFail);

		for(i=0; i<=m_iTraNo; i++)
		{
			free(iStep[i]);
		}

		free(iStep);	
	}

	m_bStepShow = 1;
	UpdateData(TRUE);
	m_iStepSelect++;
	if(m_bLoad == TRUE)
	{
		CTestGLView* m_Temp;
		m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
		m_Temp->m_Clear = TRUE;
		m_Temp->Invalidate(TRUE);
	}
	UpdateData(FALSE);
}

void CFormCommandView::OnStepdecrease() 
{
	// TODO: Add your control notification handler code here
	if(m_bBklLoad == FALSE || m_bRecovered == FALSE || m_iStepSelect == 0)
	{
		MessageBox(_T(" Please load data first! "));
		return;
	}
	if(m_bStepShow == 0)
	{
		int i,j,k;
		int a,b,c;
		float ***fTemp;
		fTemp = (float ***)calloc(m_iTraNo, sizeof(float**));
		for(i=0; i<m_iTraNo; i++)
		{
			fTemp[i] = (float **)calloc(6, sizeof(float*));
		}

		for(i=0; i<m_iTraNo; i++)
		{
			for(j=0; j<6; j++)
			{
				fTemp[i][j] = (float*)calloc(20, sizeof(float));
			}
		}

		for(i=0; i<m_iTraNo; i++)
		{
			for(j=0; j<6; j++)
			{
				for(k=0; k<20; k++)
				{
					fTemp[i][j][k] = 0;
				}
			}
		}

		int *iFail;
		iFail = (int *)calloc(m_iTraNo+1, sizeof(int));
		for(i=0; i<=m_iTraNo; i++)
		{
			iFail[i] = 0;
		}

		int **iStep;
		iStep = (int **)calloc(m_iTraNo+1, sizeof(int*));
		for(i=0; i<=m_iTraNo; i++)
		{
			iStep[i] = (int*)calloc(20, sizeof(int));
		}
		for(i=0; i<=m_iTraNo; i++)
		{
			for(j=0; j<20; j++)
			{
				iStep[i][j] = 0;
			}
		}

		m_iStepFailure = (int **)calloc(m_iTraNo+1, sizeof(int*));
		for(i=0; i<=m_iTraNo; i++)
		{
			m_iStepFailure[i] = (int*)calloc(10, sizeof(int));
		}
		for(i=0; i<=m_iTraNo; i++)
		{
			for(j=0; j<10; j++)
			{
				m_iStepFailure[i][j] = 0;
			}
		}

		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] > 0)
					{
						if(abs(m_iFail[m_iLabel[i][j][k]])<abs(iFail[m_iMatrix[i][j][k]]) && m_iFail[m_iLabel[i][j][k]] != 0 || (m_iFail[m_iLabel[i][j][k]]!= 0 && iFail[m_iMatrix[i][j][k]] == 0))
						{
							iFail[m_iMatrix[i][j][k]] = m_iFail[m_iLabel[i][j][k]];
						}
					}
				}
			}
		}

		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] > 0)
					{
						for(a=0; a<6; a++)
						{
							for(b=0; b<10; b++)
							{
								fTemp[m_iMatrix[i][j][k]-1][a][b] += m_fStrain[m_iLabel[i][j][k]][a][b];
								fTemp[m_iMatrix[i][j][k]-1][a][b+10] += m_fStress[m_iLabel[i][j][k]][a][b];
							}
						}
					}
				}
			}
		}

		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2; i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] > 0)
					{
						for(a=0; a<10; a++)
						{
							if(m_iStepCT[m_iLabel[i][j][k]][a] == 1)
								iStep[m_iMatrix[i][j][k]][a]++;
							else if(m_iStepCT[m_iLabel[i][j][k]][a] == -1)
								iStep[m_iMatrix[i][j][k]][a+10]++;
						}
					}
				}
			}
		}

		for(i=1; i<=m_iTraNo; i++)
		{
			for (j=0; j<10; j++)
			{
				if(iStep[i][j] == 0 && iStep[i][j+10] == 0)
					m_iStepFailure[i][j] = 0;
				else
					m_iStepFailure[i][j] = 1;
			}
		}
		for(i=0; i<m_iTraNo; i++)
		{
			for(j=0; j<6; j++)
			{
				free(fTemp[i][j]);
			}
		}

		for(i=0; i<m_iTraNo; i++)
		{
			free(fTemp[i]);
		}

		free(fTemp);
		free(iFail);

		for(i=0; i<=m_iTraNo; i++)
		{
			free(iStep[i]);
		}

		free(iStep);	
	}
	
	m_bStepShow = 1;
		UpdateData(TRUE);
		m_iStepSelect--;
		if(m_bLoad == TRUE)
		{
			CTestGLView* m_Temp;
			m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pImageView;
			m_Temp->m_Clear = TRUE;
			m_Temp->Invalidate(TRUE);
		}
		UpdateData(FALSE);
	
}

void CFormCommandView::OnToolBinary() 
{
	// TODO: Add your command handler code here
	int i,j,k;
	int	 rc=0;
	unsigned char m_char;
	
	CFile m_file;

	
	if(m_bLoad == FALSE)
	{
		/**** loading the look_up_table from Saha's table ****/
		FILE *fp;
		unsigned char a,b;

		if((fp = fopen ("tab3b", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
			tab3b[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab4a", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab4a[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab4b", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab4b[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab5", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab5[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab6", "r")) != NULL)
		{
			i=0;
			while (fscanf(fp, "%d %d\n", &a, &b) == 2) 
			{
				tab6[i][0] = a;
				tab6[i][1] = b;
				i = i + 1;
			}
			fclose(fp);
		}

		/*m_iTemp is for storing the 27 points configuration(0/1) in simple point detection*/
		m_iTemp = (int ***)calloc(3, sizeof(int**));
		for(i=0; i<=2; i++)
		{
			m_iTemp[i] = (int **)calloc(3, sizeof(int*));
		}
		for(i=0; i<=2; i++)
		{
			for(j=0; j<=2; j++)
			{
				m_iTemp[i][j] = (int *)calloc(3, sizeof(int));
			}
		}

		for(i=0; i<=2; i++)
			for(j=0; j<=2; j++)
				for(k=0; k<=2; k++)
					m_iTemp[i][j][k] = 0;

		m_iSize = (int*)malloc(sizeof(int) * 3);
	}


	m_file.Abort();

	CFileDialog fPartDlg(TRUE, _T("bin"), _T("*.bin"));
	//fPartDlg.m_ofn.lpstrTitle = _T("open data file");
	fPartDlg.DoModal();
	rc = m_file.Open(fPartDlg.GetPathName().GetBuffer(0), CFile::modeRead);
	if(rc == 0)
	{
		MessageBox(TEXT("Invalid Pathname!"), MB_OK, NULL);
		return;
	}
	
	if(m_bLoad == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++) 
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iMatrix[i][j]);
	
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iMatrix[i]);
		
		free(m_iMatrix);

		m_fBVF = 0;		//BV/TV
		m_fPBVF = 0;		//Plate volume/TV
		m_fRBVF = 0;		//Rod volume/TV
		m_fPThickness = 0;	//Plate Thickness(mm)
		m_fRDiameter = 0;	//Rod radius(mm)
		m_fPSurface = 0;	//Plate length(mm)
		m_fRLength = 0;	//Rod length(mm)
		m_fJuncNo = 0;		//Total Junction No/TV (1/mm^3)
		m_fRRJNo = 0;			//Rod-Rod Junction No/TV(1/mm^3)
		m_fRPJNo = 0;			//Rod-Plate Junction No/TV(1/mm^3)
		m_fPNo = 0;			//Plate No/TV(1/mm^3)
		m_fRNo = 0;			//Rod No/TV(1/mm^3)
		m_fPBVF_s = 0;	//pBV/TV of simplified model
		m_fRBVF_s = 0;	//rBV/TV of simplified model
	}

	if(m_bThinned == TRUE)
	{
		for(i=0; i<m_iSize[0]+4; i++)
			for(j=0; j<m_iSize[1]+4; j++)
				free(m_iPtType[i][j]);
		
		for(i=0; i<m_iSize[0]+4; i++)
			free(m_iPtType[i]);

		free(m_iPtType);
	}

	/*if(m_bCurveMeshed == TRUE)
	{
		for(i=0; i<1000; i++)
			free(m_iNodelist[i]);

		free(m_iNodelist);

		for(i=0; i<1000; i++)
			free(m_iCurvelist[i]);

		free(m_iCurvelist);
	}*/

	if(m_bPClustered == TRUE)
	{
		for(i=0; i <= m_iClusterNo; i++)
			free(m_iCluster[i]);

		for(i=0; i < m_iNodelistSize; i++)
			free(m_iNodelist[i]);

		for(i=0; i <= m_iTraNo; i++)
			free(m_iConnection[i]);

		free(m_iCluster);
		free(m_iNodelist);
		free(m_iConnection);
	}

	m_bThinned = FALSE;
	m_bArcThinned = FALSE;
	m_bClassified = FALSE;
	m_bDebugmode = FALSE;
	m_bRecovered = FALSE;
	m_bPClustered = FALSE;
	m_bCurveMeshed = FALSE;
	m_bTrasep = FALSE;

	/**************** Begin loading data *******************/
	m_strDisp.Format(_T("Start Loading Data"));
	UpdateData( FALSE );

	m_bLoad = TRUE;

	m_file.Seek(0, CFile::begin);
	m_file.Read(&m_char, 1);
	m_iSize[0] = (int)m_char*256;
	m_file.Read(&m_char,1);
	m_iSize[0] += (int)m_char;

	m_file.Seek(2, CFile::begin);
	m_file.Read(&m_char, 1);
	m_iSize[1] = (int)m_char*256;
	m_file.Read(&m_char,1);
	m_iSize[1] += (int)m_char;

	m_file.Seek(4, CFile::begin);
	m_file.Read(&m_char, 1);
	m_iSize[2] = (int)m_char*256;
	m_file.Read(&m_char,1);
	m_iSize[2] += (int)m_char;

/*	m_iXStart = 1;
	m_iYStart = 1;
	m_iZStart = 1;
	m_iXEnd = m_iSize[0];
	m_iYEnd = m_iSize[1];
	m_iZEnd = m_iSize[2];*/
	

	m_iMatrix = (int ***)calloc(m_iSize[0]+4, sizeof(int**));
	for(i=0; i<m_iSize[0]+4; i++)
	{
		m_iMatrix[i] = (int **)calloc(m_iSize[1]+4, sizeof(int*));
	}
	for(i=0; i<m_iSize[0]+4; i++)
	{
		for(j=0; j<m_iSize[1]+4; j++)
		{
			m_iMatrix[i][j] = (int *)calloc(m_iSize[2]+4, sizeof(int));
		}
	}

	m_file.Seek(6, CFile::begin);

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				m_file.Read(&m_char,1);
				m_iMatrix[i][j][k] = (int)m_char;
			}
		}
	}

	for(i=0; i<m_iSize[0]+4; i++)
		for(j=0; j<m_iSize[1]+4; j++)
			for(k=0; k<m_iSize[2]+4; k++)
				if(i < 2 || j < 2 || k < 2 || i > m_iSize[0] + 1 || j > m_iSize[1] + 1 || k > m_iSize[2] + 1)
					m_iMatrix[i][j][k] = 0;

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2; i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] ==0 && m_iMatrix[i-1][j][k] > 0 && m_iMatrix[i+1][j][k] > 0 && m_iMatrix[i][j-1][k] > 0 
					&& m_iMatrix[i][j+1][k] >0 && m_iMatrix[i][j][k-1] > 0 && m_iMatrix[i][j][k+1] > 0)
					m_iMatrix[i][j][k] = m_iMatrix[i-1][j][k];
			}
		}
	}

	OnCluster();

	m_strDisp.Format(_T("Data Loading Sucessfully!"));
	m_strSize.Format(_T("The Image Size is   x=%d,   y=%d,   z=%d"), m_iSize[0], m_iSize[1], m_iSize[2]);
	m_strDebug.Format(_T(""));
	UpdateData( FALSE );


/******************** End of Loading Data *************************/	
}

void CFormCommandView::OnToolPfcal() 
{
	// TODO: Add your command handler code here
					
/*	OnThinning();
	OnClassify();
	m_bRecovered = TRUE;

	int i,j,k,l;
	int iPlate = 0;
	int iRod = 0;
	int iTotal = 0;
	m_strDisp.Format("Begin Recover!");
	UpdateData( FALSE );

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iPtType[i][j][k] ==1 ||m_iPtType[i][j][k] ==2 ||m_iPtType[i][j][k] ==3)
				{
					m_iPtType[i][j][k] = 1;
				}
				else if(m_iPtType[i][j][k] ==5 ||m_iPtType[i][j][k] ==6 ||m_iPtType[i][j][k] ==7)
				{
					m_iPtType[i][j][k] = 2;
				}
				else if(m_iPtType[i][j][k] ==4)
				{
					m_iPtType[i][j][k] = -MAXNUM-1;
				}
				else if(m_iPtType[i][j][k] ==8)
				{
					m_iPtType[i][j][k] = -MAXNUM;
				}

			}
		}
	}

	for(l=m_iThr+1; l>-MAXNUM; l--)
	{
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2;i<m_iSize[0]+2; i++)
				{
					if(m_iPtType[i][j][k] == l)
					{
						Recover(m_iPtType, i, j, k, m_iSize);
					}
					
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				m_iMatrix[i][j][k] = 0;
				if(m_iPtType[i][j][k] <= 2 && m_iPtType[i][j][k] >=1)
				{
					if(m_iPtType[i][j][k] < 1.5)
					{
						m_iMatrix[i][j][k] = 1;
					}
					else
					{
						m_iMatrix[i][j][k] = 2;
					}
				}

			}
		}
	}

	int iChange = 0;
	while(iChange == 0)
	{
		iChange = 1;
		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2;i<m_iSize[0]+2; i++)
				{
					if(m_iPtType[i][j][k] == -MAXNUM-1)
					{
						m_iPtType[i][j][k] = (int)RecoverConnection(m_iPtType, m_iMatrix, i, j, k);
						if(m_iPtType[i][j][k] == 0)
						{
							m_iPtType[i][j][k] = -MAXNUM-1;
							iChange = 0;
						}
						m_iMatrix[i][j][k] = -MAXNUM-1;
					}
				}
			}
		}

		for(k=2; k<m_iSize[2]+2; k++)
		{
			for(j=2; j<m_iSize[1]+2; j++)
			{
				for(i=2;i<m_iSize[0]+2; i++)
				{
					if(m_iMatrix[i][j][k] == -MAXNUM-1 && m_iPtType[i][j][k] != -MAXNUM-1)
					{
						 m_iMatrix[i][j][k] = m_iPtType[i][j][k];
					}
				}
			}
		}
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] == 1 )
					iPlate++;
				else if(m_iMatrix[i][j][k] == 2)
					iRod++;
			}
		}
	}
	
	iTotal = iPlate + iRod;

	m_strDisp.Format("Finish Recover!");
	m_strDebug.Format("Plate Fraction: %f", ((float)iPlate)/((float)iTotal));
	UpdateData( FALSE );*/
}

void CFormCommandView::OnToolMultiselect() 
{
	// TODO: Add your command handler code here
		FILE *fp;
		unsigned char a,b;
		int i;

		if((fp = fopen ("tab3b", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
			tab3b[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab4a", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab4a[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab4b", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab4b[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab5", "r")) != NULL)
		{
			i = 0;
			while (fscanf (fp, "%d\n", &a) == 1)
				tab5[i++] = a;
			fclose (fp);
		}

		if((fp = fopen ("tab6", "r")) != NULL)
		{
			i=0;
			while (fscanf(fp, "%d %d\n", &a, &b) == 2) 
			{
				tab6[i][0] = a;
				tab6[i][1] = b;
				i = i + 1;
			}
			fclose(fp);
		}
		
	CFile m_file0;
	m_file0.Abort();

	CFileDialog fPartDlg2(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_ALLOWMULTISELECT );
	fPartDlg2.m_ofn.lpstrTitle = _T("Open the Data File");
	fPartDlg2.DoModal();
	
	POSITION pos = fPartDlg2.GetStartPosition();
    CString str;
	int x,y,z;
	char chr1;
	char chr3[2];
	char chr[5];
	char chr2[11];
	float temp;
	int itemp;
	int count=0;
	int tag = 0;
	
	while(pos)
    {
		//count++;
        // add the file paths to the list
		m_strPath = fPartDlg2.GetNextPathName(pos);
		OnLoad();
	}
		
	
}

void CFormCommandView::OnToolMesh() 
{
	CFormCommandView::OnThinning();
	CFormCommandView::OnClassify();
	CFormCommandView::OnArcthinning();
	CFormCommandView::OnArcClassify();
	CFormCommandView::OnPlatecluster();
	CFormCommandView::OnRecover();

}

int CFormCommandView::IsSC(int i, int j, int k, int ***matrix)	//identify whether a SC point has both plate and rod points as neighbors
{
	int a, b, c;
	for(a=0; a<=2; a++)
	{
		for(b=0; b<=2; b++)
		{
			for(c=0; c<=2; c++)
			{
				if(matrix[i-1+a][j-1+b][k-1+c] > 0 && matrix[i-1+a][j-1+b][k-1+c] < 2*MAXNUM+1)
				{
					if(matrix[i-1+a][j-1+b][k-1+c] == 2*MAXNUM)
						return 1;
					else if(m_iCluster[matrix[i-1+a][j-1+b][k-1+c]][1] == 1 && !(a==1 && b==1 && c==1))
					{
						return 1;
					}
				}
			}
		}
	}
	
	return 0;
	
}

int CFormCommandView::IsSE_TR(int i, int j, int k, int ***matrix) //identify the surface edge points which has more than two individual plate points as neighbors
{
	int a, b, c;
	int count = 0;
	int temp = 0;
	for(a=0; a<=2; a++)
	{
		for(b=0; b<=2; b++)
		{
			for(c=0; c<=2; c++)
			{
				if(matrix[i-1+a][j-1+b][k-1+c] < 2*MAXNUM && matrix[i-1+a][j-1+b][k-1+c] > 0)
				{
					if(count == 0 )
					{
						temp = matrix[i-1+a][j-1+b][k-1+c];
						count = 1;
					}
					else if(temp != matrix[i-1+a][j-1+b][k-1+c])
						return 1;
				}
			}
		}
	}
	return 0;
}

int CFormCommandView::IsSI_TR(int i, int j, int k, int ***matrix)  //identify the surface inner points which has more than three individual plate points as neighbors
{
	int a, b, c;
	int count1 = 0;
	int count2 = 0;
	int temp1 = 0;
	int temp2 = 0;

	for(a=0; a<=2; a++)
	{
		for(b=0; b<=2; b++)
		{
			for(c=0; c<=2; c++)
			{
				if(matrix[i-1+a][j-1+b][k-1+c] < 2*MAXNUM && matrix[i-1+a][j-1+b][k-1+c] > 0)
				{
					if(count1 == 0 )
					{
						temp1 = matrix[i-1+a][j-1+b][k-1+c];
						count1 = 1;
					}
					else if(count2 == 0 && temp1 != matrix[i-1+a][j-1+b][k-1+c])
					{
						temp2 = matrix[i-1+a][j-1+b][k-1+c];
						count2 = 1;
					}
					else if(temp1 != matrix[i-1+a][j-1+b][k-1+c] && temp2 != matrix[i-1+a][j-1+b][k-1+c])
						return 1;
				}
			}
		}
	}
	return 0;
}

int CFormCommandView::Node_Conn(int i, int j, int k, int ***CrPnts, int ***matrix, int ***PtType, int **Node)
{
	int a, b, c, d;
	int count = 5;
	int temp = 0;

	for(a=0; a<=2; a++)
	{
		for(b=0; b<=2; b++)
		{
			for(c=0; c<=2; c++)
			{
				if(CrPnts[i-1+a][j-1+b][k-1+c] <= 2*MAXNUM && CrPnts[i-1+a][j-1+b][k-1+c] > 0)
				{
					if(Node[matrix[i][j][k]][5] == 0)
					{
						if(CrPnts[i-1+a][j-1+b][k-1+c] == 2*MAXNUM)
							Node[matrix[i][j][k]][5] = PtType[i-1+a][j-1+b][k-1+c];
						else
							Node[matrix[i][j][k]][5] = CrPnts[i-1+a][j-1+b][k-1+c];
						count = 5;
					}
					else
					{
						temp = 0;
						count = 5;
						while(Node[matrix[i][j][k]][count]!=0)
						{
							if(Node[matrix[i][j][k]][count] == CrPnts[i-1+a][j-1+b][k-1+c] || Node[matrix[i][j][k]][count] == PtType[i-1+a][j-1+b][k-1+c])
								temp = 1;
							count++;
						}
						if(temp == 0)
						{
							if(CrPnts[i-1+a][j-1+b][k-1+c] != 2*MAXNUM)
								Node[matrix[i][j][k]][count] = CrPnts[i-1+a][j-1+b][k-1+c];
							else
								Node[matrix[i][j][k]][count] = PtType[i-1+a][j-1+b][k-1+c];
						}
					}
				}
			}
		}
	}

	return count+1-5;
}

float CFormCommandView::GetDistance(int i, int j, int k, int *ClusterNode, int **Node)
{
	int a;
	float d = 0.0;
	for(a=1; a<=ClusterNode[0]; a++)
	{
		d += sqrtf(((float)i-Node[ClusterNode[a]][1])*((float)i-Node[ClusterNode[a]][1]) + ((float)j-Node[ClusterNode[a]][2])*((float)j-Node[ClusterNode[a]][2]) + ((float)k-Node[ClusterNode[a]][3])*((float)k-Node[ClusterNode[a]][3]));
	}
	return d;
}


int CFormCommandView::GetPlateNormal(int i, int **ClusterNode, int **Node, float **Norm)
{
	int NodeNo = ClusterNode[i][0];
	int a, b, c;
	float length1, length2, length3;
	float s, Area;
	float MaxArea = 0;
	int Max_a, Max_b, Max_c;

	//Get the biggest triangle within a plate cluster, the node IDs of the triangle is Max_a, Max_b and Max_c
	for(a=1; a<=NodeNo; a++)
	{
		for(b=a+1; b<=NodeNo; b++)
		{
			for(c=b+1; c<=NodeNo; c++)
			{
				Area = GetTriangleArea(ClusterNode[i][a], ClusterNode[i][b], ClusterNode[i][c], Node);
				if(Area > MaxArea)
				{
					MaxArea = Area;
					Max_a = ClusterNode[i][a];
					Max_b = ClusterNode[i][b];
					Max_c = ClusterNode[i][c];
				}
			}
		}
	}

	if(Max_a<0 || Max_b<0 || Max_c<0)
	{
		Max_a=Max_a;
		return 0;
	}
	//Get the normal of the biggest trirangle
	if(GetTriangleNormal(Max_a, Max_b, Max_c, Node, Norm[i])==0)
		return 0;
	else
		return 1;
}
				

float CFormCommandView::GetTriangleArea(int a, int b, int c, int **Node)
{
	float length1, length2, length3, s;

	length1 = sqrtf(float((Node[a][1]-Node[b][1])*(Node[a][1]-Node[b][1])+(Node[a][2]-Node[b][2])*(Node[a][2]-Node[b][2])+(Node[a][3]-Node[b][3])*(Node[a][3]-Node[b][3])));
	length2 = sqrtf(float((Node[a][1]-Node[c][1])*(Node[a][1]-Node[c][1])+(Node[a][2]-Node[c][2])*(Node[a][2]-Node[c][2])+(Node[a][3]-Node[c][3])*(Node[a][3]-Node[c][3])));
	length3 = sqrtf(float((Node[b][1]-Node[c][1])*(Node[b][1]-Node[c][1])+(Node[b][2]-Node[c][2])*(Node[b][2]-Node[c][2])+(Node[b][3]-Node[c][3])*(Node[b][3]-Node[c][3])));
	s = 0.5*(length1 + length2 + length3);
	return sqrtf(s*(s-length1)*(s-length2)*(s-length3));
}
				
int CFormCommandView::GetTriangleNormal(int a, int b, int c, int **Node, float *Norm)
{
	float a1, a2, a3, b1, b2, b3, c1, c2, c3, n1, n2, n3;
	a1 = (float)Node[a][1];
	a2 = (float)Node[b][1];
	a3 = (float)Node[c][1];

	b1 = (float)Node[a][2];
	b2 = (float)Node[b][2];
	b3 = (float)Node[c][2];

	c1 = (float)Node[a][3];
	c2 = (float)Node[b][3];
	c3 = (float)Node[c][3];

	if(a1!=a2 && (b3-b1)!=(a3-a1)/(a2-a1)*(b2-b1))
	{
		n2 = -((c3-c1)-(a3-a1)/(a2-a1)*(c2-c1))/((b3-b1)-(a3-a1)/(a2-a1)*(b2-b1));
		n1 = (b2-b1)/(a1-a2)*n2+(c2-c1)/(a1-a2);

		Norm[0] = n1/sqrtf(n1*n1+n2*n2+1);
		Norm[1] = n2/sqrtf(n1*n1+n2*n2+1);
		Norm[2] = 1/sqrtf(n1*n1+n2*n2+1);
	}
	else if(b1!=b2 && (a3-a1)!=(b3-b1)/(b2-b1)*(a2-a1))
	{
		n1 = -((c3-c1)-(b3-b1)/(b2-b1)*(c2-c1))/((a3-a1)-(b3-b1)/(b2-b1)*(a2-a1));
		n2 = (a2-a1)/(b1-b2)*n1+(c2-c1)/(b1-b2);

		Norm[0] = n1/sqrtf(n1*n1+n2*n2+1);
		Norm[1] = n2/sqrtf(n1*n1+n2*n2+1);
		Norm[2] = 1/sqrtf(n1*n1+n2*n2+1);
	}
	else if(c1!=c2 && (a3-a1)!=(c3-c1)/(c2-c1)*(a2-a1))
	{
		n1 = -((b3-b1)-(c3-c1)/(c2-c1)*(b2-b1))/((a3-a1)-(c3-c1)/(c2-c1)*(a2-a1));
		n3 = (a2-a1)/(c1-c2)*n1+(b2-b1)/(c1-c2);

		Norm[0] = n1/sqrtf(n1*n1+n3*n3+1);
		Norm[1] = 1/sqrtf(n1*n1+n3*n3+1);
		Norm[2] = n3/sqrtf(n1*n1+n3*n3+1);
	}
	else if (a1==a2 && a2==a3)
	{
		Norm[0] = 1.0;
		Norm[1] = 0;
		Norm[2] = 0;
	}
	else if(b1==b2 && b2==b3)
	{
		Norm[0] = 0;
		Norm[1] = 1.0;
		Norm[2] = 0;
	}
	else if(c1==c2 && c2==c3)
	{
		Norm[0] = 0;
		Norm[1] = 0;
		Norm[2] = 1.0;
	}
	else if(a1==a2 && b1==b2 && c1==c3)
	{
		Norm[0] = float(b3-b1)/sqrt(powf(float(b3-b1),2.0)+powf(float(a3-a1),2.0));
		Norm[1] = float(a1-a3)/sqrt(powf(float(b3-b1),2.0)+powf(float(a3-a1),2.0));
		Norm[2] = 1.0;
	}
	else if(a1==a2 && c1==c2 && b1==b3)
	{
		Norm[0] = float(c3-c1)/sqrt(powf(float(c3-c1),2.0)+powf(float(a3-a1),2.0));
		Norm[1] = 1.0;
		Norm[2] = float(a1-a3)/sqrt(powf(float(c3-c1),2.0)+powf(float(a3-a1),2.0));
	}
	else if(b1==b2 && c1==c2 && a1==a3)
	{
		Norm[0] = 1.0;
		Norm[1] = float(c3-c1)/sqrt(powf(float(c3-c1),2.0)+powf(float(b3-b1),2.0));
		Norm[2] = float(b1-b3)/sqrt(powf(float(c3-c1),2.0)+powf(float(b3-b1),2.0));
	}
	else if(a1==a3 && b1==b3 && c1==c2)
	{
		Norm[0] = float(b2-b1)/sqrt(powf(float(b2-b1),2.0)+powf(float(a2-a1),2.0));
		Norm[1] = float(a1-a2)/sqrt(powf(float(b2-b1),2.0)+powf(float(a2-a1),2.0));
		Norm[2] = 1.0;
	}
	else if(a1==a3 && c1==c3 && b1==b2)
	{
		Norm[0] = float(c2-c1)/sqrt(powf(float(c2-c1),2.0)+powf(float(a2-a1),2.0));
		Norm[1] = 1.0;
		Norm[2] = float(a1-a2)/sqrt(powf(float(c2-c1),2.0)+powf(float(a2-a1),2.0));
	}
	else if(b1==b3 && c1==c3 && a1==a2)
	{
		Norm[0] = 1.0;
		Norm[1] = float(c2-c1)/sqrt(powf(float(c2-c1),2.0)+powf(float(b2-b1),2.0));
		Norm[2] = float(b1-b2)/sqrt(powf(float(c2-c1),2.0)+powf(float(b2-b1),2.0));
	}
	else if(((c1==c2) ||(c1==c3)) && (b3-b1)==(a3-a1)/(a2-a1)*(b2-b1))
	{
		Norm[0] = float(b2-b1)/sqrt(powf(float(b2-b1),2.0)+powf(float(a2-a1),2.0));
		Norm[1] = float(a1-a2)/sqrt(powf(float(b2-b1),2.0)+powf(float(a2-a1),2.0));
		Norm[2] = 1.0;
	}
	else if(((b1==b2) || (b1==b3)) && (a3-a1)==(c3-c1)/(c2-c1)*(a2-a1))
	{
		Norm[0] = float(c2-c1)/sqrt(powf(float(c2-c1),2.0)+powf(float(a2-a1),2.0));
		Norm[1] = 1.0;
		Norm[2] = float(a1-a2)/sqrt(powf(float(c2-c1),2.0)+powf(float(a2-a1),2.0));
	}
	else if(((a1==a2) || (a1==a3)) && (c3-c1)==(b3-b1)/(b2-b1)*(c2-c1))
	{
		Norm[0] = 1.0;
		Norm[1] = float(c2-c1)/sqrt(powf(float(c2-c1),2.0)+powf(float(b2-b1),2.0));
		Norm[2] = float(b1-b2)/sqrt(powf(float(c2-c1),2.0)+powf(float(b2-b1),2.0));
	}
	else
		return 0;
		
	return 1;
}

int CFormCommandView::Delaunay(int ClusterID, int *ClusterNode, int **Node, float *Norm, float Size, int Temp, int TriPointer, int **Triangle)
{
	int i, j, k;
	int NodeNo = ClusterNode[0];

	float **TriNode;
	TriNode = (float **)calloc(NodeNo+1, sizeof(float*));
	for(i=0; i<=NodeNo; i++)
	{
		TriNode[i] = (float *)calloc(4, sizeof(float));
		for(j=0; j<=3; j++)
			TriNode[i][j] = 0;
	}

	for(i=1; i<=NodeNo; i++)
	{
		TriNode[i][0] = ClusterNode[i];
		for(j=1; j<=3; j++)
			TriNode[i][j] = Node[ClusterNode[i]][j];
	}

	//***************2D Projection***************//
	float e11, e12, e13, e31, e32, e33;
	float n1 = Norm[0];
	float n2 = Norm[1];
	float n3 = Norm[2];

	e11 = -n2/sqrtf(n2*n2+n1*n1);
	e12 = n1/sqrtf(n2*n2+n1*n1);
	e13 = 0;

	e31 = n1*n3/sqrtf(n1*n1*n3*n3+n2*n2*n3*n3+(n1*n1+n2*n2)*(n1*n1+n2*n2));
	e32 = n2*n3/sqrtf(n1*n1*n3*n3+n2*n2*n3*n3+(n1*n1+n2*n2)*(n1*n1+n2*n2));
	e33 = -(n1*n1+n2*n2)/sqrtf(n1*n1*n3*n3+n2*n2*n3*n3+(n1*n1+n2*n2)*(n1*n1+n2*n2));

	float x,y;

	for(i=2; i<=NodeNo; i++)
	{
		x = e11*(TriNode[i][1]-TriNode[1][1]) + e12*(TriNode[i][2]-TriNode[1][2]) + e13*(TriNode[i][3]-TriNode[1][3]);
		y = e31*(TriNode[i][1]-TriNode[1][1]) + e32*(TriNode[i][2]-TriNode[1][2]) + e33*(TriNode[i][3]-TriNode[1][3]);

		TriNode[i][1] = x;
		TriNode[i][2] = y;
		TriNode[i][3] = 0;
	}

	for(i=1; i<=3; i++)
		TriNode[1][i] = 0;

	//*******************Triangulation*******************//

	int a, b;
	float a1, a2, a3, b1, b2, b3, cx, cy, r;

	int TriNo = NodeNo*10;
	int **Tri;
	Tri = (int **)calloc(TriNo+1, sizeof(int));
	for(i=0; i<=TriNo+1; i++)
	{
		Tri[i] = (int *)calloc(4, sizeof(int));
		for(j=0; j<=3; j++)
			Tri[i][j] = 0;
	}

	int count = 0;
	float TriArea = 0;

	for(i=1; i<=NodeNo; i++)
	{
		for(j=i+1; j<=NodeNo; j++)
		{
			for(k=j+1; k<=NodeNo; k++)
			{	
				a1 = TriNode[i][1];
				b1 = TriNode[i][2];
				a2 = TriNode[j][1];
				b2 = TriNode[j][2];
				a3 = TriNode[k][1];
				b3 = TriNode[k][2];

				if((a1==a2 && a2==a3) || (b1==b2 && b2==b3))
					b = 0;
				else
				{
					if(a1==a2 && b1==b2)
					{
						cx = (a1+a3)/2;
						cy = (b1+b3)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a2==a3 && b2==b3)
					{
						cx = (a1+a2)/2;
						cy = (b1+b2)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a1==a3 && b1==b3)
					{
						cx = (a3+a2)/2;
						cy = (b3+b2)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a1==a2 && b1==b3)
					{
						cx = (a2+a3)/2;
						cy = (b2+b3)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a1==a2 && b3==b2)
					{
						cx = (a1+a3)/2;
						cy = (b1+b3)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a1==a3 && b1==b2)
					{
						cx = (a2+a3)/2;
						cy = (b2+b3)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a1==a3 && b2==b3)
					{
						cx = (a1+a2)/2;
						cy = (b1+b2)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a2==a3 && b1==b2)
					{
						cx = (a1+a3)/2;
						cy = (b1+b3)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a2==a3 && b1==b3)
					{
						cx = (a1+a2)/2;
						cy = (b1+b2)/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a1==a2)
					{
						cy = (b1+b2)/2;
						cx = (a2+a3-(b2+b3-2*cy)*(b3-b2)/(a2-a3))/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a2==a3)
					{
						cy = (b3+b2)/2;
						cx = (a2+a1-(b2+b1-2*cy)*(b1-b2)/(a2-a1))/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(a1==a3)
					{
						cy = (b1+b3)/2;
						cx = (a3+a2-(b3+b2-2*cy)*(b2-b3)/(a3-a2))/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(b1==b2)
					{
						cx = (a1+a2)/2;
						cy = (b2+b3-(a2+a3-2*cx)*(a3-a2)/(b2-b3))/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(b2==b3)
					{
						cx = (a3+a2)/2;
						cy = (b2+b1-(a2+a1-2*cx)*(a1-a2)/(b2-b1))/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else if(b1==b3)
					{
						cx = (a1+a3)/2;
						cy = (b2+b3-(a2+a3-2*cx)*(a3-a2)/(b2-b3))/2;
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}
					else
					{
						cx = (b3-b1+(a2*a2-a3*a3)/(b2-b3)-(a1*a1-a2*a2)/(b1-b2))/2/((a2-a3)/(b2-b3)-(a1-a2)/(b1-b2));
						cy = (a3-a1+(b2*b2-b3*b3)/(a2-a3)-(b1*b1-b2*b2)/(a1-a2))/2/((b2-b3)/(a2-a3)-(b1-b2)/(a1-a2));
						r = sqrtf((a1-cx)*(a1-cx)+(b1-cy)*(b1-cy));
					}

					b=1;
					for(a=1; a<=NodeNo; a++)
					{
						if(a!=i && a!=j && a!=k)
						{
							if(sqrtf((TriNode[a][1]-cx)*(TriNode[a][1]-cx)+(TriNode[a][2]-cy)*(TriNode[a][2]-cy)) < r)
								b = 0;
						}
					}
				}

				if(b==1)
				{
					count++;
					if((a2-a1)*(b3-b2)>(a3-a2)*(b2-b1))
					{
						Tri[count][1] = TriNode[i][0];
						Tri[count][2] = TriNode[j][0];
						Tri[count][3] = TriNode[k][0];
						TriArea += GetTriangleArea(Tri[count][1], Tri[count][2], Tri[count][3], Node);
					}
					else
					{
						Tri[count][1] = TriNode[i][0];
						Tri[count][2] = TriNode[k][0];
						Tri[count][3] = TriNode[j][0];
						TriArea += GetTriangleArea(Tri[count][1], Tri[count][2], Tri[count][3], Node);
					}
				}
			}
		}
	}
	
	if((TriArea < (Size/2.0)) && Temp == 0)
		return 0;
	else
	{
		for(i=1; i<=count; i++)
		{
			Triangle[TriPointer][0] = ClusterID;
			Triangle[TriPointer][1] = Tri[i][1];
			Triangle[TriPointer][2] = Tri[i][2];
			Triangle[TriPointer][3] = Tri[i][3];
			TriPointer++;
		}
		return TriPointer;
	}
}


int CFormCommandView::CompareNode(int a, int b, int **ClusterNode, int **Node)
{
	int i, j, count;
	if(Node[a][0] != Node[b][0] || Node[a][4] != Node[b][4])
		return 0;
	else
	{
		for(i=5; i<=5+Node[a][4]; i++)
		{
			count = 0;
			for(j=5; j<=5+Node[a][4]; j++)
			{
				if(Node[a][i] == Node[a][j])
					count = 1;
			}
			if(count == 0)
				return 0;
		}
	}

	if(a>b)
	{
		Node[a][0] = 0;
		Node[a][1] = b;
		for(i=5; i<=5+Node[b][0]; i++)
		{
			count = 1;
			while(count != 0)
			{
				if(ClusterNode[i][count] == a && count != ClusterNode[i][0])
				{
					ClusterNode[i][count] = ClusterNode[i][ClusterNode[i][0]];
					ClusterNode[i][ClusterNode[i][0]] = 0;
					count = 0;
				}
				else if(ClusterNode[i][count] == a && count == ClusterNode[i][0])
				{
					ClusterNode[i][count] = 0;
					count = 0;
				}
				else if(count>ClusterNode[i][0])
				{
					//MessageBox(_T("mistake10!"), NULL, MB_OK);
					count = 0;
				}
				else
					count++;
			}
		}
	}
	return 1;
}
		
float CFormCommandView::GetRodVolume(int *Node1, int *Node2, float th)
{
	float x1 = float(Node1[1]);
	float y1 = float(Node1[2]);
	float z1 = float(Node1[3]);
	float x2 = float(Node2[1]);
	float y2 = float(Node2[2]);
	float z2 = float(Node2[3]);

	float length;
	length = sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));

	float volume = length * th * th * 3.1415927;
	
	return volume;
}

float CFormCommandView::GetPlateVolume(int *Node1, int *Node2, int *Node3, float th)
{
	float x1 = float(Node1[1]);
	float y1 = float(Node1[2]);
	float z1 = float(Node1[3]);
	float x2 = float(Node2[1]);
	float y2 = float(Node2[2]);
	float z2 = float(Node2[3]);
	float x3 = float(Node3[1]);
	float y3 = float(Node3[2]);
	float z3 = float(Node3[3]);

	float a	= sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
	float b = sqrtf((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3)+(z1-z3)*(z1-z3));
	float c = sqrtf((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3)+(z2-z3)*(z2-z3));
	float s = (a+b+c)/2.0;

	if(sqrtf(s*(s-a)*(s-b)*(s-c))<0)
		s=s;

	float volume = sqrtf(s*(s-a)*(s-b)*(s-c)) * th;
	
	return volume;
}

int CFormCommandView::Connectivity(int Beam3No, int **Beam3, int Beam2No, int **Beam2, int ShellNo, int **Shell, int NodeNo, int *NodeLabel, int *LabelList, int **NodeConn)
{
	int i, j, k;
	for(i=1; i<=Beam3No; i++)
	{
		NodeConn[Beam3[i][1]][Beam3[i][2]] = 1;
		NodeConn[Beam3[i][2]][Beam3[i][1]] = 1;
	}

	for(i=1; i<=Beam2No; i++)
	{
		NodeConn[Beam2[i][1]][Beam2[i][2]] = 1;
		NodeConn[Beam2[i][2]][Beam2[i][1]] = 1;
	}

	for(i=1; i<=ShellNo; i++)
	{
		NodeConn[Shell[i][1]][Shell[i][2]] = 1;
		NodeConn[Shell[i][2]][Shell[i][1]] = 1;
		NodeConn[Shell[i][1]][Shell[i][3]] = 1;
		NodeConn[Shell[i][3]][Shell[i][1]] = 1;
		NodeConn[Shell[i][2]][Shell[i][3]] = 1;
		NodeConn[Shell[i][3]][Shell[i][2]] = 1;
	}

	int inc = 1;
	int pointer = 1;	//pointer of labellist
	NodeLabel[1] = 1;	//Labeled
	LabelList[1] = 1;

	if(pointer<NodeNo)
	{
		while(LabelList[inc] != 0)
		{
			for(i=1; i<=NodeNo; i++)
			{
				if(NodeConn[LabelList[inc]][i] == 1 && NodeLabel[i] == 0)
				{
					NodeLabel[i] = 1;
					LabelList[pointer] = i;
					pointer++;
				}
			}
			inc++;
		}
	}



	return pointer-1;
}

int CFormCommandView::AbaqusInput()
{
	int i, j, k;

	m_iTotalBeamNo = 0;
	m_i3NodeBeamNo = 0;
	m_i2NodeBeamNo = 0;
	m_iPlateNo = 0;
	m_iNodeNo = 0;
	m_iShellNo = m_iTriPointer-1;

	int itemp;
	float ftemp, ftemp1, ftemp2;

	//Lookup Tabel  <m_iCluster>--> <Plate>
	int *m_iPlateReplace = (int *)calloc(m_iTraNo+1, sizeof(int));

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_iCluster[i][2] != 0 && m_iClusterNode[i][0] >= 3)
		{
			m_iPlateNo++;
			m_iPlateReplace[i] = m_iPlateNo;
		}
		else if(m_iCluster[i][1] == 2 && m_iCluster[i][2] != 0 && m_iClusterNode[i][0] >=2 && m_iClusterNode[i][1]!= m_iClusterNode[i][2])
		{
			ftemp = sqrtf(powf(float(m_iNode[m_iClusterNode[i][1]][1]-m_iNode[m_iClusterNode[i][2]][1]),2.0) 
						+ powf(float(m_iNode[m_iClusterNode[i][1]][2]-m_iNode[m_iClusterNode[i][2]][2]),2.0) 
						+ powf(float(m_iNode[m_iClusterNode[i][1]][3]-m_iNode[m_iClusterNode[i][2]][3]),2.0));
			if(ftemp > 10.0)
				m_i3NodeBeamNo++;
			else
				m_i2NodeBeamNo++;
		}
	}

	m_iTotalBeamNo = m_i3NodeBeamNo + m_i2NodeBeamNo;

	m_i3NodeBeam = (int **)calloc(m_i3NodeBeamNo+1, sizeof(int*));
	for(i=0; i<=m_i3NodeBeamNo; i++)
	{
		m_i3NodeBeam[i] = (int *)calloc(4, sizeof(int));
	}

	for(i=0; i<=m_i3NodeBeamNo; i++)
		for(j=0; j<=3; j++)
			m_i3NodeBeam[i][j] = 0;

	m_i2NodeBeam = (int **)calloc(m_i2NodeBeamNo+1, sizeof(int*));
	for(i=0; i<=m_i2NodeBeamNo; i++)
	{
		m_i2NodeBeam[i] = (int *)calloc(3, sizeof(int));
	}

	for(i=0; i<=m_i2NodeBeamNo; i++)
		for(j=0; j<=2; j++)
			m_i2NodeBeam[i][j] = 0;

	int count1 = 1;
	int count2 = 1;
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 2 && m_iCluster[i][2] != 0 && m_iClusterNode[i][0] >=2 && m_iClusterNode[i][1]!= m_iClusterNode[i][2])
		{
			ftemp = sqrtf(powf(float(m_iNode[m_iClusterNode[i][1]][1]-m_iNode[m_iClusterNode[i][2]][1]),2.0) 
						+ powf(float(m_iNode[m_iClusterNode[i][1]][2]-m_iNode[m_iClusterNode[i][2]][2]),2.0) 
						+ powf(float(m_iNode[m_iClusterNode[i][1]][3]-m_iNode[m_iClusterNode[i][2]][3]),2.0));
			if(ftemp > 10.0)
			{
				m_i3NodeBeam[count1][0] = i;
				m_i3NodeBeam[count1][1] = m_iClusterNode[i][1];
				m_i3NodeBeam[count1][2] = m_iClusterNode[i][2];
				m_i3NodeBeam[count1][3] = 0;
				count1++;
			}
			else
			{
				m_i2NodeBeam[count2][0] = i;
				m_i2NodeBeam[count2][1] = m_iClusterNode[i][1];
				m_i2NodeBeam[count2][2] = m_iClusterNode[i][2];
				count2++;
			}
		}
	}
	
	//Finding the middle node for long rod
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iCrPnts[i][j][k] > 0 && m_iCrPnts[i][j][k] < 2*MAXNUM)
				{
					itemp = m_iCrPnts[i][j][k];
					if(m_iCluster[itemp][1] == 2 && m_iCluster[itemp][2] != 0 && m_iClusterNode[itemp][0] >=2 && m_iClusterNode[i][1]!= m_iClusterNode[i][2] )
					{
						ftemp = sqrtf(powf(float(m_iNode[m_iClusterNode[itemp][1]][1]-m_iNode[m_iClusterNode[itemp][2]][1]),2.0) 
									+ powf(float(m_iNode[m_iClusterNode[itemp][1]][2]-m_iNode[m_iClusterNode[itemp][2]][2]),2.0) 
									+ powf(float(m_iNode[m_iClusterNode[itemp][1]][3]-m_iNode[m_iClusterNode[itemp][2]][3]),2.0));
						if(ftemp > 10.0)
						{
							if(m_iClusterNode[itemp][97] == 0 && m_iClusterNode[itemp][98] == 0 && m_iClusterNode[itemp][99] == 0)
							{
								m_iClusterNode[itemp][97] = i;
								m_iClusterNode[itemp][98] = j;
								m_iClusterNode[itemp][99] = k;
							}
							else
							{
								ftemp1 = sqrtf(powf((float(i)-float(m_iNode[m_iClusterNode[itemp][1]][1]+m_iNode[m_iClusterNode[itemp][2]][1])/2.0), 2.0)
											 + powf((float(j)-float(m_iNode[m_iClusterNode[itemp][1]][2]+m_iNode[m_iClusterNode[itemp][2]][2])/2.0), 2.0)
											 + powf((float(k)-float(m_iNode[m_iClusterNode[itemp][1]][3]+m_iNode[m_iClusterNode[itemp][2]][3])/2.0), 2.0));
								ftemp2 = sqrtf(powf((float(m_iClusterNode[itemp][97])-float(m_iNode[m_iClusterNode[itemp][1]][1]+m_iNode[m_iClusterNode[itemp][2]][1])/2.0), 2.0)
											 + powf((float(m_iClusterNode[itemp][98])-float(m_iNode[m_iClusterNode[itemp][1]][2]+m_iNode[m_iClusterNode[itemp][2]][2])/2.0), 2.0)
											 + powf((float(m_iClusterNode[itemp][99])-float(m_iNode[m_iClusterNode[itemp][1]][3]+m_iNode[m_iClusterNode[itemp][2]][3])/2.0), 2.0));
								if(ftemp1<ftemp2)
								{
									m_iClusterNode[itemp][97] = i;
									m_iClusterNode[itemp][98] = j;
									m_iClusterNode[itemp][99] = k;
								}
							}
						}
					}
				}
			}
		}
	}

	int count;
	for(i=1; i<=m_i3NodeBeamNo; i++)
	{
		count = 1;
		itemp = 0;
		while(itemp == 0)
		{
			if(m_iNode[count][0] == 0)
				itemp = 1;
			else
				count++;
		}
		m_iNode[count][0] = 8;
		m_iNode[count][1] = m_iClusterNode[m_i3NodeBeam[i][0]][97];
		m_iNode[count][2] = m_iClusterNode[m_i3NodeBeam[i][0]][98];
		m_iNode[count][3] = m_iClusterNode[m_i3NodeBeam[i][0]][99];

		m_iCrPnts[m_iNode[count][1]][m_iNode[count][2]][m_iNode[count][3]] = 2*MAXNUM+8;
		
		m_i3NodeBeam[i][3] = count;
	}

	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				m_iMatrix[i][j][k] = 0;
			}
		}
	}

	for(i=1; i<m_iNodeSize; i++)
	{
		if(m_iNode[i][0] != 0)
		{
			m_iNodeNo++;
			m_iMatrix[m_iNode[i][1]][m_iNode[i][2]][m_iNode[i][3]] = i;
		}
	}
	
	//Lookup Table  <m_iCluster>--> <Node>
	int *iNodeReplace = (int *)calloc(m_iNodeSize, sizeof(int));
	//Lookup Tabel  <Node>--> <m_iCluster>
	m_iNewNode = (int *)calloc(m_iNodeNo+1, sizeof(int));

	count = 1;
	for(k=2; k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			for(i=2;i<m_iSize[0]+2; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					m_iNewNode[count] = m_iMatrix[i][j][k];
					iNodeReplace[m_iMatrix[i][j][k]] = count;
					count++;
				}
			}
		}
	}

	for(i=1; i<=m_i3NodeBeamNo; i++)
	{
		m_i3NodeBeam[i][1] = iNodeReplace[m_i3NodeBeam[i][1]];
		m_i3NodeBeam[i][2] = iNodeReplace[m_i3NodeBeam[i][2]];
		m_i3NodeBeam[i][3] = iNodeReplace[m_i3NodeBeam[i][3]];
	}

	for(i=1; i<=m_i2NodeBeamNo; i++)
	{
		m_i2NodeBeam[i][1] = iNodeReplace[m_i2NodeBeam[i][1]];
		m_i2NodeBeam[i][2] = iNodeReplace[m_i2NodeBeam[i][2]];
	}

	for(i=1; i<=m_iShellNo; i++)
	{
		m_iTriangle[i][1] = iNodeReplace[m_iTriangle[i][1]];
		m_iTriangle[i][2] = iNodeReplace[m_iTriangle[i][2]];
		m_iTriangle[i][3] = iNodeReplace[m_iTriangle[i][3]];
	}

	//*****************************For connectivity test***************************//
	m_iNodeLabel = (int *)calloc(m_iNodeNo+1, sizeof(int));		
	m_iLabelList = (int *)calloc(m_iNodeNo+1, sizeof(int));
	m_iNodeConn = (int **)calloc(m_iNodeNo+1, sizeof(int*));
	for(i=0; i<=m_iNodeNo; i++)
	{
		m_iNodeConn[i] = (int *)calloc(m_iNodeNo+1, sizeof(int));
	}

	for(i=0; i<=m_iNodeNo; i++)
	{
		m_iNodeLabel[i] = 1;
		m_iLabelList[i] = 0;
		for(j=0; j<=m_iNodeNo; j++)
		{
			m_iNodeConn[i][j] = 0;
		}
	}
	//Connectivity(m_i3NodeBeamNo, m_i3NodeBeam, m_i2NodeBeamNo, m_i2NodeBeam, m_iShellNo, m_iTriangle, m_iNodeNo, m_iNodeLabel, m_iLabelList, m_iNodeConn);

	for(i=2;i<m_iSize[0]+2; i++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			//bottom
			for(k=2; k<2+15; k++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] != 8)
					{
						m_iNode[m_iMatrix[i][j][k]][99] = MAXNUM;
						//k=2+10;
					}
				}
			}
			//top
			for(k=m_iSize[2]+1; k>m_iSize[2]+1-15;k--)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] == 1 || m_iNode[m_iMatrix[i][j][k]][0] == 2 ||m_iNode[m_iMatrix[i][j][k]][0] == 3)//!= 8 && m_iNode[m_iMatrix[i][j][k]][0] != 4 && m_iNode[m_iMatrix[i][j][k]][0] != 5)
					{
						m_iNode[m_iMatrix[i][j][k]][99] = MAXNUM+1;
						//k=m_iSize[2]+1-10;
					}
				}
			}
		}
	}
	
	for(k=2;k<m_iSize[2]+2; k++)
	{
		for(j=2; j<m_iSize[1]+2; j++)
		{
			//bottom_x
			for(i=2; i<2+10; i++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] != 8) 
					{
						m_iNode[m_iMatrix[i][j][k]][99] = MAXNUM+2;
						//i=2+10;
					}
				}
			}
			//top_x
			for(i=m_iSize[0]+1; i>m_iSize[0]+1-10;i--)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] != 8) 
					{
						m_iNode[m_iMatrix[i][j][k]][99] = MAXNUM+3;
						//i=m_iSize[0]+1-10;
					}
				}
			}
		}
	}

	for(k=2;k<m_iSize[2]+2; k++)
	{
		for(i=2; i<m_iSize[0]+2; i++)
		{
			//bottom_y
			for(j=2; j<2+10; j++)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] != 8) 
					{
						m_iNode[m_iMatrix[i][j][k]][99] = MAXNUM+4;
						//j=2+10;
					}
				}
			}
			//top_y
			for(j=m_iSize[1]+1; j>m_iSize[1]+1-10;j--)
			{
				if(m_iMatrix[i][j][k] > 0)
				{
					if(m_iNode[m_iMatrix[i][j][k]][0] != 8) 
					{
						m_iNode[m_iMatrix[i][j][k]][99] = MAXNUM+5;
						//j=m_iSize[1]+1-10;
					}
				}
			}
		}
	}
	

	//Calculate Bone Volume Fraction for Plate-Rod Model
	float fSize1 = float(m_resolution[0])/1000.0;
	float fSize2 = float(m_resolution[1])/1000.0;
	float fSize3 = float(m_resolution[2])/1000.0;


	//*******************************************************************************//
	m_fPBVF_s = 0.0;
	m_fRBVF_s = 0.0;
	for(i=1; i<=m_i3NodeBeamNo; i++)
	{
		if(m_iNodeLabel[m_i3NodeBeam[i][1]] != 0 && m_iNodeLabel[m_i3NodeBeam[i][2]] != 0)
		{
			if(m_fTh[m_i3NodeBeam[i][0]][0]/1000.0>0)
				m_fRBVF_s += GetRodVolume(m_iNode[m_iNewNode[m_i3NodeBeam[i][1]]], m_iNode[m_iNewNode[m_i3NodeBeam[i][2]]], m_fTh[m_i3NodeBeam[i][0]][0]/2.0);
			//else
				//m_fRBVF_s += GetRodVolume(m_iNode[m_iNewNode[m_i3NodeBeam[i][1]]], m_iNode[m_iNewNode[m_i3NodeBeam[i][2]]], 0.05/fSize1);
		}
	}

	for(i=1; i<=m_i2NodeBeamNo; i++)
	{
		if(m_iNodeLabel[m_i2NodeBeam[i][1]] != 0 && m_iNodeLabel[m_i2NodeBeam[i][2]] != 0)
		{
			if(m_fTh[m_i2NodeBeam[i][0]][0]/1000.0>0)
				m_fRBVF_s += GetRodVolume(m_iNode[m_iNewNode[m_i2NodeBeam[i][1]]], m_iNode[m_iNewNode[m_i2NodeBeam[i][2]]], m_fTh[m_i2NodeBeam[i][0]][0]/2.0);
			//else
				//m_fRBVF_s += GetRodVolume(m_iNode[m_iNewNode[m_i2NodeBeam[i][1]]], m_iNode[m_iNewNode[m_i2NodeBeam[i][2]]], 0.05/fSize1);
		}
	}

	for(i=1; i<=m_iShellNo; i++)
	{
		if(m_iNodeLabel[m_iTriangle[i][1]] != 0 && m_iNodeLabel[m_iTriangle[i][2]] != 0 && m_iNodeLabel[m_iTriangle[i][3]] != 0)
		{
			if(m_fTh[m_iTriangle[i][0]][0]/1000.0>0)
				m_fPBVF_s += GetPlateVolume(m_iNode[m_iNewNode[m_iTriangle[i][1]]], m_iNode[m_iNewNode[m_iTriangle[i][2]]], m_iNode[m_iNewNode[m_iTriangle[i][3]]], m_fTh[m_iTriangle[i][0]][0]);
			//else
				//m_fPBVF_s += GetPlateVolume(m_iNode[m_iNewNode[m_iTriangle[i][1]]], m_iNode[m_iNewNode[m_iTriangle[i][2]]], m_iNode[m_iNewNode[m_iTriangle[i][3]]], 0.1/fSize1);
		}
	}
	
	m_fPBVF_s /= float(m_iSize[0]*m_iSize[1]*m_iSize[2]);
	m_fRBVF_s /= float(m_iSize[0]*m_iSize[1]*m_iSize[2]);

	//*************************

	m_strDisp.Format(_T("Simplified pBV/TV = %5f rBV/TV = %5f"), m_fPBVF_s, m_fRBVF_s);
	UpdateData( FALSE );
	//*************************

#ifdef	WRITEINPUT
	//Writing input file

	int end;
	BYTE cha1=' ';
	char cha10[10];
	
	CFile crfile;
    CString str;
	str = m_strPath;
	str.Insert(m_strPath.GetLength(), _T(".inp"));
	crfile.Open(str.GetBuffer(0),CFile::modeWrite|CFile::modeCreate);

	CString strInput;
	strInput.Format(_T("*HEADING\n"));
	crfile.Write(strInput, strInput.GetLength());
	
	//*******************************Nodes***************************//
	strInput.Format(_T("*Node\n"));
	crfile.Write(strInput, strInput.GetLength());
	
	for(i=1; i<=m_iNodeNo; i++)
	{
		if(m_iNodeLabel[i] != 0)
		{
			strInput.Format(_T("      %d,   %4f,  %4f,  %4f\n"), i, fSize1*(float(m_iNode[m_iNewNode[i]][1]) - 1.5), fSize2*(float(m_iNode[m_iNewNode[i]][2]) - 1.5), fSize3*(float(m_iNode[m_iNewNode[i]][3]) - 1.5));
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	//********************************Node Sets**********************//
	strInput.Format(_T("*NSET, NSET= TOP_y\n"));
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_iNodeNo; i++)
	{
		if(m_iNode[m_iNewNode[i]][99] == MAXNUM+4 && m_iNodeLabel[i] != 0)
		{
			strInput.Format(_T(" %d\n"), i);
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	strInput.Format(_T("*NSET, NSET= BOTTOM_y\n"));
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_iNodeNo; i++)
	{
		if(m_iNode[m_iNewNode[i]][99] == MAXNUM+5 && m_iNodeLabel[i] != 0)
		{
			strInput.Format(_T(" %d\n"), i);
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	strInput.Format(_T("*NSET, NSET= TOP_x\n"));
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_iNodeNo; i++)
	{
		if(m_iNode[m_iNewNode[i]][99] == MAXNUM+2 && m_iNodeLabel[i] != 0)
		{
			strInput.Format(_T(" %d\n"), i);
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	strInput.Format(_T("*NSET, NSET= BOTTOM_x\n"));
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_iNodeNo; i++)
	{
		if(m_iNode[m_iNewNode[i]][99] == MAXNUM+3 && m_iNodeLabel[i] != 0)
		{
			strInput.Format(_T(" %d\n"), i);
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	strInput.Format(_T("*NSET, NSET= TOP_z\n"));
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_iNodeNo; i++)
	{
		if(m_iNode[m_iNewNode[i]][99] == MAXNUM+1 && m_iNodeLabel[i] != 0)
		{
			strInput.Format(_T(" %d\n"), i);
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	strInput.Format(_T("*NSET, NSET= BOTTOM_z\n"));
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_iNodeNo; i++)
	{
		if(m_iNode[m_iNewNode[i]][99] == MAXNUM && m_iNodeLabel[i] != 0)
		{
			strInput.Format(_T(" %d\n"), i);
			crfile.Write(strInput, strInput.GetLength());
		}
	}


	//*******************************3Node Beam**********************//
	
	//strInput.Format("*ELEMENT,TYPE=B32\n", i);
	strInput.Format(_T("*ELEMENT,TYPE=B31\n"), i);
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_i3NodeBeamNo; i++)
	{
		if(m_iNodeLabel[m_i3NodeBeam[i][1]] != 0 && m_iNodeLabel[m_i3NodeBeam[i][2]] != 0)
		{
			//strInput.Format("      %d,   %d,  %d,  %d\n", i, m_i3NodeBeam[i][1], m_i3NodeBeam[i][3], m_i3NodeBeam[i][2]);
			strInput.Format(_T("      %d,   %d,  %d\n"), i, m_i3NodeBeam[i][1], m_i3NodeBeam[i][2]);
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	//*******************************2Node Beam**********************//

	strInput.Format(_T("*ELEMENT,TYPE=B31\n"), i);
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_i2NodeBeamNo; i++)
	{
		if(m_iNodeLabel[m_i2NodeBeam[i][1]] != 0 && m_iNodeLabel[m_i2NodeBeam[i][2]] != 0)
		{
			strInput.Format(_T("      %d,   %d,  %d\n"), m_i3NodeBeamNo + i, m_i2NodeBeam[i][1], m_i2NodeBeam[i][2]);
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	//*******************************3Node Shell**********************//

	strInput.Format(_T("*ELEMENT,TYPE=STRI3\n"), i);
	crfile.Write(strInput, strInput.GetLength());
	for(i=1; i<=m_iShellNo; i++)
	{
		if(m_iNodeLabel[m_iTriangle[i][1]] != 0 && m_iNodeLabel[m_iTriangle[i][2]] != 0 && m_iNodeLabel[m_iTriangle[i][3]] != 0)
		{
			strInput.Format(_T("      %d,   %d,  %d,  %d\n"), m_i3NodeBeamNo + m_i2NodeBeamNo + i, m_iTriangle[i][1], m_iTriangle[i][2], m_iTriangle[i][3]);
			crfile.Write(strInput, strInput.GetLength());
		}
	}

	//*********************************Element Set********************************//
	for(i=1; i<=m_i3NodeBeamNo; i++)
	{
		strInput.Format(_T("*ELSET, ELSET=Bone3NodeBeam%d\n"), i);
		crfile.Write(strInput, strInput.GetLength());
		strInput.Format(_T("%d\n"), i);
		crfile.Write(strInput, strInput.GetLength());
	}

	for(i=1; i<=m_i2NodeBeamNo; i++)
	{
		strInput.Format(_T("*ELSET, ELSET=Bone2NodeBeam%d\n"), i);
		crfile.Write(strInput, strInput.GetLength());
		strInput.Format(_T("%d\n"), m_i3NodeBeamNo + i);
		crfile.Write(strInput, strInput.GetLength());
	}

	j=1;
	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_iCluster[i][2] != 0 && m_iClusterNode[i][0] >= 3)
		{
			strInput.Format(_T("*ELSET, ELSET=BoneShell%d\n"), m_iPlateReplace[i]);
			crfile.Write(strInput, strInput.GetLength());
			while(m_iTriangle[j][0]==i && j<=m_iShellNo)
			{
				strInput.Format(_T("%d\n"), m_i3NodeBeamNo + m_i2NodeBeamNo + j);
				crfile.Write(strInput, strInput.GetLength());
				j++;
			}
		}
	}

	//**********************************Thickness**********************************//

	for(i=1; i<=m_i3NodeBeamNo; i++)
	{
		strInput.Format(_T("*BEAM SECTION, ELSET=Bone3NodeBeam%d, MATERIAL= bone, SECTION = CIRC\n"), i);
		crfile.Write(strInput, strInput.GetLength());
		if(m_fTh[m_i3NodeBeam[i][0]][0]/1000.0>0)
		{
			strInput.Format(_T("%f\n"), fSize1*m_fTh[m_i3NodeBeam[i][0]][0] / 2.0);
			crfile.Write(strInput, strInput.GetLength());
		}
		else
		{
			strInput.Format(_T("%f\n"), 0.05);
			crfile.Write(strInput, strInput.GetLength());
		}
		strInput.Format(_T("%f,   %f,   %f\n"), m_fNorm[m_i3NodeBeam[i][0]][3], m_fNorm[m_i3NodeBeam[i][0]][4], m_fNorm[m_i3NodeBeam[i][0]][5]);
		crfile.Write(strInput, strInput.GetLength());
	}

	for(i=1; i<=m_i2NodeBeamNo; i++)
	{
		strInput.Format(_T("*BEAM SECTION, ELSET=Bone2NodeBeam%d, MATERIAL= bone, SECTION = CIRC\n"), i);
		crfile.Write(strInput, strInput.GetLength());
		if(m_fTh[m_i2NodeBeam[i][0]][0]/1000.0>0)
		{
			strInput.Format(_T("%f\n"), fSize1*m_fTh[m_i2NodeBeam[i][0]][0] / 2.0);
			crfile.Write(strInput, strInput.GetLength());
		}
		else
		{
			strInput.Format(_T("%f\n"), 0.05);
			crfile.Write(strInput, strInput.GetLength());
		}
		strInput.Format(_T("%f,   %f,   %f\n"), m_fNorm[m_i2NodeBeam[i][0]][3], m_fNorm[m_i2NodeBeam[i][0]][4], m_fNorm[m_i2NodeBeam[i][0]][5]);
		crfile.Write(strInput, strInput.GetLength());
	}

	for(i=1; i<=m_iTraNo; i++)
	{
		if(m_iCluster[i][1] == 1 && m_iCluster[i][2] != 0 && m_iClusterNode[i][0] >= 3)
		{
			strInput.Format(_T("*SHELL SECTION, ELSET=BoneShell%d, MATERIAL= bone\n"), m_iPlateReplace[i]);
			crfile.Write(strInput, strInput.GetLength());
			if(m_fTh[i][0]/1000.0>0)
			{
				strInput.Format(_T("%f\n"), fSize1*m_fTh[i][0]);
				crfile.Write(strInput, strInput.GetLength());
			}
			else
			{
				strInput.Format(_T("%f\n"), 0.1);
				crfile.Write(strInput, strInput.GetLength());
			}
		}
	}

	//**********************************Material**********************************//
	strInput.Format(_T("*MATERIAL, NAME= bone\n"));
	crfile.Write(strInput, strInput.GetLength());
	strInput.Format(_T("*ELASTIC, TYPE = ISOTROPIC\n"));
	crfile.Write(strInput, strInput.GetLength());
	strInput.Format(_T("15000.0,  0.3\n"));
	crfile.Write(strInput, strInput.GetLength());

	//**********************************Bounday**********************************//
	strInput.Format(_T("*BOUNDARY\n"));
	crfile.Write(strInput, strInput.GetLength());
	strInput.Format(_T("BOTTOM_z, 3\n"));
	crfile.Write(strInput, strInput.GetLength());
	count = 1;
	for(i=1; i<=m_iNodeNo; i++)
	{
		if(count <= 3)
		{
			if(m_iNode[m_iNewNode[i]][99] == MAXNUM && m_iNodeLabel[i] != 0)
			{
				strInput.Format(_T(" %d, 1, 2\n"), i);
				crfile.Write(strInput, strInput.GetLength());
				count++;
			}
		}
		else
			i=m_iNodeNo+1;
	}

	//**********************************Step**********************************//
	strInput.Format(_T("*STEP\n"));
	crfile.Write(strInput, strInput.GetLength());
	strInput.Format(_T("*STATIC\n"));
	crfile.Write(strInput, strInput.GetLength());
	strInput.Format(_T("*BOUNDARY\n"));
	crfile.Write(strInput, strInput.GetLength());
	strInput.Format(_T("TOP_z, 3, 3, -0.01\n"));
	crfile.Write(strInput, strInput.GetLength());

	strInput.Format(_T("** OUTPUT REQUESTS\n**\n*Restart, write, frequency=0\n**\n** FIELD OUTPUT: F-Output-1\n**\n*Output, field, variable=PRESELECT\n**\n** HISTORY OUTPUT: H-Output-1\n**\n*Output, history\n*Node Print, nset=TOP_z,TOTALS=YES\nRF3\n"));
	crfile.Write(strInput, strInput.GetLength());
	
	strInput.Format(_T("*END STEP\n"));
	crfile.Write(strInput, strInput.GetLength());

	//***********************************************************************

#endif
	free(iNodeReplace);

	UpdateData( FALSE );

	return 1;
}
				




























