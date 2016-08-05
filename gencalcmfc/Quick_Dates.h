#if !defined(AFX_QUICK_DATES_H__34902E80_AC3A_11D1_8F5B_44455354616F__INCLUDED_)
#define AFX_QUICK_DATES_H__34902E80_AC3A_11D1_8F5B_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Quick_Dates.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Quick_Dates dialog

class Quick_Dates : public CDialog
{
// Construction
public:
	Quick_Dates(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Quick_Dates)
	enum { IDD = IDD_Quick_Dates };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Quick_Dates)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Quick_Dates)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUICK_DATES_H__34902E80_AC3A_11D1_8F5B_44455354616F__INCLUDED_)
