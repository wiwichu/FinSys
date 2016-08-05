#include "stdafx.h"
#include "datedec.h"
#include "shrtdecs.h"
#include <stdlib.h>
//#include "iodec.h"

/*{adj_date adjusts a date according to the indicators passed.

	Usage:  unsigned long 	adj_date(date_union *in_date,
					char adj_date_ind,
					char holiday_adj,
					char weekend_ind,
					char holiday_ind,
					char holiday_code[],
					unsigned int holi_chan,
					holidays_struct holi_parm []);

	where:  in_date =	Input/Output parameter of date_union type
				which contains the date to be adjusted.

		adj_date_ind =	Input parameter of char type which indincates
				whether the adjustment is from non business
				to business or the reverse. The constants
				adj_date_xxx indicate valid values.

		holiday_adj =	Input parameter of char type which indicates
				the type of adjustment to be made. The
				constants event_sched_xxx_period indicate
				valid values.

		weekend_ind =	Input parameter of char type which indicates
				whether weekends are to be adjusted for. The
				constants adj_date_xxx_we indicate valid
				values.

		holiday_ind =	Input parameter of char type which indicates
				whether holidays are to be adjusted for. The
				constants adj_date_xxx_hol indicate valid
				values.

		holiday_code =	Input parameter of string type which indicates
				which holiday table to use.

		holi_chan =	Input parameter of file channel to be used for
				holiday file.

		holi_parm =	input parameter of type holidays_struct array
                		containing holiday schedule.

		return value =  of unsigned long type gives completion status.

    Called by:	<[n_p_pay]

}*/

unsigned long 	Date_Funcs::adj_date(date_union *date_parm,
			char adj_date_ind,
			char holiday_adj,
			char weekend_ind,
			char holiday_ind,
//			char holiday_code[],
			unsigned int holi_chan
//			,holidays_struct holi_parm []
			,const set<string> &holiSet
			)

{
	char *holiday_code = 0;
	#include "locals.h"

	char	dummy_char = 0;
	char	bus_day = adj_date_ind;		/*{ bus_day indicates whether the current date is a business day or not.}*/
	char	day_of_week = 0;			/*{ day_of_week holds the name of the day.}*/
	char	holiday_result = 0;			/*{ day_of_week holds the name of the day.}*/
	char	adj_dir = 0;			/*{ adj_dir indicates the direction of adjustment from non business to business, with 1 indicating into the future, and -1 indicating into the past. }*/
	char	loop_count = 0;                 /*{loop_count is used to prevent looping.}*/
	char const	loop_limit = 20;        /*{loop_limit is used to prevent looping.}*/

	int cmpres;
	long tenor_days;
	long tenor_days2;

	date_union in_date;			/*{ in_date is a work field for date_parm. }*/
	date_union hold_date;		/*{ hold_date is a work field for date manipulation. }*/
	date_union prevIMM_date;	/*{ prevIMM_date holds the previous IMM date. }*/
	date_union nextIMM_date;	/*{ nextIMM_date holds the next IMM date. }*/
	date_union nearIMM_date;	/*{ nearIMM_date holds the nearest IMM date. }*/

	booleans	month_changed = isfalse;			/*{ month_changed is true if the month has already changed.. }*/

//	strcpy(module_name,"adj_date");

	datecpy(in_date.date_string,date_parm->date_string);

	/*{ For same type adjustment, or, if no adjustment required,
		return without adjusting. For IMM always adjust.}*/

	if (
		((holiday_adj != event_sched_same_holiday_adj) &&
	   !((holiday_ind == adj_date_no_hol) &&
	   (weekend_ind == adj_date_no_we))) ||
		(holiday_adj == event_sched_nextIMM_holiday_adj) ||
		(holiday_adj == event_sched_prevIMM_holiday_adj) ||
		(holiday_adj == event_sched_nearIMM_holiday_adj)
		){

	  /*{ Initialize adj_dir according to holiday_adj.}*/

	  switch (holiday_adj)
	  {
	    case event_sched_next_holiday_adj:
	    case event_sched_np_holiday_adj:
	    case event_sched_march_holiday_adj:
	    {
	      adj_dir = 1;
	      break;
	    }
	    case event_sched_prev_holiday_adj:
	    case event_sched_pn_holiday_adj:
	    {
	      adj_dir = -1;
	      break;
	    }
	    case event_sched_prevIMM_holiday_adj:
	    case event_sched_nextIMM_holiday_adj:
	    case event_sched_nearIMM_holiday_adj:
	    {

		  if (holiday_adj != event_sched_prevIMM_holiday_adj)
		  {

			return_status = forecast(in_date,
			  (in_date.date.months % 3),
			  0,
			  date_act_cal,
			  &nextIMM_date);

			if (return_status)
			{
					
				goto func_end;

			}

			nextIMM_date.date.days = 1;

			return_status = findday(nextIMM_date, &day_of_week);			

			switch (day_of_week)
			{
				case    date_sun_day:
				{
					nextIMM_date.date.days = 17;
					break;
				}
				case    date_mon_day:
				{
					nextIMM_date.date.days = 18;
					break;
				}
				case    date_tues_day:
				{
					nextIMM_date.date.days = 19;
					break;
				}
				case	date_wednes_day:
				{
					nextIMM_date.date.days = 13;
					break;
				}
				case    date_thurs_day:
				{
					nextIMM_date.date.days = 14;
					break;
				}
				case    date_fri_day:
				{
					nextIMM_date.date.days = 15;
					break;
				}
				case    date_satur_day:
				{
					nextIMM_date.date.days = 16;
					break;
				}
			}


			cmpres = datecmp(in_date.date_string,
							nextIMM_date.date_string);

			if (cmpres >= 0 )
			{

				return_status = forecast(nextIMM_date,
				  (nextIMM_date.date.months % 3),
				  0,
				  date_act_cal,
				  &hold_date);

				if (return_status)
				{
					
					goto func_end;

				}

				nextIMM_date.date.days = 1;
	
				return_status = findday(nextIMM_date, &day_of_week);			
	
				switch (day_of_week)
				{
					case    date_sun_day:
					{
						nextIMM_date.date.days = 17;
						break;
					}
					case    date_mon_day:
					{
						nextIMM_date.date.days = 18;
						break;
					}
					case    date_tues_day:
					{
						nextIMM_date.date.days = 19;
						break;
					}
					case	date_wednes_day:
					{
						nextIMM_date.date.days = 13;
						break;
					}
					case    date_thurs_day:
					{
						nextIMM_date.date.days = 14;
						break;
					}
					case    date_fri_day:
					{
						nextIMM_date.date.days = 15;
						break;
					}
					case    date_satur_day:
					{
						nextIMM_date.date.days = 16;
						break;
					}
				}

			}

			datecpy(hold_date.date_string,prevIMM_date.date_string);
			
		  }

		  if (holiday_adj != event_sched_nextIMM_holiday_adj)
		  {

			return_status = forecast(in_date,
			  -(in_date.date.months % 3),
			  0,
			  date_act_cal,
			  &nextIMM_date);

			if (return_status)
			{
					
				goto func_end;

			}

			nextIMM_date.date.days = 1;

			return_status = findday(nextIMM_date, &day_of_week);			

			switch (day_of_week)
			{
				case    date_sun_day:
				{
					nextIMM_date.date.days = 17;
					break;
				}
				case    date_mon_day:
				{
					nextIMM_date.date.days = 18;
					break;
				}
				case    date_tues_day:
				{
					nextIMM_date.date.days = 19;
					break;
				}
				case	date_wednes_day:
				{
					nextIMM_date.date.days = 13;
					break;
				}
				case    date_thurs_day:
				{
					nextIMM_date.date.days = 14;
					break;
				}
				case    date_fri_day:
				{
					nextIMM_date.date.days = 15;
					break;
				}
				case    date_satur_day:
				{
					nextIMM_date.date.days = 16;
					break;
				}
			}


			cmpres = datecmp(in_date.date_string,
							nextIMM_date.date_string);

			if (cmpres < 0 )
			{

				return_status = forecast(nextIMM_date,
				  -(nextIMM_date.date.months % 3),
				  0,
				  date_act_cal,
 				  &hold_date);

				if (return_status)
				{
					
					goto func_end;

				}

				nextIMM_date.date.days = 1;
	
				return_status = findday(nextIMM_date, &day_of_week);			
	
				switch (day_of_week)
				{
					case    date_sun_day:
					{
						nextIMM_date.date.days = 17;
						break;
					}
					case    date_mon_day:
					{
						nextIMM_date.date.days = 18;
						break;
					}
					case    date_tues_day:
					{
						nextIMM_date.date.days = 19;
						break;
					}
					case	date_wednes_day:
					{
						nextIMM_date.date.days = 13;
						break;
					}
					case    date_thurs_day:
					{
						nextIMM_date.date.days = 14;
						break;
					}
					case    date_fri_day:
					{
						nextIMM_date.date.days = 15;
						break;
					}
					case    date_satur_day:
					{
						nextIMM_date.date.days = 16;
						break;
					}
				}

			}

			datecpy(hold_date.date_string,nextIMM_date.date_string);			

		  }
		  if (holiday_adj == event_sched_nearIMM_holiday_adj)
		  {

			return_status = tenor	(prevIMM_date,
				in_date,
				date_act_cal,
				&tenor_days);

			if (return_status)
			{
					
				goto func_end;

			}

			return_status = tenor	(in_date,
				nextIMM_date,
				date_act_cal,
				&tenor_days2);

			if (return_status)
			{
					
				goto func_end;

			}

			if (tenor_days2 >= tenor_days)
			{

				datecpy(nearIMM_date.date_string,nextIMM_date.date_string);

			}
			else
			{

				datecpy(nearIMM_date.date_string,prevIMM_date.date_string);

			}

			datecpy(hold_date.date_string,nearIMM_date.date_string);
					  
		  }

		  datecpy(in_date.date_string,hold_date.date_string);
						
		  goto func_end;
	      break;
	    }
	    default:
	    {
         goto func_end;

			break;
		}
	  }

	  /*{ Keep adjusting date until desired result achieved.}*/

	  do {

	    /*{ First do weekend check, if required.}*/

			if (weekend_ind == adj_date_yes_we)
			{

				return_status = findday(in_date, &day_of_week);

				if (return_status != return_success)
				{

					goto func_end;
				}

				if ((day_of_week == date_sun_day) ||
					(day_of_week == date_satur_day))
				{

					bus_day = adj_date_non_to_bus;

				}

				else
				{

					bus_day = adj_date_bus_to_non;

				}

			}

			/*{ Next do holiday adjustment, if required.}*/

			if ((holiday_ind == adj_date_yes_hol) &&
				((bus_day != adj_date_ind) &&
					(adj_date_ind == adj_date_non_to_bus)) ||
				((bus_day == adj_date_ind) &&
					(adj_date_ind == adj_date_bus_to_non)))
			{

				return_status = findhol(in_date
					, holiday_code
					,&holiday_result
					, holi_chan
					, &dummy_char
//					,holi_parm
					,holiSet
					);

				if (return_status != return_success)
				{

  					goto func_end;
				}

				if (holiday_result == findhol_yes_hol)
				{

					bus_day = adj_date_non_to_bus;

				}

				else
				{

					bus_day = adj_date_bus_to_non;

				}
			}

			/*{ If target date has not been achieved, adjust date.}*/

			if (bus_day == adj_date_ind)
			{

				return_status = forecast(in_date,0,(adj_dir*bus_day),
					date_act_cal,&hold_date);

				if (return_status != return_success)
				{

  					goto func_end;
				}

				/*{ If the month has changed for a type which prohibits this,
					change direction of adjustment.}*/

				if ((in_date.date.months != hold_date.date.months) &&
					(( holiday_adj == event_sched_np_holiday_adj) ||
					(holiday_adj == event_sched_march_holiday_adj) ||
					( holiday_adj == event_sched_pn_holiday_adj)))
				{

					/*{ For np and pn, flag error if entire
						month is set to a holiday.}*/

					if (month_changed )
					{

						goto func_end;
					}

					else
					{

						adj_dir = adj_dir*(-1);
						month_changed = istrue;

					}

				}

				/*{ Otherwise loop again with the new date.}*/

				else
				{

					datecpy (in_date.date_string,hold_date.date_string);

				}
			}
			loop_count++; /* Flag error if looping.*/

		}  while ((bus_day == adj_date_ind) && (loop_count < loop_limit));
	}

func_end:

	/* Flag error if looping.*/

	if (loop_count >= loop_limit)
	{

	  return_status = return_err_loop;

	}

	datecpy(date_parm->date_string,in_date.date_string);

	return return_status;

}

