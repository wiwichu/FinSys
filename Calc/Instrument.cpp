#include "stdafx.h"
#include "datedec.h"
#include "pydecs.h"
#include "insclass.h"
#include "instr.h"

_INSTRUMENT Instrument()
{
}
/*
_INSTRUMENT Instrument(CDB * DB_parm) : Inst_Event (DB_parm)
{
	DB_local = DB_parm;

//	DB_local->InitDB();

//	DB_local->GetStatementHandle(&localhandles);
}
*/
/*{classdef accepts an instrument record and returns the defaults for the
instrument class passed.

	Usage:  unsigned long	classdef(instr *in_instr)

	where:  in_instr =	Input/Output parameter of instr type which
				contains the defaults for the instrument
				class passed.

		return value =  of unsigned long type gives completion status.

    Called by:	<[]

}*/
	/*{ Global variables.}*/

	unsigned long  	_INSTRUMENT classdef(instr *in_instr)

{

#include "locals.h"
size_t		string_size = 0;

/*{ Set general defaults.}*/

in_instr->instr_code[0] = 0;
in_instr->prin_curr = 0;
in_instr->pay_curr = 0;
//in_instr->holiday_code[0] = 0;
//strcpy(in_instr->holiday_code,"xxx");
in_instr->rate_code[0] = 0;
in_instr->part_pays = 0;
in_instr->redemps = 0;
in_instr->part_pay_price_base = 1;
in_instr->rate_offset = 0;
in_instr->interm_cap = 0;
in_instr->interm_floor = 0;
in_instr->life_cap = 0;
in_instr->life_floor = 0;
in_instr->issue_price = 0;
in_instr->redemp_price = 0;

switch (in_instr->instr_class)
{
  case instr_ustbo_class:
  {

    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_ustbo_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_ustbo_class_desc,string_size);
    in_instr->day_count		= date_act_act_day_count;
    in_instr->cal_num		= date_act_cal;
    in_instr->cal_den 		= date_act_cal;
	 in_instr->pay_factor	= instr_no_pay_factor;
	 in_instr->pay_type		= instr_fixed_pay_type;
	 in_instr->pay_sched		= instr_str_pay_sched;
	 in_instr->comp_freq.period	= event_sched_free_period;
	 in_instr->pay_freq.period	= event_sched_month_period;
	 in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
	 in_instr->pay_freq.freq	= 6;
	 in_instr->ex_coup_days	= 0;
	 in_instr->neg_first		= instr_no_neg_first;
	 in_instr->yield_meth	= py_ustr_yield_meth;
	 in_instr->part_pays		= 0;
	 in_instr->redemps		= 0;
	 in_instr->issue_price	= 1;
    in_instr->redemp_price	= 1;

	 break;

  }
  case instr_usdsc_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_usdsc_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_usdsc_class_desc,string_size);
    in_instr->day_count		= date_act_360_day_count;
    in_instr->cal_num		= date_act_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 12;
    in_instr->ex_coup_days	= 0;
	 in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_mmdisc_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;
    in_instr->pay_freq.month_day = 0;
    break;
  }
  case instr_cp_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_usdsc_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_usdsc_class_desc,string_size);
    in_instr->day_count		= date_act_360_day_count;
    in_instr->cal_num		= date_act_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 12;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_mm_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;
    in_instr->pay_freq.month_day = 0;
    break;
  }
  case instr_ukdsc_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_ukdsc_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_ukdsc_class_desc,string_size);
    in_instr->day_count		= date_act_365_day_count;
    in_instr->cal_num		= date_act_cal;
    in_instr->cal_den 		= date_365_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_next_holiday_adj;
    in_instr->pay_freq.freq	= 12;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_mmdisc_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;
    in_instr->pay_freq.month_day = 0;

    break;
  }
  case instr_gilt_class:
  {
	 string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_gilt_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_gilt_class_desc,string_size);
	/*
    in_instr->day_count		= date_act_365_day_count;
    in_instr->cal_num		= date_act_cal;
    in_instr->cal_den 		= date_365_cal;
	*/
	in_instr->day_count = date_act_act_day_count;
	in_instr->cal_num = date_act_cal;
	in_instr->cal_den = date_act_cal;

    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 6;
    in_instr->ex_coup_days	= 37;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_gm_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;

    break;
  }
  case instr_goj_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_goj_class_name,string_size);
	 string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_goj_class_desc,string_size);
    in_instr->day_count		= date_act_365_day_count;
    in_instr->cal_num		= date_act_cal;
    in_instr->cal_den 		= date_365_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 6;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_simp_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;

    break;
  }

  case instr_euro_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_euro_class_name,string_size);
    string_size = instr_class_desc_len;
	 memcpy(&in_instr->class_desc,instr_euro_class_desc,string_size);
    in_instr->day_count		= date_30e_360_day_count;
    in_instr->cal_num		= date_30e_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 12;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_aibd_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;

    break;
  }
  case instr_cashflow_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_cashflow_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_cashflow_class_desc,string_size);
    in_instr->day_count		= date_30e_360_day_count;
	 in_instr->cal_num		= date_30e_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 12;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_ty_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;

    break;
  }


  case instr_uscd_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_uscd_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_uscd_class_desc,string_size);
    in_instr->day_count		= date_act_360_day_count;
	in_instr->cal_num		= date_act_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 6;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_mm_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;

    break;
  }

  case instr_ukcd_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_ukcd_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_ukcd_class_desc,string_size);
    in_instr->day_count		= date_act_365cd_day_count;
    in_instr->cal_num		= date_act_cal;
	 in_instr->cal_den 		= date_365_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 6;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_mm_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;

    break;
  }

  case instr_bund_class:
  {
	 string_size = instr_class_name_len;
	 memcpy(&in_instr->class_name,instr_bund_class_name,string_size);
	 string_size = instr_class_desc_len;
	 memcpy(&in_instr->class_desc,instr_bund_class_desc,string_size);
	 in_instr->day_count		= date_30_360german_day_count;
	 in_instr->cal_num		= date_30german_cal;
	 in_instr->cal_den 		= date_30_cal;
	 in_instr->pay_factor	= instr_no_pay_factor;
	 in_instr->pay_type		= instr_fixed_pay_type;
	 in_instr->pay_sched		= instr_str_pay_sched;
	 in_instr->comp_freq.period	= event_sched_free_period;
	 in_instr->pay_freq.period	= event_sched_month_period;
	 in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
	 in_instr->pay_freq.freq	= 12;
	 in_instr->ex_coup_days	= 0;
	 in_instr->neg_first		= instr_no_neg_first;
	 in_instr->yield_meth	= py_aibd_yield_meth;
	 in_instr->part_pays		= 0;
	 in_instr->redemps		= 0;
	 in_instr->issue_price	= 0;
	 in_instr->redemp_price	= 1;


	 break;
  }

  case instr_ssd_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_bund_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_bund_class_desc,string_size);
    in_instr->day_count		= date_30e_360_day_count;
    in_instr->cal_num		= date_30e_cal;
    in_instr->cal_den 		= date_30_cal;
	 in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 12;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_moos_yield_meth;
	 in_instr->part_pays		= 0;
	 in_instr->redemps		= 0;
	 in_instr->issue_price	= 0;
	 in_instr->redemp_price	= 1;


	 break;
  }
  case instr_uschatz_buba_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_bund_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_bund_class_desc,string_size);
    in_instr->day_count		= date_30_360german_day_count;
    in_instr->cal_num		= date_30german_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
	 in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 12;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_mm_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;


    break;
  }
  case instr_fschatz_class:
  case instr_uschatz_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_bund_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_bund_class_desc,string_size);
    in_instr->day_count		= date_30_360german_day_count;
    in_instr->cal_num		= date_30german_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
	 in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 12;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_mm_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;


    break;
  }

  case instr_mbs_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_mbs_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_mbs_class_desc,string_size);
    in_instr->day_count		= date_30_360_day_count;
    in_instr->cal_num		= date_30_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_yes_pay_factor;
	 in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 1;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_MBS_yield_meth;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;


    break;
  }

  case instr_float_class:
  {
    string_size = instr_class_name_len;
    memcpy(&in_instr->class_name,instr_float_class_name,string_size);
    string_size = instr_class_desc_len;
    memcpy(&in_instr->class_desc,instr_float_class_desc,string_size);
    in_instr->day_count		= date_act_360_day_count;
    in_instr->cal_num		= date_act_cal;
    in_instr->cal_den 		= date_30_cal;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_float_pay_type;
	 in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->pay_freq.freq	= 6;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
    in_instr->yield_meth	= py_mm_yield_meth;
    in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;

    break;
  }

  default:
  {

    in_instr->instr_class = instr_cust_class;
    in_instr->pay_factor	= instr_no_pay_factor;
    in_instr->pay_type		= instr_fixed_pay_type;
    in_instr->pay_sched		= instr_str_pay_sched;
    in_instr->comp_freq.period	= event_sched_free_period;
    in_instr->pay_freq.period	= event_sched_month_period;
    in_instr->pay_freq.holiday_adj = event_sched_same_holiday_adj;
    in_instr->ex_coup_days	= 0;
    in_instr->neg_first		= instr_no_neg_first;
	 in_instr->part_pays		= 0;
    in_instr->redemps		= 0;
    in_instr->issue_price	= 0;
    in_instr->redemp_price	= 1;
    in_instr->yield_meth	= py_ytm_comp_yield_meth;


    break;
  }
}




//func_end:

	return return_status;

}