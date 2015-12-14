//	#define _YOURCLASS _export

//
#if defined (BUILDING_YOUR_DLL)
	#define _EX_IN_CLASS __export
	#define _EX_IN_FUNC //_export
	#define _FAR_CLASS  //FAR
	#define _FAR_FUNC   //FAR
	#define _EXTERN  extern
#elif defined(USING_YOUR_DLL)
	#define _EX_IN_CLASS __import
	#define _EX_IN_FUNC 
	#define _FAR_CLASS
	#define _FAR_FUNC
	#define _EXTERN
#else
	#define _EX_IN_CLASS
	#define _EX_IN_FUNC
	#define _FAR_CLASS
	#define _FAR_FUNC
	#define _EXTERN
#endif
//
#ifndef __pyfront_H
#define __pyfront_H
#include "pydecs.h"
#include "errdecs.h"
#include "holicodeproc.h"


const char change_new = 0;
const char change_step = 1;

const	char	py_action_start	= 0;
/*{py_action_start indicates the start of processing.}*/

const	char	py_action_init_screen	= 1;
/*{py_action_init_screen indicates the initiation of the screen.}*/

const	char	py_action_ver_all	= 2;
/*{py_action_ver_all indicates all the input should be verified.}*/

const	char	py_instr_class_init	= 3;
/*{py_instr_class_init indicates the instrument class choices
should be set up.}*/

const	char	py_day_count_init	= 4;
/*{py_day_count_init indicates the day count choices
should be set up.}*/

const	char	py_freq_count_init	= 5;
/*{py_freq_count_init indicates the frequency count choices
should be set up.}*/

const	char	py_yield_meth_init	= 6;
/*{py_yield_meth_init indicates the yield method choices
should be set up.}*/

const	char	py_yield_days_init	= 7;
/*{py_yield_days_init indicates the yield days choices
should be set up.}*/

const	char	py_set_current	= 8;
/*{py_set_current indicates the current fields should be
set based on the instrument class.}*/

const	char	py_proc_pay_freq = 9;
/*{py_proc_pay_freq indicates the pay frequency should be
processed.}*/

const	char	py_proc_day_count = 10;
/*{py_proc_day_count indicates the day count should be
processed.}*/

const	char	py_proc_yield_days = 11;
/*{py_proc_day_count indicates the yield days should be
processed.}*/

const	char	py_proc_class_desc = 12;
/*{py_proc_class_desc indicates the instrument class description
should be processed.}*/

const	char	py_proc_mat_date = 13;
/*{py_proc_mat_date indicates the maturity date
should be processed.}*/

const	char	py_proc_val_date = 14;
/*{py_proc_val_date indicates the value date
should be processed.}*/

const	char	py_check_date = 15;
/*{py_check_date indicates the passed date
should be checked.}*/

const	char	py_proc_def_dates = 16;
/*{py_proc_def_dates indicates default dates
should be processed.}*/

const	char	py_proc_iss_date = 17;
/*{py_proc_iss_date indicates issue date
should be processed.}*/

const	char	py_check_val_vs_mat = 18;
/*{py_check_val_vs_mat indicates value date
should be checked against maturity date.}*/

const	char	py_check_tenor = 19;
/*{py_check_tenor indicates the tenor of the
instrument should be checked.}*/

const	char	py_check_all_parms = 20;
/*{py_check_all_parms indicates parameters
for the calculation should be checked.}*/

const	char	py_proc_penult_date = 21;
/*{py_proc_indicate_date indicates the
penultimate pay date should be processed.}*/

const	char	py_proc_first_date = 22;
/*{py_proc_first_date indicates the
first pay date should be processed.}*/

const	char	py_proc_all_dates = 23;
/*{py_proc_all_dates indicates that all
dates should be processed.}*/

const	char	py_check_iss_vs_mat = 24;
/*{py_check_iss_vs_mat indicates issue date
should be checked against maturity date.}*/

const	char	py_check_iss_vs_val = 25;
/*{py_check_iss_vs_val indicates issue date
should be checked against value date.}*/

const	char	py_check_iss_vs_first = 26;
/*{py_check_iss_vs_first indicates issue date
should be checked against first pay date.}*/

const	char	py_check_first_vs_mat = 27;
/*{py_check_first_vs_mat indicates first pay date
should be checked against maturity date.}*/

