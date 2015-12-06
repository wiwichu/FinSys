#include "stdafx.h"
#include "datedec.h"
#include "gendec.h"
#include <math.h>

_PYFUNCS Py_Funcs()
{
}
/*
_PYFUNCS Py_Funcs(CDB * DB_parm) : Int_Calcs (DB_parm)
{

	DB_local = DB_parm;

//	DB_local->InitDB();

//	DB_local->GetStatementHandle(&localhandles);
}
*/
/*{py_calc accepts .

	Usage:	unsigned long	py_calc(instr in_instr_parm, date_union py_date_parm,
			long double *in_price_parm, long double *out_price_parm,
			long double *acc_int_parm, long double *first_int_parm,
			long double *nom_adj_parm, long double *in_yield_parm,
			long double *out_yield_parm, py_parms py_parm_parm,
			char ex_coup_parm, unsigned int holi_chan_parm,
			unsigned int event_chan_parm, long double *duration_parm,
			long double *modified_duration_parm, holidays_struct holi_parm [],
			long double *convexity_parm, long double *pvbp_parm,
			redemps_struc redemps_array_parm[], insevent_struct rate_array [max_rates])


	where:  in_instr_parm =	Input parameter of instr type which contains
				the instrument for which price/yield is to be
				calculated.

		py_date_parm =	Input parameter of date_union type which
				contains the date for which price/yield is to be
				calculated.

		in_price_parm = Input parameter of type pointer to long double
				which contains the clean price from which
				yield will be calculated.

		out_price_parm= Output parameter of type pointer to long double
				which contains the clean price calculated from yield.

		acc_int_parm =  Input parameter of type pointer to long double
				which contains the accrued interest as of
				py_date_parm.

		first_int_parm= Input parameter of type pointer to long double
				which contains the interest payment expected on
				the next coupon date. This parameter is not
				currently used

		nom_adj_parm =  Input parameter of type pointer to long double
				which contains an adjustment to the current
										  nominal amount. This parameter is not currently used.

		in_yield_parm = Input parameter of type pointer to long double
				which contains the yield from which the price
				will be calculated.

		out_yield_parm= Output parameter of type pointer to long double
				which contains the yield calculated from price.

		py_parm_parm =  Input parameter of type py_parms which contains
				various parameters related to price yield
				calculations. Some of the fields should always
				be set and others are used for customizing the
				calculations. For now the following values should
				be used:

				parm_use always = py_yes_parm_use.

				yield_meth = one of the py_xxx_yield_meth symbols.

				calc_what = one of py_yield_from_price_calc_what
						or py_price_from_yield_calc_what.

				cpr_rate = any number between 0 and 100,
					only used if yield_meth = py_cpr_yield_meth.

				current_factor always = 1.

		ex_coup_parm =  input parameter of type char indicating whether this
				is an ex-coupon period. It must be either true
                                or false.

		holi_chan_parm=	Input parameter of unsigned int type which is
				the file channel for the holiday file.
				Currently not used.

		event_chan_parm=Input parameter of unsigned int type which is
				the file channel for the instrument event file.
                                Currently not used.

		duration_parm =	Output parameter of type pointer to long double
				which returns duration (Macaulay's).

		modified_duration_parm   =
				Output parameter of type pointer to long double
				which returns modified duration.

		holi_parm =	Input parameter of type holidays_struct array
				which holds the holiday schedule. For an
				explanation of how to set up holiday dates or
				rules see the holiday_struct description. To
				indicate that no holidays are used, the first
				element of the array should be set as:

				holi_parm[0].holi_date.first_date.date.years = io_no_use

		convexity_parm=	Output parameter of type pointer to long double
				which returns convexity.

		pvbp_parm     =	Output parameter of type pointer to long double
				which returns Price change for a Yield 01
				increase.

		redemps_array_parm =
				Input parameter of type redemps_struc array
				used for sinking fund schedules. Not currently
				used.

		rate_array =
				Input parameter of type insevent_struct array
				which contains the rates for a floater.

		return value =  of unsigned long type gives completion status.

    Called by:	<[]
	 }*/
	/*{ Global variables.}*/
/*
int pay_array_index = 0;
int redemps_array_index = 0;

boolean fast_calc = istrue;

pay_struc  pay_array_a[max_coups];
redemps_struc * part_pay_array_a;
redemps_struc even_redemps[max_coups];
*/

unsigned long 	_PYFUNCS py_calc(instr in_instr_parm, date_union py_date_parm,
			long double *in_price_parm, long double *out_price_parm,
			long double *acc_int_parm, long double *first_int_parm,
			long double *nom_adj_parm, long double *in_yield_parm,
			long double *out_yield_parm, py_parms py_parm_parm,
			char ex_coup_parm, unsigned int holi_chan_parm,
			unsigned int event_chan_parm, long double *duration_parm,
			long double *modified_duration_parm
//			, holidays_struct holi_parm []
			,const set<string> &holiSet
			,long double *convexity_parm, long double *pvbp_parm,
			redemps_struc redemps_array_parm[], insevent_struct rate_array []
			,
			pay_struc  pay_array_a[],
			redemps_struc  part_pay_array_a[],
			redemps_struc even_redemps[]
			)

