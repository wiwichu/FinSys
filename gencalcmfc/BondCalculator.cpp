// BondCalculator.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "BondCalculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBondCalculator dialog
CBondCalculator::CBondCalculator(CWnd* pParent /*=NULL*//*, CDB * DB_parm*/) 
	: CDialog(CBondCalculator::IDD, pParent), 
	Py_Front ()
//	Py_Front (DB_parm)
//	,cholicodeproc (DB_parm)

{
//	DB_local = DB_parm;

//	DB_local->InitDB();

//	DB_local->GetStatementHandle(&localhandles);
	//{{AFX_DATA_INIT(CBondCalculator)
	//}}AFX_DATA_INIT
}

CBondCalculator::~CBondCalculator() 

{

//	DB_local->EndDB();
}


void CBondCalculator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBondCalculator)
	DDX_Control(pDX, IDC_STATIC_Prepay, m_Label_Prepay);
	DDX_Control(pDX, IDC_COMBO_Prepay, m_Combo_Prepay);
	DDX_Control(pDX, IDC_STATIC_Lag, m_Label_Lag);
	DDX_Control(pDX, IDC_EDIT_Lag, m_Edit_Lag);
	DDX_Control(pDX, IDC_STATIC_Service_Fee, m_Static_Service_Fee);
	DDX_Control(pDX, IDC_EDIT_Service_Fee, m_Edit_Service_Fee);
	DDX_Control(pDX, IDC_COMBO_Holidays, m_Holidays);
	DDX_Control(pDX, IDC_STATIC_Convexity_Value, m_Convexity);
	DDX_Control(pDX, IDC_STATIC_Modified_Duration_Value, m_ModDuration);
	DDX_Control(pDX, IDC_STATIC_PVBP_Value, m_pvbp);
	DDX_Control(pDX, IDC_STATIC_Duration_Value, m_Duration);
	DDX_Control(pDX, IDC_STATIC_Dirty_Price_Value, m_DirtyPrice);
	DDX_Control(pDX, IDC_STATIC_Accrued_Interest_Value, m_AccruedInterest);
	DDX_Control(pDX, IDC_STATIC_Interest_Days_Value, m_InterestDays);
	DDX_Control(pDX, IDC_STATIC_Next_Coupon_Value, m_NextCoup);
	DDX_Control(pDX, IDC_STATIC_Previous_Coupon_Value, m_PreviousCoup);
	DDX_Control(pDX, ID_Calculate, m_Calculate);
	DDX_Control(pDX, IDC_EDIT_Issue_Date, m_Issue_Date);
	DDX_Control(pDX, IDC_EDIT_First_Pay_Date, m_First_Pay);
	DDX_Control(pDX, IDC_EDIT_Value_Date, m_ValueDate);
	DDX_Control(pDX, IDC_EDIT_Next_To_Last_Pay_Date, m_Next_To_Last_Pay);
	DDX_Control(pDX, IDC_EDIT_Maturity_Date, m_MaturityDate);
	DDX_Control(pDX, ID_Default_Dates, m_DefaultDates);
	DDX_Control(pDX, IDC_RADIO1_Yield_from_Price, m_y_from_p);
	DDX_Control(pDX, IDC_RADIO1_Price_from_Yield, m_p_from_y);
	DDX_Control(pDX, IDC_STATIC_Calculation_Choice, m_CalcChoice);
	DDX_Control(pDX, IDC_STATIC_Ex_Coup_Days_Value, m_Excoup_Days);
	DDX_Control(pDX, IDC_COMBO_Yield_Frequency, m_YieldFreq);
	DDX_Control(pDX, IDC_COMBO_Ex_Coup, m_Excoup);
	DDX_Control(pDX, IDC_COMBO_EOM, m_EOM);
	DDX_Control(pDX, IDC_COMBO_Yield_Days, m_YieldDays);
	DDX_Control(pDX, IDC_EDIT_Yield_Discount, m_YieldDiscount);
	DDX_Control(pDX, IDC_EDIT_Clean_Price, m_CleanPrice);
	DDX_Control(pDX, IDC_EDIT_Interest_Rate, m_InterestRate);
	DDX_Control(pDX, IDC_COMBO_Yield_method, m_YieldMeth);
	DDX_Control(pDX, IDC_COMBO_Pay_Frequency, m_PayFreq);
	DDX_Control(pDX, IDC_COMBO_Day_Count, m_DayCount);
	DDX_Control(pDX, IDC_COMBO_Instrument_Class, m_InstrClass);
	//}}AFX_DATA_MAP
}


