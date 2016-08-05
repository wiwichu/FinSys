#ifndef __intdecs_H
#ifndef _ANSIC
#define _INTCALCS Int_Calcs::
#else
#define _INTCALCS
#endif
#include "datedec.h"
#include "instr.h"
#include "insevent.h"
//#include "holihead.h"
#include "datedec.h"
const	char    int_yes_total_per = 0;
/*{ int_yes_total_per indicates that interest for the entire period should be calculated.}*/

const	char    int_no_total_per = 1;
/*{ int_no_total_per indicates that normal interest date should be calculated.}*/

const	char    int_yes_redemp_adj = 0;
/*{ int_yes_redemp_adj indicates that interest should be adjusted by nominal redeemed.}*/

const	char    int_no_redemp_adj = 1;
/*{ int_no_redemp indicates that interest should not be adjusted by nominal redeemed.}*/

#ifndef _ANSIC

class CALC_API Int_Calcs: public Instrument
	{

public:

#endif

Int_Calcs();
//Int_Calcs(CDB * DB_parm);


unsigned long   nom_adj (instr *,
			date_union ,
			date_union *,
			date_union *,
			long double *);

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

/*{ redemp_adj is an internal function which returns the redemption
adjustment boundaries and the redemption adjustment for the current date.}*/

unsigned long   redemp_adj (instr ,
			date_union ,
			long double *,
			unsigned int,
//			holidays_struct holi_parm [],
			const set<string> &holiSet,
			date_union *);


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



  unsigned long 	intcalc	(instr ,
			date_union ,
			long double  *,
			long *,
			unsigned int ,
			char ,
			char ,
			long double  *,
			long double  *,
			char ,
			unsigned int 
//			holidays_struct  [],
			,const set<string> &holiSet
			,insevent_struct [],
			long double *whole_period_factor);

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
					long double *whole_period_factor)

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

		whole_period_factor  =

				Output parameter of type pointer to long double
				which returns a factor representing the fraction
				of a year which this whole period is.

		return value =  of unsigned long type gives completion status.

	 Called by:	<[]

  }*/

unsigned long	n_p_pay	(instr,
			date_union,
			date_union *,
			date_union *,
			unsigned int
//			,holidays_struct []
			,const set<string> &holiSet
			);

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


	unsigned long schedgen(event_sched event_parm
		, insevent_struct sched_dates []
		,date_union start_date
		, date_union end_date
		,unsigned int holi_chan
//		, holidays_struct holi_parm []
		,const set<string> &holiSet
		,char pay_type
		);

unsigned long	excoup (instr,
		       date_union,
		       booleans *,
				 unsigned int
//				 , holidays_struct []
				,const set<string> &holiSet
				 );

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
#ifndef _ANSIC

private:
#endif


//	CDB * DB_local;
//	CDB::DB_Handles localhandles;

	unsigned long	findfut(instr in_instr, date_union in_date,
			date_union *out_date, unsigned char day_hold, unsigned char week_hold);


   unsigned long eventchk(event_sched event_parm);


	/*{ per_calc is an internal function which calculates the interest
	over a specified period.}*/

	unsigned long per_calc (instr *, unsigned int *, unsigned int *,
				date_union *, date_union *, long double *,
				long *, date_union *, date_union *, long double *,
				insevent_struct rate_array [max_rates],
				long double *period_factor);

	/*{ quasi_proc applies quasi coupon processing to the current period.}*/

	unsigned long quasi_proc (instr, date_union, unsigned int, unsigned int,
				date_union *, date_union *, long double *, int,
				int, long *, long *, long double *, date_union *,
				date_union *, date_union *, date_union,
				long double *, insevent_struct rate_array [max_rates]);

	/*{ get_rate is an internal function which returns the current rate
	and the boundaries for when that rate is effective.}*/

	unsigned long   get_rate (instr *,
				date_union ,
				date_union *,
				date_union *,
				long double *,
				unsigned int,
				unsigned int,
				insevent_struct rate_array [max_rates]);

	/*{ get_pfactor is an internal function which returns the current
	pool factor.}*/

	unsigned long   get_pfactor (instr ,
				date_union ,
				long double *,
				unsigned int);

	/*{ comp_bounds is an internal function which returns the compounding
	boundaries for the current date.}*/

	unsigned long   comp_bounds (instr *,
				date_union ,
				date_union *,
				date_union *,
				unsigned int);
#ifndef _ANSIC
};
#endif



#define __intdecs_H
#endif

