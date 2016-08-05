// RateCurvesScreen.cpp : implementation file
//

#include "stdafx.h"
#include "math.h"
#include "gencalcmfc.h"
#include "RateCurvesScreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RateCurvesScreen dialog


RateCurvesScreen::RateCurvesScreen(CWnd* pParent /*=NULL*/)
	: CDialog(RateCurvesScreen::IDD, pParent)
{
	//{{AFX_DATA_INIT(RateCurvesScreen)
	//}}AFX_DATA_INIT
}


void RateCurvesScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RateCurvesScreen)
	DDX_Control(pDX, IDC_LIST_Curve, m_ListCurve);
	DDX_Control(pDX, IDC_LIST_Boot_Result, m_BootResult);
	DDX_Control(pDX, IDC_EDIT_Term2_1, m_Term2);
	DDX_Control(pDX, IDC_EDIT_Term1_1, m_Term1);
	DDX_Control(pDX, IDC_EDIT_Start_Date, m_StartDate);
	DDX_Control(pDX, IDC_EDIT_Rate_1, m_Rate1);
	DDX_Control(pDX, IDC_EDIT_End_Date, m_EndDate);
	DDX_Control(pDX, IDC_EDIT_Value_Date, m_ValueDate);
	DDX_Control(pDX, IDC_COMBO_DayAdjust_1, m_DayAdjust);
	DDX_Control(pDX, IDC_COMBO_EOM_1, m_EOM);
	DDX_Control(pDX, IDC_COMBO_DayCount_1, m_DayCount);
	DDX_Control(pDX, IDC_COMBO_Frequency_1, m_Freq);
	DDX_Control(pDX, IDC_COMBO_Unit_1, m_TermUnits);
	DDX_Control(pDX, IDC_COMBO_Source, m_Source);
	DDX_Control(pDX, IDC_COMBO_Type_1, m_InstrType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RateCurvesScreen, CDialog)
	//{{AFX_MSG_MAP(RateCurvesScreen)
	ON_CBN_SELCHANGE(IDC_COMBO_Type_1, OnSelchangeCOMBOType1)
	ON_CBN_SELCHANGE(IDC_COMBO_Source, OnSelchangeCOMBOSource)
	ON_CBN_SELCHANGE(IDC_COMBO_Unit_1, OnSelchangeCOMBOUnit1)
	ON_CBN_SELCHANGE(IDC_COMBO_DayCount_1, OnSelchangeCOMBODayCount1)
	ON_CBN_SELCHANGE(IDC_COMBO_EOM_1, OnSelchangeComboEom1)
	ON_CBN_SELCHANGE(IDC_COMBO_DayAdjust_1, OnSelchangeCOMBODayAdjust1)
	ON_CBN_SELCHANGE(IDC_COMBO_Frequency_1, OnSelchangeCOMBOFrequency1)
	ON_BN_CLICKED(IDOK_Add, OnAdd)
	ON_BN_CLICKED(IDOK_Select, OnSelectInstr)
	ON_BN_CLICKED(IDOK_Remove, OnRemove)
	ON_BN_CLICKED(IDOK_Boot, OnBoot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RateCurvesScreen message handlers

BOOL RateCurvesScreen::Create( CWnd* pParentWnd) 
{
	BOOL	return_BOOL = TRUE;
	unsigned long return_state;
	int element_count;
	char HoldStr[rc_type_name_size];

	// TODO: Add your specialized code here and/or call the base class

	return_state = InitTypeNames(rc_type_names_list);

	if (return_state != return_success)
	{

		return FALSE;

	}

	return_state = InitSourceNames(rc_source_names_list);

	if (return_state != return_success)
	{

		return FALSE;

	}

	return_state = InitUnitNames(rc_unit_names_list);

	if (return_state != return_success)
	{

		return FALSE;

	}

	return_state = InitFreqNames(rc_freq_names_list);

	if (return_state != return_success)
	{

		return FALSE;

	}

	return_state = InitDayCountNames(rc_day_count_names_list);

	if (return_state != return_success)
	{

		return FALSE;

	}

	return_state = InitEOMNames(rc_EOM_names_list);

	if (return_state != return_success)
	{

		return FALSE;

	}

	return_state = InitDayAdjustNames(rc_dayadjust_names_list);

	if (return_state != return_success)
	{

		return FALSE;

	}

//	return CDialog::Create(IDD, pParentWnd);
	return_BOOL = CDialog::Create(IDD, pParentWnd);

	if (return_BOOL == FALSE)
	{
		return FALSE;

	}
	
	for (element_count = 0; element_count <
	  rc_type_count; ++element_count)
	{

		m_InstrType.AddString(rc_type_names_list[element_count]);

	}
	m_InstrType.SetCurSel(0);
	
	for (element_count = 0; element_count <
	  rc_source_count; ++element_count)
	{

		m_Source.AddString(rc_source_names_list[element_count]);

	}
	m_Source.SetCurSel(0);
	
	for (element_count = 0; element_count <
	  rc_unit_count; ++element_count)
	{

		m_TermUnits.AddString(rc_unit_names_list[element_count]);

	}
	m_TermUnits.SetCurSel(0);
	
	for (element_count = 0; element_count <
	  freq_count; ++element_count)
	{

		m_Freq.AddString(rc_freq_names_list[element_count]);

	}
	m_Freq.SetCurSel(0);
	
	for (element_count = 0; element_count <
	  date_last_day_count; ++element_count)
	{

		m_DayCount.AddString(rc_day_count_names_list[element_count]);

	}
	m_DayCount.SetCurSel(0);
	
	
	for (element_count = 0; element_count <
	  monthend_count; ++element_count)
	{

		m_EOM.AddString(rc_EOM_names_list[element_count]);

	}
	m_EOM.SetCurSel(0);
	
	
	for (element_count = 0; element_count <
	  rc_dayadjust_count; ++element_count)
	{

		m_DayAdjust.AddString(rc_dayadjust_names_list[element_count]);

	}
	m_DayAdjust.SetCurSel(0);

	OnSelchangeCOMBOType1();

	return return_BOOL;

}

void RateCurvesScreen::OnSelchangeCOMBOType1() 
{
	unsigned long return_state;
	char err_msg[80];
	char dummy_char;

	char HoldStr[rc_type_name_size];
	char UnitStr[rc_unit_name_size];
	char DayCountStr[day_count_names_len];
	char EOMStr[monthend_names_len];
	char DayAdjustStr[holiday_adj_names_len];
	char FreqStr[freq_names_len];


	// TODO: Add your control notification handler code here
	m_InstrType.GetWindowText(HoldStr,sizeof(HoldStr));

	return_state = SetRCType(HoldStr);

	if (return_state != return_success)
	{


		goto func_end;

	}

	return_state = GetRCUnit(UnitStr);

	if (return_state != return_success)
	{
		goto func_end;
	}


	return_state = GetRCDayCount(DayCountStr);

	if (return_state != return_success)
	{
		goto func_end;
	}


	return_state = GetRCEOM(EOMStr);

	if (return_state != return_success)
	{
		goto func_end;
	}


	return_state = GetRCDayAdjust(DayAdjustStr);

	if (return_state != return_success)
	{
		goto func_end;
	}


	return_state = GetRCFrequencyState(&dummy_char);

	if (return_state != return_success)
	{
		goto func_end;
	}
	
	if (dummy_char == enabled_no)
	{

		m_Freq.EnableWindow(FALSE);	
	
	}
	else
	{

		m_Freq.EnableWindow(TRUE);	

		return_state = GetRCFrequency(FreqStr);

		if (return_state != return_success)
		{
			goto func_end;
		}
		m_Freq.SelectString(-1,FreqStr);
	}

	return_state = GetRCTerm2State(&dummy_char);

	if (return_state != return_success)
	{
		goto func_end;
	}
	
	if (dummy_char == enabled_no)
	{

		m_Term2.EnableWindow(FALSE);	
	
	}
	else
	{

		m_Term2.EnableWindow(TRUE);	
	
	
	}

	m_InstrType.SelectString(-1,HoldStr);
	m_TermUnits.SelectString(-1,UnitStr);
	m_DayCount.SelectString(-1,DayCountStr);
	m_DayAdjust.SelectString(-1,DayAdjustStr);
	m_EOM.SelectString(-1,EOMStr);

func_end:

	if (return_state != return_success)
	{
	
		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);


	}
	
}