/*{adj_last adjusts the days in the date passed if they exceed the maximum
   days in month.

	Usage:  unsigned long adj_last(date_union *in_date)

	where:  *in_date =	Input parameter of pointer to date_union
				type which contains the date to be adjusted.

		return value =  of unsigned long type gives completion status.

    Called by:	<[forecast]

}*/

unsigned long Date_Funcs::adj_last(date_union *in_date)

{

//	#include "locals.h"
	int	month_days = 0;
	int	actual_year = 0;
	unsigned long return_status = return_success;

//	strcpy(module_name,"adj_last");

	switch (in_date->date.months)
	{
		 case 1:
		 {
			if (in_date->date.days > 31)
			{
				in_date->date.days = 31;
			}
		 }
		 break;
		 case 2:
		 {
			month_days = 28;

			actual_year = (in_date->date.centuries*100) +
				in_date->date.years;

			/*{If this is a leap year, add an extra day.}*/

			if ((actual_year)%4==0)
			{
				if (!((in_date->date.centuries%4!=0)&&actual_year==0))
				{
				 month_days++;
				}
			}
			if (in_date->date.days > month_days)
			{
				in_date->date.days = month_days;
			}
			break;
		 }
		 case 3:
		 {
			if (in_date->date.days > 31)
			{
				in_date->date.days = 31;
			}
			break;
		 }
		 case 4:
		 {
			if (in_date->date.days > 30)
			{
				in_date->date.days = 30;
			}
			break;
		 }
		 case 5:
		 {
			if (in_date->date.days > 31)
			{
				in_date->date.days = 31;
			}
			break;
		 }
		 case 6:
		 {
			if (in_date->date.days > 30)
			{
				in_date->date.days = 30;
			}
			break;
		 }
		 case 7:
		 {
			if (in_date->date.days > 31)
			{
				in_date->date.days = 31;
			}
			break;
		 }
		 case 8:
		 {
			if (in_date->date.days > 31)
			{
				in_date->date.days = 31;
			}
			break;
		 }
		 case 9:
		 {
			if (in_date->date.days > 30)
			{
				in_date->date.days = 30;
			}
			break;
		 }
		 case 10:
		 {
			if (in_date->date.days > 31)
			{
				in_date->date.days = 31;
			}
			break;
		 }
		 case 11:
		 {
			if (in_date->date.days > 30)
			{
				in_date->date.days = 30;
			}
			break;
		 }
		 case 12:
		 {
			if (in_date->date.days > 31)
			{
				in_date->date.days = 31;
			}
			break;
		 }
		 default:
		 {
			return_status = return_err_invalid_month;
			goto func_end;
		 }



	}

func_end:
	  return return_status;
}


  /*{datechck validates whether the passed date is possible.

	Usage:  unsigned long 	datechck(date_union check_date1);

	where:  check_date1 =	Input/Output parameter of date_union type
				which contains the date to be checked.

  }*/



unsigned long   Date_Funcs::datechck	(date_union check_date1)

{

	#include "locals.h"
	date_union dummy_date1;

//	strcpy(module_name,"datechck");

			if ((check_date1.date.centuries + check_date1.date.years) <= 0)
			{

			  return_status = return_err_date_bad;

			}
			else
			{

			  if ((check_date1.date.months <= 0) ||
				  (check_date1.date.months > 12))
			  {

				 return_status = return_err_date_bad;

			  }
			  else
			  {

				  if (check_date1.date.days <= 0)
				  {

					return_status = return_err_date_bad;

				  }
				  else
				  {

					 datecpy(dummy_date1.date_string,check_date1.date_string);

					 return_status = adj_last(&dummy_date1);

					 if (return_status)
					 {


					 }
					 else
					 {

						if (dummy_date1.date.days < check_date1.date.days)
						{

						 return_status = return_err_date_bad;

						}
					 }
				  }
			  }
			}


//func_end:
	  return return_status;
}
unsigned long   Date_Funcs::CheckDate
	(unsigned int year, unsigned int month, unsigned int day)
{
	unsigned long return_state;
	date_union check_date;

	return_state = return_success;
	check_date.date.centuries = year/100;
	check_date.date.years = year%100;
	check_date.date.months = month;
	check_date.date.days = day;
	check_date.date.null = null;

	return_state = datechck(check_date);

//func_end:
	return return_state;
}

