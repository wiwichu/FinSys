#include "stdafx.h"
#include "Calc.h"
#include "datedec.h"
#include "pydecs.h"
#include "intdecs.h"
#include <math.h>


unsigned long	_PYFUNCS py_coup_load( char py_period_length, char *simp_comp_frac,
					long double days_in_year, long double comp_freq,
					long double *sett_2_first_fact,
					long double *nom_adj_int_calc,
					long double ex_coup, char py_cal_num,
					unsigned int *coup_count,
					unsigned int holi_chan, date_union py_date,
					instr *in_instr, py_parms *py_parm, char pay_adj,
					unsigned int event_chan, char skip_odd,
					char *first_simp_comp_frac
//					,holidays_struct holi_parm []
					,const set<string> &holiSet
					,long days_sett_to_mat, long double pay_freq,
					int *coups_left, insevent_struct rate_array [max_rates],
					int *pay_array_index, booleans fast_calc,
					pay_struc pay_array_a [max_coups], long double first_int)

{

#include "locals.h"

char adj_hold = 0;

int date_cmp = -1;
int date_cmp2 = -1;
int date_cmp_real = 0;
int element_num = 0;
int pay_array_size = 0;
int num_per = 0;

long int_days = 0;
long num_days = 0;

long double interest = 0;
long double dummy_double = 0;

//unsigned long return_state;

date_union prv_pay;
date_union nxt_pay;
date_union date_hold;
date_union date_hold2;
//date_union real_prv_pay;
//date_union real_nxt_pay;

date_union base_date;

	datecpy(base_date.date_string,py_date.date_string);

		  /*{ Determine size of array necessary to hold all the payments.}*/

	pay_array_a[0].time_to_pay = 0;

	if (fast_calc == istrue)
	{


			 /*{ Determine the number of coupon payments to maturity. }*/
/*
	  return_status = coups_to_mat(coups_left, *in_instr, py_date,
			holi_chan, holi_parm, pay_freq);

	  if (return_status != return_success) {

		 ////errproc(return_status,module_name,"","","");

		 goto py_coup_load_end;
	  }
*/
	  pay_array_size = 3;

	}
	else
	{

	  pay_array_size = (int)(12 + ( pay_freq * (days_sett_to_mat / (12 * 30))));

	}
/*
	if (!(pay_array_a = new pay_struc[pay_array_size]))
	{
		 return_status = return_err_ins_mem;
		 ////errproc(return_status,module_name,"","","");
		 goto py_coup_load_end;
	}
*/
	/*{ Keep loading coupon dates and amounts into array until maturity date.}*/

	for (*coup_count = 0, date_cmp = -1; date_cmp < 0; *coup_count = *coup_count + 1)
	{

	 /* For cashflow determine the time to each payment.*/

	 if (in_instr->instr_class == instr_cashflow_class)

	 {

		 pay_array_a[*coup_count + 1].work_double = 0;

		 /* First estimate the number of periods.*/

		 return_status = tenor (py_date,
				pay_array_a[*coup_count + 1].pay_date,
				py_cal_num,
				&num_days);

		 if (return_status != return_success)
		 {


			goto py_coup_load_end;

		 }

		 num_per = (int)(num_days/(days_in_year/comp_freq));

		 /* Try the estimated periods. */

		 return_status = forecast(py_date,
					  num_per * in_instr->pay_freq.freq,
					  0,
					  in_instr->cal_den,
					  &date_hold);

		 if (return_status != return_success)
		 {

			goto py_coup_load_end;

		 }

		 /* Compare the resulting date.*/

		 date_cmp2 = datecmp(date_hold.date_string,
							pay_array_a[*coup_count + 1].pay_date.date_string);

		 /* If the date is less, try one more period. */

		 if (date_cmp2 < 0)
		 {

			return_status = forecast(date_hold,
					  in_instr->pay_freq.freq,
					  0,
					  in_instr->cal_den,
					  &date_hold2);

			if (return_status != return_success)
			{

			  goto py_coup_load_end;

			}

			/* Compare dates again. */

			date_cmp2 = datecmp(date_hold2.date_string,
							pay_array_a[*coup_count + 1].pay_date.date_string);

			/* If the date is still too low, try one more.*/

			if (date_cmp2 < 0)
			{

			  num_per = num_per + 1;

			  return_status = forecast(date_hold2,
					  in_instr->pay_freq.freq,
					  0,
					  in_instr->cal_den,
					  &date_hold);

			  if (return_status != return_success)
			  {

				 goto py_coup_load_end;

			  }

			  date_cmp2 = datecmp(date_hold.date_string,
							pay_array_a[*coup_count + 1].pay_date.date_string);

			  /* If the date is still too low, flag an error.*/

			  if (date_cmp2 < 0)
			  {

				 return_status = return_err_cashflow;
				 goto py_coup_load_end;

			  }
			  else
			  {

				 datecpy(date_hold.date_string, date_hold2.date_string);

				 pay_array_a[*coup_count + 1].work_double = num_per;

			  }

			}
			else
			{
				pay_array_a[*coup_count + 1].work_double = num_per;
			}

		 }
		 else
		 {

			/* If there is a match, use the periods.*/

			if (date_cmp2 == 0)
			{

				pay_array_a[*coup_count + 1].work_double = num_per;

			}
			else
			{

			  /* If the date was exceeded, try one period less.*/

			  return_status = forecast(date_hold,
					  -in_instr->pay_freq.freq,
					  0,
					  in_instr->cal_den,
					  &date_hold2);

			  if (return_status != return_success)
			  {

				 goto py_coup_load_end;

			  }

			  /*If the date is still exceeded, flag an error.*/

			  date_cmp2 = datecmp(date_hold2.date_string,
							pay_array_a[*coup_count + 1].pay_date.date_string);

			  if (date_cmp2 > 0)
			  {

				 return_status = return_err_cashflow;
				 goto py_coup_load_end;

			  }
			  else
			  {

				 datecpy(date_hold.date_string, date_hold2.date_string);

				 pay_array_a[*coup_count + 1].work_double = num_per - 1;

			  }
			}
		 }

		 if (date_cmp2 != 0)
		 {

			datecpy(in_instr->issue_date.date_string,date_hold.date_string);

			datecpy(in_instr->accrue_date.date_string,date_hold.date_string);

			datecpy(in_instr->mat_date.date_string,
			  pay_array_a[*coup_count + 1].pay_date.date_string);

			datecpy(in_instr->pay_freq.first_date.date_string,
			  pay_array_a[*coup_count + 1].pay_date.date_string);

			in_instr->pay_freq.month_day =
			  pay_array_a[*coup_count + 1].pay_date.date.days;

			return_status = intcalc(*in_instr, date_hold, &dummy_double,
				&int_days, holi_chan, isfalse,int_no_total_per,
				nom_adj_int_calc, sett_2_first_fact, int_no_redemp_adj,
				event_chan
//				, holi_parm
				,holiSet
				, rate_array, &dummy_double);

			if (return_status != return_success)
			{

			 goto py_coup_load_end;

			}

			pay_array_a[*coup_count + 1].work_double =
				pay_array_a[*coup_count + 1].work_double + *sett_2_first_fact;

			if (	(*coup_count + 1)	== (unsigned int)pay_array_a[0].last_element)
			{

			 date_cmp = 0;

			}
		 }
	 }

	 else

	 {

	  return_status = n_p_pay(*in_instr
		  , base_date
		  , &prv_pay
		  , &nxt_pay,
		holi_chan
//		, holi_parm
		,holiSet
		);

	  if (return_status != return_success)
	  {


		 goto py_coup_load_end;
	  }

	  /*{ Check whether an odd first coupon must be ignored.}*/

	  if (skip_odd == py_yes_skip_odd)
	  {

		 date_cmp = datecmp(nxt_pay.date_string, in_instr->pay_freq.first_date.date_string);

		 if (date_cmp == 0)
		 {

			datecpy(date_hold.date_string, in_instr->pay_freq.first_date.date_string);

			if (pay_adj != event_sched_same_holiday_adj)

			{

			  return_status = adj_date(&date_hold,
				adj_date_non_to_bus,
				pay_adj,
				adj_date_yes_we,
				adj_date_yes_hol,
//				in_instr->holiday_code,
				holi_chan
//				,holi_parm
				, holiSet
				);

			  if (return_status != return_success)
			  {

				  goto py_coup_load_end;

			  }

			}

			do
			{

			  return_status = forecast(date_hold,
					  -in_instr->pay_freq.freq,
					  0,
					  in_instr->cal_den,
					  &date_hold2);

			  if (return_status != return_success)
			  {

				goto py_coup_load_end;

			  }

			  date_cmp = datecmp(date_hold2.date_string, base_date.date_string);

			  if (date_cmp <= 0)
			  {

				datecpy(in_instr->issue_date.date_string, date_hold2.date_string);
				datecpy(in_instr->accrue_date.date_string, date_hold2.date_string);

			  }
			  else
			  {

				datecpy( date_hold.date_string, date_hold2.date_string);

				datecpy( in_instr->pay_freq.first_date.date_string, date_hold.date_string);

			  }


			} while (date_cmp > 0);

			return_status = n_p_pay(*in_instr
				, base_date
				, &prv_pay
				,&nxt_pay
				, holi_chan
//				, holi_parm
				,holiSet
				);

			if (return_status != return_success)
			{


			  goto py_coup_load_end;
			}

		 }

	  }

	  date_cmp = datecmp(nxt_pay.date_string, in_instr->mat_date.date_string);

	  if (date_cmp <= 0)
	  {

		 /*{ Increment base date.}*/

		 datecpy(base_date.date_string, nxt_pay.date_string);

		 /*{ Check for real pay day.}*/

		 datecpy(date_hold.date_string, base_date.date_string);

		 if (pay_adj != event_sched_same_holiday_adj)

		 {

			return_status = adj_date(&date_hold,
				adj_date_non_to_bus,
				pay_adj,
				adj_date_yes_we,
				adj_date_yes_hol,
//				in_instr->holiday_code,
				holi_chan
//				,holi_parm
				,holiSet
				);

			if (return_status != return_success)
			{

				goto py_coup_load_end;

			}

		 }

		 if ((fast_calc) && (*coup_count != 0))

		 {

			if (date_cmp != 0)
			{

				date_cmp2 = datecmp(nxt_pay.date_string,
				in_instr->pay_freq.first_date.date_string);

				if (date_cmp2 != 0)

				{

					datecpy(base_date.date_string,  in_instr->mat_date.date_string);
					datecpy(date_hold.date_string,  in_instr->mat_date.date_string);

					date_cmp = 0;

				}

			}

		 }

		 return_status = intcalc(*in_instr, base_date, &interest,
				&int_days, holi_chan, isfalse,
				int_yes_total_per, nom_adj_int_calc,
				&dummy_double, int_no_redemp_adj,
				event_chan
//				, holi_parm
				,holiSet
				, rate_array, &dummy_double);

		 if (return_status != return_success)
		 {


			goto py_coup_load_end;

		 }

		 if (*coup_count == 0)
		 {

			return_status = intcalc(*in_instr, py_date, &dummy_double,
				&int_days, holi_chan, isfalse,int_no_total_per,
				nom_adj_int_calc, sett_2_first_fact, int_no_redemp_adj,
				event_chan
//				, holi_parm
				,holiSet
				, rate_array, &dummy_double);

			if (return_status != return_success)
			{


				goto py_coup_load_end;
			}

			if (ex_coup)
			{

				interest = 0;

			}

			return_status = py_frac_per(py_period_length, simp_comp_frac,
			days_in_year, comp_freq, sett_2_first_fact,
			py_cal_num, py_date, py_parm, nxt_pay, in_instr
			,holi_chan, first_simp_comp_frac
//			, holi_parm
			,holiSet
			);

			if (return_status != return_success)
			{


				goto py_coup_load_end;
			}

			/* If the first payment is passed, load this into the first coupon.*/

			if (py_parm->parm_use == py_yes_parm_use &&
				py_parm->calc_first == py_no_calc_first)
			{

			  interest = first_int;

			}

		 }

		 /*{ If the base date is on a payment date, start with a zero payment.}*/

		 if ((int_days == 0) &&
			 (*coup_count == 0))
		 {

			*coup_count = *coup_count + 1;

			datecpy(pay_array_a[0].pay_date.date_string,
				py_date.date_string);

			pay_array_a[0].payment = 0;

		 }

		 *pay_array_index = *coup_count;

		 datecpy(pay_array_a[*pay_array_index].pay_date.date_string,
			date_hold.date_string);

		 pay_array_a[*pay_array_index].payment = interest;

	  }
	 }
	}

py_coup_load_end:

	return return_status;
}


