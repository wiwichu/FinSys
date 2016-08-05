#if defined (WIN32)
	#define _HUGE_
#else
	#define _HUGE_ __huge
#endif

#ifndef __datedec_H
#define __datedec_H
//#ifdef _ANSIC
//#define _DATEFUNCS
//#else
//#define _DATEFUNCS Date_Funcs::
//#endif

#include "stdafx.h"
#include "calc.h"
#include <string>
#include <set>
#include "wordsymb.h"

//#include "iokeys.h"
//#include "convutil.h"
//#include "db.h"

using namespace std;

const	int	date_string_size	= 11;
const	unsigned char	date_format_1 = 0;
const	unsigned char	dateconv_string_to_union = 0;
const	unsigned char	dateconv_union_to_string = 1;
const	unsigned char	dateconv_double_to_union = 2;
const	unsigned char	dateconv_union_to_double = 3;
char *const	date_format_1_separator = "/";


const	unsigned char    date_sun_day = 0;
const	unsigned char    date_mon_day = 1;
const	unsigned char    date_tues_day = 2;
const	unsigned char    date_wednes_day = 3;
const	unsigned char    date_thurs_day = 4;
const	unsigned char    date_fri_day = 5;
const	unsigned char    date_satur_day = 6;
const	unsigned char    date_days = 7;

const	unsigned char    date_1sun_day = 110;    /*{date_1sun_day means the first sunday of the month.}*/
const	unsigned char    date_1mon_day = 111;    /*{date_1mon_day means the first monday of the month.}*/
const	unsigned char    date_1tues_day = 112;   /*{date_1tues_day means the first tuesday of the month.}*/
const	unsigned char    date_1wednes_day = 113; /*{date_1wednes_day means the first wednesday of the month.}*/
const	unsigned char    date_1thurs_day = 114;  /*{date_1thurs_day means the first thursday of the month.}*/
const	unsigned char    date_1fri_day = 115;    /*{date_1fri_day means the first friday of the month.}*/
const	unsigned char    date_1satur_day = 116;  /*{date_1satur_day means the first saturday of the month.}*/

const	unsigned char    date_2sun_day = 120;    /*{date_2sun_day means the second sunday of the month.}*/
const	unsigned char    date_2mon_day = 121;    /*{date_2mon_day means the second monday of the month.}*/
const	unsigned char    date_2tues_day = 122;   /*{date_2tues_day means the second tuesday of the month.}*/
const	unsigned char    date_2wednes_day = 123; /*{date_2wednes_day means the second wednesday of the month.}*/
const	unsigned char    date_2thurs_day = 124;  /*{date_2thurs_day means the second thursday of the month.}*/
const	unsigned char    date_2fri_day = 125;    /*{date_2fri_day means the second friday of the month.}*/
const	unsigned char    date_2satur_day = 126;  /*{date_2satur_day means the second saturday of the month.}*/

const	unsigned char    date_3sun_day = 130;    /*{date_3sun_day means the third sunday of the month.}*/
const	unsigned char    date_3mon_day = 131;    /*{date_3mon_day means the third monday of the month.}*/
const	unsigned char    date_3tues_day = 132;   /*{date_3tues_day means the third tuesday of the month.}*/
const	unsigned char    date_3wednes_day = 133; /*{date_3wednes_day means the third wednesday of the month.}*/
const	unsigned char    date_3thurs_day = 134;  /*{date_3thurs_day means the third thursday of the month.}*/
const	unsigned char    date_3fri_day = 135;    /*{date_3fri_day means the third friday of the month.}*/
const	unsigned char    date_3satur_day = 136;  /*{date_3satur_day means the third saturday of the month.}*/

const	unsigned char    date_4sun_day = 140;    /*{date_4sun_day means the fourth sunday of the month.}*/
const	unsigned char    date_4mon_day = 141;    /*{date_4mon_day means the fourth monday of the month.}*/
const	unsigned char    date_4tues_day = 142;   /*{date_4tues_day means the fourth tuesday of the month.}*/
const	unsigned char    date_4wednes_day = 143; /*{date_4wednes_day means the fourth wednesday of the month.}*/
const	unsigned char    date_4thurs_day = 144;  /*{date_4thurs_day means the fourth thursday of the month.}*/
const	unsigned char    date_4fri_day = 145;    /*{date_4fri_day means the fourth friday of the month.}*/
const	unsigned char    date_4satur_day = 146;  /*{date_4satur_day means the fourth saturday of the month.}*/

