// TestGLView.cpp : implementation of the CTestGLView class
//

#include "stdafx.h"
#include "Display.h"

#include "DisplayDoc.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "GLEnableView.h"
#include "TestGLView.h"
#include "MainFrm.h"
#include "ColorSelectionDialog.h"
//#include "OGLInfoDlg.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXNUM 9999

/////////////////////////////////////////////////////////////////////////////
// CTestGLView

IMPLEMENT_DYNCREATE(CTestGLView, CGLEnableView)

BEGIN_MESSAGE_MAP(CTestGLView, CGLEnableView)
	//{{AFX_MSG_MAP(CTestGLView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	//ON_COMMAND(ID_HELP_OGLINFO, OnHelpOglinfo)
	ON_COMMAND(ID_IMAGE_SMOOTH, OnImageSmooth)
	ON_COMMAND(ID_IMAGE_CULL, OnImageCull)
	ON_COMMAND(ID_IMAGE_COLOR, OnImageColor)
	ON_COMMAND(ID_IMAGE_ENLARGE, OnImageEnlarge)
	ON_COMMAND(ID_IMAGE_SHRINK, OnImageShrink)

	ON_UPDATE_COMMAND_UI(ID_IMAGE_SMOOTH, OnUpdateImageSmooth)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_CULL, OnUpdateImageCull)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGLView construction/destruction

CTestGLView::CTestGLView():
	X_Angle(0.0), Y_Angle(0.0), X_Distance(0.0), Y_Distance(0.0),
	TessWindRule(GLU_TESS_WINDING_ODD), TessFilling(TRUE),
	sceneselect(0),	quadricNormals(GLU_NONE),
	quadricDwStyle(GLU_LINE), quadricOrientation(GLU_OUTSIDE)

{
	// TODO: add construction code here
	m_Clear = FALSE;
	m_fSIcolor[0] = 1;
	m_fSIcolor[1] = 0;
	m_fSIcolor[2] = 0;

	m_fSEcolor[0] = 0;
	m_fSEcolor[1] = 1;
	m_fSEcolor[2] = 0;

	m_fSScolor[0] = 0;
	m_fSScolor[1] = 0.5;
	m_fSScolor[2] = 1;

	m_fAIcolor[0] = 0;
	m_fAIcolor[1] = 1;
	m_fAIcolor[2] = 1;

	m_fAEcolor[0] = 1;
	m_fAEcolor[1] = 0;
	m_fAEcolor[2] = 1;

	m_fAAcolor[0] = 1;
	m_fAAcolor[1] = 0.5;
	m_fAAcolor[2] = 0;

	m_fSAcolor[0] = 1;
	m_fSAcolor[1] = 1;
	m_fSAcolor[2] = 0;

	m_fIPcolor[0] = 0.5;
	m_fIPcolor[1] = 0.5;
	m_fIPcolor[2] = 0.5;

	m_fBKcolor[0] = 0.3f;
	m_fBKcolor[1] = 0.3f;
	m_fBKcolor[2] = 0.3f;

	m_fEGcolor[0] = 0.4f;
	m_fEGcolor[1] = 0.2f;
	m_fEGcolor[2] = 0.7f;

	m_fScolor[0] = 0;
	m_fScolor[1] = 0;
	m_fScolor[2] = 0;

	m_fS2color[0] = 1;
	m_fS2color[1] = 1;
	m_fS2color[2] = 1;

}

CTestGLView::~CTestGLView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTestGLView diagnostics

#ifdef _DEBUG
void CTestGLView::AssertValid() const
{
	CGLEnableView::AssertValid();
}

void CTestGLView::Dump(CDumpContext& dc) const
{
	CGLEnableView::Dump(dc);
}