{

#include "locals.h"
char	eligible_result = 0;	/*{Holds result of eligibility check.}*/
char 	py_period_length = 0;	/*{ py_period_length holds the rule for period length.}*/
char 	simp_comp_frac = 0;	/*{ simp_comp_frac indicates whether simple or compound discounting is used in a fractional period.}*/
char 	first_simp_comp_frac = 0; /*{ first_simp_comp_frac indicates whether simple or compound discounting is used in the first period.}*/
char 	redemp_sched = 0;		/*{ redemp_sched holds the rule for the redemption schedule.}*/
char 	pay_adj = 0;		/*{ pay_adj holds the rule for the non business date adjustments.}*/
char 	force_par = 0;		/*{ force_par holds the rule for forcing par. }*/
char 	skip_odd = 0;		/*{ skip_odd holds the rule for ignoring odd coupons. }*/
char 	py_rule_hold = 0;
char  adj_dir = 1;
long 	days_sett_to_mat = 0;	/*{ days_sett_to_mat is days from settlement to maturity.}*/

long double days_in_year = 0;	/*{ days_in_year is the normal number of days in a year for this method.}*/
long double cap_tax_adj = 0;	/*{ cap_tax_adj holds the capital gains tax adjustment.}*/
long double inc_tax_adj = 0;	/*{ inc_tax_adj holds the income tax adjustment.}*/
long double reinvest_factor = 0;	/*{ reinvest_factor holds the factor by which a payment must be multiplied to assume a reinvestment rate different from the yield.}*/
long double comp_freq = 0;	/*{ Holds the frequency of compounding per year.}*/
long double comp_freq_hold = 0;	/*{ Holds the frequency of compounding per year.}*/
long double pay_freq = 0;	/*{ Holds the frequency of payments.}*/
long double freq_adj = 0;	/*{ Holds the frequency of payments.}*/
long double sett_2_first_fact = 0;
long double simp_frac = 0;
long double comp_frac = 0;
long double price_var = 0;		/*{ Price_var holds the acceptable price variance when calculating yield.}*/
long double price_diff = 0;		/*{ Price_diff holds the latest difference between sought price and calculated price.}*/
long double start_price = 0;
long double start_yield = 0;
long double work_price = 0;
long double work_yield = 0;
long double work_duration = 0;
long double redemp_factor = 0;
long double pv_redemps = 0;
long double pv_coups = 0;
long double pv_factor = 0;
long double pv_part_pay = 0;
long double dummy_double = 0;
long double coups_prime = 0;
long double coup_prime_factor = 0;
long double redemps_prime = 0;
long double part_pay_prime = 0;
long double curr_nom = 0;
long double dirt_price_plus = 0;
long double dirt_price_minus = 0;
long double lag_adj_price = 0;
long double lag_adj_prime = 0;
long double lag_adj_duration = 0;
long double curr_redemp = 0;
long double redemp_duration = 0;

/* Parameter hold fields begin.*/

long double in_price = 0;
long double out_price = 0;
long double acc_int = 0;
long double first_int = 0;
long double nom_adjustment = 0;
long double nom_adj_int_calc = 0;
long double in_yield = 0;
long double out_yield = 0;
long double total_payment = 0;
long double duration = 0;
long double modified_duration = 0;
long double convexity = 0;
long double pvbp = 0;

char ex_coup = 0;
char py_cal_num = 0;
char py_cal_den = 0;
char py_day_count = 0;

unsigned int coup_count = 0;	/*{ coup_count holds the total number of future coupons.}*/
unsigned int even_redemps_count = 0;	/*{ even_redemps_count holds the total number of future even redemptions.}*/
unsigned int holi_chan = 0;
unsigned int event_chan = 0;

int	date_cmp =0;
int	total_part_pay = 0;
unsigned int	element_count = 0;
int     coups_left = 0;
int     iter_count = 0;
int     iter_count_save = 0;
int     max_iter = 10000;

int pay_array_index = 0;
int redemps_array_index = 0;
booleans fast_calc = istrue;


booleans second_pass = isfalse;
booleans third_pass = isfalse;

date_union py_date; 		/*{ py_date is the base date for calculations.}*/
instr	in_instr;		/*{ instrument is the instrument for calculations.}*/
py_parms py_parm;

/* Parameter hold fields end.*/

date_union redemp_date; 	/*{ redemp_date is the date used for redemption when a single date is used.}*/
date_union dummy_date;
date_union next_date;
date_union prev_date;

//	strcpy (module_name,"py_calc");

	in_price = *in_price_parm;
	out_price = *out_price_parm;
	acc_int = *acc_int_parm;
	first_int = *first_int_parm;
	nom_adjustment = *nom_adj_parm;
	in_yield = *in_yield_parm;
	out_yield = *out_yield_parm;
	ex_coup = ex_coup_parm;
	holi_chan = holi_chan_parm;
	event_chan = event_chan_parm;
	py_date = py_date_parm;
	in_instr = in_instr_parm;
	py_parm = py_parm_parm;
	duration = *duration_parm;
	modified_duration = *modified_duration_parm;
	convexity = *convexity_parm;
	pvbp = *pvbp_parm;
	duration = 0;
	work_duration = 0;
	modified_duration = 0;
	convexity = 0;
	pvbp = 0;
	curr_nom = 1;
	py_rule_hold = py_parm.calc_what;

	/*{ Validate eligibility for py_calc.}*/

	py_eligible_check(&in_instr, py_eligible_general, &eligible_result);


	if (eligible_result == py_no_eligible)
	{

	  return_status = return_err_py_incomp;
	  goto py_calc_end;

	}

	return_status = py_force_par(&force_par, &py_parm);


	if (return_status)
	{
	  goto py_calc_end;
	}

	if (force_par == py_yes_force_par)
	{

	  if ((py_parm.calc_what == py_yield_from_price_calc_what) &&
		(in_instr.redemp_price == in_price))
	  {

		 out_yield = in_instr.rate_offset;
		 goto py_calc_end;

	  }
	  else
	  {
		 if (in_instr.rate_offset == in_yield)
		 {

			out_price = in_instr.redemp_price;
			goto py_calc_end;


		 }

	  }

	}

	/*{ Check whether odd coupons should be ignored.}*/

	return_status = py_skip_odd(&skip_odd, &py_parm);


	if (return_status)
	{
	  goto py_calc_end;
	}

	/*{ Calculate the normal number of days in a year.}*/

	return_status = py_cal_set(&py_cal_num, &py_cal_den, &in_instr,
			&py_parm);

	if (return_status)
	{
	  goto py_calc_end;
	}

	return_status = py_day_count_set(&py_day_count, &in_instr, &py_parm);

	if (return_status)
	{
	  goto py_calc_end;
	}

	return_status = py_days_in_year(&days_in_year, py_cal_num, py_cal_den);

	if (return_status)
	{
	  goto py_calc_end;
	}

		  /*{ Adjust the current nominal for any sinking funds.}*/

	if (in_instr.redemps != 0)

	{

	  return_status = redemp_adj (in_instr, py_date, &curr_redemp,
		holi_chan_parm
//		, holi_parm
		,holiSet
		, &redemp_date);

	  if (return_status)
	  {
		 goto py_calc_end;
	  }

			 /*{ Modify the maturity date if average life is indicated.}*/

	  if (py_parm.redemp_sched != py_equivalent_redemp_sched)
	  {

		 return_status = forecast(redemp_date,
			  0,
			  -1,
			  date_act_cal,
			  &dummy_date);

		 if (return_status != return_success)
		 {

			goto py_calc_end;
		 }

		 return_status = n_p_pay(in_instr
			 , dummy_date
			 , &prev_date
			 ,&next_date
			 , holi_chan
//			 , holi_parm
			,holiSet
			 );

		 if (return_status != return_success)
		 {

			goto py_calc_end;

		 }

		 datecpy(in_instr.mat_date.date_string,redemp_date.date_string);

		 datecpy(in_instr.pre_last_pay.date_string,dummy_date.date_string);

		 in_instr.redemps = 0;
	  }
	}


	/*{ Calculate the days from settlement to maturity if not a perpetuity.}*/

	return_status = py_days_sett_to_mat(&days_sett_to_mat, py_date,
				&in_instr);

	if (return_status)
	{
	  goto py_calc_end;
	}

	/*{ Adjust the price for nominal payments.}*/

	return_status = nom_adj ( &in_instr,
				 py_date,
				 &dummy_date,
				 &dummy_date,
				 &curr_nom);


	if (return_status != return_success)
	{


		goto py_calc_end;
	}

	if (py_parm.calc_what == py_yield_from_price_calc_what)
	{
	  in_price = in_price * curr_nom;
	}
	/*{ Carry out the calculations according to the chosen method.}*/

	if (py_parm.yield_meth == py_mmdisc_yield_meth)
	{


		 if (in_instr.instr_class == instr_cashflow_class)
		 {

			return_status = return_err_py_incomp;
			goto py_calc_end;

		 }


		 return_status = py_mmdisc(days_sett_to_mat, days_in_year,
				in_price, &out_price, &out_yield, in_yield,
				&in_instr, &py_parm, &pvbp);

		 if (return_status)
		 {
		 }
		 goto py_calc_end;

	}

	if (py_parm.yield_meth == py_curr_yield_meth)
	{
		 if (py_parm.calc_what == py_yield_from_price_calc_what)
		 {

				  out_yield = in_instr.rate_offset/in_price;

		 }
		 else
		 {

			out_price = in_instr.rate_offset/in_yield;

		 }


		 goto py_calc_end;

	}

	if (py_parm.yield_meth == py_simp_yield_meth)
	{

		 return_status = py_simp(days_sett_to_mat, days_in_year,
				in_price, &out_price, &out_yield, in_yield,
				&in_instr, &py_parm, &pvbp);
		 if (return_status)
		 {
		 }
		 goto py_calc_end;

	}

	/*{ Establish compounding frequency.}*/

	return_status = py_comp_freq(&comp_freq, &in_instr, &py_parm,
			&pay_freq, &comp_freq_hold);
	if (return_status)
	{
		goto py_calc_end;
	}

	if (comp_freq > pay_freq)
	{
	  freq_adj = pay_freq;
	}
	else
	{
	  freq_adj = comp_freq;
	}

	/*{ Establish period length.}*/

	return_status = py_per_len( &py_period_length, &py_parm);
	if (return_status)
	{
		goto py_calc_end;
	}

	/*{ Determine non business date adjustment rules.}*/

	return_status = py_pay_adj( &pay_adj, &py_parm, &py_period_length);
	if (return_status)
	{
		goto py_calc_end;
	}

		  /*{ Determine the number of coupon payments to maturity. }*/

	if (in_instr.instr_class == instr_cashflow_class)

	{

	  pay_array_a[0].time_to_pay = 0;
	  coups_left = pay_array_a[0].last_element;
	  pay_array_index = coups_left;

	  in_instr.instr_class = instr_euro_class;

	  return_status =	classdef(&in_instr);

	  if (return_status != return_success) {


		  goto py_calc_end;

	  }

	  in_instr.instr_class = instr_cashflow_class;
	  in_instr.pay_freq.freq = (unsigned char)(12/comp_freq);
	  in_instr.cal_num		= py_cal_num;
	  in_instr.cal_den 		= py_cal_den;
	  datecpy(in_instr.issue_date.date_string,py_date.date_string);
	  datecpy(in_instr.accrue_date.date_string,in_instr.issue_date.date_string);

	}
	else
	{

	  return_status = coups_to_mat(&coups_left
		  , in_instr
		  , py_date
		  ,	holi_chan
//		  , holi_parm
			,holiSet
		  , pay_freq
		  );

	  if (return_status != return_success)
	  {


		 goto py_calc_end;
	  }

	}

	/*{ Determine whether the fast calculation (closed formula)
		can be used.}*/
/*
	return_status = fast_calc_check(&fast_calc, in_instr,
			comp_freq, pay_adj, pay_freq, py_parm,
			in_yield, py_day_count, coups_left);
*/
	return_status = fast_calc_check(&fast_calc, in_instr,
			comp_freq_hold, pay_adj, pay_freq, py_parm,
			in_yield, py_day_count, coups_left);


	if (return_status)
	{
		goto py_calc_end;
	}

	/*{ Load remaining coupons into an array.}*/

	return_status = py_coup_load(py_period_length, &simp_comp_frac,
				days_in_year, comp_freq, &sett_2_first_fact,
				&nom_adj_int_calc, ex_coup, py_cal_num,
				&coup_count, holi_chan, py_date, &in_instr,
				&py_parm, pay_adj, event_chan, skip_odd,
				&first_simp_comp_frac
//				, holi_parm
				,holiSet
				,days_sett_to_mat, pay_freq, &coups_left,
				rate_array, &pay_array_index, fast_calc,
				pay_array_a, first_int);

	if (return_status)
	{
	 goto py_calc_end;
	}

	if (in_instr.instr_class != instr_cashflow_class)

	{
	  /*{ Load even redemptions (falling on a coupon date) into an array.}*/

	  return_status = py_even_redemps_load( &redemp_sched, coup_count,
				&even_redemps_count, &in_instr, pay_adj,
				&py_parm, &redemps_array_index, pay_array_a,
				even_redemps);

	  if (return_status)
	  {
		 goto py_calc_end;
	  }

			 /*{ Process partial payments.}*/

	  if (in_instr.part_pays != 0)

	  {
/*
		 if (!(part_pay_array_a = new redemps_struc[in_instr.part_pays]))
		 {
			return_status = return_err_ins_mem;
			goto py_calc_end;
		 }
*/
		 return_status = py_part_pay_load( holi_chan
			 , py_date
			 , &in_instr
			 , pay_adj
			 ,	&total_part_pay
//			 , holi_parm
			,holiSet
			 , part_pay_array_a);

		 if (return_status)
		 {
			goto py_calc_end;
		 }

	  }

	}
	else
	{

	  coup_count = coups_left + 1;

	}

	/*{ establish acceptable price variance.}*/

	return_status = py_price_var(&price_var, &py_parm);
	if (return_status)
	{
		goto py_calc_end;
	}

	/*{ establish redemption schedule for calculations.}*/
		/*
	return_status = py_redemp_sched( &redemp_sched, &redemp_factor,
		even_redemps_count, py_parm);
	if (return_status)
	{
		goto py_calc_end;
	}
	*/
	/*{ establish starting price and yield values.}*/

	return_status = py_start_py(&start_price, &start_yield,
				&work_price, &work_yield, in_price, in_yield,
				&py_parm, &in_instr);

	if (return_status)
	{
		goto py_calc_end;
	}

	
	if ((comp_freq_hold != comp_freq) &&
		(py_parm.calc_what == py_price_from_yield_calc_what))

	{
	  work_yield = (pay_freq)*
	  (pow((1 + work_yield/comp_freq_hold),(comp_freq_hold/pay_freq)) - 1);

	}


	/*{ Iterate price/yield calculation until sought result is realized.}*/

	iter_count = 0;

	do
	{

		iter_count++;

		if (iter_count >= max_iter)
		{

			return_status = return_err_max_iter;
			goto py_calc_end;

		}

		work_duration = 0;
		pv_factor = 1;
		pv_coups = 0;
		pv_redemps = 0;
		pv_part_pay = 0;

		if (work_yield == 0)
		{

		  work_yield = price_var/1000;

		}


		/*{ Calculate present value of coupons.}*/

		return_status = py_pv_coups( py_period_length, simp_comp_frac,
					days_in_year, &comp_freq,
					sett_2_first_fact, &work_yield,
					&pv_coups, &pv_factor, py_cal_num,
					coup_count, py_date, &py_parm,
					&coups_prime, &coup_prime_factor,
					pay_freq, &simp_frac, &comp_frac,
					&work_duration, first_simp_comp_frac,
					holi_chan
//					, holi_parm
					, in_instr,
					coups_left, &comp_freq_hold, &pay_array_index,
					fast_calc, pay_array_a);

		if (return_status)
		{
			goto py_calc_end;
		}


		if (in_instr.instr_class != instr_cashflow_class)

		{


		  /*{ Calculate present value of partial payments.}*/


		  return_status = py_pv_part_pays(&work_duration, simp_comp_frac,
				in_instr.part_pays, py_date, py_cal_num,
				comp_freq, work_yield, days_in_year,
				&part_pay_prime, &pv_part_pay,
				first_simp_comp_frac, pay_freq, part_pay_array_a,
				fast_calc);

		  if (return_status)
		  {
			 goto py_calc_end;
		  }

		  /*{ Calculate present value of redemptions.}*/

		  return_status = py_pv_redemps(redemp_sched, &pv_redemps, pv_factor,
				coup_count, &redemps_prime, coup_prime_factor,
				&work_duration, days_sett_to_mat,
				days_in_year, work_yield, pay_freq, py_parm,
				fast_calc, pay_array_a, even_redemps, &redemp_duration);
		  if (return_status)
		  {
			 goto py_calc_end;
		  }

		}


		/*{ Where there is one payment left, calculate yield without iterating }*/

		date_cmp = datecmp(py_date.date_string, in_instr.issue_date.date_string);

		if (
			((even_redemps_count == 1) || ((date_cmp == 0) &&
		(even_redemps_count == 2))) &&
		(py_parm.calc_what == py_yield_from_price_calc_what)
			)

		{

		  if (simp_frac == 0)
		  {

					simp_frac = 1;

		  }


		  pay_array_index = (coup_count - 1);
		  redemps_array_index = (even_redemps_count - 1);

		  total_payment =
			(pay_array_a[pay_array_index].payment +
			even_redemps[redemps_array_index].redemps_factor);

		  work_yield =
			 (pow((total_payment/(work_price + acc_int)),(1/comp_frac)) - 1) *
				(long double) comp_freq/simp_frac;

		  work_duration = pay_array_a[pay_array_index].time_to_pay  *
				(in_price + acc_int);

		  price_var = 0;

		}

		else

		{

		  work_price = pv_coups + pv_redemps + pv_part_pay - acc_int;

		  if (py_parm.calc_what == py_price_from_yield_calc_what)
		  {

			 price_var = 0;

		  }
		  else
		  {
			 /*{ Adjust yield for next iteration.}*/

			 price_diff = (fabs((in_price) - (work_price ))/in_price);

			 if (price_diff > price_var)
			 {
/*
		 work_yield = work_yield + (((in_price)- work_price)/
		  (coups_prime + redemps_prime + part_pay_prime));
*/

				work_yield = work_yield +  (((in_price)- work_price) /
					(coups_prime + redemps_prime + part_pay_prime))
					* freq_adj;

			 }
		  }
		}

		if ((price_var == 0) || (price_diff <= price_var) ||
			(second_pass) || (third_pass))
		{

		  if (second_pass)
		  {

			 dirt_price_plus = work_price + acc_int;

			 pvbp = out_price - (work_price/curr_nom);
			 work_yield = work_yield - .0002;
			 price_var = 1;
			 price_diff = price_var + 1;

			 second_pass = isfalse;
			 third_pass = istrue;

		  }
		  else
		  {

			 if (third_pass)
			 {

				dirt_price_minus = work_price + acc_int;
/*
		 if (fast_calc == true)
					  {
*/
				convexity = (((dirt_price_plus + dirt_price_minus) -
					2 * (out_price + acc_int)) / (out_price + acc_int))
					* 1000000;


				pvbp = (pvbp + ( (work_price/curr_nom) - out_price)) / 2;
				price_var = 0;

				third_pass = isfalse;

			 }

			 else
			 {

		 /*{ If the requested compound frequency is different from
		 the pay frequency, and yield from price is being calculated,
		 make a pass now with the desired compound frequency and
		 the adjusted yield, calculating price from yield for speed
		 and getting the proper duration, etc.}*/
/*
		 if (comp_freq_hold != comp_freq)

		 {
						 comp_freq = comp_freq_hold;
			work_yield = (comp_freq/pay_freq)*
			(pow((1 + work_yield),(pay_freq/comp_freq)) - 1);
			py_parm.calc_what == py_price_from_yield_calc_what;
			price_var = 1;
				  price_diff = price_var + 1;
			fast_calc = false;

		 }
		 else
					  {
*/
				out_price = work_price/curr_nom;
				out_yield = work_yield;

				  /*{ Calculate Duration and Convexity.}*/
/*
		 if (fast_calc == istrue)
		 {
			duration =
				(((1 + work_yield/comp_freq) / (work_yield / comp_freq)) *
				pv_coups / (out_price + acc_int )) +
				(((work_yield/comp_freq) - (in_instr.rate_offset / pay_freq))
				/ (work_yield / comp_freq))
				* work_duration * (1 - (pv_coups / (out_price + acc_int )));

				duration = duration / comp_freq;
		 }
		 else
*/
				duration = work_duration;
				if (fast_calc == isfalse)
				{
					duration = duration/(out_price + acc_int);
				}
				else
				{

					duration = (duration + redemp_duration)/ (out_price + acc_int);

				}
				modified_duration = duration/(1 + (out_yield/comp_freq));

				if (fast_calc == isfalse)
				{

					 /*{ Calculate Convexity}*/

			  /*{ First sum up the convexity components of the regular payments. }*/

					for (element_count = 0; element_count < coup_count;
						++element_count)
					{

						convexity = convexity +
						(pay_array_a[element_count].time_to_pay) *
						(pay_array_a[element_count].payment /
						pay_array_a[element_count].pv_factor) *
						(pay_array_a[element_count].time_to_pay + 1/comp_freq);

					}

					 /*{ Next add the redemption component.}*/

					pay_array_index = (coup_count - 1);

					if (in_instr.instr_class != instr_cashflow_class)
					{

						convexity = convexity +
						(pay_array_a[pay_array_index].time_to_pay) *
						(even_redemps[pay_array_index].redemps_factor /
						pay_array_a[pay_array_index].pv_factor) *
						(pay_array_a[pay_array_index].time_to_pay + 1/comp_freq);
					}

					convexity = convexity/((out_price + acc_int) *
					pow((1 + (out_yield/comp_freq)),comp_freq));

				}
				else
				{

				}

				  /*{ Set up second pass for pvbp.}*/

				iter_count_save = iter_count;
				second_pass = istrue;
				py_parm.calc_what = py_price_from_yield_calc_what;
				work_yield = work_yield + .0001;
				price_var = 1;
				price_diff = price_var + 1;

			 }
		  }
		}

	} while ((price_var != 0) && (price_diff > price_var));

	if (comp_freq_hold != comp_freq)

	{
	  out_yield = (comp_freq_hold)*
	  (pow((1 + out_yield/pay_freq),(pay_freq/comp_freq_hold)) - 1);

	}

/*
	if (in_instr.part_pays != 0)

	{

	  delete []  part_pay_array_a;

	}
*/
py_calc_end:

	py_parm.calc_what = py_rule_hold;

	*in_price_parm = in_price;
	*out_price_parm = out_price;
	*acc_int_parm = acc_int;
	*first_int_parm = first_int;
	*nom_adj_parm = nom_adjustment;
	*in_yield_parm = in_yield;
	*out_yield_parm = out_yield;
	ex_coup_parm = ex_coup;
	holi_chan_parm = holi_chan;
	event_chan_parm = event_chan;
	py_date_parm = py_date;
	py_parm_parm = py_parm;
	*duration_parm = duration;
	*modified_duration_parm = modified_duration;
	*convexity_parm = convexity;
	*pvbp_parm = pvbp;

	return return_status;
}

