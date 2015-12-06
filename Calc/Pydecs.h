//#define FAR
#define _export
#ifndef __pydecs_H
#define __pydecs_H
#ifndef _ANSIC
#define _PYFUNCS Py_Funcs::
#else
#define _PYFUNCS
#endif
#ifndef __insclass_H
#include "insclass.h"
#endif
#ifndef __instr_MAP
#include "instr.h"
#endif
#ifndef __insevent_MAP
#include "insevent.map"
#endif
#ifndef __shrtdecs_H
#include "shrtdecs.h"
#endif
#ifndef __intdecs_H
#include "intdecs.h"
#endif

/*{ Py_parms describes parameters to be used in py_calc.}*/

const	char	py_yes_parm_use = 0; /*{py_yes_parm_use means use the parameters.}*/
const	char	py_no_parm_use = 1;  /*{py_no_parm_use means use standards from the yield method.}*/
const	char	py_yes_calc_acc = 0; /*{py_yes_calc_acc means accrued interest should be calculated.}*/
const	char	py_no_calc_acc = 1;  /*{py_no_calc_acc means accrued interest is passed.}*/
const	char	py_pay_comp_freq = 0; /*{py_pay_comp_freq indicates that compounding occurs with the frequency of the payment.
					If payment is at maturity, compounding occurs annually.}*/