CDisplayDoc* CTestGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDisplayDoc)));
	return (CDisplayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestGLView Overridables from CGLEnableView

void CTestGLView::VideoMode(ColorsNumber & c, ZAccuracy & z, BOOL & dbuf)
{
// ask for 65355 colors...
	c=THOUSANDS;
// ...16 bit Z-buffer...
	z=NORMAL;
// ...double-buffering
	dbuf=TRUE;
}

void CTestGLView::OnCreateGL()
{
// perform hidden line/surface removal (enable Z-Buffering)
	glEnable(GL_DEPTH_TEST);
// set background color to black
	glClearColor(m_fBKcolor[0],m_fBKcolor[1],m_fBKcolor[2],1.0f );
// set clear Z-Buffer value
	glClearDepth(1.0f);

	// create and enable a white directional light
/*	float  color[]={0.f,0.f,0.f,1.f};// RGBA color spec
	glLightfv(GL_LIGHT0,GL_DIFFUSE,color);
	float  ambient[]={.3f,.3f,.3f,1.f};// RGBA color spec
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	float pos[]={1.f,0.f,0.f,0.f};
	//glLightfv(GL_LIGHT0,GL_POSITION,pos);

	//GLfloat light_diffuse[]={0.0,0.0,1.0,1.0}; 
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse); 
	//GLfloat light_ambient[]={1.0,0.0,0.0,1.0}; 
	//glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient); 
	//首先定义一个材质，定义方法非常类似前面讲到的光源定义。 
/*GLfloat mat_ambient[]={0.8,0.8,0.8,1.0}; 
//定义 紫色 的漫反射特性 
GLfloat mat_diffuse[]={0.8,0.0,0.8,1.0}; 
//定义 亮紫色 的镜面反射特性 
GLfloat mat_specular[]={1.0,0.0,1.0,1.0}; 
//定义镜面反射的光亮度 
GLfloat mat_shininess[]={50.0}; 
//将以上材质定义应用 
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient); 
glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse); 
glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular); 
glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess); 

//这里我们简化光源，以显示材质的效果。 
//这里我们只指定光源位置，其他默认：白色光源。 
//你也可以加入光源的定义，看看光源和材质的合成的效果 
//正是因为它们能够合成，才能产生比真实生活中多的多的效果，这也正是 
//3D技术吸引人的魅力所在。 
GLfloat light_position[]={1.0,1.0,100.0,0.0}; 
glLightfv(GL_LIGHT0,GL_POSITION,light_position); 
// GLfloat light_diffuse[]={0.0,0.0,1.0,1.0}; 
// glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse); */

//	glEnable(GL_LIGHTING); 
//	glEnable(GL_LIGHT0);


// prepare a bunch of line segments (carthesian axes arrows)
	StartStockDListDef();
	
	glBegin(GL_LINES);
		// yellow x axis arrow
		glColor3f(1.f,1.f,0.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,0.07f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,-0.07f,0.0f);
		// cyan y axis arrow
		glColor3f(0.f,1.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.07f,0.9f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-0.07f,0.9f,0.0f);
		// magenta z axis arrow
		glColor3f(1.f,0.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.07f,0.9f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,-0.07f,0.9f);
	glEnd();
	EndStockListDef();

	glPolygonMode(GL_BACK, GL_FILL);
	// prepare a single display list (yet another cube)

}



void CTestGLView::OnDrawGL()
{

	int i,j,k;
	int a,b,c;
	float color[3];
	int remain;
// the couple glPush - glPop is necessary because the entire
// scene is rotated of the given angle (which is absolute) at every redraw
	glPushMatrix();
// rotate the objects of the given angle
	glRotated(X_Angle,1.0,0.0,0.0);
	glRotated(Y_Angle,0.0,1.0,0.0);

	glTranslated(X_Distance, Y_Distance, 0.0);
	// this should be self explanatory
	DrawStockDispLists();
	glClearColor(m_fBKcolor[0],m_fBKcolor[1],m_fBKcolor[2],1.0f );



// execute previously prepared displ. list 2 times
// Note:All translations are relative (imagine to deal with a "3D cursor")
	
	if(m_Clear == TRUE)
	{
		OnCreateDispList();
		
		CFormCommandView* m_Temp;
		m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pFormView;
		int normal_draw = 0;
		
		for(i=2; i<m_Temp->m_iSize[0]+2; i++)
		{
			for (j=2; j<m_Temp->m_iSize[1]+2; j++)
			{
				for(k=2; k<m_Temp->m_iSize[2]+2; k++)
				{
					//display at different step, which trabeculae (belong to plate or rod) fail
					if(m_Temp->m_bStepShow == TRUE)
					{
						if(m_Temp->m_iMatrix[i][j][k] > 0)
						{
							if(m_Temp->m_iStepFailure[m_Temp->m_iMatrix[i][j][k]][m_Temp->m_iStepSelect] == 1)
							{
								if(m_Temp->m_iCluster[m_Temp->m_iMatrix[i][j][k]][1] == 1)
								{
						 			glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
									Surface_edge.Draw();
									glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								}
								else
								{
						 			glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
									Surface_inner.Draw();
									glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								}
							}
							else
							{
								if(m_Temp->m_iCluster[m_Temp->m_iMatrix[i][j][k]][1] == 1)
								{
						 			glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
									Transparent_plate.Draw();
									glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								}
								else
								{
						 			glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
									Transparent_rod.Draw();
									glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));

								}
							}
						}
					}
					else if(m_Temp->m_bDebugmode == FALSE && m_Temp->m_bRecovered == FALSE && m_Temp->m_bPClustered == FALSE)
					{
						switch(m_Temp->m_iMatrix[i][j][k])
						{
							case 1:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_edge.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 2:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_inner.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 3:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_surface.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 4:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_arc.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 5:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_end.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 6:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_inner.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 7:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_arc.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 8:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Isolated_point.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							default:
								break;
						}
					}
					else if(m_Temp->m_bDebugmode == TRUE && m_Temp->m_bRecovered == FALSE && m_Temp->m_bPClustered == FALSE)
					{
						if(m_Temp->m_iMatrix[i][j][k]==0)
						{
				 			glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
							Surface_arc.Draw();
							glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
						}
						else if(m_Temp->m_iMatrix[i][j][k]>0)
						{
				 			glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
							Arc_end.Draw();
							glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
						}
					}
					else if(m_Temp->m_bDebugmode == FALSE && m_Temp->m_bRecovered == TRUE && m_Temp->m_bPClustered == FALSE && m_Temp->m_bTrasep == FALSE)
					{	
						if(m_Temp->m_iPtType[i][j][k] >= 1 && m_Temp->m_iPtType[i][j][k] <= 1.5)
						{
							/*color[0] = 1;
							color[1] = (m_Temp->m_iPtType[i][j][k]-1)/0.5;
							color[2] = 0;
							Surface_inner.StartDef();
								glBegin(GL_QUADS);
									glColor3f(color[0],color[1],color[2]);
									glVertex3f(0.0f,0.0f,0.0f);
									glVertex3f(m_fSize,.0f,.0f);
									glVertex3f(m_fSize,m_fSize,.0f);
									glVertex3f(0.0f,m_fSize,.0f);

									glVertex3f(0.0f,m_fSize,m_fSize);
									glVertex3f(m_fSize,m_fSize,m_fSize);
									glVertex3f(m_fSize,.0f,m_fSize);
									glVertex3f(0.0f,0.0f,m_fSize);
								glEnd();
								glBegin(GL_QUAD_STRIP);
									glColor3f(color[0],color[1],color[2]);
									glVertex3f(0.0f,0.0f,.0f);
									glVertex3f(0.0f,0.0f,m_fSize);

									glVertex3f(m_fSize,.0f,.0f);
									glVertex3f(m_fSize,.0f,m_fSize);

									glVertex3f(m_fSize,m_fSize,.0f);
									glVertex3f(m_fSize,m_fSize,m_fSize);

									glVertex3f(0.0f,m_fSize,.0f);
									glVertex3f(0.0f,m_fSize,m_fSize);

									glVertex3f(0.0f,0.0f,.0f);
									glVertex3f(0.0f,0.0f,m_fSize);
								glEnd();
								glBegin(GL_LINE_LOOP);
									glLineWidth(3.0);
									glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
									glVertex3f(0.0f,0.0f,0.0f);
									glVertex3f(m_fSize,0.0f,0.0f);
									glVertex3f(m_fSize,m_fSize,0.0f);
									glVertex3f(m_fSize,m_fSize,m_fSize);
									glVertex3f(m_fSize,0.0f,m_fSize);
									glVertex3f(0.0f,0.0f,m_fSize);
									glVertex3f(0.0f,m_fSize,m_fSize);
									glVertex3f(0.0f,m_fSize,0.0f);
								glEnd();
								glBegin(GL_LINES);
									glLineWidth(3.0);
									glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
									glVertex3f(0.0f,m_fSize,0.0f);
									glVertex3f(m_fSize,m_fSize,0.0f);
								glEnd();
								glBegin(GL_LINES);
									glLineWidth(3.0);
									glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
									glVertex3f(0.0f,m_fSize,m_fSize);
									glVertex3f(m_fSize,m_fSize,m_fSize);
								glEnd();
								glBegin(GL_LINES);
									glLineWidth(3.0);
									glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
									glVertex3f(0.0f,0.0f,0.0f);
									glVertex3f(0.0f,0.0f,m_fSize);
								glEnd();
								glBegin(GL_LINES);
									glLineWidth(1.0);
									glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
									glVertex3f(m_fSize,0.0f,0.0f);
									glVertex3f(m_fSize,0.0f,m_fSize);
								glEnd();

								glEnable(GL_LINE_SMOOTH);
								glLineWidth(1.0);
								glEnable(GL_BLEND);
								glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
								glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

								glEnable(GL_CULL_FACE); 
								glEnable(GL_POLYGON_SMOOTH); 

								glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

							Surface_inner.EndDef();*/


							glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
							Surface_inner.Draw();
							glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
						}
						else if(m_Temp->m_iPtType[i][j][k] >= 1.5 && m_Temp->m_iPtType[i][j][k] <= 2)
						{
							/*color[0] = (2-m_Temp->m_iPtType[i][j][k])/0.5;
							color[1] = 1;
							color[2] = 0;
							Surface_edge.StartDef();// <- do not execute list immediately
								glBegin(GL_QUADS);
									glColor3f(color[0],color[1],color[2]);
									glVertex3f(0.0f,0.0f,0.0f);
									glVertex3f(m_fSize,.0f,.0f);
									glVertex3f(m_fSize,m_fSize,.0f);
									glVertex3f(0.0f,m_fSize,.0f);

									glVertex3f(0.0f,m_fSize,m_fSize);
									glVertex3f(m_fSize,m_fSize,m_fSize);
									glVertex3f(m_fSize,.0f,m_fSize);
									glVertex3f(0.0f,0.0f,m_fSize);
								glEnd();
								glBegin(GL_QUAD_STRIP);
									glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
									glVertex3f(0.0f,0.0f,.0f);
									glVertex3f(0.0f,0.0f,m_fSize);

									glVertex3f(m_fSize,.0f,.0f);
									glVertex3f(m_fSize,.0f,m_fSize);

									glVertex3f(m_fSize,m_fSize,.0f);
									glVertex3f(m_fSize,m_fSize,m_fSize);

									glVertex3f(0.0f,m_fSize,.0f);
									glVertex3f(0.0f,m_fSize,m_fSize);

									glVertex3f(0.0f,0.0f,.0f);
									glVertex3f(0.0f,0.0f,m_fSize);
								glEnd();
								glBegin(GL_LINE_LOOP);
									glLineWidth(3.0);
									glColor3f(0.4f,.2f,.7f);
									glVertex3f(0.0f,0.0f,0.0f);
									glVertex3f(m_fSize,0.0f,0.0f);
									glVertex3f(m_fSize,m_fSize,0.0f);
									glVertex3f(m_fSize,m_fSize,m_fSize);
									glVertex3f(m_fSize,0.0f,m_fSize);
									glVertex3f(0.0f,0.0f,m_fSize);
									glVertex3f(0.0f,m_fSize,m_fSize);
									glVertex3f(0.0f,m_fSize,0.0f);
								glEnd();
								glBegin(GL_LINES);
									glLineWidth(3.0);
									glColor3f(0.4f,.2f,.7f);
									glVertex3f(0.0f,m_fSize,0.0f);
									glVertex3f(m_fSize,m_fSize,0.0f);
								glEnd();
								glBegin(GL_LINES);
									glLineWidth(3.0);
									glColor3f(0.4f,.2f,.7f);
									glVertex3f(0.0f,m_fSize,m_fSize);
									glVertex3f(m_fSize,m_fSize,m_fSize);
								glEnd();
								glBegin(GL_LINES);
									glLineWidth(3.0);
									glColor3f(0.4f,.2f,.7f);
									glVertex3f(0.0f,0.0f,0.0f);
									glVertex3f(0.0f,0.0f,m_fSize);
								glEnd();
								glBegin(GL_LINES);
									glLineWidth(1.0);
									glColor3f(0.4f,.2f,.7f);
									glVertex3f(m_fSize,0.0f,0.0f);
									glVertex3f(m_fSize,0.0f,m_fSize);
								glEnd();
							Surface_edge.EndDef();*/
							
							glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
							Surface_edge.Draw();
							glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
						}
					}
					else if(m_Temp->m_bDebugmode == FALSE && m_Temp->m_bRecovered == TRUE && m_Temp->m_bPClustered == TRUE && m_Temp->m_bTrasep == FALSE)
					{
						if(m_Temp->m_iMatrix[i][j][k] <= 0)
							remain = 0;
						else if(m_Temp->m_iMatrix[i][j][k] == 2*MAXNUM)
							remain = 10;
						else if(m_Temp->m_iMatrix[i][j][k] >= 2*MAXNUM+1)
							//remain = 0;
							remain = 9;
						else
							remain = (m_Temp->m_iMatrix[i][j][k]) % 7 + 1;
						
						//if(m_Temp->m_iMatrix[i][j][k] <= 0)
						//	remain = 0;
						//else
						//	remain = m_Temp->m_iCluster[m_Temp->m_iMatrix[i][j][k]][1];
						switch(remain)
						{
							case 0:
								break;
							case 1:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_edge.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 2:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_inner.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 3:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_surface.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 4:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_arc.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 5:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_end.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 6:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_inner.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 7:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_arc.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 8:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Isolated_point.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 9:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Special_point2.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 10:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Special_point.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							default:
								break;
						}
					}
					else if(m_Temp->m_bDebugmode == FALSE && m_Temp->m_bRecovered == TRUE && m_Temp->m_bPClustered == TRUE && m_Temp->m_bTrasep == TRUE)
					{
						remain = 0;
						if(m_Temp->m_iPtType[i][j][k] <= 0)
							remain = 0;
						//else if(m_Temp->m_iPtType[i][j][k]>0)
						//	remain = (m_Temp->m_iPtType[i][j][k])%8+1;
						else if(m_Temp->m_iPtType[i][j][k] == m_Temp->m_iTraSelect)
							remain = m_Temp->m_iCluster[m_Temp->m_iPtType[i][j][k]][1];
						/*if(m_Temp->m_iMatrix[i][j][k] <= 0)
							remain = 0;
						else if(m_Temp->m_iMatrix[i][j][k] == 2*MAXNUM)
							remain = 10;
						else if(m_Temp->m_iMatrix[i][j][k] == 2*MAXNUM+1)
							remain = 9;
						else if(m_Temp->m_iMatrix[i][j][k] == m_Temp->m_iTraSelect)
							remain = (m_Temp->m_iMatrix[i][j][k]+2) % 8 + 1;*/


						switch(remain)
						{
							case 0:
								break;
							case 1:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_edge.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								if(normal_draw == 0)
								{
									normal_draw = 1;
						 			glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
									glBegin(GL_LINES);
										glColor3f(1.f,1.f,0.f);
										glVertex3f(0.0f,0.0f,0.0f);
//										glVertex3f(m_Temp->m_fNorm[m_Temp->m_iTraSelect][1],m_Temp->m_fNorm[m_Temp->m_iTraSelect][2],m_Temp->m_fNorm[m_Temp->m_iTraSelect][0]);
									glEnd();
									glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								}
								break;
							case 2:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_inner.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								if(normal_draw == 0)
								{
									normal_draw = 1;
						 			glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
									glBegin(GL_LINES);
										glColor3f(1.f,1.f,0.f);
										glVertex3f(0.0f,0.0f,0.0f);
										//glVertex3f(m_Temp->m_fNorm[m_Temp->m_iTraSelect][1],m_Temp->m_fNorm[m_Temp->m_iTraSelect][2],m_Temp->m_fNorm[m_Temp->m_iTraSelect][0]);
									glEnd();
									glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								}
								break;
							case 3:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_surface.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 4:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Surface_arc.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 5:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_end.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 6:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_inner.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 7:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Arc_arc.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 8:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Isolated_point.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 9:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Special_point2.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							case 10:
						 		glTranslatef(m_fSize*(j-2),m_fSize*(k-2),m_fSize*(i-2));
								Special_point.Draw();
								glTranslatef(m_fSize*(2-j),m_fSize*(2-k),m_fSize*(2-i));
								break;
							default:
								break;
						}
					}
				}
			}
		}

		if(m_Temp->m_bMesh == TRUE && m_Temp->m_bTrasep == TRUE)
		{
			if(m_Temp->m_iCluster[m_Temp->m_iTraSelect][1] == 2 && m_Temp->m_iCluster[m_Temp->m_iTraSelect][2] != 0)
			{
				for(i=1; i<=m_Temp->m_iTraNo; i++)
				{
					if(i == m_Temp->m_iTraSelect)
					{
						glBegin(GL_LINES);
							glLineWidth(3.0);
							glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][1]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][1]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][1]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][2]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][2]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][2]][1])-1.5f));
						glEnd();
					}
				}
			}
			else if(m_Temp->m_iCluster[m_Temp->m_iTraSelect][1] == 1 && m_Temp->m_iCluster[m_Temp->m_iTraSelect][2] != 0)
			{
				for(i=1; i<m_Temp->m_iTriPointer; i++)
				{
					if(m_Temp->m_iTriangle[i][0] == m_Temp->m_iTraSelect)
					{
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][1])-1.5f));
						glEnd();
					}
					/*else
					{
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][1]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][3]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iTriangle[i][2]][1])-1.5f));
						glEnd();
					}*/
				}
				for(i=1; i<=m_Temp->m_iClusterNode[m_Temp->m_iTraSelect][0]; i++)
				{
			 		glTranslatef(m_fSize*(m_Temp->m_iNode[m_Temp->m_iClusterNode[m_Temp->m_iTraSelect][i]][2]-2),m_fSize*(m_Temp->m_iNode[m_Temp->m_iClusterNode[m_Temp->m_iTraSelect][i]][3]-2),m_fSize*(m_Temp->m_iNode[m_Temp->m_iClusterNode[m_Temp->m_iTraSelect][i]][1]-2));
					Special_point2.Draw();
					glTranslatef(m_fSize*(2-m_Temp->m_iNode[m_Temp->m_iClusterNode[m_Temp->m_iTraSelect][i]][2]),m_fSize*(2-m_Temp->m_iNode[m_Temp->m_iClusterNode[m_Temp->m_iTraSelect][i]][3]),m_fSize*(2-m_Temp->m_iNode[m_Temp->m_iClusterNode[m_Temp->m_iTraSelect][i]][1]));
				}
			}
		}
		
		else if(m_Temp->m_bMesh == TRUE && m_Temp->m_bTrasep == FALSE)
		{
			/*for(i=1; i<=m_Temp->m_iTraNo; i++)
			{
				if(m_Temp->m_iCluster[i][1] == 2 && m_Temp->m_iCluster[i][2] != 0)
				{
					glBegin(GL_LINES);
						glLineWidth(3.0);
						glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
						glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][1]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][1]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][1]][1])-1.5f));
						glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][2]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][2]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iClusterNode[i][2]][1])-1.5f));
					glEnd();
				}
			}*/

			for(i=1; i<=m_Temp->m_i2NodeBeamNo; i++)
			{
				glBegin(GL_LINES);
					glEnable(GL_LINE_SMOOTH);
					glLineWidth(10.0);
					glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
					glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i2NodeBeam[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i2NodeBeam[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i2NodeBeam[i][1]]][1])-1.5f));
					glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i2NodeBeam[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i2NodeBeam[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i2NodeBeam[i][2]]][1])-1.5f));
				glEnd();
			}

			for(i=1; i<=m_Temp->m_i3NodeBeamNo; i++)
			{
				glBegin(GL_LINES);
					glEnable(GL_LINE_SMOOTH);
					glLineWidth(15.0);
					glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
					glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][1]]][1])-1.5f));
					glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][3]]][1])-1.5f));
				glEnd();
				glBegin(GL_LINES);
					glEnable(GL_LINE_SMOOTH);
					glLineWidth(15.0);
					glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
					glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][2]]][1])-1.5f));
					glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_i3NodeBeam[i][3]]][1])-1.5f));
				glEnd();
			}
			
			for(i=1; i<m_Temp->m_iTriPointer; i++)
			{
				remain = (m_Temp->m_iTriangle[i][0])%8 + 1;//i % 8 + 1;
				switch(remain)
				{
					case 1:
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
						glEnd();
						break;
					case 2:
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
						glEnd();
						break;
					case 3:
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSScolor[0],m_fSScolor[1],m_fSScolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSScolor[0],m_fSScolor[1],m_fSScolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
						glEnd();
						break;
					case 4:
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSAcolor[0],m_fSAcolor[1],m_fSAcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fSAcolor[0],m_fSAcolor[1],m_fSAcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
						glEnd();
						break;
					case 5:
						glBegin(GL_TRIANGLES);
							glColor3f(m_fAIcolor[0],m_fAIcolor[1],m_fAIcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fAIcolor[0],m_fAIcolor[1],m_fAIcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
						glEnd();
						break;
					case 6:
						glBegin(GL_TRIANGLES);
							glColor3f(m_fAEcolor[0],m_fAEcolor[1],m_fAEcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fAEcolor[0],m_fAEcolor[1],m_fAEcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
						glEnd();
						break;
					case 7:
						glBegin(GL_TRIANGLES);
							glColor3f(m_fAAcolor[0],m_fAAcolor[1],m_fAAcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fAAcolor[0],m_fAAcolor[1],m_fAAcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
						glEnd();
						break;
					case 8:
						glBegin(GL_TRIANGLES);
							glColor3f(m_fIPcolor[0],m_fIPcolor[1],m_fIPcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
						glEnd();
						glBegin(GL_TRIANGLES);
							glColor3f(m_fIPcolor[0],m_fIPcolor[1],m_fIPcolor[2]);
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][1]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][3]]][1])-1.5f));
							glVertex3f(m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][2])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][3])-1.5f),m_fSize*(float(m_Temp->m_iNode[m_Temp->m_iNewNode[m_Temp->m_iTriangle[i][2]]][1])-1.5f));
						glEnd();
						break;
					default:
						break;
				}
			}
		}
	}
	glPopMatrix();
}