void	_PYFUNCS py_eligible_check(instr *in_instr, char check_type, char *eligible_result)
{

	*eligible_result = py_yes_eligible;

}

unsigned long	_PYFUNCS py_days_in_year(long double *days_in_year,
			char py_cal_num, char py_cal_den)

{

#include "locals.h"

	  switch (py_cal_den)
	  {
	  case date_NL365_cal:
	  case date_365_cal:
		 case date_act_cal:
		 {

			*days_in_year = 365;
			break;
		 }
		 case date_366_cal:
		 {

			 *days_in_year = 366;
			 break;
		 }
		 case date_365A_cal:
		 case date_365L_cal:
		 case date_actISDA_cal:
		 {

			*days_in_year = 365;
			break;
		 }
		 case date_30_cal:
		 case date_30eplus_cal:
		 {

			*days_in_year = 360;
			break;
		 }
		 case date_365_25_cal:
		 {

			*days_in_year = 365.25;
			break;
		 }
		 default:
		 {
			return_status = return_err_py_incomp;
			return return_status;
			break;
		 }
	  }
py_days_in_year_end:

	return return_status;

}

unsigned long	_PYFUNCS py_days_sett_to_mat(long *days_sett_to_mat, date_union py_date,
			instr *in_instr)

{

#include "locals.h"


	if ((in_instr->mat_date.date.centuries != 0) &&
			  (in_instr->instr_class != instr_cashflow_class))
	{

	  return_status = tenor (py_date,
				in_instr->mat_date,
				in_instr->cal_num,
				days_sett_to_mat);

	  if (return_status != return_success) {


		return return_status;

	  }
	}

py_days_sett_to_mat_end:

	return return_status;

}

