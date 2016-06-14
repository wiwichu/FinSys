//#include <envir.h>
//#include datehead
//#include genhead
#include "stdafx.h"
#include "datedec.h"
//#include <pydecs.h>
#include "insclass.h"
//#include <intdecs.h>
#include "gendec.h"
//#include "iodec.h"
#include "scrdec.h"
#include <math.h>
#include "pyfront.h"
//#include iokeys
//#include holidays
/*
const char change_new = 0;
const char change_step = 1;



typedef struct 	actions		{
				char prev_action;
				char curr_action;
				char next_action;}
		actions;
*/
Py_Front::Py_Front()
{
	scr_meth = scr_meth_general;
}
/*
Py_Front::Py_Front(CDB * DB_parm) 
:Py_Funcs (DB_parm),
cholicodeproc (DB_parm)

//, holidays_class (DB_parm)
//,Instrument (DB_parm)
//,Int_Calcs (DB_parm) 

{
	DB_local = DB_parm;

//	DB_local->InitDB();

//	DB_local->GetStatementHandle(&localhandles);
	
}
*/
unsigned long FAR _export	Py_Front::pyproc45	(
//	char action,
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
//	char *current_yield_freq,
//	char current_yield_freq_name [freq_names_len],
//	char *current_ex_coup_days,
//	char holidays_code [holiday_code_length],
//	holidays_struct holi_parm [],
//	char prepay_type_name [prepay_type_names_len],
//	char prepay_type_choice [py_last_prepay_type] [prepay_type_names_len],
//	redemps_struc redemps_array_parm[],
//	insevent_struct rate_array [],
//	py_rate_parm *rerate_sched,
//	pyproc_parm *extra_parms
	)


{

#include "locals.h"
/*

	long double int_rate;
	long double in_price;
	long double in_yield;
	long double out_price;
	long double out_yield;
	char calc_what;
	char prepay_type;
	long double cpr_rate;
	long double current_factor;
	long double service_fee;
	long double lag;
	date_union mat_date_parm;
	date_union val_date_parm;
	date_union penult_date_parm;
	date_union issue_date_parm;
	date_union first_date_parm;
	date_union prev_coup_parm;
	date_union next_coup_parm;
	long double interest;
	long interest_days;
	long double nominal_adjust;
	long double duration_hold;
	long double modified_duration_hold;
	long double conv;
	long double pvbp_out;
	long double first_int;
	boolean ex_coup;

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
static instr in_instr;
static py_parms pyparm;
static	redemps_struc redemps_array_parm[5];
pay_struc  pay_array_a[max_coups];
redemps_struc part_pay_array_a[max_part_pays];
redemps_struc even_redemps[max_coups];

*/

char rule_spec = 0;
char loop_counter = 0;
//char class_desc [instr_last_class] [instr_class_desc_len];

int element_count = 0;
int actions_index = 0;

int str_cmp = 0;
int str_cmp2 = 0;
int bad_date_found = isfalse;

unsigned int dummy_ui = 0;
long tenor_days = 0;
long double	dummy_long_double = 0;
long double	work_long_double = 0;

size_t num_bytes = 0;

set<string> holiSet;


//	strcpy(module_name,"pyproc");


//	int_rate = extra_parms->int_rate;
//	in_price = extra_parms->in_price;
//	in_yield = extra_parms->in_yield;
//	out_price = extra_parms->out_price;
//	out_yield = extra_parms->out_yield;
//	calc_what = extra_parms->calc_what;
//	prepay_type = extra_parms->prepay_type;
//	cpr_rate = extra_parms->cpr_rate;
//	current_factor = extra_parms->current_factor;
//	service_fee = extra_parms->service_fee;
//	lag = extra_parms->lag;
//	 datecpy(mat_date_parm.date_string,extra_parms->mat_date.date_string);
//	 datecpy(val_date_parm.date_string,extra_parms->val_date_parm.date_string);
//	 datecpy(penult_date_parm.date_string,extra_parms->penult_date.date_string);
//	 datecpy(issue_date_parm.date_string,extra_parms->issue_date.date_string);
//	 datecpy(first_date_parm.date_string,extra_parms->first_date.date_string);
//	 datecpy(prev_coup_parm.date_string,extra_parms->prev_coup.date_string);
//	 datecpy(next_coup_parm.date_string,extra_parms->next_coup.date_string);
//	interest = extra_parms->interest;
//	interest_days = extra_parms->interest_days;
//	nominal_adjust = extra_parms->nominal_adjust;
//	duration_hold = extra_parms->duration_hold;
//	modified_duration_hold = extra_parms->modified_duration_hold;
//	conv = extra_parms->conv;
//	pvbp_out = extra_parms->pvbp_out;
//	first_int = extra_parms->first_int;

	return_state = return_success;
//	pyparm = *py_parm;
//	in_instr = *instr_parm;
//	 datecpy(val_date_loc.date_string,val_date.date_string);
//	 datecpy(mat_date_loc.date_string,mat_date.date_string);
//	 datecpy(iss_date_loc.date_string,issue_date.date_string);
//	 datecpy(first_date_loc.date_string,first_date.date_string);
//	 datecpy(penult_date_loc.date_string,penult_date.date_string);
	num_bytes = 3;
//	memmove(holidays_code,current_holiday_name,num_bytes);

	/* Process chosen action.*/

	actions_array[actions_index].prev_action = py_action_start;
	actions_array[actions_index].curr_action = action;
	actions_array[actions_index].next_action = py_action_end;

	while (actions_array[actions_index].curr_action != py_action_end)
	{
	  switch (actions_array[actions_index].curr_action)
	  {
		 case py_action_init_screen:
		 /*{Initialize the screen.}*/
		 {

					 /*{First do common setups.}*/

			if (actions_array[actions_index].prev_action
			== py_action_start)
			{

				actions_index ++;

				actions_proc(change_new, actions_index,
				actions_array, py_instr_class_init );

				break;

			}

			if (actions_array[actions_index].prev_action
			== py_instr_class_init)
			{


				actions_proc(change_new, actions_index,
				actions_array, py_day_count_init );

				break;

			}

			if (actions_array[actions_index].prev_action
				== py_day_count_init)
			{


				actions_proc(change_new, actions_index,
				actions_array, fra_holiday_init );

				break;

			}

			if (actions_array[actions_index].prev_action
			== fra_holiday_init)
			{


				actions_proc(change_new, actions_index,
				actions_array, py_freq_count_init );

				break;

			}

			if (actions_array[actions_index].prev_action
			== py_freq_count_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_yield_meth_init );

				break;

			}

			if (actions_array[actions_index].prev_action
			== py_yield_meth_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_yield_days_init );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_yield_days_init)
			{
//
				actions_proc(change_new, actions_index,
				actions_array, py_action_init_part_pay );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_action_init_part_pay)
			{
				actions_proc(change_new, actions_index,
				actions_array, py_action_init_monthend );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_action_init_monthend)
			{
//
				actions_proc(change_new, actions_index,
				actions_array, py_action_init_excoup );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_action_init_excoup)
			{
				actions_proc(change_new, actions_index,
				actions_array, py_yield_freq_init );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_yield_freq_init)
			{
				actions_proc(change_new, actions_index,
				actions_array, py_action_init_sink_fund_mat );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_action_init_sink_fund_mat)
			{
//
				actions_proc(change_new, actions_index,
				actions_array, py_prepay_type_init );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_prepay_type_init)
			{
//
				actions_proc(change_new, actions_index,
				actions_array, py_set_current );

				break;
			}

			actions_index --;


			actions_proc(change_step, actions_index,
				actions_array, 0 );

			switch (scr_meth)
			{
				case 	scr_meth_general:
				case	scr_meth_borwin:
					/*{For Borland Windows.}*/
				{

					break;
				}
				default:
				{

					return_state = return_err_inv_scr_meth;

//					//errproc(return_state,module_name,"","","");

					goto func_end;

					break;

				}
			}
			break;
		 }
		 case py_action_init_cf:
		 /*{Initialize the cashflow screen.}*/
		 {

					 /*{First do common setups.}*/

			if (actions_array[actions_index].prev_action
			== py_action_start)
			{

				current_class = instr_cashflow_class;
				in_instr.instr_class = instr_cashflow_class;

				actions_index ++;

				actions_proc(change_new, actions_index,
				actions_array, py_yield_meth_init );

				break;

			}

			if (actions_array[actions_index].prev_action
			== py_yield_meth_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_yield_days_init );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_yield_days_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_yield_freq_init );

				break;
			}
//
			if (actions_array[actions_index].prev_action
			== py_yield_freq_init)
			{
				actions_proc(change_new, actions_index,
				actions_array, py_action_init_part_pay );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_action_init_part_pay)
			{
				actions_proc(change_new, actions_index,
				actions_array, py_set_current );

				break;
			}