const	char	py_no_per_len = 0; /*{py_no_per_len indicates that the period length is taken from the formula convention.}*/
const	char	py_uniform_per_len = 1; /*{py_uniform_per_len indicates that the period length is uniform across periods.}*/
const	char	py_exact_per_len = 2; /*{py_exact_per_len indicates that the exact length for every period is taken.}*/
const	char	py_total_days_per_len = 3; /*{py_total_days_per_len indicates that the total days from each payment is divided by the period frequency.}*/
const	char	py_yes_eligible = 0; /*{ py_yes_eligible indicates a py eligibility.}*/
const	char	py_no_eligible = 1; /*{ py_no_eligible indicates a py ineligibility.}*/
const	char	py_eligible_general = 0; /*{ py_eligible_general indicates a general check for eligibility should be carried out.}*/
const	char	py_first_yield_meth = 0; /*{py_first_yield_meth marks the first symbol.}*/
const	char	py_aibd_yield_meth = 0; /*{py_aibd_yield_meth means the AIBD method.}*/
const	char	py_mmdisc_yield_meth = 1; /*{py_mmdisc_yield_meth means the Money Market Discount method.}*/
const	char	py_mm_yield_meth = 2; /*{py_mm_yield_meth means the Money Market Yield method.}*/
const	char	py_ytm_simp_yield_meth = 3; /*{py_ytm_simp_yield_meth means yield to maturity with simple fractional discounting.}*/
const	char	py_ytm_comp_yield_meth = 4; /*{py_ytm_comp_yield_meth means yield to maturity with compound fractional discounting.}*/
const	char	py_simp_yield_meth = 5; /*{py_simp_yield_meth means the simple (Japanese) method.}*/
const	char	py_curr_yield_meth = 6; /*{py_curr_yield_meth means the current yield method.}*/
const	char	py_gm_yield_meth = 7; /*{py_gm_yield_meth means the Greenwell Montagu method.}*/
const	char	py_muni_yield_meth = 8; /*{py_muni_yield_meth means the Municipal method.}*/
const	char	py_corp_yield_meth = 9; /*{py_corp_yield_meth means the Corporate Bond method.}*/
const	char	py_ustr_yield_meth = 10; /*{py_ustr_yield_meth means the US Treasury Bond method.}*/
const	char	py_moos_yield_meth = 11; /*{py_moos_yield_meth means the Moosmueller method.}*/
const	char	py_bf_yield_meth = 12; /*{py_bf_yield_meth means the Braess/Fangmeyer method.}*/
const	char	py_ty_yield_meth = 13; /*{py_ty_yield_meth means True Yield.}*/
const	char	py_MBS_yield_meth = 14; /*{py_MBS_yield_meth means Constant Prepayment Rate method (for MBS's).}*/
const	char	py_last_yield_meth = 15; /*{py_last_yield_meth marks the last symbol.}*/
const	char	py_dormant_yield_meth = 99; /*{py_dormant_yield_meth is used to inactivate code for methods not being used.}*/
const	char	py_yield_from_price_calc_what = 0; /*{py_yield_from_price_calc_what means calculate the yield from the price.}*/
const	char	py_price_from_yield_calc_what = 1; /*{py_price_from_yield_calc_what means calculate the price from the yield.}*/
const	char	py_yes_given_reinvest = 0; /*{py_yes_given_reinvest means the future payments are reinvested at a given rate.}*/
const	char	py_yes_sched_reinvest = 1; /*{py_yes_sched_reinvest means the future payments are reinvested at a scheduled rate.}*/
const	char	py_no_reinvest = 2; /*{py_no_reinvest means that no reinvestment assumption is made.}*/
const	char	py_coup_freq_comp_freq = 0; /*{py_coup_freq_comp_freq means compound with the frequency of the coupon.}*/
const	char	py_coup_days_comp_freq = 99; /*{py_coup_freq_comp_freq means compound with the days of the coupon.}*/
const	char	py_month_1_comp_freq = 1; /*{py_month_1_comp_freq means monthly compounding.}*/
const	char	py_month_2_comp_freq = 2; /*{py_month_2_comp_freq means compounding every two months.}*/
const	char	py_month_3_comp_freq = 3; /*{py_month_3_comp_freq means compounding every three months.}*/
const	char	py_month_4_comp_freq = 4; /*{py_month_4_comp_freq means compounding every four months.}*/
const	char	py_month_6_comp_freq = 6; /*{py_month_6_comp_freq means compounding every six months.}*/
const	char	py_month_12_comp_freq = 12; /*{py_month_12_comp_freq means compounding every twelve months.}*/
const	char	py_no_sched_disc_rule = 0; /*{py_no_sched_disc_rule means there is no schedule for discounting future cashflows, but the passed yield is used throughout.}*/
const	char	py_yes_sched_disc_rule = 1; /*{py_yes_sched_disc_rule means there is a schedule for discounting future cashflows.}*/
const	char	py_empty_force_par = 0; /*{py_empty_force_par means that no rule is passed.}*/
const	char	py_no_force_par = 1; /*{py_no_force_par means that par is not forced.}*/
const	char	py_yes_force_par = 2; /*{py_yes_force_par means that par is forced.}*/
const	char	py_empty_skip_odd = 0; /*{py_empty_skip_odd means that no rule is passed.}*/
const	char	py_no_skip_odd = 1; /*{py_no_skip_odd means that odd coupons are not ignored in yield calculations.}*/
const	char	py_yes_skip_odd = 2; /*{py_yes_skip_odd means that odd coupons are ignored in yield calculations.}*/
const	char	py_no_per_days = 0; /*{py_no_per_days means no special rule applies, and the calender from the instrument should be used. Otherwise one of the date_xxx_cal should be used.}*/
const	char	py_no_frac_per = 0; /*{py_no_frac_per means no special rule applies.}*/
const	char	py_simp_frac_per = 1; /*{py_simp_frac_per means simple discounting in a fractional period.}*/
const	char	py_comp_frac_per = 2; /*{py_comp_frac_per means compounding discounting in a fractional period.}*/
const	char	py_skip_frac_per = 3; /*{py_skip_frac_per means skip the first period as a special calculation.}*/
const	char	py_no_days_in_year = 0; /*{py_no_days_in_year means use the instrument definition.}*/
const	char	py_360_days_in_year = 1; /*{py_360_days_in_year means assume 360 days in the year.}*/
const	char	py_365_days_in_year = 2; /*{py_365_days_in_year means assume 365 days in the year.}*/
const	char	py_365L_days_in_year = 3; /*{py_365L_days_in_year means assume 366 days in the year if terminating date in a calculation falls in a leap year. Otherwise 365.}*/
const	char	py_actISDA_days_in_year = 4; /*{py_actISDA_days_in_year means assume 366 days in leap years. Otherwise 365.}*/
const	char	py_365_25_days_in_year = 5; /*{py_365_25_days_in_year means assume 365.25 days in the year.}*/
const	char	py_NL365_days_in_year = 6; /*{py_365_days_in_year means assume 365 days in the year.}*/
const	char	py_365A_days_in_year = 7; /*{py_365L_days_in_year means assume 366 days in the year if terminating date in a calculation falls in a leap year. Otherwise 365.}*/
const	char	py_366_days_in_year = 8; /*{py_366_days_in_year means assume 366 days in the year.}*/
const	char	py_average_redemp_sched = 0; /*{py_average_redemp_sched means the average redemption date is taken.}*/
const	char	py_equivalent_redemp_sched = 1; /*{py_equivalent_redemp_sched means the equivalent redemption dates are taken.}*/
const	char	py_last_redemp_sched = 2; /*{py_ast_redemp_sched means the last redemption schedule rule.}*/
const	char	py_cpr_prepay_type = 0; /*{ py_cpr_prepay_type means CPR method.}*/
const	char	py_smm_prepay_type = 1; /*{ py_smm_prepay_type means SMM method.}*/
const	char	py_last_prepay_type = 2; /*{ py_last_prepay_type marks the last symbol.}*/
const	char	py_yes_calc_first = 0; /*{ py_yes_calc_first indicates first period interest
												should be calculated.}*/