const	char	py_check_iss_vs_penult = 28;
/*{py_check_iss_vs_penult indicates issue date
should be checked against penultimate pay date.}*/

const	char	py_check_penult_vs_mat = 29;
/*{py_check_penult_vs_mat indicates penultimate
pay date should be checked against maturity date.}*/

const	char	py_check_date_synch = 30;
/*{py_check_date_synch indicates instrument dates
should be checked for synchronization.}*/

const	char	py_proc_int = 31;
/*{py_proc_int indicates interest rate should be processed.}*/

const	char	py_check_int_vs_instr = 32;
/*{py_check_int_vs_instr means check interest rate against instrument.}*/

const	char	py_proc_yield_meth = 33;
/*{py_proc_yield_meth indicates the yield method should be
processed.}*/

const	char	py_proc_calc_what = 34;
/*{py_proc_calc_what indicates the calculation choice should
be processeed.}*/

const	char	py_proc_price = 35;
/*{py_proc_price indicates the price should be processeed.}*/

const	char	py_check_price_vs_calc = 36;
/*{py_check_price_vs_calc indicates the price should e checked
against the calculation choice.}*/

const	char	py_calc_np = 37;
/*{py_calc_np means calculate next and previous coupons.}*/

const	char	py_prepay_type_init	= 38;
/*{py_prepay_type_init indicates the prepayment type choices
should be set up.}*/

const	char	py_proc_service = 39;
/*{py_proc_service indicates service fee should be processed.}*/

const	char	py_proc_prepay_type = 40;
/*{py_proc_prepay_type indicates prepayment type should be processed.}*/

const	char	py_proc_prepay_rate = 41;
/*{py_proc_prepay_rate indicates prepayment rate should be processed.}*/

const	char	py_proc_lag = 42;
/*{py_proc_lag indicates lag should be processed.}*/

const	char	py_set_accrue_date = 43;
/*{py_set_accrue_date indicates accrue date should be processed.}*/

const	char	py_calc_int = 44;
/*{py_calc_int indicates accrued_interest should be calculated.}*/

const	char	py_calc_py = 45;
/*{py_calc_py indicates price or yield should be calculated.}*/

const	char	py_yield_freq_init	= 46;
/*{py_yield_days_init indicates the yield frequency choices
should be set up.}*/

const	char	py_proc_yield_freq = 48;
/*{py_proc_yield_freq indicates the yield frequency should be
processed.}*/

const	char	py_proc_int1 = 49;
/*{py_proc_int1 indicates first interest rate should be processed.}*/

const	char	py_proc_int2 = 50;
/*{py_proc_int2 indicates second interest rate should be processed.}*/

const	char	py_calc_int1 = 51;
/*{py_calc_int1 indicates first interest should be calculated.}*/

const	char	py_calc_int2 = 52;
/*{py_calc_int2 indicates second interest should be calculated.}*/

const	char	py_init_frn = 53;
/*{py_init_frn indicates frn screen should be initialized.}*/

const	char	py_freq_count_init_frn	= 54;
/*{py_freq_count_init_frn indicates the frn_frequency count choices
should be set up.}*/

const	char	py_set_current_frn	= 55;
/*{py_set_current_frn indicates the current FRN fields should be
set.}*/

const	char	py_holiday_adj_count_init_frn	= 56;
/*{py_holiday_adj_count_init_frn indicates the FRN holiday adjustment
choices should be set up. */

const	char	py_simp_comp_init_frn	= 57;
/*{py_simp_comp_init_frn indicates the FRN Simple/Compound
choices should be set up. */

const	char	py_proc_gen_dates_frn	= 58;
/*{py_proc_gen_dates_frn indicates the FRN date generation
should be processed. */

const	char	py_proc_first_date_frn = 59;
/*{py_proc_first_date_frn indicates the
first rate date should be processed.}*/

const	char	py_check_val_vs_first_date_frn = 60;
/*{py_check_val_vs_first_date_frn indicates the
first rate date should be checked against the value date.}*/

const	char	py_proc_pay_freq_frn = 61;
/*{py_proc_pay_freq_frn indicates the rate frequency should be
processed.}*/

const	char	py_proc_holi = 62;
/*{py_proc_holi indicates the holiday adjust should be
processed.}*/

const	char	fra_proc_deal_date = 63;
/*{fra_proc_deal_date indicates the deal date should be
processed.}*/