unsigned long	_PYFUNCS py_mmdisc(long days_sett_to_mat, long double days_in_year,
			long double in_price, long double *out_price,
			long double *out_yield, long double in_yield,
			instr *in_instr, py_parms *py_parm,
			long double *pvbp)

{

#include "locals.h"
char eligible_result;
long double	disc_rate;		/*{ disc_rate is the discount rate.}*/

	  /*{ Validate eligibility for mmdisc.}*/

	  py_eligible_check(in_instr, py_mmdisc_yield_meth, &eligible_result);

	  if (eligible_result == py_no_eligible)
	  {

		 return_status = return_err_py_incomp;
		 return return_status;

	  }

	  switch (py_parm->calc_what)
	  {
		 case py_yield_from_price_calc_what:
		 {
			disc_rate = ((1- in_price) * days_in_year) /
				((long double)days_sett_to_mat);
			*out_yield = disc_rate;
			break;
		 }
		 case py_price_from_yield_calc_what:
		 {

			*out_price = (1 - (in_yield)*
				((long double)days_sett_to_mat/days_in_year));
			break;
		 }
		 default:
		 {

			return_status = return_err_py_incomp;
			return return_status;

			break;

		 }

	  }

py_mmdisc_end:
	return return_status;
}


unsigned long	_PYFUNCS py_simp(long days_sett_to_mat, long double days_in_year,
			long double in_price, long double *out_price,
			long double *out_yield, long double in_yield,
			instr *in_instr, py_parms *py_parm,
			long double *pvbp)

