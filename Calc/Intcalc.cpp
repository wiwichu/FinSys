#include "stdafx.h"
#include "datedec.h"
#include "gendec.h"
//#include "iodec.h"

_INTCALCS Int_Calcs()
{
}
/*
_INTCALCS Int_Calcs(CDB * DB_parm) : Instrument (DB_parm)
{

	DB_local = DB_parm;

//	DB_local->InitDB();

//	DB_local->GetStatementHandle(&localhandles);
}
*/
/*{intcalc accepts an instrument record and a base date and returns the
accrued interest and number of days of interest for that date.

	Usage:  unsigned long	intcalc(instr in_instr, date_union in_date_parm,
					long double *interest, int *int_days,
					unsigned int holi_chan,
					unsigned char ex_coup_ind,
					unsigned char total_per,
					*long double nom_adj,
					*long double sett_to_first_fact_parm,
					char redemp_adj,
					unsigned int event_chan,
					holidays_struct holi_parm,
					insevent_struct rate_array []
					*long double whole_period_factor)

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which interest is to be
				calculated.

		in_date_parm =	Input parameter of date_union type which
				contains the date to which interest is to be
				calculated.

		interest =	Output parameter of long double pointer type
				which contains the interest up to the in date
				on in_instr.

		int_days =	Output parameter of int pointer type which
				contains the number of days of accrued interest.

		holi_chan =	Input parameter of unsigned int type which is
				the file channel for the holiday file. Not
				currently used

		ex_coup_ind =	Input parameter of unsigned char type which
				indicates whether the passed date is:

					Not ex-coup = ex_coup_no
					Ex-coup	    = ex_coup_yes
					Should be determined by the routine =
					ex_coup_auto

		total_per =	Input parameter of unsigned char type which
				indicates whether interest for the entire
				period should be calculated. See
				int_xxx_total_per symbols for allowable values.

		nom_adj  =	Output parameter of type pointer to long double
				which returns the nominal adjustment used in
				calculating the interest.

		sett_to_first_fact_parm  =

				Output parameter of type pointer to long double
				which returns a factor representing the fraction
				of a whole period which is between the settlement
				date and the first coupon.

		redemp_adj =	Input parameter of type char which indicates
				whether the interest calculated should be
				adjusted by the portion of the nominal
				redeemed before the base date.

		event_chan =	Input parameter of unsigned int type which is
				the file channel for the instrument event file.
				Not currently used.


		holi_parm =	Input parameter of type holidays_struct array
				which holds the holiday schedule. For an
				explanation of how to set up holiday dates or
				rules see the holiday_struct description. To
				indicate that no holidays are used, the first
				element of the array should be set as:

				holi_parm[0].holi_date.first_date.date.years = io_no_use

		rate_array =	Input parameter of type insevent_struct array
				which holds the rates for floaters.

		whole_period_factor  =

				Output parameter of type pointer to long double
				which returns a factor representing the fraction
				of a year which this whole period is.
				
		return value =  of unsigned long type gives completion status.

    Called by:	<[]

}*/
	/*{ Global variables.}*/

	unsigned long 	_INTCALCS intcalc(instr in_instr
		, date_union in_date_parm
		,long double *interest
		, long *int_days
		,unsigned int holi_chan
		, char ex_coup_ind
		,char total_per
		, long double *nom_adj
		,long double *sett_to_first_fact_parm
		,char redeem_adj
		, unsigned int event_chan
//		,holidays_struct holi_parm []
		,const set<string> &holiSet
		,insevent_struct rate_array [max_rates]
		,	long double *whole_period_factor
		)