const	char	fra_proc_val_from_deal = 64;
/*{fra_proc_val_from_deal indicates the val date should be
calculated from deal.}*/

const	char	fra_proc_sett_date = 65;
/*{fra_proc_sett_date indicates the settlement date
should be processed.}*/

const	char	py_check_sett_vs_mat = 66;
/*{py_check_sett_vs_mat indicates settlement pay date
should be checked against maturity date.}*/

const	char	fra_proc_sett_from_val = 67;
/*{fra_proc_sett_from_val indicates the settlement date should be
calculated from the value date.}*/

const	char	fra_proc_mat_from_sett = 68;
/*{fra_proc_mat_from_sett indicates the maturity date should be
calculated from the settlement date.}*/

const	char	fra_proc_fix_from_sett = 69;
/*{fra_proc_fix_from_sett indicates the fixing date should be
calculated from the settlement date.}*/

const	char	py_rate_source_init = 70;
/*{py_rate_source_init indicates rate source array choices is initialized.}*/

const	char	py_proc_rate_source = 71;
/*{py_proc_rate_source indicates rate source choices is processed.}*/

const	char	fra_fraterm_check = 72;
/*{fra_fraterm_check indicates the fra terms should be checked.}*/

const	char	py_gen_rates = 73;
/*{py_gen_rates indicates rates should be generated.}*/

const	char	fra_get_single_fra = 74;
/*{fra_get_single_fra indicates a single FRA should be determined.}*/

const	char	fra_currency_init = 75;
/*{fra_currency_init indicates the currency choice should be initialized.}*/

const	char	fra_holiday_init = 76;
/*{fra_holiday_init indicates the holiday choice should be initialized.}*/

const	char	fra_interpolation_init = 77;
/*{fra_interpolation_init indicates the interpolation choice should be initialized.}*/

const	char	fra_proc_holiday = 78;
/*{fra_proc_holiday indicates the holiday choice should be processed.}*/

const	char	fra_proc_interpolation = 79;
/*{fra_proc_interpolation indicates the interpolation choice should be processed.}*/

const	char	fra_proc_bid_ask = 80;
/*{fra_proc_bid_ask indicates the bid_ask choice should be processed.}*/

const	char	fra_bid_ask_init = 81;
/*{fra_bid_ask_init indicates the bid_ask choice should be initialized.}*/

const	char	py_proc_simp_comp_frn = 82;
/*{py_proc_simp_comp_frn indicates the simple/compound indicator should be
processed.}*/

const	char	py_proc_cashflow = 83;
/*{py_proc_cashflow indicates the cashflow should be processed.}*/

const	char	py_action_init_mbs	= 84;
/*{py_action_init_mbs indicates the initiation of the MBS screen.}*/

const	char	py_action_proc_mbs	= 85;
/*{py_action_proc_mbs indicates processing the MBS fields.}*/

const	char	py_action_init_monthend	= 86;
/*{py_action_init_monthend indicates the initiation of the monthend choices.}*/

const	char	py_action_proc_monthend	= 87;
/*{py_action_proc_monthend indicates processing the monthend fields.}*/

const	char	py_action_init_excoup	= 88;
/*{py_action_init_excoup indicates the initiation of the excoup choices.}*/

const	char	py_action_proc_excoup	= 89;
/*{py_action_proc_excoup indicates processing the excoup fields.}*/

const	char	py_action_init_cf	= 90;
/*{py_action_init_cf indicates initiation of cashflow processing.}*/

const	char	py_action_proc_part_pay	= 91;
/*{py_action_proc_part_pay indicates processing the partial payment fields.}*/

const	char	py_action_init_part_pay	= 92;
/*{py_action_init_part_pay indicates initiation of partial payments.}*/

const	char	py_action_init_sink_fund_mat	= 93;
/*{py_action_init_sink_fund_mat indicates initiation of sinking fund maturity rules.}*/

const	char	py_action_proc_sink_fund_mat	= 94;
/*{py_action_proc_sink_fund_mat indicates processing of sinking fund maturity rules.}*/

const	char	py_action_proc_sink_fund_dates	= 95;
/*{py_action_proc_sink_fund_dates indicates processing of sinking fund dates.}*/

const	char	proc_holiday	= 96;
/*{proc_holiday indicates processing of the holiday.}*/

const	char	py_action_end	= 99;
/*{py_action_end indicates the end of processing.}*/