{

#include "locals.h"
char eligible_result;

long double rate;
long double temp_price;
long double temp_yield;
long double years_to_mat;

	  *pvbp = 0;
	  rate = in_instr->rate_offset;
	  years_to_mat = (days_sett_to_mat/days_in_year);

	  /*{ Validate eligibility for simp.}*/

	  py_eligible_check(in_instr, py_simp_yield_meth, &eligible_result);

	  if (eligible_result == py_no_eligible)
	  {

		 return_status = return_err_py_incomp;
		 return return_status;

	  }

	  switch (py_parm->calc_what)
	  {
		 case py_yield_from_price_calc_what:
		 {
			*out_yield = (rate + ((in_instr->redemp_price - in_price)/
			(years_to_mat))) / in_price;

			temp_price = in_price;
			temp_yield = *out_yield;

			break;
		 }
		 case py_price_from_yield_calc_what:
		 {
		  *out_price =
		  ((years_to_mat) * rate + in_instr->redemp_price)/
		  ((years_to_mat) * in_yield + 1);

				  temp_price = *out_price;
			temp_yield = in_yield;

			break;
		 }
		 default:
		 {

			return_status = return_err_py_incomp;
			return return_status;

			break;

		 }

	  }

	  *pvbp = (temp_price - ((years_to_mat) * rate + in_instr->redemp_price)/
		  ((years_to_mat) * (temp_yield + .01)+ 1));

	  *pvbp = *pvbp + (((years_to_mat) * rate + in_instr->redemp_price)/
		  ((years_to_mat) * (temp_yield - .01)+ 1) - temp_price);

	  *pvbp = *pvbp/2;

py_simp_end:
	return return_status;
}


unsigned long	_PYFUNCS py_cal_set(char *py_cal_num, char *py_cal_den, instr *in_instr,
			py_parms *py_parm)

{

#include "locals.h"


	*py_cal_num = in_instr->cal_num;
	*py_cal_den = in_instr->cal_den;

	if (py_parm->parm_use == py_yes_parm_use)
	{

	  if (py_parm->date_cal_num != date_no_cal)

	  {

		 *py_cal_num = py_parm->date_cal_num;

	  }

	  if (py_parm->date_cal_den != date_no_cal)

	  {

		 *py_cal_den = py_parm->date_cal_den;

	  }

	}


//py_cal_set_end:
	return return_status;
}