{

	#include "locals.h"
	booleans ex_coup = isfalse; /*{ ex_coup is true if the base date falls
				in the ex-coupon period.}*/
	booleans part_pay = isfalse; /*{ part_pay is true if partial payments
				occur in this period.}*/
	int	cmp_first_per = 0;	/*{ cmp_first_per is used for first period
				comparison results}*/

	int	cmpint = 0;	/*{ cmpint is used for holding comparison results}*/
	int	cmplast = 0;	/*{ cmplast is used for holding comparison results of last period}*/

	int	cmpint2 = 0;	/*{ cmpint2 is used for holding comparison results}*/

	int 	element_count = 0;

	int	months_per = 0;/*{ months_per is the number of months in a
				period.}*/

	int	days_per   = 0;/*{ days_per is the number of days in a period.}*/

	char	total_calc = int_no_total_per;	/*{ total_calc indicates whether
					interest for the entire period is claculated}*/

	long	days_to_next = 0; /*{ days_to_next holds the days from the
					base date to the next coupon date.}*/

	long	days_to_mat = 0; /*{ days_to_next holds the days from the
					base date to the maturity date.}*/

	long	divisor_days = 0; /*{ divisor_days holds the days in the divisor
				for interest calculations.}*/

	long double	comp_factor = 0; /*{ comp_factor holds the
					multiplication factor passed from one
					compound period to the next.}*/

	long double	curr_redemp = 0; /*{ curr_redemp holds the redemption adjustment which is currently
				effective.}*/

	long double	current_pool_factor = 0; /*{ current_pool_factor holds the
						current pool factor.}*/

	long double	sett_to_first_fact = 0;

	date_union	temp_date; /*{ temp_date is used as a date work field.}*/

	date_union	prv_pay;   /*{ prv_pay is a hold field for calculations.}*/

	date_union	nxt_pay;   /*{ nxt_pay is a hold field for calculations.}*/

//	date_union	redemp_start;  //{ redemp_start is the start date for the current redemption adjustment period.}

//	date_union	redemp_end;    //{ redemp_end is the end date for the current redemption adjustment period.}

	date_union	sub_per_start;	/*{ sub_per_start is the start date
					for sub periods.}*/

	date_union	sub_per_end; /*{ calc_end is the end date for sub
					periods.}*/

	date_union	quasi_prv_pay;	/*{ quasi_prv_pay is a quasi period
					boundary.}*/

	date_union	quasi_nxt_pay;  /*{ quasi_nxt_pay is a quasi period
					boundary.}*/

	date_union	calc_start;	/*{ calc_start is the start date for
					partial calculations.}*/

	date_union	calc_end;       /*{ calc_end is the end date for
					partial calculations.}*/

	date_union	in_date;

//	strcpy(module_name,"intcalc");

	*interest = 0;
	*int_days = 0;
	*nom_adj = 0;
	*sett_to_first_fact_parm = 0;
	*whole_period_factor = 0;


	*nom_adj = 1;

	comp_factor = 1;
	datecpy(in_date.date_string,in_date_parm.date_string);
	sett_to_first_fact = 0;
	*whole_period_factor = 0;

	/*{ Call nxt_prv_pay to determine period boundaries}*/

	return_status = n_p_pay(in_instr
		, in_date
		, &prv_pay
		, &nxt_pay
		,holi_chan
//		, holi_parm
		,holiSet
		);

	if (return_status != return_success)
	{
	  return return_status;
	}
	
	if (in_instr.cal_den == date_actISDA_cal 
		&& (prv_pay.date.years != nxt_pay.date.years))
	{
		//divide period by year and use 365/366 depending on leap year.
		date_union p_pay = prv_pay;
		date_union n_pay = nxt_pay;
		instr *inst = new instr(in_instr);
		date_union valueDate = in_date;
		do
		{
			if (p_pay.date.years != n_pay.date.years)
			{
				n_pay = p_pay;
				n_pay.date.months = 12;
				n_pay.date.days = 31;
				return_status = forecast(n_pay,
					0,
					1,
					date_act_cal,
					&n_pay);
				valueDate = n_pay;

				if (return_status != return_success)
				{
					return return_status;
				}
			}
			if (datecmp(in_date.date_string, valueDate.date_string) < 0)
			{
				valueDate = in_date;
			}
			long double interestParm;
			long int_daysParm;
			long double nom_adjParm;
			long double sett_to_first_factParm;
			long double whole_period_factorParm;
			date_union preValueDate = valueDate;
			return_status = forecast(valueDate,
				0,
				-1,
				date_act_cal,
				&preValueDate);
			if (return_status != return_success)
			{
				return return_status;
			}
			if (isLeapYear(preValueDate))
			{
				inst->cal_den = date_366_cal;
			}
			else
			{
				inst->cal_den = date_365_cal;
			}
			return_status = intcalc(*inst
				, valueDate
				, &interestParm
				, &int_daysParm
				, holi_chan
				, ex_coup_ind
				, total_per
				, &nom_adjParm
				, &sett_to_first_factParm
				, redeem_adj
				, event_chan
				, holiSet
				, rate_array
				, &whole_period_factorParm
				);
			if (return_status != return_success)
			{
				return return_status;
			}

			*interest += interestParm;
			*int_days += int_daysParm;
			*nom_adj = nom_adjParm;
			*sett_to_first_fact_parm += sett_to_first_factParm;
			*whole_period_factor += whole_period_factorParm;

			return_status = forecast(n_pay,
				0,
				1,
				date_act_cal,
				&p_pay);
			if (return_status != return_success)
			{
				return return_status;
			}

			n_pay = nxt_pay;
			inst->pay_freq.first_date = n_pay;
			inst->issue_date = valueDate;
			inst->accrue_date = valueDate;
			valueDate = in_date;
		} while (datecmp(p_pay.date_string, in_date.date_string) < 0);
		delete inst;
		return return_success;
	}

	if (in_instr.cal_den == date_365L_cal)
	{
		instr *inst = new instr(in_instr);
		if (isLeapYear(in_date))
		{
			inst->cal_den = date_366_cal;
		}
		else
		{
			inst->cal_den = date_365_cal;
		}
		return_status = intcalc(*inst
			, in_date
			, interest
			, int_days
			, holi_chan
			, ex_coup_ind
			, total_per
			, nom_adj
			, sett_to_first_fact_parm
			, redeem_adj
			, event_chan
			, holiSet
			, rate_array
			, whole_period_factor
			);
		if (return_status != return_success)
		{
			return return_status;
		}


		delete inst;
		return return_success;
	}


		  /* Note whether the first period is also the last.*/

	cmplast = datecmp(in_instr.mat_date.date_string,
			in_instr.pay_freq.first_date.date_string);

	/*{Check to see if interest for the entire period should be calculated.}*/

	if (total_per == int_yes_total_per)
	{

	 cmpint = datecmp(in_date.date_string,	in_instr.issue_date.date_string);
	 if (cmpint != 0)
	 {
	  cmpint = datecmp(in_date.date_string, prv_pay.date_string);
	  if (cmpint == 0)
	  {

		 return_status = forecast(in_date,
				  0,
				  -1,
				  date_act_cal,
				  &temp_date);

		 if (return_status != return_success)
		 {


			return return_status;

		 }

		 total_calc = int_yes_total_per;

		 return_status = n_p_pay(in_instr
			 , temp_date
			 , &prv_pay
			 , &nxt_pay
			 ,holi_chan
//			 , holi_parm
			,holiSet
			 );

		 if (return_status != return_success)
		 {

			return return_status;
		 }

		 /* { Set partial payment indicator if necessary.} */

		 if (in_instr.part_pays > 0)
		 {

			cmpint =
				datecmp(in_instr.part_pays_sched[in_instr.part_pays-1].pay_date.date_string,
				prv_pay.date_string);
			if (cmpint >= 0)
			{

			  part_pay = istrue;

			}
		 }
	  }
    }
	}
	if (in_instr.cal_den == date_365A_cal)
	{
		instr *inst = new instr(in_instr);
		if (isLeapDayInRange(prv_pay,nxt_pay))
		{
			inst->cal_den = date_366_cal;
		}
		else
		{
			inst->cal_den = date_365_cal;
		}
		return_status = intcalc(*inst
			, in_date
			, interest
			, int_days
			, holi_chan
			, ex_coup_ind
			, total_per
			, nom_adj
			, sett_to_first_fact_parm
			, redeem_adj
			, event_chan
			, holiSet
			, rate_array
			, whole_period_factor
			);
		if (return_status != return_success)
		{
			return return_status;
		}


		delete inst;
		return return_success;
	}


	/*{ Calculate days from settlement to next coupon.}*/

	return_status = tenor (in_date,
				nxt_pay,
				in_instr.cal_num,
				&days_to_next);

	if (return_status != return_success)
	{


				return return_status;
	}

	/*{ Initialize quasi period to actual period.}*/

	datecpy(quasi_prv_pay.date_string,prv_pay.date_string);
	datecpy(quasi_nxt_pay.date_string,nxt_pay.date_string);

	/*{ Set the number of interest days to the difference between the
	previous coupon and the base date.}*/

	return_status = tenor (prv_pay,
				in_date,
				in_instr.cal_num,
				int_days);

	if (return_status != return_success)
	{

	  return return_status;

	}

	/*{ Assume boundaries for interest calculation are previous coupon
	and base date.}*/

	datecpy(calc_start.date_string,prv_pay.date_string);
	datecpy(calc_end.date_string,in_date.date_string);

	/*{ Check whether this is an ex coupon period.}*/


	switch (ex_coup_ind)
	{
		 case ex_coup_yes:
		 {

			ex_coup = istrue;
			break;

		 }
		 case ex_coup_no:
		 {

			ex_coup = isfalse;
			break;

		 }
		 default:

		 {

			return_status = excoup( in_instr
				,  in_date
				, &ex_coup
			 , holi_chan
//			 , holi_parm
			,holiSet
			 );

			break;
		 }
	}

	if ( ex_coup)
	{

		 *int_days = -days_to_next; /*{ For an ex coupon case, the number
				of interest days is negative the
				number of days to the period end.}*/

		 /*{ Boundaries for interest calculation are base date and next
		 coupon.}*/

		 datecpy(calc_start.date_string,in_date.date_string);
		 datecpy(calc_end.date_string,nxt_pay.date_string);
	}

	/*{Start with the date boundaries at the start of the calculation
	period.}*/
/*
	datecpy(sub_per_end.date_string,calc_start.date_string);
	datecpy(sub_per_start.date_string,sub_per_end.date_string);
*/
	datecpy(sub_per_end.date_string,calc_end.date_string);
	datecpy(sub_per_start.date_string,calc_start.date_string);


	/*{ If instrument pays regularly, then set standard adjustment
	periods.}*/

	if (in_instr.pay_sched == instr_str_pay_sched)
	{

	  switch (in_instr.pay_freq.period)
	  {
		 case event_sched_day_period:

		 { days_per = in_instr.pay_freq.freq;
			break;
		 }

		 case event_sched_month_period:

		 { months_per = in_instr.pay_freq.freq;
			break;
		 }

		 case event_sched_end_period:

		 { months_per = 12;
			break;
		 }

		 default :

		 { 
			return_status = return_err_invalid_period;
			return return_status;
		 }
	  }
	}

	/*{ Check for irregular periods.}*/

	if (in_instr.pay_sched == instr_str_pay_sched)
	{

	  cmp_first_per = datecmp(in_date.date_string,
				in_instr.pay_freq.first_date.date_string);

	  if ((cmp_first_per < 0)||
		 ((cmp_first_per == 0)&&(total_calc == int_yes_total_per)))
	  {

		 /*{ If the base date is in the first coupon period, calculate interest for each
		 quasi period.}*/

		 /*{ Start with the quasi previous and next both set to the
		 next coupon date.}*/

		 datecpy(quasi_prv_pay.date_string,nxt_pay.date_string);
		 datecpy(quasi_nxt_pay.date_string,nxt_pay.date_string);

		 /*{ Push the quasi previous date backward until it is on
		 or before the start date.}*/

		 do
		 {

			return_status = forecast(quasi_nxt_pay,
					  -months_per,
					  -days_per,
					  in_instr.cal_num,
					  &quasi_prv_pay);

			if (return_status != return_success)
			{

				return return_status;
			}

			/*{ Make sure the derived date falls on the last day of
			the month, if this is the rule.}*/

			if (in_instr.pay_freq.month_day == date_last_day_in_month)
			{

				quasi_prv_pay.date.days = month_end(quasi_prv_pay);

			}

			cmpint = datecmp(quasi_prv_pay.date_string,calc_start.date_string);

			if (cmpint > 0)
			{

				datecpy(quasi_nxt_pay.date_string,quasi_prv_pay.date_string);

			}

		 } while (cmpint > 0);

	  }


	  else /*{ If the base date is after the first period, check
			to see if it is in the last period.}*/
	  {
		 cmpint = datecmp(prv_pay.date_string,
			in_instr.pre_last_pay.date_string);

		 if (cmpint == 0) /*{ If the base date is in the last
				coupon period, do irregular period calculations.}*/
		 {
			/*{Set next quasi period.}*/

			return_status = forecast(quasi_prv_pay,
				  months_per,
				  days_per,
				  in_instr.cal_num,
				  &quasi_nxt_pay);

			if (return_status != return_success)
			{

				return return_status;
			}

			/*{ Make sure the derived date falls on the last day of
		  the month, if this is the rule.}*/

			if (in_instr.pay_freq.month_day == date_last_day_in_month)
			{

				quasi_nxt_pay.date.days = month_end(quasi_nxt_pay);

			}

		 }
	  }
	}

	switch (in_instr.cal_den)
	{
		case date_actISDA_cal:
		case date_365L_cal:
		case date_365A_cal:
		case date_act_cal: 	/*{ If calendar denominator is ACT, then
				determine number of quasi periods (ACT is
				not permitted when payment period is in days).}*/
	  {

		/*{ Irregular periods is only an issue for regularly paying
		 instruments.}*/

		if (in_instr.pay_sched == instr_str_pay_sched)
		{

			cmp_first_per = datecmp(in_date.date_string,
				in_instr.pay_freq.first_date.date_string);

			/*{ If the base date is in the last
			coupon period, do irregular period calculations.}*/

			cmpint = datecmp(prv_pay.date_string,
			in_instr.pre_last_pay.date_string);

			if ((cmp_first_per < 0)||(cmpint == 0) ||
				((cmp_first_per == 0)&&(total_calc == int_yes_total_per)))
			{

				/*{ Accumulate interest over all the quasi periods.}*/
/*
		return_status = quasi_proc(in_instr, nxt_pay, holi_chan, event_chan,
					&sub_per_start, &sub_per_end, &comp_factor,
					months_per, days_per, &days_to_next,
					&divisor_days, &sett_to_first_fact, &quasi_prv_pay,
					&quasi_nxt_pay, &calc_end, in_date, nom_adj,
					rate_array );

		if (return_status != return_success) {

		  return return_status;
		}
*/

		/*{ Accumulate the interest over all the quasi periods.}*/

				do
				{

					/*{ Calculate the number of days in this period.}*/

					return_status = tenor (quasi_prv_pay,
						quasi_nxt_pay,
						in_instr.cal_den,
						&divisor_days);

					if (return_status != return_success)
					{
						return return_status;
					}

					//if (in_instr.cal_den == date_actISDA_cal)
					//{
					//	date_union end_date = in_date;
					//	cmpint = datecmp(in_date.date_string,
					//		quasi_nxt_pay.date_string);

					//	if (cmpint > 0)
					//	{
					//		end_date = quasi_nxt_pay;
					//	}

					//	double base_fact = 365;
					//	if (isLeapDayInRange(quasi_prv_pay, end_date))
					//	{
					//		base_fact = 366;
					//	}
					//	long perDays = 0;
					//	return_status = tenor(quasi_prv_pay,
					//		end_date,
					//		in_instr.cal_den,
					//		&perDays);
					//	if (return_status != return_success)
					//	{
					//		return return_status;
					//	}
					//	long per1Days = 0;
					//	long per2Days = 0;
					//	if (quasi_prv_pay.date.years == in_date.date.years)
					//	{
					//		per1Days = perDays;
					//	}
					//	else
					//	{
					//		date_union eoy = prv_pay;
					//		eoy.date.months = 12;
					//		eoy.date.days = 31;
					//		return_status = tenor(quasi_prv_pay,
					//			eoy,
					//			in_instr.cal_den,
					//			&per1Days);
					//		if (return_status != return_success)
					//		{
					//			return return_status;
					//		}
					//		return_status = tenor(
					//			eoy, end_date,
					//			in_instr.cal_den,
					//			&per2Days);
					//		if (return_status != return_success)
					//		{
					//			return return_status;
					//		}
					//	}
					//	double p1Fact = 0;
					//	double p2Fact = 0;
					//	if (isLeapYear(quasi_prv_pay))
					//	{
					//		p1Fact = (366.0 / base_fact)*(double)((double)per1Days / (double)perDays);
					//	}
					//	else
					//	{
					//		p1Fact = (365.0 / base_fact)*(double)((double)per1Days / (double)perDays);
					//	}
					//	if (isLeapYear(end_date))
					//	{
					//		p2Fact = (366.0 / base_fact)*(double)((double)per2Days / (double)perDays);
					//	}
					//	else
					//	{
					//		p2Fact = (365.0 / base_fact)*(double)((double)per2Days / (double)perDays);
					//	}
					//	divisor_days = divisor_days * (double)(p1Fact + p2Fact);
					//}
					if (
						(in_instr.cal_den == date_365L_cal && isLeapYear(in_date))
						&& !isLeapDayInRange(quasi_prv_pay, quasi_nxt_pay)
						)
					{
						divisor_days = divisor_days * 366 / 365;
					}

					cmpint = datecmp(quasi_prv_pay.date_string,
					  in_date.date_string);

					if (cmpint > 0)
					{

						cmpint = datecmp(quasi_nxt_pay.date_string,
							in_instr.mat_date.date_string);

						if ((cmpint > 0) && (cmp_first_per >= 0))
						{

							return_status = tenor (quasi_prv_pay,
								in_instr.mat_date,
								in_instr.cal_den,
								&days_to_next);

							if (return_status != return_success)
							{
								return return_status;

							}

							/*{ Add fraction of period to the number of periods
								between settlement and coupon.}*/

							sett_to_first_fact = sett_to_first_fact +
								((long double) days_to_next/
								(long double) divisor_days);

						}
						else
						{

						  /*{ Add one whole period to the number of
						  periods between settlement and coupon.}*/

						  sett_to_first_fact = sett_to_first_fact + 1;
						}
					}
					else
					{

						cmpint = datecmp(quasi_nxt_pay.date_string,
						in_date.date_string);

						if (cmpint > 0)
						{

						  cmpint = datecmp(quasi_nxt_pay.date_string,
							in_instr.mat_date.date_string);

						  if ((cmpint > 0) && (cmp_first_per >= 0))
						  {

							return_status = tenor (in_date,
								in_instr.mat_date,
								in_instr.cal_den,
								&days_to_next);

						  }
						  else
						  {

							/*{Calculate the number of days from
							settlement to end of quasi period.}*/

							  return_status = tenor (in_date,
								quasi_nxt_pay,
								in_instr.cal_den,
								&days_to_next);
						  }

						  if (return_status != return_success)
						  {

								return return_status;

						  }


						  /*{ Add fraction of period to the number of periods
								between settlement and coupon.}*/

						  sett_to_first_fact = sett_to_first_fact +
								((long double) days_to_next/
								(long double) divisor_days);
						}
					}

					/*{Annualize divisor days.}*/

					if (months_per != 0)
					{

						divisor_days = divisor_days * 12/ months_per;

					}

					/*{Interest is calculated in periods defined by rerate
					and compounding boundaries.}*/

					return_status = per_calc (&in_instr, &holi_chan, &event_chan,
						&sub_per_start, &sub_per_end, &comp_factor,
						&divisor_days, &quasi_nxt_pay, &calc_end,
						nom_adj, rate_array,whole_period_factor);

					if (return_status != return_success)
					{

						return return_status;
					}

					/*{Set next quasi period.}*/

					datecpy(quasi_prv_pay.date_string,quasi_nxt_pay.date_string);

					return_status = forecast(quasi_prv_pay,
						months_per,
						days_per,
						in_instr.cal_num,
						&quasi_nxt_pay);

					if (return_status != return_success)
					{

						return return_status;

					}

					/*{ Make sure the derived date falls on the last day of
						the month, if this is the rule.}*/

					if (in_instr.pay_freq.month_day == date_last_day_in_month)
					{

						quasi_nxt_pay.date.days = month_end(quasi_nxt_pay);

					}

					cmpint = datecmp(quasi_prv_pay.date_string,nxt_pay.date_string);

				} while (cmpint < 0);


			}
			else
			{

				/*{ The divisor days is the number of days in the period.}*/

				return_status = tenor (prv_pay,
					nxt_pay,
					in_instr.cal_den,
					&divisor_days);
				if (return_status != return_success)
				{
					return return_status;
				}

				//if (in_instr.cal_den == date_actISDA_cal)
				//{
				//	double base_fact = 365;
				//	if (isLeapDayInRange(prv_pay, in_date))
				//	{
				//		base_fact = 366;
				//	}
				//	long perDays = 0;
				//	return_status = tenor(prv_pay,
				//		in_date,
				//		in_instr.cal_den,
				//		&perDays);
				//	if (return_status != return_success)
				//	{
				//		return return_status;
				//	}
				//	long per1Days = 0;
				//	long per2Days = 0;
				//	if (prv_pay.date.years == in_date.date.years)
				//	{
				//		per1Days = perDays;
				//	}
				//	else
				//	{
				//		date_union eoy = prv_pay;
				//		eoy.date.months = 12;
				//		eoy.date.days = 31;
				//		return_status = tenor(prv_pay,
				//			eoy,
				//			in_instr.cal_den,
				//			&per1Days);
				//		if (return_status != return_success)
				//		{
				//			return return_status;
				//		}
				//		return_status = tenor(
				//			eoy,in_date,
				//			in_instr.cal_den,
				//			&per2Days);
				//		if (return_status != return_success)
				//		{
				//			return return_status;
				//		}
				//	}
				//	double p1Fact = 0;
				//	double p2Fact = 0;
				//	if (isLeapYear(prv_pay))
				//	{
				//		p1Fact = (366.0/base_fact)*(double)((double)per1Days/ (double)perDays);
				//	}
				//	else
				//	{
				//		p1Fact = (365.0 / base_fact)*(double)((double)per1Days / (double)perDays);
				//	}
				//	if (isLeapYear(in_date))
				//	{
				//		p2Fact = (366.0 / base_fact)*(double)((double)per2Days / (double)perDays);
				//	}
				//	else
				//	{
				//		p2Fact = (365.0 / base_fact)*(double)((double)per2Days / (double)perDays);
				//	}
				//	divisor_days = divisor_days * (p1Fact + p2Fact);
				//}

				if (
					(in_instr.cal_den == date_365L_cal && isLeapYear(in_date))
					&& !isLeapDayInRange(quasi_prv_pay, quasi_nxt_pay)
					)
				{
					divisor_days = divisor_days * 366 / 365;
				}


				/*{ Calculate fraction of period between settlement and coupon.}*/

				sett_to_first_fact =
					((long double) days_to_next/(long double) divisor_days);

				/*{Annualize divisor days.}*/

				if (months_per != 0)
				{

					divisor_days = divisor_days * 12/months_per;

				}

				/*{Interest is calculated in periods defined by rerate
					and compounding boundaries.}*/

				return_status = per_calc (&in_instr, &holi_chan, &event_chan,
					&sub_per_start, &sub_per_end, &comp_factor,
					&divisor_days, &quasi_nxt_pay, &calc_end,
					nom_adj,rate_array,whole_period_factor);
																														  
				if (return_status != return_success) {

					return return_status;
				}

			}

		} /* End of regularly paying instruments. */
		else
		{

			/* Irregular periods not yet completed.*/

		}

		break;

	  }

	  //case date_366_cal: 	/*{ If calendar denominator is 366, then
			//	determine number of quasi periods due to
			//	leap years.}*/
	  //{
		 ///*This method is not yet supported.*/
		 ///* For now always 366 */

		 //divisor_days = 366;

		 //break;
	  //}
	  case date_NL365_cal:
	  case date_365_cal: 	/*{ If calendar denominator is 365, days are
				simply divided by 365.}*/
	  {

		 /*{ For a 365 day denominator the divisor days is always 365.}*/

		 divisor_days = 365;

		 /*{ Calculate fraction of period between settlement and coupon.}*/

		 sett_to_first_fact = ((long double) days_to_next/
		((long double) divisor_days*(long double) months_per/12));

		 /*{Interest is calculated in periods defined by rerate
			and compounding boundaries.}*/

		 return_status = per_calc (&in_instr, &holi_chan, &event_chan,
				&sub_per_start, &sub_per_end, &comp_factor,
				&divisor_days, &nxt_pay, &calc_end, nom_adj,
				rate_array,whole_period_factor);

		 if (return_status != return_success)
		 {

			 return return_status;
		 }

		 break;
	  }
	  case date_366_cal: 	/*{ If calendar denominator is 365, days are
							simply divided by 365.}*/
	  {

		  /*{ For a 365 day denominator the divisor days is always 365.}*/

		  divisor_days = 366;

		  /*{ Calculate fraction of period between settlement and coupon.}*/

		  sett_to_first_fact = ((long double)days_to_next /
			  ((long double)divisor_days*(long double)months_per / 12));

		  /*{Interest is calculated in periods defined by rerate
		  and compounding boundaries.}*/

		  return_status = per_calc(&in_instr, &holi_chan, &event_chan,
			  &sub_per_start, &sub_per_end, &comp_factor,
			  &divisor_days, &nxt_pay, &calc_end, nom_adj,
			  rate_array, whole_period_factor);

		  if (return_status != return_success)
		  {

			  return return_status;
		  }

		  break;
	  }
	  case date_30_cal: 	/*{ If calendar denominator is 30, days are
				simply divided by 360.}*/
	  {

		 /*{ For a 360 day denominator the divisor days is always 360.}*/

		 divisor_days = 360;

		 /*{ Calculate fraction of period between settlement and coupon.}*/

		 sett_to_first_fact = (((long double) days_to_next)/
		((long double) divisor_days*(long double) months_per/12));

		 /*{Interest is calculated in periods defined by rerate
		  and compounding boundaries.}*/

		 return_status = per_calc (&in_instr, &holi_chan, &event_chan,
				&sub_per_start, &sub_per_end, &comp_factor,
				&divisor_days, &nxt_pay, &calc_end, nom_adj,
				rate_array,whole_period_factor);

		 if (return_status != return_success)
		 {

			 return return_status;
		 }

		 break;
	  }

	}


	if ((*int_days == 0) &&
		 (cmplast != 0 )


			  )
	{

	  *sett_to_first_fact_parm = 0;

	}
	else
	{

	  *sett_to_first_fact_parm = sett_to_first_fact;

	}

	/*Set interest to be returned.*/

	/*{ Check for the case when a whole
	period is calculated and an even amount results.}*/

	if (! (part_pay ) &&
		(in_instr.day_count != date_act_365cd_day_count) &&
		(in_instr.yield_meth != py_mm_yield_meth) &&
		(total_calc == int_yes_total_per) &&
		(in_instr.pay_type != instr_float_pay_type) &&
		(in_instr.pay_sched == instr_str_pay_sched) )

	{

	  cmpint = datecmp(prv_pay.date_string,
			quasi_prv_pay.date_string);

	  if (cmpint == 0)
	  {

		 cmpint = datecmp(nxt_pay.date_string,
			quasi_nxt_pay.date_string);

		 if (cmpint == 0)
		 {

			*interest = in_instr.rate_offset/ (12/months_per);
			goto redemp_proc;

		 }

	  }

	}

	if (ex_coup == istrue)
	{

	  *interest = -1*(comp_factor - 1);

	}

	else
	{

	  *interest = comp_factor - 1;

	}

redemp_proc:

	if (redeem_adj == int_yes_redemp_adj)

	{

	  /*{ Get the redemption adjustment period boundaries.}*/

	  return_status = redemp_adj ( in_instr,
				 in_date,
				 &curr_redemp,
				 holi_chan,
//				 holi_parm,
				holiSet,
				 &temp_date);

	  if (return_status != return_success)
	  {

		return return_status;
	  }
	  else
	  {

		 *interest = *interest * curr_redemp;

	  }
	}

	/*{ Get the current pool factor. }*/

	return_status = get_pfactor (in_instr ,
				in_date,
				&current_pool_factor,
				event_chan);

	if (return_status != return_success)
	{

	  return return_status;
	}
	else
	{

		 *interest = *interest * current_pool_factor;

	}

intcalc_end:

	return return_status;
}