const	char	py_no_calc_first = 1; /*{ py_no_calc_first indicates first period interest
												is given.}*/

const	int	prepay_type_names_len = 4;

char	*const	prepay_type_names[py_last_prepay_type] =
			{"CPR","SMM"};


const	int	redemp_sched_names_len = 11;
/*
char	*const	sink_fund_mat_names[py_last_sink_fund_mat] =
			{"Equivalent","Average"};
*/
char	*const	redemp_sched_names[py_last_redemp_sched] =
			{"Average","Equivalent"};

const	int	yield_names_len = 18;

char	*const	yield_MBS_meth_name	= "MBS";

char 	*const  yield_meth_names[py_last_yield_meth] =
			{"ISMA","MM Discount",
			"MM Yield","Simple YtM",
			"Compound YtM","Simple (Japan)",
			"Current Yield","Greenwell Montagu","Muni",
			"Corporate","US TBond","Moosmueller",
			"Braess/Fangmeyer",
			"True Yield",
			yield_MBS_meth_name};
#ifndef _ANSIC
class CALC_API Py_Funcs : public Int_Calcs {

public:
#endif

Py_Funcs();
//Py_Funcs(CDB * DB_parm);

  typedef struct	py_parms	{char	parm_use;
				 /*{parm_use indicates whether the parameters are used, or standards are taken from the
				 yield method. See py_xxx_parm_use for allowable values.}*/
				 char	comp_freq;
				 /*{ comp_freq describes how frequently compounding occurs.
				 See py_xxxx_comp_freq for allowable values.}*/
				 char	comp_simp;
				 /*{ comp_simp indicates whether compound or simple interest is used in partial periods.
				 See py_xxxx_comp_simp for allowable values.}*/
				 char	per_len;
				 /*{ per_len indicates what conventions are used for period lengths.
				 See py_xxxx_per_len for allowable values.}*/
				 char	calc_first;
				 /*{ calc_first indicates whether interest for the first period is calculated or given.
				 See py_xxxx_calc_first for allowable values.}*/
				 char	yield_meth;
				 /*{ yield_meth indicates what yield method should be used.
				 See py_xxxx_yield_meth for allowable values.}*/
				 char	calc_what;
				 /*{ calc_what indicates what should be calculated.
				 See py_xxxx_calc_what for allowable values.}*/
				 char	calc_acc;
				 /*{ calc_acc indicates whether the accrued interest should be calculated.
				 See py_xxxx_calc_acc for allowable values.}*/
				 char	calc_nom_adj;
				 /*{ calc_nom_adj indicates whether the initial nominal adjustment should be calculated.
				 See py_xxxx_calc_nom_adj for allowable values.}*/
				 char	day_count;
				 /*{ day_count is an indicator of what calculation method
				 to use. See the same field in the instr record for
				 allowable values.}*/
				 char	date_cal_num;
				 /*{ date_cal_num is the numerator part of the calendar to use.
				 See date_xxx_cal for allowable values.}*/
				 char	date_cal_den;
				 /*{ date_cal_den is the denominator part of the calendar to use.
				 See date_xxx_cal for allowable values.}*/
				 char	frac_per;
				 /*{ frac_per indicates the rules for fractional periods.}*/
				 char	tax_rules[3];
				 /*{ tax_rules indicates what tax rules apply for this calculation.}*/
				 char	rate_assum[3];
				 /*{ rate_assum indicates what assumptions are made for future rates.}*/
				 char	prin_assum[3];
				 /*{ prin_assum indicates what assumptions are made for future principal payments.}*/
				 char	reinvest;
				 /*{ reinvest indicates what assumptions are made for future reinvestments.}*/
				 char	reinvest_sched[3];
				 /*{ reinvest_sched indicates what schedule is used for reinvestment assumptions.}*/
				 char	disc_rule;
				 /*{ disc_rule indicates what rule is used for discounting future cash flows.}*/
				 char	disc_sched[3];
				 /*{ disc_sched indicates what schedule is used for discounting future cash flows.}*/
				 char	per_days;
				 /*{ per_days indicates what rule is used for days_in a period.}*/
				 char	redemp_sched;
				 /*{ redemp_sched indicates what rule is used for time to redemption.}*/
				 char	pay_adj;
				 /*{ pay_adj indicates what rule is used for adjusting a date from a non business day.}*/
				 char	force_par;
				 /*{ force_par indicates whether a price of 100 forces the yield to the coupon and vice versa.}*/
				 char	skip_odd;
				 /*{  skip_odd indicates whether odd coupons are ignored in the yield calculation.}*/
				 char	prepay_type;
				 /*{  prepay_type indicates how prepayment rates are quoted.}*/
				 long double 	reinvest_rate;
				 /*{ reinvest_rate is the assumed reinvestment rate.}*/
				 long double 	cpr_rate;
				 /*{ cpr_rate is the constant prepayment rate.}*/
				 long double 	current_factor;
				 /*{ current_factor is the current pool factor.}*/
				 long double 	days_in_year;
				 /*{ days_in_year is the assumed number of days in a year.}*/
				 long double 	price_var;
				 /*{ price_var is the acceptable price variation when calculating yield.}*/
				}
		py_parms;