void RateCurvesScreen::OnSelchangeCOMBOSource() 
{
	// TODO: Add your control notification handler code here
	unsigned long return_state;
	int element_count;
	char err_msg[80];

	char HoldStr[rc_source_name_size];

	m_Source.GetWindowText(HoldStr,sizeof(HoldStr));

	return_state = SetRCSource(RateInstrText,HoldStr,&TotalInstr);

	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_rate_curve_source,MB_OK);

//		goto func_end;

	}
//func_end:
	m_EOM.SelectString(-1,HoldStr);

	m_ListCurve.ResetContent();

	for (element_count = 0;element_count < TotalInstr;++element_count)
	{

		m_ListCurve.AddString(RateInstrText[element_count]);

	}
	
}

void RateCurvesScreen::OnSelchangeCOMBOUnit1() 
{
	// TODO: Add your control notification handler code here
	unsigned long return_state;
	char err_msg[80];

	char HoldStr[rc_unit_name_size];

	m_TermUnits.GetWindowText(HoldStr,sizeof(HoldStr));

	return_state = SetRCUnit(HoldStr);

	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_rate_curve_unit,MB_OK);

//		goto func_end;

	}
//func_end:
	
	m_TermUnits.SelectString(-1,HoldStr);
	
}

void RateCurvesScreen::OnSelchangeCOMBODayCount1() 
{
	// TODO: Add your control notification handler code here
	unsigned long return_state;
	char err_msg[80];

	char HoldStr[day_count_names_len];

	m_DayCount.GetWindowText(HoldStr,sizeof(HoldStr));

	return_state = SetRCDayCount(HoldStr);

	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_day_count_method_colon	,MB_OK);