/*{ quasi_proc accepts an instrument record and the next pay date and
  calculates accrued interest over the period defined by variables
  inherited from the caller, detecting a period of irregular length.

	Usage:	unsigned long   quasi_proc (instr in_instr, date_union nxt_pay,
						 unsigned int holi_chan,
						 unsigned int event_chan,
						 date_union *sub_per_start,
						 date_union *sub_per_end,
						 long double *comp_factor,
						 int *months_per, int *days_per,
						 long *days_to_next, long *divisor_days,
						 long double *sett_to_first_fact,
						 date_union *quasi_prv_pay,
						 date_union *in_date,
						 long double *nom_adj,
						 insevent_struct rate_array [max_rates]);

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which the interest is to be
				calculated.

		nxt_pay  =	Input parameter of date_union type, indicating the
				end boundary of the current period.

		holi_chan  =	Input parameter of unsigned int type, which is
				the file channel for the holiday file.

		event_chan  =	Input parameter of unsigned int type, which is
				the file channel for the instrument event file.


		sub_per_start =	Input parameter of pointer to date_union type which is
				the start date for calculations.

		sub_per_end =	Input parameter of pointer to date_union type which is
				the end date for calculations.

		comp_factor =	Input/Output parameter of pointer to long double type
				which is the compounding factor.

		months_per =	Input/Output parameter of pointer to int type
				which indicates the months in the period.

		days_per =	Input/Output parameter of pointer to int type
				which indicates the days in the period.

		days_to_next =	Input/Output parameter of pointer to long type
				which indicates the days to the next payment.

		divisor_days =	Input/Output parameter of pointer to long type
				which indicates the days in the calculation divisor.

		sett_to_first_fact =

				Input/Output parameter of pointer to long double type
				which indicates the portion of the period from settlement
				to the first payment.

		quasi_prv_pay =	Input/Output parqameter of type pointer to date union
							which indicates the previous quasi payment.

		quasi_nxt_pay =	Input/Output parqameter of type pointer to date union
							which indicates the next quasi payment.

		calc_end =	Input/Output parqameter of type pointer to date union
							which indicates the end of the calculation period.

		in_date =	Input/Output parqameter of type pointer to date union
							which holds the base date for calculations.

		nom_adj =	Input/Output parqameter of type pointer to long double
							which holds the nominal adjustment.

		return value =  of unsigned long type gives completion status.

	 Called by:	<[int_calc]

}*/

/* quasi_proc deactivated


unsigned long quasi_proc (instr in_instr, date_union nxt_pay, unsigned int holi_chan,
unsigned int event_chan, date_union *sub_per_start, date_union *sub_per_end,
long double *comp_factor, int months_per, int days_per, long *days_to_next,
long *divisor_days, long double *sett_to_first_fact, date_union *quasi_prv_pay,
date_union *quasi_nxt_pay, date_union *calc_end, date_union in_date,
long double *nom_adj, insevent_struct rate_array [max_rates])

{

	#include "locals.h"

	date_union quasi_prv_pay_hold;
	date_union quasi_nxt_pay_hold;
	long divisor_days_hold = 0;

	int	cmpint = 0;	/*{ cmpint is used for holding comparison results}*/

/* quasi_proc deactivated

	datecpy(quasi_prv_pay_hold.date_string,quasi_prv_pay->date_string);
	datecpy(quasi_nxt_pay_hold.date_string,quasi_nxt_pay->date_string);

	/*{ Accumulate the interest over all the quasi periods.}*/
/* quasi_proc deactivated

	do {


	  /*{ Calculate the number of days in this period.}*/
/* quasi_proc deactivated

	  return_status = tenor (quasi_prv_pay_hold,
				quasi_nxt_pay_hold,
				in_instr.cal_den,
				&divisor_days_hold);


	  if (return_status != return_success) {

		  goto quasi_proc_end;
	  }

	  cmpint = datecmp(quasi_prv_pay_hold.date_string,in_date.date_string);

	  if (cmpint > 0) {

			/*{ Add one whole period to the number of periods between settlement and coupon.}*/

/* quasi_proc deactivated
			*sett_to_first_fact = *sett_to_first_fact + 1;

	  }
	  else
	  {

			cmpint = datecmp(quasi_nxt_pay_hold.date_string,in_date.date_string);

			if (cmpint > 0) {


		/*{Calculate the number of days from settlement to end of quasi period.}*/

