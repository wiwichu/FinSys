// gencalcmfcDoc.h : interface of the CGencalcmfcDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENCALCMFCDOC_H__C6E1EA0D_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_)
#define AFX_GENCALCMFCDOC_H__C6E1EA0D_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGencalcmfcDoc : public CDocument
{
protected: // create from serialization only
	CGencalcmfcDoc();
	DECLARE_DYNCREATE(CGencalcmfcDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGencalcmfcDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGencalcmfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGencalcmfcDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENCALCMFCDOC_H__C6E1EA0D_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_)