unsigned long	_PYFUNCS py_frac_per(char py_period_length, char *simp_comp_frac,
			long double days_in_year, long double comp_freq,
			long double *sett_2_first_fact,
			char py_cal_num, date_union py_date,
			py_parms *py_parm, date_union nxt_pay, instr *in_instr,
			unsigned int holi_chan, char *first_simp_comp_frac
//			,holidays_struct holi_parm []
			,const set<string> &holiSet
			)

{

#include "locals.h"
long days_to_next = 0;


	if (py_period_length == py_total_days_per_len)
	{

	  *sett_2_first_fact = 0;
	  *simp_comp_frac = py_skip_frac_per;
	  *first_simp_comp_frac = *simp_comp_frac;

	}
	else
	{

	  return_status = py_simp_comp_frac (simp_comp_frac, py_parm,
		in_instr, py_date, holi_chan, first_simp_comp_frac
//		,holi_parm
		,holiSet
		);

	  if (return_status != return_success)
	  {


			goto py_frac_per_end;
	  }

	  if (((py_parm->parm_use == py_yes_parm_use) &&
		  (*sett_2_first_fact != 0)) &&
		  ((py_parm->date_cal_num != date_no_cal) ||
		  (py_parm->date_cal_den != date_no_cal)))

	  {

			return_status = tenor (py_date,
				nxt_pay,
				py_cal_num,
				&days_to_next);

			if (return_status != return_success)
			{


				goto py_frac_per_end;
			}

			*sett_2_first_fact = days_to_next/(days_in_year/comp_freq);

	  }
	}

py_frac_per_end:
	return return_status;
}