const	unsigned char    date_5sun_day = 150;    /*{date_5sun_day means the fifth sunday of the month.}*/
const	unsigned char    date_5mon_day = 151;    /*{date_5mon_day means the fifth monday of the month.}*/
const	unsigned char    date_5tues_day = 152;   /*{date_5tues_day means the fifth tuesday of the month.}*/
const	unsigned char    date_5wednes_day = 153; /*{date_5wednes_day means the fifth wednesday of the month.}*/
const	unsigned char    date_5thurs_day = 154;  /*{date_5thurs_day means the fifth thursday of the month.}*/
const	unsigned char    date_5fri_day = 155;    /*{date_5fri_day means the fifth friday of the month.}*/
const	unsigned char    date_5satur_day = 156;  /*{date_5satur_day means the fifth saturday of the month.}*/

const	unsigned char    date_9sun_day = 190;    /*{date_9sun_day means the last sunday of the month.}*/
const	unsigned char    date_9mon_day = 191;    /*{date_9mon_day means the last monday of the month.}*/
const	unsigned char    date_9tues_day = 192;   /*{date_9tues_day means the last tuesday of the month.}*/
const	unsigned char    date_9wednes_day = 193; /*{date_9wednes_day means the last wednesday of the month.}*/
const	unsigned char    date_9thurs_day = 194;  /*{date_9thurs_day means the last thursday of the month.}*/
const	unsigned char    date_9fri_day = 195;    /*{date_9fri_day means the last friday of the month.}*/
const	unsigned char    date_9satur_day = 196;  /*{date_9satur_day means the last saturday of the month.}*/

const	unsigned char	date_last_day_in_month = 99; /*{ date_last_day_in_month indicates the last day in the month.}*/

const	unsigned char	date_30e_360_day_count	= 0;
const	unsigned char	date_30_360_day_count	= 1;
const	unsigned char	date_act_360_day_count	= 2;
const	unsigned char	date_act_365_day_count	= 3;
const	unsigned char	date_act_365cd_day_count = 4;
const	unsigned char	date_act_act_day_count	= 5;
const	unsigned char	date_act_366_day_count	= 6;
const	unsigned char	date_last_day_count	= 7;

		 

char *const	date_30e_360_day_count_name	= "30E/360";
char *const	date_30_360_day_count_name	= "30/360";
char *const date_act_360_day_count_name	= "ACT/360";
char *const	date_act_365_day_count_name	= "ACT/365";
char *const	date_act_365cd_day_count_name = "ACT/365CD";
char *const	date_act_act_day_count_name	= "ACT/ACT";
char *const	date_act_366_day_count_name	= "ACT/366";

const	unsigned char    date_no_cal = 0;
const	unsigned char    date_act_cal = 1;
const	unsigned char	date_30_cal  = 2;
const	unsigned char	date_30e_cal = 3;
const	unsigned char	date_365_cal = 4;
const	unsigned char	date_366_cal = 5;
const	unsigned char	date_365_25_cal = 6;

const	unsigned day_counts[date_last_day_count] =
		{
		date_30e_360_day_count
		,date_30_360_day_count
		,date_act_360_day_count
		,date_act_365_day_count
		,date_act_365cd_day_count
		,date_act_act_day_count
		,date_act_366_day_count
		};

char *const day_count_names[date_last_day_count] =
//		 {"30E/360","30/360","ACT/360","ACT/365","ACT/365CD","ACT/ACT","ACT/366"};
		{
		date_30e_360_day_count_name
		,date_30_360_day_count_name
		,date_act_360_day_count_name
		,date_act_365_day_count_name
		,date_act_365cd_day_count_name
		,date_act_act_day_count_name
		,date_act_366_day_count_name
		};
char const  day_count_nums[date_last_day_count] =
			 {date_30e_cal,date_30_cal,date_act_cal,date_act_cal,
			date_act_cal,date_act_cal,date_act_cal};
char const  day_count_dens[date_last_day_count] =
			 {date_30_cal,date_30_cal,date_30_cal,date_365_cal,
			date_365_cal,date_act_cal,date_366_cal};

