// FastDates.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "FastDates.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFastDates dialog


CFastDates::CFastDates(CWnd* pParent /*=NULL*/)
	: CDialog(CFastDates::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFastDates)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


CFastDates::CFastDates(CWnd* pParent /*=NULL*/, CDB * DB_parm)
: CDialog(CFastDates::IDD, pParent), holidays_class(DB_parm)
, cholicodeproc(DB_parm)
{

	if ((TotalCodes = new int ) == NULL)

	{

		return_state = return_err_ins_mem;
		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);


	}

	else
	{

		*TotalCodes = 0;

		DB_local = DB_parm;

		DB_local->InitDB();

	}

}

CFastDates::~CFastDates()
{

	DB_local->EndDB();

}
BOOL CFastDates::Create(CWnd* pParent /*=NULL*/)
{
	
	return_BOOL = TRUE;

	return_BOOL = CDialog::Create(IDD, pParent);

	if (return_BOOL == FALSE)
	{
		return FALSE;

	}

	InitHolidayBaseMonth();
	InitHolidayBaseDay();


	DB_local->GetStatementHandle(&localhandles);

	return_state = Setholicodearray(TotalCodes);

	for (element_count = 0; element_count <
	  *TotalCodes; ++element_count)
	{

		return_state = GetHoliCode(holicodehold,element_count);
		m_Code.AddString(holicodehold);

	}

	return return_BOOL;
	
}
BOOL CFastDates::SetDB(CDB * DB_parm)
{

	BOOL return_BOOL;
	return_BOOL = TRUE;


	DB_local = DB_parm;
	DB_local->GetDBType(&db_type );
	return return_BOOL;
}

void CFastDates::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFastDates)
	DDX_Control(pDX, IDTest, m_Test);
	DDX_Control(pDX, IDDELETE, m_Delete);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDADD, m_Add);
	DDX_Control(pDX, IDC_EDIT_Holiday_Year, m_Holiday_Year);
	DDX_Control(pDX, IDC_COMBO_Holiday_Month, m_Holiday_Month);
	DDX_Control(pDX, IDC_COMBO_Holiday_Day, m_Holiday_Day);
	DDX_Control(pDX, IDC_COMBO_Code, m_Code);
	//}}AFX_DATA_MAP
}


void CFastDates::InitHolidayBaseMonth()
{
	 for (element_count = 0; element_count <
	  month_names_total; ++element_count)
	 {

		return_status =  GetMonth(element_count, monthhold);

		m_Holiday_Month.AddString(monthhold);


	 }

	 return_status =  GetCurrentMonth(&currentmonth);

	 m_Holiday_Month.SetCurSel(currentmonth);


}

void CFastDates::InitHolidayBaseDay()
{

	 for (element_count = 0; element_count <
	  holidaybasedaytotal; ++element_count)
	 {

		return_status =  GetHolidayBaseDay(element_count, dayhold);

		m_Holiday_Day.AddString(dayhold);


	 }

	 return_status =  GetCurrentBaseDay(&currentday);

	 m_Holiday_Day.SetCurSel(currentday);


}


void CFastDates::OnSelchangeCOMBOHolidayMonth() 
{
	// TODO: Add your control notification handler code here

  element_count = m_Holiday_Month.GetCurSel();
  m_Holiday_Month.GetLBText( element_count,monthhold);

  return_status =  SetHolidayMonth(monthhold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }
func_end:

  return;
	
}

void CFastDates::OnSelchangeCOMBOHolidayDay() 
{
	// TODO: Add your control notification handler code here

  element_count = m_Holiday_Day.GetCurSel();
  m_Holiday_Day.GetLBText( element_count,dayhold);

  return_status =  SetHolidayDay(dayhold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }
func_end:
    return;
	
}

void CFastDates::OnAdd() 
{
	// TODO: Add your control notification handler code here

  element_count = m_Code.GetCurSel();
  m_Code.GetLBText( element_count,holiday_code_hold);

  return_status =  SetHolidayCode(holiday_code_hold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  element_count = m_Holiday_Day.GetCurSel();
  m_Holiday_Day.GetLBText( element_count,dayhold);

  return_status =  SetHolidayDay(dayhold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  element_count = m_Holiday_Month.GetCurSel();
  m_Holiday_Month.GetLBText( element_count,monthhold);

  return_status =  SetHolidayMonth(monthhold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }
  
  m_Holiday_Year.GetWindowText(holiday_year_hold, holidayyearlength);
  return_status =  SetHolidayYear(atoi(holiday_year_hold));

  if (return_status)
  {
	 errtext(return_status, hold_msg);

	::MessageBox(NULL,hold_msg,language_error,MB_OK);

	goto func_end;

  }
  return_status =  SetBaseAdj(holiday_adj_names[event_sched_same_holiday_adj]);
  return_status =  SetBaseAdjTimes(language_first);
  return_status =  SetBaseWeekday(language_monday);
  return_status =  SetDayAdjust(language_first);
  return_status =  SetDesignate(language_no);
  return_status =  SetHolidayBase(language_date);
  return_status =  HolidayCheckAll();

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  return_status =  AddHoliday();

  if (return_status != return_success)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,"",MB_OK);

	 goto func_end;

  }


func_end:
    return;
	
}