//		goto func_end;

	}
//func_end:
	
	m_DayCount.SelectString(-1,HoldStr);

}

void RateCurvesScreen::OnSelchangeComboEom1() 
{
	// TODO: Add your control notification handler code here
	unsigned long return_state;
	char err_msg[80];

	char HoldStr[monthend_names_len];

	m_EOM.GetWindowText(HoldStr,sizeof(HoldStr));

	return_state = SetRCEOM(HoldStr);

	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_month_end,MB_OK);

//		goto func_end;

	}
//func_end:
	
	m_EOM.SelectString(-1,HoldStr);
	
}

void RateCurvesScreen::OnSelchangeCOMBODayAdjust1() 
{
	// TODO: Add your control notification handler code here
	unsigned long return_state;
	char err_msg[80];

	char HoldStr[holiday_adj_names_len];

	m_DayAdjust.GetWindowText(HoldStr,sizeof(HoldStr));

	return_state = SetRCDayAdjust(HoldStr);

	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_holiday_adjust_times_colon,MB_OK);

//		goto func_end;

	}
//func_end:
	m_DayAdjust.SelectString(-1,HoldStr);
	
}

void RateCurvesScreen::OnSelchangeCOMBOFrequency1() 
{
	// TODO: Add your control notification handler code here
	unsigned long return_state;
	char err_msg[80];

	char HoldStr[freq_names_len];

	m_Freq.GetWindowText(HoldStr,sizeof(HoldStr));

	return_state = SetRCFrequency(HoldStr);

	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_pay_freq_colon,MB_OK);

//		goto func_end;

	}
//func_end:
	m_Freq.SelectString(-1,HoldStr);
	
}