/* {Datecmp compares one date to another.

    Usage:	int		datecmp	(const void * date1,
				const void * date2)

    where:	date1 = 	Input parameter of type pointer to constant void
				indicating the first date.

		date2  =	Input parameter of type pointer to void constant
				indicating the second date.

		return value has the same signficance as by memcmp.
    Calls:	>

    }
*/

int  Date_Funcs::datecmp 	(const void * date1,
			const void * date2)

{

	#include "locals.h"

int cmp_result = 0;


	cmp_result = memcmp(date1, date2, 5);


//datecmp_end:

	return cmp_result;

}


/*{dateconv accepts a date format, a direction indicator and either a
date string or a date union or a double with the date. It uses the direction
indicator to determine whether the datestring or the date union will be converted.

	Usage:  unsigned long	dateconv(char date_format, char conv_dir
				char date_chars[], date_union *date_stored,
				double in_date)

	where:  date_format	input parameter of type char which indicates
				the date format.

		conv_dir	input parameter of type char which indicates
				the direction of conversion. It must be one
				of the following:

				dateconv_string_to_union
				dateconv_union_to_string

		date_charscharacter array holding the date as a
				string.

		date_union	a date_union type holding the date as a
				date_union.

                in_date		a double type holding the date.

		return value =  of unsigned long type gives completion status.

    Called by:	<[]

}*/

unsigned long 	Date_Funcs::dateconv(char date_format, char conv_dir,
		char date_chars[], date_union *date_stored, double *in_date)


{

#include "locals.h"

char *const zero_char = "0";

char date_separator = 0;
char date_days[3];
char date_months[3];
char date_years[5];

int days_hold = 0;
int months_hold = 0;
int years_hold = 0;
int centuries_hold = 0;

int int_cmp = 0; 

long julian_hold = 0;
long in_date_hold = 0;
long est_years = 0;
long extra_years = 0;

date_union date_hold;
date_union date_hold_2;

//  strcpy (module_name,"dateconv");


  switch (conv_dir)
  {
    case (dateconv_string_to_union):
    {

      /*{Initialize result to all nines so that on an error an invalid
      date is returned.}*/
     
      date_stored->date.centuries = 99;
      date_stored->date.years = 99;
      date_stored->date.months = 99;
      date_stored->date.days = 99;
      date_stored->date.null = null;

      /*{ Determine whether the date is in the proper format }*/
      switch (date_format)
      {

	case (date_format_1):
	{

	  memcpy(&date_separator,date_format_1_separator,1);

          /*{Check that the separators are properly placed.}*/

	  int_cmp = memcmp(&date_separator,&date_chars[2],1);

	  if (int_cmp != 0)
	  {

	    return_status = return_err_date_form_bad;


      	    goto func_end;

	  }
	  else
	  {

	    int_cmp = memcmp(&date_separator,&date_chars[5],1);

	    if (int_cmp != 0)
	    {

	      return_status = return_err_date_form_bad;


      	      goto func_end;

	    }
	  }

          /*{ Load the date components into the date union.}*/

	  memcpy(date_years,&date_chars[6],4);
	  memcpy(&date_years[4],&null,1);
	  years_hold = atoi(date_years);

	  if (years_hold <= 0)
	  {

	      return_status = return_err_date_bad;


      	      goto func_end;
	  }

	  memcpy(date_months,&date_chars[3],2);
	  memcpy(&date_months[2],&null,1);
	  months_hold = atoi(date_months);

	  if ((months_hold <= 0) || (months_hold > 12))
	  {

	      return_status = return_err_date_bad;


      	      goto func_end;
	  }

	  memcpy(date_days,date_chars,2);
	  memcpy(&date_days[2],&null,1);
	  days_hold = atoi(date_days);

	  if (days_hold <= 0)
	  {

	      return_status = return_err_date_bad;


      	      goto func_end;
	  }

	  date_stored->date.centuries = years_hold / 100;
	  date_stored->date.years = years_hold % 100;
	  date_stored->date.months = months_hold;
	  date_stored->date.days = days_hold;
	  date_stored->date.null = null;

	  datecpy(date_hold.date_string,date_stored->date_string);

          return_status = adj_last(&date_hold);

	  if (return_status)
	  {


      	    goto func_end;

	  }

	  if (date_hold.date.days < date_stored->date.days)
	  {

	      return_status = return_err_date_bad;


      	      goto func_end;
	  }


          break;
	}
	default:

	  return_status = return_err_date_form_inv;


      	  goto func_end;


      }


      break;
    }
    case (dateconv_union_to_string):
    {


      memcpy(&date_separator,date_format_1_separator,1);

      days_hold = date_stored->date.days;
      months_hold = date_stored->date.months;
      years_hold = (date_stored->date.centuries * 100) +
      	date_stored->date.years;

//      utilitoa(days_hold,date_days,10);
//      utilitoa(months_hold,date_months,10);
//      utilitoa(years_hold,date_years,10);
      _itoa(days_hold,date_days,10);
      _itoa(months_hold,date_months,10);
      _itoa(years_hold,date_years,10);

/*
      gcvt(double(days_hold),2,date_days);
      gcvt(double(months_hold),2,date_months);
      gcvt(double(years_hold),4,date_years);
*/
      if (days_hold < 10)
      {

	memcpy(&date_days[1],date_days,2);
	memcpy(date_days,zero_char,1);

      }

      if (months_hold < 10)
      {

	memcpy(&date_months[1],date_months,2);
	memcpy(date_months,zero_char,1);

      }


      strcpy(date_chars,date_days);
      memcpy(&date_chars[2],&date_separator,1);
      strcpy(&date_chars[3],date_months);
      memcpy(&date_chars[5],&date_separator,1);
      strcpy(&date_chars[6],date_years);
      memcpy(&date_chars[10],&null,1);

      break;
    }
    case (dateconv_double_to_union):
    {

      /*{ First get the Julian date for the base year. For Access this is
      	December 30, 1899.}*/	

      /*{ First set the the base year. For Access this is
      	December 30, 1899.}*/	

      date_hold.date.centuries = 18;
      date_hold.date.years = 99;
      date_hold.date.months = 12;
      date_hold.date.days = 30;
      date_hold.date.null = null;

      /*{ Estimate the years.}*/

      est_years = (long) (*in_date / 365);

      /*{ Force increments of four.}*/

      est_years = est_years - (est_years % 4);

      /*{ Figure estimated date.}*/

      return_status = forecast(date_hold,
			  (est_years * 12),
			  0,
			  date_act_cal,
			  &date_hold_2);

      if (return_status != return_success) {

	      goto func_end;
      }

      /*{ Find the days between the two dates.}*/

      return_status = tenor (date_hold,
      				date_hold_2,
				date_act_cal,
				&julian_hold);

      if (return_status != return_success) {


		goto func_end;

      }

      /*{ Forecast the number of days.}*/

      return_status = forecast(date_hold_2,
			  0,
			  (long)( *in_date - julian_hold),
			  date_act_cal,
			  &date_hold);

      if (return_status != return_success) {

	      goto func_end;
      }

      datecpy(date_stored->date_string,date_hold.date_string);
/*
      return_status = date_to_days (date_hold, &julian_hold);

      if (return_status)
      {


        goto func_end;

      }
*/
      /*{ Add the passed days to the base date.}*/


      /*{ Convert the Julian date back to a date_union.}*/
/*
      return_status = days_to_date (julian_hold, date_stored);

      if (return_status)
      {


        goto func_end;

      }
*/
      break;
    }
    case (dateconv_union_to_double):
    {

      /*{ First get the Julian date for the base year. For Access this is
      	December 30, 1899.}*/	

      /*{ First set the the base year. For Access this is
      	December 30, 1899.}*/	

      date_hold.date.centuries = 18;
      date_hold.date.years = 99;
      date_hold.date.months = 12;
      date_hold.date.days = 30;
      date_hold.date.null = null;

      /*{ Find the tenor between the two dates.}*/

      return_status = tenor (date_hold,
      				*date_stored,
				date_act_cal,
				&julian_hold);

      if (return_status != return_success) {


		goto func_end;

      }

      *in_date = (double) julian_hold;

/*
      return_status = date_to_days (date_hold, &julian_hold);

      if (return_status)
      {


        goto func_end;

      }
*/
      /*{ Get the days in the passed date.}*/
/*
      return_status = date_to_days (*date_stored, &in_date_hold);

      if (return_status)
      {


        goto func_end;

      }
*/
      /*{ Subtract the base days from the derived date.}*/


      break;
    }
    default:
    {

      return_status = return_err_date_conv_dir_inv;


      goto func_end;

      break;
    }
  }  

func_end:

  return return_status;

}