BOOL CBondCalculator::Create( CWnd* pParentWnd) 
{

	return_BOOL = TRUE;

	return_BOOL = CDialog::Create(IDD, pParentWnd);

	if (return_BOOL == FALSE)
	{
		return FALSE;

	}
	
	return_status =  init_screen();

	InitInstrClass();
	//InitHolidays();
	InitDayCount();
	InitFreqCount();
	InitYieldMeth();
	InitIntRate();
	InitPrice();
	InitYield();
	InitYieldDays();
	InitYieldFreq();
	InitMonthEnd();
	InitExCoup();
	InitExCoupDays();
	InitCalcChoice();
	InitPrepay();
	InitServiceFee();
	InitLag();

	Calc_type = 0;
	FRN_type = 1;

	active_type = Calc_type;
	price_places = 15;

	return return_BOOL;
}
void CBondCalculator::InitInstrClass()
{
	for (element_count = 0; element_count <
	  instr_last_class; ++element_count)
	{

		return_status =  getclassdesc(element_count, class_desc_hold);

		m_InstrClass.AddString(class_desc_hold);

	}


	return_status =  getclassdesc(class_desc_hold);
	return_status = m_InstrClass.SelectString(-1, class_desc_hold);
}
void CBondCalculator::InitHolidays()
{
	
	return_status = getholidaytotal(&TotalCodes);

	for (element_count = 0; element_count <
	  TotalCodes; ++element_count)
	{
//		return_status = GetHoliCode(holicodehold,element_count);
//		return_status = getholiday(element_count,holicodehold);
//		m_Holidays.AddString(holicodehold);

	}

}

void CBondCalculator::InitDayCount()
{

	for (element_count = 0; element_count <
	 date_last_day_count; ++element_count)
	{

		return_status =  getdaycount(element_count, day_count_hold);

		m_DayCount.AddString(day_count_hold);

	}

	return_status =  getdaycount(day_count_hold);
	return_status = m_DayCount.SelectString(-1, day_count_hold);
}

void CBondCalculator::InitFreqCount()
{
	for (element_count = 0; element_count <
	  freq_count; ++element_count)
	{


		return_status =  getpayfreq(element_count, pay_freq_hold);

		m_PayFreq.AddString(pay_freq_hold);

	}


	return_status =  getpayfreq(pay_freq_hold);
	m_PayFreq.SelectString(-1, pay_freq_hold);
}
void CBondCalculator::InitYieldMeth()
{

	for (element_count = 0; element_count <
	  py_last_yield_meth; ++element_count)
	{


		return_status =  getyieldmeth(element_count, yieldmeth_name_hold);

		m_YieldMeth.AddString(yieldmeth_name_hold);

	}


	return_status =  getyieldmeth(yieldmeth_name_hold);
 	m_YieldMeth.SelectString(-1, yieldmeth_name_hold);
}
void CBondCalculator::InitPrepay()
{

	for (element_count = 0; element_count <
	  py_last_prepay_type; ++element_count)
	{


		return_status =  getprepay(element_count, prepay_type_name);

		m_Combo_Prepay.AddString(prepay_type_name);

	}


	return_status =  getprepayname(prepay_type_name);
 	m_Combo_Prepay.SelectString(-1, prepay_type_name);
}

void CBondCalculator::InitIntRate()
{
 
	return_status =  getintrate(&dummy_long_double);

	ltoa(dummy_long_double,work_str,10);
	m_InterestRate.SetWindowText(work_str);
}

void CBondCalculator::InitServiceFee()
{
 
	return_status =  getservicefee(&dummy_long_double);

	ltoa(dummy_long_double,work_str,10);
	m_Edit_Service_Fee.SetWindowText(work_str);
}

