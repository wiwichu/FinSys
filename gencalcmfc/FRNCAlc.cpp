// FRNCAlc.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "FRNCAlc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFRNCAlc dialog


CFRNCAlc::CFRNCAlc(CWnd* pParent /*=NULL*/)
	: CDialog(CFRNCAlc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFRNCAlc)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


CFRNCAlc::CFRNCAlc(CWnd* pParent, /*=NULL*/ CDB * DB_parm)
	: CDialog(CFRNCAlc::IDD, pParent), /* cholicodeproc (DB_parm), */
	Py_Front (DB_parm)
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

//		DB_local->InitDB();
	}
}

CFRNCAlc::~CFRNCAlc()
{

	DB_local->EndDB();

}
BOOL CFRNCAlc::Create( CWnd* pParentWnd) 
{

	return_BOOL = TRUE;

	return_BOOL = CDialog::Create(IDD, pParentWnd);

	DB_local->GetStatementHandle(&localhandles);

	return_state = init_frn();

	if (return_state != return_success)
	{
		goto func_end_error;
	}

	setreratecount(max_rates);

	return_state = Setholicodearray(TotalCodes);

	if (return_state)
	{
		goto func_end_error;
	}

	for (element_count = 0; element_count <
	  *TotalCodes; ++element_count)
	{

		return_state = GetHoliCode(holicodehold,element_count);

		if (return_state)
		{
			goto func_end_error;
		}
		
		m_Holidays.AddString(holicodehold);

	}

	for (element_count = 0; element_count <
		holiday_adj_count; ++element_count)
	{
		return_state = getholidayadj(element_count, holiday_adj_choice);

		if (return_state)
		{
			goto func_end_error;
		}
		m_Holiday_Adjust.AddString(holiday_adj_choice);
	}
	return_state =  getholidayadj(holiday_adj_choice);

	if (return_state)
	{
		goto func_end_error;
	}
	m_Holiday_Adjust.SelectString(-1, holiday_adj_choice);

	if (return_state)
	{

		goto func_end_error;
	
	}

	for (element_count = 0; element_count <
		simp_comp_count; ++element_count)
	{
		return_state = getsimpcomp(element_count, simp_comp_choice);

		if (return_state)
		{
			goto func_end_error;
		}
		m_Simp_Comp.AddString(simp_comp_choice);
	}
	return_state =  getsimpcomp(simp_comp_choice);

	if (return_state)
	{
		goto func_end_error;
	}
	m_Simp_Comp.SelectString(-1, simp_comp_choice);

	if (return_state)
	{
		goto func_end_error;
	}

	for (element_count = 0; element_count <
		freq_count; ++element_count)
	{
		return_state = getpayfreq(element_count, pay_freq_choice);

		if (return_state)
		{
			goto func_end_error;
		}

		m_Pay_Freq.AddString(pay_freq_choice);
	}	
	return_state =  getpayfreq(pay_freq_choice);

	if (return_state)
	{
		goto func_end_error;
	}

	m_Pay_Freq.SelectString(-1, pay_freq_choice);

	if (return_state)
	{
		goto func_end_error;
	}


	for (element_count = 0; element_count <
		freq_count; ++element_count)
	{
		return_state = getfrnpayfreq(element_count, frn_pay_freq_choice);

		if (return_state)
		{
			goto func_end_error;
		}

		m_Rerate_Freq.AddString(frn_pay_freq_choice);
	}	
	return_state =  getfrnpayfreq(frn_pay_freq_choice);

	if (return_state)
	{
		goto func_end_error;
	}

	m_Rerate_Freq.SelectString(-1, frn_pay_freq_choice);

	if (return_state)
	{
		goto func_end_error;
	}


	for (element_count = 0; element_count <
		date_last_day_count; ++element_count)
	{
		return_state = getdaycount(element_count, day_count_choice);

		if (return_state)
		{
			goto func_end_error;
		}

		m_Day_Count.AddString(day_count_choice);
	}
	return_state =  getdaycount(day_count_choice);

	if (return_state)
	{
		goto func_end_error;
	}

	m_Day_Count.SelectString(-1, day_count_choice);

	if (return_state)
	{
		goto func_end_error;
	}

	price_places = 15;

	goto func_end;

func_end_error:

	errtext(return_state, err_msg);

	::MessageBox(NULL,err_msg,"",MB_OK);

func_end:
	return return_BOOL;

}

