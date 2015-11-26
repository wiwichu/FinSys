
#ifndef __Holidays_H
#if defined (BUILDING_YOUR_DLL)
	#define _EX_IN_CLASS __export
	#define _EX_IN_FUNC //_export
	#define _FAR_CLASS  //FAR
	#define _FAR_FUNC   //FAR
	#define _EXTERN  extern
#elif defined(USING_YOUR_DLL)
	#define _EX_IN_CLASS __import
	#define _EX_IN_FUNC
	#define _FAR_CLASS
	#define _FAR_FUNC
	#define _EXTERN
#else
	#define _EX_IN_CLASS
	#define _EX_IN_FUNC
	#define _FAR_CLASS
	#define _FAR_FUNC
	#define _EXTERN
#endif
//

#define __Holidays_H
#include <string.h>
#include "errdecs.h"
#include "datedec.h"
#include "wordsymb.h"
//#include "db.h"
#include "shrtdecs.h"
//#include "iodec.h"

//
const	unsigned char	holiday_date_base	= 1;
const	unsigned char	holiday_month_base	= 2;
const	unsigned char	holiday_easter_base	= 3;
const int holidaybasetotal = 4;
const int holidaybaselength = 10;
const int holidaybasedaytotal = 32;
const int holidaybasedaylength = 9;
const int holidaybaseadjtotal = 3;
const int holidaybaseadjlength = holiday_adj_names_len;
const int holidaybaseadjtimestotal = 5;
const int holidaybaseadjtimeslength = 13;
const int holidayweekdaytotal = 9;
const int holidayweekdaylength = 9;
const int adjustdirectiontotal = 4;
const int adjustdirectionlength = 15;
const int adjustdirection_exact = 1;
const int adjustdirection_after = 2;
const int adjustdirection_before = 3;
const int dayadjusttotal = 6;
const int dayadjustlength = 13;
const int baseweekdaytotal = 8;
const int baseweekdaylength = 13;
const int holidayyearlength = 5;
const int holidayadjtimeslength = 4;
const int holiday_date_max = 20;
const	unsigned char	holiday_yes_designate	= 1;
const	unsigned char	holiday_no_designate	= 2;
const int designatetotal = 2;
const int designatelength = 4;
const int MAXHOLIRECS = 5;
//
class CALC_API _EX_IN_CLASS holidays_class : virtual public Date_Funcs, virtual public _errtext
{


private:
/*
	unsigned char	holiday_date_base;
	unsigned char	holiday_month_base;
	unsigned char	holiday_easter_base;
	int holidaybasetotal;
	int holidaybaselength;
	int holidaybasedaytotal;
	int holidaybasedaylength;
	int holidaybaseadjtotal;
	int holidaybaseadjlength;


	char * holiday_base_names[holidaybasetotal];
*/
/*
	typedef struct 	holiday_date	{char code [holidaycodelength];
				char centuries;
				char years;
				char months;
				char days;
				char null;}
		holiday_date;
*/
	int holiday_date_count;

//	holiday_date holiday_date_array[holiday_date_max];

	int dummy_int;
	size_t dummy_size_t;
	unsigned long return_state;
	unsigned char current_base;
	unsigned char current_month;
	unsigned char current_day;
	unsigned int current_year;
	unsigned char current_base_adj;
	unsigned char current_base_adj_times;
	unsigned char current_holiday_adj_times;
	unsigned char current_holiday_weekday;
	unsigned char current_adjust_direction;
	unsigned char current_day_adjust;
	unsigned char current_base_weekday;
	unsigned char current_designate;
//	char holiday_code [holidaycodelength];
//	CDB * DB_holiday;
//	CDB::DB_Handles holidayhandles;

	char db_type;