void CBondCalculator::InitLag()
{
 
	return_status =  getlag(&dummy_long_double);

	ltoa(dummy_long_double,work_str,10);
	m_Edit_Lag.SetWindowText(work_str);
}
void CBondCalculator::InitPrice()
{

	return_status =  getinprice(&dummy_long_double);

	ltoa(dummy_long_double,work_str,10);
	m_CleanPrice.SetWindowText(work_str);
}
void CBondCalculator::InitYield()
{

	return_status =  getinyield(&dummy_long_double);

	ltoa(dummy_long_double,work_str,10);
	m_YieldDiscount.SetWindowText(work_str);
}
void CBondCalculator::InitYieldDays()
{

	for (element_count = 0; element_count <
	  date_last_day_count; ++element_count)
	{


		return_status =  getyielddays(element_count, yielddays_name_hold);

		m_YieldDays.AddString(yielddays_name_hold);

	}


	return_status =  getyielddays(yielddays_name_hold);
	m_YieldDays.SelectString(-1, yielddays_name_hold);
}
void CBondCalculator::InitYieldFreq()
{

	for (element_count = 0; element_count <
	  freq_count; ++element_count)
	{


		return_status =  getyieldfreq(element_count, yieldmeth_name_hold);

		m_YieldFreq.AddString(yieldmeth_name_hold);

	}
	 

	return_status =  getyieldfreq(yieldmeth_name_hold);
	return_status = m_YieldFreq.SelectString(-1, yieldmeth_name_hold);

}
void CBondCalculator::InitMonthEnd()
{
	for (element_count = 0; element_count <
	  monthend_count; ++element_count)
	{


		return_status =  getmonthend(element_count, month_end_hold);

		m_EOM.AddString(month_end_hold);

	}


	return_status =  getmonthend(month_end_hold);
	return_status = m_EOM.SelectString(-1, month_end_hold);
}
void CBondCalculator::InitExCoup()
{

	for (element_count = 0; element_count <
	  excoup_count; ++element_count)
	{

		return_status =  getexcoupchoice(element_count, excoup_name_hold);

		m_Excoup.AddString(excoup_name_hold);

	}

	return_status =  getexcoup(excoup_name_hold);

	return_status = m_Excoup.SelectString(-1,excoup_name_hold);
}
void CBondCalculator::InitExCoupDays()
{

	return_status =  getexcoupdays(&dummy_int);

	itoa(dummy_int,work_str,10);
	m_Excoup_Days.SetWindowText(work_str);
}

void CBondCalculator::InitCalcChoice()
{

	return_status =  getcalcwhat(&current_calc_what);

	if ( current_calc_what == py_yield_from_price_calc_what )
	{
		m_y_from_p.SetCheck(1);
		m_p_from_y.SetCheck(0);
	}
	else
	{
		m_p_from_y.SetCheck(1);
		m_y_from_p.SetCheck(0);
	}

}
BEGIN_MESSAGE_MAP(CBondCalculator, CDialog)
	//{{AFX_MSG_MAP(CBondCalculator)
	ON_CBN_SELCHANGE(IDC_COMBO_Day_Count, OnSelchangeCOMBODayCount)
	ON_CBN_SELCHANGE(IDC_COMBO_Pay_Frequency, OnSelchangeCOMBOPayFrequency)
	ON_CBN_SELCHANGE(IDC_COMBO_Yield_Days, OnSelchangeCOMBOYieldDays)
	ON_CBN_SELCHANGE(IDC_COMBO_Yield_Frequency, OnSelchangeCOMBOYieldFrequency)
	ON_CBN_SELCHANGE(IDC_COMBO_Yield_method, OnSelchangeCOMBOYieldmethod)
	ON_CBN_SELCHANGE(IDC_COMBO_Instrument_Class, OnSelchangeCOMBOInstrumentClass)
	ON_BN_CLICKED(IDC_RADIO1_Price_from_Yield, OnRADIO1PricefromYield)
	ON_BN_CLICKED(IDC_RADIO1_Yield_from_Price, OnRADIO1YieldfromPrice)
	ON_BN_CLICKED(ID_Default_Dates, OnDefaultDates)
	ON_CBN_SELCHANGE(IDC_COMBO_EOM, OnSelchangeComboEom)
	ON_CBN_SELCHANGE(IDC_COMBO_Ex_Coup, OnSelchangeCOMBOExCoup)
	ON_BN_CLICKED(ID_Calculate, OnCalculate)
	ON_CBN_SELCHANGE(IDC_COMBO_Holidays, OnSelchangeCOMBOHolidays)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBondCalculator message handlers

void CBondCalculator::OnSelchangeCOMBODayCount() 
{
	// TODO: Add your control notification handler code here

	 day_count_number = m_DayCount.GetCurSel();
	 m_DayCount.GetLBText( day_count_number, day_count_hold);

	 return_status =  setdaycount(day_count_hold);

	 return_status =  proc_day_count();
 
 	 return_status =  getyielddays(yielddays_name_hold);
	 m_YieldDays.SelectString(-1, yielddays_name_hold);
	
}

