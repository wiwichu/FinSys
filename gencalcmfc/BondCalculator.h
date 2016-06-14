#if !defined(AFX_BONDCALCULATOR_H__9E86AC80_E1A3_11D1_8F5B_A04D05C10000__INCLUDED_)
#define AFX_BONDCALCULATOR_H__9E86AC80_E1A3_11D1_8F5B_A04D05C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BondCalculator.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBondCalculator dialog

#include "pyfront.h"

class CBondCalculator : public CDialog, public Py_Front
// , public cholicodeproc
{
// Construction
public:
	CBondCalculator(CWnd* pParent = NULL);   // standard constructor
//	CBondCalculator(CWnd* pParent, CDB * DB_parm);   // standard constructor
	~CBondCalculator();   // destructor

// Dialog Data
	//{{AFX_DATA(CBondCalculator)
	enum { IDD = IDD_BondCalculator };
	CStatic	m_Label_Prepay;
	CComboBox	m_Combo_Prepay;
	CStatic	m_Label_Lag;
	CEdit	m_Edit_Lag;
	CStatic	m_Static_Service_Fee;
	CEdit	m_Edit_Service_Fee;
	CComboBox	m_Holidays;
	CStatic	m_Convexity;
	CStatic	m_ModDuration;
	CStatic	m_pvbp;
	CStatic	m_Duration;
	CStatic	m_DirtyPrice;
	CStatic	m_AccruedInterest;
	CStatic	m_InterestDays;
	CStatic	m_NextCoup;
	CStatic	m_PreviousCoup;
	CButton	m_Calculate;
	CEdit	m_Issue_Date;
	CEdit	m_First_Pay;
	CEdit	m_ValueDate;
	CEdit	m_Next_To_Last_Pay;
	CEdit	m_MaturityDate;
	CButton	m_DefaultDates;
	CButton	m_y_from_p;
	CButton	m_p_from_y;
	CButton	m_CalcChoice;
	CStatic	m_Excoup_Days;
	CComboBox	m_YieldFreq;
	CComboBox	m_Excoup;
	CComboBox	m_EOM;
	CComboBox	m_YieldDays;
	CEdit	m_YieldDiscount;
	CEdit	m_CleanPrice;
	CEdit	m_InterestRate;
	CComboBox	m_YieldMeth;
	CComboBox	m_PayFreq;
	CComboBox	m_DayCount;
	CComboBox	m_InstrClass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBondCalculator)
	virtual BOOL Create( CWnd* pParentWnd);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBondCalculator)
	afx_msg void OnSelchangeCOMBODayCount();
	afx_msg void OnSelchangeCOMBOPayFrequency();
	afx_msg void OnSelchangeCOMBOYieldDays();
	afx_msg void OnSelchangeCOMBOYieldFrequency();
	afx_msg void OnSelchangeCOMBOYieldmethod();
	afx_msg void OnSelchangeCOMBOInstrumentClass();
	afx_msg void OnRADIO1PricefromYield();
	afx_msg void OnRADIO1YieldfromPrice();
	afx_msg void OnDefaultDates();
	afx_msg void OnSelchangeComboEom();
	afx_msg void OnSelchangeCOMBOExCoup();
	afx_msg void OnCalculate();
	afx_msg void OnSelchangeCOMBOHolidays();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL	return_BOOL;
	size_t dummy_size_t;
	long interest_days_parm;
	long double interest_parm;
	double interest_double;
	int price_places;
	long double	dirt_price;
	long double	nominal_adj_parm;
	char *str_ptr;
	int active_type;
	int Calc_type;
	int FRN_type;
	char pay_type_control;
	char date_hold[11];
	char err_msg[80];
	unsigned long return_status;
	unsigned int element_count;
	int dummy_int;
	char class_desc_hold [instr_class_desc_len];
	int TotalCodes;
//	char (*holicode) [holidaycodelength];
//	char holicodehold [holidaycodelength];
	char day_count_hold [day_count_names_len];
	char pay_freq_hold [freq_names_len];
	char yieldmeth_name_hold [yield_names_len];
	long double	dummy_long_double;
	char yieldfreq_name_hold [freq_names_len];
	char month_end_hold [monthend_names_len];
	char excoup_name_hold[excoup_name_length];
	char work_str[33];
	char yielddays_name_hold [day_count_names_len];
	int class_number;
	int day_count_number;
	int pay_freq_number;
	int yield_days_number;
	int yield_freq_number;
	int yield_meth_number;
	int month_end_number;
	int excoup_number;
	int prepay_number;
	char current_calc_what;
	char prepay_type_name [prepay_type_names_len];
// 	Py_Front pyfront;
	
	void InitInstrClass();
	void InitHolidays();
	void InitDayCount();
	void InitFreqCount();
	void InitYieldMeth();
	void InitIntRate();
	void InitPrice();
	void InitYield();
	void InitYieldDays();
	void InitYieldFreq();
	void InitMonthEnd();
	void InitExCoup();
	void InitExCoupDays();
	void InitCalcChoice();
	void InitServiceFee();
	void InitLag();
	void InitPrepay();
	unsigned long CheckDates(  );
    void InitDateHold(char *, int);
//	CDB * DB_local;
//	CDB::DB_Handles localhandles;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BONDCALCULATOR_H__9E86AC80_E1A3_11D1_8F5B_A04D05C10000__INCLUDED_)
