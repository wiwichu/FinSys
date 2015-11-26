// gencalcmfcDoc.cpp : implementation of the CGencalcmfcDoc class
//

#include "stdafx.h"
#include "gencalcmfc.h"

#include "gencalcmfcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcDoc

IMPLEMENT_DYNCREATE(CGencalcmfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CGencalcmfcDoc, CDocument)
	//{{AFX_MSG_MAP(CGencalcmfcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcDoc construction/destruction

CGencalcmfcDoc::CGencalcmfcDoc()
{
	// TODO: add one-time construction code here

}

CGencalcmfcDoc::~CGencalcmfcDoc()
{
}

BOOL CGencalcmfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcDoc serialization

void CGencalcmfcDoc::Serialize(CArchive& ar)
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
// CGencalcmfcDoc diagnostics

#ifdef _DEBUG
void CGencalcmfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGencalcmfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcDoc commands
