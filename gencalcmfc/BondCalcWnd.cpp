// BondCalcWnd.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "BondCalcWnd.h"
#include "Wordsymb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBondCalcWnd

IMPLEMENT_DYNCREATE(CBondCalcWnd, CMDIChildWnd)

CBondCalcWnd::CBondCalcWnd()
{
}

CBondCalcWnd::~CBondCalcWnd()
{
}



BEGIN_MESSAGE_MAP(CBondCalcWnd, CMDIChildWnd)
	ON_CBN_SELCHANGE(ID_instr_class,HandleInstrClass)
	ON_CBN_SELCHANGE(ID_day_count,HandleDayCount)
	ON_CBN_SELCHANGE(ID_pay_freq,HandlePayFreq)	
	ON_CBN_SELCHANGE(ID_yield_days,HandleYieldDays)
	ON_CBN_SELCHANGE(ID_yield_freq,HandleYieldFreq)	
	ON_CBN_SELCHANGE(ID_yield_meth,HandleYieldMeth)
	ON_CBN_SELCHANGE(ID_monthend,HandleMonthEnd)
	ON_CBN_SELCHANGE(ID_excoup,HandleExcoup)
    ON_COMMAND(ID_y_from_p,HandleCalcBox)
    ON_COMMAND(ID_p_from_y,HandleCalcBox)
    ON_COMMAND(ID_def_date,HandleDefDates)
    ON_COMMAND(ID_calculate,HandleCalculate)
  //{{AFX_MSG_MAP(CBondCalcWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBondCalcWnd message handlers

BOOL CBondCalcWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	Calc_type = 0;
	FRN_type = 1;
	pay_type_control = 0;
	price_places = 15;
	pay_type_control = 0;
	interest_days_parm = 0;
	interest_parm = 0;
	interest_double = 0;
	dirt_price = 0;
	nominal_adj_parm = 0;

	active_type = Calc_type;

	return_status = pyfront.init_screen();

	InitInstrClass();
	InitInterestRate();
	InitValueDate();
	InitPreviousCoup();
	InitNextCoup();
	InitCleanPrice();
	InitAccruedInterest();
	InitDirtyPrice();
	InitYieldDiscount();
	InitMaturityDate();
	InitDayCount();
	InitPayFreq();
	InitDefDate();
	InitIssueDate();	
	InitFirstPay();	
	InitPenultPay();
	InitExCoup();
	InitIntDays();	
	InitYieldMeth();
	InitCalcChoice();
	InitCalculate();
	InitMonthEnd();
	InitExcoup();
	InitYieldDays();
	InitYieldFreq();
	InitDuration();
	InitModDuration();
	InitConvexity();
	InitPVBP();


	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

void CBondCalcWnd::HandleInstrClass( )

{

	{

	 class_number = instr_class.GetCurSel();
	 instr_class.GetLBText( class_number, class_desc_hold);

	 return_status = pyfront.setclassdesc(class_desc_hold);
	 return_status = pyfront.proc_class_desc();
	 return_status = pyfront.getdaycount(day_count_hold);

	 day_count.SelectString(-1,day_count_hold);
	 return_status = pyfront.getpayfreq(pay_freq_hold);

	 pay_freq.SelectString(-1,pay_freq_hold);
	 return_status = pyfront.getyielddays(yielddays_name_hold);
	 yield_days.SelectString(-1,yielddays_name_hold);
	 return_status = pyfront.getyieldfreq(yieldfreq_name_hold);

	 yield_freq.SelectString(-1,yieldfreq_name_hold);

	 return_status = pyfront.getyieldmeth(yieldmeth_name_hold);

	 yield_meth.SelectString(-1,yieldmeth_name_hold);

	 if ( current_calc_what == py_yield_from_price_calc_what )
	 {
		y_from_p.SetCheck(BS_CHECKED);
		p_from_y.SetCheck(BS_UNCHECKED);
	 }
	 else
	 {
		p_from_y.SetCheck(BS_CHECKED);
		y_from_p.SetCheck(BS_UNCHECKED);
	 }
	 return_status = pyfront.getmonthend(month_end_hold);

	 monthend.SelectString(-1,month_end_hold);
	 return_status = pyfront.getexcoup(excoup_name_hold);
	 return_status = excoup.SelectString(-1,excoup_name_hold);



	 return_status = pyfront.getcalcwhat(&current_calc_what);


	 return_status = pyfront.getexcoupdays(&dummy_int);
	 itoa(dummy_int,work_str,10);
	 ex_coup.SetWindowText(work_str);


  
  }

}

void CBondCalcWnd::HandleDayCount( )
{
  {

	 day_count_number = day_count.GetCurSel();
	 day_count.GetLBText( day_count_number, day_count_hold);

	 return_status = pyfront.setdaycount(day_count_hold);

	 return_status = pyfront.proc_day_count();

	 return_status = pyfront.getyielddays(&yield_days_number);
	 yield_days.SetCurSel(yield_days_number);

  }
}

void CBondCalcWnd::HandlePayFreq()
{
  {

	 pay_freq_number = pay_freq.GetCurSel();
	 pay_freq.GetLBText( pay_freq_number, pay_freq_hold);

	 return_status = pyfront.setpayfreq(pay_freq_hold);

	 return_status = pyfront.proc_pay_freq();

	 return_status = pyfront.getyieldfreq(&yield_freq_number);

	 yield_freq.SetCurSel(yield_freq_number);
  
	}
}

void CBondCalcWnd::HandleYieldDays( )
{
  {

	 yield_days_number = yield_days.GetCurSel();
	 yield_days.GetLBText( yield_days_number, yielddays_name_hold);

	 return_status = pyfront.setyielddays(yielddays_name_hold);

	 return_status = pyfront.proc_yield_days();

  }
}

