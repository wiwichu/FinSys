#if !defined(AFX_RATECURVESSCREEN_H__F302E0E0_AE94_11D1_8F5B_44455354616F__INCLUDED_)
#define AFX_RATECURVESSCREEN_H__F302E0E0_AE94_11D1_8F5B_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RateCurvesScreen.h : header file
//
#include <RateCurve.h>
/////////////////////////////////////////////////////////////////////////////
// RateCurvesScreen dialog

class RateCurvesScreen : public CDialog, 
						 public CRateCurve,
						 virtual public _errtext
{
// Construction
public:
	RateCurvesScreen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RateCurvesScreen)
	enum { IDD = IDD_RateCurves };
	CListBox	m_ListCurve;
	CListBox	m_BootResult;
	CEdit	m_Term2;
	CEdit	m_Term1;
	CEdit	m_StartDate;
	CEdit	m_Rate1;
	CEdit	m_EndDate;
	CEdit	m_ValueDate;
	CComboBox	m_DayAdjust;
	CComboBox	m_EOM;
	CComboBox	m_DayCount;
	CComboBox	m_Freq;
	CComboBox	m_TermUnits;
	CComboBox	m_Source;
	CComboBox	m_InstrType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RateCurvesScreen)
	public:
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL Create( CWnd* pParentWnd);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:

		char rc_type_names_list [rc_type_count] [rc_type_name_size];
		char rc_source_names_list [rc_source_count] [rc_source_name_size];
		char rc_unit_names_list [rc_unit_count] [rc_unit_name_size];
		char rc_freq_names_list [freq_count] [freq_names_len];
		char rc_day_count_names_list [date_last_day_count] [day_count_names_len];
		char rc_EOM_names_list [monthend_count] [monthend_names_len];
		char rc_dayadjust_names_list[ rc_dayadjust_count ] [holiday_adj_names_len ];

		char RateInstrText[rc_max_instr][RateInstrTextSize];
		char BootText[rc_max_boot_results][BootTextSize];
		RateInstr *RateInstrArray;
		RateCurve *RateCurveArray;
		char TotalInstr;
		char TotalBoot;

protected:

	// Generated message map functions
	//{{AFX_MSG(RateCurvesScreen)
	afx_msg void OnSelchangeCOMBOType1();
	afx_msg void OnSelchangeCOMBOSource();
	afx_msg void OnSelchangeCOMBOUnit1();
	afx_msg void OnSelchangeCOMBODayCount1();
	afx_msg void OnSelchangeComboEom1();
	afx_msg void OnSelchangeCOMBODayAdjust1();
	afx_msg void OnSelchangeCOMBOFrequency1();
	afx_msg void OnAdd();
	afx_msg void OnSelectInstr();
	afx_msg void OnRemove();
	afx_msg void OnBoot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RATECURVESSCREEN_H__F302E0E0_AE94_11D1_8F5B_44455354616F__INCLUDED_)