/* quasi_proc deactivated
		return_status = tenor (in_date,
				quasi_nxt_pay_hold,
				in_instr.cal_den,
				days_to_next);

		if (return_status != return_success) {

		  goto quasi_proc_end;
		}

		/*{ Add fraction of period to the number of periods between settlement and coupon.}*/
/* quasi_proc deactivated

		*sett_to_first_fact = *sett_to_first_fact + ((long double) *days_to_next/(long double) divisor_days_hold);

			}
	  }

	  /*{Annualize divisor days.}*/
/* quasi_proc deactivated

	  if (months_per != 0) {

		 divisor_days_hold = divisor_days_hold * 12/ months_per;

	  }

	  /*{Interest is calculated in periods defined by rerate
		 and compounding boundaries.}*/
/* quasi_proc deactivated

	  return_status = per_calc (&in_instr, &holi_chan, &event_chan,
				sub_per_start, sub_per_end, comp_factor,
				&divisor_days_hold, &quasi_nxt_pay_hold, calc_end,
				nom_adj, rate_array);

	  if (return_status != return_success) {

		 goto quasi_proc_end;
	  }

	  /*{Set next quasi period.}*/
/* quasi_proc deactivated

	  datecpy(quasi_prv_pay_hold.date_string,quasi_nxt_pay_hold.date_string);

	  return_status = forecast(quasi_prv_pay_hold,
				  months_per,
				  days_per,
				  in_instr.cal_num,
				  &quasi_nxt_pay_hold);

	  if (return_status != return_success) {

		 goto quasi_proc_end;
	  }

	  /*{ Make sure the derived date falls on the last day of
	  the month, if this is the rule.}*/
/* quasi_proc deactivated

	  if (in_instr.pay_freq.month_day == date_last_day_in_month) {

		 quasi_nxt_pay_hold.date.days = month_end(quasi_nxt_pay_hold);

	  }

	  cmpint = datecmp(quasi_prv_pay_hold.date_string,nxt_pay.date_string);

	} while (cmpint < 0);


	datecpy(quasi_prv_pay->date_string,quasi_prv_pay_hold.date_string);
	datecpy(quasi_nxt_pay->date_string,quasi_nxt_pay_hold.date_string);
		  *divisor_days = divisor_days_hold;


quasi_proc_end:
	return return_status;

}

*/


/*{ per_calc accepts an instrument record and calculates accrued interest over
  a period defined by variables inherited from the caller. It iterates over rate
  change and compounding boundaries

	Usage:	unsigned long   per_calc (instr *in_instr, unsigned int *holi_chan, unsigned int *event_chan,
				date_union *sub_per_start, date_union *sub_per_end,
				long double *comp_factor, long *divisor_days,
				long double *curr_nom);

	where:  in_instr =	Input parameter of pointer to instr type which contains
				the instrument for which the interest is to be
				calculated.

	where:  holi_chan =	Input parameter of pointer to unsigned int type which is
				the file channel for the holiday file.

	where:  event_chan =	Input parameter of pointer to unsigned int type which is
				the file channel for the instrument event file.

	where:  sub_per_start =	Input parameter of pointer to date_union type which is
				the start date for calculations.

	where:  sub_per_end =	Input parameter of pointer to date_union type which is
				the end date for calculations.

	where:  comp_factor =	Input/Output parameter of pointer to long double type
				which is the compounding factor.

	where:  divisor_days =	Input/Output parameter of pointer to long type
				which is the calculation diviosor days.

	where:	quasi_nxt_pay =	Input/Output parameter of type pointer to date_union
        			which indicates the next quasi payment.

	where:	calc_end =	Input/Output parameter of type pointer to date_union
        			which indicates the end of the calculation period.

	where:  curr_nom =	Input/Output parameter of pointer to long double type
				which is the nominal adjustment.

		return value =  of unsigned long type gives completion status.

    Called by:	<[int_calc]

}*/

unsigned long _INTCALCS per_calc (instr *in_instr, unsigned int *holi_chan, unsigned int *event_chan,
			date_union *sub_per_start, date_union *sub_per_end,
			long double *comp_factor, long *divisor_days, date_union *quasi_nxt_pay,
			date_union *calc_end, long double *curr_nom,
			  insevent_struct rate_array [max_rates],
			  long double *period_factor)

{

	#include "locals.h"

	char	cal_hold = 0;

	int	cmpint = 0;	/*{ cmpint is used for holding comparison results}*/

	int	cmp_curr_calc_end = 0; /*{ cmp_curr_calc_end is used for holding
						 the comparison result of the current
						 date and the calc period end date.}*/

	int	cmp_curr_quas_nxt = 0; /*{ cmp_curr_quas_nxt is used for holding
						 the comparison result of the current
						 date and the next quasi date.}*/

	long	numerator_days = 0; /*{ numerator_days holds the days in the
				numerator for interest calculations.}*/

	long double	temp_double = 0;

	long double	int_accum = 0; /*{ int_accum is used to accumulate
					interest over several periods within
					a single coupon period.}*/

	long double	curr_rate = 0; /*{ curr_rate holds the rate which is currently
				effective.}*/

	date_union	comp_start;  /*{ comp_start is the start date for
					compounding.}*/

	date_union	comp_end;    /*{ comp_end is the end date for
					compounding.}*/

	date_union	rate_start;  /*{ rate_start is the start date for
					the current rate period.}*/

	date_union	rate_end;    /*{ rate_end is the end date for the
					current rate period.}*/

	date_union	nom_start;  /*{ nom_start is the start date for
					the current nominal adjustment period.}*/

	date_union	nom_end;    /*{ nom_end is the end date for the
					current nominal adjustment period.}*/

			 datecpy(&comp_start.date_string, sub_per_start->date_string);
			 datecpy(&comp_end.date_string, quasi_nxt_pay->date_string);
			 datecpy(&rate_start.date_string, sub_per_start->date_string);
			 datecpy(&rate_end.date_string, quasi_nxt_pay->date_string);
			 datecpy(&nom_start.date_string, sub_per_start->date_string);
			 datecpy(&nom_end.date_string, quasi_nxt_pay->date_string);

			 *curr_nom = 1;

			 do
			 {


				/*{ Get the compounding period boundaries.}*/

				return_status = comp_bounds ( in_instr,
					 *sub_per_start,
					 &comp_start,
					 &comp_end,
					 *holi_chan);


				if (return_status != return_success)
				{

					return return_status;
				}

				/*{ Get the current rate, and the rate period boundaries.}*/

				return_status = get_rate (  in_instr,
						*sub_per_start,
						&rate_start,
						&rate_end,
						&curr_rate,
						*holi_chan,
						*event_chan,
						rate_array);

				if (return_status != return_success)
				{

					return return_status;
				}

				/*{ Get the nominal adjustment period boundaries.}*/

				return_status = nom_adj ( in_instr,
					 *sub_per_start,
					 &nom_start,
					 &nom_end,
					 curr_nom);

				if (return_status != return_success)
				{

					return return_status;
				}

				/*{Set the sub period end to the narrowest boundary.}*/

				cmpint = datecmp(comp_end.date_string,rate_end.date_string);

				if (cmpint < 0)
				{

					datecpy(sub_per_end->date_string,comp_end.date_string);

				}
				else
				{

					datecpy(sub_per_end->date_string,rate_end.date_string);

				}

				cmpint = datecmp(sub_per_end->date_string,nom_end.date_string);

				if (cmpint > 0)
				{

					datecpy(sub_per_end->date_string,nom_end.date_string);

				}

				/*{Do not exceed the quasi-period.}*/

				cmpint = datecmp(sub_per_end->date_string,quasi_nxt_pay->date_string);

				if (cmpint >= 0)
				{

					datecpy(sub_per_end->date_string,quasi_nxt_pay->date_string);

				}

				/*{Do not exceed the calculation end date.}*/

				cmpint = datecmp(sub_per_end->date_string,calc_end->date_string);

				if (cmpint >= 0)
				{

					datecpy(sub_per_end->date_string,calc_end->date_string);

				}

				/*{Do calculation.}*/

				cal_hold = in_instr->cal_num;

				return_status = tenor (*sub_per_start,
				*sub_per_end,
				cal_hold,
				&numerator_days);

				if (return_status != return_success)
				{

					return return_status;

				}

				temp_double =  ((long double)numerator_days /
				(long double)*divisor_days);

				*period_factor = *period_factor + temp_double;

				temp_double =  curr_rate * temp_double;

				int_accum = *curr_nom * temp_double;

				/*{Compound if necessary}*/

				if (in_instr->comp_freq.period != event_sched_free_period)
				{

					*comp_factor = *comp_factor*( 1 + int_accum);

				}
				else
				{

					*comp_factor = *comp_factor + int_accum;

				}

				/*{Reset boundaries.}*/

				datecpy(sub_per_start->date_string,sub_per_end->date_string);

				cmp_curr_calc_end = datecmp(sub_per_start->date_string,calc_end->date_string);
				cmp_curr_quas_nxt = datecmp(sub_per_start->date_string,quasi_nxt_pay->date_string);


			 } while ((cmp_curr_calc_end < 0) && (cmp_curr_quas_nxt < 0));

per_calc_end:

	return return_status;

}

/*{get_pfactor accepts an instrument record and a base date and returns the
current pool factor.

	Usage:  unsigned long	get_pfactor(instr in_instr, date_union base_date,
					float *pfactor, unsigned int event chan)

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which the pool factor is to be
				determined.

		base_date =	Input parameter of date_union type which
				contains the date for which the current pool
				factor is to be determined.

		pfactor	 =     	Output parameter of long double type which
				contains the current pfactor.

		event_chan =	Input parameter of unsigned int type which
				is the file channel for the instrument event
				file.

		return value =  of unsigned long type gives completion status.

    Called by:	<[int_calc]

}*/


unsigned long   _INTCALCS get_pfactor (instr in_instr,
			  date_union base_date,
			  long double *pfactor,
			  unsigned int event_chan)

{
	#include "locals.h"

	int	str_cmp1 = 0;


/*{ Pool Factor processing is temporarily disabled, always returning 1.}*/

*pfactor = 1;
return return_status;



	  /* Look for a pool factor record for this instrument with an end date
	  after the base date. */
/*
	  string_size = instr_instr_code_len;

	  memcpy (&inev_key.segment_1, &in_instr.instr_code, string_size);
	  inev_key.segment_2 = insevent_factor_event;

	  string_size = date_len;

	  memcpy (&inev_key.segment_3, &base_date, string_size);

	  return_status = iogetkey (event_chan, 1,
			inev_key.segment_1, io_gt,
			inev_buff.instr_code);

	  switch  (return_status)
          {
	    case	io_eof:

	    {

              *pfactor = 1;

	      break;
	    }
	    case	return_success:

	    {

			string_size = instr_instr_code_len;
	      str_cmp1 = memcmp(&inev_key.segment_1,inev_buff.instr_code,string_size);

	      if (str_cmp1 == 0)
	      {

	        string_size = insevent_event_len;
	        str_cmp1 = memcmp(&inev_key.segment_2,&inev_buff.event,string_size);

			  if (str_cmp1 == 0)
	        {

	          string_size = date_len;
 	          str_cmp1 = memcmp (base_date.date_string, inev_buff.eff_start_date.date_string,string_size);

		  if (str_cmp1 < 0)
		  {

                    *pfactor = 1;

		  }
		  else
		  {

		    *pfactor = inev_buff.rate;

                  }

		}
		else
		{

                  *pfactor = 1;
		}

              }
	      else
			{

                *pfactor = 1;
	      }


              break;
	    }
	    default:

	      //errproc(return_status,module_name,"","","");

	      return return_status;

	  };
	}
	else
        {

	  *pfactor = 1;
	}
*/
get_pfactor_end:
	return return_status;
}

