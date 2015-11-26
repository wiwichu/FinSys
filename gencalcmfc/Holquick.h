#if !defined(AFX_HOLQUICK_H__CC2CE451_771E_11D2_9371_00105A1E6A31__INCLUDED_)
#define AFX_HOLQUICK_H__CC2CE451_771E_11D2_9371_00105A1E6A31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Holquick.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHolquick dialog

class CHolquick : public CDialog
{
// Construction
public:
	CHolquick(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHolquick)
	enum { IDD = IDD_QuickDates };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHolquick)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHolquick)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOLQUICK_H__CC2CE451_771E_11D2_9371_00105A1E6A31__INCLUDED_)
