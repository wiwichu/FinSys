#if !defined(AFX_FASTDATES_H__98FE5D71_921D_11D2_938C_00105A1E6A31__INCLUDED_)
#define AFX_FASTDATES_H__98FE5D71_921D_11D2_938C_00105A1E6A31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FastDates.h : header file
//
//#include "holihead.h"
#include "datedec.h"
#include "guidecs.h"
#include "resource.h"       // main symbols
#include "db.h"   // Data Base Class Header

/////////////////////////////////////////////////////////////////////////////
// CFastDates dialog

class CFastDates : public CDialog, public holidays_class, public cholicodeproc
{
// Construction
public:
	CFastDates(CWnd* pParent = NULL);   // standard constructor
	~CFastDates();   // destructor
	CFastDates(CWnd* pParent, CDB * DB_parm);   // standard constructor
	BOOL Create(CWnd* pParent = NULL);   // 
	BOOL SetDB(CDB *);           

// Dialog Data
	//{{AFX_DATA(CFastDates)
	enum { IDD = IDD_FastDates };
	CButton	m_Test;
	CButton	m_Delete;
	CButton	m_Cancel;
	CButton	m_Add;
	CEdit	m_Holiday_Year;
	CComboBox	m_Holiday_Month;
	CComboBox	m_Holiday_Day;
	CComboBox	m_Code;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFastDates)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	char holicodehold [holidaycodelength];
	CDB::DB_Handles localhandles;
	char err_msg[80];
	unsigned long return_state;
	char dummy_char;
	char db_type;
	char holiday_code_hold [holidaycodelength];
	char holiday_year_hold [holidayyearlength];
	char hold_msg[80];
	BOOL return_BOOL;
	unsigned int return_status;
	int * TotalCodes;
	int element_count;
	char monthhold [month_names_length];
	char currentmonth;
	char dayhold [holidaybasedaylength];
	char currentday;
	void InitHolidayBaseMonth();
	void InitHolidayBaseDay();
	CDB * DB_local;
	holidays_class * holidaysclass;


	// Generated message map functions
	//{{AFX_MSG(CFastDates)
	afx_msg void OnSelchangeCOMBOHolidayMonth();
	afx_msg void OnSelchangeCOMBOHolidayDay();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnTest();
	afx_msg void OnSelchangeCOMBOCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTDATES_H__98FE5D71_921D_11D2_938C_00105A1E6A31__INCLUDED_)