/*{get_rate accepts an instrument record and a base date and returns the
current rate and the boundary dates for when that rate is in effect.

	Usage:  unsigned long	get_rate(instr in_instr, date_union base_date,
					date_union *rate_begin, date_union *rate_end,
					float *rate, unsigned int holi_chan,
					unsigned int event chan)

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which the rate is to be
				determined.

		base_date =	Input parameter of date_union type which
				contains the date for which the current rate
				and boundaries are to be determined.

		rate_begin =	output parameter of pointer to date_union
				type which contains the date when the current rate
				takes effect.

		rate_end =	output parameter of pointer to date_union
				type which contains the date when the current rate
				is no longer in effect.

		rate	 =     	Output parameter of long double type which
				contains the current rate.

		holi_chan =	Input parameter of unsigned int type which
				is the file channel for the holiday file.

		event_chan =	Input parameter of unsigned int type which
				is the file channel for the instrument event
				file.

		return value =  of unsigned long type gives completion status.

	 Called by:	<[int_calc]

}*/


unsigned long   _INTCALCS get_rate (instr *in_instr,
			  date_union base_date,
			  date_union *rate_begin,
			  date_union *rate_end,
			  long double *rate,
			  unsigned int holi_chan,
			  unsigned int event_chan,
			  insevent_struct rate_array [max_rates])

{
	#include "locals.h"

	int	str_cmp1 = 0;

	int	str_cmp2 = 0;

		  int 	element_count = 0;
//	size_t		string_size;

	switch (in_instr->pay_type)
	{
	  case instr_fixed_pay_type:
	  {
			*rate = in_instr->rate_offset;
/*
			return_status = n_p_pay(*in_instr, base_date, rate_begin, rate_end, holi_chan);

			if (return_status != return_success) {

		return return_status;
			}     */
			break;
	  }
	  case  	instr_float_pay_type:
//				instr_stepped_pay_type:
	  {

			*rate = 0;

			for
			(str_cmp1 = 0, str_cmp2 = -1, element_count = 0;
			str_cmp1 <= 0 && str_cmp2 <= 0 &&
			element_count < rate_array[0].event_date.date.centuries;)
			{

				++element_count;

				str_cmp1 =
					datecmp(rate_array[element_count].eff_start_date.date_string,
					base_date.date_string);
				str_cmp2 =
					datecmp(rate_array[element_count].eff_end_date.date_string,
					base_date.date_string);

			}

			if (str_cmp1 <= 0 && str_cmp2 > 0)
			{

				datecpy(rate_begin->date_string,
				rate_array[element_count].eff_start_date.date_string);
				datecpy(rate_end->date_string,
				rate_array[element_count].eff_end_date.date_string);
				*rate = rate_array[element_count].rate;

			}

			return return_status;

			/* IO not yet supported.*/

			/* Look for a rate record for this instrument with an end date
			 after the base date. */
/*
			string_size = instr_instr_code_len;

			memcpy (&inev_key.segment_1, &in_instr->instr_code, string_size);
			inev_key.segment_2 = insevent_intrate_event;

			string_size = date_len;

			memcpy (&inev_key.segment_3, &base_date, string_size);

			return_status = iogetkey (event_chan, 1,
			inev_key.segment_1, io_gt,
			inev_buff.instr_code);

			switch  (return_status)
				  {
		case	io_eof:

		  {

						  *rate = 0;

			 break;
		  }
					 case	return_success:

		  {

			 string_size = instr_instr_code_len;
			 str_cmp1 = memcmp(&inev_key.segment_1,inev_buff.instr_code,string_size);

			 if (str_cmp1 == 0)
			 {

				string_size = insevent_event_len;
				str_cmp1 = memcmp(&inev_key.segment_2,&inev_buff.event,string_size);

				if (str_cmp1 == 0)
				{

				  string_size = date_len;
				  str_cmp1 = memcmp (base_date.date_string, inev_buff.eff_start_date.date_string,string_size);

			if (str_cmp1 < 0)
			{

								  *rate = 0;
			}
			else
			{

			  *rate = inev_buff.rate;
			  memcpy(rate_begin,inev_buff.eff_start_date.date_string,date_len);
			  memcpy(rate_end,inev_buff.eff_end_date.date_string,date_len);

								}

				}
				else
				{

								*rate = 0;
				}

			 }
			 else
			 {

				*rate = 0;
			 }


						  break;
		  }
		default:

			 //errproc(return_status,module_name,"","","");

			 return return_status;

			 break;
				  }
*/
			break;
	  }
	  default:
			break;
	};

get_rate_end:
	return return_status;
}

/*

	unsigned long   dummy_func (instr *in_instr,
						date_union base_date,
				date_union *comp_begin,
				date_union *comp_end,
				unsigned int holi_chan)

				{
										  return 0;
				}

*/
/*{comp_bounds accepts an instrument record and a base date and returns the
boundary dates for compounding around that date.

	Usage:	unsigned long   comp_bounds (instr in_instr,
				date_union base_date,
				date_union *comp_begin,
				date_union *comp_end,
				unsigned int holi_chan);

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which the boundaries are
				to be determined.

		base_date =	Input parameter of date_union type which
				contains the date for which the boundaries
				are to be determined.

		comp_begin =	output parameter of pointer to date_union
				type which contains the date when the
				current compounding period began.

		comp_end =	output parameter of pointer to date_union
				type which contains the date when the
				current compounding period ends.

		holi_chan =	input parameter of unsigned int which is the
				file channel for the holiday file.

		rate	 =	Output parameter of float type which
				contains the current rate.

		return value =  of unsigned long type gives completion status.

	 Called by:	<[int_calc]

}*/

	unsigned long   _INTCALCS comp_bounds (instr *in_instr,
				date_union base_date,
				date_union *comp_begin,
				date_union *comp_end,
				unsigned int holi_chan)

{
	#include "locals.h"

	switch (in_instr->comp_freq.period)
	{
	  case event_sched_free_period:
	  {
  /*
			return_status = n_p_pay(*in_instr, base_date, comp_begin, comp_end, holi_chan);

			if (return_status != return_success) {

		goto comp_bounds_end;

			} */
			break;
	  }
	  default:
	  {
			break;
	  }
	};

//comp_bounds_end:
	return return_status;
}

/*{excoup accepts an instrument record and a base date determines
whether the date is ex-coupon for the instrument.

	Usage:  unsigned long	excoup(instr in_instr, date_union in_date,
			boolean *ex_coup, unsigned int holi_chan,
			holidays_struct holi_parm [])

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which ex-coupon status is to be determined.

		in_date =	Input parameter of date_union type which
				contains the date for which ex-coupon is to be determined.

		ex_coup =	Output parameter of boolean type which
				indicates whether the passed date is ex-coupon or not:

		holi_chan =	Input parameter of unsigned int type which is
				the file channel for the holiday file.

		holi_parm =	input parameter of type holidays_struct array
                		which holds the holiday schedule

		return value =  of unsigned long type gives completion status.

    Called by:	<[intcalc]

}*/
/*
unsigned long	n_p_pay	(instr,
			date_union,
			date_union *,
			date_union *,
			unsigned int,
			holidays_struct []);
*/
unsigned long	_INTCALCS excoup(instr in_instr
			, date_union in_date
			,booleans *ex_coup
			, unsigned int holi_chan
//			,holidays_struct holi_parm []
			,const set<string> &holiSet
			)

{
	#include "locals.h"

	int	cmp_first_per;	/*{ cmp_first_per is used for first period
				comparison results}*/

	long	dummy_long = 0;

	long	days_to_next = 0; /*{ days_to_next holds the days from the
					base date to the next coupon date.}*/

//	date_union	temp_date; /*{ temp_date is used as a date work field.}*/

	date_union	prv_pay;   /*{ prv_pay is a hold field for calculations.}*/

	date_union	nxt_pay;   /*{ nxt_pay is a hold field for calculations.}*/

//	strcpy(module_name,"ex_coup");

	*ex_coup = isfalse;

	/*{ Call nxt_prv_pay to determine period boundaries}*/

	return_status = n_p_pay(in_instr
		, in_date
		, &prv_pay
		, &nxt_pay
		,holi_chan
//		, holi_parm
		,holiSet
		);

	if (return_status != return_success)
	{

	  return return_status;
	}

	cmp_first_per = datecmp(nxt_pay.date_string,
		in_instr.pay_freq.first_date.date_string);

	if ((in_instr.ex_coup_days != 0) ||
		((cmp_first_per == 0) &&
		(in_instr.neg_first == instr_yes_neg_first)))
	{

	  return_status = tenor (in_date,
			nxt_pay,
			in_instr.cal_num,
			&days_to_next);

	  if (return_status != return_success)
	  {

		 return return_status;

	  }

	  if ((days_to_next <= in_instr.ex_coup_days) ||
		  ((cmp_first_per == 0) &&
		  (in_instr.neg_first == instr_yes_neg_first)))
	  {

		 *ex_coup = istrue;

	  }
	}
ex_coup_end:
	return return_status;

}
/*{n_p_pay accepts an instrument record and a base date and returns the
next and previous pay days.

	Usage:  unsigned long	n_p_pay(instr in_instr, date_union in_date,
					date_union *prv_date,
					date_union *nxt_date,
					unsigned int holi_chan,
					holidays_struct holi_parm [])

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which dates are to be
				determined.

		in_date =	Input parameter of date_union type which
				contains the date around which pay dates are
				to be determined.

		prv_pay =	Output parameter of pointer to date_union type
				which contains the pay date less than or equal
				to in_date.

		nxt_pay =	Output parameter of pointer date_union type
				which contains the pay date greater than
				in_date.

		holi_chan =	Input parameter of unsigned int which is the
				file channel for the holiday file.

		holi_parm =	input parameter of type holidays_struct array
                		which holds the holiday schedule

		return value =  of unsigned long type gives completion status.

    Called by:	<[intcalc]

}*/
unsigned long	_INTCALCS n_p_pay(instr in_instr, 
			date_union in_date,
			date_union *prv_pay, 
			date_union *nxt_pay,
			unsigned int holi_chan
//			, holidays_struct holi_parm []
			,const set<string> &holiSet
			)