void CBondCalcWnd::HandleYieldFreq()
{
  {

	 yield_freq_number = yield_freq.GetCurSel();
	 yield_freq.GetLBText( yield_freq_number, yieldfreq_name_hold);

	 return_status = pyfront.setyieldfreq(yieldfreq_name_hold);

	 return_status = pyfront.proc_yield_freq();

	}
}

void CBondCalcWnd::HandleYieldMeth()
{
  {

	 yield_meth_number = yield_meth.GetCurSel();
	 yield_meth.GetLBText( yield_meth_number, yieldmeth_name_hold);

	 return_status = pyfront.setyieldmeth(yieldmeth_name_hold);

	 return_status = pyfront.proc_yield_meth();

	}
}

void CBondCalcWnd::InitInstrClass()
{
  
	Rect1.left = instr_class_prompt_x;
	Rect1.right = instr_class_prompt_x + instr_class_prompt_w;
	Rect1.top = instr_class_prompt_y;
	Rect1.bottom = instr_class_prompt_y + instr_class_prompt_h;

	instr_class_prompt.Create(language_instrument_class_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

  
	Rect1.left = instr_class_x;
	Rect1.right = instr_class_x + instr_class_w;
	Rect1.top = instr_class_y;
	Rect1.bottom = instr_class_y + instr_class_h;

	instr_class.Create(combo_style 
					,Rect1
					,this
					,ID_instr_class
					);
	for (element_count = 0; element_count <
	  instr_last_class; ++element_count)
	{

		return_status = pyfront.getclassdesc(element_count, class_desc_hold);

		instr_class.AddString(class_desc_hold);

	}

	return_status = pyfront.getclassnumber(&class_number);
	return_status = instr_class.SetCurSel(class_number);

}


void CBondCalcWnd::InitInterestRate()
{

	Rect1.left = interest_rate_prompt_x;
	Rect1.right = interest_rate_prompt_x + interest_rate_prompt_w;
	Rect1.top = interest_rate_prompt_y;
	Rect1.bottom = interest_rate_prompt_y + interest_rate_prompt_h;

	interest_rate_prompt.Create(language_interest_rate_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = interest_rate_x;
	Rect1.right = interest_rate_x + interest_rate_w;
	Rect1.top = interest_rate_y;
	Rect1.bottom = interest_rate_y + interest_rate_h;

	interest_rate.Create(edit_style 
						,Rect1
						,this
						,ID_interest_rate
							);

	return_status = pyfront.getintrate(&dummy_long_double);

	ltoa(dummy_long_double,work_str,10);
	interest_rate.SetWindowText(work_str);

}

void CBondCalcWnd::InitValueDate()
{

	Rect1.left = value_date_prompt_x;
	Rect1.right = value_date_prompt_x + value_date_prompt_w;
	Rect1.top = value_date_prompt_y;
	Rect1.bottom = value_date_prompt_y + value_date_prompt_h;

	value_date_prompt.Create(language_value_date_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = value_date_x;
	Rect1.right = value_date_x + value_date_w;
	Rect1.top = value_date_y;
	Rect1.bottom = value_date_y + value_date_h;

	value_date.Create(edit_style 
						,Rect1
						,this
						,ID_value_date
							);

}

void CBondCalcWnd::InitMaturityDate()
{

	Rect1.left = maturity_date_prompt_x;
	Rect1.right = maturity_date_prompt_x + maturity_date_prompt_w;
	Rect1.top = maturity_date_prompt_y;
	Rect1.bottom = maturity_date_prompt_y + maturity_date_prompt_h;

	maturity_date_prompt.Create(language_maturity_date_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = maturity_date_x;
	Rect1.right = maturity_date_x + maturity_date_w;
	Rect1.top = maturity_date_y;
	Rect1.bottom = maturity_date_y + maturity_date_h;

	maturity_date.Create(edit_style 
						,Rect1
						,this
						,ID_maturity_date
							);

}

void CBondCalcWnd::InitPreviousCoup()
{

	Rect1.left = previous_coup_prompt_x;
	Rect1.right = previous_coup_prompt_x + previous_coup_prompt_w;
	Rect1.top = previous_coup_prompt_y;
	Rect1.bottom = previous_coup_prompt_y + previous_coup_prompt_h;

	previous_coup_prompt.Create(language_previous_coupon_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = previous_coup_x;
	Rect1.right = previous_coup_x + previous_coup_w;
	Rect1.top = previous_coup_y;
	Rect1.bottom = previous_coup_y + previous_coup_h;


	previous_coup.Create(""
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

}

void CBondCalcWnd::InitNextCoup()
{

	Rect1.left = next_coup_prompt_x;
	Rect1.right = next_coup_prompt_x + next_coup_prompt_w;
	Rect1.top = next_coup_prompt_y;
	Rect1.bottom = next_coup_prompt_y + next_coup_prompt_h;

	next_coup_prompt.Create(language_next_coupon_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = next_coup_x;
	Rect1.right = next_coup_x + next_coup_w;
	Rect1.top = next_coup_y;
	Rect1.bottom = next_coup_y + next_coup_h;


	next_coup.Create(""
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

}

void CBondCalcWnd::InitCleanPrice()
{

	Rect1.left = clean_price_prompt_x;
	Rect1.right = clean_price_prompt_x + clean_price_prompt_w;
	Rect1.top = clean_price_prompt_y;
	Rect1.bottom = clean_price_prompt_y + clean_price_prompt_h;

	clean_price_prompt.Create(language_clean_price_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = clean_price_x;
	Rect1.right = clean_price_x + clean_price_w;
	Rect1.top = clean_price_y;
	Rect1.bottom = clean_price_y + clean_price_h;

	clean_price.Create(edit_style
						,Rect1
						,this
						,ID_clean_price
							);

	return_status = pyfront.getinprice(&dummy_long_double);

	ltoa(dummy_long_double,work_str,10);
	clean_price.SetWindowText(work_str);

}

void CBondCalcWnd::InitAccruedInterest()
{

	Rect1.left = accrued_interest_prompt_x;
	Rect1.right = accrued_interest_prompt_x + accrued_interest_prompt_w;
	Rect1.top = accrued_interest_prompt_y;
	Rect1.bottom = accrued_interest_prompt_y + accrued_interest_prompt_h;

	accrued_interest_prompt.Create(language_accrued_interest_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = accrued_interest_x;
	Rect1.right = accrued_interest_x + accrued_interest_w;
	Rect1.top = accrued_interest_y;
	Rect1.bottom = accrued_interest_y + accrued_interest_h;

	accrued_interest.Create(""
						,prompt_style 
						,Rect1
						,this
						,ID_accrued_interest
							);

}

void CBondCalcWnd::InitDirtyPrice()
{

	Rect1.left = dirty_price_prompt_x;
	Rect1.right = dirty_price_prompt_x + dirty_price_prompt_w;
	Rect1.top = dirty_price_prompt_y;
	Rect1.bottom = dirty_price_prompt_y + dirty_price_prompt_h;

	dirty_price_prompt.Create(language_dirty_price_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = dirty_price_x;
	Rect1.right = dirty_price_x + dirty_price_w;
	Rect1.top = dirty_price_y;
	Rect1.bottom = dirty_price_y + dirty_price_h;

	dirty_price.Create(""
						,prompt_style 
						,Rect1
						,this
						,ID_dirty_price
							);

}

void CBondCalcWnd::InitYieldDiscount()
{

	Rect1.left = yield_discount_prompt_x;
	Rect1.right = yield_discount_prompt_x + yield_discount_prompt_w;
	Rect1.top = yield_discount_prompt_y;
	Rect1.bottom = yield_discount_prompt_y + yield_discount_prompt_h;

	yield_discount_prompt.Create(language_yield_discount_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = yield_discount_x;
	Rect1.right = yield_discount_x + yield_discount_w;
	Rect1.top = yield_discount_y;
	Rect1.bottom = yield_discount_y + yield_discount_h;

	yield_discount.Create(edit_style 
						,Rect1
						,this
						,ID_yield_discount
							);

	return_status = pyfront.getinyield(&dummy_long_double);

	ltoa(dummy_long_double,work_str,10);
	yield_discount.SetWindowText(work_str);

}

void CBondCalcWnd::InitYieldDays()
{
  
	Rect1.left = yield_days_prompt_x;
	Rect1.right = yield_days_prompt_x + yield_days_prompt_w;
	Rect1.top = yield_days_prompt_y;
	Rect1.bottom = yield_days_prompt_y + yield_days_prompt_h;

	yield_days_prompt.Create(language_yield_days_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

  
	Rect1.left = yield_days_x;
	Rect1.right = yield_days_x + yield_days_w;
	Rect1.top = yield_days_y;
	Rect1.bottom = yield_days_y + yield_days_h;

	yield_days.Create(combo_style 
					,Rect1
					,this
					,ID_yield_days
					);

	 for (element_count = 0; element_count <
	  date_last_day_count; ++element_count)
	 {


		return_status = pyfront.getyielddays(element_count, yielddays_name_hold);

		yield_days.AddString(yielddays_name_hold);

	 }


	 return_status = pyfront.getyielddays(&yield_days_number);
	 return_status = yield_days.SetCurSel(yield_days_number);

}

void CBondCalcWnd::InitYieldFreq()
{
  
	Rect1.left = yield_freq_prompt_x;
	Rect1.right = yield_freq_prompt_x + yield_freq_prompt_w;
	Rect1.top = yield_freq_prompt_y;
	Rect1.bottom = yield_freq_prompt_y + yield_freq_prompt_h;

	yield_freq_prompt.Create(language_yield_freq_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

  
	Rect1.left = yield_freq_x;
	Rect1.right = yield_freq_x + yield_freq_w;
	Rect1.top = yield_freq_y;
	Rect1.bottom = yield_freq_y + yield_freq_h;

	yield_freq.Create(combo_style 
					,Rect1
					,this
					,ID_yield_freq
					);

	 for (element_count = 0; element_count <
	  freq_count; ++element_count)
	 {


		return_status = pyfront.getyieldfreq(element_count, yieldmeth_name_hold);

		yield_freq.AddString(yieldmeth_name_hold);

	 }


	 return_status = pyfront.getyieldfreq(&yield_freq_number);
	 return_status = yield_freq.SetCurSel(yield_freq_number);

}

void CBondCalcWnd::InitDuration()
{

	Rect1.left = duration_prompt_x;
	Rect1.right = duration_prompt_x + duration_prompt_w;
	Rect1.top = duration_prompt_y;
	Rect1.bottom = duration_prompt_y + duration_prompt_h;

	duration_prompt.Create(language_duration_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = duration_x;
	Rect1.right = duration_x + duration_w;
	Rect1.top = duration_y;
	Rect1.bottom = duration_y + duration_h;

	duration.Create(""
						,prompt_style 
						,Rect1
						,this
						,ID_duration
							);

}

void CBondCalcWnd::InitModDuration()
{

	Rect1.left = mod_duration_prompt_x;
	Rect1.right = mod_duration_prompt_x + mod_duration_prompt_w;
	Rect1.top = mod_duration_prompt_y;
	Rect1.bottom = mod_duration_prompt_y + mod_duration_prompt_h;

	mod_duration_prompt.Create(language_modified_dur_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = mod_duration_x;
	Rect1.right = mod_duration_x + mod_duration_w;
	Rect1.top = mod_duration_y;
	Rect1.bottom = mod_duration_y + mod_duration_h;

	mod_duration.Create(""
						,prompt_style 
						,Rect1
						,this
						,ID_mod_duration
							);

}

void CBondCalcWnd::InitConvexity()
{

	Rect1.left = convexity_prompt_x;
	Rect1.right = convexity_prompt_x + convexity_prompt_w;
	Rect1.top = convexity_prompt_y;
	Rect1.bottom = convexity_prompt_y + convexity_prompt_h;

	convexity_prompt.Create(language_convexity_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = convexity_x;
	Rect1.right = convexity_x + convexity_w;
	Rect1.top = convexity_y;
	Rect1.bottom = convexity_y + convexity_h;

	convexity.Create(""
						,prompt_style 
						,Rect1
						,this
						,ID_convexity
							);

}

void CBondCalcWnd::InitPVBP()
{

	Rect1.left = pvbp_prompt_x;
	Rect1.right = pvbp_prompt_x + pvbp_prompt_w;
	Rect1.top = pvbp_prompt_y;
	Rect1.bottom = pvbp_prompt_y + pvbp_prompt_h;

	pvbp_prompt.Create(language_pvbp_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = pvbp_x;
	Rect1.right = pvbp_x + pvbp_w;
	Rect1.top = pvbp_y;
	Rect1.bottom = pvbp_y + pvbp_h;

	pvbp.Create(""
						,prompt_style 
						,Rect1
						,this
						,ID_pvbp
							);

}


void CBondCalcWnd::InitDayCount()
{


	Rect1.left = day_count_prompt_x;
	Rect1.right = day_count_prompt_x + day_count_prompt_w;
	Rect1.top = day_count_prompt_y;
	Rect1.bottom = day_count_prompt_y + day_count_prompt_h;

	day_count_prompt.Create(language_day_count_method_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

  
	Rect1.left = day_count_x;
	Rect1.right = day_count_x + day_count_w;
	Rect1.top = day_count_y;
	Rect1.bottom = day_count_y + day_count_h;


	day_count.Create(combo_style 
					,Rect1
					,this
					,ID_day_count
					);

	for (element_count = 0; element_count <
	 date_last_day_count; ++element_count)
	{


		return_status = pyfront.getdaycount(element_count, day_count_hold);

		day_count.AddString(day_count_hold);

	}


	return_status = pyfront.getdaycount(&day_count_number);
	day_count.SetCurSel(day_count_number);
	day_count.GetLBText( day_count_number, day_count_hold);

	return_status = pyfront.setdaycount(day_count_hold);


}


void CBondCalcWnd::InitPayFreq()
{
  
	Rect1.left = pay_freq_prompt_x;
	Rect1.right = pay_freq_prompt_x + pay_freq_prompt_w;
	Rect1.top = pay_freq_prompt_y;
	Rect1.bottom = pay_freq_prompt_y + pay_freq_prompt_h;

	pay_freq_prompt.Create(language_pay_freq_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);
  
	Rect1.left = pay_freq_x;
	Rect1.right = pay_freq_x + pay_freq_w;
	Rect1.top = pay_freq_y;
	Rect1.bottom = pay_freq_y + pay_freq_h;


	pay_freq.Create(combo_style 
					,Rect1
					,this
					,ID_pay_freq
					);

	 for (element_count = 0; element_count <
	  freq_count; ++element_count)
	 {


		return_status = pyfront.getpayfreq(element_count, pay_freq_hold);

		pay_freq.AddString(pay_freq_hold);

	 }

	 return_status = pyfront.getpayfreq(&pay_freq_number);

	 pay_freq.SetCurSel(pay_freq_number);

} 

void CBondCalcWnd::InitDefDate()
{
  
	Rect1.left = date_format_prompt_x;
	Rect1.right = date_format_prompt_x + date_format_prompt_w;
	Rect1.top = date_format_prompt_y;
	Rect1.bottom = date_format_prompt_y + date_format_prompt_h;

	date_format_prompt.Create(language_date_format
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);
 
	Rect1.left = def_date_x;
	Rect1.right = def_date_x + def_date_w;
	Rect1.top = def_date_y;
	Rect1.bottom = def_date_y + def_date_h;

	def_date.Create(language_default_dates
					 ,button_style
					 ,Rect1
					 ,this
					 ,ID_def_date);
}

void CBondCalcWnd::InitIssueDate()
{

	Rect1.left = issue_date_prompt_x;
	Rect1.right = issue_date_prompt_x + issue_date_prompt_w;
	Rect1.top = issue_date_prompt_y;
	Rect1.bottom = issue_date_prompt_y + issue_date_prompt_h;

	issue_date_prompt.Create(language_issue_date_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = issue_date_x;
	Rect1.right = issue_date_x + issue_date_w;
	Rect1.top = issue_date_y;
	Rect1.bottom = issue_date_y + issue_date_h;

	issue_date.Create(edit_style 
						,Rect1
						,this
						,ID_issue_date
							);

}

void CBondCalcWnd::InitFirstPay()
{

	Rect1.left = first_pay_prompt_x;
	Rect1.right = first_pay_prompt_x + first_pay_prompt_w;
	Rect1.top = first_pay_prompt_y;
	Rect1.bottom = first_pay_prompt_y + first_pay_prompt_h;

	first_pay_prompt.Create(language_first_pay_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = first_pay_x;
	Rect1.right = first_pay_x + first_pay_w;
	Rect1.top = first_pay_y;
	Rect1.bottom = first_pay_y + first_pay_h;

	first_pay.Create(edit_style 
						,Rect1
						,this
						,ID_first_pay
							);

}

void CBondCalcWnd::InitPenultPay()
{

	Rect1.left = penult_pay_prompt_x;
	Rect1.right = penult_pay_prompt_x + penult_pay_prompt_w;
	Rect1.top = penult_pay_prompt_y;
	Rect1.bottom = penult_pay_prompt_y + penult_pay_prompt_h;

	penult_pay_prompt.Create(language_penult_pay_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = penult_pay_x;
	Rect1.right = penult_pay_x + penult_pay_w;
	Rect1.top = penult_pay_y;
	Rect1.bottom = penult_pay_y + penult_pay_h;

	penult_pay.Create(edit_style 
						,Rect1
						,this
						,ID_penult_pay
							);

}


void CBondCalcWnd::InitExCoup()
{

	Rect1.left = ex_coup_prompt_x;
	Rect1.right = ex_coup_prompt_x + ex_coup_prompt_w;
	Rect1.top = ex_coup_prompt_y;
	Rect1.bottom = ex_coup_prompt_y + ex_coup_prompt_h;

	ex_coup_prompt.Create(language_ex_coup_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = ex_coup_x;
	Rect1.right = ex_coup_x + ex_coup_w;
	Rect1.top = ex_coup_y;
	Rect1.bottom = ex_coup_y + ex_coup_h;

	ex_coup.Create(""
						,prompt_style 
						,Rect1
						,this
						,ID_ex_coup
							);

	return_status = pyfront.getexcoupdays(&dummy_int);

	itoa(dummy_int,work_str,10);
	ex_coup.SetWindowText(work_str);
}

void CBondCalcWnd::InitIntDays()
{

	Rect1.left = int_days_prompt_x;
	Rect1.right = int_days_prompt_x + int_days_prompt_w;
	Rect1.top = int_days_prompt_y;
	Rect1.bottom = int_days_prompt_y + int_days_prompt_h;

	int_days_prompt.Create(language_int_days_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

	Rect1.left = int_days_x;
	Rect1.right = int_days_x + int_days_w;
	Rect1.top = int_days_y;
	Rect1.bottom = int_days_y + int_days_h;

	int_days.Create(""
						,prompt_style 
						,Rect1
						,this
						,ID_int_days
							);

}

void CBondCalcWnd::InitYieldMeth()
{
  
	Rect1.left = yield_meth_prompt_x;
	Rect1.right = yield_meth_prompt_x + yield_meth_prompt_w;
	Rect1.top = yield_meth_prompt_y;
	Rect1.bottom = yield_meth_prompt_y + yield_meth_prompt_h;

	yield_meth_prompt.Create(language_yield_meth_colon
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

  
	Rect1.left = yield_meth_x;
	Rect1.right = yield_meth_x + yield_meth_w;
	Rect1.top = yield_meth_y;
	Rect1.bottom = yield_meth_y + yield_meth_h;

	yield_meth.Create(combo_style 
					,Rect1
					,this
					,ID_yield_meth
					);

	 for (element_count = 0; element_count <
	  py_last_yield_meth; ++element_count)
	 {


		return_status = pyfront.getyieldmeth(element_count, yieldmeth_name_hold);

		yield_meth.AddString(yieldmeth_name_hold);

	 }


	 return_status = pyfront.getyieldmeth(&yield_meth_number);
	 return_status = yield_meth.SetCurSel(yield_meth_number);

}

void CBondCalcWnd::InitCalcChoice()
{
 	current_calc_what = 0;
	BS_CHECKED  = 1;
	BS_UNCHECKED  = 0;
	
	Rect1.left = calc_choice_x;
	Rect1.right = calc_choice_x + calc_choice_w;
	Rect1.top = calc_choice_y;
	Rect1.bottom = calc_choice_y + calc_choice_h;

	calc_choice.Create(language_calc_choice
							,group_box_style 
							,Rect1
							,this
							,ID_calc_choice
							);

	
	Rect1.left = y_from_p_x;
	Rect1.right = y_from_p_x + y_from_p_w;
	Rect1.top = y_from_p_y;
	Rect1.bottom = y_from_p_y + y_from_p_h;

	y_from_p.Create(language_y_from_p
							,radiobutton_style 
							,Rect1
							,this
							,ID_y_from_p
							);
	
	Rect1.left = p_from_y_x;
	Rect1.right = p_from_y_x + p_from_y_w;
	Rect1.top = p_from_y_y;
	Rect1.bottom = p_from_y_y + p_from_y_h;

	p_from_y.Create(language_p_from_y
							,radiobutton_style 
							,Rect1
							,this
							,ID_p_from_y
							);

}

void CBondCalcWnd::HandleCalcBox(  )
{



  if ( y_from_p.GetCheck() == BS_CHECKED )
  {

	 return_status = pyfront.setcalcwhat(py_yield_from_price_calc_what);

  }
  else
  {

	 return_status = pyfront.setcalcwhat(py_price_from_yield_calc_what);

  }

  return_status = pyfront.proc_calc_what( );



}

void CBondCalcWnd::InitCalculate()
{
 
	Rect1.left = calculate_x;
	Rect1.right = calculate_x + calculate_w;
	Rect1.top = calculate_y;
	Rect1.bottom = calculate_y + calculate_h;

	calculate.Create(language_calculate
					 ,button_style
					 ,Rect1
					 ,this
					 ,ID_calculate);
}

void CBondCalcWnd::InitMonthEnd()
{
  
	Rect1.left = monthend_prompt_x;
	Rect1.right = monthend_prompt_x + monthend_prompt_w;
	Rect1.top = monthend_prompt_y;
	Rect1.bottom = monthend_prompt_y + monthend_prompt_h;

	monthend_prompt.Create(language_month_end
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

  
	Rect1.left = monthend_x;
	Rect1.right = monthend_x + monthend_w;
	Rect1.top = monthend_y;
	Rect1.bottom = monthend_y + monthend_h;

	monthend.Create(combo_style 
					,Rect1
					,this
					,ID_monthend
					);

	 for (element_count = 0; element_count <
	  monthend_count; ++element_count)
	 {


		return_status = pyfront.getmonthend(element_count, month_end_hold);

		monthend.AddString(month_end_hold);

	 }

	 return_status = pyfront.getmonthend(&month_end_number);

	 return_status = monthend.SetCurSel(month_end_number);
}

void CBondCalcWnd::HandleMonthEnd()
{
  {

	 month_end_number = monthend.GetCurSel();
	 monthend.GetLBText( month_end_number, month_end_hold);

	 return_status = pyfront.setmonthend(month_end_hold);
	 return_status = pyfront.proc_monthend();

	 return_status = pyfront.getmonthend(&month_end_number);

	 monthend.SetCurSel(month_end_number);

  }
}

void CBondCalcWnd::InitExcoup()
{
  
	Rect1.left = excoup_prompt_x;
	Rect1.right = excoup_prompt_x + excoup_prompt_w;
	Rect1.top = excoup_prompt_y;
	Rect1.bottom = excoup_prompt_y + excoup_prompt_h;

	excoup_prompt.Create(language_excoup
							,prompt_style 
							,Rect1
							,this
							,ID_prompt
							);

  
	Rect1.left = excoup_x;
	Rect1.right = excoup_x + excoup_w;
	Rect1.top = excoup_y;
	Rect1.bottom = excoup_y + excoup_h;

	excoup.Create(combo_style 
					,Rect1
					,this
					,ID_excoup
					);

	 for (element_count = 0; element_count <
	  excoup_count; ++element_count)
	 {


		return_status = pyfront.getexcoupchoice(element_count, excoup_name_hold);

		excoup.AddString(excoup_name_hold);

	 }

	 return_status = pyfront.getexcoup(excoup_name_hold);
	 excoup_number = excoup.FindStringExact(-1,excoup_name_hold);

	 return_status = excoup.SetCurSel(excoup_number);
}


void CBondCalcWnd::HandleExcoup()
{
  {

	 excoup_number = excoup.GetCurSel();
	 excoup.GetLBText( excoup_number, excoup_name_hold);

	 return_status = pyfront.setexcoup(excoup_name_hold);
	 return_status = pyfront.proc_excoup();


  }
}

void CBondCalcWnd::HandleDefDates()
{

/* Validate Maturity Date.*/

  InitDateHold(date_hold,sizeof(date_hold));

  maturity_date.GetWindowText(date_hold,sizeof(date_hold));
//  maturity_date.GetLine(0,date_hold);

  return_status = pyfront.setmatdate(date_hold);
  if (return_status)
  {

	 if (return_status == return_err_date_form_bad)
	 {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_maturity_date,MB_OK);

		goto func_end;

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
			  pyfront.errtext(return_status, date_msg);

			  ::MessageBox(NULL,date_msg,language_maturity_date,MB_OK);

			  goto func_end;
			}
		}

	 }
  }

  /* Validate Value Date.*/

  InitDateHold(date_hold,sizeof(date_hold));

  value_date.GetWindowText(date_hold,sizeof(date_hold));
//  value_date.GetLine(0,date_hold);

  return_status = pyfront.setvaldate(date_hold);

  if (return_status)
  {

    if (return_status == return_err_date_form_bad)
	{
	 	pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_value_date,MB_OK);

	 	goto func_end;

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

			pyfront.errtext(return_status, date_msg);

			::MessageBox(NULL,date_msg,language_value_date,MB_OK);

			goto func_end;
		 }
	  }
	}

  }
  return_status = pyfront.proc_def_dates();

  if (return_status == return_err_val_ge_cf)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_value_date,MB_OK);

		goto func_end;

  }

  if (return_status == return_err_mat_date_bad)
  {
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_maturity_date,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_val_date_bad)
  {
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_value_date,MB_OK);

	  goto func_end;

  }

  if (return_status == return_info_max_mat_exc)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		goto func_end;

  }

  if (return_status == return_err_val_gt_mat)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		goto func_end;

  }


  if (return_status)
  {

		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_default_dates_application_error,MB_OK);

		goto func_end;

  }


  InitDateHold(date_hold,sizeof(date_hold));

  return_status = pyfront.getpenultdate(date_hold);

  penult_pay.SetWindowText(date_hold);

  InitDateHold(date_hold,sizeof(date_hold));

  return_status = pyfront.getissuedate(date_hold);

  issue_date.SetWindowText(date_hold);

  InitDateHold(date_hold,sizeof(date_hold));

  return_status = pyfront.getfirstdate(date_hold);
  first_pay.SetWindowText(date_hold);

  if (active_type == Calc_type)

  {

		return_status = pyfront.getexcoup(excoup_name_hold);
		excoup_number = excoup.FindStringExact(-1,excoup_name_hold);

		return_status = excoup.SetCurSel(excoup_number);

  }

func_end:

return;

}
void CBondCalcWnd::InitDateHold(char * date_hold, int date_hold_size)
{
	int local_count;
	
	dummy_size_t = date_hold_size;
	for (local_count = 0; local_count < date_hold_size; local_count++)
	{
	  memcpy(&date_hold[local_count]," ", 1);
	}

}

unsigned long CBondCalcWnd::CheckDates(  )
{

	 /* Validate Value Date.*/

	 InitDateHold(date_hold,sizeof(date_hold));

	 value_date.GetWindowText(date_hold,sizeof(date_hold));

	 return_status = pyfront.setvaldate(date_hold);

	 if ((return_status) && (return_status != return_err_date_bad))
	 {

		if (return_status == return_err_date_form_bad)
		{
		  pyfront.errtext(return_status, date_msg);

		  ::MessageBox(NULL,date_msg,language_value_date,MB_OK);

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

	 maturity_date.GetWindowText(date_hold,sizeof(date_hold));

     return_status = pyfront.setmatdate(date_hold);

	 if ((return_status) &&
	  (return_status != return_err_date_bad))

	 {

		if (return_status == return_err_date_form_bad)
		{

		  pyfront.errtext(return_status, date_msg);

		}
		else
		{

//		  errproc(return_status,module_name,"","","");

		  goto func_end;
		}

		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_maturity_date,MB_OK);

		goto func_end;

	 }


	 /*{ Validate Issue Date. }*/

	 InitDateHold(date_hold,sizeof(date_hold));

	 issue_date.GetWindowText(date_hold,sizeof(date_hold));

	 return_status = pyfront.setissuedate(date_hold);

	 if ((return_status) && (return_status != return_err_date_bad))
	 {

		if (return_status == return_err_date_form_bad)
		{
		  pyfront.errtext(return_status, date_msg);

		  ::MessageBox(NULL,date_msg,language_issue_date,MB_OK);

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

		first_pay.GetWindowText(date_hold,sizeof(date_hold));

		return_status = pyfront.setfirstdate(date_hold);
		if ((return_status) && (return_status != return_err_date_bad))
		{

		  if (return_status == return_err_date_form_bad)
		  {
				pyfront.errtext(return_status, date_msg);

				::MessageBox(NULL,date_msg,"First Pay Date",MB_OK);

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

		penult_pay.GetWindowText(date_hold,sizeof(date_hold));

		return_status = pyfront.setpenultdate(date_hold);

		if ((return_status) && (return_status != return_err_date_bad))
		{

		  if (return_status == return_err_date_form_bad)
		  {
				pyfront.errtext(return_status, date_msg);

				::MessageBox(NULL,date_msg,language_next_to_last_pay_date ,MB_OK);

				goto func_end;

		  }
		  else
		  {

//			 errproc(return_status,module_name,"","","");

			 goto func_end;

		  }

		}

		interest_rate.GetWindowText(work_str,sizeof(work_str));
		dummy_long_double = strtod(work_str, &str_ptr);
		dummy_long_double = dummy_long_double/100;
		return_status = pyfront.setintrate(dummy_long_double);

	 }

func_end:

	return return_status;
}

void CBondCalcWnd::HandleCalculate()
{
/*
  getdate(&sys_date);

  if ((sys_date.da_year > 1997) || ((sys_date.da_year == 1997) && (sys_date.da_mon > 9)))

  {
	 ::MessageBox(Null,date_msg,language_version_expired,MB_OK);

	 goto func_end;

  }
*/

  if (pay_type_control == instr_open_pay_type)
  {
		pay_type_control = instr_fixed_pay_type;

  }

  return_status = pyfront.getclassnumber(&class_number);

  if (class_number != instr_cashflow_class)

  {

	 return_status = CheckDates();

	 if ((return_status) && (return_status != return_err_date_bad))
	 {

		goto func_end;

	 }

  }
  else
  {

	 /* Validate Value Date.*/

	 InitDateHold(date_hold,sizeof(date_hold));

	 value_date.GetWindowText(date_hold,sizeof(date_hold));

	 return_status = pyfront.setvaldate(date_hold);

	 if ((return_status) && (return_status != return_err_date_bad))
	 {

		if (return_status == return_err_date_form_bad)
		{
		  pyfront.errtext(return_status, date_msg);

		  ::MessageBox(NULL,date_msg,language_value_date,MB_OK);

		  goto func_end;

		}
		else
		{

//		  errproc(return_status,module_name,"","","");

		  goto func_end;

		}
	 }
  }


  return_status = pyfront.getcalcwhat(&current_calc_what);

  if (current_calc_what == py_yield_from_price_calc_what)
  {
	 yield_discount.Clear();

	 clean_price.GetWindowText(work_str,sizeof(work_str));

	 dummy_long_double = strtod(work_str, &str_ptr);

	 return_status = pyfront.setinprice(dummy_long_double);

  }
  else
  {
	 clean_price.Clear();

	 yield_discount.GetWindowText(work_str,sizeof(work_str));

	 dummy_long_double = strtod(work_str, &str_ptr);
	 pyfront.setinyield(dummy_long_double);
  }
 
  return_status = pyfront.check_all_parms();

  if (return_status == return_err_mat_date_bad)
  {
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_maturity_date,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_val_date_bad)
  {
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_value_date,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_iss_date_bad)
  {
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_issue_date,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_penult_date_bad)
  {

	pyfront.errtext(return_status, date_msg);

	::MessageBox(NULL,date_msg,language_next_to_last_pay_date,MB_OK);

	goto func_end;

  }

  if (return_status == return_info_max_mat_exc)
  {
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_val_gt_mat)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		goto func_end;

  }


  if (return_status == return_err_iss_gt_val)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }


  if (return_status == return_err_iss_gt_mat)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_iss_gt_penult)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_penult_ge_mat)
  {
  		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_iss_ge_first)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }
  if (return_status == return_err_first_gt_mat)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_dates_out_synch)
  {
  /*{ Dates are not in synch. }*/
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_compare_dates,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_non_zero_disc)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_interest_rate,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_neg_int)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_interest_rate,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_int_too_high)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_interest_rate,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_yield_meth_inv)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_yield_method,MB_OK);

		return_status = return_error;

		goto func_end;

  }

  if (return_status == return_err_calc_what_inv)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_yield_price_choice,MB_OK);

		goto func_end;

  }

  if (return_status == return_err_price_le_zero)
  {
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_price_check,MB_OK);

		goto func_end;

  }



  if (return_status)
  {

		itoa((int)return_status,work_str,10);
		pyfront.errtext(return_status, date_msg);

		::MessageBox(NULL,date_msg,language_default_dates_application_error,MB_OK);

		goto func_end;

  }
  /*{ Clear the dynamic fields before calculating.}*/

  return_status = pyfront.getclassnumber(&class_number);

  if (class_number != instr_cashflow_class)
  {

	previous_coup.SetWindowText("                  ");
	next_coup.SetWindowText("                  ");
	int_days.SetWindowText("                  ");
	accrued_interest.SetWindowText("                  ");
	dirty_price.SetWindowText("                  ");

	InitDateHold(date_hold,sizeof(date_hold));

	return_status = pyfront.getprevcoup(date_hold);
	previous_coup.SetWindowText(date_hold);

	InitDateHold(date_hold,sizeof(date_hold));

	return_status = pyfront.getnextcoup(date_hold);
	next_coup.SetWindowText(date_hold);
  }
  duration.SetWindowText("                  ");
  mod_duration.SetWindowText("                  ");
  convexity.SetWindowText("                  ");
  pvbp.SetWindowText("                  ");

  return_status = pyfront.getclassnumber(&class_number);

  if (class_number != instr_cashflow_class)
  {
	return_status = pyfront.calc_int();

	if (return_status)
	{
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_error,MB_OK);

	  goto func_end;
	}

	return_status = pyfront.getintdays(&interest_days_parm);

	ltoa(interest_days_parm,work_str,10);

	int_days.SetWindowText(work_str);

	return_status = pyfront.getinterest(&interest_parm);

	interest_double = (double)interest_parm * 100;

	gcvt(interest_double, price_places, work_str);

	accrued_interest.SetWindowText(work_str);

  }

  return_status = pyfront.getcalcwhat(&current_calc_what);

  if (current_calc_what == py_yield_from_price_calc_what)

  {

	return_status = pyfront.getinprice(&dummy_long_double);

	return_status = pyfront.getnomadj(&nominal_adj_parm);

	dirt_price = ((dummy_long_double * nominal_adj_parm) + interest_double);

	return_status = pyfront.getclassnumber(&class_number);

	if (class_number != instr_cashflow_class)
	{

	  interest_double = (double) dirt_price;

	  gcvt(interest_double, price_places, work_str);

	  dirty_price.SetWindowText(work_str);
	}

  }

  return_status = pyfront.getinprice(&dummy_long_double);

  dummy_long_double = dummy_long_double /100;

  return_status = pyfront.setinprice(dummy_long_double);

  dirt_price = dirt_price/100;

  pyfront.getinyield(&dummy_long_double);

  dummy_long_double = dummy_long_double/100;

  pyfront.setinyield(dummy_long_double);

  return_status = pyfront.calc_py();

  if (return_status == return_err_max_coups)
  {
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_yield_price_choice,MB_OK);

	  goto func_end;

  }

  if (return_status == return_err_max_iter)
  {
	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_yield_price_choice,MB_OK);

	  goto func_end;

  }

  if (return_status)
  {

	  pyfront.errtext(return_status, date_msg);

	  ::MessageBox(NULL,date_msg,language_error,MB_OK);

	  goto func_end;

  }

  return_status = pyfront.getcalcwhat(&current_calc_what);

  if (current_calc_what == py_yield_from_price_calc_what)
  {

	  return_status = pyfront.getoutyield(&dummy_long_double);

	  interest_double = (double)dummy_long_double * 100;

	  gcvt(interest_double, price_places, work_str);

	  yield_discount.SetWindowText(work_str);

  }
  else
  {

	  return_status = pyfront.getoutprice(&dummy_long_double);

	  interest_double = ((double) dummy_long_double) * 100;

	  gcvt(interest_double, price_places, work_str);

	  clean_price.SetWindowText(work_str);

	  return_status = pyfront.getclassnumber(&class_number);

	  if (class_number != instr_cashflow_class)
	  {

		 return_status = pyfront.getinterest(&interest_parm);

		 interest_double = (double)interest_parm * 100;

		 gcvt(interest_double, price_places, work_str);

		 accrued_interest.SetWindowText(work_str);

		 return_status = pyfront.getoutprice(&dummy_long_double);

		 return_status = pyfront.getnomadj(&nominal_adj_parm);

		 dirt_price = ((dummy_long_double * nominal_adj_parm) + interest_parm) * 100;

		 interest_double = (double) dirt_price;

		 gcvt(interest_double, price_places, work_str);

		 dirty_price.SetWindowText(work_str);
	  }
	}

	return_status = pyfront.getduration(&dummy_long_double);
	gcvt(dummy_long_double, price_places, work_str);
	duration.SetWindowText(work_str);

	return_status = pyfront.getmodduration(&dummy_long_double);
	gcvt(dummy_long_double, price_places, work_str);
	mod_duration.SetWindowText(work_str);

	return_status = pyfront.getconvexity(&dummy_long_double);
	gcvt(dummy_long_double, price_places, work_str);
	convexity.SetWindowText(work_str);

	return_status = pyfront.getpvbp(&dummy_long_double);
	gcvt(dummy_long_double * 100, price_places, work_str);
	pvbp.SetWindowText(work_str);


func_end:

return;

}
 