const	int	day_count_names_len = 10;
const	int	date_len = 5;

char const zero_date[5] = {0,0,0,0,0};

const	unsigned char	event_sched_day_period		= 1;
/*{ event_sched_day_period means the periodicity is indicated in number of
days.}*/
const	unsigned char	event_sched_month_period	= 2;
/*{ event_sched_month_period means the periodicity is indicated in number
of months.}*/
const	unsigned char	event_sched_end_period		= 3;
/*{ event_sched_end_period means the periodicity is at the end (maturity).
For rate frequency (and compounding), this means it changes at every coupon
(rate change).}*/
const	unsigned char	event_sched_free_period		= 4;
/*{ event_sched_free_period means the periodicity is open.
For compounding, this means simple interest (no compounding).}*/
const	unsigned char	event_sched_cont_period		= 5;
/*{ event_sched_cont_period is only applicable for compounding,
and means continuous compounding.}*/

const	unsigned char	event_sched_march_holiday_adj	= 0;
/*{ event_sched_march_holiday_adj means the next business day is taken,
and then becomes the new base for the next calculation, causing the day to
march forward from month to month. It will never go into the next month
however, but stay on the last business date once that is reached.}*/
const	unsigned char	event_sched_next_holiday_adj	= 1;
/*{ event_sched_next_holiday_adj means the next business day is taken.}*/
const	unsigned char	event_sched_np_holiday_adj	= 2;
/*{ event_sched_np_holiday_adj means the next business day is taken,
but if this is in a different month, the previous business day is taken.}*/
const	unsigned char	event_sched_prev_holiday_adj	= 3;
/*{ event_sched_prev_holiday_adj means the previous business day is taken.}*/
const	unsigned char	event_sched_pn_holiday_adj	= 4;
/*{ event_sched_pn_holiday_adj means the previous business day is taken,
but if this is in a different month, the next business day is taken.}*/
const	unsigned char	event_sched_same_holiday_adj	= 5;
/*{ event_sched_same_holiday_adj means that no adjustment occurs.}*/
const	unsigned char	event_sched_last_holiday_adj	= 6;
/*{ event_sched_last_holiday_adj means total symbols.}*/
const	unsigned char	event_sched_nearIMM_holiday_adj	= 10;
/*{ event_sched_nearIMM_holiday_adj means the nearest IMM;
	first Monday after second Wednesday of March, June, September, December
	(if next and previous are equidistant, next is taken).}*/
const	unsigned char	event_sched_nextIMM_holiday_adj	= 11;
/*{ event_sched_nextIMM_holiday_adj means the next IMM. 
	If passed date is an exact match, next date is taken}*/
const	unsigned char	event_sched_prevIMM_holiday_adj	= 12;
/*{ event_sched_prevIMM_holiday_adj means the previous IMM.
	If passed date is an exact match, it is taken.}*/
const	unsigned char	event_sched_no_holiday_adj	= 99;
/*{ event_sched_no_holiday_adj means that no adjustment is specified.}*/
//
char *const	event_sched_next_holiday_adj_name = "Next";
char *const	event_sched_same_holiday_adj_name = "Same";
char *const	event_sched_prev_holiday_adj_name = "Previous";
//char *const	event_sched_np_holiday_adj_name = "Next-Previous";
char *const	event_sched_np_holiday_adj_name = "NextinMonth";
char *const	event_sched_pn_holiday_adj_name = "Previous-Next";
char *const	event_sched_march_holiday_adj_name = "Marching";
char *const	event_sched_nearIMM_holiday_adj_name = "NearIMM";
char *const	event_sched_nextIMM_holiday_adj_name = "NextIMM";
char *const	event_sched_prevIMM_holiday_adj_name = "PrevIMM";
//

const int holiday_adj_count = 6;
const int holiday_adj_names_len = 14;

char *const holiday_adj_names[event_sched_last_holiday_adj] =
				{
				event_sched_march_holiday_adj_name
				,event_sched_next_holiday_adj_name
				,event_sched_np_holiday_adj_name
				,event_sched_prev_holiday_adj_name
				,event_sched_pn_holiday_adj_name
				,event_sched_same_holiday_adj_name
/*
				"Marching"
				,"Next"
//				,"Next-Previous"
				,"NextinMonth"
				,"Previous"
				,"Previous-Next"
				,"Same"
*/
				};

