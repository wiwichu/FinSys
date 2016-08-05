#if !defined(AFX_BONDCALCSCREEN_H__F25D7042_5A6D_11D1_8F5B_444553540000__INCLUDED_)
#define AFX_BONDCALCSCREEN_H__F25D7042_5A6D_11D1_8F5B_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BondCalcScreen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBondCalcScreen dialog

class CBondCalcScreen : public CDialog
{
// Construction
public:
	CBondCalcScreen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBondCalcScreen)
	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBondCalcScreen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBondCalcScreen)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BONDCALCSCREEN_H__F25D7042_5A6D_11D1_8F5B_444553540000__INCLUDED_)
