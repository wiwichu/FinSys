#ifdef _ANSIC
#define _INSTRUMENT
#else
#define _INSTRUMENT Instrument::
#endif
#ifndef __instr_MAP
#include "datedec.h"
#include "shrtdecs.h"
//#include "holihead.h"
#include "datedec.h"
/*
#ifndef __intdecs_H
#include <intdecs.h>
#endif
*/

/* {  The instrument file, instr describes each instrument which may be
traded in the system. The fields are described below. Before the field
descriptions, constants are defined.
} */


/* Constants for the pay_type field. */

const	char	instr_fixed_pay_type	= 1;	/*{ instr_fixed_pay_type means
						a fixed rate }*/

const	char	instr_stepped_pay_type	= 2;	/*{ instr_stepped_pay_type means
						the rate varies but is known in advance. }*/

const	char	instr_float_pay_type	= 3; 	/*{ instr_float_pay_type means
						a floating rate }*/

const	char	instr_futstr_pay_type	= 4; 	/*{ instr_futstr_pay_type means
						a futures strip. }*/

const	char	instr_open_pay_type	= 5; 	/*{ instr_open_pay_type means
						unspecified }*/

/* Constants for the pay_sched field.*/

const	char	instr_str_pay_sched	= 1; 	/*{ instr_str_pay_sched means
						a straight schedule (regular
						frequency) }*/
/*
const	char	instr_step_pay_sched	= 2; 	/*{ instr_step_pay_sched means
						a stepped schedule (irregular,
						but known frequency) }*/

const	char	instr_free_pay_sched	= 3; 	/*{ instr_free_pay_sched means
						an unknown schedule }*/

/* Constants for the pay_factor field. */

const 	char 	instr_yes_pay_factor     = 1;	/*{ instr_yes_pay_factor means
						that pay factors are maintained.}*/

const 	char 	instr_no_pay_factor      = 0;	/*{ instr_no_pay_factor means
						that no pay factors are maintained.}*/

/* Constants for the neg_first field. */

const 	char 	instr_yes_neg_first     = 1;	/*{ instr_yes_neg_first means
						that the first coupon period
						is traded with negative
						interest.}*/

const 	char 	instr_no_neg_first      = 2;	/*{ instr_yes_neg_first means
						that the first coupon period
						is traded with negative
						interest.}*/


/* Constants for the rate_code field.*/

char	*const	instr_free_rate_code	= "free";  /*{ instr_free_rate_code
							means rates do not
							correspond to a standard
							code. }*/

char	*const	instr_fixed_rate_code	= "fixed"; /*{ instr_fixed_rate_code
							means instrument is fixed. }*/




/* Constants for field lengths. */

const	int	instr_instr_code_len	= 14;
const	int	instr_class_name_len	= 6;
const	int	instr_class_desc_len	= 25;
const	int	max_part_pays		= 5;
const	int	max_sink_fund		= 5;
//const	int	max_coups		= 62;
const	int	max_coups		= 1000;
const	int	max_rates		= 6;
const	int	max_cashflow		= 6;
const	int	max_holidays		= 20;
/*
typedef struct	pay_struc	{ date_union pay_date;
				long double payment;
				long double pv_factor;
				long double prime_factor;
				long double time_to_pay;};
*/

/* insevent constants */

const	char	insevent_intrate_event	= 1;	/*{ insevent_intrate_event contains an interest rate.}*/

const	char	insevent_factor_event	= 2;	/*{ insevent_factor_event contains a pool factor.}*/

const	char	insevent_redemp_event	= 3;	/*{ insevent_redemp_event contains a redemption per cent.}*/

const	char	insevent_partpay_event	= 4;	/*{ insevent_redemp_event contains a partial payment per cent.}*/

const	int	insevent_len		= 35;	/*{ insevent_len contains the length in bytes of insevent.}*/

const	int	insevent_event_len	= 1;	/*{ insevent_event_len contains the length in bytes of insevent.event.}*/
#ifndef __insevent_MAP
#include "insevent.h"
#endif

#ifndef _ANSIC