void CFastDates::OnDelete() 
{
	// TODO: Add your control notification handler code here

  element_count = m_Code.GetCurSel();
  m_Code.GetLBText( element_count,holiday_code_hold);

  return_status =  SetHolidayCode(holiday_code_hold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  element_count = m_Holiday_Day.GetCurSel();
  m_Holiday_Day.GetLBText( element_count,dayhold);

  return_status =  SetHolidayDay(dayhold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  element_count = m_Holiday_Month.GetCurSel();
  m_Holiday_Month.GetLBText( element_count,monthhold);

  return_status =  SetHolidayMonth(monthhold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }
  
  m_Holiday_Year.GetWindowText(holiday_year_hold, holidayyearlength);
  return_status =  SetHolidayYear(atoi(holiday_year_hold));

  if (return_status)
  {
	 errtext(return_status, hold_msg);

	::MessageBox(NULL,hold_msg,language_error,MB_OK);

	goto func_end;

  }
  return_status =  SetBaseAdj(holiday_adj_names[event_sched_same_holiday_adj]);
  return_status =  SetBaseAdjTimes(language_first);
  return_status =  SetBaseWeekday(language_monday);
  return_status =  SetDayAdjust(language_first);
  return_status =  SetDesignate(language_no);
  return_status =  SetHolidayBase(language_date);
  return_status =  HolidayCheckAll();

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  return_status =  DelHoliday();

  if (return_status != return_success)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,"",MB_OK);

	 goto func_end;

  }


func_end:
    return;
	
}

void CFastDates::OnTest() 
{
	// TODO: Add your control notification handler code here

  m_Code.GetWindowText(holiday_code_hold, holidaycodelength);

  return_status =  SetHolidayCode(holiday_code_hold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  element_count = m_Holiday_Day.GetCurSel();
  m_Holiday_Day.GetLBText( element_count,dayhold);

  return_status =  SetHolidayDay(dayhold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  element_count = m_Holiday_Month.GetCurSel();
  m_Holiday_Month.GetLBText( element_count,monthhold);

  return_status =  SetHolidayMonth(monthhold);

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }
  
  m_Holiday_Year.GetWindowText(holiday_year_hold, holidayyearlength);
  return_status =  SetHolidayYear(atoi(holiday_year_hold));

  if (return_status)
  {
	 errtext(return_status, hold_msg);

	::MessageBox(NULL,hold_msg,language_error,MB_OK);

	goto func_end;

  }
  return_status =  SetBaseAdj(holiday_adj_names[event_sched_same_holiday_adj]);
  return_status =  SetBaseAdjTimes(language_first);
  return_status =  SetBaseWeekday(language_monday);
  return_status =  SetDayAdjust(language_first);
  return_status =  SetDesignate(language_no);
  return_status =  SetHolidayBase(language_date);
  return_status =  HolidayCheckAll();

  if (return_status)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,language_error,MB_OK);

	 goto func_end;

  }

  return_status =  GetHoliday();

  if (return_status != return_success)
  {
	  errtext(return_status, hold_msg);

	 ::MessageBox(NULL,hold_msg,"",MB_OK);

	 goto func_end;

  }
  else
  {
	  errtext(return_info_date_is_holiday, hold_msg);

	 ::MessageBox(NULL,hold_msg,"",MB_OK);

	 goto func_end;

  }


func_end:
	return;
	
}
/*
int CFastDates::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CFastDates::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}
*/

BEGIN_MESSAGE_MAP(CFastDates, CDialog)
	//{{AFX_MSG_MAP(CFastDates)
	ON_CBN_SELCHANGE(IDC_COMBO_Holiday_Month, OnSelchangeCOMBOHolidayMonth)
	ON_CBN_SELCHANGE(IDC_COMBO_Holiday_Day, OnSelchangeCOMBOHolidayDay)
	ON_BN_CLICKED(IDADD, OnAdd)
	ON_BN_CLICKED(IDDELETE, OnDelete)
	ON_BN_CLICKED(IDTest, OnTest)
	ON_CBN_SELCHANGE(IDC_COMBO_Code, OnSelchangeCOMBOCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFastDates message handlers

void CFastDates::OnSelchangeCOMBOCode() 
{
	// TODO: Add your control notification handler code here
	
}