void CFRNCAlc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFRNCAlc)
	DDX_Control(pDX, IDC_STATIC_Interest_Days_Display, m_Interest_Days);
	DDX_Control(pDX, IDC_STATIC_Interest_Display, m_Interest);
	DDX_Control(pDX, IDC_STATIC_Previous_Coup_Display, m_Previous_Coup);
	DDX_Control(pDX, IDC_STATIC_Next_Coup_Display, m_Next_Coup);
	DDX_Control(pDX, IDC_EDIT_Rerate_Rate6, m_Rerate_Rate6);
	DDX_Control(pDX, IDC_EDIT_Rerate_Rate5, m_Rerate_Rate5);
	DDX_Control(pDX, IDC_EDIT_Rerate_Rate4, m_Rerate_Rate4);
	DDX_Control(pDX, IDC_EDIT_Rerate_Rate3, m_Rerate_Rate3);
	DDX_Control(pDX, IDC_EDIT_Rerate_Rate2, m_Rerate_Rate2);
	DDX_Control(pDX, IDC_EDIT_Rerate_Rate1, m_Rerate_Rate1);
	DDX_Control(pDX, IDC_STATIC_Rerate_Dates6, m_Rerate_Date6);
	DDX_Control(pDX, IDC_STATIC_Rerate_Dates5, m_Rerate_Date5);
	DDX_Control(pDX, IDC_STATIC_Rerate_Dates4, m_Rerate_Date4);
	DDX_Control(pDX, IDC_STATIC_Rerate_Dates3, m_Rerate_Date3);
	DDX_Control(pDX, IDC_STATIC_Rerate_Dates2, m_Rerate_Date2);
	DDX_Control(pDX, IDC_STATIC_Rerate_Dates1, m_Rerate_Date1);
	DDX_Control(pDX, IDC_Rerate_Freq, m_Rerate_Freq);
	DDX_Control(pDX, SetDates, m_SetDates);
	DDX_Control(pDX, IDC_EDIT_Value_Date, m_Value_Date);
	DDX_Control(pDX, IDC_EDIT_Maturity_Date, m_Maturity_Date);
	DDX_Control(pDX, IDC_EDIT_Issue_Date, m_Issue_Date);
	DDX_Control(pDX, IDC_Day_Count, m_Day_Count);
	DDX_Control(pDX, IDC_Pay_Freq, m_Pay_Freq);
	DDX_Control(pDX, IDC_Simp_Comp, m_Simp_Comp);
	DDX_Control(pDX, IDC_Holidays_Adjust, m_Holiday_Adjust);
	DDX_Control(pDX, IDC_Holidays, m_Holidays);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFRNCAlc, CDialog)
	//{{AFX_MSG_MAP(CFRNCAlc)
	ON_BN_CLICKED(SetDates, OnSetDates)
	ON_CBN_SELCHANGE(IDC_Day_Count, OnSelchangeDayCount)
	ON_CBN_SELCHANGE(IDC_Holidays, OnSelchangeHolidays)
	ON_CBN_SELCHANGE(IDC_Holidays_Adjust, OnSelchangeHolidaysAdjust)
	ON_CBN_SELCHANGE(IDC_Pay_Freq, OnSelchangePayFreq)
	ON_CBN_SELCHANGE(IDC_Rerate_Freq, OnSelchangeRerateFreq)
	ON_CBN_SELCHANGE(IDC_Simp_Comp, OnSelchangeSimpComp)
	ON_BN_CLICKED(CalcInterest, OnCalcInterest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFRNCAlc message handlers

void CFRNCAlc::OnSetDates() 
{
	// TODO: Add your control notification handler code here

	char rerate_count;
	m_Maturity_Date.GetWindowText(date_hold,sizeof(date_hold));

	return_state =  setmatdate(date_hold);
	if (return_state)
	{

	 if (return_state == return_err_date_form_bad)
	 {
		 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_maturity_date,MB_OK);

		return;
		//		return;

	 }
	 else
	 {
		if (return_state == return_err_date_bad)
		{


		}

		else
		{


			if (return_state != return_err_date_bad)
			{
			   errtext(return_state, err_msg);

			  ::MessageBox(NULL,err_msg,language_maturity_date,MB_OK);

				return;

			  // return;
			}
		}

	 }
	}

  m_Value_Date.GetWindowText(date_hold,sizeof(date_hold));
//  value_date.GetLine(0,date_hold);

  return_state =  setvaldate(date_hold);

  if (return_state)
  {

    if (return_state == return_err_date_form_bad)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_value_date,MB_OK);

	 	return;

	}
	else
	{
	  if (return_state == return_err_date_bad)
	  {


	  }

	  else
	  {


		 if (return_state != return_err_date_bad)
		 {

			 errtext(return_state, err_msg);

			::MessageBox(NULL,err_msg,language_value_date,MB_OK);

			return;
		 }
	  }
	}

  }

  m_Issue_Date.GetWindowText(date_hold,sizeof(date_hold));