class CALC_API Instrument: public Inst_Event
	{

public:

#endif



  typedef struct	redemps_struc	{ date_union redemps_date;
				date_union end_date;
				long double redemps_factor;
				long double pv_factor;
				long double prime_factor;
				unsigned int coup_num;
				long double time_to_pay;};
  typedef struct	pay_struc	{char last_element;
				date_union pay_date;
				long double payment;
				long double pv_factor;
				long double prime_factor;
				long double time_to_pay;
				long double work_double;
				};
  typedef struct	rate_struc	{ date_union rate_date;
				date_union end_date;
				long double rate;
				};

typedef struct 	instr	{

			char 		instr_code[instr_instr_code_len];

			/*{ instr_code is a unique identifier for the
			instrument. It can be up to 14 characters in
			length. }*/

			char		class_name[instr_class_name_len];

								/*{ class_name names the class to which this instrument belongs.}*/

			char		class_desc[instr_class_desc_len];

                        /*{ class_desc describes the class to which this instrument belongs.}*/

			char		instr_class;

			/*{ instr_class holds the class to which this instrument belongs.}*/

			date_union 	issue_date;

			/*{ issue_date is the date the instrument was
			issued. }*/

			date_union 	accrue_date;

			/*{ accrue_date is the date the instrument starts
			accruing. }*/

			date_union 	mat_date;

			/*{ mat_date is the date the instrument
			matures. }*/

			unsigned char	prin_curr;

			/*{ prin_curr is the currency in which the
			principal is denominated. It is validated
			against the currency file (curr) }*/

			unsigned char	pay_curr;

			/* {pay_curr is the currency in which the
			payments are denominated. It is validated
			against the currency file (curr)} */

			char		day_count;

			/*{ day_count is a code determining what
			values are contained in cal_num and cal_den.
			valid choices are indicated by the
			date_xxx_day_count symbols.
			
			}*/

			char		cal_num;

			/*{ cal_num is the numerator indicator for accrual
			calculations. It must be one of the following:

				date_act_cal
				date_30_cal
				date_30e_cal

			}*/

			char		cal_den;

			/*{ cal_den is the denominator indicator for accrual

			calculations. It must be one of the following:

				date_act_cal	must have pay_type = instr_fixed_pay_type and pay_sched = instr_str_pay_sched.
				date_30_cal
				date_365_cal
				date_366_cal

			}*/

			char		lag;

			/*{ lag indicates the delay in days from the time a
			payment is due until when it is received. }*/

			char		pay_factor;

			/*{ pay_factor indicates whether payment factors are
			maintained for principal payments. acceptable values
			are indicated by the symbols instr_xxx_pay_factor.}*/

			long double 	service_fee;

			/* service_fee is the amount of fee taken in
			servicing an MBS.
                        */

			char 		pay_type;

			/* {pay_type indicates whether the pay rate is
			fixed or floating. For acceptable values see
			the constants instr_xxx_pay_type.} */

			char 		pay_sched;

			/*{ pay_sched indicates whether the pay schedule is
			straight, stepped or free. For acceptable values
			see the constants instr_xxx_pay_sched. }*/

			event_sched	pay_freq;

			/*{ pay_freq indicates how often payments are made.}*/

			date_union 	pre_last_pay;

			/*{ pre_last_pay is the last pay date before maturity. }*/

			event_sched	rerate_freq;

			/*{ rerate_freq indicates how often rate changes occur.
			See the constants event_sched_xxx_xxx for acceptable values. }*/

			event_sched	comp_freq;

			/*{ comp_freq indicates how often rate changes occur.
			See the constants event_sched_xxx_xxx for acceptable values. }*/

//			char  	holiday_code[holidaycodelength];

			/*{ Code to holiday table.}*/

			char		ex_coup_days;

			/*{ ex_coup_days is the number of days before a payment
			that the instrument is traded ex-coup, or with negative
			interest. }*/

			char		neg_first;

			/*{ neg_first is an indicator of whether the first coupon is traded with
			negative interest. See constants instr_xxx_neg_first
			for acceptable values.}*/

			char		rate_code[10];

			/*{ rate_code indicates the rate which is used for rerating the
			payments. It must correspond to an existing rate in the rate file,
			(rate) or be one of the constants instr_xxx_rate_code. }*/

			char		yield_meth;

			/*{ yield_meth indicates the default method for yield calculations.
			It must be one of the py_xxx_yield_meth symbols. }*/

			char		part_pays;

			/*{ part_pays indicates the number of partial payments. }*/

			char		redemps;

			/*{ redemps indicates the number of redemption ranges. }*/

			long double     part_pay_price_base;

			/*{ part_pay_price_base indicates the price base for the partial payments. }*/

			pay_struc	part_pays_sched[max_part_pays];

			/*{ part_pays_sched contains the partial payments schedule.}*/

			redemps_struc	redemp_sched[max_sink_fund];

			/*{ redemp_sched contains the redemption schedule for sinking funds.}*/

			long double           rate_offset;

			/*{ rate_offset indicates the deviation from the rate
			indicated under rate_code. }*/

			long double           interm_cap;

			/*{ interm_cap indicates the biggest upward movement
			allowed for any one rate change. }*/

			long double           interm_floor;

			/*{ interm_floor indicates the biggest downward movement
			allowed for any one rate change. }*/

			long double           life_cap;

			/*{ life_cap indicates the highest level the rate may
			reach. }*/

			long double           life_floor;

			/*{ life_floor indicates the lowest level the rate may
			reach. }*/

			long double           issue_price;

			/*{ issue_price is the price at which the instrument was issued. }*/

			long double           redemp_price;

			/*{ redemp_price is the price at which the instrument is redeemed. }*/

			}

		instr;

#ifndef _ANSIC

public:

#endif

	Instrument();
//	Instrument(CDB * DB_parm);


  unsigned long  classdef(instr *in_instr);

  /*{classdef accepts an instrument record and returns the defaults for the
  instrument class passed.

	Usage:  unsigned long	classdef(instr *in_instr)

	where:  in_instr =	Input/Output parameter of instr type which
				contains the defaults for the instrument
				class passed.

		return value =  of unsigned long type gives completion status.

	 Called by:	<[]

  }*/


unsigned long	redmparr(instr *, date_union , long double *,
			redemps_struc *, char);
/*
	unsigned long schedgen(event_sched event_parm, insevent_struct sched_dates [],
		date_union start_date, date_union end_date,
		unsigned int holi_chan, holidays_struct holi_parm [],
		char pay_type);
*/

#ifndef _ANSIC
private:
//	CDB * DB_local;
//	CDB::DB_Handles localhandles;
#endif

#ifndef _ANSIC

};
#endif

#define __instr_MAP
#endif