void CBondCalculator::OnSelchangeCOMBOPayFrequency() 
{
	// TODO: Add your control notification handler code here

	 pay_freq_number = m_PayFreq.GetCurSel();
	 m_PayFreq.GetLBText( pay_freq_number, pay_freq_hold);

	 return_status =  setpayfreq(pay_freq_hold);

	 return_status =  proc_pay_freq();

	 return_status =  getpayfreq(pay_freq_hold);
  	 m_PayFreq.SelectString(-1, pay_freq_hold);

	 return_status =  getyieldfreq(yieldmeth_name_hold);
	 return_status = m_YieldFreq.SelectString(-1, yieldmeth_name_hold);
	
}

void CBondCalculator::OnSelchangeCOMBOYieldDays() 
{
	// TODO: Add your control notification handler code here

	 yield_days_number = m_YieldDays.GetCurSel();
	 m_YieldDays.GetLBText( yield_days_number, yielddays_name_hold);

	 return_status =  setyielddays(yielddays_name_hold);

	 return_status =  proc_yield_days();
	
}

void CBondCalculator::OnSelchangeCOMBOYieldFrequency() 
{
	// TODO: Add your control notification handler code here

	 yield_freq_number = m_YieldFreq.GetCurSel();
	 m_YieldFreq.GetLBText( yield_freq_number, yieldfreq_name_hold);

	 return_status =  setyieldfreq(yieldfreq_name_hold);

	 return_status =  proc_yield_freq();
	
}

void CBondCalculator::OnSelchangeCOMBOYieldmethod() 
{
	// TODO: Add your control notification handler code here

	 yield_meth_number = m_YieldMeth.GetCurSel();
	 m_YieldMeth.GetLBText( yield_meth_number, yieldmeth_name_hold);

	 return_status =  setyieldmeth(yieldmeth_name_hold);

	 return_status =  proc_yield_meth();
	
}

void CBondCalculator::OnSelchangeCOMBOInstrumentClass() 
{
	// TODO: Add your control notification handler code here


	 class_number = m_InstrClass.GetCurSel();
	 m_InstrClass.GetLBText( class_number, class_desc_hold);

	 return_status =  setclassdesc(class_desc_hold);
	 return_status =  proc_class_desc();

	 return_status =  getdaycount(day_count_hold);

	 m_DayCount.SelectString(-1,day_count_hold);

	 return_status =  getpayfreq(pay_freq_hold);

	 m_PayFreq.SelectString( -1,pay_freq_hold);

	 return_status =  getyielddays(yielddays_name_hold);
	 m_YieldDays.SelectString(-1,yielddays_name_hold);

	 return_status =  getyieldfreq(yieldfreq_name_hold);

	 m_YieldFreq.SelectString(-1,yieldfreq_name_hold);

	 return_status =  getyieldmeth(yieldmeth_name_hold);

	 m_YieldMeth.SelectString(-1,yieldmeth_name_hold);


	 return_status =  getcalcwhat(&current_calc_what);

	 if ( current_calc_what == py_yield_from_price_calc_what )
	 {
		m_y_from_p.SetCheck(1);
		m_p_from_y.SetCheck(0);
	 }
	 else
	 {
		m_p_from_y.SetCheck(1);
		m_y_from_p.SetCheck(0);
	 }

	 return_status =  getmonthend(month_end_hold);

	 m_EOM.SelectString(-1,month_end_hold);

	 return_status =  getexcoup(excoup_name_hold);
	 excoup_number = m_Excoup.SelectString(-1,excoup_name_hold);


	 return_status =  getcalcwhat(&current_calc_what);


	 return_status =  getexcoupdays(&dummy_int);
	 itoa(dummy_int,work_str,10);
	 m_Excoup.SetWindowText(work_str);

	 m_Static_Service_Fee.ShowWindow(SW_SHOWNORMAL);
	 m_Edit_Service_Fee.ShowWindow(SW_SHOWNORMAL);
	 m_Label_Lag.ShowWindow(SW_SHOWNORMAL);
	 m_Edit_Lag.ShowWindow(SW_SHOWNORMAL);
	 m_Label_Prepay.ShowWindow(SW_SHOWNORMAL);
	 m_Combo_Prepay.ShowWindow(SW_SHOWNORMAL);

	
}