/////////////////////////////////////////////////////////////////////////////
// CTestGLView message handlers

void CTestGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
// remember where we clicked
	MouseDownPoint=point;
// capture mouse movements even outside window borders
	SetCapture();
	if(nFlags == 5)
	{
		BeginGLCommands();
		glScalef(1.05f, 1.05f, 1.05f);
		EndGLCommands();
		Invalidate(TRUE);
	}
}

void CTestGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
// forget where we clicked
	MouseDownPoint=CPoint(0,0);
// release mouse capture
	ReleaseCapture();
}

void CTestGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	MouseDownPoint = point;
	SetCapture();
}

void CTestGLView::OnRButtonUp(UINT nFlags, CPoint point)
{
	MouseDownPoint = CPoint(0,0);
	ReleaseCapture();
	if(nFlags == 4)
	{
		BeginGLCommands();
		glScalef(0.95f, 0.95f, 0.95f);
		EndGLCommands();
		Invalidate(TRUE);
	}

}

void CTestGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
// check if we have captured the mouse
	if (GetCapture()==this)
	{
		if(nFlags == MK_LBUTTON)
		{
// increment the object rotation angles
		//glTranslatef(0.5f,0.5f,0.5f);
			X_Angle+=double(point.y-MouseDownPoint.y)/3.6;
			Y_Angle+=double(point.x-MouseDownPoint.x)/3.6;
		//glTranslatef(-0.5f,-0.5f,-0.5f);
// redraw the view
			Invalidate(TRUE);
// remember the mouse point
			MouseDownPoint=point;
		}

		if(nFlags == MK_RBUTTON)
		{
			X_Distance+=double(point.x-MouseDownPoint.x)/400;
			Y_Distance+=double(-point.y+MouseDownPoint.y)/400;
			Invalidate(TRUE);
			MouseDownPoint=point;
		}

	};
}