/* {Datecpy copies one date to another.

    Usage:	void		datecpy	(void * dest_date,
				const void * src_date)

    where:	dest_date = 	Output parameter of type pointer to void
				indicating the destination date.

		src_date  =	Input parameter of type pointer to void constant
				indicating the source date.

    Calls:	>

    }
*/

void  	 Date_Funcs::datecpy	(void * dest_date,
			const void * src_date)

{

	#include "locals.h"

	size_t date_size;

      date_size = 5;

		memcpy(dest_date, src_date, date_size);


//datecpy_end:

	return;

}

/*{date_to_days converts a calendar date to the number of days since December
31, B.C.

	Usage:	unsigned long 	date_to_days	(date_union in_date,
					int *out_days)

	where:  in_date =	input parameter of structure type date_union,
				which is the date to be translated into days.

		out_days =      output parameter of type integer which is the
				total number of days in_date contains.

		return value =	unsigned long indicating completion status

    Called by:	<[tenor]

}*/

unsigned long Date_Funcs::date_to_days	(date_union in_date, long *out_days)
{
/*{variables used}*/

//	#include "locals.h"
	long	hold_years = 0;	/*{hold_years is number of years in date.}*/
	long	year_days = 0;  /*{year_days is number of days in years of date.}*/
	long	month_days = 0; /*{month_days is number of days in months of date.}*/

	char	month_count = 1; /*{month_count tracks months in current year.}*/

	date_union date_less_1_year;

	unsigned long return_status = return_success;

//	strcpy(module_name,"date_to_days");

/*{Extract years from the date.}*/

	hold_years = (in_date.date.centuries*100)+in_date.date.years;

/*{Reduce years by one for current year.}*/

	hold_years = hold_years - 1;
	return_status = forecast(in_date,-12,0,
		date_act_cal,&date_less_1_year);

	if (return_status != return_success)
	{


	  goto func_end;
	}


/*{Multiply years by 365}*/

	year_days = hold_years*365;

/*{Increment for normal leap years.}*/

	year_days = year_days + hold_years/4;

/*{Reduce years for centuries without leapyears.}*/

	year_days = year_days -((3 * (date_less_1_year.date.centuries/4))+
				(date_less_1_year.date.centuries%4));

/*{Calculate the days in each month which has passed in the current year.}*/

	while ((int)month_count < in_date.date.months)

	{
	  switch (month_count)
	  {
		 case 1:
		 {
			/*{Add 31 days if January has passed.}*/
			month_days = month_days + 31;
			break;
		 }
		 case 2:
		 {
			/*{Add 28 days if February has passed.}*/
			month_days = month_days + 28;
			/*{But if this is a leap year, add an extra day.}*/
			if ((hold_years+1)%4==0)
			{
				if (!((in_date.date.centuries%4!=0) &&
				in_date.date.years==0))
				{
					 month_days = month_days + 1;
				}
			}
			break;
		 }
		 case 3:
		 {
			/*{Add 31 days if March has passed.}*/
			month_days = month_days + 31;
			break;
		 }
		 case 4:
		 {
			/*{Add 30 days if April has passed.}*/
			month_days = month_days + 30;
			break;
		 }
		 case 5:
		 {
			/*{Add 31 days if May has passed.}*/
			month_days = month_days + 31;
			break;
		 }
		 case 6:
		 {
			/*{Add 30 days if June has passed.}*/
			month_days = month_days + 30;
			break;
		 }
		 case 7:
		 {
			/*{Add 31 days if July has passed.}*/
			month_days = month_days + 31;
			break;
		 }
		 case 8:
		 {
			/*{Add 31 days if August has passed.}*/
			month_days = month_days + 31;
			break;
		 }
		 case 9:
		 {
			/*{Add 30 days if September has passed.}*/
			month_days = month_days + 30;
			break;
		 }
		 case 10:
		 {
			/*{Add 31 days if October has passed.}*/
			month_days = month_days + 31;
			break;
		 }
		 case 11:
		 {
			/*{Add 30 days if November has passed.}*/
			month_days = month_days + 30;
			break;
		 }
	  }
	  month_count = month_count + 1;
	}

	/*{Add days in years, days in months and days in current month.}*/

	*out_days = year_days + month_days + in_date.date.days;

func_end:

	return return_status;

}

/*{days_to_date converts number of days to a calendar date.

	Usage:	unsigned long 	days_to_date	(long in_days,
					date_union *out_date)

	where:  in_days =	input parameter of long type, which is the
				number of days to be translated into a date.

		out_date =      output parameter of union type date_union, which
				is the resulting output date.

		return value =  unsigned long indicating completion status.

    Called by:	<[forecast]

}*/

unsigned long Date_Funcs::days_to_date	(long in_days,
				date_union *out_date)
{

/*{variables used}*/

	#include "locals.h"
	long	hold_years 	= 0;	/*{hold_years is number of years in date.}*/
	long	hold_years_2 	= 0;	/*{hold_years is number of years in date.}*/
	long	hold_centuries 	= 0;	/*{hold_years is number of years in date.}*/
	long	leap_days 	= 0; /*{month_days is number of days in months of date.}*/

//	strcpy(module_name,"days_to_date");

	/*{Divide days by 365, giving years.}*/

	hold_years = in_days/365;

	/*{Determine number of leap days to be adjusted for.}*/

	leap_days = hold_years/4;

	/*{Extract centuries from years.}*/

	hold_centuries = hold_years/100;

	/*{Reduce leap_days by non leap centuries.}*/

	leap_days = leap_days -((3*(hold_centuries/4))+
				(hold_centuries%4));

	/*{Subtract leap_years from resulting year.}*/

	hold_years_2 = hold_years - leap_days/365;

	/*{Remove whole years from leap_days.}*/

	leap_days = (leap_days%365);

	/*{Subtract a day for every leap year between hold_years and hold_years_2}*/

	while (hold_years > hold_years_2) {

		/*{Every year evenly divisible by 4 is a leap year.}*/

		if ((hold_years)%4==0)
		{

		  /*{Except centuries not divisible by 400.}*/

		  if (!((hold_years%100==0)&&(hold_years%400!=0)))
		  {
			    leap_days--;
		  }
		}
		hold_years--;
	}

	in_days = in_days%365 - leap_days;

	/*{Initialize out_date.}*/

	out_date->date.centuries	= hold_years_2/100;
	out_date->date.years		= hold_years_2%100;
	out_date->date.months	= 12;
	out_date->date.days		= 31;

	/*{Add remaining in_days to hold_years_2.}*/

	out_date->date.days	= (char)(out_date->date.days + in_days);

	while ((out_date->date.days > month_end(*out_date)) ||
		(out_date->date.days < 1))
	{

		if (out_date->date.days < 1)
		{

			out_date->date.months--;

			if (out_date->date.months < 1)
			{

				out_date->date.years--;
				out_date->date.months = 12;

				if (out_date->date.years < 0)
				{

					out_date->date.years = 99;
					out_date->date.centuries--;
				}

			}

			out_date->date.days = out_date->date.days +
				month_end(*out_date);

		}

		else
		{
			out_date->date.days = out_date->date.days -
				month_end(*out_date);
			out_date->date.months++;

			if (out_date->date.months > 12)
			{

				out_date->date.years++;
				out_date->date.months = 1;

				if (out_date->date.years == 100)
				{

					out_date->date.years = 0;
					out_date->date.centuries++;
				}

			}
		}
	}

	return return_status;
}

/*{findday returns the day of the week when a date is passed to it.

	Usage:  unsigned long findday(date_union in_date, char out_day)

	where:  in_date =	Input parameter of date_union type which
				contains the date for which the day is to
				be found.

		out_day =	Output parameter of type pointer to
				character which contains the day of the
				week which in_date falls on. It will be one
				of the date_xxx_day symbols.

		return value =  of unsigned long type gives completion status.

    Called by:	<[forecast]

}*/

unsigned long Date_Funcs::findday(date_union in_date, char *out_day)