{
	#include "locals.h"

	char	adj_dir = 0;	/*{ adj_dir steers the direction of date adjustment.}*/
	unsigned char	day_hold = 0;	/*{ day_hold is used to hold a day of the month.}*/
	unsigned char	day_hold2 = 0;	/*{ day_hold is used to hold a day of the month.}*/
	unsigned char	week_hold = 0;	/*{ week_hold is used to hold the week of the month.}*/
	char	last_bus_in_month_reached = isfalse; /*{ last_bus_in_month_reached indicates the last business date in the month has been reached.}*/
	char	first_run = 0; /*{ first_run indicates the first pass in a loop.}*/
	int	rr_in_pay = 0;	/*{ rr_in_pay holds the number of rerates per payment.}*/
	int	rerate_counter = 0;	/*{ rr_counter is a counter for rerates.}*/
	int	cmpint = 0;		/*{ cmpint is a work field for string comparisons.}*/
	int	prv_base_cmp = 0;	/*{ prv_base_cmp holds the latest comparison result between the previous date and the base date.}*/
	int	nxt_base_cmp = 0;	/*{ nxt_base_cmp holds the latest comparison result between the next date and the base date.}*/
	int	nxt_mat_cmp = 0;	/*{ nxt_mat_cmp holds the latest comparison result between the next date and the maturity date.}*/
	int	prv_last_cmp = 0;	/*{ prv_base_cmp holds the latest comparison result between the previous date and the previous to last pay date.}*/
	int	loop_check_cmp = 0;	/*{ nxt_base_cmp holds the latest comparison result between the next date and the base date.}*/
	int	prv_nxt_cmp = 0;	/*{ prv_nxt_cmp holds the latest comparison result between the previous date and the next date.}*/

	int	months_fore = 0;/*{ months_fore is a work field for holding the amount of months to forecast.}*/
	int	days_fore   = 0;/*{ days_fore is a work field for holding the amount of days to forecast.}*/

	int	months_per = 0;/*{ months_per is the number of months in a period.}*/
	int	days_per   = 0;/*{ days_per is the number of days in a period.}*/

	int 	centuries_calc = 0;
	int 	years_calc = 0;
	int 	months_calc = 0;
	int 	days_calc = 0;

	long	period_hold = 0;	/*{ period_hold is a work field for period calculations.}*/

	date_union date_hold;	/*{ date_hold is a work field to hold the date.}*/
	date_union date_hold2;	/*{ date_hold2 is a work field to hold the date.}*/
	date_union first_date_adj;/*{ first_date_adj holds the first pay date adjusted to the regular pay day.}*/
	date_union pre_adj_date;/*{ pre_adj_date holds the date before it is adjusted.}*/
	date_union prv_rerate;/*{ prv_rerate is a hold field for rerate date counting.}*/
	date_union nxt_rerate;/*{ nxt_rerate is a hold field for rerate date counting.}*/

//	strcpy(module_name,"n_p_pay");

        /*{ Check whether a futures strip is being processed.}*/

	if (in_instr.pay_type == instr_futstr_pay_type)
	{

	  if ((in_instr.pay_freq.month_day < date_1sun_day) ||
		  (in_instr.pay_freq.month_day > date_9satur_day))
	  {

		 return_status = return_err_inv_futstr_day;
		 return return_status;

	  }

	  if ( in_instr.pay_freq.period != event_sched_month_period)
	  {

		 return_status = return_err_inv_futstr_period;
	    return return_status;

	  }

	  if ((12 % in_instr.pay_freq.freq) > 0)
	  {

	    return_status = return_err_invalid_pay_freq;
	    return return_status;

	  }

	  if (( in_instr.pay_freq.first_date.date.months < 1) ||
	      ( in_instr.pay_freq.first_date.date.months > 12) ||
	      ( in_instr.pay_freq.first_date.date.months >
			in_instr.pay_freq.freq))
	  {

	    return_status = return_err_invalid_month;
	    return return_status;

	  }

	  week_hold = ((in_instr.pay_freq.month_day - 100)/10);
	  day_hold = (in_instr.pay_freq.month_day - 100 - (10 * week_hold));

	  /*{ Starting exactly one year before the passed date, keep incrementing
	  the futures dates until those bracketing the passed date are
	  determined. }*/

	  return_status = forecast(in_date,
				  - 12,
				  0,
				  date_30_cal,
				  &date_hold);

	  if (return_status != return_success)
	  {

		return return_status;

	  }

	  /*{Set the month to the first futures month of the year.}*/

	  date_hold.date.months = in_instr.pay_freq.first_date.date.months;

	  /*{ Find the futures day in this month.}*/

	  return_status = findfut(in_instr, date_hold, &date_hold, day_hold, week_hold);

	  if (return_status != return_success)
	  {

		return return_status;

	  }


	  for (cmpint = 0; cmpint <= 0;)
	  {

		 return_status = forecast(date_hold,
				  in_instr.pay_freq.freq,
				  0,
				  date_30_cal,
				  &date_hold2);

		 if (return_status != return_success)
		 {

			return return_status;

		 }

		 /*{ Find the futures day in this month.}*/

		 return_status = findfut(in_instr, date_hold2, &date_hold2, day_hold, week_hold);

		 if (return_status != return_success)
		 {

			return return_status;

		 }

		 cmpint = datecmp(date_hold2.date_string, in_date.date_string);

		 if (cmpint <= 0)

		 {

			datecpy(date_hold.date_string,date_hold2.date_string);

		 }

	  }

	  datecpy(prv_pay->date_string,date_hold.date_string);

	  datecpy(nxt_pay->date_string,date_hold2.date_string);

	  return return_status;

	}

	/*{ If in_date is not within the life of the instrument, return an error.}*/

	cmpint = datecmp(in_date.date_string,in_instr.issue_date.date_string);

	if (cmpint < 0)
	{

		return_status = return_err_bad_base_date;

		return return_status;

	}

	cmpint = datecmp(in_date.date_string,in_instr.mat_date.date_string);

	if (cmpint > 0)
	{

		return_status = return_err_bad_base_date;

		return return_status;

	}

	if (cmpint == 0)
	{

		datecpy(prv_pay->date_string,in_instr.mat_date.date_string);
		datecpy(nxt_pay->date_string,in_instr.mat_date.date_string);

		return return_status;

	}

	/*{ Initialize previous and next dates to the first pay date and the maturity date.}*/

	datecpy(prv_pay->date_string,in_instr.pay_freq.first_date.date_string);
	datecpy(nxt_pay->date_string,in_instr.mat_date.date_string);
	datecpy(pre_adj_date.date_string,prv_pay->date_string);

	switch (in_instr.pay_sched)
	{
	  case instr_str_pay_sched: /*{ instr_str_pay_sched dates can be algorithmically determined.}*/
	  {

		 /*{ if the base date is in the first period, return the accrue date and the first pay date.}*/

		 cmpint = datecmp(in_date.date_string,
			in_instr.pay_freq.first_date.date_string);

		 if (cmpint < 0)
		 {

			datecpy(prv_pay->date_string,in_instr.accrue_date.date_string);
			datecpy(nxt_pay->date_string,in_instr.pay_freq.first_date.date_string);

		 }

		 else
		 {

			/*{ If the base date is in the last period, return this.}*/

			cmpint = datecmp(in_date.date_string,in_instr.pre_last_pay.date_string);

			if (cmpint >= 0)
			{

				datecpy(prv_pay->date_string,in_instr.pre_last_pay.date_string);

				return return_status;

			}

			/*{ Set standard adjustment periods.}*/

			switch (in_instr.pay_freq.period)
			{
			case event_sched_day_period:

				{ days_per = in_instr.pay_freq.freq;
					break;
				}

			case event_sched_month_period:

				{ months_per = in_instr.pay_freq.freq;
					break;
				}

			default :

				{ 
					return_status = return_err_invalid_period;
					return return_status;
				}
			}

			/*{ If date is beyond the first pay date, start with a rough approximation.}*/

			/*{ Only approximate non-marching.}*/

			if (in_instr.pay_freq.holiday_adj != event_sched_march_holiday_adj)
			{

			/*{If the first pay date is not on the regular pay day of the month,
			adjust to this day for forecasting and tenor calculations.}*/

				datecpy(first_date_adj.date_string,
					in_instr.pay_freq.first_date.date_string);

				if (in_instr.pay_freq.month_day == date_last_day_in_month)
				{

					day_hold = month_end(first_date_adj);

				}
				else
				{

					day_hold = in_instr.pay_freq.month_day;

				}

				if (first_date_adj.date.days != day_hold)
				{

					return_status = adj_date(&first_date_adj,
						adj_date_bus_to_non,
						in_instr.pay_freq.holiday_adj,
						adj_date_yes_we,
						adj_date_yes_hol,
//						in_instr.holiday_code,
						holi_chan
//						,holi_parm
						,holiSet
						);

					if (return_status != return_success)
					{

						return return_status;

					}

					if (in_instr.pay_freq.month_day == date_last_day_in_month)
					{

						day_hold = month_end(first_date_adj);

					}

					cmpint = datecmp(first_date_adj.date_string,
						in_instr.pay_freq.first_date.date_string);

					if (cmpint < 0)
					{

						adj_dir = -1;

					}
					else
					{

						if (cmpint > 0)
						{

							adj_dir = 1;

						}
						else
						{
							return_status = return_err_np_uncalc;
							return return_status;

						}

					}

					while (first_date_adj.date.days != day_hold)
					{

						return_status = forecast(first_date_adj,
							0,
							adj_dir,
							date_act_cal,
							&first_date_adj);

						if (return_status != return_success)
						{

							return return_status;

						}

						if (in_instr.pay_freq.month_day == date_last_day_in_month)
						{

							day_hold = month_end(first_date_adj);

						}

					}

				}


				if (in_instr.pay_freq.period == event_sched_day_period )
				{

				/*{ Use tenor to find the number of days between the first pay date and the base date.}*/

					return_status = tenor(first_date_adj,
						in_date,
						in_instr.cal_num,
						&period_hold);

					if (return_status != return_success)
					{

						return return_status;

					}

				}

				else
				{

				/*{ Express the number of days in terms of the period.}*/

					if (in_instr.pay_freq.period == event_sched_month_period )
					{

						centuries_calc = 100 *
							(in_date.date.centuries - first_date_adj.date.centuries);
						years_calc = centuries_calc + 12 *
							(in_date.date.years - first_date_adj.date.years);
						months_calc = years_calc +
							(in_date.date.months - first_date_adj.date.months);

						if (first_date_adj.date.days <= in_date.date.days)
						{

							 days_calc = 0;

						}
						else
						{

							 days_calc = -1;

						}

						period_hold = months_calc + days_calc;

					}

				}

				period_hold = (int)period_hold/(int)in_instr.pay_freq.freq;

				/*{ If final result is greater than zero, reduce it by one period to assure base date is not exceeded.}*/

				if (period_hold > 0)
				{

					period_hold--;

				}

				/*{ Add the number of periods calculated to the first pay date, using forecast.}*/

				if (period_hold != 0)
				{

					datecpy(date_hold.date_string,first_date_adj.date_string); /*{ Save previous date at the beginning of each loop.}*/

					switch (in_instr.pay_freq.period)
					{
						case event_sched_day_period:

						{ days_fore = period_hold * in_instr.pay_freq.freq;
							break;
						}

						case event_sched_month_period:

						{ months_fore = period_hold * in_instr.pay_freq.freq;
							break;
						}
						default :

						{ 
							return_status = return_err_invalid_period;
							return return_status;
						}
					}

					return_status = forecast(first_date_adj,
					  months_fore,
					  days_fore,
					  in_instr.cal_num,
					  prv_pay);

					if (return_status != return_success)
					{

					}

					/*{ Adjust date to last day of month, if this is necessary. }*/

					if (in_instr.pay_freq.month_day == date_last_day_in_month)
					{

						prv_pay->date.days = month_end(*prv_pay);

					}

					/*{ Adjust date for non business day.}*/

					/*{ Save the date before adjusting it.}*/

					datecpy(pre_adj_date.date_string,prv_pay->date_string); /*{ Save previous date at the beginning of each loop.}*/

					return_status = adj_date(prv_pay,
						adj_date_non_to_bus,
						in_instr.pay_freq.holiday_adj,
						adj_date_yes_we,
						adj_date_yes_hol,
//						in_instr.holiday_code,
						holi_chan
//						,holi_parm
						,holiSet
						);

					if (return_status != return_success)
					{

						return return_status;

					}

					/*{ If adjustment pushes date past base date, then go back a period.}*/

					cmpint = datecmp(prv_pay->date_string,in_date.date_string);

					if (cmpint >= 0)
					{

						cmpint = datecmp(pre_adj_date.date_string,
							in_date.date_string);

						if (cmpint < 0)
						{

							return_status = forecast(pre_adj_date,
								months_per*(-1),
								days_per*(-1),
								in_instr.cal_num,
								prv_pay);

							if (return_status != return_success)
							{

								return return_status;

							}

							/*{ Adjust date to last day of month, if this is necessary. }*/

							if (in_instr.pay_freq.month_day == date_last_day_in_month)
							{

								prv_pay->date.days = month_end(*prv_pay);

							}

							/*{ Adjust date for non business day.}*/

							/*{ Save the date before adjusting it.}*/

							datecpy(pre_adj_date.date_string,prv_pay->date_string); /*{ Save previous date at the beginning of each loop.}*/

							return_status = adj_date(prv_pay,
								adj_date_non_to_bus,
								in_instr.pay_freq.holiday_adj,
								adj_date_yes_we,
								adj_date_yes_hol,
//								in_instr.holiday_code,
								holi_chan
//								,holi_parm
								,holiSet
								);

							if (return_status != return_success)
							{

								return return_status;

							}
						}
					}
				}
				else
				{

					datecpy(pre_adj_date.date_string,first_date_adj.date_string);

				}
				/*{ If derived previous date greater than base date, flag error.}*/

				cmpint = datecmp(prv_pay->date_string,in_date.date_string);

				if (cmpint > 0)
				{

					return_status = return_err_np_uncalc;
					return return_status;
				}

				/*{ repeatedly adjust previous and next dates until they bracket the base date.}*/

				do
				{

					datecpy(date_hold.date_string,prv_pay->date_string); /*{ Save previous date at the beginning of each loop.}*/

					return_status = forecast(pre_adj_date,
					  months_per,
					  days_per,
					  in_instr.cal_num,
					  prv_pay);

					if (return_status != return_success)
					{

						return return_status;

					}

					/*{ Adjust date to last day of month, if this is necessary. }*/

					if (in_instr.pay_freq.month_day == date_last_day_in_month)
					{

						prv_pay->date.days = month_end(*prv_pay);

					}

					/*{ Adjust date for non business day.}*/

					/*{ Save the date before adjusting it.}*/

					datecpy(pre_adj_date.date_string,prv_pay->date_string); /*{ Save previous date at the beginning of each loop.}*/

					return_status = adj_date(prv_pay,
						adj_date_non_to_bus,
						in_instr.pay_freq.holiday_adj,
						adj_date_yes_we,
						adj_date_yes_hol,
//						in_instr.holiday_code,
						holi_chan
//						,holi_parm
						,holiSet
						);

					if (return_status != return_success)
					{

						return return_status;

					}

					prv_base_cmp = datecmp(prv_pay->date_string,in_date.date_string);
					loop_check_cmp = datecmp(prv_pay->date_string,date_hold.date_string);
					prv_nxt_cmp = datecmp(prv_pay->date_string,nxt_pay->date_string);

				} while ((prv_base_cmp <= 0) &&
					(loop_check_cmp != 0) &&
					(prv_nxt_cmp <= 0));

				/*{ If loop_check_cmp = 0, then a loop was detected.}*/

				if (loop_check_cmp == 0)
				{

					return_status = return_err_loop;
					return return_status;
				}

				/*{ If prv_nxt_cmp >= 0, then previous date has surpassed next.}+*/

				if (prv_nxt_cmp >=0)
				{

					return_status = return_err_np_uncalc;
					return return_status;
				}

				/*{ The base date has been surpassed, so set next date to the latest calculated date, and previous date to the date before that. }*/

				datecpy(nxt_pay->date_string,prv_pay->date_string);
				datecpy(prv_pay->date_string,date_hold.date_string);
			}

			else
			{ /*{ Start marching types from the beginning.}*/
/*
				cmpint = datecmp(in_instr.issue_date.date_string,
					in_instr.rerate_freq.first_date.date_string);
*/
				cmpint = 0;

				if ((in_instr.pay_type ==  instr_float_pay_type) &&
					(in_instr.pay_freq.period == in_instr.rerate_freq.period) &&
					((in_instr.pay_freq.freq % in_instr.rerate_freq.freq) == 0) &&
					(cmpint == 0))
				{


					/*{ Set standard adjustment periods.}*/

					switch (in_instr.rerate_freq.period)
					{
						case event_sched_day_period:

						{
							days_per = in_instr.rerate_freq.freq;
							break;
						}

						case event_sched_month_period:

						{
							months_per = in_instr.rerate_freq.freq;
							break;
						}

						default :

						{
							return_status = return_err_invalid_period;
							return return_status;
						}
					}

					/*{ If this is a floater with rerate and pay periods the same,
					pay date must match rerate date marching.}*/

					/*{ Calculate the number of rerates in each pay period.}*/

					rr_in_pay = in_instr.pay_freq.freq/in_instr.rerate_freq.freq;

					/*{ Initialize the rerate dates.}*/

					datecpy(nxt_rerate.date_string,
					in_instr.rerate_freq.first_date.date_string);
						datecpy(prv_rerate.date_string,nxt_rerate.date_string);

					do
					{

						/*{ Check whether the last business day of the month has been reached.}*/

						if (	last_bus_in_month_reached == isfalse)
						  {
							 datecpy (date_hold.date_string,prv_rerate.date_string);
							 date_hold.date.days = month_end(prv_rerate);

							 return_status = adj_date(&date_hold,
								 adj_date_non_to_bus,
								in_instr.rerate_freq.holiday_adj,
								adj_date_yes_we,
								adj_date_yes_hol,
//								in_instr.holiday_code,
								holi_chan
//								,holi_parm
								,holiSet
								);

							 if (return_status != return_success)
							 {

							  return return_status;

							 }

							 if (date_hold.date.days == prv_rerate.date.days)
							 {

							  last_bus_in_month_reached = istrue;

							 }
						}
						datecpy(prv_pay->date_string,nxt_rerate.date_string);

						for ( first_run = istrue;
							(((rerate_counter % rr_in_pay) != 0) || first_run);
							rerate_counter++)
						{


						/*{ Check whether the last business day of the month has been reached.}*/

						  if (	last_bus_in_month_reached == isfalse)
						  {
							 datecpy (date_hold.date_string,prv_rerate.date_string);
							 date_hold.date.days = month_end(prv_rerate);

							 return_status = adj_date(&date_hold,
								 adj_date_non_to_bus,
								in_instr.rerate_freq.holiday_adj,
								adj_date_yes_we,
								adj_date_yes_hol,
//								in_instr.holiday_code,
								holi_chan
//								,holi_parm
								,holiSet
								);

							 if (return_status != return_success)
							 {

							  return return_status;

							 }

							 if (date_hold.date.days == prv_rerate.date.days)
							 {

							  last_bus_in_month_reached = istrue;

							 }
						  }

							first_run = isfalse;
							datecpy(prv_rerate.date_string,nxt_rerate.date_string);
							return_status = forecast(prv_rerate,
								months_per,
								days_per,
								in_instr.cal_num,
								&nxt_rerate);

							if (return_status != return_success)
							{

								return return_status;

							}

							/*{ Make last business day of month, if this has already happened.}*/

							if (last_bus_in_month_reached)
							{

								nxt_rerate.date.days = month_end(nxt_rerate);

								return_status = adj_date(&nxt_rerate,
									adj_date_non_to_bus,
									in_instr.rerate_freq.holiday_adj,
									adj_date_yes_we,
									adj_date_yes_hol
//									,in_instr.holiday_code
									,holi_chan
//									,holi_parm
									,holiSet
									);

								if (return_status != return_success)
								{

									return return_status;

								}

							}

							/*{ Otherwise adjust date for holiday.}*/

							else
							{

								return_status = adj_date(&nxt_rerate,
									adj_date_non_to_bus,
									in_instr.rerate_freq.holiday_adj,
									adj_date_yes_we,
									adj_date_yes_hol
//									,in_instr.holiday_code
									,holi_chan
//									holi_parm
									,holiSet
									);

								if (return_status != return_success)
								{

									return return_status;

								}
							}
						}


						/*{ If the first calculated date does
						not match the first pay date, flag an error.}*/
/*
						if (rerate_counter == rr_in_pay)
						{

							cmpint = datecmp(nxt_rerate.date_string,
								in_instr.pay_freq.first_date.date_string);

							if (cmpint != 0)
							{

								//errproc(return_err_rr_pay_mis,module_name,"","","");
								return_status = return_err_rr_pay_mis;
								return return_status;

							}

						}
*/
						nxt_base_cmp = datecmp(nxt_rerate.date_string,
							in_date.date_string);
						nxt_mat_cmp = datecmp(nxt_rerate.date_string,
							in_instr.mat_date.date_string);

					} while ((nxt_base_cmp <= 0) &&
						(nxt_mat_cmp <= 0));

					datecpy(nxt_pay->date_string,nxt_rerate.date_string);

				}

				else

				{

					datecpy(nxt_pay->date_string,prv_pay->date_string);

					do
					{
						datecpy(prv_pay->date_string,nxt_pay->date_string);

						/*{ Check whether the last business day of the month has been reached.}*/

						datecpy (date_hold.date_string,prv_pay->date_string);
						date_hold.date.days = month_end(*prv_pay);

						return_status = adj_date(&date_hold,
							adj_date_non_to_bus,
							in_instr.pay_freq.holiday_adj,
							adj_date_yes_we,
							adj_date_yes_hol
//							,in_instr.holiday_code
							,holi_chan
//							holi_parm
							,holiSet
							);

						if (return_status != return_success)
						{

							return return_status;

						}

						if (date_hold.date.days == prv_pay->date.days)
						{

							last_bus_in_month_reached = istrue;

						}

						return_status = forecast(*prv_pay,
							months_per,
							days_per,
							in_instr.cal_num,
							nxt_pay);

						if (return_status != return_success)
						{

							return return_status;

						}

						/*{ Make last business day of month, if this has already happened.}*/

						if (last_bus_in_month_reached)
						{

							nxt_pay->date.days = month_end(*nxt_pay);

							return_status = adj_date(nxt_pay,
								adj_date_non_to_bus,
								in_instr.pay_freq.holiday_adj,
								adj_date_yes_we,
								adj_date_yes_hol
//								,in_instr.holiday_code
								,holi_chan
//								,holi_parm
								,holiSet
								);

							if (return_status != return_success)
							{

								return return_status;

							}

						}

						/*{ Otherwise adjust date for holiday.}*/

						else
						{

							return_status = adj_date(nxt_pay,
								adj_date_non_to_bus,
								in_instr.pay_freq.holiday_adj,
								adj_date_yes_we,
								adj_date_yes_hol,
//								in_instr.holiday_code,
								holi_chan
//								,holi_parm
								,holiSet
								);

							if (return_status != return_success)
							{

								return return_status;

							}
						}

						nxt_base_cmp = datecmp(nxt_pay->date_string,in_date.date_string);
						nxt_mat_cmp = datecmp(nxt_pay->date_string,in_instr.mat_date.date_string);

					} while ((nxt_base_cmp <= 0) &&
						(nxt_mat_cmp <= 0));
				}
			}
		  }

		  break;
	  }
	  /*{ instr_free_pay_sched dates must be read.}*/
	  case instr_free_pay_sched:
		 break;
	  default :

	  {
		 return_status = return_err_invalid_pay_sched;
		 return return_status;
	  }
	}

n_p_pay_end:

	return return_status;
}