void CBondCalculator::OnRADIO1PricefromYield() 
{
	// TODO: Add your control notification handler code here

	 return_status =  setcalcwhat(py_price_from_yield_calc_what);

	 return_status =  proc_calc_what( );
	
	 return_status =  getcalcwhat(&current_calc_what);

	 if ( current_calc_what == py_yield_from_price_calc_what )
	 {
		m_y_from_p.SetCheck(1);
		m_p_from_y.SetCheck(0);
	 }
	 else
	 {
		m_p_from_y.SetCheck(1);
		m_y_from_p.SetCheck(0);
	 }

}

void CBondCalculator::OnRADIO1YieldfromPrice() 
{
	// TODO: Add your control notification handler code here

	 return_status =  setcalcwhat(py_yield_from_price_calc_what);

	 return_status =  proc_calc_what( );

	 return_status =  getcalcwhat(&current_calc_what);

	 if ( current_calc_what == py_yield_from_price_calc_what )
	 {
		m_y_from_p.SetCheck(1);
		m_p_from_y.SetCheck(0);
	 }
	 else
	 {
		m_p_from_y.SetCheck(1);
		m_y_from_p.SetCheck(0);
	 }
	
}

void CBondCalculator::OnDefaultDates() 
{
	// TODO: Add your control notification handler code here


	m_MaturityDate.GetWindowText(date_hold,sizeof(date_hold));

	return_status =  setmatdate(date_hold);
	if (return_status)
	{

	 if (return_status == return_err_date_form_bad)
	 {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_maturity_date,MB_OK);

		return;
		//		return;

	 }
	 else
	 {
		if (return_status == return_err_date_bad)
		{


		}

		else
		{


			if (return_status != return_err_date_bad)
			{
			   errtext(return_status, err_msg);

			  ::MessageBox(NULL,err_msg,language_maturity_date,MB_OK);

				return;

			  // return;
			}
		}

	 }
	}

  m_ValueDate.GetWindowText(date_hold,sizeof(date_hold));
//  value_date.GetLine(0,date_hold);

  return_status =  setvaldate(date_hold);

  if (return_status)
  {

    if (return_status == return_err_date_form_bad)
	{
	 	 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_value_date,MB_OK);

	 	return;

	}
	else
	{
	  if (return_status == return_err_date_bad)
	  {


	  }

	  else
	  {


		 if (return_status != return_err_date_bad)
		 {

			 errtext(return_status, err_msg);

			::MessageBox(NULL,err_msg,language_value_date,MB_OK);

			return;
		 }
	  }
	}

  }
	
  return_status =  proc_def_dates();

  if (return_status == return_err_val_ge_cf)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_value_date,MB_OK);

		return;

  }

  if (return_status == return_err_mat_date_bad)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_maturity_date,MB_OK);

	  return;

  }

  if (return_status == return_err_val_date_bad)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_value_date,MB_OK);

	  return;

  }

  if (return_status == return_info_max_mat_exc)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return;

  }

  if (return_status == return_err_val_gt_mat)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return;

  }


  if (return_status)
  {

		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_default_dates_application_error,MB_OK);

		return;

  }

//  InitDateHold(date_hold,sizeof(date_hold));

  return_status =  getpenultdate(date_hold);

  m_Next_To_Last_Pay.SetWindowText(date_hold);

//  InitDateHold(date_hold,sizeof(date_hold));

  return_status =  getissuedate(date_hold);

  m_Issue_Date.SetWindowText(date_hold);

//  InitDateHold(date_hold,sizeof(date_hold));

  return_status =  getfirstdate(date_hold);
  m_First_Pay.SetWindowText(date_hold);

//  if (active_type == Calc_type)

//  {

		return_status =  getexcoup(excoup_name_hold);
		return_status = m_Excoup.SelectString(-1,excoup_name_hold);

//  }


//func_end:
	
}

void CBondCalculator::OnSelchangeComboEom() 
{
	// TODO: Add your control notification handler code here
	
	 month_end_number = m_EOM.GetCurSel();
	 m_EOM.GetLBText( month_end_number, month_end_hold);

	 return_status =  setmonthend(month_end_hold);
	 return_status =  proc_monthend();

//	 return_status =  getmonthend(&month_end_number);

//	 monthend.SetCurSel(month_end_number);

}

