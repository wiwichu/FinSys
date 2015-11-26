// gencalcmfcView.h : interface of the CGencalcmfcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENCALCMFCVIEW_H__C6E1EA0F_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_)
#define AFX_GENCALCMFCVIEW_H__C6E1EA0F_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGencalcmfcView : public CView
{
protected: // create from serialization only
	CGencalcmfcView();
	DECLARE_DYNCREATE(CGencalcmfcView)

// Attributes
public:
	CGencalcmfcDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGencalcmfcView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGencalcmfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGencalcmfcView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in gencalcmfcView.cpp
inline CGencalcmfcDoc* CGencalcmfcView::GetDocument()
   { return (CGencalcmfcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENCALCMFCVIEW_H__C6E1EA0F_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_)