unsigned long	_INTCALCS findfut(instr in_instr
			, date_union in_date
			,date_union *out_date
			, unsigned char day_hold
			,unsigned char week_hold
			)

{
	#include "locals.h"

	char	adj_dir = 0;	/*{ adj_dir steers the direction of date adjustment.}*/
	char	day_hold2 = 0;	/*{ day_hold is used to hold a day of the month.}*/

	date_union date_hold;	/*{ date_hold is a work field to hold the date.}*/
//	date_union date_hold2;	/*{ date_hold2 is a work field to hold the date.}*/

//	strcpy(module_name,"futfind");

	  /*{ Find what weekday the first day of the month falls on.}*/

	  in_date.date.days = 1;

	  return_status = findday(in_date, &day_hold2);

	  /*{ Adjust the day to the first instance of the regular futures
	  day.}*/

	  adj_dir = day_hold - day_hold2;

	  if (adj_dir < 0)
	  {

		 adj_dir = (adj_dir + 7);

	  }

	  return_status = forecast(in_date,
				  0,
				  adj_dir,
				  date_act_cal,
				  &date_hold);

	  if (return_status != return_success)
	  {

		return return_status;

	  }

	  if (week_hold != 9)
	  {

		 /*{ If the futures day is not the last of the month,
		 determine the date at once.}*/

		 return_status = forecast(date_hold,
				  0,
				  7 * (week_hold - 1),
				  date_act_cal,
				  out_date);

		 if (return_status != return_success)
		 {

			return return_status;

		 }


	  }
	  else
	  {

		 /*{ If the futures day is the last of the month, first add 28
		 days.}*/

		 return_status = forecast(date_hold,
				  0,
				  28,
				  date_act_cal,
				  out_date);

		 if (return_status != return_success)
		 {

			return return_status;

		 }

				/*{ If the next month has been reached, subtract 7 days.}*/

		 return_status = forecast(*out_date,
				  0,
				  -7,
				  date_act_cal,
				  out_date);

		 if (return_status != return_success)
		 {

			return return_status;

		 }

	  }

func_end:

	return return_status;


}

/*{nom_adj accepts an instrument record and a base date and returns the
current nominal adjustment and the boundary dates for when that adjustment is in effect.

	Usage:  unsigned long	nom_adj(instr in_instr, date_union base_date,
					date_union *nom_begin, date_union *nom_end,
					long double *curr_nom)

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which the adjustment is to be
				determined.

		base_date =	Input parameter of date_union type which
				contains the date for which the current adjustment
				and boundaries are to be determined.

		nom_begin =	output parameter of pointer to date_union
				type which contains the date when the current adjustment
				takes effect.

		nom_end =	output parameter of pointer to date_union
				type which contains the date when the current adjustment
				is no longer in effect.

		curr_nom =     	Output parameter of long double type which
				contains the current adjustment.

		return value =  of unsigned long type gives completion status.

    Called by:	<[int_calc,py_calc]

}*/

