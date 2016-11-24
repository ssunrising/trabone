#if !defined(AFX_FORMCOMMANDVIEW1_H__A93D5735_1963_4785_8DA3_8C2A4E1F468F__INCLUDED_)
#define AFX_FORMCOMMANDVIEW1_H__A93D5735_1963_4785_8DA3_8C2A4E1F468F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormCommandView1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormCommandView : public CFormView
{
protected:
	CFormCommandView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormCommandView)

// Form Data
public:
	//{{AFX_DATA(CFormCommandView)
	enum { IDD = IDD_FORM_COMMAND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CString	m_strSize;
	CString m_strDisp;
	CString m_strDebug;

// Attributes
public:
    CString m_strPath;

	int ***m_iMatrix;
	int ***m_iCrPnts;
	int *m_iSize;
	int ***m_iTemp;
	float ***m_fTemp;
	int ***m_iPtType;
	float m_resolution[3];
	int m_iTraSelect;
	int m_iStepSelect;

	//save [0]the total number in the cluster [1]the voxel type: plate-1, rod-2 
	//[2]temporary use for labeling, then store the total number in the clustered arc-skeleton, 
	//finally store the total number in clustered plate_rod-skeleton;
	int **m_iCluster;
	int m_iClusterNo;
	//save the connection of trabecula
	int **m_iConnection;
	//save the starting/ending coordinate of each trabecula;
	//int **m_iDimension;	//[0][1][2]minimum x,y,z  [3][4][5]maximum 
	int m_iTraNo;		//actual total number of trabecular piece
	
	int m_iLayer;
	int m_iThr;
	int m_iPlateThr;

	BOOL m_bLoad;
	BOOL m_bBklLoad;
	BOOL m_bRecovered;
	BOOL m_bPClustered;
	BOOL m_bClassified;
	BOOL m_bThinned;
	BOOL m_bArcThinned;
	BOOL m_bCurveMeshed;
	BOOL m_bDebugmode;
	BOOL m_bDebugProcess;
	BOOL m_bTrasep;
	BOOL m_bStepShow;
	BOOL m_bMesh;

	int m_iSCSize;	//save the total number of SC points
	int m_iCCSize;	//save the total number of CC points
	int m_iCESize;  //save the total number of CE points
	int m_iSSSize;	//save the total number of SSarc points

	//For Berkeley Data
	int ***m_iLabel;	//save the stress/strain label
	int m_iTotalNo;
	float ***m_fStrain;
	float ***m_fStress;
	int *m_iFail;
	int **m_iStepCT;	//At every step, how many voxels failed in each trabeculae by Tension 1, Compression -1;
	int **m_iStepFailure;	//At every step, whether a cluster fails (1) or not(0)

	int m_iNodelistSize;
	int m_iCurvelistSize;
	int **m_iNodelist;			//save all the node label
	int **m_iCurvelist;			//save all the curve's beginning label and end label
	float *m_fCurvethickness; //save all the curve's diameters;

	//morphological and topological parameters
	float m_fBVF;		//BV/TV
	float m_fPf;		//plate fraction
	float m_fRf;		//rod fraction
	float m_fPBVF;		//Plate volume/TV
	float m_fRBVF;		//Rod volume/TV
	float m_fPThickness;	//Plate Thickness(mm)
	float m_fRDiameter;	//Rod diameter(mm)
	float m_fPSurface;	//Plate surface(mm^2)
	float m_fRLength;	//Rod length(mm)
	float m_fJuncNo;		//Total Junction No
	float m_fRRJNo;			//Rod-Rod Junction No
	float m_fRPJNo;			//Rod-Plate Junction No
	float m_fPPJNo;			//plate-plate arc junction No
	float m_fPNo;			//Plate No/TV(1/mm^3)
	float m_fRNo;			//Rod No/TV(1/mm^3)

	float m_fPBVF_s;			//pBV/TV for plate-rod model
	float m_fRBVF_s;			//rBV/TV for plate-rod model
	
	float m_fxlf;
	float m_fxhf;
	float m_fylf;
	float m_fyhf;
	float m_fzlf;
	float m_fzhf;

	float m_fxlpf;
	float m_fxhrf;
	float m_fylpf;
	float m_fyhrf;
	float m_fzlpf;
	float m_fzhrf;
	
	float **m_fTh;			//Plate or rod thickness for each trabecula
	float **m_fNorm;		//norm for each plate and orientation for each rod

	int **m_iClusterNode;	//[0]the total number of nodes in each cluster [1]~[99] the ID number of nodes 
	int **m_iNode;			//[0]node type: 1 plate-rod 2 plate_edge_mesh 3 plate_inner_mesh 4 rod-rod 5 rod-end [1]~[3]coordinates of node [4]Number of connected elments [5]~[99] the ID number of connected elements
	int m_iNodeSize;
	int **m_iTriangle;		//[0]Cluster ID [1]~[3] Nodes ID
	int m_iTriPointer;

	int m_iTotalBeamNo;
	int m_i3NodeBeamNo;
	int **m_i3NodeBeam;
	int m_i2NodeBeamNo;
	int **m_i2NodeBeam;
	int m_iPlateNo;
	int m_iShellNo;
	int m_iNodeNo;
	int *m_iNewNode;	//lookup table

	int *m_iNodeLabel;		//For connectivity test
	int *m_iLabelList;
	int **m_iNodeConn;

	// Operations
public:

private:
	int Neighbor(int i, int j, int k, int type1, int type2, int type3, int type4);
	int Neighbor_CC(int i, int j, int k);
	void Curvemesh();
	void FindConnection(int i, int j, int k, int a, int b, int c);
	int NeighborC(int i, int j, int k);
	int NeighborSE(int i, int j, int k);
	int LookforCC(int i, int a, int b, int c);
	int LookforCE(int i, int j, int k);
	int LookforSC(int i, int j, int k);

	int IsSC(int i, int j, int k, int ***matrix);	//identify whether a SC point has both plate and rod points as neighbors
	int IsSE_TR(int i, int j, int k, int ***matrix);  //identify the surface edge points which has more than two individual plate points as neighbors
	int IsSI_TR(int i, int j, int k, int ***matrix);  //identify the surface inner points which has more than three individual plate points as neighbors
	int Node_Conn(int i, int j, int k, int ***CrPnts, int ***matrix, int ***PtType, int **Node);	//Identify the connecting cluster for each node
	float GetTriangleArea(int a, int b, int c, int **Node);
	int GetTriangleNormal(int a, int b, int c, int **Node, float *Norm);
	int GetPlateNormal(int i, int **ClusterNode, int **Node, float **Norm);
	float GetDistance(int i, int j, int k, int *ClusterNode, int **Node);
	int Delaunay(int ClusterID, int *ClusterNode, int **Node, float *Norm, float Size, int Temp, int TriPointer, int **Triangle);
	int CompareNode(int a, int b, int **ClusterNode, int **Node);
	//int CurveNode_Comb(int i, int j, int k, int ***matrix, int **Node)
	float GetRodVolume(int *Node1, int *Node2, float th);
	float GetPlateVolume(int *Node1, int *Node2, int *Node3, float th);
	int Connectivity(int NodeBeam3No, int **NodeBeam3, int NodeBeam2No, int **NodeBeam2, int ShellNo, int **Shell, int NodeNo, int *NodeLabel, int *LabelList, int **NodeConn);

	int AbaqusInput();	//Write abaqus input file

//	void SetDimension(int i, int j, int k);
	int GetNorm(float **A, float **norm, int i);
	int GetOri(float **A, float **norm, int i);
	float GetTh(int ***matrix, int ***type, float **norm, int i, int j, int k, int tra, float **th);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormCommandView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormCommandView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormCommandView)
	afx_msg void OnLoad();
	afx_msg void OnThinning();
	afx_msg void OnCancel();
	afx_msg void OnOK();
	afx_msg void OnClassify();
	afx_msg void OnArcthinning();
	afx_msg void OnPrimary();
	afx_msg void OnFinal();
	afx_msg void OnDebugstart();
	afx_msg void OnDebugend();
	afx_msg void OnRecordClassify();
	afx_msg void OnCluster();
	afx_msg void OnRecover();
	afx_msg void OnRecoverPlate();
	afx_msg void OnRecoverRod();
	afx_msg void OnPlatecluster();
	afx_msg void OnArcClassify();
	afx_msg void OnToolTrasep();
	afx_msg void OnUpdateToolTrasep(CCmdUI* pCmdUI);
	afx_msg void OnToolParameter();
	afx_msg void OnUpdateToolParameter(CCmdUI* pCmdUI);
	afx_msg void OnIncrease();
	afx_msg void OnDecrease();
	afx_msg void OnToolMorph();
	afx_msg void OnUpdateToolMorph(CCmdUI* pCmdUI);
	afx_msg void OnToolSavebinary();
	afx_msg void OnUpdateToolSavebinary(CCmdUI* pCmdUI);
	afx_msg void OnArcprimary();
	afx_msg void OnArcfinal();
	afx_msg void OnToolBkldata();
	afx_msg void OnToolStress();
	afx_msg void OnUpdateToolStress(CCmdUI* pCmdUI);
	afx_msg void OnStepincrease();
	afx_msg void OnStepdecrease();
	afx_msg void OnToolBinary();
	afx_msg void OnToolPfcal();
	afx_msg void OnToolMultiselect();
	afx_msg void OnToolMesh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMCOMMANDVIEW1_H__A93D5735_1963_4785_8DA3_8C2A4E1F468F__INCLUDED_)
