// DisplayDoc.cpp : implementation of the CDisplayDoc class
//

#include "stdafx.h"
#include "Display.h"

#include "DisplayDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayDoc

IMPLEMENT_DYNCREATE(CDisplayDoc, CDocument)

BEGIN_MESSAGE_MAP(CDisplayDoc, CDocument)
	//{{AFX_MSG_MAP(CDisplayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayDoc construction/destruction

CDisplayDoc::CDisplayDoc()
{
	// TODO: add one-time construction code here

}

CDisplayDoc::~CDisplayDoc()
{
}

BOOL CDisplayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDisplayDoc serialization

void CDisplayDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayDoc diagnostics

#ifdef _DEBUG
void CDisplayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDisplayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDisplayDoc commands