void RateCurvesScreen::OnAdd() 
{
	// TODO: Add your control notification handler code here
	unsigned short dummy_ushort;
	long double dummy_ld;
	char dummy_char;
	unsigned long return_state;
	char err_msg[80];
	int element_count;
	char *str_ptr;

	char TypeStr[rc_type_name_size];
	char TermStr[rc_term_size];
	char SourceStr[rc_source_name_size];
	char UnitStr[rc_unit_name_size];
	char DayCountStr[day_count_names_len];
	char EOMStr[monthend_names_len];
	char DayAdjustStr[holiday_adj_names_len];
	char FreqStr[freq_names_len];
	char RateStr[rc_rate_size];

	m_InstrType.GetWindowText(TypeStr,sizeof(TypeStr));
	return_state = SetRCType(TypeStr);
	if (return_state != return_success)
	{
		errtext(return_state, err_msg);
		::MessageBox(NULL,err_msg,"",MB_OK);
	}
/*
	m_Source.GetWindowText(SourceStr,sizeof(SourceStr));
	return_state = SetRCSource(RateInstrText,SourceStr,&dummy_char);
	if (return_state != return_success)
	{
		errtext(return_state, err_msg);
		::MessageBox(NULL,err_msg,"",MB_OK);
	}
*/ 
	m_TermUnits.GetWindowText(UnitStr,sizeof(UnitStr));
	return_state = SetRCUnit(UnitStr);
	if (return_state != return_success)
	{
		errtext(return_state, err_msg);
		::MessageBox(NULL,err_msg,"",MB_OK);
	}
	m_DayCount.GetWindowText(DayCountStr,sizeof(DayCountStr));
	return_state = SetRCDayCount(DayCountStr);
	if (return_state != return_success)
	{
		errtext(return_state, err_msg);
		::MessageBox(NULL,err_msg,"",MB_OK);
	}
	m_EOM.GetWindowText(EOMStr,sizeof(EOMStr));
	return_state = SetRCEOM(EOMStr);
	if (return_state != return_success)
	{
		errtext(return_state, err_msg);
		::MessageBox(NULL,err_msg,"",MB_OK);
	}
	m_DayAdjust.GetWindowText(DayAdjustStr,sizeof(DayAdjustStr));
	return_state = SetRCDayAdjust(DayAdjustStr);
	if (return_state != return_success)
	{
		errtext(return_state, err_msg);
		::MessageBox(NULL,err_msg,"",MB_OK);
	}
	m_Freq.GetWindowText(FreqStr,sizeof(FreqStr));
	return_state = SetRCFrequency(FreqStr);
	if (return_state != return_success)
	{
		errtext(return_state, err_msg);
		::MessageBox(NULL,err_msg,"",MB_OK);
	}

	m_Term1.GetWindowText(TermStr,sizeof(TermStr));

	dummy_ushort = atoi(TermStr);	

	SetRCTerm1(dummy_ushort);
	
	m_Term2.GetWindowText(TermStr,sizeof(TermStr));

	dummy_ushort = atoi(TermStr);	

	SetRCTerm2(dummy_ushort);
	
	m_Rate1.GetWindowText(RateStr,sizeof(RateStr));

	dummy_ld = strtod(RateStr, &str_ptr);	

	SetRCRate1(dummy_ld);

	return_state = AddRCInstr(RateInstrText,&TotalInstr);

	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

//		goto func_end;

	}
	else
	{

		m_ListCurve.ResetContent();

		for (element_count = 0;element_count < TotalInstr;++element_count)
		{

			m_ListCurve.AddString(RateInstrText[element_count]);

		}
	}



}