{


//	#include "locals.h"
	long	hold_in_days 	= 0; /*{hold_in_days holds the number of days in in_date.}*/
	long	hold_base_days 	= 0; /*{hold_base_days holds the number of days in base_date.}*/

	unsigned long return_status = return_success;

	date_union base_date;

//	strcpy(module_name,"findday");

	/*{ Use Sunday, November 15, 1992 as base_date. }*/

	base_date.date.centuries 	= 19;
	base_date.date.years	 	= 92;
	base_date.date.months 		= 11;
	base_date.date.days 		= 15;

	/*{ Convert base_date to days. }*/

	return_status = date_to_days 	(base_date,
					&hold_base_days);

	if (return_status != return_success)
	{

		goto func_end;
	}

	/*{ Convert in_date to days. }*/

	return_status = date_to_days 	(in_date,
					&hold_in_days);

	if (return_status != return_success)
	{

		goto func_end;

	}

	/*{ Take the difference between hold_in_days and hold_base_date,
	divide by seven, add seven to remainder if negative.}*/

	*out_day = (hold_in_days - hold_base_days) % 7;

	if (*out_day < 0)
	{

		*out_day = *out_day + 7;

	}
func_end:
	return return_status;
}

/*{findhol returns whether the passed date is a holiday according to the passed schedule.

	Usage:  unsigned long findhol(date_union in_date, char holiday_code [],
				char *holiday_result, unsigned int holi_chan,
				holidays_struct holi_parm [])

	where:  in_date =	Input parameter of date_union type which
				contains the date for which the holiday
				check is to be made.

		holiday_code =	Input parameter of type string which contains
				the code of the holiday schedule.

		holiday_result=	Output parameter of type character pointer which
				indicates whether the date is a holiday or not.
				It will be one of the findhol_xxx_hol symbols.

		holi_chan=	input parameter of file channel for holiday
				file.

		holi_parm [] =  input parameter of type holidays_struct array
                		which passes the holiday schedule.

		rule_spec=	Output parameter of type type character pointer
				which indicates whether the result is because of
				a rule or specified.

		return value =  of unsigned long type gives completion status.

    Called by:	<[adj_date]

}*/

unsigned long Date_Funcs::findhol(date_union in_date
			, char holiday_code []
			,char *holiday_result
			, unsigned int holi_chan
			,char *rule_spec
//			, holidays_struct holi_parm []
			, const set<string> &holiSet
			)

{
	*holiday_result = findhol_no_hol;

	char _years[20];
	char _months[20];
	char _days[20];

	_itoa(in_date.date.years,_years,10);
	_itoa(in_date.date.months,_months,10);
	_itoa(in_date.date.days,_days,10);
	string _date(_years);
	_date.append(_months);
	_date.append(_days);

	

	if (holiSet.find(_date) != holiSet.end())
		*holiday_result = findhol_yes_hol;

	return return_success;
/*
	#include "locals.h"
	holidays_struct	holi_buff;
	char const zero_char = 0;
	char h_key[holiday_key_length];
	char month_range_hold[3];
	char day_hold = 0;
	char sought_day = 0;
	char sought_day_instance = 0;
	int str_comp1 = 0;
	int str_comp2 = 0;
	int str_comp3 = 0;
	int incr_days = 0;
	int holiday_array_count = 0;

	date_union work_date_in;
	date_union work_date_out;

//	strcpy(module_name,"findhol");

	memcpy(h_key,holiday_code,holiday_code_length);
	memcpy(&h_key[holiday_code_length],in_date.date_string,date_len);

	*holiday_result = findhol_no_hol;

	//{First search for an exact match.}

	if (holi_parm[0].holi_date.first_date.date.years == io_yes_use)
	{

	  holiday_array_count = -1;

	}
	else
	{

	  holiday_array_count = 0;

	  str_comp1 = 1;

	  while (
		(holiday_array_count <
		  holi_parm[0].holi_date.first_date.date.centuries) &&
		(str_comp1 != 0)  )
	  {


		 holiday_array_count++;

		 str_comp1 = memcmp(holi_parm[holiday_array_count].holi_code,
			h_key, holiday_key_length);

		 if (str_comp1 == 0)
		 {

			if (holi_buff.holi_yes_no != findhol_no_hol)
			{

			  *holiday_result = findhol_yes_hol;

			}
			else
			{

				str_comp1 = 1;

			}

		 }

	  }

	  if (*holiday_result == findhol_yes_hol)
	  {

		 goto func_end;

	  }
	  else
	  {

		 return_status = io_rec_nf;

	  }

	  str_comp1 = 0;
	  holiday_array_count = 0;

	}

	if (return_status == return_success)
	{

	  *rule_spec = findhol_spec;

	  if (holi_buff.holi_yes_no != findhol_no_hol)
	  {

		 *holiday_result = findhol_yes_hol;

	  }

	}
	else
	{
	  if (return_status == io_rec_nf)


	  {

		 *rule_spec = findhol_rule;

		 return_status = return_success;

		 //{If no exact match is found, look for a rule.}

		 memcpy(&h_key[holiday_code_length], &holiday_rule, 2);
		 memcpy(&h_key[holiday_code_length + 1], &zero_char, 3);

		 while ((str_comp1 == 0) && (str_comp2 == 0) &&
		  (*holiday_result == findhol_no_hol) &&
		  (holiday_array_count < holi_parm[0].holi_date.first_date.date.centuries))

		 {

			if (holi_parm[0].holi_date.first_date.date.years == io_yes_use)
			{


			}
			else
			{

				holiday_array_count++;
				memcpy(holi_buff.holi_code,
				holi_parm[holiday_array_count].holi_code,
				holiday_record_length);

			}

			if (return_status == return_success)

			{

				str_comp1 = memcmp(holi_buff.holi_code, holiday_code, holiday_code_length);

				if (str_comp1 == 0)

				{

					str_comp2 = memcmp(&holi_buff.holi_date, &holiday_rule, 1);

					if (str_comp2 == 0)
					{

						switch (holi_buff.holi_date.first_date.date.years)
						{

							case 99:
							{

								//{ Apply rules for passed month and check to see if rules
								//from previous or next months are adjusted into passed month.}

								month_range_hold[1] = in_date.date.months;
								month_range_hold[0] = in_date.date.months - 1;
								if (month_range_hold[0] == 0)
								{

								  month_range_hold[0] = 12;

								}
								month_range_hold[2] = in_date.date.months + 1;
								if (month_range_hold[2] == 13)
								{

								  month_range_hold[2] = 1;

								}

								if ((holi_buff.holi_date.first_date.date.months
									== in_date.date.months)
									||
									(((holi_buff.holi_date.holiday_adj
									!= event_sched_same_holiday_adj)
									&&
									((holi_buff.holi_date.first_date.date.months
									== month_range_hold[0])
									||
									(holi_buff.holi_date.first_date.date.months
									== month_range_hold[2])))))

								{

									datecpy(work_date_in.date_string,
										in_date.date_string);

									work_date_in.date.months =
										holi_buff.holi_date.first_date.date.months;
									work_date_in.date.days =
										holi_buff.holi_date.first_date.date.days;

									//{ First process specific dates.}

									if (holi_buff.holi_date.first_date.date.days < 100)
									{

										return_status = adj_last(&work_date_in);

										if (return_status != return_success)
										{


											goto func_end;

										}

										return_status =
											adj_date(&work_date_in,adj_date_non_to_bus,
												holi_buff.holi_date.holiday_adj,
												adj_date_yes_we,adj_date_no_hol,
												holiday_code, holi_chan, holi_parm);

										if (return_status != return_success)
										{

//											errproc(return_status,module_name,"","","");

											goto func_end;

										}

										str_comp3 = datecmp(work_date_in.date_string,
											in_date.date_string);

										if (str_comp3 == 0)
										{

											*holiday_result = findhol_yes_hol;

										}

									}

									//{ Process day algorithms.}

									else
									{

										datecpy(work_date_out.date_string,
											work_date_in.date_string);
										work_date_out.date.days = 1;

										//{ Get the first day of the month as a base.}

										return_status =
											findday(work_date_out, &day_hold);

										if (return_status != return_success)

										{

											goto func_end;

										}

										//{ Adjust base if this is indicated.}

										if (holi_buff.holi_date.holiday_adj !=
											event_sched_same_holiday_adj)
										{

											sought_day =
												((holi_buff.holi_date.month_day - 100)
												% 10);
											sought_day_instance =
												((holi_buff.holi_date.month_day - 100)
												/ 10);

											incr_days = sought_day - day_hold;

											if (sought_day_instance != 9)
											{

												if (incr_days >= 0)
												{

													sought_day_instance =
														sought_day_instance - 1;

												}

												incr_days =
													incr_days + (sought_day_instance * 7);

												return_status =
													forecast (work_date_out,
														0,
														incr_days,
														date_act_cal,
														&work_date_in);

												if (return_status != return_success)

												{

													goto func_end;

												}

												datecpy(work_date_out.date_string,
													work_date_in.date_string);

											}


											else

												//{ Last instance in month.}

											{
												incr_days = incr_days + 7;

												return_status = forecast (work_date_out,
													0,
													incr_days,
													date_act_cal,
													&work_date_in);

												if (return_status != return_success)

												{

													goto func_end;

												}

												incr_days = 7;

												while
													(work_date_out.date.months ==
														work_date_in.date.months)
												{

													return_status = forecast (work_date_out,
														0,
														incr_days,
														date_act_cal,
														&work_date_in);

													if (return_status != return_success)

													{

														goto func_end;

													}


													if (work_date_in.date.months ==
														work_date_out.date.months)
													{

														datecpy(work_date_out.date_string,
															work_date_in.date_string);

													}

												}
											}
										}
										else
										{

											sought_day = day_hold;

										}

										//{ work_date_out is the base date.}

										//{ Calculate sought date from base date. }

										day_hold = sought_day;

										sought_day =
											((holi_buff.holi_date.first_date.date.days
												- 100)
												% 10);

										sought_day_instance =
											((holi_buff.holi_date.first_date.date.days
												- 100)
												/ 10);

										incr_days = sought_day - day_hold;

										if (sought_day_instance != 9)
										{

											if (incr_days >= 0)
											{

											 sought_day_instance = sought_day_instance - 1;

											}

											incr_days =
												incr_days + (sought_day_instance * 7);

											if (holi_buff.holi_date.holiday_adj ==
												event_sched_prev_holiday_adj)
											{

												incr_days = incr_days * (-1);

											}


											return_status = forecast (work_date_out,
												0,
												incr_days,
												date_act_cal,
												&work_date_in);

											if (return_status != return_success)

											{

												goto func_end;

											}

												datecpy(work_date_out.date_string,
													work_date_in.date_string);

										}
										else

										//{ Last instance in month.}

										{
											incr_days = incr_days + 7;

											return_status = forecast (work_date_out,
												0,
												incr_days,
												date_act_cal,
												&work_date_in);

											if (return_status != return_success)

											{

												goto func_end;

											}

											incr_days = 7;

											while (work_date_out.date.months ==
												work_date_in.date.months)
											{

												if (work_date_in.date.months ==
													work_date_out.date.months)
												{

													datecpy(work_date_out.date_string,
														work_date_in.date_string);

												}

												return_status = forecast (work_date_out,
													0,
													incr_days,
													date_act_cal,
													&work_date_in);

												if (return_status != return_success)

												{

													goto func_end;

												}
											}
										}

										str_comp3 = datecmp(in_date.date_string,
											work_date_out.date_string);

										if (str_comp3 == 0)
										{

											*holiday_result = findhol_yes_hol;

										}

									}

								}

								break;

							}
							default:
							{


								goto func_end;



							}

						}

					}
					else
					{

						if (holi_parm[0].holi_date.first_date.date.years ==
							io_yes_use)
						{

							str_comp3 =
								datecmp(holi_buff.holi_date.first_date.date_string,
									in_date.date_string);

							if (str_comp3 == 0)
							{
								*rule_spec = findhol_spec;

								if (holi_buff.holi_yes_no != findhol_no_hol)
								{

									*holiday_result = findhol_yes_hol;

								}
							}
						}

					}


				}

			}

			else
			{

				if (return_status == io_eof)
				{

					str_comp1 = 1;
					return_status = return_success;

				}
				else
				{


					goto func_end;

				}

			}

			memcpy(&h_key,&holi_buff,holiday_key_length);


		}

	}

}

if (return_status)
{

	  goto func_end;

}
func_end:
return return_status;
*/
}