const	long double py_max_int = 1000;
/*{py_max_int is the maximum interest rate.}*/

const	char	py_max_cashflow	= max_cashflow;
/*{py_max_cashflow indicates the maximum number of cash flows.}*/

const	int	date_str_size	= 11;
const	int	excoup_name_length = excoup_names_len;

class CALC_API _EX_IN_CLASS _FAR_CLASS Py_Front 
:public Py_Funcs, public cholicodeproc 
//, virtual public holidays_class
//,virtual public Instrument, 
//,virtual public Int_Calcs 
	{

public:
Py_Front();
//Py_Front(CDB * DB_parm);


unsigned long _FAR_FUNC  _EX_IN_FUNC   proc_def_dates	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_calc_what	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   init_screen	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_pay_freq	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_monthend	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_excoup	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_class_desc	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_day_count	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_yield_meth	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_yield_days	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_yield_freq	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   check_all_parms	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   calc_int	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   calc_py	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_simp_comp_frn	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_pay_freq_frn	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_holi	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_gen_dates_frn	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   init_frn	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   init_mbs	();
unsigned long  _FAR_FUNC _EX_IN_FUNC   proc_mbs	();

unsigned long  _FAR_FUNC _EX_IN_FUNC   setmatdate(	char mat_date_str[date_str_size]);
unsigned long   _FAR_FUNC _EX_IN_FUNC  setmatdate(Date_Funcs::date_union &date);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getmatdate(Date_Funcs::date_union &date);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setvaldate(	char val_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setvaldate(Date_Funcs::date_union &date);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getvaldate(Date_Funcs::date_union &date);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpenultdate(	char penult_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setpenultdate(Date_Funcs::date_union &date);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setpenultdate(	char penult_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setissuedate(Date_Funcs::date_union &date);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setissuedate(	char issue_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getissuedate(	char issue_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getfirstdate(	char first_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setfirstdate(Date_Funcs::date_union &date);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setfirstdate(	char first_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getexcoup (char excoup_name_str[excoup_name_length]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setexcoup (char excoup_name_str[excoup_name_length]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getexcoupchoice(int element_count, char excoup_name_str[excoup_name_length]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getcalcwhat(char *current_calc_what);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setcalcwhat(char current_calc_what);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setintrate(long double intrateparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getintrate(long double *intrateparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setinprice(long double inpriceparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getinprice(long double *inpriceparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setinyield(long double inyieldparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getinyield(long double *inyieldparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setoutprice(long double outpriceparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getoutprice(long double *outpriceparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setoutyield(long double outyieldparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getoutyield(long double *outyieldparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setprepay(char prepaytypeparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getprepay(char *prepaytypeparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getprepay(int prepay_number, char prepayparm [prepay_type_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getprepayname( char prepayparm [prepay_type_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setprepay(	char prepayparm [prepay_type_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setcprrate(long double cprrateparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getcprrate(long double *cprrateparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setcurrentfactor(long double currentfactorparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getcurrentfactor(long double *currentfactorparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setservicefee(long double servicefeeparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getservicefee(long double *servicefeeparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setlag(long double lagparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getlag(long double *lagparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setclassdesc(int class_number,
	char classdescparm [instr_class_desc_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setclassdesc(char classdescparm [instr_class_desc_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getclassdesc(char classdescparm [instr_class_desc_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getclassdesc(int class_number,
	char classdescparm [instr_class_desc_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setclassnumber(char classnumberparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getclassnumber(char *classnumberparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setdaycount(int daycount_number,
	char daycountparm [day_count_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getdaycount(int daycount_number,
	char daycountparm [day_count_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setdaycount(	char daycountparm [day_count_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getdaycount(	char daycountparm [day_count_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getdaycount(int *daycount_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setdaycount(int daycount_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setpayfreq(int payfreq_number,
	char payfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpayfreq(int payfreq_number,
	char payfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpayfreq(char payfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setpayfreq(int payfreq_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setpayfreq(	char payfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpayfreq(int *payfreq_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpayfreqlength(int *payfreq_length);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpayfreqperiod(int *payfreq_period);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpayfreqlengthyield(int *payfreq_length);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpayfreqperiodyield(int *payfreq_period);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setmonthend(int monthend_number,
	char monthendparm [monthend_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getmonthend(int monthend_number,
	char monthendparm [monthend_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getmonthend(char monthendparm [monthend_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setmonthend(	char monthendparm [monthend_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyieldmeth(int yieldmeth_number,
	char yieldmethparm [yield_names_len]);
typedef struct _HOLIDAY
{
	int year;
	int month;
	int day;
} HOLIDAY;

unsigned long _FAR_FUNC _EX_IN_FUNC		setHolidays(HOLIDAY* pHolidayArray, int size);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyieldmeth(char yieldmethparm [yield_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyieldmeth(int yieldmeth_number,
	char yieldmethparm [yield_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyieldmeth(char yieldmethparm [yield_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyieldmeth(int yieldmeth_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyieldmeth(int *yieldmeth_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyielddays(int yielddays_number,
	char yielddaysparm [day_count_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyielddays(int yielddays_number,
	char yielddaysparm [day_count_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyielddays(char yielddaysparm [day_count_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyielddays(int yielddays_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyielddays(char yielddaysparm [day_count_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyielddays(int *yielddays_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyieldfreq(int yieldfreq_number,
	char yieldfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyieldfreq(char yieldfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyieldfreq(int yieldfreq_number,
	char yieldfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyieldfreq(char yieldfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setyieldfreq(int yieldfreq_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getyieldfreq(int *yieldfreq_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setmonthend(int monthend_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getmonthend(int *monthend_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setexcoupdays(int excoupdays);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getexcoupdays(int *excoupdays);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getprevcoup(	char prev_coup_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getnextcoup(	char next_coup_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getintdays(long *intdaysparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getinterest(long double *interestparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getnomadj(long double *nomadjparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getduration(long double *durationparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getmodduration(long double *moddurationparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getconvexity(long double *convexityparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpvbp(long double *pvbpparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getsinkcount(char *sinkcountparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setsinkcount(char sinkcountparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getsinkdate(int sink_number, char sink_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setsinkdate(int sink_number, char sink_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getsinkpay(int sink_number, long double *sink_pay);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setsinkpay(int sink_number, long double sink_pay);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getsinkmatchoice(int element_count,
	char sink_mat_str[redemp_sched_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getsinkmat (char sink_mat_str[redemp_sched_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setsinkmat (char sink_mat_str[redemp_sched_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpartpaycount(char *partpaycountparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setpartpaycount(char partpaycountparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpartpaydate(int partpay_number, char partpay_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setpartpaydate(int partpay_number, char partpay_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getpartpaypay(int partpay_number, long double *partpay_pay);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setpartpaypay(int partpay_number, long double partpay_pay);
void errtext(unsigned long errnum, char error_text [error_text_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setsimpcomp (char simp_comp_str[simp_comp_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setreratecount(char reratecountparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getreratecount(char *reratecountparm);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getfrnrate(int frn_number, long double *frnrate);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setfrnrate(int frn_number, long double frnrate);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setfrnpayfreq(	char frnpayfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getfrnpayfreq(	char frnpayfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getfrnpayfreq(	int *frnpayfreq_number );
unsigned long  _FAR_FUNC _EX_IN_FUNC   getreratedate(int frn_number, char frn_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setreratedate(int frn_number, char frn_date_str[date_str_size]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getholidaytotal(int *holiday_number);
//unsigned long  _FAR_FUNC _EX_IN_FUNC   getholiday(int holiday_number, char holiday_str[fra_holiday_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setholiday(int holiday_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getholiday(int *holiday_number);
//unsigned long  _FAR_FUNC _EX_IN_FUNC   setholiday(char holiday_str[fra_holiday_names_len]);
//unsigned long  _FAR_FUNC _EX_IN_FUNC   getholiday(char holiday_str[fra_holiday_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setholidayadj(	char holidayparm [holiday_adj_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getholidayadj(	char holidayparm [holiday_adj_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getholidayadj(int holadj_number, char holidayparm [holiday_adj_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   setholidayadj(	int holadj_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getholidayadj(int *holadj_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getfrnpayfreq(int payfreq_number,	char payfreqparm [freq_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getsimpcomp(int simpcomp_number,	char simpcompparm [simp_comp_names_len]);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getsimpcomp(int *simpcomp_number);
unsigned long  _FAR_FUNC _EX_IN_FUNC   getsimpcomp(char simpcompparm [simp_comp_names_len]);
//unsigned long  _FAR_FUNC _EX_IN_FUNC   getcprrate(int *cprrate);

static Py_Front& getInstance()
{
	static Py_Front instance; // Guaranteed to be destroyed.
						  // Instantiated on first use.
	return instance;
}


typedef struct py_rate_parm
{
	event_sched rerate_sched;
	char pay_type;
	char current_pay_freq;
	char pay_freq_choice[freq_count][freq_names_len];
	char current_pay_freq_name[freq_names_len];
	char holiday_adj_choice[holiday_adj_count][holiday_adj_names_len];
	char current_holiday_adj;
	char current_holiday_adj_name[holiday_adj_names_len];
	char simp_comp_choice[simp_comp_count][simp_comp_names_len];
	char current_simp_comp;
	char current_simp_comp_name[simp_comp_names_len];
	unsigned int holi_chan;
}
py_rate_parm;



unsigned long action_init_cf();
unsigned long action_init_mbs();
unsigned long init_fra_holiday();
unsigned long action_init_part_pay();
unsigned long action_proc_part_pay();
unsigned long action_init_excoup();
unsigned long action_sink_fund_mat();
unsigned long action_proc_monthend();
unsigned long proc_sink_fund_mat();
unsigned long action_proc_excoup();
unsigned long action_init_frn();
unsigned long set_rerate();
unsigned long instr_class_init();
unsigned long freq_count_init_frn();
unsigned long simp_comp_init_frn();
unsigned long yield_meth_init();
unsigned long set_current();
unsigned long set_current_frn();
unsigned long proc_pay_freq_frn_py();
unsigned long proc_simp_comp_frn_py();
unsigned long proc_holi_py();
unsigned long proc_pay_freq_py();
unsigned long proc_yield_freq_py();
unsigned long proc_day_count_py();
unsigned long proc_yield_meth_py();
unsigned long proc_yield_days_py();
unsigned long proc_class_desc_py();
unsigned long proc_mat_date_py();
unsigned long proc_iss_date_py();
unsigned long proc_val_date_py();
unsigned long check_val_vs_mat_py();
unsigned long check_val_vs_first_date_frn();
unsigned long check_iss_vs_mat();
unsigned long check_iss_vs_first();
unsigned long check_first_vs_mat();
unsigned long check_iss_vs_penult();
unsigned long check_iss_vs_val();
unsigned long check_penult_vs_mat();
unsigned long set_accrue_date_py();
unsigned long check_tenor_py();
unsigned long proc_def_dates_py();
unsigned long calc_np_py();
unsigned long proc_gen_dates_frn_py();
unsigned long check_date_synch_py();
unsigned long proc_penult_date_py();
unsigned long proc_first_date_py(); 
unsigned long proc_first_date_frn_py();
unsigned long proc_all_dates_py();
unsigned long proc_int_py();
unsigned long proc_price_py();
unsigned long check_price_vs_calc_py();
unsigned long py_proc_calc_what_py();
unsigned long check_all_parms_py();
unsigned long prepay_type_init_py();
unsigned long proc_service_py();
unsigned long proc_prepay_type_py();
unsigned long proc_prepay_rate_py();
unsigned long proc_lag_py();
unsigned long proc_cashflow_py();
unsigned long calc_int_py();
unsigned long calc_py_py();
unsigned long freq_count_init_py();
unsigned long action_init_screen_py();
unsigned long action_proc_mbs_py();
unsigned long pyproc45(
//	char action,
//	instr *instr_parm,
//	py_parms *py_parm,
//	char instr_class_desc_choice [instr_last_class] [instr_class_desc_len],
//	char *current_class,
//	char current_class_desc [instr_class_desc_len],
//	char day_count_choice [date_last_day_count] [day_count_names_len],
//	char *current_day_count,
//	char current_day_count_name [day_count_names_len],
//	char pay_freq_choice [freq_count] [freq_names_len],
//	char *current_pay_freq,
//	char current_pay_freq_name [freq_names_len],
//	char yield_meth_choice [py_last_yield_meth] [yield_names_len],
//	char *current_yield_meth,
//	char current_yield_meth_name [yield_names_len],
//	char yield_days_choice [date_last_day_count] [day_count_names_len],
//	char *current_yield_days,
//	char current_yield_days_name [day_count_names_len],
//	char yield_freq_choice [freq_count] [freq_names_len],
//	char *current_yield_freq ,
//	char current_yield_freq_name [freq_names_len],
//	char *current_ex_coup_days,
//	char holidays_code [holiday_code_length],
//	holidays_struct holi_parm [],
//	char prepay_type_name [prepay_type_names_len],
//	char prepay_type_choice [py_last_prepay_type] [prepay_type_names_len],
//	redemps_struc redemps_array_parm[],
//	insevent_struct [],
//	py_rate_parm *rerate_sched,
//	pyproc_parm *extra_parms
	);
/*
unsigned long  pyproc	(
	char action,
	instr *instr_parm,
	py_parms *py_parm,
	char instr_class_desc_choice [instr_last_class] [instr_class_desc_len],
	char *current_class,
	char current_class_desc [instr_class_desc_len],
	char day_count_choice [date_last_day_count] [day_count_names_len],
	char *current_day_count,
	char current_day_count_name [day_count_names_len],
	char pay_freq_choice [freq_count] [freq_names_len],
	char *current_pay_freq,
	char current_pay_freq_name [freq_names_len],
	char yield_meth_choice [py_last_yield_meth] [yield_names_len],
	char *current_yield_meth,
	char current_yield_meth_name [yield_names_len],
	char yield_days_choice [date_last_day_count] [day_count_names_len],
	char *current_yield_days,
	char current_yield_days_name [day_count_names_len],
	char yield_freq_choice [freq_count] [freq_names_len],
	char *current_yield_freq ,
	char current_yield_freq_name [freq_names_len],
	char *current_ex_coup_days,
	char holidays_code [holiday_code_length],
	long double *int_rate,
	long double *in_price,
	long double *in_yield,
	long double *out_price,
	long double *out_yield,
	holidays_struct holi_parm [],
	char *calc_what,
	char *prepay_type,
	long double *cpr_rate,
	long double *current_factor,
	long double *service_fee,
	long double *lag,
	  date_union *mat_date,
	  date_union *val_date_parm,
	  date_union *penult_date,
	  date_union *issue_date,
	  date_union *first_date,
	  date_union *prev_coup,
	  date_union *next_coup,
	char prepay_type_name [prepay_type_names_len],
	char prepay_type_choice [py_last_prepay_type] [prepay_type_names_len],
	long double *interest,
	long *interest_days,
	long double *nominal_adjust,
	long double *duration_hold,
	long double *modified_duration_hold,
	long double *conv,
	long double *pvbp_out,
	redemps_struc redemps_array_parm[],
	long double *first_int,
	insevent_struct [],
	py_rate_parm *rerate_sched,
	pyproc_parm *extra_parms
	);
*/

protected:

// instr in_instr;

private:

//CDB * DB_local;
//CDB::DB_Handles localhandles;

//char	scr_meth;
set<string> holiSet;


//   Date_Funcs Dates;
//   Instrument Instr;
//   Int_Calcs Interest;
//   Py_Funcs Py;
	char prepay_type_name [prepay_type_names_len];
	char prepay_type_choice [py_last_prepay_type] [prepay_type_names_len];
//	Instrument::insevent_struct rate_array[max_rates];
	  insevent_struct rate_array[max_rates];
//	char holiday_choice [fra_last_holiday] [fra_holiday_names_len];
	char current_holiday;
//	char current_holiday_name [fra_holiday_names_len];
//	char current_sink_fund_mat;
	char total_part_pays;
	long double  first_int;
	unsigned int holi_chan;
 char action;
 double work_double;
// boolean ex_coup;
 booleans ex_coup;
 date_union  mat_date;
 date_union  val_date;
 date_union  penult_date;
 date_union  issue_date;
 date_union  first_date;
 char current_excoup_name [excoup_names_len];
 char excoup_choice [excoup_count] [excoup_names_len];
 char  calc_what;
 long double  int_rate;
 unsigned long return_state;
 long double  in_price;
 long double  in_yield;
 long double  out_price;
 long double  out_yield;
 char  prepay_type;
 long double  cpr_rate;
 long double  current_factor;
 long double  service_fee;
 long double  lag;
 //char instr_class_desc_choice [instr_last_class] [instr_class_desc_len];
 char current_class;
 //char day_count_choice [date_last_day_count] [day_count_names_len];
 char pay_freq_choice [freq_count] [freq_names_len];
 //char monthend_choice [monthend_count] [monthend_names_len];
 char yield_meth_choice [py_last_yield_meth] [yield_names_len];
 //char yield_days_choice [date_last_day_count] [day_count_names_len];
 //char yield_freq_choice [freq_count] [freq_names_len];
 char current_day_count;
 char current_day_count_name [day_count_names_len];
 char current_pay_freq;
 char current_yield_meth;
 char current_yield_days;
 char current_yield_freq;
 char current_monthend;
 char current_ex_coup_days;
 char current_pay_freq_name [freq_names_len];
 char current_monthend_name [monthend_names_len];
 char current_class_desc [instr_class_desc_len];
 char current_yield_meth_name [yield_names_len];
 char current_yield_days_name [day_count_names_len];
 char current_yield_freq_name [freq_names_len];
 date_union  prev_coup;
 date_union  next_coup;
 long  interest_days;
 long double  interest;
 long double  nominal_adjust;
 long double  duration_hold;
 long double  modified_duration_hold;
 long double  conv;
 long double  pvbp_out;
 char sink_fund_count;
// Instrument::pay_struc	sink_fund_sched[max_sink_fund];
   pay_struc	sink_fund_sched[max_sink_fund];
 char sink_fund_mat_choice [py_last_redemp_sched] [redemp_sched_names_len];
 char current_sink_fund_mat_name [redemp_sched_names_len];
// Instrument::pay_struc	part_pays_sched[max_part_pays];
   pay_struc	part_pays_sched[max_part_pays];
 char current_excoup;
// char holidays_code [holiday_code_length];
// holidays_struct holi_parm [max_holidays]; //Must be changed.
 py_rate_parm rerate_sched;

 typedef struct 	actions		{
				char prev_action;
				char curr_action;
				char next_action;}
		actions;

actions	actions_array [4];
date_union date_union_hold;
date_union issue_date_hold;
date_union check_date1;
date_union dummy_date1;
date_union prev_date;
date_union next_date;
date_union val_date_loc;
date_union mat_date_loc;
date_union iss_date_loc;
date_union first_date_loc;
date_union penult_date_loc;
//Instrument::instr in_instr;
  instr in_instr;
py_parms pyparm;
//Instrument::redemps_struc redemps_array_parm[5];
  redemps_struc redemps_array_parm[5];
//Instrument::pay_struc  pay_array_a[max_coups];
  pay_struc  pay_array_a[max_coups];
//Instrument::redemps_struc part_pay_array_a[max_part_pays];
  redemps_struc part_pay_array_a[max_part_pays];
//Instrument::redemps_struc even_redemps[max_coups];
  redemps_struc even_redemps[max_coups];

typedef struct pyproc_parm
	{
//	char holiday_choice [fra_last_holiday] [fra_holiday_names_len];
//	char current_holiday;
//	char current_holiday_name [fra_holiday_names_len];
//	char sink_fund_mat_choice [py_last_redemp_sched] [redemp_sched_names_len];
//	char current_sink_fund_mat;
//	char current_sink_fund_mat_name [redemp_sched_names_len];
//	char monthend_choice [monthend_count] [monthend_names_len];
//	char current_monthend;
//	char current_monthend_name [monthend_names_len];
//	char excoup_choice [excoup_count] [excoup_names_len];
//	char current_excoup;
//	char total_part_pays;
//	char current_excoup_name [excoup_names_len];
//	long double  int_rate;
//	long double  in_price;
//	long double  in_yield;
//	long double  out_price;
//	long double  out_yield;
//	char  calc_what;
/*
	char  prepay_type;
	long double  cpr_rate;
	long double  current_factor;
	long double  service_fee;
	long double  lag;
	  date_union  mat_date;
	  date_union  val_date_parm;
	  date_union  penult_date;
	  date_union  issue_date;
	  date_union  first_date;
	  date_union  prev_coup;
	  date_union  next_coup;
	long double  interest;
	long  interest_days;
	long double  nominal_adjust;
	long double  duration_hold;
	long double  modified_duration_hold;
	long double  conv;
	long double  pvbp_out;
	long double  first_int;
	unsigned int holi_chan;
	pay_struc	sink_fund_sched[max_sink_fund];
	pay_struc	part_pays_sched[max_part_pays];
*/
	}
			 pyproc_parm;

void actions_proc(char change, int actions_index,
	actions actions_array[4], char new_action);

};
#endif