void CTestGLView::OnEnvirLighting() 
{
	BeginGLCommands();
// toggle lighting
	if(glIsEnabled(GL_LIGHTING)) glDisable(GL_LIGHTING);
	else glEnable(GL_LIGHTING);
	EndGLCommands();
// redraw
	Invalidate(TRUE);
}

void CTestGLView::OnImageSmooth() 
{
	BeginGLCommands();
// set smooth shading
	GLint val;
	glGetIntegerv(GL_SHADE_MODEL,&val);
	if(val == GL_SMOOTH)
		glShadeModel(GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);
	EndGLCommands();
// redraw
	Invalidate(TRUE);
}

void CTestGLView::OnImageCull()
{
	BeginGLCommands();
	GLint mode;
	glGetIntegerv(GL_CULL_FACE_MODE, &mode);
	if(mode == GL_BACK)
		glCullFace(GL_FRONT);
	else
		glCullFace(GL_BACK);
	EndGLCommands();
	Invalidate(TRUE);
}

void CTestGLView::OnImageEnlarge()
{
	BeginGLCommands();
	glScalef(1.1f, 1.1f, 1.1f);
	EndGLCommands();
	Invalidate(TRUE);
}

void CTestGLView::OnImageShrink()
{
	BeginGLCommands();
	glScalef(0.9f, 0.9f, 0.9f);
	EndGLCommands();
	Invalidate(TRUE);
}

