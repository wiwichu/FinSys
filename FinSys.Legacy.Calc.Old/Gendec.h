
#ifndef __gendec_H
#define __gendec_H

#include "shrtdecs.h"

/*{ Instrument functions follow.}*/

#ifndef __datedec_H
#include "datedec.h"
#endif
#ifndef __pydecs_H
#include "pydecs.h"
#endif
#ifndef __intdecs_H
#include "intdecs.h"
#endif
#ifndef __insclass_H
#include "insclass.h"
#endif

/*{ Define structures and declarations for an Access Dll. }*/

const char date_default = 0;
const char int_default = 99;

typedef struct instr_a{

			int		instr_class;
			/*{ Access Basic - Integer}*/

			/*{ instr_class holds the class to which this
			instrument belongs. It must be one of the following:

			instr_bund_class	= 0

				{instr_bund_class is German Bunds.}

			instr_goj_class		= 1

				{instr_goj_class is Government of Japan.}

			instr_euro_class	= 2

				{instr_euro_class is Eurobonds.}

			instr_gilt_class	= 3

				{instr_gilt_class is UK Gilts.}

			instr_mbs_class		= 4

				{instr_mbs_class is Mortgage Backed Instruments.}

			instr_ukcd_class	= 5

				{instr_ukcd_class is UK CD's.}

			instr_ukdsc_class	= 6

				{instr_ukdsc_class is UK Discounts.}

			instr_uscd_class	= 7

				{instr_uscd_class is US CD's.}

			instr_usdsc_class	= 8

				{instr_usdsc_class is US Discounts.}

			instr_ustbo_class	= 9

				{instr_ustbo_class is US Treasury Bonds.}

			instr_cust_class	= 99

				{instr_cust_class is for customizing instruments.}

			}*/

			double 	mat_date;
			/*{ Access Basic - Double}*/


			/*{ mat_date is the date the instrument
			matures. }*/

			double           interest_rate;
			/*{ Access Basic - Double}*/

			/*{ interest_rate indicates the interest rate of the
			instrument. }*/

			int		day_count;
			/*{ Access Basic - Integer}*/


			/*{ day_count is a code determiining what
			values are contained in cal_num and cal_den.
			valid choices are indicated by the
			date_xxx_day_count symbols:

			date_30e_360_day_count	= 0; 30e/360
			date_30_360_day_count	= 1; 30/360
			date_act_360_day_count	= 2; act/360
			date_act_365_day_count	= 3; act/365
			date_act_365cd_day_count = 4; act/365(cd)
			date_act_act_day_count	= 5; act/act

			}*/

			int 		freq;
			/*{ Access Basic - Integer}*/


			/*{ freq indicates the frequency of payments.
			It must be one of the following:

			1 = monthly,
			3 = quarterly,
			6 = semi-annually,
			12 = annually,
			99 = at maturity}*/

			double 	issue_date;
			/*{ Access Basic - Double}*/

			/*{ issue_date is the date the instrument was
			issued. 

                        To indicate that the default should be used = 0.

                        }*/

			double 	accrue_date;
			/*{ Access Basic - Double}*/

			/*{ accrue_date is the date the instrument starts
			accruing. This is normally the same as the issue
			date but would be one day less for JGB's.

                        To indicate that the default should be used = 0.

                        }*/

			double 	first_pay;
			/*{ Access Basic - Double}*/


			/*{ first_pay is the first pay date after issue date. 

                        To indicate that the default should be used = 0.

                        }*/

			double	pre_last_pay;
			/*{ Access Basic - Double}*/

			/*{ pre_last_pay is the last pay date before maturity. 

                        To indicate that the default should be used = 0.

                        }*/

			int 		month_day;
			/*{ Access Basic - Integer}*/


			/*{month_day is the day of the month on which the regular payment
			occurs. It must be 1-31 or 99 for last day of the month.}*/

			int		lag;
			/*{ Access Basic - Integer}*/

			/*{ lag indicates the delay in days from the time a
			payment is due until when it is received. }*/

			double 	service_fee;
			/*{ Access Basic - Double}*/

			/* service_fee is the amount of fee taken in
			servicing an MBS.
                        */

			int		ex_coup_days;
			/*{ Access Basic - Integer}*/

			/*{ ex_coup_days is the number of days before a payment
			that the instrument is traded ex-coup, or with negative
			interest. 

                        To indicate that the default should be used = 999.

                        }*/

			int		neg_first;
			/*{ Access Basic - Integer}*/

			/*{ neg_first is an indicator of whether the first coupon is traded with
			negative interest. See constants instr_xxx_neg_first
			for acceptable values.}*/

			double           redemp_price;
			/*{ Access Basic - Double}*/

			/*{ redemp_price is the price at which the instrument is redeemed. }*/

		      }
	       instr_a;	