//  value_date.GetLine(0,date_hold);

  return_state =  setissuedate(date_hold);

  if (return_state)
  {

    if (return_state == return_err_date_form_bad)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_value_date,MB_OK);

	 	return;

	}
	else
	{
	  if (return_state == return_err_date_bad)
	  {


	  }

	  else
	  {


		 if (return_state != return_err_date_bad)
		 {

			 errtext(return_state, err_msg);

			::MessageBox(NULL,err_msg,language_value_date,MB_OK);

			return;
		 }
	  }
	}

  }

  return_state = setreratecount(max_rates);

  return_state =  proc_gen_dates_frn();

  if (return_state)
  {
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_value_date,MB_OK);

		return;
  }

  return_state = getreratecount(&rerate_count);

  if (return_state)
  {
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_value_date,MB_OK);

		return;
  }

  m_Rerate_Date1.SetWindowText(" ");
  m_Rerate_Date2.SetWindowText(" ");
  m_Rerate_Date3.SetWindowText(" ");
  m_Rerate_Date4.SetWindowText(" ");
  m_Rerate_Date5.SetWindowText(" ");
  m_Rerate_Date6.SetWindowText(" ");

  for (element_count = 1; element_count <= rerate_count; ++element_count)
  {

	return_state = getreratedate(element_count,date_hold);

	if (return_state)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,language_value_date,MB_OK);

		return;
	}

	if (element_count == 1)
	{

		m_Rerate_Date1.SetWindowText(date_hold);


	}

	if (element_count == 2)
	{

		m_Rerate_Date2.SetWindowText(date_hold);


	}

	if (element_count == 3)
	{

		m_Rerate_Date3.SetWindowText(date_hold);


	}

	if (element_count == 4)
	{

		m_Rerate_Date4.SetWindowText(date_hold);


	}

	if (element_count == 5)
	{

		m_Rerate_Date5.SetWindowText(date_hold);


	}

	if (element_count == 6)
	{

		m_Rerate_Date6.SetWindowText(date_hold);


	}

  }

  return_state = getnextcoup(date_hold);

  if (return_state)
  {
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

		return;
  }

  m_Next_Coup.SetWindowText(date_hold);


  return_state = getprevcoup(date_hold);

  if (return_state)
  {
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

		return;
  }

  m_Previous_Coup.SetWindowText(date_hold);

}

void CFRNCAlc::OnSelchangeDayCount() 
{
	// TODO: Add your control notification handler code here

	int listcount;

	listcount = m_Day_Count.GetCurSel();
	m_Day_Count.GetLBText( listcount, day_count_choice);

	return_state =  setdaycount(day_count_choice);

	if (return_state)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

		return;
	}
	return_state =  proc_day_count();

	if (return_state)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

		return;
	}
	
}

void CFRNCAlc::OnSelchangeHolidays() 
{
	// TODO: Add your control notification handler code here
	
	int list_number;

	list_number = m_Holidays.GetCurSel();
	m_Holidays.GetLBText( list_number, holicodehold);

	return_state =  setholiday(holicodehold);

	if (return_state)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

		return;
	}
	
}

void CFRNCAlc::OnSelchangeHolidaysAdjust() 
{
	// TODO: Add your control notification handler code here
	
	int list_number;

	list_number = m_Holiday_Adjust.GetCurSel();
	m_Holiday_Adjust.GetLBText( list_number, holiday_adj_choice);

	return_state =  setholidayadj(holiday_adj_choice);

	if (return_state)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

		return;
	}
	return_state =  proc_holi();

	if (return_state)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

		return;
	}
	
}

void CFRNCAlc::OnSelchangePayFreq() 
{
	// TODO: Add your control notification handler code here
	
	 int list_number;

	 list_number = m_Pay_Freq.GetCurSel();
	 m_Pay_Freq.GetLBText( list_number, pay_freq_choice);

	 return_state =  setpayfreq(pay_freq_choice);

	 return_state =  proc_pay_freq();
	
}