void CBondCalculator::OnSelchangeCOMBOExCoup() 
{
	// TODO: Add your control notification handler code here
	
	 excoup_number = m_Excoup.GetCurSel();
	 m_Excoup.GetLBText( excoup_number, excoup_name_hold);

	 return_status =  setexcoup(excoup_name_hold);
	 return_status =  proc_excoup();

}

void CBondCalculator::OnCalculate() 
{
	// TODO: Add your control notification handler code here

  if (pay_type_control == instr_open_pay_type)
  {
		pay_type_control = instr_fixed_pay_type;

  }

  //return_status =  getclassnumber(&class_number);
  return_status =  getclassdesc(class_desc_hold);
  
  //if (class_number != instr_cashflow_class)
  if (strcmp(class_desc_hold, instr_cashflow_class_name) != 0)

  {

	 return_status = CheckDates();

	 if ((return_status) && (return_status != return_err_date_bad))
	 {

		   errtext(return_status, err_msg);

		  ::MessageBox(NULL,err_msg,language_value_date,MB_OK);

		  return;

	 }

  }
  else
  {

	 /* Validate Value Date.*/

	 InitDateHold(date_hold,sizeof(date_hold));

	 m_ValueDate.GetWindowText(date_hold,sizeof(date_hold));

	 return_status =  setvaldate(date_hold);

	 if ((return_status) && (return_status != return_err_date_bad))
	 {

		if (return_status == return_err_date_form_bad)
		{
		   errtext(return_status, err_msg);

		  ::MessageBox(NULL,err_msg,language_value_date,MB_OK);

		  return;

		}
		else
		{

//		  errproc(return_status,module_name,"","","");

		  return;

		}
	 }
  }

  return_status =  getcalcwhat(&current_calc_what);

  if (current_calc_what == py_yield_from_price_calc_what)
  {
	 m_YieldDiscount.Clear();

	 m_CleanPrice.GetWindowText(work_str,sizeof(work_str));

	 dummy_long_double = strtod(work_str, &str_ptr);

	 return_status =  setinprice(dummy_long_double);

  }
  else
  {
	 m_CleanPrice.Clear();

	 m_YieldDiscount.GetWindowText(work_str,sizeof(work_str));

	 dummy_long_double = strtod(work_str, &str_ptr);
	  setinyield(dummy_long_double);
  }

  m_Edit_Service_Fee.GetWindowText(work_str,sizeof(work_str));

  dummy_long_double = strtod(work_str, &str_ptr);
  return_status = setservicefee(dummy_long_double/100);

  if (return_status != return_success)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,"",MB_OK);

	  goto func_end;

  }

  m_Edit_Lag.GetWindowText(work_str,sizeof(work_str));
  dummy_long_double = strtod(work_str, &str_ptr);
  return_status = setlag(dummy_long_double);

  if (return_status != return_success)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,"",MB_OK);

	  goto func_end;

  }
  return_status = proc_mbs();

  if (return_status != return_success)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,"",MB_OK);

	  goto func_end;

  }



  dummy_long_double = strtod(work_str, &str_ptr);
  return_status = setlag(dummy_long_double);
 
  return_status =  check_all_parms();

  if (return_status == return_err_mat_date_bad)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_maturity_date,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_val_date_bad)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_value_date,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_iss_date_bad)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_issue_date,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_penult_date_bad)
  {

	 errtext(return_status, err_msg);

	::MessageBox(NULL,err_msg,language_next_to_last_pay_date,MB_OK);

	goto func_end;

  }

  if (return_status == return_info_max_mat_exc)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_val_gt_mat)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		goto func_end;

  }


  if (return_status == return_err_iss_gt_val)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }


  if (return_status == return_err_iss_gt_mat)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_iss_gt_penult)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_penult_ge_mat)
  {
  		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_iss_ge_first)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }
  if (return_status == return_err_first_gt_mat)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_dates_out_synch)
  {
  /*{ Dates are not in synch. }*/
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_non_zero_disc)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_interest_rate,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_neg_int)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_interest_rate,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_int_too_high)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_interest_rate,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_yield_meth_inv)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_yield_method,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_calc_what_inv)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_yield_price_choice,MB_OK);

		goto func_end;

  }

  if (return_status == return_err_price_le_zero)
  {
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_price_check,MB_OK);

		goto func_end;

  }



  if (return_status)
  {

		itoa((int)return_status,work_str,10);
		 errtext(return_status, err_msg);

		::MessageBox(NULL,err_msg,language_default_dates_application_error,MB_OK);

		goto func_end;

  }
  /*{ Clear the dynamic fields before calculating.}*/

  return_status =  getclassdesc(class_desc_hold);

  if (strcmp(class_desc_hold,instr_cashflow_class_name) != 0)
  {

	m_PreviousCoup.SetWindowText("                  ");
	m_NextCoup.SetWindowText("                  ");
	m_InterestDays.SetWindowText("                  ");
	m_AccruedInterest.SetWindowText("                  ");
	m_DirtyPrice.SetWindowText("                  ");

	InitDateHold(date_hold,sizeof(date_hold));

	return_status =  getprevcoup(date_hold);
	m_PreviousCoup.SetWindowText(date_hold);

	InitDateHold(date_hold,sizeof(date_hold));

	return_status =  getnextcoup(date_hold);
	m_NextCoup.SetWindowText(date_hold);
  }
  m_Duration.SetWindowText("                  ");
  m_ModDuration.SetWindowText("                  ");
  m_Convexity.SetWindowText("                  ");
  m_pvbp.SetWindowText("                  ");

  return_status =  getclassdesc(class_desc_hold);

  if (strcmp(class_desc_hold,instr_cashflow_class_name) != 0)
  {
	return_status =  calc_int();

	if (return_status)
	{
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_error,MB_OK);

	  goto func_end;
	}

	return_status =  getintdays(&interest_days_parm);

	ltoa(interest_days_parm,work_str,10);

	m_InterestDays.SetWindowText(work_str);

	return_status =  getinterest(&interest_parm);

	interest_double = (double)interest_parm * 100;

	gcvt(interest_double, price_places, work_str);

	m_AccruedInterest.SetWindowText(work_str);

  }

  return_status =  getcalcwhat(&current_calc_what);

  if (current_calc_what == py_yield_from_price_calc_what)

  {

	return_status =  getinprice(&dummy_long_double);

	return_status =  getnomadj(&nominal_adj_parm);

	dirt_price = ((dummy_long_double * nominal_adj_parm) + interest_double);

	return_status =  getclassdesc(class_desc_hold);

	if (strcmp(class_desc_hold, instr_cashflow_class_name) != 0)
	{

	  interest_double = (double) dirt_price;

	  gcvt(interest_double, price_places, work_str);

	  m_DirtyPrice.SetWindowText(work_str);
	}

  }

  return_status =  getinprice(&dummy_long_double);

  dummy_long_double = dummy_long_double /100;

  return_status =  setinprice(dummy_long_double);

  dirt_price = dirt_price/100;

   getinyield(&dummy_long_double);

  dummy_long_double = dummy_long_double/100;

   setinyield(dummy_long_double);

  return_status =  calc_py();

  if (return_status == return_err_max_coups)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_yield_price_choice,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_max_iter)
  {
	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_yield_price_choice,MB_OK);

	  goto func_end;

  }

  if (return_status)
  {

	   errtext(return_status, err_msg);

	  ::MessageBox(NULL,err_msg,language_error,MB_OK);

	  goto func_end;

  }

  return_status =  getcalcwhat(&current_calc_what);

  if (current_calc_what == py_yield_from_price_calc_what)
  {

	  return_status =  getoutyield(&dummy_long_double);

	  interest_double = (double)dummy_long_double * 100;

	  gcvt(interest_double, price_places, work_str);

	  m_YieldDiscount.SetWindowText(work_str);

  }
  else
  {

	  return_status =  getoutprice(&dummy_long_double);

	  interest_double = ((double) dummy_long_double) * 100;

	  gcvt(interest_double, price_places, work_str);

	  m_CleanPrice.SetWindowText(work_str);


	  return_status =  getclassdesc(class_desc_hold);

	  if (strcmp(class_desc_hold, instr_cashflow_class_name) != 0)
	  {

		 return_status =  getinterest(&interest_parm);

		 interest_double = (double)interest_parm * 100;

		 gcvt(interest_double, price_places, work_str);

		 m_AccruedInterest.SetWindowText(work_str);

		 return_status =  getoutprice(&dummy_long_double);

		 return_status =  getnomadj(&nominal_adj_parm);

		 dirt_price = ((dummy_long_double * nominal_adj_parm) + interest_parm) * 100;

		 interest_double = (double) dirt_price;

		 gcvt(interest_double, price_places, work_str);

		 m_DirtyPrice.SetWindowText(work_str);
	  }
	}

	return_status =  getduration(&dummy_long_double);
	gcvt(dummy_long_double, price_places, work_str);
	m_Duration.SetWindowText(work_str);

	return_status =  getmodduration(&dummy_long_double);
	gcvt(dummy_long_double, price_places, work_str);
	m_ModDuration.SetWindowText(work_str);

	return_status =  getconvexity(&dummy_long_double);
	gcvt(dummy_long_double, price_places, work_str);
	m_Convexity.SetWindowText(work_str);

	return_status =  getpvbp(&dummy_long_double);
	gcvt(dummy_long_double * 100, price_places, work_str);
	m_pvbp.SetWindowText(work_str);