unsigned long	_PYFUNCS py_simp_comp_frac(char *simp_comp_frac, py_parms *py_parm,
				instr *in_instr, date_union base_date,
				unsigned int holi_chan,
				char *first_simp_comp_frac
//				,holidays_struct holi_parm []
				,const set<string> &holiSet
				)
{

#include "locals.h"

int	date_cmp = 1;

date_union date_hold;
date_union date_hold2;


	  if ((py_parm->parm_use == py_yes_parm_use) &&
			(py_parm->frac_per != py_no_frac_per))
	  {
		  *simp_comp_frac = py_parm->frac_per;
				 *first_simp_comp_frac = *simp_comp_frac;
	  }
	  else
	  {

		  if (py_parm->yield_meth == py_muni_yield_meth)
		  {

			return_status = forecast(in_instr->mat_date,
					  -6,
					  0,
					  in_instr->cal_den,
					  &date_hold);

			if (return_status != return_success)
			{


				goto py_simp_comp_frac_end;

			}

			date_cmp = datecmp(date_hold.date_string, base_date.date_string);

		  }

		  if (py_parm->yield_meth == py_ustr_yield_meth)
		  {


			return_status = n_p_pay(*in_instr
				, base_date
				, &date_hold2
				,&date_hold
				, holi_chan
//				, holi_parm
				,holiSet
				);

			if (return_status != return_success)
			{

				goto py_simp_comp_frac_end;

			}

			date_cmp = datecmp(in_instr->mat_date.date_string, date_hold.date_string);

		  }

		  if ((py_parm->yield_meth == py_mm_yield_meth) ||
			(py_parm->yield_meth == py_ytm_simp_yield_meth) ||
			(date_cmp <= 0))

		  {

			 *simp_comp_frac = py_simp_frac_per;

		  }
		  else
		  {

			 *simp_comp_frac = py_comp_frac_per;

		  }

		  if ((py_parm->yield_meth == py_bf_yield_meth) ||
			(py_parm->yield_meth == py_moos_yield_meth)
			)

		  {

			 *first_simp_comp_frac = py_simp_frac_per;

		  }
		  else
		  {

			 *first_simp_comp_frac = *simp_comp_frac;

		  }

	  }

py_simp_comp_frac_end:

	return return_status;

}


