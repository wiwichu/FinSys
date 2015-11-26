#include "stdafx.h"
#include "instr.h"
#include "shrtdecs.h"

/*{redmparr accepts an instrument record a base date, a redemptions array
and a rule indicator and returns the current redemption adjustment, the
boundary dates for when that adjustment is in effect and adjusts the
maturity date on the instrument record to reflect average life if that is
the rule indicated.

	Usage:  unsigned long	redmparr(instr *in_instr, date_union base_date,
					long double *curr_redemp,
					redemps_struc redemps_array[],
					char calc_rule)

	where:  in_instr =	Input parameter of pointer to instr type which contains
				the instrument for which the adjustment is to be
				determined.

		base_date =	Input parameter of date_union type which
				contains the date for which the current adjustment
				and boundaries are to be determined.

		curr_redemp =  	Output parameter of long double type which
				contains the current adjustment.

		redemps_struc = Input paramater of type redemps_struc array
				containing the redemptions schedule.

		calc_rule =	Input parameter of type char which indicates
				the redemption rule. For valid choices see
				the py_xxx_redemp_sched symbols.

		return value =  of unsigned long type gives completion status.

    Called by:	<[py_calc]

}*/


unsigned long	_INSTRUMENT redmparr	(instr *in_instr, date_union base_date,
					long double *curr_redemp,
					redemps_struc redemps_array[],
					char calc_rule)

{
	#include "locals.h"

	long double temp_curr_redemp = 0;
	signed int cmp_int = -1;
	char element_count = 0;

	      /*{ Check for a redemption schedule.}*/

	      if (in_instr->redemps != 0)

	      {

		/*{ Cycle through all the redemption schedules before the base date.}*/

			 for 	(element_count = 0;
			  (cmp_int< 0) && (element_count < in_instr->redemps);
			  element_count++)
			 {


				cmp_int = datecmp(redemps_array[element_count].redemps_date.date_string,
					base_date.date_string);

				if (cmp_int < 0)

				{

					temp_curr_redemp = temp_curr_redemp +
					redemps_array[element_count].redemps_factor;

				}

			 }

			 *curr_redemp = in_instr->redemp_price - temp_curr_redemp;

			}

			else

			{

				*curr_redemp = 1;

			}

//redmparr_end:

	return return_status;
}