void RateCurvesScreen::OnSelectInstr() 
{
	// TODO: Add your control notification handler code here
	unsigned long return_state;
	char err_msg[80];
	char dummy_char;

	char HoldStr[rc_type_name_size];
	char UnitStr[rc_unit_name_size];
	char DayCountStr[day_count_names_len];
	char EOMStr[monthend_names_len];
	char DayAdjustStr[holiday_adj_names_len];
	char FreqStr[freq_names_len];
	char Term1Str[rc_term_size];
	char Term2Str[rc_term_size];
	char Rate1Str[rc_rate_size];
	unsigned short Term1Value;
	unsigned short Term2Value;
	long double Rate1Value;
	int Instr_Selection;

	Instr_Selection = m_ListCurve.GetCurSel();

	if (LB_ERR == Instr_Selection)
	{

		return_state = return_err_LB_ERR_no_select;

		goto func_end;

	}

	return_state = SelectRCInstr(Instr_Selection);	

	if (return_state != return_success)
	{

		goto func_end;

	}


	return_state = GetRCType(HoldStr);

	if (return_state != return_success)
	{
		goto func_end;
	}

	return_state = GetRCUnit(UnitStr);

	if (return_state != return_success)
	{
		goto func_end;
	}


	return_state = GetRCDayCount(DayCountStr);

	if (return_state != return_success)
	{
		goto func_end;
	}


	return_state = GetRCEOM(EOMStr);

	if (return_state != return_success)
	{
		goto func_end;
	}


	return_state = GetRCDayAdjust(DayAdjustStr);

	if (return_state != return_success)
	{
		goto func_end;
	}


	return_state = GetRCFrequencyState(&dummy_char);

	if (return_state != return_success)
	{
		goto func_end;
	}
	
	if (dummy_char == enabled_no)
	{

		m_Freq.EnableWindow(FALSE);	
	
	}
	else
	{

		m_Freq.EnableWindow(TRUE);	

		return_state = GetRCFrequency(FreqStr);

		if (return_state != return_success)
		{
			goto func_end;
		}

		m_Freq.SelectString(-1,FreqStr);

	}

	return_state = GetRCTerm1(&Term1Value);

	if (return_state != return_success)
	{
		goto func_end;
	}

	_itoa( Term1Value, Term1Str, 10 );

	return_state = GetRCRate1(&Rate1Value);

	if (return_state != return_success)
	{
		goto func_end;
	}

	gcvt( Rate1Value, rate_precision, Rate1Str );


	return_state = GetRCTerm2State(&dummy_char);

	if (return_state != return_success)
	{
		goto func_end;
	}
	
	if (dummy_char == enabled_no)
	{

		m_Term2.EnableWindow(FALSE);	
	
	}
	else
	{

		m_Term2.EnableWindow(TRUE);	

		return_state = GetRCTerm2(&Term2Value);

		if (return_state != return_success)
		{
			goto func_end;
		}

		_itoa( Term2Value, Term2Str, 10 );
		m_Term2.SetWindowText(Term2Str);
	
	
	}

	m_InstrType.SelectString(-1,HoldStr);
	m_TermUnits.SelectString(-1,UnitStr);
	m_DayCount.SelectString(-1,DayCountStr);
	m_DayAdjust.SelectString(-1,DayAdjustStr);
	m_EOM.SelectString(-1,EOMStr);
	m_Term1.SetWindowText(Term1Str);
	m_Rate1.SetWindowText(Rate1Str);

func_end:

	if (return_state != return_success)
	{
	
		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);


	}

}

void RateCurvesScreen::OnRemove() 
{
	// TODO: Add your control notification handler code here
	char err_msg[80];
	int element_count;
	int Instr_Selection;
	unsigned long return_state;

	Instr_Selection = m_ListCurve.GetCurSel();

	if (LB_ERR == Instr_Selection)
	{

		return_state = return_err_LB_ERR_no_select;

		goto func_end;

	}

 	return_state = DeleteRCInstr(Instr_Selection );

	if (return_state != return_success)
	{

		goto func_end;

	}

	return_state = GetRCInstrText(RateInstrText, &TotalInstr);

	if (return_state != return_success)
	{

		goto func_end;

	}

	m_ListCurve.ResetContent();

    for (element_count = 0;element_count < TotalInstr;++element_count)
	{

		m_ListCurve.AddString(RateInstrText[element_count]);

	}

func_end:
	
	if (return_state != return_success)
	{
	
		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);


	}

}

void RateCurvesScreen::OnBoot() 
{
	// TODO: Add your control notification handler code here
	char date_hold[rc_date_len];	
	unsigned long return_state;
	char err_msg[80];
	int element_count;

	m_ValueDate.GetWindowText(date_hold,sizeof(date_hold));

	return_state = SetRCValDate(date_hold);

	if (return_state != return_success)
	{

		goto func_end;

	}

	return_state = GetRCBootDiscText(BootText, &TotalBoot);

	if (return_state != return_success)
	{

		goto func_end;

	}

	m_BootResult.ResetContent();

    for (element_count = 0;element_count < TotalBoot;++element_count)
	{

		m_BootResult.AddString(BootText[element_count]);

	}

func_end:
	
	if (return_state != return_success)
	{
	
		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_value_date_colon ,MB_OK);


	}
	
}