func_end:

return;
	
}

unsigned long CBondCalculator::CheckDates(  )
{

	 /* Validate Value Date.*/

	 InitDateHold(date_hold,sizeof(date_hold));

	 m_ValueDate.GetWindowText(date_hold,sizeof(date_hold));

	 return_status =  setvaldate(date_hold);

	 if ((return_status) && (return_status != return_err_date_bad))
	 {

		if (return_status == return_err_date_form_bad)
		{

		  goto func_end;

		}
		else
		{

//		  errproc(return_status,module_name,"","","");

		  goto func_end;

		}
	 }

	 /* Maturity Date.*/

	 InitDateHold(date_hold,sizeof(date_hold));

	 m_MaturityDate.GetWindowText(date_hold,sizeof(date_hold));

     return_status =  setmatdate(date_hold);

	 if ((return_status) &&
	  (return_status != return_err_date_bad))

	 {

		if (return_status == return_err_date_form_bad)
		{

		   errtext(return_status, err_msg);

		}
		else
		{

//		  errproc(return_status,module_name,"","","");

		  goto func_end;
		}


		goto func_end;

	 }


	 /*{ Validate Issue Date. }*/

	 InitDateHold(date_hold,sizeof(date_hold));

	 m_Issue_Date.GetWindowText(date_hold,sizeof(date_hold));

	 return_status =  setissuedate(date_hold);

	 if ((return_status) && (return_status != return_err_date_bad))
	 {

		if (return_status == return_err_date_form_bad)
		{

		  goto func_end;

		}
      else
		{

//		  errproc(return_status,module_name,"","","");

		  goto func_end;
		}

	 }

	 if (active_type != FRN_type)
	 {

		/*{ Validate First Pay Date. }*/

		InitDateHold(date_hold,sizeof(date_hold));

		m_First_Pay.GetWindowText(date_hold,sizeof(date_hold));

		return_status =  setfirstdate(date_hold);
		if ((return_status) && (return_status != return_err_date_bad))
		{

		  if (return_status == return_err_date_form_bad)
		  {

				goto func_end;

		  }
		  else
		  {

//			 errproc(return_status,module_name,"","","");

			 goto func_end;

		  }

		}

		/* { Validate Next to Last Pay Date. }*/

		InitDateHold(date_hold,sizeof(date_hold));

		m_Next_To_Last_Pay.GetWindowText(date_hold,sizeof(date_hold));

		return_status =  setpenultdate(date_hold);

		if ((return_status) && (return_status != return_err_date_bad))
		{

		  if (return_status == return_err_date_form_bad)
		  {

				goto func_end;

		  }
		  else
		  {

//			 errproc(return_status,module_name,"","","");

			 goto func_end;

		  }

		}

		m_InterestRate.GetWindowText(work_str,sizeof(work_str));
		dummy_long_double = strtod(work_str, &str_ptr);
		dummy_long_double = dummy_long_double/100;
		return_status =  setintrate(dummy_long_double);

	 }

func_end:

	return return_status;
}
void CBondCalculator::InitDateHold(char * date_hold, int date_hold_size)
{
	int local_count;
	
	dummy_size_t = date_hold_size;
	for (local_count = 0; local_count < date_hold_size; local_count++)
	{
	  memcpy(&date_hold[local_count]," ", 1);
	}

}

void CBondCalculator::OnSelchangeCOMBOHolidays() 
{
	// TODO: Add your control notification handler code here
	
	int list_number;

	list_number = m_Holidays.GetCurSel();
//	m_Holidays.GetLBText( list_number, holicodehold);

//	return_status =  setholiday(holicodehold);
//	return_status =  proc_excoup();

	
}