unsigned long	_PYFUNCS py_day_count_set(char *py_day_count, instr *in_instr,
			py_parms *py_parm)

{

#include "locals.h"


	*py_day_count = in_instr->day_count;

	if (py_parm->parm_use == py_yes_parm_use)
	{

	  if (py_parm->date_cal_num != date_no_cal)

	  {

		 *py_day_count = py_parm->day_count;

	  }

	}


//py_day_count_set_end:
	return return_status;
}

unsigned long	py_reinvest_factor(long double *reinvest_factor)

{

#include "locals.h"

  *reinvest_factor = 1;

//  py_reinvest_factor_end:
  return return_status;
}

unsigned long	_PYFUNCS py_per_len( char *py_period_length, py_parms *py_parm)

{

#include "locals.h"

	if ((py_parm->parm_use == py_yes_parm_use) && (py_parm->per_len != py_no_per_len))
	{

	  *py_period_length = py_parm->per_len;

	}
	else
	{

	  if (py_parm->yield_meth == py_mm_yield_meth)

	  {

		 *py_period_length = py_exact_per_len;

	  }
	  else
	  {
		 if ((py_parm->yield_meth == py_gm_yield_meth)||
		(py_parm->yield_meth == py_ty_yield_meth))
		 {

			*py_period_length = py_total_days_per_len;

		 }
		 else
		 {

			*py_period_length = py_uniform_per_len;

		 }
	  }
	}


//py_per_len_end:
	return return_status;
}

unsigned long	_PYFUNCS py_force_par( char *force_par, py_parms *py_parm)

{

#include "locals.h"

	if ((py_parm->parm_use == py_yes_parm_use) && (py_parm->force_par != py_empty_force_par))
	{

	  *force_par = py_parm->force_par;

	}
	else
	{

	  if (py_parm->yield_meth == py_corp_yield_meth)

	  {

		 *force_par = py_yes_force_par;

	  }
	  else
	  {
		 *force_par = py_no_force_par;

	  }

	}


//py_force_par_end:
	return return_status;
}

unsigned long	_PYFUNCS py_skip_odd( char *skip_odd, py_parms *py_parm)

{

#include "locals.h"

	if ((py_parm->parm_use == py_yes_parm_use) && (py_parm->skip_odd != py_empty_skip_odd))
	{

	  *skip_odd = py_parm->skip_odd;

	}
	else
	{

	  if (py_parm->yield_meth == py_muni_yield_meth)

	  {

		 *skip_odd = py_yes_skip_odd;

	  }
	  else
	  {
		 *skip_odd = py_no_skip_odd;

	  }

	}


//py_skip_odd_end:
	return return_status;
}

unsigned long	_PYFUNCS py_comp_freq(long double *comp_freq, instr *in_instr,
			py_parms *py_parm, long double *pay_freq,
			long double *comp_freq_hold)

{

#include "locals.h"


	if (in_instr->pay_freq.freq != 0)
	{

	  *pay_freq = 12/in_instr->pay_freq.freq;

	}

	if ((py_parm->parm_use == py_yes_parm_use) && (py_parm->comp_freq != 0))
	{

		*comp_freq = 12/py_parm->comp_freq;

	}
	else
	{

	  if (py_parm->yield_meth == py_bf_yield_meth)
	  {

		 *comp_freq = 1;

	  }
	  else
	  {
		 if (in_instr->pay_freq.period == event_sched_month_period)
		 {

			*comp_freq = *pay_freq;

		 }
		 else
		 {

			*comp_freq = 1;

		 }
	  }

	}

	*comp_freq_hold = *comp_freq;

	if ((py_parm->parm_use == py_yes_parm_use) &&
//		 (py_parm->calc_what == py_yield_from_price_calc_what) &&
		 (*comp_freq != *pay_freq))
	{
	  *comp_freq = *pay_freq;
	}



//py_comp_freq_end:
	return return_status;
}

unsigned long	_PYFUNCS py_pay_adj(char *pay_adj, py_parms *py_parm,
			char *py_period_length)

{

#include "locals.h"

	*pay_adj = event_sched_same_holiday_adj;


	if (*py_period_length == py_total_days_per_len)

	{

		if ((py_parm->parm_use == py_yes_parm_use) &&
		((py_parm->pay_adj == event_sched_next_holiday_adj) ||
		(py_parm->pay_adj == event_sched_prev_holiday_adj) ||
		(py_parm->pay_adj == event_sched_same_holiday_adj)))

		{

		  *pay_adj = py_parm->pay_adj;

		}

		else

		{

				 if ((py_parm->yield_meth == py_gm_yield_meth)||
					(py_parm->yield_meth == py_ty_yield_meth))
				 {

					*pay_adj = event_sched_next_holiday_adj;


				 }

		}

	}

//py_pay_adj_end:
	return return_status;
}

unsigned long	_PYFUNCS py_part_pay_load( unsigned int holi_chan, date_union py_date,
					instr *in_instr, char pay_adj, int *this_pay
//					,holidays_struct holi_parm []
					,const set<string> &holiSet
					, redemps_struc part_pay_array_a[])

{

#include "locals.h"

//char adj_hold;

int cmp_int = -1;
int element_count = 0;
int element_num = 0;

date_union date_hold;
date_union base_date;


		  if (in_instr->part_pays != 0)

		  {

			 datecpy(base_date.date_string,py_date.date_string);

			 for 	(element_count = 0;
				(element_count <= in_instr->part_pays);
				element_count++)
			 {

/*
		  cmp_int = datecmp(in_instr->part_pays_sched[element_count].pay_date.date_string,
					base_date.date_string);

		  if (cmp_int > 0)

		  {
*/
				part_pay_array_a[*this_pay].redemps_factor =
					-in_instr->part_pays_sched[element_count].payment;

				if (pay_adj != event_sched_same_holiday_adj)

				{

				  datecpy(date_hold.date_string, in_instr->pay_freq.first_date.date_string);

				  return_status = adj_date(&date_hold,
					  adj_date_non_to_bus,
					pay_adj,
					adj_date_yes_we,
					adj_date_yes_hol,
//					in_instr->holiday_code,
					holi_chan
//					,holi_parm
					,holiSet
					);

				  if (return_status != return_success)
				  {

					return return_status;

				  }

				  datecpy(part_pay_array_a[*this_pay].redemps_date.date_string,
					date_hold.date_string);

				}
				else
				{

					datecpy(part_pay_array_a[*this_pay].redemps_date.date_string,
						in_instr->part_pays_sched[element_count].pay_date.date_string);

				}

				++*this_pay;


			 }

		  }


py_part_pay_load_end:

	return return_status;

}