  unsigned long py_calc( instr,  date_union,
			 long double *,  long double *,
			 long double *,  long double *,
			  long double *,  long double *,
			 long double *,  py_parms,  char,
			  unsigned int,  unsigned int,
			 long double *,  long double *
//			 ,holidays_struct []
			,const set<string> &holiSet
			, long double *,
			 long double *,  redemps_struc [],
			 insevent_struct []
			,
			pay_struc  pay_array_a[],
			redemps_struc * part_pay_array_a,
			redemps_struc even_redemps[]
			 );

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
			redemps_struc redemps_array_parm[])


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
				py_date_oarm.

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
					only used if yield_meth = py_MBS_yield_meth.

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

		return value =  of unsigned long type gives completion status.

	 Called by:	<[]
	 }*/
/*
	unsigned long schedgen(event_sched event_parm, insevent_struct sched_dates [],
		date_union start_date, date_union end_date,
		unsigned int holi_chan, holidays_struct holi_parm [],
		char pay_type);
*/
#ifndef _ANSIC
private:
#endif

//	CDB * DB_local;
//	CDB::DB_Handles localhandles;
  unsigned long	py_frac_per(char, char *, long double, long double,
			long double *, char, date_union,	py_parms *,
			date_union, instr *, unsigned int, char *
//			,holidays_struct []
			,const set<string> &holiSet
			);


  unsigned long	py_simp_comp_frac( char *, py_parms *, instr *, date_union,
				unsigned int, char *
//				, holidays_struct []
				,const set<string> &holiSet
				);


  void		py_eligible_check(instr *, char, char *);

  unsigned long	py_days_in_year(long double *, char, char);

  unsigned long	py_days_sett_to_mat(long *, date_union, instr *);

  unsigned long	py_mmdisc(long, long double, long double, long double *,
			long double *, long double, instr *, py_parms *,
			long double *);

  unsigned long	py_simp(long, long double, long double, long double *,
			long double *, long double, instr *, py_parms *,
			long double *);

  unsigned long	py_reinvest_factor(long double);

  unsigned long	py_comp_freq(long double *, instr *, py_parms *,
			long double *, long double *);


  unsigned long	py_cal_set(char *, char *, instr *, py_parms *);

  unsigned long	py_day_count_set(char *, instr *, py_parms *);

  unsigned long	py_per_len( char *, py_parms *);

  unsigned long	py_pay_adj( char *, py_parms *, char *);

  unsigned long	py_price_var(long double *, py_parms *);

  unsigned long	py_start_py(long double *, long double *,
			long double *, long double *, long double,
			long double, py_parms *, instr *);
  /*
  unsigned long	py_redemp_sched( char *, long double *, unsigned int,
			py_parms);
  */
  unsigned long	py_pv_part_pays(long double *, char, int, date_union,
				char, long double, long double,
				long double, long double *, long double *,
				char, long double,redemps_struc * part_pay_array_a,
				int fast_calc);


  unsigned long	py_part_pay_load( unsigned int, date_union ,
					instr *, char, int *
//					, holidays_struct []
					,const set<string> &holiSet
					,redemps_struc * part_pay_array_a);

  unsigned long	py_force_par( char *, py_parms *);

  unsigned long	py_skip_odd( char *, py_parms *);