/* {Forecast returns a final date when passed a base date and the number of
    months and days to add to the base date as well as the calendar
    convention to use.

    Usage:	unsigned long forecast	(date_union base_date,
				int months,
				int days,
				unsigned char cal_type,
				date_union out_date)
    where:	base_date = 	Input parameter of type date_union
				indicating the beginning date for the
				calculation.

		months =	Input parameter of integer type indicating
				the number of months to add to the
				base_date. Positive or negative integers
				are permitted.

		days =		Input parameter of long type indicating
				the number of days to add to the
				base_date. Positive or negative integers
				are permitted.

		cal_type =	input parameter of type char
				indicating the convention used for calendar
				calculations. It must be one of the
				following:

				date_act_cal	= "1", indicating that the
						actual number of days are
						used.

				date_30_cal	= "2", indicating that a
						thirty day month is used,
						with the following rules:

						The number of days between
						D1/M1/Y1 and D2/M2/Y2, where
						if D1 is 31, change to 30.
						if D2 is 31 and D1 is 30 or
						31 change D2 to 30, otherwise
						leave it at 31.

				date_30e_cal	= "3", indicating that a
						thirty day month is used,
						with the following rules:

						if D1 is 31, change to 30.
						if D2 is 31, change to 30.

		out_date = 	output parameter of type
				date_union which is the result of adding
				the indicated months and days to base_date.

		return value =  unsigned long indicating completion status.

	 Calls:	>[date_to_days]

	 }
*/

unsigned long Date_Funcs::forecast	(date_union base_date,
			int months,
			long days,
			char cal_type,
			date_union *out_date)