void CFRNCAlc::OnSelchangeRerateFreq() 
{
	// TODO: Add your control notification handler code here
	
	 int list_number;

	 list_number = m_Rerate_Freq.GetCurSel();
	 m_Rerate_Freq.GetLBText( list_number, pay_freq_choice);

	 return_state =  setfrnpayfreq(pay_freq_choice);

	 return_state =  proc_pay_freq_frn();
	
}

void CFRNCAlc::OnSelchangeSimpComp() 
{
	// TODO: Add your control notification handler code here
	
	 int list_number;

	 list_number = m_Simp_Comp.GetCurSel();
	 m_Simp_Comp.GetLBText( list_number, simp_comp_choice);

	 return_state =  setsimpcomp(simp_comp_choice);

	 return_state =  proc_simp_comp_frn();
	
}

void CFRNCAlc::OnCalcInterest() 
{
	// TODO: Add your control notification handler code here
	char rerate_count;
	long double rate_hold;

	OnSetDates();

	  return_state = getreratecount(&rerate_count);

	if (return_state)
	{
	 	 errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

		return;
	}

	for (element_count = 1; element_count <= rerate_count; ++element_count)
	{

		if (element_count == 1)
		{

			m_Rerate_Rate1.GetWindowText(work_str,sizeof(work_str));
			rate_hold = strtod(work_str, &str_ptr);
			return_state = setfrnrate(element_count,rate_hold/100);

			if (return_state)
			{
	 			errtext(return_state, err_msg);

				::MessageBox(NULL,err_msg,"",MB_OK);

				return;
			}

		}

		if (element_count == 2)
		{

			m_Rerate_Rate2.GetWindowText(work_str,sizeof(work_str));
			rate_hold = strtod(work_str, &str_ptr);
			return_state = setfrnrate(element_count,rate_hold/100);

			if (return_state)
			{
	 			errtext(return_state, err_msg);

				::MessageBox(NULL,err_msg,"",MB_OK);

				return;
			}


		}

		if (element_count == 3)
		{
			m_Rerate_Rate3.GetWindowText(work_str,sizeof(work_str));
			rate_hold = strtod(work_str, &str_ptr);
			return_state = setfrnrate(element_count,rate_hold/100);

			if (return_state)
			{
	 			errtext(return_state, err_msg);

				::MessageBox(NULL,err_msg,"",MB_OK);

				return;
			}


		}

		if (element_count == 4)
		{

			m_Rerate_Rate4.GetWindowText(work_str,sizeof(work_str));
			rate_hold = strtod(work_str, &str_ptr);
			return_state = setfrnrate(element_count,rate_hold/100);

			if (return_state)
			{
	 			errtext(return_state, err_msg);

				::MessageBox(NULL,err_msg,"",MB_OK);

				return;
			}

		}

		if (element_count == 5)
		{

			m_Rerate_Rate5.GetWindowText(work_str,sizeof(work_str));
			rate_hold = strtod(work_str, &str_ptr);
			return_state = setfrnrate(element_count,rate_hold/100);

			if (return_state)
			{
	 			errtext(return_state, err_msg);

				::MessageBox(NULL,err_msg,"",MB_OK);

				return;
			}

		}

		if (element_count == 6)
		{

			m_Rerate_Rate6.GetWindowText(work_str,sizeof(work_str));
			rate_hold = strtod(work_str, &str_ptr);
			return_state = setfrnrate(element_count,rate_hold/100);

			if (return_state)
			{
	 			errtext(return_state, err_msg);

				::MessageBox(NULL,err_msg,"",MB_OK);

				return;
			}

		}


		return_state =  setinprice(100);

		if (return_state)
		{
			errtext(return_state, err_msg);

			::MessageBox(NULL,err_msg,language_error,MB_OK);

			  goto func_end;
		}

		return_state =  calc_int();

		if (return_state)
		{
			errtext(return_state, err_msg);

			::MessageBox(NULL,err_msg,language_error,MB_OK);

			  goto func_end;
		}

		return_state =  getintdays(&interest_days_parm);

		if (return_state)
		{
			errtext(return_state, err_msg);

			::MessageBox(NULL,err_msg,language_error,MB_OK);

			  goto func_end;
		}

		ltoa(interest_days_parm,work_str,10);

		m_Interest_Days.SetWindowText(work_str);

		return_state =  getinterest(&interest_parm);

		if (return_state)
		{
			errtext(return_state, err_msg);

			::MessageBox(NULL,err_msg,language_error,MB_OK);

			  goto func_end;
		}

		interest_double = (double)interest_parm * 100;

		gcvt(interest_double, price_places, work_str);

		m_Interest.SetWindowText(work_str);


	}
func_end:
	return;
}