typedef struct pyparm_a{

			double value_date;
			/*{ Access Basic - Double}*/

			/*{ value_date is the date as of when the
				calculation takes place.}*/	

			int	yield_meth;
			/*{ Access Basic - Integer}*/

			/*{ yield_meth indicates what yield method should
			   be used. One of the following should be used:

			py_aibd_yield_meth = 0
				py_aibd_yield_meth means the
				AIBD method.

			py_mmdisc_yield_meth = 1
				py_mmdisc_yield_meth means the
				Money Market Discount method.

			py_mm_yield_meth = 2
				py_mm_yield_meth means the
				Money Market Yield method.

			py_ytm_simp_yield_meth = 3
				py_ytm_simp_yield_meth means yield to
				maturity with simple fractional discounting.

			py_ytm_comp_yield_meth = 4
				py_ytm_comp_yield_meth means yield to
				maturity with compound fractional discounting.

			py_simp_yield_meth = 5
				py_simp_yield_meth means the simple
				(Japanese) method.

			py_curr_yield_meth = 6
				py_curr_yield_meth means the current yield
				method.

			py_gm_yield_meth = 7
				py_gm_yield_meth means the Greenwell Montagu
				method.

			py_muni_yield_meth = 8
				py_muni_yield_meth means the Municipal
				method.

			py_corp_yield_meth = 9
				py_corp_yield_meth means the Corporate Bond
				method.

			py_ustr_yield_meth = 10
				py_ustr_yield_meth means the US Treasury
				Bond method.

			py_moos_yield_meth = 11
				py_moos_yield_meth means the Moosmueller
				method.

			py_bf_yield_meth = 12
				py_bf_yield_meth means the Braess/Fangmeyer
				method.

			py_cpr_yield_meth = 13
				py_cpr_yield_meth means Constant Prepayment
				Rate method (for MBS's).

			py_ty_yield_meth = 14
				py_ty_yield_meth means True Yield.

                        To indicate that the default should be used = 999.

			}*/
			int	calc_what;
			/*{ Access Basic - Integer}*/

			/*{ calc_what indicates what should be calculated.
			Allowable values are:

			py_yield_from_price_calc_what = 0
				py_yield_from_price_calc_what means
				calculate the yield from the price.

			py_price_from_yield_calc_what = 1
				py_price_from_yield_calc_what means calculate
				the price from the yield.
			}*/

			double	price_yield;
			/*{ Access Basic - double}*/

			/*{ price_yield is the price or yield to be used
			depending on calc_what}*/

			int	calc_acc;
			/*{ Access Basic - Integer}*/

			/*{ calc_acc indicates whether the accrued interest should be calculated.
			Allowable values are:

			py_yes_calc_acc = 0
				py_yes_calc_acc means accrued interest
				should be calculated.

			py_no_calc_acc = 1
				py_no_calc_acc means accrued interest is
				passed.
			}*/
                        double	accr_int;
			/*{ Access Basic - double}*/

			/*{ accr_int contains the interest passed if
			calc_acc = py_no_calc_acc.
			}*/

			double 	cpr_rate;
			/*{ Access Basic - double}*/

			/*{ cpr_rate is the constant prepayment rate.}*/

		      }
	       pyparm_a;	

typedef struct result_a{

			double	price_yield;
			/*{ Access Basic - double}*/

			/*{ price_yield is the price or yield result.}*/

			double	duration;
			/*{ Access Basic - double}*/

			/*{ duration is the calculated McAuley Duration.}*/

			double	mod_duration;
			/*{ Access Basic - double}*/

			/*{ mod_duration is the calculated Modified Duration.}*/

			double	convexity;
			/*{ Access Basic - double}*/

			/*{ convexity is the calculated Convexity.}*/

			/*{ Access Basic - double}*/

			/*{ pvbp_plus is the price change for an .01 yield
			increase.}*/

			/*{ Access Basic - double}*/

			/*{ pvbp_minus is the price change for an .01 yield
			decrease.}*/

			double	pvbp_ave;
			/*{ Access Basic - double}*/

			/*{ pvbp_ave is the average of pvbp_plus and
			pvbp_minus.}*/

			double	accr_int;
			/*{ Access Basic - double}*/

			/*{ accr_int is the accrued interest calculated.}*/

			int	int_days;
			/*{ Access Basic - integer}*/

			/*{ int_days is the accrued interest days calculated.}*/
		      }
	       result_a;	

typedef struct holiday_a{ char * holiday_rules;
			/*{holiday_rules is not yet supported and should be
			passed from access simply as a string.}*/
			}
	       holiday_a;	


const unsigned long pyaccess_success_return = 0;
/*{pyaccess_success_return means successful completion.}*/

const unsigned long pyaccess_general_return = 1;
/*{pyaccess_success_return means general error.}*/

const unsigned long pyaccess_licexp_return = 2;
/*{pyaccess_licexp_return means license has expired.}*/

const unsigned long pyaccess_badint_return = 3;
/*{pyaccess_badint_return means bad interest.}*/

const unsigned long  pyaccess_nodaycount_return = 4;
/*{pyaccess_nodaycount_return means bad day_count.}*/