unsigned long	_PYFUNCS py_even_redemps_load(char *redemp_sched, unsigned int coup_count,
			unsigned int *even_redemps_count, instr *in_instr,
			char pay_adj, py_parms *py_parm, int *redemps_array_index,
			pay_struc pay_array_a [max_coups], redemps_struc even_redemps [max_coups])

{

#include "locals.h"


	*redemp_sched = py_parm->redemp_sched;

	if ((py_parm->parm_use == py_yes_parm_use) &&
		 (py_parm->redemp_sched == py_average_redemp_sched))
	{

		/*{ do average processing here. }*/

	}
	else
	{

		/*{ do equivalent processing here. }*/

	}
	/*
	*redemp_sched = py_average_redemp_sched;

	datecpy(redemp_date.date_string,
		even_redemps_array_a[*even_redemps_count].redemps_date.date_string);

	*redemp_factor = even_redemps_array_a[*even_redemps_count].redemps_factor;
	*/

	/*{ For now always set to equivalent.}*/
	*redemp_sched = py_equivalent_redemp_sched;

	/*{ For now assume bullet loans.}*/

	*even_redemps_count = coup_count - 1;

	*redemps_array_index = *even_redemps_count + 1;
/*
	if (!(even_redemps = new redemps_struc[redemps_array_index]))
	{
		 return_status = return_err_ins_mem;
		 goto py_even_redemps_load_end;
	}
*/
	datecpy(even_redemps[*even_redemps_count].redemps_date.date_string,
		pay_array_a[*even_redemps_count].pay_date.date_string);

	even_redemps[*even_redemps_count].redemps_factor = in_instr->redemp_price;

	even_redemps[*even_redemps_count].coup_num = *even_redemps_count;

	*even_redemps_count = *even_redemps_count + 1;

//py_even_redemps_load_end:

	return return_status;

}

unsigned long	_PYFUNCS py_price_var(long double *price_var, py_parms *py_parm)

{

#include "locals.h"
const long double def_price_var = 0.00000001;	/*{ def_price_var is the default price variance.}*/

	if (py_parm->calc_what == py_yield_from_price_calc_what)

	{
		 if (py_parm->price_var == 0)

		 {

		  *price_var = def_price_var;

		 }
		 else
		 {

		  *price_var = py_parm->price_var;

		 }
	}
	else
	{

		  *price_var = 0;

	}

//py_price_var_end:

	return return_status;

}

unsigned long	_PYFUNCS py_start_py(long double *start_price,
			long double *start_yield, long double *work_price,
			long double *work_yield, long double in_price,
			long double in_yield, py_parms *py_parm,
			instr *in_instr)

{

#include "locals.h"

	*start_price = in_price;

	if (py_parm->calc_what == py_yield_from_price_calc_what)
	{

		/*{ Establish average rate.}*/
/*
		if (in_instr->rate_offset == 0)

		{

		  *start_yield = .10;

		}
		else
*/
		{

		  *start_yield = in_instr->rate_offset/(*start_price);

		}
	}
	else
	{

		*start_yield = in_yield;

	}

	*work_price = *start_price;
	*work_yield = *start_yield;

//py_start_py_end:

	return return_status;

}

unsigned long	py_redemp_sched(char *redemp_sched, long double *redemp_factor,
			unsigned int even_redemps_count, _PYFUNCS py_parms py_parm)

{

#include "locals.h"

	*redemp_sched = py_parm.redemp_sched;

	if ((py_parm.parm_use == py_yes_parm_use) &&
		 (py_parm.redemp_sched == py_average_redemp_sched))
	{

		/*{ do average processing here. }*/

	}
	else
	{

		/*{ do equivalent processing here. }*/

	}

	/*
	*redemp_sched = py_average_redemp_sched;

	datecpy(redemp_date.date_string,
		even_redemps_array_a[*even_redemps_count].redemps_date.date_string);

	*redemp_factor = even_redemps_array_a[*even_redemps_count].redemps_factor;
	*/

	/*{ For now always set to equivalent.}*/
	*redemp_sched = py_equivalent_redemp_sched;

//py_redemp_sched_end:

	return return_status;

}

unsigned long	_PYFUNCS py_pv_part_pays(long double *work_duration, char simp_comp_frac,
				int total_part_pays, date_union py_date,
				char py_cal_num,
				long double comp_freq,
				long double work_yield,
				long double days_in_year,
				long double *part_pay_prime,
				long double *pv_part_pay,
				char first_simp_comp_frac,
				long double pay_freq,
				redemps_struc * part_pay_array_a,
				int fast_calc)

/*{ This process requires that the payments be before the first coupon.}*/

{

#include "locals.h"
int date_cmp;
int this_pay;
long days_to_pay;
long double period_fraction;
long double pv_factor;
long double comp_frac;
long double simp_frac;
long double yield_adj;
long double pv_this_part_pay;
long double part_pay_prime_factor;

	for (this_pay = 0, *pv_part_pay = 0, *part_pay_prime = 0;
		this_pay < total_part_pays; this_pay++)
	{

	  date_cmp = datecmp(py_date.date_string,
		part_pay_array_a[this_pay].redemps_date.date_string);

	  if (date_cmp < 0)
	  {

		 /*{ Determine the fraction of a period to the payment.}*/

		 return_status = tenor (py_date,
		part_pay_array_a[this_pay].redemps_date,
		py_cal_num,
		&days_to_pay);

		 if (return_status != return_success)
		 {


			return return_status;
		 }

		 period_fraction = days_to_pay * comp_freq/days_in_year;

		 switch (simp_comp_frac)
		 {
			case py_simp_frac_per:
			{

				comp_frac = 1;
				simp_frac = period_fraction;
				break;

			}
			default:
			{

			  simp_frac = 1;
			  comp_frac = period_fraction;
			  break;
			}
		 }

		 pv_factor =
				pow((long double) (1 + (simp_frac) * work_yield/comp_freq),comp_frac);

		 yield_adj = simp_frac * work_yield/comp_freq;

		 part_pay_prime_factor = ((-1) * comp_frac ) *
					((long double)1/pow((1 + (yield_adj)),(comp_frac * + 1))
					);
		 pv_this_part_pay = part_pay_array_a[this_pay].redemps_factor/ pv_factor;
		 *pv_part_pay = *pv_part_pay + pv_this_part_pay;
		 *part_pay_prime = *part_pay_prime +
			(part_pay_array_a[this_pay].redemps_factor * part_pay_prime_factor);


		 part_pay_array_a[this_pay].pv_factor = pv_factor;
		 part_pay_array_a[this_pay].prime_factor = part_pay_prime_factor;
		 part_pay_array_a[this_pay].time_to_pay =
			(simp_frac * comp_frac)/comp_freq;

		 if (fast_calc == isfalse)
		 {

			*work_duration = *work_duration +
			 (pv_this_part_pay * part_pay_array_a[this_pay].time_to_pay);

		 }
	  }

	}

py_pv_part_pays_end:

	return return_status;

}

