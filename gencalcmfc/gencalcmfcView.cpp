// gencalcmfcView.cpp : implementation of the CGencalcmfcView class
//

#include "stdafx.h"
#include "gencalcmfc.h"

#include "gencalcmfcDoc.h"
#include "gencalcmfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcView

IMPLEMENT_DYNCREATE(CGencalcmfcView, CView)

BEGIN_MESSAGE_MAP(CGencalcmfcView, CView)
	//{{AFX_MSG_MAP(CGencalcmfcView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcView construction/destruction

CGencalcmfcView::CGencalcmfcView()
{
	// TODO: add construction code here

}

CGencalcmfcView::~CGencalcmfcView()
{
}

BOOL CGencalcmfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcView drawing

void CGencalcmfcView::OnDraw(CDC* pDC)
{
	CGencalcmfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcView printing

BOOL CGencalcmfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGencalcmfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGencalcmfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcView diagnostics

#ifdef _DEBUG
void CGencalcmfcView::AssertValid() const
{
	CView::AssertValid();
}

void CGencalcmfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGencalcmfcDoc* CGencalcmfcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGencalcmfcDoc)));
	return (CGencalcmfcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcView message handlers