const int freq_count = 4;
const int freq_names_len = 14;

const char frequency_annually = 12;
const char frequency_monthly = 1;
const char frequency_quarterly = 3;
const char frequency_semiannually = 6;

const char frequency_list[freq_count] =
	{
		frequency_annually
		,frequency_monthly
		,frequency_quarterly
		,frequency_semiannually
	};

char *const frequency_annually_name = "Annually";
char *const frequency_monthly_name = "Monthly";
char *const frequency_quarterly_name = "Quarterly";
char *const frequency_semiannually_name = "Semi-Annually";

char *const freq_names[freq_count] = {
	frequency_annually_name
	,frequency_monthly_name
	,frequency_quarterly_name
	,frequency_semiannually_name
};

const int simp_comp_simple = 0;
const int simp_comp_compound = 1;

const int simp_comp_count = 2;
const int simp_comp_names_len = 9;

char *const simp_comp_names[simp_comp_count] = {"Simple","Compound"};

const char monthend_yes = 0;
const char monthend_no = 1;
const int monthend_count = 2;

const char monthends[monthend_count] = {monthend_yes,monthend_no};

const int monthend_names_len = 4;

char *const	monthend_yes_name = "Yes";
char *const	monthend_no_name = "No";

char *const monthend_names[monthend_count] = {monthend_yes_name,monthend_no_name};

/*{ ex_coup_xxx is used to indicate whether a date is ex-coupon.}*/

const	unsigned char	ex_coup_no	= 0;
/*{ ex_coup_no means the date is not ex-coupon.}*/
const	unsigned char	ex_coup_yes	= 1;
/*{ ex_coup_yes means the date is ex-coupon.}*/
const	unsigned char	ex_coup_auto	= 2;
/*{ ex_coup_auto means it must be determined whether the date is ex-coupon.}*/

const int excoup_count = 2;
const int excoup_names_len = 4;

char *const excoup_names[excoup_count] = {"No","Yes"};

/*{ constants and declaration for the adj_date function.}*/

const	char	adj_date_non_to_bus = 1; /*{ adj_date_non_to_bus indicates that the function adj_date will adjust the passed date from a non business day to a business day.}*/
const	char	adj_date_bus_to_non = -1; /*{ adj_date_non_to_bus indicates that the function adj_date will adjust the passed date from a business day to a non business day.}*/
const	char	adj_date_yes_we = 1; 	 /*{ adj_date_yes_we indicates that the function adj_date will adjust for a weekend.}*/
const	char	adj_date_no_we = 2; 	 /*{ adj_date_no_we indicates that the function adj_date will not adjust for a weekend.}*/
const	char	adj_date_yes_hol = 1; 	 /*{ adj_date_yes_hol indicates that the function adj_date will adjust for a holiday.}*/
const	char	adj_date_no_hol = 2; 	 /*{ adj_date_no_hol indicates that the function adj_date will not adjust for a holiday.}*/

const	unsigned char	mem_alloc_yes = 0;
const	unsigned char	mem_alloc_no = 1;

const	unsigned char	holi_action_start	= 0;
/*{holi_action_start indicates the start of processing.}*/

const	unsigned char	holi_action_init_screen	= 1;
/*{holi_action_init_screen indicates the initiation of the holiday maintenance screen.}*/

const	unsigned char	holi_action_ver_all	= 2;
/*{holi_action_ver_all indicates all the input should be verified.}*/

const	unsigned char	holi_action_find_holi_rec	= 3;
/*{holi_action_find_holi_rec indicates the holiday record should be found.}*/

const	unsigned char	holi_action_code_val	= 4;
/*{holi_action_code_val indicates the holiday code should be validated.}*/

const	unsigned char	holi_action_rule_or_spec	= 5;
/*{holi_action_rule_or_spec indicates the holiday rule/spec indicator
should be validated.}*/

const	unsigned char	holi_action_rule_val	= 6;
/*{holi_action_rule_val indicates the holiday rule should be validated.}*/

const	unsigned char	holi_action_spec_date	= 7;
/*{holi_action_spec_date indicates the specified holiday date should be
validated.}*/

const	unsigned char	holi_action_end	= 99;
/*{holi_action_end indicates the end of processing.}*/