unsigned long   _INTCALCS nom_adj (instr *in_instr,
			  date_union base_date,
			  date_union *nom_begin,
			  date_union *nom_end,
			  long double *curr_nom)

{
	#include "locals.h"
	long double temp_curr_nom = 0;
	signed int cmp_int = -1;
	char element_count = 0;
			/*{ Start with the assumption of no adjustment.}*/

			*curr_nom = 1;

			datecpy(nom_begin->date_string,
			in_instr->issue_date.date_string);
			datecpy(nom_end->date_string,
			in_instr->mat_date.date_string);


			/*{ Check for a partial payment schedule.}*/

			if (in_instr->part_pays != 0)

			{

		/*{ Cycle through all the partial payment schedules before the base date.}*/

	       for 	(element_count = 0;
				(cmp_int<= 0) && (element_count <= in_instr->part_pays);
				element_count++)
			 {


				cmp_int = datecmp(in_instr->part_pays_sched[element_count].pay_date.date_string,
					base_date.date_string);

				if (cmp_int <= 0)
				{

					temp_curr_nom = temp_curr_nom +
						in_instr->part_pays_sched[element_count].payment;

					datecpy(nom_begin->date_string,
						in_instr->part_pays_sched[element_count].pay_date.date_string);
				}
				else
				{

					datecpy(nom_end->date_string,
						in_instr->part_pays_sched[element_count].pay_date.date_string);
				}

			 }

			 *curr_nom = temp_curr_nom/in_instr->part_pay_price_base;

			}

//nom_adj_end:

	return return_status;
}


/*{redemp_adj accepts an instrument record and a base date and returns the
current redemption adjustment and the boundary dates for when that adjustment is in effect.

	Usage:  unsigned long	redemp_adj(instr in_instr, date_union base_date,
					long double *curr_redemp,
					unsigned int holi_chan,
			  		holidays_struct holi_parm [],
			  		date_union *average_maturity)
)

	where:  in_instr =	Input parameter of instr type which contains
				the instrument for which the adjustment is to be
				determined.

		base_date =	Input parameter of date_union type which
				contains the date for which the current adjustment
				and boundaries are to be determined.

		curr_redemp =  	Output parameter of long double type which
				contains the current adjustment.

		holi_chan =	Input parameter of type unsigned int which
				indicates the channel number for accessing
				the holiday file.

		holi_parm =	Input parameter of type holiday_struct which
				contains an array of holidays.

		average_maturity =

				Output parameter of type date which contains
                                the average maturity from the passed date.

		return value =  of unsigned long type gives completion status.

    Called by:	<[int_calc]

}*/


unsigned long   _INTCALCS redemp_adj (instr in_instr,
			  date_union base_date,
			  long double *curr_redemp,
			  unsigned int holi_chan,
//			  holidays_struct holi_parm [],
				const set<string> &holiSet,
			  date_union *average_maturity)

{
	#include "locals.h"
	long days_hold = 0;
	long double temp_curr_redemp = 0;
	long double redemps_due = 0;
	long double weighted_days = 0;
	signed int cmp_int = -1;
	signed int cmp_last = 1;
	char element_count = 0;
	date_union this_date;
	date_union prev_coup;
	date_union next_coup;

			/*{ Check for a redemption schedule.}*/

			if (in_instr.redemps != 0)

			{

		/*{ Cycle through all the redemption schedules before the base date.}*/

			 for 	(element_count = 0;
				(cmp_int< 0) && (element_count < in_instr.redemps);
				element_count++)
			 {

				datecpy(this_date.date_string,
					in_instr.redemp_sched[element_count].redemps_date.date_string);

				cmp_last = 1;

				/*{ Cover all the payment dates within the specified range. }*/

				while ((cmp_int < 0) && (cmp_last > 0))
				{

					cmp_int = datecmp(this_date.date_string,
					base_date.date_string);

					if (cmp_int < 0)

					{

						temp_curr_redemp = temp_curr_redemp +
						in_instr.redemp_sched[element_count].redemps_factor;

						return_status = n_p_pay(in_instr
							, this_date
							, &prev_coup,
							&next_coup
							, holi_chan
//							, holi_parm
							,holiSet
							);

						if (return_status)
						{
							return return_status;
						}

						cmp_last = datecmp(
							in_instr.redemp_sched[element_count].end_date.date_string,
							this_date.date_string);

						datecpy(this_date.date_string,
							next_coup.date_string);

					}

				}

			 }

			 *curr_redemp = in_instr.redemp_price - temp_curr_redemp;

					/*{ Now determine the average maturity. }*/

			 if (cmp_last == 0)
			 {

					  element_count++;

			 }

			 for(;(element_count < in_instr.redemps);element_count++)
			 {

				if (cmp_last == 0)
				{

					datecpy(this_date.date_string,
						in_instr.redemp_sched[element_count].redemps_date.date_string);

					cmp_last = 1;

				}

				while (cmp_last > 0)
				{

					redemps_due = redemps_due +
						in_instr.redemp_sched[element_count].redemps_factor;

					return_status = tenor (base_date,
						this_date,
						in_instr.cal_den,
						&days_hold);

					if (return_status != return_success)
					{


						return return_status;
					}

					weighted_days = weighted_days +
						(days_hold *
							in_instr.redemp_sched[element_count].redemps_factor);

					return_status = n_p_pay(in_instr
						, this_date
						, &prev_coup
						,&next_coup
						, holi_chan
//						, holi_parm
						,holiSet
						);

					if (return_status)
					{
						return return_status;
					}

					cmp_last =
						datecmp(in_instr.redemp_sched[element_count].end_date.date_string,
											this_date.date_string);

					datecpy(this_date.date_string,
						next_coup.date_string);

				}

			 }

			 days_hold = (long) (weighted_days / redemps_due);

			 return_status = forecast(base_date,
					  0,
					  days_hold,
					  in_instr.cal_den,
					  average_maturity);

			 if (return_status != return_success)
			 {

				return return_status;

			 }

			}

			else

			{

				*curr_redemp = 1;

				datecpy(average_maturity->date_string,
					in_instr.mat_date.date_string);

	      }

func_end:

	return return_status;
}

/*{schedgen returns an array of dates when passed a schedule and start and end
dates for that schedule.

	Usage:  unsigned long schedgen(event_sched event_parm, date_union sched_dates[],
					date_union start_date, date_union end_date,
					unsigned int holi_chan, holidays_struct holi_parm,
					char pay_type)


	where:

		event_parm   =	Input parameter of event_sched type which contains
				the schedule for calculating the dates.

		sched_dates  =	Output parameter of insevent_struct type which contains
                		the dates calculated from the schedule.

		start_date   =	Start date for calculation period.

                end_date     =	End date for calculation period.

		holi_chan =	Input parameter of unsigned int type which is
				the file channel for the holiday file. Not
				currently used

		holi_parm =	Input parameter of type holidays_struct array
				which holds the holiday schedule. For an
				explanation of how to set up holiday dates or
				rules see the holiday_struct description. To
				indicate that no holidays are used, the first
				element of the array should be set as:

				holi_parm[0].holi_date.first_date.date.years = io_no_use

		pay_type  =	Input parameter of type char which indicates
				which pay type is to be used. Must be a
				valid symbol of the series
				instr_xxx_pay_type.

		return value =  of unsigned long type gives completion status.

}*/

unsigned long _INTCALCS schedgen(event_sched event_parm
		, insevent_struct sched_dates []
		,date_union start_date
		, date_union end_date
		,unsigned int holi_chan
//		, holidays_struct holi_parm []
			,const set<string> &holiSet
		,char pay_type
		)

{


	#include "locals.h"

	int date_comp = 0;
	int start_comp = 0;
	int end_comp = 0;
		  int date_count = 0;

	instr in_instr_loc;

	date_union calc_date;
	date_union prev_date;
	date_union next_date;

//	strcpy(module_name,"schedgen");

	/*{ Validate the event schedule.}*/

	return_status = eventchk(event_parm);

	if (return_status == return_err_date_bad)
	{

	  return_status = return_err_event_date_bad;
			 return return_status;

	}

	if (return_status)
	{

          return return_status;

	}

        /*{ Make sure the start date is not before the first scheduled date.}*/

	date_comp = datecmp(start_date.date_string,
		event_parm.first_date.date_string);

        if (date_comp < 0)
	{

	  return_status = return_err_start_less_first;
			 return return_status;

	}

        /*{ Check the date array size.}*/

	if (sched_dates[0].event_date.date.centuries < 1)
	{

	  return_status = return_inv_array_size;
			 return return_status;

	}

	/*{ Create Instrument record for calls to next/previous coupon generator.}*/

	in_instr_loc.instr_class = instr_euro_class;

	return_status =	classdef(&in_instr_loc);

	if (return_status != return_success)
	{


		return return_status;

	}

	in_instr_loc.pay_freq = event_parm;
	in_instr_loc.rerate_freq = event_parm;
	in_instr_loc.pay_type = pay_type;
//	strcpy(in_instr_loc.holiday_code,holi_parm[0].holi_code);
	if( pay_type == instr_float_pay_type)
	{

	  datecpy(in_instr_loc.issue_date.date_string,
	  event_parm.first_date.date_string);



	}
	else
	{

	  return_status = forecast(event_parm.first_date,
				  -12,
				  0,
				  date_act_cal,
				  &in_instr_loc.issue_date);

	 if (return_status != return_success)
	 {


		 return return_status;

	 }
	}
	return_status = forecast(end_date,
				  12,
				  0,
				  date_act_cal,
				  &in_instr_loc.pre_last_pay);

	if (return_status != return_success)
	{


	  return return_status;

	}

	return_status = forecast(end_date,
				  24,
				  0,
				  date_act_cal,
				  &in_instr_loc.mat_date);

	if (return_status != return_success)
	{


	  return return_status;

	}

	datecpy(calc_date.date_string,start_date.date_string);

	end_comp = datecmp(calc_date.date_string,end_date.date_string);

	for ( date_count = 1;
		((date_count <= sched_dates[0].event_date.date.centuries) &&
		 (end_comp < 0));
		 date_count++)

	{

	  return_status = n_p_pay(in_instr_loc
		  , calc_date
		  , &prev_date
		  ,&next_date
		  , holi_chan
//		  , holi_parm
		,holiSet
		  );

	  if (return_status != return_success)
	  {


		 return return_status;
	  }

	  datecpy(sched_dates[date_count].event_date.date_string,calc_date.date_string);

	  datecpy(sched_dates[date_count].eff_start_date.date_string,calc_date.date_string);

	  datecpy(sched_dates[date_count].eff_end_date.date_string,next_date.date_string);

	  datecpy(calc_date.date_string,next_date.date_string);

	  end_comp = datecmp(calc_date.date_string,end_date.date_string);

	}

	sched_dates[0].event_date.date.centuries = date_count - 1;

func_end:

	return return_status;
}

unsigned long _INTCALCS eventchk (event_sched event_parm)

{
	#include "locals.h"

		  date_union dummy_date1;

		  /*{Make sure the date is valid.}*/

	if (event_parm.first_date.date.years <= 0)
	{

	  return_status = return_err_date_bad;
			 return return_status;

	}

	if ((event_parm.first_date.date.months <= 0) ||
		 (event_parm.first_date.date.months > 12))
	{

	  return_status = return_err_date_bad;
			 return return_status;

	}

	if (event_parm.first_date.date.days <= 0)
	{

	  return_status = return_err_date_bad;
	  return return_status;

	}

	datecpy(&dummy_date1.date_string,&event_parm.first_date.date_string);

	return_status = adj_last(&dummy_date1);

	if (return_status)
	{

	  return_status = return_err_date_bad;
	  return return_status;

	}

	if (dummy_date1.date.days < event_parm.first_date.date.days)
	{

	  return_status = return_err_date_bad;
	  return return_status;

	}

	/*{ Make sure the period is valid}*/

	if ((event_parm.period != event_sched_month_period) &&
		(event_parm.period != event_sched_day_period))
	{

	  return_status = return_err_invalid_period;
	  return return_status;

	}

	/*{ Make sure the frequency is valid}*/

	/*{ Make sure the holiday adjustment is valid}*/

	/*{ Make sure the month day is valid}*/



/*
	event_sched.period;
	event_sched.freq;
	event_sched.holiday_adj;
	event_sched.month_day;
*/

func_end:

	return return_status;

}