const unsigned long  pyaccess_badfreq_return = 5;
/*{pyaccess_badfreq_return means bad frequency.}*/

const unsigned long pyaccess_valaftmat_return = 6;
/*{pyaccess_valaftmat_return means value date after maturity date.}*/

const unsigned long pyaccess_valbefiss_return = 7;
/*{pyaccess_valbefiss_return means value date before issue date.}*/

const unsigned long pyaccess_firstbefiss_return = 8;
/*{pyaccess_firstbefiss_return means first pay date before issue date.}*/

const unsigned long pyaccess_firstaftmat_return = 9;
/*{pyaccess_firstaftmat_return means first pay date after maturity date.}*/

const unsigned long pyaccess_badfirstday_return = 10;
/*{pyaccess_badfirstday_return means first pay day does not match rule.}*/

const unsigned long pyaccess_firstnotmat_return = 11;
/*{pyaccess_firstnotmat_return means first pay date should be maturity date
for instruments paying at maturity.}*/

const unsigned long pyaccess_prebefiss_return = 12;
/*{pyaccess_prebefiss_return means the pre last pay date is before issue
date.}*/

const unsigned long pyaccess_preaftmat_return = 13;
/*{pyaccess_preaftmat_return means the pre last pay date is not before
maturity date.}*/

const unsigned long pyaccess_prenotiss_return = 14;
/*{pyaccess_prenotiss_return means pre last pay date should be issue date
for instruments paying at maturity.}*/

const unsigned long pyaccess_badpreday_return = 15;
/*{pyaccess_badpreday_return means pre last pay day does not match rule.}*/

const unsigned long pyaccess_badpayday_return = 16;
/*{pyaccess_badpayday_return means the pay day can lead to impossible dates.}*/

const unsigned long pyaccess_firstprenomatch_return = 17;
/*{pyaccess_firstprenomatch_return means the first and pre last pay dates
don't match.}*/

const unsigned long pyaccess_minuslag_return = 18;
/*{pyaccess_minuslag_return means a minus lag was passed.}*/

const unsigned long pyaccess_minusservice_return = 19;
/*{pyaccess_minusservice_return means a minus service fee was passed.}*/

const unsigned long pyaccess_minusexcoup_return = 20;
/*{pyaccess_minusexcoup_return means a minus ex-coup days was passed.}*/

const unsigned long pyaccess_badcalcwhat_return = 21;
/*{pyaccess_badcalcwhat_return means an invalid value was passed for the
calculation direction.}*/

const unsigned long pyaccess_zeroprice_return = 22;
/*{pyaccess_zeroprice_return means a zero price was passed for calculating
yield.}*/

const unsigned long pyaccess_badcalcacc_return = 23;
/*{pyaccess_badcalcacc_return means a calc accrued value was passed.}*/

const unsigned long pyaccess_badcprrate_return = 24;
/*{pyaccess_badcprrate_return means the cpr rate is less than 0 or
not less than 100.}*/

const unsigned long pyaccess_insmem_return = 25;
/*{pyaccess_insmem_return means insufficient memory.}*/

unsigned long EXPORT FAR pyaccess(instr_a FAR *,
					pyparm_a FAR *,
					result_a FAR *,
					holiday_a FAR *);
/*
extern unsigned long EXPORT FAR pyaccess(instr_a FAR *,
					pyparm_a FAR *,
					result_a FAR *,
					holiday_a FAR *);
*/
/*{

pyaccess is a filter for the py_calc and intcalc routines which works with
Access compatible parameters. The parameters are described above, indicating
the Access Basic data types to be used. Usage is described below:

In the simp0lest case, instr_a.instr_class can be set to one of the indicated
values. This permits the system to determine defaults for most of the
fields.

If instr_a.instr_class is set to one of the provided values, the system can
create enough defaults so that only instr_a.mat_date and
instr_a.interest_rate must be provided on the instr_a record. In addition the
following fields are required on the pyparm_a record: value_date, yield_meth,
calc_what, and price_yield.

The date fields on the parameters are expected in Access Date format
(December 30th, 1899 = 0, January 1, 1900 = 2, Negative numbers = dates
before December 30th, 1899).

If an invalid amount is passed in a field (0 for dates), it is assumed that
that field should be determined by the system.

If the instr_class is not a valid choice or is instr_cust_class, then it
is assumed that all the fields are passed. 

The return value of the function indicates the completion status. The
various possibilities are listed above under the pyaccess_xxx_return
symbols.

}*/
/*
unsigned long py_filter( instr,  date_union,
			 long double *,  long double *,
			 long double *,  long double *,
			  long double *,  long double *,
			 long double *,  py_parms,  char,
			  unsigned int,  unsigned int,
			 long double *,  long double *,
			 holidays_struct [], long double *,
			 long double *,  redemps_struc [],
			 instr_a *,
			pyparm_a *,
			result_a *,
			holiday_a *
				);
*/
/*
extern long EXPORT FAR testdll(double FAR *in_double,
					double FAR *out_double);
*/

#endif