{

	#include "locals.h"

	int	centuries_hold = 0;
	int	years_hold = 0;
	int	months_hold = 0;
	long	days_hold = 0;

	long	days_year	= 0; /*{days_year holds the number of days from the difference in years. Only used for date$30$cal and date$30e$cal.}*/
	long	days_month	= 0; /*{days_year holds the number of days from the difference in months. Only used for date$30$cal and date$30e$cal.}*/
	long	days_day	= 0; /*{days_year holds the number of days from the difference in days. Only used for date$30$cal and date$30e$cal.}*/
	long	base_date_days	= 0; /*{start_date_days holds the number of days in start_date.}*/
	long	out_date_days 	= 0; /*{end_date_days holds the number of days in end_date.}*/

	date_union temp_date;

//	strcpy(module_name,"forecast");

	/*{ Assume out_date = base_date.}*/

	datecpy(out_date->date_string, base_date.date_string);

	/*{ Either months or days may be passed, but not both.}*/

	if ((months != 0) && (days != 0))
	{

		return_status = return_error;
		goto func_end;
	}

	/*{ If neither months nor days are passed, out_date = base_date.}*/

	if ((months == 0) && (days == 0))
	{

		goto func_end;
	}

	if (months != 0)
	{

		month_add(*out_date,months,&temp_date);

		datecpy(out_date->date_string, temp_date.date_string);

	}

	/*{ Make sure day does not exceed last date of month, by calling adj_last}*/

	return_status = adj_last	(out_date);

	if (return_status != return_success)
	{


		goto func_end;
	}

	/*{ Add days to intermediate date according to calendar convention. }*/

	if (days != 0)
	{

	  switch (cal_type)
	  {

			case date_act_cal: /*{ For actual, add real number of days to base_date.}*/
			{

				centuries_hold = out_date->date.centuries;
				years_hold = out_date->date.years;
				months_hold = out_date->date.months;
				days_hold = out_date->date.days;

				/*{Add days to out_date.date.days.}*/

				days_hold = days_hold + days;

				datecpy(temp_date.date_string, out_date->date_string);

				while ((days_hold > month_end(temp_date)) ||
					(days_hold < 1))
				{

					if (days_hold < 1)
					{

						months_hold--;

						if (months_hold < 1)
						{

							years_hold--;
							temp_date.date.years = years_hold;
							months_hold = 12;

							if (years_hold < 0)
							{

								years_hold = 99;
								centuries_hold--;
								temp_date.date.centuries = centuries_hold;
							} /* out_date.date.years < 0 */
						}   /* out_date.date.months < 1 */

						temp_date.date.months = months_hold;

						days_hold = days_hold + month_end(temp_date);

					} /* out_date.date.days < 1 */

					else
					{ /* Days greater than month days. */

						temp_date.date.months = months_hold;

						days_hold = days_hold - month_end(temp_date);

						months_hold++;

						if (months_hold > 12)
						{

							years_hold++;
							temp_date.date.years = years_hold;
							months_hold = 1;

							if (years_hold == 100)
							{

								years_hold = 0;
								centuries_hold++;
								temp_date.date.years = years_hold;
								temp_date.date.centuries = centuries_hold;
							}  /* out_date.date.years is 100. */
						}   /* out_date.date.months more than 12. */
					} /* days greater than month days. */

					temp_date.date.months = months_hold;

					datecpy(out_date->date_string, temp_date.date_string);

				} /* while still adding. */
				break;

			} /* Actual days */

			case date_30_cal:
			case date_30e_cal: /* {30 and 30e are almost identical.} */
			{

				/*{ Every 30 days constitutes a month. }*/

				month_add(*out_date, days/30 ,&temp_date);

				datecpy(out_date->date_string, temp_date.date_string);

				centuries_hold = out_date->date.centuries;
				years_hold = out_date->date.years;
				months_hold = out_date->date.months;
				days_hold = out_date->date.days;

				/*{ Add remaining days. }*/

				days_hold = days_hold + days%30;

				/*{ If a month end has been passed, adjust date. }*/

				if (days_hold > 30)
				{

					months_hold++;
					days_hold = days_hold - 30;

					/*{ If year end passed, adjust date.}*/

					if (months_hold > 12)
					{

						months_hold = months_hold%12;
							years_hold++;

						/*{ If century end is passed, adjust date.}*/

						if (years_hold > 99)
						{

							years_hold = years_hold%100;
							centuries_hold++;

						} /* Century end passed. */
					}  /* Year end passed.*/
				}  /* Month end passed. */

				/*{ If gone backwards a month, adjust date.}*/

				if (days_hold < 1)
				{

					months_hold--;

					/*{ If gone backwards a year, adjust date.}*/

					if (months_hold < 1)
					{

						months_hold = 12;
						years_hold--;

						/*{ If gone backwards a century, adjust date.}*/

						if (years_hold < 100)
						{

							centuries_hold--;
						} /* Backwards a century.*/
					} /* Backwards a year.*/

					/*{ If days end up zero, then push to last day
						of previos month.}*/

					if (days_hold == 0)
					{

						out_date->date.months = months_hold;

						days_hold = month_end(*out_date);

					}  /* Days are zero. */

					/*{ If days are less than zero,
						find days in previous month.}*/

					else
					{

						days_hold = days_hold + 30;

					} /* Days less than zero.*/
				} /* Gone back a month.*/

				/*{ Make sure last day of month is not exceeded.}*/

				out_date->date.centuries = centuries_hold;
				out_date->date.years = years_hold;
				out_date->date.months = months_hold;
				out_date->date.days = (char)days_hold;

				return_status = adj_last(out_date);

				if (return_status != return_success)
				{

					goto func_end;
				}

				centuries_hold = out_date->date.centuries;
				years_hold = out_date->date.years;
				months_hold = out_date->date.months;
				days_hold = out_date->date.days;

				/*{ For 30e method, never end on the 31st. }*/

				if ((days_hold == 31)  && (cal_type == date_30e_cal))
				{

					days_hold = 30;

				} /* 30e adjustment from 31. */
				break;

			} /* 30 day months */
			default:
			{

				return_status = return_err_inv_day_count;
				goto func_end;

			}
		} /* cal_type switch */

		out_date->date.centuries = centuries_hold;
		out_date->date.years = years_hold;
		out_date->date.months = months_hold;
		out_date->date.days = (char)days_hold;

	} /* days Processing */

func_end:

	return return_status;
}

/* {Month Add increments a date by the number of months passed.

	 Usage:	void month_add	(date_union in_date,
				int months,
				date_union *out_date)

	 where:	in_date = 	Input parameter of type date_union
				indicating the beginning date for the
				calculation.

		months =	Input parameter of integer type indicating
				the number of months to add to the
				base_date. Positive or negative integers
				are permitted.

		out_date = 	output parameter which is a pointer to
				type date_union which is the
				result of adding the indicated months to
				base_date.

	 }
*/

void Date_Funcs::month_add(date_union in_date, int months, date_union *out_date)
{

int month_hold = 0;
int month_hold2 = 0;
int year_hold = 0;

	/*{ Set out_date to in_date.}*/

	datecpy(out_date->date_string, in_date.date_string);

	/*{ Add months to base_date. }*/

	months = months + out_date->date.months;
	//out_date->date.months = out_date->date.months + months;

	/*{ Keep months below thirteen }*/

	if (months <= 0)
	{

	  out_date->date.months = 12 + (months % 12);
	  month_hold = (months % 12);
	  month_hold2 = (months / 12);

	  if ((month_hold != 0) || (month_hold2 < 1))
	  {

				 year_hold = year_hold - 1;

	  }


	}

	else

	{

	  out_date->date.months = (months % 12);

	}
	/*{ Divide resulting months by 12 to determine whole years.}*/

	year_hold = year_hold + out_date->date.years + ((months)/12);

	if (year_hold < 0)
	{

	  out_date->date.centuries =
	  out_date->date.centuries + ((year_hold)/100) - 1;

	  out_date->date.years = 100 + (year_hold%100);

	}

	else
	{

	  out_date->date.years = year_hold;

	}


	/*{ If months are now negative or zero.}*/

	if (out_date->date.months <= 0)
	{

		out_date->date.months = 12 + out_date->date.months;
		/*{ Reduce years by 1}*/
		out_date->date.years = out_date->date.years - 1;
	}

	/*{ Divide resulting years by 100 to determine centuries.}*/

	out_date->date.centuries = out_date->date.centuries +
		(out_date->date.years/100);

	/*{ Keep years below 100. }*/

	out_date->date.years = out_date->date.years % 100;

	return;

}

unsigned long Date_Funcs::holiload(holidays_struct holi_parm [], char mem_alloc)
{

#include "locals.h"

int str_cmp = 0;
/*
	holi_parm[0].holi_date.first_date.date.centuries = 0;
	holi_parm[0].holi_date.first_date.date.years = io_no_use;

goto func_end;
*/
/*
	str_cmp = memcmp(holi_parm[0].holi_code,"xxx",3);


	if (str_cmp == 0)
		  {

	   if (mem_alloc == mem_alloc_yes)
           {
		holi_parm[0].holi_date.first_date.date.centuries = 2;
		memcpy(holi_parm[0].holi_code,"xxx",3);

		memcpy (holi_parm[1].holi_code,holi_parm[0].holi_code,3);
		holi_parm[1].holi_date.first_date.date.centuries = 99 ;
		holi_parm[1].holi_date.first_date.date.years = 99 ;
		holi_parm[1].holi_date.first_date.date.months = 8 ;
		holi_parm[1].holi_date.first_date.date.days = 191 ;
		holi_parm[1].holi_date.first_date.date.null = 0 ;
		strcpy(holi_parm[1].holi_name," August Bank Holiday");
		holi_parm[1].null = 0;
		holi_parm[1].holi_yes_no = findhol_yes_hol;
		holi_parm[1].holi_date.holiday_adj = event_sched_same_holiday_adj;

		memcpy (holi_parm[2].holi_code,holi_parm[0].holi_code,3);
		holi_parm[2].holi_date.first_date.date.centuries = 19 ;
		holi_parm[2].holi_date.first_date.date.years = 95 ;
		holi_parm[2].holi_date.first_date.date.months = 9 ;
		holi_parm[2].holi_date.first_date.date.days = 4 ;
		holi_parm[2].holi_date.first_date.date.null = 0 ;
		strcpy(holi_parm[2].holi_name," Labor Day");
		holi_parm[2].null = 0;
		holi_parm[2].holi_yes_no = findhol_yes_hol;
		holi_parm[2].holi_date.holiday_adj = event_sched_same_holiday_adj;
	   }
	   else
		{

	     delete [] holi_parm;

           }

	}

	str_cmp = memcmp(holi_parm[0].holi_code,"USD",3);


	if (str_cmp == 0)
		  {

		if (mem_alloc == mem_alloc_yes)
		{
		holi_parm[0].holi_date.first_date.date.centuries = 2;
		memcpy(holi_parm[0].holi_code,"USD",3);

		memcpy (holi_parm[1].holi_code,holi_parm[0].holi_code,3);
		holi_parm[1].holi_date.first_date.date.centuries = 99 ;
		holi_parm[1].holi_date.first_date.date.years = 99 ;
		holi_parm[1].holi_date.first_date.date.months = 11 ;
		holi_parm[1].holi_date.first_date.date.days = 191 ;
		holi_parm[1].holi_date.first_date.date.null = 0 ;
		strcpy(holi_parm[1].holi_name," November Holiday");
		holi_parm[1].null = 0;
		holi_parm[1].holi_yes_no = findhol_yes_hol;
		holi_parm[1].holi_date.holiday_adj = event_sched_same_holiday_adj;

		memcpy (holi_parm[2].holi_code,holi_parm[0].holi_code,3);
		holi_parm[2].holi_date.first_date.date.centuries = 19 ;
		holi_parm[2].holi_date.first_date.date.years = 95 ;
		holi_parm[2].holi_date.first_date.date.months = 9 ;
		holi_parm[2].holi_date.first_date.date.days = 4 ;
		holi_parm[2].holi_date.first_date.date.null = 0 ;
		strcpy(holi_parm[2].holi_name," Labor Day");
		holi_parm[2].null = 0;
		holi_parm[2].holi_yes_no = findhol_yes_hol;
		holi_parm[2].holi_date.holiday_adj = event_sched_same_holiday_adj;
	   }
	   else
	   {

	     delete [] holi_parm;

           }

	}


//func_end:
*/
return return_status;
}