	unsigned long AddHolidayRec();
	unsigned long DelHolidayRec();
//	unsigned long SortHolidayArray();
//	unsigned long SearchHolidayArray(char *search_result);

public:
	holidays_class();
//	holidays_class(CDB * DB_parm);
	unsigned long settestdate(	char test_date[date_string_size]);
	unsigned long AddHoliday();
	unsigned long DelHoliday();
	unsigned long GetHoliday();
	unsigned long TestHoliday();
	unsigned long HolidayInit(); //Initialize the members.
	unsigned long HolidayCheckAll(); //Check all Data.
	unsigned long HolidayFind(); //Find a Holiday.
	unsigned long HolidayAdd(); //Add a new Holiday.
	unsigned long HolidayDelete(); //Delete a Holiday.
	unsigned long GetHolidayBaseTotal(int *array_size); //Gets the total base choices.
	unsigned long GetHolidayBase(char *base_parm); //Gets the current base.
	unsigned long GetHolidayBase(int element_count,
	char base_name_str[holidaybaselength]); //Gets the base month choice in position element_count.
	unsigned long GetDesignate(char *designate_parm); //Gets the current base.
	unsigned long GetDesignate(int element_count,
	char designate_str[designatelength]); //Gets the base month choice in position element_count.
	unsigned long GetCurrentMonth(char *month_parm); //Gets the current base month.
	unsigned long GetHolidayBaseDay(int element_count,
	char day_number_str[holidaybasedaylength]); //Gets the base day choice in position element_count.
	unsigned long GetCurrentBaseDay(char *day_parm); //Gets the current base day.
	unsigned long GetBaseAdjTotal(int *array_size); //Gets the total base adjust choices.
	unsigned long GetBaseAdj(char *adj_parm); //Gets the current base adjust.
	unsigned long GetBaseAdj(int element_count,
	char name_str[holidaybaseadjlength]); //Gets the base adjust choice in position element_count.
	unsigned long GetBaseAdjTimesTotal(int *array_size); //Gets the total base adjust choices.
	unsigned long GetBaseAdjTimes(char *adj_times_parm); //Gets the current base adjust.
	unsigned long GetBaseAdjTimes(int element_count,
	char name_str[holidaybaseadjtimeslength]); //Gets the base adjust choice in position element_count.
	unsigned long GetHolidayWeekdayTotal(int *array_size); //Gets the total holiday weekday choices.
	unsigned long GetHolidayWeekday(char *weekday_parm); //Gets the current holiday weekday.
	unsigned long SetHolidayWeekday(char *weekday_parm); //Sets the current holiday weekday.
	unsigned long GetHolidayWeekday(int element_count,
	char name_str[holidayweekdaylength]); //Gets the holiday weekday choice in position element_count.
	unsigned long CheckHolidayWeekday(char name_str[holidayweekdaylength],
		unsigned char *weekday_code); //Checks the holiday weekday.
	unsigned long GetAdjustDirectionTotal(int *array_size); //Gets the total adjust direction choices.
	unsigned long GetAdjustDirection(char *direction_parm); //Gets the current adjust direction.
	unsigned long GetAdjustDirection(int element_count,
	char name_str[adjustdirectionlength]); //Gets the adjust direction choice in position element_count.
	unsigned long SetAdjustDirection(char *direction_parm); //Sets the current adjust direction.
	unsigned long CheckAdjustDirection(char name_str[adjustdirectionlength],
		unsigned char *direction_code); //Checks the adjust direction.
	unsigned long GetDayAdjustTotal(int *array_size); //Gets the total day adjust choices.
	unsigned long GetDayAdjust	(char *day_adjust_parm); //Gets the current day adjust .
	unsigned long GetDayAdjust(int element_count,
	char name_str[dayadjustlength]); //Gets the day adjust choice in position element_count.
	unsigned long SetDayAdjust(char *day_adjust_parm); //Sets the day adjust.
	unsigned long CheckDayAdjust(char name_str[dayadjustlength],
		unsigned char *day_adjust_code); //Checks the day adjust.
	unsigned long GetBaseWeekdayTotal(int *array_size); //Gets the total base weekday choices.
	unsigned long GetBaseWeekday	(char *base_weekday_parm); //Gets the current base weekday .
	unsigned long GetBaseWeekday(int element_count,
	char name_str[baseweekdaylength]); //Gets the base weekday choice in position element_count.
	unsigned long SetBaseWeekday(char *base_weekday_parm); //Sets the base weekday.
	unsigned long CheckBaseWeekday(char name_str[baseweekdaylength],
		unsigned char *base_weeday_code); //Checks the base weekday.
	unsigned long CheckBaseWeekday(unsigned char base_weeday_code); //Checks the base weekday.
	unsigned long SetHolidayCode(char name_str[baseweekdaylength]); //Sets the holiday code.
	unsigned long SetHolidayBase(char name_str[holidaybaselength]); //Sets the holiday base.
	unsigned long SetDesignate(char designate_str[designatelength]); //Sets the holiday base.
	unsigned long CheckHolidayBase(char name_str[holidaybaselength],
		unsigned char *base_code); //Checks the holiday base.
	unsigned long SetHolidayYear(unsigned int base_year); //Sets the holiday year.
//	unsigned long CheckHolidayYear(unsigned int base_year); //Checks the holiday year.
	unsigned long SetHolidayMonth(char name_str[month_names_length]); //Sets the holiday month.
	unsigned long CheckHolidayMonth(char name_str[month_names_length],
		unsigned char *month_code); //Checks the holiday month.
	unsigned long SetHolidayDay(char name_str[holidaybasedaylength]); //Sets the holiday day.
	unsigned long CheckHolidayDay(int day_code); //Checks the holiday day.
	unsigned long SetBaseAdj(char name_str[holidaybaseadjlength]); //Sets the base adjustment.
	unsigned long CheckBaseAdj(char name_str[holidaybaseadjlength],
		unsigned char *base_code); //Checks the base adjustment.
	unsigned long SetBaseAdjTimes(char name_str[holidaybaseadjtimeslength]); //Sets the holiday base adjust times.
	unsigned long CheckBaseAdjTimes(int adj_times_code); //Checks the holiday base adjust times.
	unsigned long SetHolidayAdjTimes(char name_str[holidayadjtimeslength]); //Sets holiday adjust times.
	unsigned long CheckDesignate(char designate_str[designatelength],
		unsigned char *designate_code); //Checks the designate choice.
//	unsigned long SetDB(CDB *);
//	unsigned long AddArray();
//	unsigned long AddODBC();
//	unsigned long AddOLEDB();
//	unsigned long DelArray();
//	unsigned long DelODBC();
//	unsigned long DelOLEDB();
//	unsigned long SetDBArray();
//	unsigned long SetDBODBC(CDB *);
//	unsigned long SetDBOLEDB(CDB *);

		char holiday_counter;

//	holiday_rec holiday_file[MAXHOLIRECS];	
//	CDB::holiday_rec * holiday_record;	
//	CDB::holiday_rec * holiday_record_hold;	

};


#endif