/*{ constants and declaration for the findhol function.}*/

const	unsigned char	findhol_yes_hol = 1; /*{ findhol_yes_hol indicates that the date is a holiday.}*/
const	unsigned char	findhol_no_hol = 2; /*{ findhol_no_hol indicates that the date is not a holiday.}*/

const	unsigned char	findhol_rule = 1; /*{ findhol_rule indicates that the holiday is determined by rule.}*/
const	unsigned char	findhol_spec = 2; /*{ findhol_spec indicates that the holiday is determined by specification.}*/

const	unsigned char	fra_holiday_usd = 0;
/*{fra_holiday_usd means USD.}*/

const	unsigned char	fra_holiday_dem = 1;
/*{fra_holiday_dem means DEM.}*/

const	unsigned char	fra_holiday_gbp = 2;
/*{fra_holiday_gbp means GBP.}*/

const	unsigned char	fra_holiday_jpy = 3;
/*{fra_holiday_jpy means JPY.}*/

const	unsigned char	fra_last_holiday = 4;
/*{fra_last_holiday means the last holiday possibility.}*/

char *const fra_holiday_names[fra_last_holiday] =
		 {"USD","DEM","GBP","JPY"};

//const	int	fra_holiday_names_len = holidaycodelength;

const unsigned int holiday_record_length = 94;
/*
static unsigned int holi_keys[4] = {
	// First Integer is the record length. 
	holiday_record_length,
	// set up second integer as key definition. 
	key_0 		// This is key 0 
	|keys_1		// There is one key. 
	|segment_2	// There are two segments to this key.
	|changes_yes 	// Changes are permitted. 
	|dupl_no,        // Duplicates are not permitted. 
	// set up third integer as first segment of key 0. 
	 seg_start_base * 0 // This segment starts at position 0. 
	|seg_length_base * 3, // The segment length is 3. 
	// set up fourth integer as second segment of key 0. 
	 seg_start_base * 3 // This segment starts at position 3. 
	|seg_length_base * 5, // The segment length is 5. 
};
*/
const char holi_rule		= 1;
const char holi_spec		= 2;
const char holiday_rule		= 99;
const char holiday_rule_simp	= 0;
const char holiday_rule_ref	= 100;
const char holiday_rule_bus_off	= 100;
const char holiday_rule_non_bus	= 110;
const char holiday_length 	= 13;
//const char holiday_code_length 	= holidaycodelength;
const char holiday_key_length 	= 8;

/*
static unsigned int test1_keys[5] = {
	// First Integer is the record length. 
	10,
	// set up second integer as key definition. 
	(key_0 		// This is key 0 
	|keys_1		// There is one key. 
	|segment_3	// There are three segments to this key.
	|changes_yes 	// Changes are permitted. 
	|dupl_no),        // Duplicates are not permitted. 
	// set up third integer as first segment of key 0. 
	(seg_start_base * 0 // This segment starts at position 0. 
	|seg_length_base * 2), // The segment length is 2. 
	// set up fourth integer as second segment of key 0. 
	(seg_start_base * 2 // This segment starts at position 2. 
	|seg_length_base * 3), // The segment length is 3. 
	// set up fifth integer as third segment of key 0. 
	(seg_start_base * 5 // This segment starts at position 5. 
	|seg_length_base * 1) // The segment length is 1. 
};
*/
const unsigned char month_title = 0;
const unsigned char month_january_number = 1;
const unsigned char month_february_number = 2;
const unsigned char month_march_number = 3;
const unsigned char month_april_number = 4;
const unsigned char month_may_number = 5;
const unsigned char month_june_number = 6;
const unsigned char month_july_number = 7;
const unsigned char month_august_number = 8;
const unsigned char month_september_number = 9;
const unsigned char month_october_number = 10;
const unsigned char month_november_number = 11;
const unsigned char month_december_number = 12;
const unsigned char month_names_total = 13;
const unsigned char month_names_length = 11;

char *const month_names[month_names_total] =
		 {language_pick_month,
		 language_january,
		 language_february,
		 language_march,
		 language_april,
		 language_may,
		 language_june,
		 language_july,
		 language_august,
		 language_september,
		 language_october,
		 language_november,
		 language_december};
//#ifndef _ANSIC