unsigned long   fast_calc_check(booleans *, instr, long double,
				char, long double, py_parms,
				long double, char, int);

  unsigned long	coups_to_mat(int *, instr, date_union, unsigned int
//	  ,	holidays_struct holi_parm []
		,const set<string> &holiSet
	  , long double);

  unsigned long	py_coup_load( char, char *, long double, long double,
			long double *, long double *, long double,
			char, unsigned int *, unsigned int, date_union,
			instr *, py_parms *, char, unsigned int, char,
			char *
//			, holidays_struct []
			,const set<string> &holiSet
			, long, long double,
			int *, insevent_struct rate_array [], int *,
			booleans, pay_struc [], long double first_int);


  unsigned long	py_pv_coups(char, char, long double, long double *, long double,
			long double *, long double *, long double *,
			char, unsigned int, date_union, py_parms *,
			long double *, long double *, long double,
			long double *, long double *, long double *, char,
			unsigned int
//			, holidays_struct []
			, instr, int,
			long double *, int *, int, pay_struc []);

  unsigned long	py_get_disc(date_union, long double *);

  unsigned long	py_even_redemps_load(char *, unsigned int, unsigned int *,
			instr *, char, py_parms *, int *, pay_struc [],
			redemps_struc []);

  unsigned long	py_pv_redemps( char, long double *, long double,
				unsigned int, long double *, long double,
				long double *, long, long double,
				long double, long double, py_parms, int,
				pay_struc [], redemps_struc [], long double *redemp_duration);

#ifndef _ANSIC
};
#endif
/*
#ifndef __pyfront_H
#include <pyfront.h>
#endif
*/
#endif