void CTestGLView::OnImageColor()
{
	CColorSelectionDialog dlg;
	dlg.DoModal();
}


/*************
NOTE: the funtions below retrieve OGL state to give some visual cue to menu items
	  but this is extremely slow (and it's been done for simplicity).
	  You should mantain local variables by which update the state of
	  menus,buttons etc.
*************/

void CTestGLView::OnUpdateImageSmooth(CCmdUI* pCmdUI) 
{
	BeginGLCommands();
// check shading mode
	GLint val;
	glGetIntegerv(GL_SHADE_MODEL,&val);
// set check accordingly
	pCmdUI->SetCheck(val==GL_SMOOTH);
	EndGLCommands();
}

void CTestGLView::OnUpdateImageCull(CCmdUI* pCmdUI)
{
	BeginGLCommands();
	GLint val;
	glGetIntegerv(GL_CULL_FACE_MODE, &val);
	pCmdUI->SetCheck(val==GL_BACK);
	EndGLCommands();
}

void CTestGLView::OnCreateDispList()
{
	CFormCommandView* m_Temp;
	m_Temp = ((CMainFrame*)AfxGetMainWnd())->m_pFormView;
	m_fSize = 1/float(mymax(m_Temp->m_iSize[0],m_Temp->m_iSize[1], m_Temp->m_iSize[2]));

	//define display list for the inner point of surface
	Surface_inner.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);

			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		//glCullFace(GL_BACK); 
		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH); 

		//glEnable(GL_BLEND); 
		//glBlendFunc(GL_SRC_ALPHA,GL_ONE); 

		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