//
			actions_index --;


			actions_proc(change_step, actions_index,
				actions_array, 0 );

			switch (scr_meth)
			{
				case 	scr_meth_general:
				case	scr_meth_borwin:
					/*{For Borland Windows.}*/
				{

					break;
				}
				default:
				{

					return_state = return_err_inv_scr_meth;

//					//errproc(return_state,module_name,"","","");

					goto func_end;

					break;

				}
			}
			break;
		 }
		 case py_action_init_mbs:
		 /*{Initialize the screen.}*/
		 {

					 /*{First do common setups.}*/

			if (actions_array[actions_index].prev_action
			== py_action_start)
			{

				actions_index ++;

				current_class = instr_mbs_class;
				in_instr.instr_class = instr_mbs_class;

				actions_proc(change_new, actions_index,
				actions_array, py_day_count_init );

				break;

			}

			if (actions_array[actions_index].prev_action
				== py_day_count_init)
			{


				actions_proc(change_new, actions_index,
				actions_array, fra_holiday_init );

				break;

			}

			if (actions_array[actions_index].prev_action
			== fra_holiday_init)
			{


				actions_proc(change_new, actions_index,
				actions_array, py_freq_count_init );

				break;

			}

			if (actions_array[actions_index].prev_action
			== py_freq_count_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_yield_freq_init );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_yield_freq_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_yield_days_init );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_yield_days_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_yield_meth_init );

				break;

			}

			if (actions_array[actions_index].prev_action
			== py_yield_meth_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_prepay_type_init );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_prepay_type_init)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_action_init_part_pay );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_action_init_part_pay)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_set_current );

				break;
			}

			actions_index --;


			actions_proc(change_step, actions_index,
				actions_array, 0 );

			switch (scr_meth)
			{
				case 	scr_meth_general:
				case	scr_meth_borwin:
					/*{For Borland Windows.}*/
				{

					break;
				}
				default:
				{

					return_state = return_err_inv_scr_meth;

					////errproc(return_state,module_name,"","","");

					goto func_end;

					break;

				}
			}
			break;
		 }
		 case py_action_proc_mbs:
		 /*{Initialize the screen.}*/
		 {

			if (actions_array[actions_index].prev_action
			== py_action_start)
			{

				actions_index ++;

				actions_proc(change_new, actions_index,
				actions_array, py_proc_service );

				break;

			}

			if (actions_array[actions_index].prev_action
				== py_proc_service)
			{


				actions_proc(change_new, actions_index,
				actions_array, py_proc_prepay_rate );

				break;

			}

			if (actions_array[actions_index].prev_action
			== py_proc_prepay_rate)
			{


				actions_proc(change_new, actions_index,
				actions_array, py_proc_lag );

				break;

			}

			if (actions_array[actions_index].prev_action
			== py_proc_lag)
			{

				actions_proc(change_new, actions_index,
				actions_array, py_proc_prepay_type );

				break;
			}

			if (actions_array[actions_index].prev_action
			== py_proc_prepay_type)
			{

			  actions_index --;

			  actions_proc(change_step, actions_index,
				actions_array, 0 );

			  break;

			}

		 }
		 case fra_holiday_init:
		 /*{Initialize the holiday choice.}*/
		 {

			for (element_count = 0; element_count <
			fra_last_holiday; ++element_count)
			{
/*
		memcpy(extra_parms->holiday_choice[element_count],
			  fra_holiday_names[element_count],
		fra_holiday_names_len);
*/
//			  strcpy(holiday_choice[element_count], fra_holiday_names[element_count]);
			}

//			strcpy(extra_parms->current_holiday_name,"USD");
//			strcpy(current_holiday_name,fra_holiday_names[0]);
			current_holiday = 0;


			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case py_action_init_monthend:
		 /*{Initialize the monthend choice.}*/
		 {

			for (element_count = 0; element_count <
			monthend_count; ++element_count)
			{

			  strcpy_s(monthend_choice[element_count],
				 monthend_names[element_count]);
			}


			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case py_action_init_part_pay:
		 /*{Initialize partial payments.}*/
		 {

			part_pays_sched[0].last_element = 0;

			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case py_action_proc_part_pay:
		 /*{Process partial payments.}*/
		 {

			if ((part_pays_sched[0].last_element < 0) ||
				(part_pays_sched[0].last_element > max_part_pays))
			{

					return_state = return_err_partpay_out_bounds;

					////errproc(return_state,module_name,"","","");

					goto func_end;

					break;

			}

			work_long_double = 0;

			for (element_count = 0;
				return_state == return_success,
					(element_count < part_pays_sched[0].last_element) &&
					(element_count < max_part_pays);
				element_count++)
			{

				return_state =
					 datechck(part_pays_sched[element_count].pay_date);

				if (return_state != return_success)
				{

				  return_state = return_err_partpay_bad_date;
				  ////errproc(return_state,module_name,"","","");
				  goto func_end;

				}

				str_cmp =  datecmp(&issue_date.date_string,
				&part_pays_sched[element_count].pay_date.date_string);

				if (str_cmp > 0)
				{

				  return_state = return_err_partpay_date_out_bounds;
				  ////errproc(return_state,module_name,"","","");
				  goto func_end;

				}

				str_cmp =  datecmp(&mat_date.date_string,
				&part_pays_sched[element_count].pay_date.date_string);

				if (str_cmp < 0)
				{

				  return_state = return_err_partpay_date_out_bounds;
				  ////errproc(return_state,module_name,"","","");
				  goto func_end;

				}

				if (element_count > 0)
				{

					str_cmp =  datecmp(
					&in_instr.part_pays_sched[element_count - 1].pay_date.date_string,
					&part_pays_sched[element_count].pay_date.date_string);

					if (str_cmp >= 0)
					{

					  return_state = return_err_partpay_date_nonasc;
					  ////errproc(return_state,module_name,"","","");
					  goto func_end;

					}

				}

				in_instr.part_pays_sched[element_count].payment =
				  part_pays_sched[element_count].payment;

				 datecpy(in_instr.part_pays_sched[element_count].pay_date.date_string,
				  part_pays_sched[element_count].pay_date.date_string);

				work_long_double = work_long_double +
					part_pays_sched[element_count].payment;

			}

			if ((work_long_double != in_instr.redemp_price) &&
             (part_pays_sched[0].last_element != 0))
			{

				  return_state = return_err_partpay_total_pay_bad;
				  ////errproc(return_state,module_name,"","","");
				  goto func_end;

			}

			in_instr.part_pays = element_count;

			in_instr.part_pay_price_base = in_instr.redemp_price;

			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case py_action_init_excoup:
		 /*{Initialize the excoup choice.}*/
		 {

			for (element_count = 0; element_count <
			excoup_count; ++element_count)
			{

			  strcpy_s(excoup_choice[element_count],
				 excoup_names[element_count]);
			}


			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case py_action_init_sink_fund_mat:
		 /*{Initialize the sinking fund maturity choice.}*/
		 {

			for (element_count = 0; element_count <
			py_last_redemp_sched; ++element_count)
			{

			  strcpy(sink_fund_mat_choice[element_count],
				 redemp_sched_names[element_count]);
			}


			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case fra_proc_holiday:
		 {


			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case proc_holiday:
		 {

//			strcpy(in_instr.holiday_code, current_holiday_name);

			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case py_action_proc_sink_fund_mat:
		 {

			if ( strcmp(current_sink_fund_mat_name,
				redemp_sched_names[py_equivalent_redemp_sched]) == 0 )
			{

//				current_sink_fund_mat = py_equivalent_redemp_sched;

			}
			else
			{

				if ( strcmp(current_sink_fund_mat_name,
					redemp_sched_names[py_average_redemp_sched]) == 0 )
				{

//					current_sink_fund_mat = py_average_redemp_sched;

				}
				else
				{

							return_state = return_err_invalid_redemp_sched;

							////errproc(return_state,module_name,"","","");

							goto func_end;

				}

			}

//			pyparm.redemp_sched = current_sink_fund_mat;

			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case py_action_proc_monthend:
		 {

			if ( strcmp(current_monthend_name,
				monthend_names[monthend_yes]) == 0 )
			{

				current_monthend = monthend_yes;

			}
			else
			{

				current_monthend = monthend_no;

			}

			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }
		 case py_action_proc_excoup:
		 {

			if ( strcmp(current_excoup_name,
				excoup_names[ex_coup_yes]) == 0 )
			{

				current_excoup = ex_coup_yes;

			}
			else
			{

				current_excoup = ex_coup_no;

			}

			actions_proc(change_step, actions_index,
				actions_array, 0 );

			break;

		 }

		 case py_init_frn:
		 /*{Initialize the frn screen.}*/
		 {

					 /*{First do common setups.}*/

		  if (actions_array[actions_index].prev_action
			== py_action_start)
		  {

			in_instr.instr_class = instr_float_class;

			actions_index ++;


			actions_proc(change_new, actions_index,
			actions_array, py_yield_meth_init );

			break;

		  }

		  if (actions_array[actions_index].prev_action
			== py_yield_meth_init)
		  {

				actions_proc(change_new, actions_index,
				  actions_array, py_action_init_sink_fund_mat );

				break;

		  }

		  if (actions_array[actions_index].prev_action
			== py_action_init_sink_fund_mat)
		  {
				actions_proc(change_new, actions_index,
				  actions_array, py_set_current );

				break;

		  }

		  if (actions_array[actions_index].prev_action
			== py_set_current)
		  {

			actions_proc(change_new, actions_index,
				actions_array, py_freq_count_init_frn );

			break;

		  }

		  if (actions_array[actions_index].prev_action
			== py_freq_count_init_frn)
		  {

			actions_proc(change_new, actions_index,
				actions_array, py_holiday_adj_count_init_frn );

			break;
		  }

		  if (actions_array[actions_index].prev_action
			== py_holiday_adj_count_init_frn)
		  {

			actions_proc(change_new, actions_index,
				actions_array, py_simp_comp_init_frn );


			break;
		  }

		  if (actions_array[actions_index].prev_action
			== py_simp_comp_init_frn)
		  {

//
			actions_proc(change_new, actions_index,
				actions_array, py_set_current_frn);

			break;
		  }

		  if (actions_array[actions_index].prev_action
			== py_set_current_frn)
		  {

//

//
			rerate_sched.current_holiday_adj =
				in_instr.pay_freq.holiday_adj;
			strcpy(rerate_sched.current_holiday_adj_name,
				rerate_sched.holiday_adj_choice[rerate_sched.current_holiday_adj]);

			rerate_sched.rerate_sched = in_instr.pay_freq;

			rerate_sched.rerate_sched.holiday_adj =
				event_sched_same_holiday_adj;
			rerate_sched.current_simp_comp = simp_comp_simple;
//


			actions_proc(change_new, actions_index,
				actions_array, fra_holiday_init );

			break;

		  }

		  if (actions_array[actions_index].prev_action
			== fra_holiday_init)
		  {


			actions_proc(change_new, actions_index,
				actions_array, py_day_count_init );

			break;

		  }

		  if (actions_array[actions_index].prev_action
			== py_day_count_init)
		  {


			actions_proc(change_new, actions_index,
				actions_array, py_freq_count_init );

			break;

		  }

		  if (actions_array[actions_index].prev_action
			== py_freq_count_init)
		  {

			actions_proc(change_new, actions_index,
				actions_array, py_yield_days_init );

			break;
		  }

		  if (actions_array[actions_index].prev_action
			== py_yield_days_init)
		  {

				actions_proc(change_new, actions_index,
				actions_array, py_action_init_part_pay );

				break;
		  }

		  if (actions_array[actions_index].prev_action
			== py_action_init_part_pay)
		  {

			actions_proc(change_new, actions_index,
				actions_array, py_yield_freq_init );

			break;
		  }


		  actions_index --;

		  actions_proc(change_step, actions_index,
				actions_array, 0);

		  break;
		 }
		 case py_instr_class_init:
		 /*{Initialize the instrument class choice.}*/
		 {


			for (element_count = 0; element_count <
			instr_last_class; ++element_count)
			{
/*
		  memcpy(instr_class_desc_choice[element_count],
		  instr_class_descs[element_count],
		  instr_class_desc_len);
*/
				strcpy(instr_class_desc_choice[element_count],
				instr_class_descs[element_count]);
			}

			in_instr.instr_class = 0;


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_day_count_init:
		 /*{Initialize the day_count choice.}*/
		 {

			for (element_count = 0; element_count <
			date_last_day_count; ++element_count)
			{
/*
		memcpy(day_count_choice[element_count],
			  day_count_names[element_count],
			  day_count_names_len);
*/
				strcpy(day_count_choice[element_count],
				day_count_names[element_count]);
			}


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_freq_count_init:
		 /*{Initialize the frequency count choice.}*/
		 {


			for (element_count = 0; element_count <
			freq_count; ++element_count)
			{
/*
		memcpy(pay_freq_choice[element_count],
			  freq_names[element_count],
			  freq_names_len);
*/
				strcpy(pay_freq_choice[element_count],
				freq_names[element_count]);
			}

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_holiday_adj_count_init_frn:
		 /*{Initialize the frn holiday adjust count choice.}*/
		 {


			for (element_count = 0; element_count <
			holiday_adj_count; ++element_count)
			{
/*
		memcpy(rerate_sched.holiday_adj_choice[element_count],
			  holiday_adj_names[element_count],
		holiday_adj_names_len);
*/
				strcpy(rerate_sched.holiday_adj_choice[element_count],
				holiday_adj_names[element_count]);
			}

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_freq_count_init_frn:
		 /*{Initialize the frn frequency count choice.}*/
		 {


			for (element_count = 0; element_count <
			freq_count; ++element_count)
			{
/*
		memcpy(rerate_sched.pay_freq_choice[element_count],
			  freq_names[element_count],
			  freq_names_len);
*/
				strcpy(rerate_sched.pay_freq_choice[element_count],
				freq_names[element_count]);
			}

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_simp_comp_init_frn:
		 /*{Initialize the frn Simple/Compound choice.}*/
		 {


			for (element_count = 0; element_count <
			simp_comp_count; ++element_count)
			{
/*
		memcpy(rerate_sched.simp_comp_choice[element_count],
			  simp_comp_names[element_count],
			  simp_comp_names_len);
*/
				strcpy(rerate_sched.simp_comp_choice[element_count],
				simp_comp_names[element_count]);
			}

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_yield_meth_init:
		 /*{Initialize the yield method choice.}*/
		 {

			for (element_count = 0; element_count <
			py_last_yield_meth; ++element_count)
			{
/*
		memcpy(yield_meth_choice[element_count],
			  yield_meth_names[element_count],
			  yield_names_len);
*/
				if (in_instr.instr_class == instr_mbs_class)
				{

				  strcpy(yield_meth_choice[element_count],
				  instr_mbs_class_name);

				}
				else
				{

				  strcpy(yield_meth_choice[element_count],
				  yield_meth_names[element_count]);

				}
			}

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_yield_days_init:
		 /*{Initialize the yield days choice.}*/
		 {

			for (element_count = 0; element_count <
			date_last_day_count; ++element_count)
			{
/*
		  memcpy(yield_days_choice[element_count],
		  day_count_names[element_count],
		  day_count_names_len);
*/
				strcpy(yield_days_choice[element_count],
				day_count_names[element_count]);
			}

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_yield_freq_init:
		 /*{Initialize the yield frequency choice.}*/
		 {


			for (element_count = 0; element_count <
			freq_count; ++element_count)
			{
/*
		memcpy(yield_freq_choice[element_count],
			  freq_names[element_count],
			  freq_names_len);
*/
				strcpy(yield_freq_choice[element_count],
				freq_names[element_count]);
			}

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_set_current:
		 /*{Set the current fields based on the instrument class.}*/
		 {

			return_state =	classdef(&in_instr);

			if (return_state != return_success) {

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}

			 datecpy(prev_date.date_string,zero_date);
			 datecpy(next_date.date_string,zero_date);

			current_class = in_instr.instr_class;
			current_day_count = in_instr.day_count;
			strcpy(current_day_count_name, day_count_names[current_day_count]);

			if (in_instr.pay_freq.freq == 12)
			{

			  current_pay_freq = (0);

			}
			else
			{
			  if (in_instr.pay_freq.freq == 1)
			  {

				 current_pay_freq = (1);
			  }
			  else
			  {
				 if (in_instr.pay_freq.freq == 3)
				 {

					current_pay_freq = (2);

				 }
				 else
				 {
					if (in_instr.pay_freq.freq == 6)
					{

					  current_pay_freq = (3);

					}
					else
					{
							 current_pay_freq = (0);

					}
				 }
			  }
			}
			strcpy(current_pay_freq_name, freq_names[current_pay_freq]);
			current_yield_meth = in_instr.yield_meth;
/*
			memcpy(current_yield_meth_name,
		yield_meth_choice[*current_yield_meth],
		yield_names_len);
*/
			if (in_instr.instr_class == instr_mbs_class)
			{

			  strcpy(current_yield_meth_name,
			  yield_MBS_meth_name);

			}
			else
			{

			  strcpy(current_yield_meth_name,
			  yield_meth_choice[current_yield_meth]);

			}

			current_yield_days = current_day_count;
			strcpy(current_yield_days_name,	day_count_names[current_day_count]);

			current_monthend = monthend_yes;

			current_excoup = ex_coup_no;

			strcpy(current_excoup_name,
					excoup_names[current_excoup]);

//			current_sink_fund_mat = py_equivalent_redemp_sched;
			strcpy(current_sink_fund_mat_name,
			  sink_fund_mat_choice[py_equivalent_redemp_sched]);

			current_yield_freq = current_pay_freq;

			rerate_sched.current_pay_freq = current_pay_freq;
			strcpy(rerate_sched.current_pay_freq_name,current_pay_freq_name
				);

			current_ex_coup_days = in_instr.ex_coup_days;

			int_rate = in_instr.rate_offset;

//			*instr_parm = in_instr;

			in_price = 0;
			in_yield = 0;
			out_price = 0;
			out_yield = 0;
			calc_what = py_yield_from_price_calc_what;
			prepay_type = py_cpr_prepay_type;
			cpr_rate = 0;
			current_factor = 1;
			service_fee = 0;
			lag = 0;

			pyparm.prepay_type = prepay_type;
			pyparm.cpr_rate = cpr_rate;
			pyparm.current_factor = current_factor;
			in_instr.service_fee = service_fee;
			in_instr.lag = (char)lag;

			pyparm.parm_use = py_no_parm_use;
			pyparm.price_var = 0;
			pyparm.frac_per = py_no_frac_per;
			pyparm.pay_adj = event_sched_no_holiday_adj;
			pyparm.comp_freq = 0;
			pyparm.per_len = 0;
			pyparm.date_cal_num = date_no_cal;
			pyparm.date_cal_den = date_no_cal;
			pyparm.yield_meth = in_instr.yield_meth;
			pyparm.calc_first = py_yes_calc_first;

			if (in_instr.instr_class == instr_ssd_class)
			{

			  pyparm.parm_use = py_yes_parm_use;
			  pyparm.calc_first = py_no_calc_first;

			}

			if (current_class == instr_cashflow_class)
			{

			  pyparm.parm_use = py_yes_parm_use;
			  pyparm.date_cal_num = in_instr.cal_num;
			  pyparm.date_cal_den = in_instr.cal_den;

			}

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_set_current_frn:
		 /*{Set the current frn fields based on the instrument class.}*/
		 {
/*
			if (actions_array[actions_index].prev_action ==
					py_proc_pay_freq_frn)
			{

					 actions_index --;
*/

			actions_proc(change_step, actions_index,
				actions_array, 0);
/*
			rerate_sched.current_holiday_adj =
				in_instr.pay_freq.holiday_adj;

			rerate_sched.rerate_sched = in_instr.pay_freq;
*/
			 datecpy(rerate_sched.rerate_sched.first_date.date_string,
				in_instr.issue_date.date_string);
			rerate_sched.rerate_sched.month_day =
				in_instr.issue_date.date.days;
/*
			rerate_sched.rerate_sched.month_day =
				in_instr.pay_freq.first_date.date.days;
*/
/*
			rerate_sched.current_holiday_adj = event_sched_same_holiday_adj; 
			strcpy(rerate_sched.current_holiday_adj_name,
				rerate_sched.holiday_adj_choice[rerate_sched.current_holiday_adj]);
*/
/*
			rerate_sched.rerate_sched.holiday_adj =
				event_sched_same_holiday_adj;
*/
//
			rerate_sched.current_simp_comp = simp_comp_simple;
			if (in_instr.comp_freq.period == event_sched_free_period)
			{

				rerate_sched.current_simp_comp = simp_comp_simple;

			}
			else
			{

				rerate_sched.current_simp_comp = simp_comp_compound;

			}

			strcpy(rerate_sched.current_simp_comp_name, 
				rerate_sched.simp_comp_choice[rerate_sched.current_simp_comp]);

//
			break;
/*
			}

				  actions_index ++;

			actions_array[actions_index].prev_action =
			actions_array[actions_index - 1].curr_action;
			actions_array[actions_index].next_action =
			actions_array[actions_index - 1].curr_action;
			actions_array[actions_index].curr_action =
			py_proc_pay_freq_frn;

			break;
*/
		 }
		 case py_proc_pay_freq_frn:
		 {

			if ( strcmp(rerate_sched.current_pay_freq_name, freq_names[0]) == 0 )
			{

				rerate_sched.rerate_sched.freq = 12;

				rerate_sched.current_pay_freq = (0);

			}

			else
			{

				if ( strcmp(rerate_sched.current_pay_freq_name, freq_names[1]) == 0 )
				{

					rerate_sched.rerate_sched.freq = 1;

					rerate_sched.current_pay_freq = (1);

				}
				else
				{
					if ( strcmp(rerate_sched.current_pay_freq_name,
						freq_names[2]) == 0 )
					{

						rerate_sched.rerate_sched.freq = 3;

						rerate_sched.current_pay_freq = (2);

					}

					else
					{

						if ( strcmp(rerate_sched.current_pay_freq_name,
							freq_names[3]) == 0 )
						{

							rerate_sched.rerate_sched.freq = 6;

							rerate_sched.current_pay_freq = (3);

						}
						else
						{

							rerate_sched.current_pay_freq = (0);

							return_state = return_err_invalid_pay_freq;

							////errproc(return_state,module_name,"","","");

							goto func_end;

						}
					}
				}
			}


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_proc_simp_comp_frn:
		 {


			if ( strcmp(rerate_sched.current_simp_comp_name,
			simp_comp_names[simp_comp_simple]) == 0 )
			{



				rerate_sched.current_simp_comp = simp_comp_simple;

				in_instr.comp_freq.period = event_sched_free_period;

			}
			else
			{
			  if ( strcmp(rerate_sched.current_simp_comp_name,
			  simp_comp_names[simp_comp_compound]) == 0 )
			  {

				 rerate_sched.current_simp_comp = simp_comp_compound;

				 in_instr.comp_freq.period = event_sched_end_period;

			  }
			  else
			  {

				rerate_sched.current_simp_comp = simp_comp_simple;

				return_state = return_err_invalid_simp_comp;

				////errproc(return_state,module_name,"","","");

				goto func_end;

			  }
			}


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_proc_holi:
		 {

			if ( strcmp(rerate_sched.current_holiday_adj_name,
				holiday_adj_names[0]) == 0 )
			{

				rerate_sched.rerate_sched.holiday_adj =
				event_sched_march_holiday_adj;

			}

			else
			{

				if ( strcmp(rerate_sched.current_holiday_adj_name,
					holiday_adj_names[1]) == 0 )
				{

					rerate_sched.rerate_sched.holiday_adj =
					event_sched_next_holiday_adj;

				}
				else
				{
					if ( strcmp(rerate_sched.current_holiday_adj_name,
					holiday_adj_names[2]) == 0 )
					{

						rerate_sched.rerate_sched.holiday_adj =
						event_sched_np_holiday_adj;

					}

					else
					{

					  if ( strcmp(rerate_sched.current_holiday_adj_name,
						holiday_adj_names[3]) == 0 )
					  {

							rerate_sched.rerate_sched.holiday_adj =
							event_sched_prev_holiday_adj;

						}
						else
						{

							if ( strcmp(rerate_sched.current_holiday_adj_name,
								holiday_adj_names[4]) == 0 )
							{

								rerate_sched.rerate_sched.holiday_adj =
									event_sched_pn_holiday_adj;

							}
							else
							{

								if ( strcmp(rerate_sched.current_holiday_adj_name,
									holiday_adj_names[5]) == 0 )
								{

									rerate_sched.rerate_sched.holiday_adj =
										event_sched_same_holiday_adj;

								}
								else
								{

									rerate_sched.rerate_sched.holiday_adj =
										event_sched_same_holiday_adj;

									return_state = return_err_invalid_holiday;

									////errproc(return_state,module_name,"","","");

									goto func_end;

								}
							}
						}
					}
				}
			}

			in_instr.pay_freq.holiday_adj =
				rerate_sched.rerate_sched.holiday_adj;


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_proc_pay_freq:
		 {

			if ( strcmp(current_pay_freq_name, freq_names[0]) == 0 )
			{

			  in_instr.pay_freq.freq = 12;

			  current_pay_freq = (0);

			}

			else
			{

			  if ( strcmp(current_pay_freq_name, freq_names[1]) == 0 )
			  {

				 in_instr.pay_freq.freq = 1;

				 current_pay_freq = (1);

			  }
			  else
			  {
				  if ( strcmp(current_pay_freq_name, freq_names[2]) == 0 )
				  {

					in_instr.pay_freq.freq = 3;

					current_pay_freq = (2);

				  }

				  else
				  {

					if ( strcmp(current_pay_freq_name, freq_names[3]) == 0 )
					 {

					  in_instr.pay_freq.freq = 6;

					  current_pay_freq = (3);

					}
					else
					{

					  current_pay_freq = (0);

					  return_state = return_err_invalid_pay_freq;

					  ////errproc(return_state,module_name,"","","");

					  goto func_end;

					}
				  }
				}
			}

//			instr_parm->pay_freq.freq = in_instr.pay_freq.freq;
			current_yield_freq = current_pay_freq;
			rerate_sched.current_pay_freq = current_pay_freq;
			pyparm.comp_freq = in_instr.pay_freq.freq;


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_proc_yield_freq:
		 {

			if ( strcmp(current_yield_freq_name, freq_names[0]) == 0 )
			{

				pyparm.comp_freq = 12;

			}

			else
			{

			  if ( strcmp(current_yield_freq_name, freq_names[1]) == 0 )
			  {

					pyparm.comp_freq = 1;

			  }
			  else
			  {
				  if ( strcmp(current_yield_freq_name, freq_names[2]) == 0 )
				  {

						pyparm.comp_freq = 3;

				  }

				  else
				  {

					if (strcmp(current_yield_freq_name, freq_names[3]) == 0 )
					{

						pyparm.comp_freq = 6;

					}
					else
					{

						return_state = return_err_invalid_pay_freq;

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}
				  }
			  }
			}


			pyparm.parm_use = py_yes_parm_use;
			current_yield_freq = pyparm.comp_freq;


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_proc_day_count:
		 {

			if ( strcmp(current_day_count_name,
				day_count_names[date_30e_360_day_count]) == 0 )
				{

					in_instr.day_count = date_30e_360_day_count;
					in_instr.cal_num = day_count_nums[date_30e_360_day_count];
					in_instr.cal_den = day_count_dens[date_30e_360_day_count];

			}
			else
			{
				if ( strcmp(current_day_count_name,
					day_count_names[date_30_360_day_count]) == 0 )
				{

					in_instr.day_count = date_30_360_day_count;
					in_instr.cal_num = day_count_nums[date_30_360_day_count];
					in_instr.cal_den = day_count_dens[date_30_360_day_count];

				}
				else
				{
					if (strcmp(current_day_count_name,
						day_count_names[date_act_360_day_count]) == 0 )
					{

					 in_instr.day_count = date_act_360_day_count;
					 in_instr.cal_num = day_count_nums[date_act_360_day_count];
					 in_instr.cal_den = day_count_dens[date_act_360_day_count];

					}
					else
					{
						if ( strcmp(current_day_count_name,
							day_count_names[date_act_365_day_count]) == 0 )
						{

							in_instr.day_count = date_act_365_day_count;
							in_instr.cal_num	= day_count_nums[date_act_365_day_count];
							in_instr.cal_den	= day_count_dens[date_act_365_day_count];

						}
						else
						{
							if ( strcmp(current_day_count_name,
								day_count_names[date_act_act_day_count]) == 0 )
							{

								in_instr.day_count = date_act_act_day_count;
								in_instr.cal_num = day_count_nums[date_act_act_day_count];
								in_instr.cal_den = day_count_dens[date_act_act_day_count];

							}
							else
							{
								if ( strcmp(current_day_count_name,
								day_count_names[date_act_365cd_day_count]) == 0 )
								{

									in_instr.day_count = date_act_365cd_day_count;
									in_instr.cal_num = day_count_nums[date_act_act_day_count];
									in_instr.cal_den = day_count_dens[date_act_365_day_count];

								}
								else
								{
									if ( strcmp(current_day_count_name,
									day_count_names[date_act_366_day_count]) == 0 )
									{

										in_instr.day_count = date_act_366_day_count;
										in_instr.cal_num = day_count_nums[date_act_act_day_count];
										in_instr.cal_den = day_count_dens[date_act_366_day_count];

									}
								}
							}
						}
					}
				}
			}

//			instr_parm->day_count = in_instr.day_count;

			current_day_count = in_instr.day_count;
			current_yield_days = in_instr.day_count;
			strcpy(current_day_count_name,	day_count_names[current_day_count]);
			strcpy(current_yield_days_name,	day_count_names[current_day_count]);
/*
			if (actions_array[actions_index].prev_action
			== py_proc_yield_days)
			{

					 actions_index --;
*/

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;
/*
				  }

				  actions_index ++;

			strcpy(current_yield_days_name, current_day_count_name);

			actions_array[actions_index].prev_action =
			actions_array[actions_index - 1].curr_action;
			actions_array[actions_index].next_action =
			actions_array[actions_index - 1].curr_action;
			actions_array[actions_index].curr_action =
			py_proc_yield_days;

				  break;
*/
		 }
		 case py_proc_yield_meth:
		 {

			if ( strcmp(current_yield_meth_name,
				yield_meth_names[py_aibd_yield_meth]) == 0 )
			{

				pyparm.yield_meth = py_aibd_yield_meth;

			}
			else
			{
				if ( strcmp(current_yield_meth_name,
					yield_meth_names[py_mmdisc_yield_meth]) == 0 )
				{

					pyparm.yield_meth = py_mmdisc_yield_meth;

				}
				else
				{
					if ( strcmp(current_yield_meth_name,
						yield_meth_names[py_mm_yield_meth]) == 0 )
					{

						pyparm.yield_meth = py_mm_yield_meth;

					}
					else
					{
						if ( strcmp(current_yield_meth_name,
							yield_meth_names[py_ytm_simp_yield_meth]) == 0 )
						{

							pyparm.yield_meth = py_ytm_simp_yield_meth;

						}
						else
						{
							if ( strcmp(current_yield_meth_name,
								yield_meth_names[py_ytm_comp_yield_meth]) == 0 )
							{

								pyparm.yield_meth = py_ytm_comp_yield_meth;

							}
							else
							{
								if ( strcmp(current_yield_meth_name,
								yield_meth_names[py_simp_yield_meth]) == 0 )
								{

									pyparm.yield_meth = py_simp_yield_meth;

								}
								else
								{
									if ( strcmp(current_yield_meth_name,
										yield_meth_names[py_curr_yield_meth]) == 0 )
										{

											pyparm.yield_meth = py_curr_yield_meth;

										}
										else
										{
											if ( strcmp(current_yield_meth_name,
												yield_meth_names[py_gm_yield_meth]) == 0 )
											{

												pyparm.yield_meth = py_gm_yield_meth;

											}
											else
											{
												if ( strcmp(current_yield_meth_name,
												yield_meth_names[py_muni_yield_meth]) == 0 )
												{

													pyparm.yield_meth = py_muni_yield_meth;

												}
												else
												{
													if ( strcmp(current_yield_meth_name,
													yield_meth_names[py_corp_yield_meth]) == 0 )
												{

													pyparm.yield_meth = py_corp_yield_meth;

												}
												else
												{
													if ( strcmp(current_yield_meth_name,
													yield_meth_names[py_ustr_yield_meth]) == 0 )
													{

														pyparm.yield_meth = py_ustr_yield_meth;

													}
													else
													{
														if ( strcmp(current_yield_meth_name,
														yield_meth_names[py_moos_yield_meth]) == 0 )
														{

															pyparm.yield_meth = py_moos_yield_meth;

														}
														else
														{
															if ( strcmp(current_yield_meth_name,
															yield_meth_names[py_bf_yield_meth]) == 0 )
															{

																pyparm.yield_meth = py_bf_yield_meth;

															}
															else
															{
/*					if ( strcmp(current_yield_meth_name,
					  yield_meth_names[py_cpr_yield_meth]) == 0 )
								 {

					  pyparm.yield_meth = py_cpr_yield_meth;

								 }
								 else
*/
																if ( strcmp(current_yield_meth_name,
																yield_meth_names[py_ty_yield_meth]) == 0 )
																{

																	pyparm.yield_meth = py_ty_yield_meth;

																}
																else
																{
																  if ( strcmp(current_yield_meth_name,
																  yield_MBS_meth_name) == 0 )
																  {

																	 pyparm.yield_meth = py_MBS_yield_meth;

																  }
																  else
																  {

																	 return_state = return_err_yield_meth_inv;

																	 ////errproc(return_state,module_name,"","","");

																	 goto func_end;
																  }
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;
		 }
		 case py_proc_yield_days:
		 {

			if ( strcmp(current_yield_days_name,
			day_count_names[date_30e_360_day_count]) == 0 )
			{

				pyparm.day_count = date_30e_360_day_count;
				pyparm.date_cal_num = day_count_nums[date_30e_360_day_count];
				pyparm.date_cal_den = day_count_dens[date_30e_360_day_count];

			}
			else
			{
				if ( strcmp(current_yield_days_name,
					day_count_names[date_30_360_day_count]) == 0 )
				{

					pyparm.day_count = date_30_360_day_count;
					pyparm.date_cal_num = day_count_nums[date_30_360_day_count];
					pyparm.date_cal_den = day_count_dens[date_30_360_day_count];

				}
				else
				{
				  if ( strcmp(current_yield_days_name,
					day_count_names[date_act_360_day_count]) == 0 )
				  {

					pyparm.day_count = date_act_360_day_count;
					pyparm.date_cal_num = day_count_nums[date_act_360_day_count];
					pyparm.date_cal_den = day_count_dens[date_act_360_day_count];

				  }
				  else
				  {
						if ( strcmp(current_yield_days_name,
						day_count_names[date_act_365_day_count]) == 0 )
						{

							pyparm.day_count = date_act_365_day_count;
							pyparm.date_cal_num	= day_count_nums[date_act_365_day_count];
							pyparm.date_cal_den	= day_count_dens[date_act_365_day_count];

						}
						else
						{
							if ( strcmp(current_yield_days_name,
							day_count_names[date_act_act_day_count]) == 0 )
							{

								pyparm.day_count = date_act_act_day_count;
								pyparm.date_cal_num = day_count_nums[date_act_act_day_count];
								pyparm.date_cal_den = day_count_dens[date_act_act_day_count];

							}
							else
							{
								if ( strcmp(current_yield_days_name,
								day_count_names[date_act_365cd_day_count]) == 0 )
								{

									pyparm.day_count = date_act_365cd_day_count;
									pyparm.date_cal_num = day_count_nums[date_act_act_day_count];
									pyparm.date_cal_den = day_count_dens[date_act_365_day_count];

								}
								else
								{
									if ( strcmp(current_yield_days_name,
									day_count_names[date_act_366_day_count]) == 0 )
									{

										pyparm.day_count = date_act_366_day_count;
										pyparm.date_cal_num = day_count_nums[date_act_act_day_count];
										pyparm.date_cal_den = day_count_dens[date_act_366_day_count];

									}
								}
							}
						}
					}
				}
			}

			pyparm.parm_use = py_yes_parm_use;
/*
			py_parm->parm_use = pyparm.parm_use;
			py_parm->day_count = pyparm.day_count;
			py_parm->date_cal_num = pyparm.date_cal_num;
			py_parm->date_cal_den = pyparm.date_cal_den;
*/
			current_yield_days = pyparm.day_count;
			strcpy(current_yield_days_name,	day_count_names[pyparm.day_count]);


			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }
		 case py_proc_class_desc:
		 {

			if (actions_array[actions_index].prev_action ==
				py_set_current)
			{

					 actions_index --;


			  actions_proc(change_step, actions_index,
				actions_array, 0);

					 break;

			}

			/*{Validate class.}*/

			for (element_count = 0, str_cmp = 1;
				(element_count < instr_last_class) && (str_cmp != 0);
				element_count++)
			{

				str_cmp = strcmp(current_class_desc,
				instr_class_descs[element_count]);

				in_instr.instr_class = element_count;

			}

			if (str_cmp == 0)
			{

					 actions_index ++;


			  actions_proc(change_new, actions_index,
				actions_array, py_set_current);

			}
			else
			{

				return_state = return_err_invalid_class_desc;

				////errproc(return_state,module_name,"","","");

				goto func_end;

			}

			break;

		 }
		 case py_proc_mat_date:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_date)
			{

					 actions_index --;


			  actions_proc(change_step, actions_index,
				actions_array, 0);

			  if (return_state != return_success) {

							 return_state = return_err_mat_date_bad;
				////errproc(return_state,module_name,"","","");
				goto func_end;
			  }

			   datecpy(in_instr.mat_date.date_string,
					mat_date.date_string);

			  break;

			}

			check_date1 = mat_date;

			actions_index ++;


			actions_proc(change_new, actions_index,
				actions_array, py_check_date);

			break;

		 }
		 case py_proc_iss_date:
		 {

			if (actions_array[actions_index].prev_action ==
				py_set_accrue_date)
			{

				actions_index --;


				actions_proc(change_step, actions_index,
				actions_array, 0);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_date)
			{

			  if (return_state != return_success)
			  {

				return_state = return_err_iss_date_bad;
				////errproc(return_state,module_name,"","","");
				goto func_end;
			  }

			   datecpy(in_instr.issue_date.date_string,
					issue_date.date_string);


			  actions_proc(change_new, actions_index,
				actions_array, py_set_accrue_date);

			  break;

			}

			check_date1 = issue_date;

			actions_index ++;


			actions_proc(change_new, actions_index,
				actions_array, py_check_date);

			break;

		 }
		 case py_proc_val_date:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_date)
			{

			  actions_index --;


			  actions_proc(change_step, actions_index,
				actions_array, 0);

			  if (return_state != return_success)
			  {

				return_state = return_err_val_date_bad;
				////errproc(return_state,module_name,"","","");
				goto func_end;
			  }

			  break;

			}

			check_date1 = val_date;

			actions_index ++;


			actions_proc(change_new, actions_index,
				actions_array, py_check_date);

			break;

		 }
		 case py_check_date:
		 {

			/*{Make sure the date is valid.}*/

			return_state =  datechck(check_date1);

			actions_proc(change_step, actions_index,
				actions_array, 0);

			break;

		 }

		 case py_proc_def_dates:
		 {

			if (actions_array[actions_index].prev_action ==
				py_proc_mat_date)
			{


			  actions_proc(change_new, actions_index,	actions_array,
				py_proc_val_date);

					 break;

			}

			if (actions_array[actions_index].prev_action ==
				py_proc_val_date)
			{

			  actions_proc(change_new, actions_index,	actions_array,
				  py_check_val_vs_mat);

					 break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_val_vs_mat)
			{

			  /*{ If this is a discount instrument, set the issue date to the
			  value date and set the first and next to last dates to maturity
			  and issue  }*/

			  if ((in_instr.instr_class == instr_usdsc_class) ||
			  (in_instr.instr_class == instr_ukdsc_class) ||
			  (in_instr.instr_class == instr_uschatz_buba_class) ||
			  (in_instr.instr_class == instr_cp_class))
			  {

				 datecpy(in_instr.issue_date.date_string,
					val_date.date_string);
				 datecpy(in_instr.pre_last_pay.date_string,
					val_date.date_string);
				 datecpy(in_instr.pay_freq.first_date.date_string,
					mat_date.date_string);
				 datecpy(in_instr.mat_date.date_string,
					mat_date.date_string);

			  }
			  else
			  {

				/*{ Start with the next to last equal to maturity and maturity a
				year later. Make the first the maturity date two years before value,
				and issue date a year before that, then find the next and previous
				coupons.}*/

				 datecpy(date_union_hold.date_string, mat_date.date_string);

				str_cmp =  month_end(date_union_hold);

				return_state =  forecast(mat_date,
				  12,
				  0,
				  in_instr.cal_den,
				  &in_instr.mat_date);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				if (str_cmp == (int) mat_date.date.days)
				{

					if (current_monthend == monthend_no)
					{

					  in_instr.pay_freq.month_day = mat_date.date.days;

					}
					else
					{

					  in_instr.pay_freq.month_day = date_last_day_in_month;

					}

				}
				else
				{

					in_instr.pay_freq.month_day = mat_date.date.days;

				}

				 datecpy(in_instr.pre_last_pay.date_string,
					mat_date.date_string);

				return_state =  forecast(val_date,
				  -24,
				  0,
				  in_instr.cal_den,
				  &in_instr.pay_freq.first_date);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				in_instr.pay_freq.first_date.date.months =
					in_instr.pre_last_pay.date.months;

				in_instr.pay_freq.first_date.date.days =
					in_instr.pre_last_pay.date.days;

				if (in_instr.pay_freq.month_day == date_last_day_in_month)
				{
					in_instr.pay_freq.first_date.date.days =
					(char)  month_end(in_instr.pay_freq.first_date);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}
				}

				return_state =  forecast(in_instr.pay_freq.first_date,
				  -12,
				  0,
				  in_instr.cal_den,
				  &in_instr.issue_date);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				if (in_instr.pay_freq.month_day == date_last_day_in_month)
				{
					in_instr.issue_date.date.days =
					(char)  month_end(in_instr.issue_date);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}
				}

				return_state =  forecast(in_instr.pre_last_pay,
				  0,
				  -1,
				  date_act_cal,
				  &date_union_hold);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				return_state = n_p_pay(in_instr, 
					date_union_hold,
					&prev_date
					, &next_date
					, dummy_ui
//					, holi_parm
					,holiSet
					);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				 datecpy(in_instr.pre_last_pay.date_string, prev_date.date_string);

				/*{Reset maturity date.}*/

				 datecpy(in_instr.mat_date.date_string,
					mat_date.date_string);


			  }

//		 datecpy(&in_instr.accrue_date.date_string, &in_instr.issue_date.date_string);

//	         datecpy(in_instr.mat_date.date_string, mat_date->date_string);
			   datecpy(issue_date.date_string,
				in_instr.issue_date.date_string);
			   datecpy(penult_date.date_string,
				in_instr.pre_last_pay.date_string);
			   datecpy(first_date.date_string,
				in_instr.pay_freq.first_date.date_string);

			  actions_proc(change_new, actions_index,	actions_array,
				  py_set_accrue_date);

			  break;

			}

			if (actions_array[actions_index].prev_action ==
				py_set_accrue_date)
			{

			/* Set default excoup indicator based on derived  */
//
			  return_state = excoup( in_instr, 
				  val_date
				  , &ex_coup,
				  holi_chan
//				  , holi_parm
				,holiSet
				  );

			  if (return_state)
			  {

					////errproc(return_state,module_name,"","","");

					goto func_end;

			  }

			  if (ex_coup)
			  {

				 strcpy(current_excoup_name,
					excoup_names[ex_coup_yes]);

//				 current_excoup = (char)ex_coup_yes;

			  }
			  else
			  {


				 strcpy(current_excoup_name,
					excoup_names[ex_coup_no]);

//				 current_excoup = (char)ex_coup_no;

			  }

			  actions_proc(change_new, actions_index,	actions_array,
				  py_action_proc_excoup);

			  break;

			}

			if (actions_array[actions_index].prev_action ==
				py_action_proc_excoup)
			{

					 actions_index --;


			  actions_proc(change_step, actions_index,	actions_array,
				  0);

					 break;

			}

			if (in_instr.instr_class == instr_cashflow_class)
			{

				str_cmp =  datecmp(&val_date.date_string,
				pay_array_a[0].pay_date.date_string);

				if (str_cmp >= 0)
				{

					return_state = return_err_val_ge_cf;
					////errproc(return_state,module_name,"","","");
					goto func_end;

				}

				actions_proc(change_step, actions_index,	actions_array,
				  0);

				break;
			}

			actions_index ++;

			actions_proc(change_new, actions_index,	actions_array,
				  py_proc_mat_date);

			break;

		 }

		 case py_proc_gen_dates_frn:
		 {

			if (actions_array[actions_index].prev_action ==
				py_proc_mat_date)
			{


			  actions_proc(change_new, actions_index,	actions_array,
				py_proc_val_date);

					 break;

			}

			if (actions_array[actions_index].prev_action ==
				py_proc_val_date)
			{

			  actions_proc(change_new, actions_index,	actions_array,
				py_proc_iss_date);

					 break;

			}

			if (actions_array[actions_index].prev_action ==
				py_proc_iss_date)
			{

				  strcpy(in_instr.pay_freq.first_date.date_string,
					in_instr.issue_date.date_string);


				  actions_proc(change_new, actions_index,	actions_array,
					py_check_val_vs_mat);

					 break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_val_vs_mat)
			{


			  actions_proc(change_new, actions_index,	actions_array,
						py_proc_pay_freq_frn);

					 break;

			}
			if (actions_array[actions_index].prev_action ==
				py_proc_pay_freq_frn)
			{

			  actions_proc(change_new, actions_index,	actions_array,
								py_proc_holi);

					 break;


			}

			if (actions_array[actions_index].prev_action ==
				py_proc_holi)
			{

				 datecpy(rerate_sched.rerate_sched.first_date.date_string,
				  in_instr.issue_date.date_string);
/*
				rerate_sched.rerate_sched.month_day =
				  in_instr.pay_freq.first_date.date.days;
*/
				rerate_sched.rerate_sched.month_day =
				  in_instr.issue_date.date.days;

				rerate_sched.rerate_sched.period =
				  in_instr.pay_freq.period;

				in_instr.rerate_freq =
				rerate_sched.rerate_sched;

				/*{ Start with the next to last equal to maturity and maturity a
				year later. Make the first pay date value date, and issue date a
				year before that, then find the next and previous
				coupons.}*/

				 datecpy(date_union_hold.date_string, issue_date.date_string);

				str_cmp =  month_end(date_union_hold);

				return_state =  forecast(mat_date,
				  12,
				  0,
				  in_instr.cal_den,
				  &in_instr.mat_date);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				if (str_cmp == (int) issue_date.date.days)
				{

					in_instr.pay_freq.month_day = date_last_day_in_month;

				}
				else
				{

					in_instr.pay_freq.month_day = issue_date.date.days;

				}

				 datecpy(in_instr.pre_last_pay.date_string,
					mat_date.date_string);

				 datecpy(in_instr.pay_freq.first_date.date_string,
					issue_date.date_string);

				return_state =  forecast(issue_date,
				  -24,
				  0,
				  in_instr.cal_den,
				  &in_instr.issue_date);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}
/*
				in_instr.pay_freq.first_date.date.months =
					in_instr.pre_last_pay.date.months;

				in_instr.pay_freq.first_date.date.days =
					in_instr.pre_last_pay.date.days;

				if (in_instr.pay_freq.month_day == date_last_day_in_month)
				{
					in_instr.pay_freq.first_date.date.days =
					(char)  month_end(in_instr.pay_freq.first_date);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}
				}

				return_state =  forecast(in_instr.pay_freq.first_date,
				  -12,
				  0,
				  in_instr.cal_den,
				  &in_instr.issue_date);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				if (in_instr.pay_freq.month_day == date_last_day_in_month)
				{
					in_instr.issue_date.date.days =
					(char)  month_end(in_instr.issue_date);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}
				}
*/
				return_state =  forecast(in_instr.pre_last_pay,
				  0,
				  -1,
				  date_act_cal,
				  &date_union_hold);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				return_state = n_p_pay(in_instr
					, date_union_hold
					,&prev_date
					, &next_date
					, dummy_ui
//					, holi_parm
					,holiSet
					);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				 datecpy(in_instr.pre_last_pay.date_string, prev_date.date_string);

				return_state =  forecast(in_instr.pay_freq.first_date,
				  0,
				  1,
				  date_act_cal,
				  &date_union_hold);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				return_state = n_p_pay(in_instr
					, date_union_hold
					,&prev_date
					, &next_date
					, dummy_ui
///					, holi_parm
					,holiSet
					);

				if (return_state)
				{

					////errproc(return_state,module_name,"","","");

					goto func_end;

				}

				 datecpy(in_instr.pay_freq.first_date.date_string,
					next_date.date_string);

				/*{Reset maturity and issue  }*/

				 datecpy(in_instr.mat_date.date_string,
					mat_date.date_string);

				 datecpy(in_instr.issue_date.date_string,
					issue_date.date_string);
				 datecpy(penult_date.date_string,
				 in_instr.pre_last_pay.date_string);
				 datecpy(first_date.date_string,
				 in_instr.pay_freq.first_date.date_string);
/*
				 datecpy(rerate_sched.rerate_sched.first_date.date_string,
					in_instr.issue_date.date_string);

				rerate_sched.rerate_sched.month_day =
					in_instr.pay_freq.first_date.date.days;
*/
//
				actions_proc(change_new, actions_index,	actions_array,
				  py_set_current_frn);

					 break;

			}

			if (actions_array[actions_index].prev_action ==
				py_set_current_frn)
			{
//

			  actions_proc(change_new, actions_index,	actions_array,
				  py_set_accrue_date);

					 break;

			}

			if (actions_array[actions_index].prev_action ==
				py_set_accrue_date)
			{

				actions_proc(change_new, actions_index,	actions_array,
				  py_calc_np);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_calc_np)
			{
//
				rerate_sched.rerate_sched.period =
					in_instr.pay_freq.period;
//
				rerate_sched.pay_type = instr_float_pay_type;

//				strcpy(holi_parm[0].holi_code,in_instr.holiday_code);

				return_state = schedgen(rerate_sched.rerate_sched,
					rate_array,
					prev_coup,
					next_coup,
//					dummy_date1,
					rerate_sched.holi_chan
//					,holi_parm
					,holiSet
					, rerate_sched.pay_type
					);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}

					actions_index --;

//
					actions_proc(change_step, actions_index,	actions_array,
										0);

					break;
//
			}

			actions_index ++;
			actions_proc(change_new, actions_index,	actions_array, py_proc_mat_date);

			break;




		 }
		 case py_check_val_vs_mat:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_tenor)
			{

					 actions_index --;


			  actions_proc(change_step, actions_index,	actions_array,
					  0);

			  break;

			}

			str_cmp =  datecmp(&mat_date.date_string,
			&val_date.date_string);

			if (str_cmp <= 0)
			{


			  return_state = return_err_val_gt_mat;

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}
			actions_index ++;


			actions_proc(change_new, actions_index,	actions_array,
			  py_check_tenor);

				  break;

		 }

		 case py_check_val_vs_first_date_frn:
		 {

			str_cmp =  datecmp(&val_date.date_string,
			rerate_sched.rerate_sched.first_date.date_string);

			if (str_cmp < 0)
			{


			  return_state = return_err_iss_gt_val;

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}


			actions_proc(change_step, actions_index,	actions_array,
			  0);

			break;

		 }
		 case py_check_iss_vs_mat:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_tenor)
			{

				actions_index --;


				actions_proc(change_step, actions_index,	actions_array,
				 0);

				break;

			}

			str_cmp =  datecmp(&mat_date.date_string,
			&issue_date.date_string);

			if (str_cmp <= 0)
			{


			  return_state = return_err_iss_gt_mat;

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}
			actions_index ++;

			actions_proc(change_new, actions_index,	actions_array,
				 py_check_tenor);

				  break;

		 }
		 case py_check_iss_vs_first:
		 {

			str_cmp =  datecmp(&first_date.date_string,
			&issue_date.date_string);

			if (str_cmp <= 0)
			{


			  return_state = return_err_iss_ge_first;

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}


			actions_proc(change_step, actions_index,	actions_array,
				 0);

			break;

		 }
		 case py_check_first_vs_mat:
		 {

			str_cmp =  datecmp(&first_date.date_string,
			&mat_date.date_string);

			if (str_cmp > 0)
			{


			  return_state = return_err_first_gt_mat;

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}


			actions_proc(change_step, actions_index,	actions_array,
				 0);

			break;

		 }
		 case py_check_iss_vs_penult:
		 {

			str_cmp =  datecmp(&penult_date.date_string,
			&issue_date.date_string);

			if (str_cmp < 0)
			{


			  return_state = return_err_iss_gt_penult;

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}


			actions_proc(change_step, actions_index,	actions_array,
				 0);

			break;

		 }
		 case py_check_iss_vs_val:
		 {

			str_cmp =  datecmp(&val_date.date_string,
			&issue_date.date_string);

			if (str_cmp < 0)
			{


				return_state = return_err_iss_gt_val;

				////errproc(return_state,module_name,"","","");

				goto func_end;

			}


			actions_proc(change_step, actions_index,	actions_array,
				 0);

			break;

		 }
		 case py_check_penult_vs_mat:
		 {

			str_cmp =  datecmp(&penult_date.date_string,
			&mat_date.date_string);

			if (str_cmp >= 0)
			{


			  return_state = return_err_penult_ge_mat;

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}


			actions_proc(change_step, actions_index,	actions_array,
				 0);

			break;

		 }
		 case py_check_date_synch:
		 {

			if (actions_array[actions_index].prev_action ==
			py_proc_day_count)
			{

				/*{ Check that the dates are synchronized.}*/


				/*{ If set to issue and maturity dates, skip check. }*/

				str_cmp =  datecmp(&in_instr.pre_last_pay.date_string,
				&in_instr.issue_date.date_string);

				str_cmp2 =  datecmp(&in_instr.pay_freq.first_date.date_string,
				&in_instr.mat_date.date_string);

				if ((str_cmp != 0) || (str_cmp2 != 0))
				{

				  /*{ Start with the next to last and maturity four years later. }*/

					 datecpy(date_union_hold.date_string,
					in_instr.pre_last_pay.date_string);

					str_cmp =  month_end(date_union_hold);

					return_state =  forecast(in_instr.mat_date,
						48,
						0,
						in_instr.cal_den,
						&in_instr.mat_date);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}

					return_state =  forecast(in_instr.pre_last_pay,
						48,
						0,
						in_instr.cal_den,
						&in_instr.pre_last_pay);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}

					if (str_cmp == (int) in_instr.pre_last_pay.date.days)
					{

						in_instr.pay_freq.month_day = date_last_day_in_month;

					}
					else
					{

						in_instr.pay_freq.month_day = in_instr.pre_last_pay.date.days;

					}

					/*{ If previous date on the next to last date does not equal the next
					to last date, dates are not in synch.}*/

					return_state = n_p_pay(in_instr
						, date_union_hold
						, &prev_date
						,&next_date
						, dummy_ui
//						, holi_parm
						,holiSet
						);


					if (return_state)
					{

						/*{ Dates are not in synch. }*/

						/*{ reload original   }*/

						return_state =  forecast(in_instr.mat_date,
							-48,
							0,
							in_instr.cal_den,
							&in_instr.mat_date);

					  if (return_state)
					  {

						////errproc(return_state,module_name,"","","");

						goto func_end;

					  }

					  return_state =  forecast(in_instr.pre_last_pay,
						-48,
						0,
						in_instr.cal_den,
						&in_instr.pre_last_pay);

					  if (return_state)
					  {

							////errproc(return_state,module_name,"","","");

							goto func_end;

					  }

						return_state = return_err_dates_out_synch ;

						goto func_end;

					}


					/*{ reload original   }*/

					return_state =  forecast(in_instr.mat_date,
						-48,
						0,
						in_instr.cal_den,
						&in_instr.mat_date);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}

					return_state =  forecast(in_instr.pre_last_pay,
						-48,
						0,
						in_instr.cal_den,
						&in_instr.pre_last_pay);

					if (return_state)
					{

						////errproc(return_state,module_name,"","","");

						goto func_end;

					}

					str_cmp =  datecmp(date_union_hold.date_string,
					prev_date.date_string);

					if (str_cmp != 0)
					{
						/*{ Dates are not in synch. }*/

						return_state = return_err_dates_out_synch ;

						goto func_end;

					}
				}

				actions_index --;


				actions_proc(change_step, actions_index,	actions_array,
				 0);

				break;

			}

			actions_index ++;


			actions_proc(change_new, actions_index,	actions_array,
				 py_proc_day_count);

			break;


		 }
		 case py_check_tenor:
		 {

			return_state =  tenor 	(val_date,
						mat_date,
				date_act_cal,
				&tenor_days);

			if (return_state)
			{

			  ////errproc(return_state,module_name,"","","");

				goto func_end;

			}

			if ((tenor_days/365) > 50)
			{

			  return_state = return_info_max_mat_exc;

			  ////errproc(return_state,module_name,"","","");

			  goto func_end;

			}

			actions_proc(change_step, actions_index,	actions_array,
				 0);

			break;

		 }
		 case py_proc_penult_date:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_date)
			{

			  actions_index --;


			  actions_proc(change_step, actions_index,	actions_array,
				 0);

			  if (return_state != return_success) {

				return_state = return_err_penult_date_bad;
				////errproc(return_state,module_name,"","","");
				goto func_end;
			  }

			   datecpy(in_instr.pre_last_pay.date_string,
					penult_date.date_string);

			  break;

			}

			check_date1 = penult_date;

			actions_index ++;


			actions_proc(change_new, actions_index,	actions_array,
				 py_check_date);

			break;

		 }
		 case py_proc_first_date:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_date)
			{

				actions_index --;


				actions_proc(change_step, actions_index,	actions_array,
				 0);

				if (return_state != return_success) {

					return_state = return_err_first_date_bad;
					////errproc(return_state,module_name,"","","");
					goto func_end;
				}

				 datecpy(in_instr.pay_freq.first_date.date_string,
				first_date.date_string);

				break;

			}

			check_date1 = first_date;

			actions_index ++;

			actions_proc(change_new, actions_index,	actions_array,
				 py_check_date);

			break;

		 }
		 case py_proc_first_date_frn:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_date)
			{

			  actions_index --;

			  actions_proc(change_step, actions_index,	actions_array,
				 0);

			  if (return_state != return_success) {

				return_state = return_err_first_date_bad;
				////errproc(return_state,module_name,"","","");
				goto func_end;
			  }

			   datecpy(in_instr.rerate_freq.first_date.date_string,
			  rerate_sched.rerate_sched.first_date.date_string);

			  break;

			}

			 datecpy(check_date1.date_string,
			rerate_sched.rerate_sched.first_date.date_string);

			actions_index ++;

			actions_proc(change_new, actions_index,	actions_array,
				 py_check_date);

			break;

		 }
		 case py_proc_all_dates:
		 {

			if (actions_array[actions_index].prev_action ==
			py_proc_val_date)
			{

				if (current_class == instr_cashflow_class)

				{

					actions_index --;


					actions_proc(change_step, actions_index,	actions_array,
						 0);

					break;

				}
				else
				{


					actions_proc(change_new, actions_index,	actions_array,
						 py_proc_iss_date);

					break;
				}

			}

			if (actions_array[actions_index].prev_action ==
				py_proc_iss_date)
			{

				actions_proc(change_new, actions_index,	actions_array,
						py_proc_penult_date);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_proc_penult_date)
			{

				actions_proc(change_new, actions_index,	actions_array,
						 py_proc_first_date);

					 break;

			}

			if (actions_array[actions_index].prev_action ==
				py_proc_first_date)
			{

				actions_proc(change_new, actions_index,	actions_array,
						py_proc_mat_date);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_proc_mat_date)
			{

				actions_proc(change_new, actions_index,	actions_array,
					  py_check_val_vs_mat);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_val_vs_mat)
			{

				actions_proc(change_new, actions_index,	actions_array,
							py_check_iss_vs_first);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_iss_vs_first)
			{

				actions_proc(change_new, actions_index,	actions_array,
										  py_check_first_vs_mat);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_first_vs_mat)
			{


				actions_proc(change_new, actions_index,	actions_array,
							py_check_iss_vs_penult);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_iss_vs_penult)
			{

				actions_proc(change_new, actions_index,	actions_array,
							py_check_penult_vs_mat);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_penult_vs_mat)
			{

				actions_proc(change_new, actions_index,	actions_array,
									py_check_iss_vs_val);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_iss_vs_val)
			{

				actions_proc(change_new, actions_index,	actions_array,
						  py_check_iss_vs_mat);

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_iss_vs_mat)
			{

				if (in_instr.pay_type != instr_float_pay_type)
				{

				  actions_proc(change_new, actions_index,	actions_array,
									  py_check_date_synch);

				}
				else
				{

				  actions_index --;

				  actions_proc(change_step, actions_index,	actions_array, 0);

				}

				break;

			}

			if (actions_array[actions_index].prev_action ==
				py_check_date_synch)
			{

				actions_index --;


				actions_proc(change_step, actions_index,	actions_array,
									  0);

				break;

			}

			actions_index ++;

			actions_proc(change_new, actions_index,	actions_array,
							py_proc_val_date);

			break;

		 }
		 case py_check_all_parms:
		 {

			if (actions_array[actions_index].prev_action ==
				py_proc_day_count)
			{

				actions_proc(change_new, actions_index,	actions_array,
							py_proc_all_dates);

				break;

			}
			if (actions_array[actions_index].prev_action ==
				py_proc_all_dates)
			{

				actions_proc(change_new, actions_index,	actions_array,
							py_proc_yield_meth);

				break;

			}
			if (actions_array[actions_index].prev_action ==
				py_proc_yield_meth)
			{

			  actions_proc(change_new, actions_index,	actions_array,
										  py_proc_int);

			  break;

			}
			if (actions_array[actions_index].prev_action ==
				py_proc_int)
			{

			  actions_proc(change_new, actions_index,	actions_array,
						  py_proc_price);

			  break;

			}
			if (actions_array[actions_index].prev_action ==
				py_proc_price)
			{

			  actions_proc(change_new, actions_index,	actions_array,
					  py_check_price_vs_calc);

			  break;

			}
			if (actions_array[actions_index].prev_action ==
				py_check_price_vs_calc)
			{

			  actions_proc(change_new, actions_index,	actions_array,
								  py_proc_calc_what);

			  break;

			}
			if (actions_array[actions_index].prev_action ==
				py_proc_calc_what)
			{

			  actions_proc(change_new, actions_index,	actions_array,
					  py_calc_np);

			  break;

			}
			if (actions_array[actions_index].prev_action ==
				py_calc_np)
			{

			  actions_proc(change_new, actions_index,	actions_array,
				py_action_proc_part_pay);

			  break;

			}
			if (actions_array[actions_index].prev_action ==
				py_action_proc_part_pay)
			{

				actions_index --;


				actions_proc(change_step, actions_index,	actions_array,
						0);

				break;

			}

			actions_index ++;

			actions_proc(change_new, actions_index,	actions_array,
						py_proc_day_count);

			break;

		 }
		 case py_proc_int:
		 {

			if (current_class != instr_cashflow_class)

			{

//			  in_instr.rate_offset = int_rate;
			  in_instr.rate_offset = int_rate - service_fee;


			  if (((in_instr.instr_class == instr_usdsc_class) ||
				(in_instr.instr_class == instr_ukdsc_class) ||
				(in_instr.instr_class == instr_uschatz_buba_class) ||
				(in_instr.instr_class == instr_cp_class)) &&
				(in_instr.rate_offset != 0))
			  {

				return_state = return_err_non_zero_disc;
				////errproc(return_state,module_name,"","","");
				goto func_end;

			  }

			  if (in_instr.rate_offset < 0)
			  {

				return_state = return_err_neg_int;
				////errproc(return_state,module_name,"","","");
				goto func_end;

			  }

			  if (in_instr.rate_offset >= (py_max_int/100))
			  {

				return_state = return_err_int_too_high;
				//errproc(return_state,module_name,"","","");
				goto func_end;

			  }
			}


			actions_proc(change_step, actions_index,	actions_array,
						0);

			break;

		 }

		 case py_proc_calc_what:
		 {

			pyparm.calc_what = calc_what;

			if ((calc_what != py_yield_from_price_calc_what) &&
				(calc_what != py_price_from_yield_calc_what))
			{

				return_state = return_err_calc_what_inv;
				//errproc(return_state,module_name,"","","");
				goto func_end;

			}



			  actions_proc(change_step, actions_index,	actions_array,
						0);

			  break;

		 }

		 case py_proc_price:
		 {


			  actions_proc(change_step, actions_index,	actions_array,
						0);

			  break;

		 }

		 case py_check_price_vs_calc:
		 {

			if ((calc_what == py_yield_from_price_calc_what) &&
			(in_price <= 0))
			{

				return_state = return_err_price_le_zero;
				//errproc(return_state,module_name,"","","");
				goto func_end;

			}


			actions_proc(change_step, actions_index,	actions_array,
						0);

			break;

		 }
		 case py_calc_np:
		 {

			if (current_class != instr_cashflow_class)

			{

				return_state = n_p_pay(in_instr
					, val_date
					, &prev_coup
					,&next_coup
					, dummy_ui
//					, holi_parm
					,holiSet
					);

				if (return_state)
				{

					//errproc(return_state,module_name,"","","");
					goto func_end;

				}

			}


			actions_proc(change_step, actions_index,	actions_array,
						0);

			break;

		 }
		 case py_prepay_type_init:
		 {

			for (element_count = 0; element_count <
			py_last_prepay_type; ++element_count)
			{
				strcpy(prepay_type_choice[element_count],
				prepay_type_names[element_count]);
			}


			actions_proc(change_step, actions_index,	actions_array,
						0);

			break;

		 }
		 case py_action_end:
		 {

			break;

		 }
		 case py_proc_service:
		 {

			in_instr.service_fee = service_fee;


			actions_proc(change_step, actions_index,	actions_array,
						0);

			break;

		 }

		 case py_proc_prepay_type:
		 {

			if ( strcmp(prepay_type_name,
				prepay_type_names[py_cpr_prepay_type]) == 0 )
			{

				pyparm.cpr_rate = cpr_rate/100;

			}
			else
			{
				if ( strcmp(prepay_type_name,
					prepay_type_names[py_smm_prepay_type]) == 0 )
				{

					pyparm.prepay_type = py_smm_prepay_type;

					pyparm.cpr_rate = 1 - pow((1 - (cpr_rate/100)),12);


				}
			}


			actions_proc(change_step, actions_index,	actions_array,
						0);

			break;

		 }
		 case py_proc_prepay_rate:
		 {

			if (actions_array[actions_index].prev_action ==
				py_proc_prepay_type)
			{

			  actions_index --;


			  actions_proc(change_step, actions_index,	actions_array,
						0);

			  break;

			}

			if ((cpr_rate < 0) || (cpr_rate >= 100))
			{

				return_state = return_err_cpr_out_range;
				//errproc(return_state,module_name,"","","");
				goto func_end;

			}

			actions_index ++;


			actions_proc(change_new, actions_index,	actions_array,
						py_proc_prepay_type);

			break;

		 }
		 case py_proc_lag:
		 {

			if ((lag < 0) || (lag > 100))
			{

				return_state = return_err_lag_out_range;
				//errproc(return_state,module_name,"","","");
				goto func_end;

			}

			in_instr.lag = (char)lag;

			actions_proc(change_step, actions_index,	actions_array,
						0);

			break;

		 }
		 case py_proc_cashflow:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_date)
			{

				if (return_state == return_err_date_bad)
				{

					bad_date_found = istrue;
					 datecpy(pay_array_a[element_count].pay_date.date_string,
						zero_date);
					pay_array_a[element_count].payment = 0;

					return_state = return_success;

					if ((element_count < py_max_cashflow) &&
						(element_count < max_coups)	&&
//						(element_count < rate_array[0].event))
						(element_count < rate_array[0].event_date.date.centuries))
					{

						actions_proc(change_new, actions_index,	actions_array,
						py_check_date);

						element_count = element_count + 1;

						 datecpy(check_date1.date_string,
						rate_array[element_count].event_date.date_string);

						break;

					}
					else
					{

						actions_index --;


						actions_proc(change_step, actions_index,	actions_array,
							0);

						break;

					}

				}
				else
				{
					if (return_state != return_success)
					{

						//errproc(return_state,module_name,"","","");
						goto func_end;

					}
					else
					{

						if (bad_date_found == istrue)
						{

							return_state = return_err_nonasc_datelist;
							//errproc(return_state,module_name,"","","");
							goto func_end;

						}
						else
						{

							str_cmp =  datecmp(date_union_hold.date_string,
							rate_array[element_count].event_date.date_string);

							if (str_cmp >= 0)
							{

								return_state = return_err_nonasc_datelist;
								//errproc(return_state,module_name,"","","");
								goto func_end;

							}

							 datecpy(date_union_hold.date_string,
							rate_array[element_count].event_date.date_string);
							 datecpy(pay_array_a[element_count].pay_date.date_string,
							rate_array[element_count].event_date.date_string);
							pay_array_a[element_count].payment =
							rate_array[element_count].rate;
							pay_array_a[0].last_element = element_count;

							if ((element_count < py_max_cashflow) &&
								(element_count < max_coups))
							{

								actions_proc(change_new, actions_index,	actions_array,
								py_check_date);

								element_count = element_count + 1;

								 datecpy(check_date1.date_string,
								rate_array[element_count].event_date.date_string);

								break;

							}
							else
							{

								actions_index --;


								actions_proc(change_step, actions_index,	actions_array,
									0);

								break;
							}
						}
					}
				}
			}

//			element_count = 0;
			element_count = 1;

			actions_index ++;

			actions_proc(change_new, actions_index,	actions_array,
						py_check_date);

			 datecpy(check_date1.date_string,
			 rate_array[element_count].event_date.date_string);

			 datecpy(date_union_hold.date_string,
			zero_date);

			break;

		 }
		 case py_set_accrue_date:
		 {
			if (in_instr.instr_class == instr_goj_class)
			{

			  return_state =  forecast(in_instr.issue_date,
				0,
				-1,
				in_instr.cal_num,
				&in_instr.accrue_date);

			  if (return_state)
			  {

				//errproc(return_state,module_name,"","","");
				goto func_end;

			  }
			}
			else
			{
				 datecpy(in_instr.accrue_date.date_string,
					in_instr.issue_date.date_string);
			}


			actions_proc(change_step, actions_index,	actions_array,
						0);

			break;
		 }
		 case py_calc_int:
		 {

			if (actions_array[actions_index].prev_action ==
			py_check_all_parms)
			{

				return_state =
					intcalc(in_instr,
						val_date,
						&interest,
						&interest_days,
						dummy_ui,
//						ex_coup_auto,
						current_excoup,
						int_no_total_per,
						&nominal_adjust,
						&dummy_long_double,
						int_no_redemp_adj,
						dummy_ui,
//						holi_parm,
						holiSet,
						rate_array,
						&dummy_long_double);

				if (return_state)
				{

					//errproc(return_state,module_name,"","","");
					goto func_end;

				}

				if (pyparm.parm_use == py_yes_parm_use &&
				pyparm.calc_first == py_no_calc_first)
				{

				  return_state =
					intcalc(in_instr,
						next_coup,
						&first_int,
						&interest_days,
						dummy_ui,
						current_excoup,
						int_yes_total_per,
						&nominal_adjust,
						&dummy_long_double,
						int_no_redemp_adj,
						dummy_ui,
//						holi_parm,
						holiSet,
						rate_array,
						&dummy_long_double);

				  if (return_state)
				  {

					 //errproc(return_state,module_name,"","","");
					 goto func_end;

				  }

				  first_int = first_int - interest;
				  interest = 0;
				  interest_days = 0;

				}
				else
				{
				  first_int = 0;

				}

				actions_index --;

				actions_proc(change_step, actions_index,	actions_array,
						0);

				break;

			}

			if (in_instr.instr_class == instr_cashflow_class)
			{


				actions_proc(change_step, actions_index,	actions_array,
							0);

				break;

			}

			actions_index ++;


			actions_proc(change_new, actions_index,	actions_array,
									py_check_all_parms);

			break;
		 }
		 case py_calc_py:
		 {

			if (actions_array[actions_index].prev_action ==
				py_check_all_parms)
			{
//

				actions_proc(change_new, actions_index,	actions_array,
												  py_proc_cashflow);


				if (current_class == instr_cashflow_class)
				{
					break;
				}

			}
			if (
				(actions_array[actions_index].prev_action ==
				py_proc_cashflow)
				||
				(actions_array[actions_index].curr_action ==
				py_proc_cashflow)
					 )
			{
//
				if (in_instr.pay_type != instr_float_pay_type)
				{


					return_state =  py_calc(in_instr,val_date, &in_price,
						&out_price, &interest, &first_int, &nominal_adjust,
						&in_yield, &out_yield, pyparm, 0, dummy_ui, dummy_ui,
						&duration_hold, &modified_duration_hold
//						, holi_parm
						,holiSet
						,&conv, &pvbp_out, redemps_array_parm, rate_array
						,pay_array_a,
						part_pay_array_a,
						even_redemps
					);

					if (return_state)
					{

						//errproc(return_state,module_name,"","","");
						goto func_end;

					}

				}
				else
				{

					out_yield = 0;
					duration_hold = 0;
					modified_duration_hold = 0;
					conv = 0;
					pvbp_out = 0;

				}

				actions_index --;


				actions_proc(change_step, actions_index,	actions_array,
												  0);

				break;

			}

			actions_index ++;

			actions_proc(change_new, actions_index,	actions_array,
							py_check_all_parms);

			break;
		}

		default:
		{

			return_state = return_err_inv_act;

			//errproc(return_state,module_name,"","","");

			goto func_end;

			break;

		}

	  }
	}


func_end:

//  *py_parm = pyparm;
//  *instr_parm = in_instr;
//   datecpy(val_date.date_string,date.date_string);
//   datecpy(mat_date.date_string,mat_date_loc.date_string);
//   datecpy(issue_date.date_string,iss_date_loc.date_string);
//   datecpy(first_date.date_string,first_date_loc.date_string);
//   datecpy(penult_date.date_string,penult_date_loc.date_string);


//	extra_parms->int_rate = int_rate;
//	extra_parms->in_price = in_price;
//	extra_parms->in_yield = in_yield;
//	extra_parms->out_price = out_price;
//	extra_parms->out_yield = out_yield;
//	extra_parms->calc_what = calc_what;
//	extra_parms->prepay_type = prepay_type;
//	extra_parms->cpr_rate = cpr_rate;
//	extra_parms->current_factor = current_factor;
//	extra_parms->service_fee = service_fee;
//	extra_parms->lag = lag;
//	 datecpy(extra_parms->mat_date.date_string,mat_date_parm.date_string);
//	 datecpy(extra_parms->val_date_parm.date_string,val_date_parm.date_string);
//	 datecpy(extra_parms->penult_date.date_string,penult_date_parm.date_string);
//	 datecpy(extra_parms->issue_date.date_string,issue_date_parm.date_string);
//	 datecpy(extra_parms->first_date.date_string,first_date_parm.date_string);
//	 datecpy(extra_parms->prev_coup.date_string,prev_coup_parm.date_string);
//	 datecpy(extra_parms->next_coup.date_string,next_coup_parm.date_string);
//	extra_parms->interest = interest;
//	extra_parms->interest_days = interest_days;
//	extra_parms->nominal_adjust = nominal_adjust;
//	extra_parms->duration_hold = duration_hold;
//	extra_parms->modified_duration_hold = modified_duration_hold;
//	extra_parms->conv = conv;
//	extra_parms->pvbp_out = pvbp_out;
//	extra_parms->first_int = first_int;


  return return_state;
}

void Py_Front::actions_proc(char change, int actions_index,
	actions actions_array[4], char new_action)
{
  if  (change == change_new)
  {

		  actions_array[actions_index].prev_action =
		  actions_array[actions_index - 1].curr_action;
		  actions_array[actions_index].next_action =
		  actions_array[actions_index - 1].curr_action;
		  actions_array[actions_index].curr_action = new_action;

  }
  else
  {
			actions_array[actions_index].prev_action =
			actions_array[actions_index].curr_action;
			actions_array[actions_index].curr_action =
			actions_array[actions_index].next_action;
  }

  return;


}

unsigned long  _FAR_FUNC _EX_IN_FUNC Py_Front::proc_def_dates()
{

action = py_proc_def_dates;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_calc_what()
{

action = py_proc_calc_what;
return pyproc45();

}
unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::init_screen()
{

action = py_action_init_screen;
return pyproc45();

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::proc_pay_freq	()
{

action = py_proc_pay_freq;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_monthend()
{

action = py_action_proc_monthend;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_excoup()
{

action = py_action_proc_excoup;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_class_desc()
{

action = py_proc_class_desc;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_day_count()
{

action = py_proc_day_count;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_yield_meth()
{

action = py_proc_yield_meth;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_yield_days()
{

action = py_proc_yield_days;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_yield_freq()
{

action = py_proc_yield_freq;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::check_all_parms()
{

action = py_check_all_parms;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::calc_int()
{

action = py_calc_int;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::calc_py()
{

action = py_calc_py;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_simp_comp_frn()
{

action = py_proc_simp_comp_frn;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_pay_freq_frn()
{

action = py_proc_pay_freq_frn;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_holi()
{

action = py_proc_holi;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_gen_dates_frn()
{

action = py_proc_gen_dates_frn;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::init_frn()
{

action = py_init_frn;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::init_mbs()
{

action = py_action_init_mbs;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::proc_mbs()
{

action = py_action_proc_mbs;
return pyproc45();

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setmatdate(char mat_date_str [date_str_size])
{

  return  dateconv(date_format_1, dateconv_string_to_union,
		mat_date_str, &mat_date, &work_double);

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setmatdate(Date_Funcs::date_union &date)
{

	mat_date = date;
	return return_success;

}
unsigned long  _FAR_FUNC _EX_IN_FUNC   Py_Front::getmatdate(Date_Funcs::date_union &date)
{

	date = mat_date;
	return return_success;
}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setvaldate(char val_date_str [date_str_size])
{

  return  dateconv(date_format_1, dateconv_string_to_union,
		val_date_str, &val_date, &work_double);

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setvaldate(Date_Funcs::date_union &date)
{

	val_date = date;
	return return_success;

}
unsigned long  _FAR_FUNC _EX_IN_FUNC   Py_Front::getvaldate(Date_Funcs::date_union &date)
{

	date = val_date;
	return return_success;
}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::getpenultdate(char penult_date_str [date_str_size])
{


	return  dateconv(date_format_1, dateconv_union_to_string,
		penult_date_str, &penult_date, &work_double);

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setpenultdate(Date_Funcs::date_union &date)
{

	penult_date = date;
	return return_success;

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setpenultdate(char penult_date_str [date_str_size])
{


	return  dateconv(date_format_1, dateconv_string_to_union,
		penult_date_str, &penult_date, &work_double);

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setissuedate(Date_Funcs::date_union &date)
{

	issue_date = date;
	return return_success;

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setissuedate(char issue_date_str [date_str_size])
{


	return  dateconv(date_format_1, dateconv_string_to_union,
		issue_date_str, &issue_date, &work_double);

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::getissuedate(char issue_date_str [date_str_size])
{


	return  dateconv(date_format_1, dateconv_union_to_string,
		issue_date_str, &issue_date, &work_double);

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::getfirstdate(char first_date_str [date_str_size])
{


	return  dateconv(date_format_1, dateconv_union_to_string,
		first_date_str, &first_date, &work_double);

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setfirstdate(Date_Funcs::date_union &date)
{

	first_date = date;
	return return_success;

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setfirstdate(char first_date_str [date_str_size])
{


	return  dateconv(date_format_1, dateconv_string_to_union,
		first_date_str, &first_date, &work_double);

}

unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::getexcoup(char excoup_name_str [excoup_name_length])
{
	return_state = return_success;
	strcpy(excoup_name_str, current_excoup_name);
	return return_state;
}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setsimpcomp (char simp_comp_str[simp_comp_names_len])
{

	return_state = return_success;
	strcpy(rerate_sched.current_simp_comp_name, simp_comp_str);
	return return_state;

}
unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::setexcoup(char excoup_name_str [excoup_name_length])
{

	return_state = return_success;
	strcpy(current_excoup_name, excoup_name_str);
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getexcoupchoice(int element_count,char excoup_name_str[excoup_name_length])
{

	return_state = return_success;
	strcpy(excoup_name_str, excoup_choice [element_count]);
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getsinkmatchoice(int element_count,
	char sink_mat_str[redemp_sched_names_len])
{

	return_state = return_success;
	strcpy(sink_mat_str, sink_fund_mat_choice [element_count]);
	return return_state;

}



unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getcalcwhat(char *current_calc_what)
{

	return_state = return_success;
	*current_calc_what = calc_what;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setcalcwhat(char current_calc_what)
{

	return_state = return_success;
	calc_what = current_calc_what;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getintrate(long double *intrateparm)
{

	return_state = return_success;
	*intrateparm = int_rate;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setintrate(long double intrateparm)
{

	return_state = return_success;
	int_rate = intrateparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getinprice(long double *inpriceparm)
{

	return_state = return_success;
	*inpriceparm = in_price;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setinprice(long double inpriceparm)
{

	return_state = return_success;
	in_price = inpriceparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getinyield(long double *inyieldparm)
{

	return_state = return_success;
	*inyieldparm = in_yield;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setinyield(long double inyieldparm)
{

	return_state = return_success;
	in_yield = inyieldparm;
	return return_state;

}


unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getoutprice(long double *outpriceparm)
{

	return_state = return_success;
	*outpriceparm = out_price;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setoutprice(long double outpriceparm)
{

	return_state = return_success;
	out_price = outpriceparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getoutyield(long double *outyieldparm)
{

	return_state = return_success;
	*outyieldparm = out_yield;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setoutyield(long double outyieldparm)
{

	return_state = return_success;
	out_yield = outyieldparm;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getcprrate(long double *cprrateparm)
{

	return_state = return_success;
	*cprrateparm = cpr_rate;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setcprrate(long double cprrateparm)
{

	return_state = return_success;
	cpr_rate = cprrateparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getcurrentfactor(long double *currentfactorparm)
{

	return_state = return_success;
	*currentfactorparm = current_factor;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setcurrentfactor(long double currentfactorparm)
{

	return_state = return_success;
	current_factor = currentfactorparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getservicefee(long double *servicefeeparm)
{

	return_state = return_success;
	*servicefeeparm = service_fee;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setservicefee(long double servicefeeparm)
{

	return_state = return_success;
	service_fee = servicefeeparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getlag(long double *lagparm)
{

	return_state = return_success;
	*lagparm = lag;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setlag(long double lagparm)
{

	return_state = return_success;
	lag = lagparm;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setclassdesc(int class_number,
	char classdescparm [instr_class_desc_len])
{
	return_state = return_success;
	strcpy(instr_class_descs[class_number], classdescparm);
	return return_state;
}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getprepay(char *prepaytypeparm)
{

	return_state = return_success;
	*prepaytypeparm = prepay_type;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setprepay(char prepaytypeparm)
{

	return_state = return_success;
	prepay_type = prepaytypeparm;
	return return_state;

}
unsigned long  _FAR_FUNC _EX_IN_FUNC   Py_Front::getprepayname( char prepayparm [prepay_type_names_len])
{
	return_state = return_success;
	strcpy(prepayparm,  prepay_type_choice[prepay_type]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setclassdesc(char classdescparm [instr_class_desc_len])
{
	return_state = return_success;
	strcpy(current_class_desc, classdescparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getclassdesc(int class_number,
	char classdescparm [instr_class_desc_len])
{
	return_state = return_success;
	strcpy(classdescparm, instr_class_descs[class_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getclassdesc(char classdescparm [instr_class_desc_len])
{
	return_state = return_success;
	strcpy(classdescparm, instr_class_descs[current_class]);
	return return_state;
}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getclassnumber(char *classnumberparm)
{

	return_state = return_success;
	*classnumberparm = current_class;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setclassnumber(char classnumberparm)
{

	return_state = return_success;
	current_class = classnumberparm;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setdaycount(int daycount_number,
	char daycountparm [day_count_names_len])
{
	return_state = return_success;
	strcpy(day_count_names[daycount_number], daycountparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getdaycount(int daycount_number,
	char daycountparm [day_count_names_len])
{
	return_state = return_success;
	strcpy(daycountparm, day_count_names[daycount_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setdaycount(char daycountparm [day_count_names_len])
{
	return_state = return_success;
	strcpy(current_day_count_name, daycountparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getdaycount(char daycountparm [day_count_names_len])
{
	return_state = return_success;
	strcpy(daycountparm, current_day_count_name);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setdaycount(int daycount_number)
{
	return_state = return_success;
	current_day_count = daycount_number;
	strcpy(current_day_count_name,day_count_names[daycount_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getdaycount(int *daycount_number)
{
	return_state = return_success;
	*daycount_number = current_day_count;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setpayfreq(int payfreq_number)
{
	return_state = return_success;
	current_pay_freq = payfreq_number;
	strcpy(current_pay_freq_name,freq_names[payfreq_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getpayfreq(int *payfreq_number)
{
	return_state = return_success;
	*payfreq_number = current_pay_freq;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setpayfreq(int payfreq_number,
	char payfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(freq_names[payfreq_number], payfreqparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getpayfreq(int payfreq_number,
	char payfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(payfreqparm, freq_names[payfreq_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getpayfreq(char payfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(payfreqparm, freq_names[current_pay_freq]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setpayfreq(char payfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(current_pay_freq_name, payfreqparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setmonthend(char monthendparm [monthend_names_len])
{
	return_state = return_success;
	strcpy(current_monthend_name, monthendparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setmonthend(int monthend_number,
	char monthendparm [monthend_names_len])
{
	return_state = return_success;
	strcpy(monthend_names[monthend_number], monthendparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getmonthend(int monthend_number,
	char monthendparm [monthend_names_len])
{
	return_state = return_success;
	strcpy(monthendparm, monthend_names[monthend_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getmonthend(char monthendparm [monthend_names_len])
{
	return_state = return_success;
	strcpy(monthendparm, monthend_names[current_monthend]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyieldmeth(int yieldmeth_number,
	char yieldmethparm [yield_names_len])
{
	return_state = return_success;
	strcpy(yield_meth_names[yieldmeth_number], yieldmethparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyieldmeth(char yieldmethparm [yield_names_len])
{
	return_state = return_success;
	strcpy(current_yield_meth_name, yieldmethparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyieldmeth(int yieldmeth_number,
	char yieldmethparm [yield_names_len])
{
	return_state = return_success;
	strcpy(yieldmethparm, yield_meth_names[yieldmeth_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyieldmeth(char yieldmethparm [yield_names_len])
{
	return_state = return_success;
	strcpy(yieldmethparm, yield_meth_names[current_yield_meth]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyielddays(int yielddays_number,
	char yielddaysparm [day_count_names_len])
{
	return_state = return_success;
	strcpy(day_count_names[yielddays_number], yielddaysparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyielddays(char yielddaysparm [day_count_names_len])
{
	return_state = return_success;
	strcpy(current_yield_days_name,yielddaysparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyielddays(int yielddays_number,
	char yielddaysparm [day_count_names_len])
{
	return_state = return_success;
	strcpy(yielddaysparm, day_count_names[yielddays_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyielddays(char yielddaysparm [day_count_names_len])
{
	return_state = return_success;
	strcpy(yielddaysparm, day_count_names[current_yield_days]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyieldfreq(int yieldfreq_number,
	char yieldfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(freq_names[yieldfreq_number], yieldfreqparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyieldfreq(char yieldfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(current_yield_freq_name, yieldfreqparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyieldfreq(int yieldfreq_number,
	char yieldfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(yieldfreqparm, freq_names[yieldfreq_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyieldfreq(char yieldfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(yieldfreqparm, freq_names[current_yield_freq]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyieldmeth(int yieldmeth_number)
{
	return_state = return_success;
	current_yield_meth = yieldmeth_number;
	strcpy(current_yield_meth_name,yield_meth_names[yieldmeth_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyieldmeth(int *yieldmeth_number)
{
	return_state = return_success;
	*yieldmeth_number = current_yield_meth;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyielddays(int yielddays_number)
{
	return_state = return_success;
	current_yield_days = yielddays_number;
	strcpy(current_yield_days_name,day_count_names[yielddays_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyielddays(int *yielddays_number)
{
	return_state = return_success;
	*yielddays_number = current_yield_days;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setyieldfreq(int yieldfreq_number)
{
	return_state = return_success;
	current_yield_freq = yieldfreq_number;
	strcpy(current_yield_freq_name,freq_names[yieldfreq_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getyieldfreq(int *yieldfreq_number)
{
	return_state = return_success;
	*yieldfreq_number = current_yield_freq;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setmonthend(int monthend_number)
{
	return_state = return_success;
	current_monthend = monthend_number;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getmonthend(int *monthend_number)
{
	return_state = return_success;
	*monthend_number = current_monthend;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setexcoupdays(int excoupdays)
{
	return_state = return_success;
	current_ex_coup_days = excoupdays;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getexcoupdays(int *excoupdays)
{
	return_state = return_success;
	*excoupdays = current_ex_coup_days;
	return return_state;
}
unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::getprevcoup(char prev_coup_str [date_str_size])
{


	return  dateconv(date_format_1, dateconv_union_to_string,
		prev_coup_str, &prev_coup, &work_double);

}
unsigned long   _FAR_FUNC _EX_IN_FUNC Py_Front::getnextcoup(char next_coup_str [date_str_size])
{


	return  dateconv(date_format_1, dateconv_union_to_string,
		next_coup_str, &next_coup, &work_double);

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getintdays(long *intdaysparm)
{

	return_state = return_success;
	*intdaysparm = interest_days;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getinterest(long double *interestparm)
{

	return_state = return_success;
	*interestparm = interest;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getnomadj(long double *nomadjparm)
{

	return_state = return_success;
	*nomadjparm = nominal_adjust;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getduration(long double *durationparm)
{

	return_state = return_success;
	*durationparm = duration_hold;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getmodduration(long double *moddurationparm)
{

	return_state = return_success;
	*moddurationparm = modified_duration_hold;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getconvexity(long double *convexityparm)
{

	return_state = return_success;
	*convexityparm = conv;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getpvbp(long double *pvbpparm)
{

	return_state = return_success;
	*pvbpparm = pvbp_out;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getsinkcount(char *sinkcountparm)
{

	return_state = return_success;
	*sinkcountparm = sink_fund_sched[0].last_element;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setsinkcount(char sinkcountparm)
{

	return_state = return_success;
	sink_fund_sched[0].last_element = sinkcountparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getsinkdate(int sink_number, char sink_date_str[date_str_size])
{


	return_state = return_success;
	return_state =   dateconv(date_format_1, dateconv_union_to_string,
		sink_date_str, &sink_fund_sched[sink_number].pay_date, &work_double);
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setsinkdate(int sink_number, char sink_date_str[date_str_size])
{


	return_state = return_success;
	return_state =  dateconv(date_format_1, dateconv_string_to_union,
		sink_date_str, &sink_fund_sched[sink_number].pay_date, &work_double);
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getsinkpay(int sink_number, long double *sink_pay)
{


	return_state = return_success;
	*sink_pay = sink_fund_sched[sink_number].payment;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setsinkpay(int sink_number, long double sink_pay)
{


	return_state = return_success;
	sink_fund_sched[sink_number].payment = sink_pay;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setsinkmat(char sink_mat_str[redemp_sched_names_len])
{
	return_state = return_success;
	strcpy(current_sink_fund_mat_name, sink_mat_str);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getsinkmat(char sink_mat_str[redemp_sched_names_len])
{
	return_state = return_success;
	strcpy(sink_mat_str, current_sink_fund_mat_name);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getpartpaycount(char *partpaycountparm)
{

	return_state = return_success;
	*partpaycountparm = part_pays_sched[0].last_element;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setpartpaycount(char partpaycountparm)
{

	return_state = return_success;
	part_pays_sched[0].last_element = partpaycountparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getpartpaydate(int partpay_number,
	char partpay_date_str[date_str_size])
{


	return_state = return_success;
	return_state =   dateconv(date_format_1, dateconv_union_to_string,
		partpay_date_str, &part_pays_sched[partpay_number].pay_date, &work_double);
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setpartpaydate(int partpay_number,
	char partpay_date_str[date_str_size])
{


	return_state = return_success;
	return_state =  dateconv(date_format_1, dateconv_string_to_union,
		partpay_date_str, &part_pays_sched[partpay_number].pay_date, &work_double);
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getpartpaypay(int partpay_number, long double *partpay_pay)
{


	return_state = return_success;
	*partpay_pay = part_pays_sched[partpay_number].payment;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setpartpaypay(int partpay_number, long double partpay_pay)
{


	return_state = return_success;
	part_pays_sched[partpay_number].payment = partpay_pay;
	return return_state;

}

void   _FAR_FUNC _EX_IN_FUNC Py_Front::errtext(unsigned long errnum, char error_text [error_text_len])
{
	_errtext error_class;

	error_class.errtext(errnum, error_text );

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getreratecount(char *reratecountparm)
{

	return_state = return_success;
//	*reratecountparm = rate_array[0].event_date.date.centuries - 1;
	*reratecountparm = rate_array[0].event_date.date.centuries;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setreratecount(char reratecountparm)
{

	return_state = return_success;
//	rate_array[0].event_date.date.centuries = reratecountparm + 1;
	rate_array[0].event_date.date.centuries = reratecountparm;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getfrnrate(int frn_number, long double *frnrate)
{


	return_state = return_success;
	*frnrate = rate_array[frn_number].rate;
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setfrnrate(int frn_number, long double frnrate)
{


	return_state = return_success;
	rate_array[frn_number].rate = (float)frnrate;
	return return_state;

}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setfrnpayfreq(char frnpayfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(rerate_sched.current_pay_freq_name, frnpayfreqparm);
	return return_state;
}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getreratedate(int frn_number,
	char frn_date_str[date_str_size])
{


	return_state = return_success;
	return_state =   dateconv(date_format_1, dateconv_union_to_string,
//		frn_date_str, &rate_array[frn_number + 1].event_date, &work_double);
		frn_date_str, &rate_array[frn_number].event_date, &work_double);
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setreratedate(int frn_number,
	char frn_date_str[date_str_size])
{


	return_state = return_success;
	return_state =  dateconv(date_format_1, dateconv_string_to_union,
		frn_date_str, &rate_array[frn_number + 1].event_date, &work_double);
	return return_state;

}

unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getholidaytotal(int *holiday_number)
{
	return_state = return_success;

	return_state = Setholicodearray(holiday_number);
	return return_state;
}
/*
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getholiday(int holiday_number, char holiday_str[fra_holiday_names_len])
{
	return_state = return_success;
	return_state = GetHoliCode(holiday_str,holiday_number);
//	strcpy( holiday_str, holiday_choice[holiday_number]);
	return return_state;
}
*/
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setholiday(int holiday_number)
{
	return_state = return_success;
	current_holiday = holiday_number;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getholiday(int *holiday_number)
{
	return_state = return_success;
	*holiday_number = current_holiday;
	return return_state;
}
/*
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setholiday(char holiday_str[fra_holiday_names_len])
{
	return_state = return_success;
	strcpy(current_holiday_name, holiday_str);
	strcpy(in_instr.holiday_code, holiday_str);
	return return_state;
}
*/
/*
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getholiday(char holiday_str[fra_holiday_names_len])
{
	return_state = return_success;
	strcpy(holiday_str, current_holiday_name);
	return return_state;
}
*/
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setholidayadj(	char holidayparm [holiday_adj_names_len])
{
	return_state = return_success;
	strcpy(rerate_sched.current_holiday_adj_name, holidayparm);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getholidayadj(	char holidayparm [holiday_adj_names_len])
{
	return_state = return_success;
	strcpy(holidayparm, rerate_sched.current_holiday_adj_name);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getfrnpayfreq(int payfreq_number,
	char payfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(payfreqparm, rerate_sched.pay_freq_choice[payfreq_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getholidayadj(int holadj_number,	char holidayparm [holiday_adj_names_len])
{
	return_state = return_success;
	strcpy(holidayparm, rerate_sched.holiday_adj_choice[holadj_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getholidayadj(int *holadj_number)
{
	return_state = return_success;
	*holadj_number =  rerate_sched.current_holiday_adj;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setholidayadj(int holadj_number)
{
	return_state = return_success;
	rerate_sched.current_holiday_adj = holadj_number;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getfrnpayfreq(char payfreqparm [freq_names_len])
{
	return_state = return_success;
	strcpy(payfreqparm, rerate_sched.current_pay_freq_name);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getfrnpayfreq(int *payfreq_number )
{
	return_state = return_success;
	*payfreq_number = rerate_sched.current_pay_freq;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getsimpcomp(char simpcompparm [simp_comp_names_len])
{
	return_state = return_success;
	strcpy(simpcompparm, rerate_sched.current_simp_comp_name);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getsimpcomp(int *simpcomp_number )
{
	return_state = return_success;
	*simpcomp_number = rerate_sched.current_simp_comp;
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getsimpcomp(int simpcomp_number,	char simpcompparm [simp_comp_names_len])
{
	return_state = return_success;
	strcpy(simpcompparm, rerate_sched.simp_comp_choice[simpcomp_number]);
	return return_state;
}
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getprepay(int prepay_number, char prepayparm [prepay_type_names_len])
{
	return_state = return_success;
	strcpy(prepayparm, prepay_type_choice[prepay_number]);
	return return_state;
}
/*
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::getcprrate(int *cprrate)
{
	return_state = return_success;
	*cprrate = cpr_rate;
	return return_state;
}
*/
unsigned long    _FAR_FUNC _EX_IN_FUNC Py_Front::setprepay(	char prepayparm [prepay_type_names_len])
{
	return_state = return_success;
	strcpy(prepay_type_name, prepayparm);
	return return_state;
}

unsigned long  _FAR_FUNC _EX_IN_FUNC   Py_Front::getpayfreqlength(int *payfreq_length)
{
	return_state = return_success;
	*payfreq_length = in_instr.pay_freq.freq;
	return return_state;
}
unsigned long  _FAR_FUNC _EX_IN_FUNC   Py_Front::getpayfreqperiod(int *payfreq_period)
{
	return_state = return_success;
	*payfreq_period = in_instr.pay_freq.period;
	return return_state;
}

unsigned long  _FAR_FUNC _EX_IN_FUNC   Py_Front::getpayfreqlengthyield(int *payfreq_length)
{
	return_state = return_success;
	*payfreq_length = pyparm.comp_freq;
	return return_state;
}
unsigned long  _FAR_FUNC _EX_IN_FUNC   Py_Front::getpayfreqperiodyield(int *payfreq_period)
{
	return_state = return_success;
	*payfreq_period = event_sched_month_period;
	return return_state;
}

extern void _export FAR testfunc();

void FAR _export testfunc()
{
}