class CALC_API _HUGE_ Date_Funcs {

public:
//#endif
  typedef struct 	date_struc	{char centuries;
				char years;
				char months;
				char days;
				char null;}
		date_struc;

  typedef union 	date_union	{char date_string[5];
				date_struc date;}
		date_union;

  /* { event schedule is used to indicate the periodicity of events.}*/

  typedef struct 	event_sched	{date_union 	first_date;
				/*{ event_sched.first_date indicates the
				first date the event occurs.}*/
				unsigned char 		period;
				/*{ event_sched.period indicates the unit
				(days, months, etc.) for standard events
				see the constants event_sched_xxx_period.}*/
				unsigned char 		freq;
				/*{ event_sched.freq indicates the number
				of periods between each event.}*/
				unsigned char 		holiday_adj;
				/*{ event_sched.holiday_adj indicates what
				day shift occurs if the scheduled date falls
				on a non business day. For acceptable values
				see the constants event_sched_xxx_holiday_adj.}*/
				unsigned char 		month_day;}
				/*{ event_sched.month_day indicates the day
				of the month the event normally occurs.
				Can be any value from 1 to 31 or the
				constant date_last_day_in_month.}*/
		event_sched;

  #include "holidays.map"

  unsigned long GetMonth(int name_number, char name_parm[month_names_length]);
  unsigned long CheckMonth(int name_number);
  unsigned long CheckYear(unsigned int base_year);
  unsigned long CheckMonthDay(unsigned int base_day);
  unsigned long CheckWeekday(unsigned int base_day);

  static unsigned long 	tenor	(date_union,
			date_union,
			char,
			long *);

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


  static unsigned long	forecast	(date_union,
				int,
				long,
				char,
				date_union *);

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


  static unsigned long	date_to_days	(date_union,
				long *);

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


  static unsigned long	adj_last	(date_union *);

  /*{adj_last adjusts the days in the date passed if they exceed the maximum
	days in month.

	Usage:  unsigned long adj_last(date_union *in_date)

	where:  *in_date =	Input parameter of pointer to date_union
				type which contains the date to be adjusted.

		return value =  of unsigned long type gives completion status.

	 Called by:	<[forecast]

  }*/


  unsigned long	days_to_date	(long,
				date_union *);

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


  static int		month_end	(date_union);

  /*{month_end returns the number of days in the month of the date passed.

	Usage:  int month_end(date_union in_date)

	where:  in_date	=	input parameter of date_union type, which is
				the date for which the last day of the month
				is to be found.

		return value =  of int type is the number of days in the month
				in in_date.

	 Called by:	<[days_to_date]

  }*/


  static unsigned long	findday		(date_union,
				char *);

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


  unsigned long	holiload	(holidays_struct [], char mem_alloc);

  unsigned long	holimain	(holidays_struct holi_parm [],
				holidays_struct *activ_holi,
				int *holi_index,
				char action);

  static void   		datecpy 	(void *,
				 const void *);

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


  int   		datecmp 	(const void *,
				 const void *);

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

//#ifndef _ANSIC
  unsigned long  dateconv(char, char, char *, date_union *, double *);


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

		date_chars	character array holding the date as a
				string.

		date_union	a date_union type holding the date as a
				date_union.

					 in_date		a double type holding the date.

		return value =  of unsigned long type gives completion status.

	 Called by:	<[]

  }*/
//#endif

  unsigned long   adj_date	(date_union *,
				char,
				char,
				char,
				char,
//				char [],
				unsigned int
//				,holidays_struct []
				,const set<string> &holiSet
				);


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

  static unsigned long   CheckDate	(unsigned int year, unsigned int month, unsigned int day);

  static unsigned long   datechck	(date_union check_date1);


  /*{datechck validates whether the passed date is possible.

	Usage:  unsigned long 	datechck(date_union check_date1);

	where:  check_date1 =	Input/Output parameter of date_union type
				which contains the date to be checked.

  }*/


  unsigned long   findhol 	(date_union,
				char [],
				char *,
				unsigned int,
				char *
//				,holidays_struct []
				,const set<string> &holiSet
				);

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
//#ifndef _ANSIC

private:
//#endif

	static void month_add(date_union,int,date_union *); /*{ Adds months to a date.}*/
//#ifndef _ANSIC

};
//#endif
#endif