/*		GLfloat fogColor[4]={0.6,0.6,0.0,1.0}; 
		glEnable(GL_FOG); 
		{ 
		//采用线性变化的雾化效果 
		glFogi(GL_FOG_MODE,GL_LINEAR); 
		//指定雾化颜色（黄色） 
		glFogfv(GL_FOG_COLOR,fogColor); 
		//指定按线性变化时计算公式的参量 
		glFogf(GL_FOG_START,3.0); 
		glFogf(GL_FOG_END,15.0); 
		//规定雾化效果的质量 
		glHint(GL_FOG_HINT,GL_DONT_CARE); 
		} */
	Surface_inner.EndDef();

	//define display list for the edge of surface
	Surface_edge.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);

			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH); 

		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Surface_edge.EndDef();

	//define display list for the junction points between surface and surface
	Surface_surface.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fSScolor[0],m_fSScolor[1],m_fSScolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glColor3f(m_fSScolor[0],m_fSScolor[1],m_fSScolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fSScolor[0],m_fSScolor[1],m_fSScolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Surface_surface.EndDef();

	//define display list for the junction point between surface and arc
	Surface_arc.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fSAcolor[0],m_fSAcolor[1],m_fSAcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fSAcolor[0],m_fSAcolor[1],m_fSAcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH); 
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Surface_arc.EndDef();

	//define display list for the points of the inner arc
	Arc_inner.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fAIcolor[0],m_fAIcolor[1],m_fAIcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fAIcolor[0],m_fAIcolor[1],m_fAIcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH); 
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Arc_inner.EndDef();

	//define the display list for the end point of arc
	Arc_end.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fAEcolor[0],m_fAEcolor[1],m_fAEcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fAEcolor[0],m_fAEcolor[1],m_fAEcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Arc_end.EndDef();

	//define the display list of the junction point between arcs
	Arc_arc.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fAAcolor[0],m_fAAcolor[1],m_fAAcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fAAcolor[0],m_fAAcolor[1],m_fAAcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Arc_arc.EndDef();

	//define the display list for the isolated point
	Isolated_point.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fIPcolor[0],m_fIPcolor[1],m_fIPcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fIPcolor[0],m_fIPcolor[1],m_fIPcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH); 
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Isolated_point.EndDef();

	//define the display list of the special points
	Special_point.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fScolor[0],m_fScolor[1],m_fScolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fScolor[0],m_fScolor[1],m_fScolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Special_point.EndDef();
	
	//define the display list of the special points
	Special_point2.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(m_fS2color[0],m_fS2color[1],m_fS2color[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fS2color[0],m_fS2color[1],m_fS2color[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fEGcolor[0],m_fEGcolor[1],m_fEGcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Special_point2.EndDef();
	
	//define the display list for the transparent point
	Transparent_plate.StartDef();// <- do not execute list immediately
	/*	glBegin(GL_QUADS);
			glColor3f(m_fIPcolor[0],m_fIPcolor[1],m_fIPcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fIPcolor[0],m_fIPcolor[1],m_fIPcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();*/
		glBegin(GL_LINE_LOOP);
			glLineWidth(3.0);
			glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fSEcolor[0],m_fSEcolor[1],m_fSEcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH); 
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Transparent_plate.EndDef();

	Transparent_rod.StartDef();// <- do not execute list immediately
	/*	glBegin(GL_QUADS);
			glColor3f(m_fIPcolor[0],m_fIPcolor[1],m_fIPcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(m_fIPcolor[0],m_fIPcolor[1],m_fIPcolor[2]);
			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);

			glVertex3f(m_fSize,.0f,.0f);
			glVertex3f(m_fSize,.0f,m_fSize);

			glVertex3f(m_fSize,m_fSize,.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);

			glVertex3f(0.0f,m_fSize,.0f);
			glVertex3f(0.0f,m_fSize,m_fSize);

			glVertex3f(0.0f,0.0f,.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();*/
		glBegin(GL_LINE_LOOP);
			glLineWidth(3.0);
			glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,m_fSize);
			glVertex3f(m_fSize,0.0f,m_fSize);
			glVertex3f(0.0f,0.0f,m_fSize);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(0.0f,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
			glVertex3f(0.0f,m_fSize,0.0f);
			glVertex3f(m_fSize,m_fSize,0.0f);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
			glVertex3f(0.0f,m_fSize,m_fSize);
			glVertex3f(m_fSize,m_fSize,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(3.0);
			glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,m_fSize);
		glEnd();
		glBegin(GL_LINES);
			glLineWidth(1.0);
			glColor3f(m_fSIcolor[0],m_fSIcolor[1],m_fSIcolor[2]);
			glVertex3f(m_fSize,0.0f,0.0f);
			glVertex3f(m_fSize,0.0f,m_fSize);
		glEnd();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

		glEnable(GL_CULL_FACE); 
		//using polygon antialias
		glEnable(GL_POLYGON_SMOOTH); 
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	Transparent_rod.EndDef();
}

int CTestGLView::mymax(int a, int b, int c)
{
	int temp;
	if(a>b)
		temp = a;
	else
		temp = b;

	if(temp>c)
		return temp;
	else
		return c;
}

