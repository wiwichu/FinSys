// gencalcmfc.h : main header file for the GENCALCMFC application
//

#if !defined(AFX_GENCALCMFC_H__C6E1EA05_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_)
#define AFX_GENCALCMFC_H__C6E1EA05_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
#include "stdafx.h"
//	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ChildFrm.h"       // Child Frame Symbols
#include "BondCalcWnd.h"   // Bond Calc Window symbols
//#include "Holidays.h"   // Holidays Window symbols
//#include "HolidayCode.h"   // Holiday Code Window symbols
//#include "db.h"   // Data Base Class Header
//#include "FRNCAlc.h"   // FRN Calcs

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcApp:
// See gencalcmfc.cpp for the implementation of this class
//

class CBondCalc	: public CChildFrame 
{
	DECLARE_DYNCREATE(CBondCalc)

};

class CGencalcmfcApp : public CWinApp
{
private:

	char db_type;
//	CDB * DB_Local;
public:
	 CBondCalcWnd BondCalcWnd();
//	 CHolidays Holidays();
	CGencalcmfcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGencalcmfcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGencalcmfcApp)
	afx_msg void OnAppAbout();
	afx_msg void OnBondCalc();
	afx_msg void OnHolidays();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnDatesQuickholiday();
	afx_msg void OnCalculatorRatecurves();
	afx_msg void OnCalculatorNewbond();
	afx_msg void OnHolidayCode();
	afx_msg void OnCalculatorFrns();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENCALCMFC_H__C6E1EA05_88DC_11CE_BB90_C17FF8B0F91A__INCLUDED_)