unsigned long	_PYFUNCS py_pv_redemps(char redemp_sched, long double *pv_redemps,
			long double pv_factor, unsigned int coup_count,
			long double *redemps_prime, long double coup_prime_factor,
			long double *work_duration, long days_sett_to_mat,
			long double days_in_year, long double work_yield,
			long double pay_freq, py_parms py_parm, int fast_calc,
			pay_struc pay_array_a [max_coups],
			redemps_struc even_redemps [max_coups], long double *redemp_duration)

{

#include "locals.h"
unsigned int even_redemps_count;

	even_redemps_count = coup_count - 1;

	if (redemp_sched == py_equivalent_redemp_sched)

	{

	  /*{ Process all the even redemptions.}*/

	  /*{ For now just do bullet instruments.}*/

	  if (fast_calc == istrue)
	  {

		 if (py_parm.yield_meth != py_MBS_yield_meth)
		 {

			*pv_redemps = even_redemps[even_redemps_count].redemps_factor
				/ pay_array_a[coup_count].pv_factor;

			*redemps_prime = even_redemps[even_redemps_count].redemps_factor
			* pay_array_a[coup_count].prime_factor;

			*redemp_duration = *pv_redemps * pay_array_a[coup_count].time_to_pay;

/*
			redemp_duration = (*redemps_prime /
			(1 + work_yield / pay_freq));

			*redemps_prime = pay_array_a[coup_count].prime_factor
			* even_redemps[even_redemps_count].redemps_factor;

			redemp_duration = *redemps_prime * pay_array_a[coup_count].pv_factor;
*/


		 }

	  }
	  else
	  {

		 *pv_redemps = *pv_redemps +
		  ( even_redemps[even_redemps_count].redemps_factor/
			pay_array_a[even_redemps_count].pv_factor);

		 *redemps_prime = even_redemps[even_redemps_count].redemps_factor *
				pay_array_a[even_redemps_count].prime_factor;

		 *work_duration = *work_duration +
			(pay_array_a[even_redemps_count].time_to_pay *
			even_redemps[even_redemps_count].redemps_factor/
			pay_array_a[even_redemps_count].pv_factor);

	  }
	  /*{ Process all the uneven redemptions.}*/

	}
	else
	{

		/*{ Process the average redemption.}*/

	}


//py_pv_redemps_end:

	return return_status;

}

unsigned long  _PYFUNCS fast_calc_check(booleans *fast_calc, instr in_instr,
				long double comp_freq, char pay_adj,
				long double pay_freq, py_parms py_parm,
				long double in_yield, char py_day_count,
				int coups_left)
{

#include "locals.h"

  return_status = return_success;

  if(
		((in_instr.instr_class != instr_cashflow_class) &&
		 (in_instr.pay_type == instr_fixed_pay_type) &&
		 (in_instr.pay_sched == instr_str_pay_sched) &&
		 (py_day_count != date_act_360_day_count) &&
		 (py_day_count != date_act_365cd_day_count) &&
		 (pay_adj == event_sched_same_holiday_adj) &&
		 (in_instr.redemps == 0) &&
		 ! ((in_yield == 0) &&
	(py_parm.calc_what == py_price_from_yield_calc_what))
	 &&
		 !((py_parm.yield_meth == py_bf_yield_meth)&&(pay_freq != 1))
/*
	 &&
	 (comp_freq == pay_freq)
*/
		) ||
		(
		 (py_parm.yield_meth == py_MBS_yield_meth)
		)
	 )
  {

	 *fast_calc = istrue;

  }
  else
  {

	 *fast_calc = isfalse;
	 if (coups_left >= max_coups)
	 {

		return_status = return_err_max_coups;

	 }

  }


//func_end:

  return return_status;

}

unsigned long _PYFUNCS coups_to_mat( int *coups_left,
			instr in_instr,
			date_union py_date,
								unsigned int holi_chan,
//			holidays_struct holi_parm [],
			const set<string> &holiSet,
			long double pay_freq)

{

#include "locals.h"

int date_cmp;
int years_hold;
//int centuries_hold;

date_union start_date;
date_union curr_date;
date_union prev_coup;
date_union next_coup;



  /*{ Determine the next coupon.}*/

  return_status = n_p_pay(in_instr
	  , py_date
	  , &prev_coup
	  ,	&start_date
	  , holi_chan
//	  , holi_parm
	,holiSet
	  );

  if (return_status != return_success)
  {

	 return return_status;

  }

  /*{ First determine the number of whole years remaining. }*/

  years_hold = (in_instr.mat_date.date.years - start_date.date.years - 1) +
	100 * (in_instr.mat_date.date.centuries - start_date.date.centuries);

  /*{ Determine the periods in the whole years.}*/

  if (years_hold >= 0)

  {

	 *coups_left = (int)(years_hold * pay_freq);

  }
  else
  {

	 *coups_left = 0;

  }

  /*{ Determine the periods in the start year.}*/

  datecpy(curr_date.date_string, py_date.date_string);

  do
  {

	 return_status = n_p_pay(in_instr
		 , curr_date
		 , &prev_coup
		 ,&next_coup
		 , holi_chan
//		 , holi_parm
		,holiSet
		 );

	 if (return_status != return_success)
	 {

		return return_status;

	 }

	 datecpy(curr_date.date_string,next_coup.date_string);

	 date_cmp = datecmp(next_coup.date_string, in_instr.mat_date.date_string);

	 if ((start_date.date.centuries == next_coup.date.centuries) &&
		(start_date.date.years == next_coup.date.years))
	 {

		*coups_left = *coups_left + 1;

	 }

  }
  while ((start_date.date.years == next_coup.date.years) &&
	(date_cmp < 0));

  /*{ Determine the periods in the end year.}*/

  if  (! ((start_date.date.years == in_instr.mat_date.date.years) &&
	  (start_date.date.centuries == in_instr.mat_date.date.centuries)))
  {

	 datecpy(curr_date.date_string,in_instr.mat_date.date_string);
	 curr_date.date.days = 1;
	 curr_date.date.months = 1;
	 datecpy(start_date.date_string,curr_date.date_string);

	 do
	 {

		return_status = n_p_pay(in_instr
			, curr_date
			, &prev_coup
			,&next_coup
			, holi_chan
//			, holi_parm
			,holiSet
			);

		if (return_status != return_success) {

		  return return_status;

		}

		date_cmp = datecmp(prev_coup.date_string, start_date.date_string);

		if (date_cmp == 0)
		{

			date_cmp = datecmp(prev_coup.date_string, next_coup.date_string);

			if (date_cmp != 0)
			{

			 *coups_left = *coups_left + 1;

			}

		}


		datecpy(curr_date.date_string,next_coup.date_string);

		date_cmp = datecmp(next_coup.date_string, in_instr.mat_date.date_string);

		*coups_left = *coups_left + 1;

	 }
	 while (date_cmp < 0);

  }


func_end:

  return return_status;

}