unsigned long	_PYFUNCS py_pv_coups(char py_period_length, char simp_comp_frac,
			long double days_in_year, long double *comp_freq,
			long double sett_2_first_fact,
			long double *work_yield, long double *pv_coups,
			long double *pv_factor, char py_cal_num,
			unsigned int coup_count_parm, date_union py_date,
			py_parms *py_parm, long double *coups_prime,
			long double *coup_prime_factor,
			long double pay_freq, long double *simp_frac,
			long double *comp_frac, long double *work_duration,
			char first_simp_comp_frac, unsigned int holi_chan
//			,holidays_struct holi_parm []
			, instr in_instr,
			int coups_left, long double *comp_freq_hold,
			int *pay_array_index, int fast_calc,
			pay_struc pay_array_a [max_coups] )

{

#include "locals.h"

int issue_cmp = 0;
int mat_cmp = 0;
int date_cmp = -1;
int prime_loop = 0;
int cmplast = 1;

long double num_pers = 0;
long double days_in_per = 0;
long double temp_long_double = 0;
long double yield_adj = 0;
long double whole_per = 0;
long double frac_per = 0;
long double pv_this_coup = 0;
long double last_prime_factor = 1;
long double last_pv_factor = 0;
long double comp_pay_ratio = 0;
/*{ Define the  variables}*/

long double UPB = 0;
long double N = 0;
long double M = 0;
long double N_D = 0;
long double M_D = 0;
long double r = 0;
long double s = 0;
long double i = 0;
long double smm = 0;
long double X = 0;
long double Y = 0;
long double P_plus_I = 0;
long double Prepays = 0;
long double Servicing= 0;
long double P_plus_I_D = 0;
long double Prepays_D = 0;
long double Servicing_D = 0;
long double first_pay = 0;
long double CPR = 0;
long double lag_adj = 0;
long double lag_adj_prime = 0;
long double fast_calc_prime = 0;
long double wf = 0;

long days_to_this_pay = 0;

unsigned int this_coup = 0;	/*{ this_coup is a counter for future coupons.}*/
unsigned int this_cycle = 0;
unsigned int cycle_count = 0;
int cycle_adj = 0;
unsigned int extra_cycles = 0;
unsigned int comp_pay_int_ratio = 0;

	*coups_prime = 0;
	*coup_prime_factor = 0;
	cycle_count = coup_count_parm;

	/* Note whether the first period is also the last.*/

	if (in_instr.instr_class != instr_cashflow_class)
	{

	  cmplast = datecmp(in_instr.mat_date.date_string,
			in_instr.pay_freq.first_date.date_string);

	}

	/*{ If the compounding frequency is more often than the payment
	frequency, increase the loop limit by this factor. This possibility
	is not permitted for payment frequencies of every two or four
	months.}*/

	if (pay_freq == 0)

	{

	  pay_freq = *comp_freq;

	}

	comp_pay_ratio = *comp_freq/pay_freq;

	sett_2_first_fact= sett_2_first_fact * comp_pay_ratio;

	if (*comp_freq > pay_freq)

	{

	  comp_pay_int_ratio = (unsigned int)(*comp_freq/pay_freq);

	  cycle_count = (unsigned int)(cycle_count * comp_pay_ratio);

	  /*{ Also add a cycle for each complete compounding period before the
	  first coupon.}*/

	  extra_cycles = (unsigned int)(sett_2_first_fact/1);

	  cycle_count = cycle_count + extra_cycles;

	  comp_pay_ratio = 1;

	}
	else
	{

	  comp_pay_int_ratio = 1;

	}

	/*{ Process all the coupons stored in the array.}*/

	for (this_coup = 0, this_cycle = 0, date_cmp = -1, *pv_coups = 0,
		 *pv_factor = 1; this_cycle < cycle_count; this_cycle++)

	{

	  /* For cashflow use the time to each payment. */

	  if (in_instr.instr_class == instr_cashflow_class)
	  {

		 sett_2_first_fact = pay_array_a[this_coup].work_double;

	  }

	  /*{ If price is being calculated get yield to use if not fast_calc.}*/

	  if ((py_parm->calc_what == py_price_from_yield_calc_what) &&
			 (fast_calc == isfalse))
	  {

		 return_status = py_get_disc ( pay_array_a[this_coup].pay_date,
				work_yield);

		 if (return_status != return_success)
		 {


			goto py_pv_coups_end;
		 }

	  }

	  /*{ Adjust yield for different comp_freq if fast calc is used.}*/


	  /*{ Calculate the days in a typical period.}*/

	  days_in_per = days_in_year/ *comp_freq;

	  switch (py_period_length)
	  {
		 case (py_total_days_per_len):

		 {

			return_status = tenor (py_date,
			pay_array_a[this_coup].pay_date,
			py_cal_num,
			&days_to_this_pay);

			if (return_status != return_success)
			{


				goto py_pv_coups_end;
			}

			num_pers = (long double) days_to_this_pay/days_in_per;

			break;

		 }

		 case (py_uniform_per_len):

		 {
			if (this_cycle == 0)

			{

				num_pers = sett_2_first_fact - extra_cycles;

			}

			else
			{

				if (cmplast != 0)

				{

				  if (in_instr.instr_class == instr_cashflow_class)
				  {

					num_pers = sett_2_first_fact;

				  }

				  else

				  {

					num_pers = num_pers + comp_pay_ratio;

				  }

				}

			}


			break;

		 }

		 case (py_exact_per_len):

		 {

				  /*{ This choice is restricted to comp_freq = pay_freq}*/

			if (this_coup == 0)

			{

				num_pers = sett_2_first_fact;


			}

			else
			{


		  /*{ Find the number of days in this period.}*/

				*pay_array_index = this_coup - 1;

				return_status = tenor (pay_array_a[*pay_array_index].pay_date,
					pay_array_a[this_coup].pay_date,
					py_cal_num,
					&days_to_this_pay);

				if (return_status != return_success)
				{


					goto py_pv_coups_end;
				}

				num_pers = (long double) days_to_this_pay/days_in_per;

			}
			break;

		 }

		 default:
		 {

			return_status = return_err_py_incomp;
			goto py_pv_coups_end;

			break;

		 }

	  }

	  switch (simp_comp_frac)
	  {
		 case py_simp_frac_per:
		 {

			if (simp_comp_frac == first_simp_comp_frac)
			{

			  *comp_frac = 1;
			  *simp_frac = num_pers;

			}
			else
			{


			  if (num_pers < 1)
			  {

					*comp_frac = num_pers;
					*simp_frac = 0;

			  }
			  else
			  {

				  if (this_coup == 0)
				  {


					 for (*comp_frac = num_pers; *comp_frac >= 1;
					 	*comp_frac = *comp_frac - 1)
					 {
					 }

				  }

				 *simp_frac = (num_pers - *comp_frac);

			  }


			}
			break;

		 }
		 default:
		 {

			if (simp_comp_frac == first_simp_comp_frac)
			{

			  *simp_frac = 1;
			  *comp_frac = num_pers;

			}
			else
			{

				if (num_pers < 1)
				{

					*simp_frac = num_pers;
					*comp_frac = 0;

				}
				else
				{

				  if (this_coup == 0)
				  {


					for (*simp_frac = num_pers; *simp_frac >= 1;
						*simp_frac = *simp_frac - 1)
					{
					}
/*					 *simp_frac = 1; */

				  }

					 *comp_frac = (num_pers - *simp_frac);

				}


			}

			break;
		 }
	  }


	  if (simp_comp_frac == first_simp_comp_frac)

	  {

		 temp_long_double =
		 pow((long double) (1 + (*simp_frac) * *work_yield/ *comp_freq),*comp_frac);

	  }
	  else
	  {
/*
		 if (first_simp_comp_frac == py_comp_frac_per)
		 {

			temp_long_double =
				(1 + (*simp_frac) * *work_yield/ *comp_freq);

			temp_long_double = temp_long_double *
				pow((long double) (1 + *work_yield/ *comp_freq),*comp_frac);

		 }
		 else
		 {
*/

			temp_long_double =
				pow((long double) (1 + *work_yield/ *comp_freq),*comp_frac);

			temp_long_double = temp_long_double *
				(1 + (*simp_frac) * *work_yield/ *comp_freq);

	  }

	  fast_calc_prime = (*comp_frac + 1) *
		pow((long double) (1 + *work_yield/ *comp_freq),*comp_frac);


	  yield_adj = *simp_frac * *work_yield/ *comp_freq;

	  *coup_prime_factor = (*comp_frac ) *
					(long double)1/pow((1 + (yield_adj)),(*comp_frac + 1));

	  if (*comp_frac != 0)
	  {

		 *coup_prime_factor = *coup_prime_factor * (-1);

	  }
	  else
	  {

		 *comp_frac = 1;

	  }


	  if (
		(py_period_length == py_exact_per_len)
		&&
		((cmplast != 0) || (this_cycle == 0))
		  )
	  {

		 *coup_prime_factor = *comp_freq * *comp_freq *
				((*pv_factor * *coup_prime_factor) +
				(temp_long_double * last_prime_factor))
				/
				(
				*coup_prime_factor *
				last_prime_factor)
				;

		 *pv_factor = (*pv_factor * temp_long_double);


		 last_prime_factor = *coup_prime_factor;

		 if (last_prime_factor == 0)
		 {

			last_prime_factor = 1;

		 }

	  }
	  else
	  {

		 *pv_factor = temp_long_double;

	  }

	  cycle_adj = this_cycle - extra_cycles;

	  if ((cycle_adj >=0 ) &&
			((cycle_adj % comp_pay_int_ratio) == 0) ||
			(pay_freq > *comp_freq))
	  {
		 pv_this_coup = pay_array_a[this_coup].payment/ *pv_factor;
		 *pv_coups = *pv_coups + pv_this_coup;
		 *coups_prime = *coups_prime +
		(pay_array_a[this_coup].payment * *coup_prime_factor);


		 pay_array_a[this_coup].pv_factor = *pv_factor;
		 pay_array_a[this_coup].prime_factor = *coup_prime_factor;
		 pay_array_a[this_coup].time_to_pay =
		(*simp_frac * *comp_frac)/ *comp_freq;

		 *work_duration = *work_duration +
			  (pv_this_coup * pay_array_a[this_coup].time_to_pay);


		 pv_this_coup = 0;

		 /*{ If the fast calculation can be used, do so.}*/

		 if (fast_calc == istrue)
		 {

			date_cmp = datecmp(pay_array_a[this_coup].pay_date.date_string,
				py_date.date_string);

			if (date_cmp != 0)
			{

				if (py_parm->yield_meth == py_MBS_yield_meth)
				{

					UPB = py_parm->current_factor;
					M = coups_left - 1;
					N = M;
					M_D = M;
					N_D = M_D;
					r = (in_instr.service_fee + in_instr.rate_offset) / pay_freq;
					s = in_instr.service_fee / pay_freq;
					i = *work_yield / *comp_freq;
					CPR = py_parm->cpr_rate;
					smm = 1 - pow((1 - CPR),(1 / *comp_freq));
					X = ((1 + i) / (1 - smm));
					Y = X / (1 + r);
					lag_adj = 1 / (pow((1 + i),( in_instr.lag /
						(days_in_year / *comp_freq))));
					lag_adj_prime = (-1) * (in_instr.lag /
						(days_in_year / *comp_freq)) /
						(pow((1 + i),( (in_instr.lag /
						(days_in_year / *comp_freq)) + 1)));

					P_plus_I = 0;
					Prepays = 0;
					Servicing = 0;
					P_plus_I_D = 0;
					Prepays_D = 0;
					Servicing_D = 0;
					first_pay = 0;

					first_pay = (1 - (((1 + r) - 1) /
						(pow((1 + r),coups_left) - 1)));

					first_pay = UPB - first_pay;
/*
		  first_pay = (UPB - (1 - (((1 + i) - 1) /
			(pow((1 + i),coups_left) - 1))));
*/
					first_pay = first_pay + (UPB * smm);

					first_pay = first_pay +
						(pay_array_a[this_coup].payment * UPB);

					UPB = (1 - (((1 + r) - 1) /
						(pow((1 + r),coups_left) - 1))) -
						(UPB * smm);

					P_plus_I = (UPB / ((pow((1 + r),N) - 1) * (1 - smm)));

					Prepays = (pow((1 + r),N) * (r + smm - s) * (pow(X,M) - 1)
						/ ((X - 1) * pow(X,M)));
					Prepays_D = (pow((1 + r),N_D) * (r + smm - s)
						* (pow(X,M_D + 1) - X - (X - 1) * M_D)
						/ (pow((X - 1),2) * pow(X,M_D)));

					if ((1 + i) == ((1 + r) * (1 - smm)))
					{

						Servicing = M * ((s/(1 + r)) - smm);
						Servicing_D = 0;

					}
					else
					{

						Servicing = (((smm - (s / (1 + r))) * (pow(Y,M) - 1))
							/ ((Y - 1) * pow(Y,M)));

						Servicing_D = (((smm - (s / (1 + r)))
							* (pow(Y,M_D + 1) - Y - (Y - 1) * M_D))
							/ (pow((Y - 1),2) * pow(Y,M_D)));

					}

					*pv_coups = (P_plus_I * (Prepays - Servicing));

					P_plus_I_D = ((UPB / (*pv_coups * (1 + i)))
						/ ((pow((1 + r),N_D) - 1) * (1 - smm)));

					*coups_prime =
						((*coup_prime_factor) *
						(first_pay + *pv_coups )) +
						(((-1) * *pv_coups *
						(P_plus_I_D * (Prepays_D - Servicing_D))) /
						(*pv_factor));

					*pv_coups = (*pv_coups +
						first_pay) /
						*pv_factor;

					*coups_prime = (lag_adj * *coups_prime) +
								(*pv_coups * lag_adj_prime);

					*pv_coups = *pv_coups * lag_adj;

					*work_duration = ((*coups_prime * (-1) *
						(1 + (*work_yield/ *comp_freq)))
						/ (*comp_freq ));
				}
				else
				{
					wf = (1 / (1 + *work_yield/ *comp_freq));

					*pv_coups =
						( pay_array_a[this_coup].payment +
						((in_instr.rate_offset/ *comp_freq) *
						((1 / (1 + *work_yield/ *comp_freq)) -
						pow((1 / (1 + *work_yield/ *comp_freq)),coups_left)) /
						(1 - (1 / (1 + *work_yield/ *comp_freq))))
						) /
						*pv_factor;

					*coups_prime =
					 (
					  (pay_array_a[this_coup].payment * num_pers * pow(wf,num_pers)) +
					  ((in_instr.rate_offset / (*comp_freq )) *
						(pow(wf,num_pers)/pow((1 - wf),2)) *
						( pow(wf,(coups_left + 1)) * (coups_left - 1 + num_pers) -
						  pow(wf,coups_left) * (coups_left + num_pers) -
						  num_pers * pow(wf,2) + wf * ( 1 + num_pers)
						)
					  )
					 )/wf;

					*work_duration = (wf / *comp_freq) * *coups_prime;


					*coups_prime = *coups_prime * (-1);

					pay_array_a[coup_count_parm].pv_factor = *pv_factor
						* pow((1 + *work_yield/ *comp_freq),
						(coups_left - 1));

					pay_array_a[coup_count_parm].prime_factor =
						((num_pers + coups_left - 1) * (-1)) /
						(1 + *work_yield/ *comp_freq);

					pay_array_a[coup_count_parm].time_to_pay =
						pay_array_a[this_coup].time_to_pay +
						((coups_left) - 1) / *comp_freq;
				}

				this_cycle = cycle_count;

			}

		 }

				++this_coup;
	  }

	}

py_pv_coups_end:
	return return_status;

}


unsigned long	_PYFUNCS py_get_disc(date_union base_date,
			long double *work_yield)


{

#include "locals.h"

//py_get_disc_end:

	return return_status;

}
