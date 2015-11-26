#if !defined(AFX_CHolidayCode_H__283BFE01_83A3_11D2_937E_00105A1E6A31__INCLUDED_)
#define AFX_CHolidayCode_H__283BFE01_83A3_11D2_937E_00105A1E6A31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CHolidayCode.h : header file
//
#include "holicodeproc.h"
/////////////////////////////////////////////////////////////////////////////
// CHolidayCode dialog

class CHolidayCode : public CDialog, public cholicodeproc
{
// Construction
public:
	CHolidayCode(CWnd* pParent = NULL);   // standard constructor
//	CHolidayCode(CWnd* pParent,CDB * DB_parm);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHolidayCode)
	enum { IDD = IDD_CHolidayCode };
	CEdit	m_CodeDescription;
	CEdit	m_NewCode;
	CButton	m_Update;
	CButton	m_Delete;
	CComboBox	m_CHolidayCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHolidayCode)
	virtual BOOL Create( CWnd* pParentWnd);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	unsigned long return_state;
	int * TotalCodes;
	char (*holicode) [holidaycodelength];
	char holicodehold [holidaycodelength];
	BOOL	return_BOOL;
//	CDB * DB_local;
//	CDB::DB_Handles localhandles;
	char err_msg[80];
	int element_count;
//	CDB::holiday_code_rec local_holicode;
	// Generated message map functions
	//{{AFX_MSG(CHolidayCode)
	afx_msg void OnSelchangeCHolidayCode();
	afx_msg void OnUpdateCode();
	afx_msg void OnDeleteCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHolidayCode_H__283BFE01_83A3_11D2_937E_00105A1E6A31__INCLUDED_)
