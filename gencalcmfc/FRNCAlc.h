#if !defined(AFX_FRNCALC_H__3F1382B1_9354_11D2_938E_00105A1E6A31__INCLUDED_)
#define AFX_FRNCALC_H__3F1382B1_9354_11D2_938E_00105A1E6A31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FRNCAlc.h : header file
//
#include "holicodeproc.h"

/////////////////////////////////////////////////////////////////////////////
// CFRNCAlc dialog

class CFRNCAlc : public CDialog,/* public cholicodeproc, */
	public Py_Front 

{
// Construction
public:
	CFRNCAlc(CWnd* pParent = NULL);   // standard constructor
	~CFRNCAlc();   // standard constructor
	CFRNCAlc(CWnd* pParent,CDB * DB_parm);   // standard constructor
	BOOL Create(CWnd* pParent = NULL);   // 

// Dialog Data
	//{{AFX_DATA(CFRNCAlc)
	enum { IDD = IDD_FRNCalc };
	CStatic	m_Interest_Days;
	CStatic	m_Interest;
	CStatic	m_Previous_Coup;
	CStatic	m_Next_Coup;
	CEdit	m_Rerate_Rate6;
	CEdit	m_Rerate_Rate5;
	CEdit	m_Rerate_Rate4;
	CEdit	m_Rerate_Rate3;
	CEdit	m_Rerate_Rate2;
	CEdit	m_Rerate_Rate1;
	CStatic	m_Rerate_Date6;
	CStatic	m_Rerate_Date5;
	CStatic	m_Rerate_Date4;
	CStatic	m_Rerate_Date3;
	CStatic	m_Rerate_Date2;
	CStatic	m_Rerate_Date1;
	CComboBox	m_Rerate_Freq;
	CButton	m_SetDates;
	CEdit	m_Value_Date;
	CEdit	m_Maturity_Date;
	CEdit	m_Issue_Date;
	CComboBox	m_Day_Count;
	CComboBox	m_Pay_Freq;
	CComboBox	m_Simp_Comp;
	CComboBox	m_Holiday_Adjust;
	CComboBox	m_Holidays;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFRNCAlc)
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
	CDB * DB_local;
	CDB::DB_Handles localhandles;
	char err_msg[80];
	int element_count;
	CDB::holiday_code_rec local_holicode;
	char holiday_adj_choice [holiday_adj_names_len];
	char simp_comp_choice [simp_comp_names_len];
	char pay_freq_choice [freq_names_len];
	char frn_pay_freq_choice [freq_names_len];
	char day_count_choice [day_count_names_len];
	char date_hold[11];
	char work_str[33];
	char *str_ptr;
	long interest_days_parm;
	long double interest_parm;
	double interest_double;
	int price_places;

	// Generated message map functions
	//{{AFX_MSG(CFRNCAlc)
	afx_msg void OnSetDates();
	afx_msg void OnSelchangeDayCount();
	afx_msg void OnSelchangeHolidays();
	afx_msg void OnSelchangeHolidaysAdjust();
	afx_msg void OnSelchangePayFreq();
	afx_msg void OnSelchangeRerateFreq();
	afx_msg void OnSelchangeSimpComp();
	afx_msg void OnCalcInterest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRNCALC_H__3F1382B1_9354_11D2_938E_00105A1E6A31__INCLUDED_)