/*{month_end returns the number of days in the month of the date passed.

	Usage:  int month_end(date_union in_date)

	where:  in_date	=	input parameter of date_union type, which is
				the date for which the last day of the month
				is to be found.

		return value =  of int type is the number of days in the month
				in in_date.

    Called by:	<[days_to_date]

}*/

int Date_Funcs::month_end(date_union in_date)

{
	#include "locals.h"
	int	month_days = 0;
	int	actual_year = 0;


//	strcpy(module_name,"month_end");

	  switch (in_date.date.months)
	  {
		 case 1:
		 {
			month_days = 31;
			break;
		 }
		 case 2:
		 {
			month_days = 28;

			actual_year = (in_date.date.centuries*100) +
			in_date.date.years;

			/*{If this is a leap year, add an extra day.}*/

			if ((actual_year)%4==0)
			{
				if  (!((actual_year % 400 != 0) &&
				(actual_year % 100 == 0)))
				{
					month_days++;
				}
			}
			break;
		 }
		 case 3:
		 {
			month_days = 31;
			break;
		 }
		 case 4:
		 {
			month_days = 30;
			break;
		 }
		 case 5:
		 {
			month_days = 31;
			break;
		 }
		 case 6:
		 {
			month_days = 30;
			break;
		 }
		 case 7:
		 {
			month_days = 31;
			break;
		 }
		 case 8:
		 {
			month_days = 31;
			break;
		 }
		 case 9:
		 {
			month_days = 30;
			break;
		 }
		 case 10:
		 {
			month_days = 31;
			break;
		 }
		 case 11:
		 {
			month_days = 30;
			break;
		 }
		 case 12:
		 {
			month_days = 31;
			break;
		 }
	  }

	  return month_days;
}

/* {Tenor returns the number of days between any two dates,
    altering the calculation depending on the convention indicated.

    Usage:	unsigned long tenor	(date_union start_date,
					date_union end_date,
					unsigned char cal_type,
				int tenor_days)
    where:	start_date = 	input parameter of type date_union
				indicating the beginning date for the
				calculation.
		end_date = 	input parameter of type date_union
				indicating the ending date for the
				calculation.
		cal_type =	input parameter of type char
				indicating the convention used for calendar
				calculations. It must be one of the
				following:

				date_act_cal	= "1", indicating that the
						actual number of days are
						used.

				date_30_cal	= "2", indicating that a
						thirty day month is used,
						with the following rules:

						The number of days between
						D1/M1/Y1 and D2/M2/Y2, where
						if D1 is 31, change to 30.
						if D2 is 31 and D1 is 30 or
						31 change D2 to 30, otherwise
						leave it at 31.

				date$30e$cal	= "3", indicating that a
						thirty day month is used,
						with the following rules:

						if D1 is 31, change to 30.
						if D2 is 31, change to 30.
		tenor_days =	output parameter of type integer giving the
				resulting number of days.

		return value =  unsigned long indicating completion status.

    Calls:	>[date_to_days]

    }
*/

unsigned long Date_Funcs::tenor	(date_union start_date,
			date_union end_date,
			char cal_type,
			long *tenor_days)
{
	#include "locals.h"

	char	days_sign	= 1; /*{days_sign determines whether days is negative or not. }*/

	long	days_year	= 0; /*{days_year holds the number of days from the difference in years. Only used for date$30$cal and date$30e$cal.}*/
	long	days_month	= 0; /*{days_year holds the number of days from the difference in months. Only used for date$30$cal and date$30e$cal.}*/
	long	days_day	= 0; /*{days_year holds the number of days from the difference in days. Only used for date$30$cal and date$30e$cal.}*/
	long	start_date_days = 0; /*{start_date_days holds the number of days in start_date.}*/
	long	end_date_days 	= 0; /*{end_date_days holds the number of days in end_date.}*/

	date_union hold_date;	     /*{hold_date is used for swapping dates. }*/

	/* {First the dates are converted to total days, calling date_to_days} */

	return_status = date_to_days 	(start_date,
					&start_date_days);

	return_status = date_to_days 	(end_date,
					&end_date_days);


	/*{Calculate actual days, which is simply the difference in real days.}*/

	*tenor_days = end_date_days - start_date_days;

	/*{set days_sign to -1 if tenor_days is less than zero. }*/

	if (*tenor_days < 0)
		{days_sign = -1;

		/*{ swap dates so that start date is always before end date.}*/

		datecpy(hold_date.date_string,end_date.date_string);
		datecpy(end_date.date_string,start_date.date_string);
		datecpy(start_date.date_string,hold_date.date_string);

		}

	switch (cal_type)
	  {

		 case date_30_cal:
		 case date_30e_cal: /* {30 and 30e are almost identical.} */

		 {
			/* {Calculate the number of days difference between the two year components.} */

			days_year = ((end_date.date.centuries - start_date.date.centuries)*100 +
				 (end_date.date.years - start_date.date.years))*360;

			/* {Calculate the number of days difference between the two month components.} */

			days_month = (end_date.date.months - start_date.date.months)*30;

			/* { Adjust days according to convention.} */

			if (start_date.date.days == 31)
			{
				start_date.date.days = 30;
			}

			if (end_date.date.days == 31)
			{

				if (cal_type == date_30e_cal)
				{

					end_date.date.days = 30;
				}

				else
				{

					if (start_date.date.days == 30)
					{
						end_date.date.days = 30;
					}
				}
			}

			/* {Calculate the number of days difference between the two day components.} */

			days_day = (end_date.date.days - start_date.date.days);

			*tenor_days = (days_year + days_month + days_day)*days_sign;
		 }

	  }

	return return_status;
}

#ifndef _ANSIC

unsigned long Date_Funcs::GetMonth(int number_parm,
	char month_parm[month_names_length])
{
	unsigned long return_state;

	return_state = return_success;
	strcpy(month_parm,month_names[number_parm]);
	return return_state;

}
unsigned long Date_Funcs::CheckMonth(int number_parm)
{
	unsigned long return_state;

	return_state = return_success;
	if ((number_parm < month_january_number) || (number_parm >
		month_december_number))
	{
	  return_state = return_err_invalid_month;
	}
	return return_state;

}
unsigned long Date_Funcs::CheckYear(unsigned int base_year)
{
	unsigned long return_state;

 if ((base_year < 1) || (base_year > 9999))
 {

	return_state = return_err_base_year_invalid;
	goto func_end;

 }
 else
 {

	return_state = return_success;

 }
func_end:
	return return_state;

}
unsigned long Date_Funcs::CheckMonthDay(unsigned int base_day)
{
unsigned long return_state;

 if ((base_day < 1) || (base_day > 31))
 {

	return_state = return_err_base_day_invalid;
	goto func_end;

 }
 else
 {

	return_state = return_success;

 }
func_end:
	return return_state;

}
unsigned long Date_Funcs::CheckWeekday(unsigned int base_day)
{
unsigned long return_state;

 if ((base_day < date_sun_day) || (base_day > date_satur_day))
 {

	return_state = return_err_weekday_invalid;
	goto func_end;

 }
 else
 {

	return_state = return_success;

 }
func_end:
	return return_state;

}
#endif

