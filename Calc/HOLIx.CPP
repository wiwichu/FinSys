//#include "stdafx.h"
#include "stdafx.h"
#include "holihead.h"
#include "stdlib.h"

holidays_class::holidays_class()
{
	HolidayInit();

}
/*
holidays_class::holidays_class(CDB * DB_parm)
{

	DB_holiday = DB_parm;

//	DB_holiday->InitDB();

//	DB_holiday->GetStatementHandle(&holidayhandles);

	return_state = HolidayInit();

}
*/
 
unsigned long holidays_class::HolidayInit()
{

	return return_success;

}

unsigned long holidays_class::AddHolidayRec()
{

	return return_success;

}

unsigned long holidays_class::DelHolidayRec()
{
	return return_err_DB_invalid;

}

unsigned long holidays_class::HolidayCheckAll()
{
	unsigned long return_state;
	return_state = return_success;

  switch (current_base)
  {
	 case holiday_date_base:
	 {

		return_state = CheckMonth(current_month);

		if (return_state != return_success)
		{
		  return return_state;
		}

		return_state = CheckYear(current_year);

		if (return_state != return_success)
		{
		  return return_state;
		}

		return_state = CheckMonthDay(current_day);

		if (return_state != return_success)
		{
		  return return_state;
		}

		return_state = CheckDate(current_year, current_month, current_day);

		if (return_state != return_success)
		{
		  return return_state;
		}
		break;
	 }
	 case holiday_month_base:
	 {
		return_state = CheckMonth(current_month);
		if (return_state == return_success)
		{
		 return_state = CheckMonthDay(current_day);
		 if (return_state == return_success)
		 {
		  return_state = CheckWeekday(current_base_weekday);
		  if (return_state == return_success)
		  {

			 return_state = return_err_day_and_weekday;
			 return return_state;

		  }
		  else
		  {

			 return_state = return_success;
			 return return_state;

		  }
		 }
		 else
		 {
		  return_state = CheckWeekday(current_base_weekday);
		  if (return_state == return_success)
		  {
		  }
		  else
		  {

			 return_state = return_err_day_nor_weekday;
			 return return_state;

		  }
		 }
		}
		else
		{
		  return return_state;
		}

		break;
	 }
	 case holiday_easter_base:
	 {
		break;
	 }
	 default:
	 {
		return_state = return_err_holiday_base_invalid;
		return return_state;
		break;
	 }
  }

//func_end:
	return return_state;
}
unsigned long holidays_class::HolidayFind()
{

	return return_success;
}
unsigned long holidays_class::HolidayAdd()
{
	AddHolidayRec();
	return return_success;
}
unsigned long holidays_class::HolidayDelete()
{

	return return_success;
}

unsigned long holidays_class::GetHolidayBaseTotal(int *array_total)
{
	*array_total = holidaybasetotal;
	return return_success;

}

unsigned long holidays_class::GetHolidayBase(int element_count,
	char base_name_str[holidaybaselength])
{

	char *const holiday_base_names[holidaybasetotal] =
		{language_pick_base, language_date,language_month,language_easter};
	unsigned long local_return;

	local_return = return_success;

	strcpy(base_name_str, holiday_base_names [element_count]);
	return local_return;
}
unsigned long holidays_class::GetHolidayBase(char *base_parm)
{
	unsigned long local_return;

	local_return = return_success;
	*base_parm = current_base;
	return local_return;
}
unsigned long holidays_class::GetCurrentMonth(char *month_parm)
{

	*month_parm = current_month;
	return return_success;
}

unsigned long holidays_class::GetHolidayBaseDay(int element_count,
	char day_number_str[holidaybasedaylength])
{

	if (element_count == 0)
	{
	  strcpy(day_number_str, language_pick_day);
	}
	else
	{
	  //itoa((element_count ),day_number_str,10);
		snprintf(day_number_str, 10, "%d", element_count);
	}
	return return_success;
}

unsigned long holidays_class::GetCurrentBaseDay(	char *day_parm)
{

	*day_parm = current_day;
	return return_success;
}

unsigned long holidays_class::GetBaseAdjTotal(int *array_total)
{
	*array_total = holidaybaseadjtotal;
	return return_success;

}

unsigned long holidays_class::GetBaseAdj(int element_count,char name_str[holidaybaseadjlength])
{

	char *const holiday_base_adj_names[holidaybaseadjtotal] =
		{holiday_adj_names[event_sched_same_holiday_adj],
		holiday_adj_names[event_sched_next_holiday_adj],
		holiday_adj_names[event_sched_prev_holiday_adj]};


	strcpy(name_str, holiday_base_adj_names [element_count]);
	return return_success;
}
unsigned long holidays_class::GetBaseAdj(char *adj_parm)
{

	*adj_parm = current_base_adj;
	return return_success;
}

unsigned long holidays_class::GetBaseAdjTimesTotal(int *array_total)
{
	*array_total = holidaybaseadjtimestotal;
	return return_success;

}

unsigned long holidays_class::GetBaseAdjTimes(int element_count,
	char name_str[holidaybaseadjtimeslength])
{

	if (element_count == 0)
	{
	  strcpy(name_str, language_adjust_times);
	}
	else
	{
	  //itoa((element_count),name_str,10);
		snprintf(name_str, 10, "%d", element_count);
	}
	return return_success;
}
unsigned long holidays_class::GetBaseAdjTimes(char *adj_parm)
{

	*adj_parm = current_base_adj_times;
	return return_success;
}

unsigned long holidays_class::GetHolidayWeekdayTotal(int *array_total)
{
	*array_total = holidayweekdaytotal;
	return return_success;

}

unsigned long holidays_class::GetHolidayWeekday(int element_count,
	char name_str[holidayweekdaylength])
{

	char *const holiday_weekday_names[holidayweekdaytotal] =
		{language_sunday,
		language_monday,
		language_tuesday,
		language_wednesday,
		language_thursday,
		language_friday,
		language_saturday,
		language_days,
		language_pick_unit};


	strcpy(name_str, holiday_weekday_names [element_count]);
	return return_success;
}
unsigned long holidays_class::GetHolidayWeekday(char *weekday_parm)
{

	*weekday_parm = current_holiday_weekday;
	return return_success;
}
unsigned long holidays_class::SetHolidayWeekday(char name_str[holidayweekdaylength])
{
	unsigned char weekday_code;

	unsigned long return_state;
	return_state = return_success;

	return_state = CheckHolidayWeekday(name_str, &weekday_code);

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_holiday_weekday = weekday_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckHolidayWeekday(char name_str[holidayweekdaylength],
	unsigned char *weekday_code)
{
	char weekday_hold[holidayweekdaylength];
	unsigned long local_return;

	unsigned long return_state;
	return_state = return_err_holiday_weekday_invalid;

	for(*weekday_code = 0;
		(*weekday_code < holidayweekdaytotal) && (return_state != return_success);
		*weekday_code = *weekday_code + 1)
	{
		local_return = holidays_class::GetHolidayWeekday(*weekday_code, weekday_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  return return_state;
		}
		dummy_int = strcmp(name_str,weekday_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

//func_end:
	return return_state;
}

unsigned long holidays_class::GetAdjustDirectionTotal(int *array_total)
{
	*array_total = adjustdirectiontotal;
	return return_success;

}

unsigned long holidays_class::GetAdjustDirection(int element_count,
	char name_str[adjustdirectionlength])
{

	char *const adjust_direction_names[adjustdirectiontotal] =
		{language_pick_direction,
		language_exact,
		language_after,
		language_before};


	strcpy(name_str, adjust_direction_names [element_count]);
	return return_success;
}
unsigned long holidays_class::GetAdjustDirection(char *direction_parm)
 {

	*direction_parm = current_adjust_direction;
	return return_success;
}
unsigned long holidays_class::SetAdjustDirection(char name_str[adjustdirectionlength])
{
	unsigned char direction_code;

	unsigned long return_state;
	return_state = return_success;

	return_state = CheckAdjustDirection(name_str, &direction_code);

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_adjust_direction = direction_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckAdjustDirection(char name_str[adjustdirectionlength],
	unsigned char *direction_code)
{
	char direction_hold[adjustdirectionlength];
	unsigned long local_return;

	unsigned long return_state;
	return_state = return_err_adjust_direction_invalid;

	for(*direction_code = 0;
		(*direction_code < adjustdirectiontotal) && (return_state != return_success);
		*direction_code = *direction_code + 1)
	{
		local_return = holidays_class::GetAdjustDirection(*direction_code, direction_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  return return_state;
		}
		dummy_int = strcmp(name_str,direction_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

//func_end:
	return return_state;
}

unsigned long holidays_class::GetDayAdjustTotal(int *array_total)
{
	*array_total = dayadjusttotal;
	return return_success;

}

unsigned long holidays_class::GetDayAdjust(int element_count,
	char name_str[dayadjustlength])
{

	char *const day_adjust_names[dayadjusttotal] =
		{language_adjust_times,
		language_first,
		language_second,
		language_third,
		language_fourth,
		language_last};


	strcpy(name_str, day_adjust_names [element_count]);
	return return_success;
}
unsigned long holidays_class::GetDayAdjust(char *day_adjust_parm)
 {

	*day_adjust_parm = current_day_adjust;
	return return_success;
}
unsigned long holidays_class::SetDayAdjust(char name_str[dayadjustlength])
{
	unsigned char day_adjust_code;

	unsigned long return_state;
	return_state = return_success;

	return_state = CheckDayAdjust(name_str, &day_adjust_code);

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_day_adjust = day_adjust_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckDayAdjust(char name_str[dayadjustlength],
	unsigned char *day_adjust_code)
{
	char day_adjust_hold[dayadjustlength];
	unsigned long local_return;

	unsigned long return_state;
	return_state = return_err_day_adjust_invalid;

	for(*day_adjust_code = 0;
		(*day_adjust_code < dayadjusttotal) && (return_state != return_success);
		*day_adjust_code = *day_adjust_code + 1)
	{
		local_return = holidays_class::GetDayAdjust(*day_adjust_code, day_adjust_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  return return_state;
		}
		dummy_int = strcmp(name_str,day_adjust_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

//func_end:
	return return_state;
}

unsigned long holidays_class::GetBaseWeekdayTotal(int *array_total)
{
	*array_total = baseweekdaytotal;
	return return_success;

}

unsigned long holidays_class::GetBaseWeekday(int element_count,
	char name_str[baseweekdaylength])
{

	char *const base_weekday_names[baseweekdaytotal] =
		{language_sunday,
		language_monday,
		language_tuesday,
		language_wednesday,
		language_thursday,
		language_friday,
		language_saturday,
		language_pick_weekday};


	strcpy(name_str, base_weekday_names [element_count]);
	return return_success;
}
unsigned long holidays_class::GetBaseWeekday(char *base_weekday_parm)
 {
	unsigned long local_return;
	local_return = return_success;
	*base_weekday_parm = current_base_weekday;
	return local_return;
}
unsigned long holidays_class::SetBaseWeekday(char name_str[baseweekdaylength])
{
	unsigned char base_weekday_code;

	unsigned long return_state;
	return_state = return_success;

	return_state = CheckBaseWeekday(name_str, &base_weekday_code);

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_base_weekday = base_weekday_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckBaseWeekday(unsigned char base_weekday_code)
{
  unsigned long local_return;

  if ((base_weekday_code > 0) && (base_weekday_code < baseweekdaytotal))
  {

	 local_return = return_success;

  }
  else
  {

	 local_return = return_err_base_weekday_invalid;

  }
//func_end:
	return local_return;
}
unsigned long holidays_class::CheckBaseWeekday(char name_str[baseweekdaylength],
	unsigned char *base_weekday_code)
{
	char base_weekday_hold[baseweekdaylength];
	unsigned long local_return;

	local_return = return_err_base_weekday_invalid;

	for(*base_weekday_code = 0;
		(*base_weekday_code < baseweekdaytotal) && (local_return != return_success);
		*base_weekday_code = *base_weekday_code + 1)
	{
		local_return = holidays_class::GetBaseWeekday(*base_weekday_code, base_weekday_hold);
		if (local_return != return_success)
		{
		  return local_return;
		}
		dummy_int = strcmp(name_str,base_weekday_hold);
		if (dummy_int == 0)
		{

		  local_return = return_success;

		}
	}

//func_end:
	return local_return;
}
/*
unsigned long holidays_class::SetHolidayCode(char name_str[holidaycodelength])
{
	return_state = return_success;

	dummy_size_t = strlen(name_str);

	if (dummy_size_t>=holidaycodelength)
	{
		return_state = return_err_holiday_code_too_big;
		return return_state;
	}
	else
	{
	  dummy_int = strcmp(name_str,"");
	  if (dummy_int == 0)
	  {

		return_state = return_err_holiday_code_blank;
		return return_state;

	  }
	  else
	  {
		 strcpy(holiday_code,name_str);
	  }
	}

func_end:
	return return_state;
}
*/
unsigned long holidays_class::SetHolidayBase(char name_str[holidaybaselength])
{
	unsigned char base_code;

	unsigned long return_state;
	return_state = return_success;

	return_state = CheckHolidayBase(name_str, &base_code);

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_base = base_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckHolidayBase(char name_str[holidaybaselength],
	unsigned char *base_code)
{
	char base_hold[holidaybaselength];
	unsigned long local_return;

	unsigned long return_state;
	return_state = return_err_holiday_base_invalid;

	for(*base_code = 0;
		(*base_code < holidaybasetotal) && (return_state != return_success);
		*base_code = *base_code + 1)
	{
		local_return = holidays_class::GetHolidayBase(*base_code, base_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  return return_state;
		}
		dummy_int = strcmp(name_str,base_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

//func_end:
	*base_code = *base_code - 1;
	return return_state;
}
unsigned long holidays_class::SetHolidayMonth(char name_str[month_names_length])
{
	unsigned char month_code;

	unsigned long return_state;
	return_state = return_success;

	return_state = CheckHolidayMonth(name_str, &month_code);

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_month = month_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckHolidayMonth(char name_str[month_names_length],
	unsigned char *month_code)
{
	char month_hold[month_names_length];
	unsigned long local_return;

	unsigned long return_state;
	return_state = return_err_holiday_month_invalid;

	for(*month_code = 0;
		(*month_code < month_names_total) && (return_state != return_success);
		*month_code = *month_code + 1)
	{
		local_return = holidays_class::GetMonth(*month_code, month_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  return return_state;
		}
		dummy_int = strcmp(name_str,month_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

//func_end:
	*month_code = *month_code - 1;
	return return_state;
}
unsigned long holidays_class::SetHolidayYear(unsigned int base_year)
{

	unsigned long return_state;
	return_state = CheckYear(base_year);

  if (return_state != return_success)
  {
	 return return_state;
  }
  else
  {
	 current_year = base_year;
  }
//func_end:
	return return_state;
}
unsigned long holidays_class::SetHolidayDay(char name_str[holidaybasedaylength])
{
	int day_code;

	unsigned long return_state;
	return_state = return_success;

	dummy_int = strcmp(language_pick_day,name_str);
	if (dummy_int == 0)
	{

	  day_code = 0;

	}
	else
	{

	  day_code = atoi(name_str);

	  return_state = CheckHolidayDay(day_code);
	}

	if (return_state != return_success)
	{
	 return return_state;
	}
	 else
	{
	 current_day = day_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckHolidayDay(int day_code)
{

	unsigned long return_state;
	return_state = return_err_holiday_day_invalid;

	if ((day_code > 0) && (day_code < 32) )
	{

		  return_state = return_success;

	}

//func_end:
	return return_state;
}
unsigned long holidays_class::SetBaseAdj(char name_str[holidaybaseadjlength])
{
	unsigned char adj_code;

	unsigned long return_state;
	return_state = return_success;

	return_state = CheckBaseAdj(name_str, &adj_code);

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_base_adj = adj_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckBaseAdj(char name_str[holidaybaseadjlength],
	unsigned char *adj_code)
{
	char adj_hold[holidaybaseadjlength];
	unsigned long local_return;

	unsigned long return_state;
	return_state = return_err_holiday_base_adj_invalid;

	for(*adj_code = 0;
		(*adj_code < holidaybaseadjtotal) && (return_state != return_success);
		*adj_code = *adj_code + 1)
	{
		local_return = holidays_class::GetBaseAdj(*adj_code, adj_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  return return_state;
		}
		dummy_int = strcmp(name_str,adj_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::SetBaseAdjTimes(char name_str[holidaybaseadjtimeslength])
{
	int adj_times_code;

	unsigned long return_state;
	return_state = return_success;

	dummy_int = strcmp(language_adjust_times,name_str);
	if (dummy_int == 0)
	{

	  adj_times_code = 0;

	}
	else
	{

	  adj_times_code = atoi(name_str);

	  return_state = CheckBaseAdjTimes(adj_times_code);
	}

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_base_adj_times = adj_times_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckBaseAdjTimes(int adj_times_code)
{

	unsigned long return_state;
	return_state = return_err_adj_times_invalid;

	if ((adj_times_code >= 0) && (adj_times_code <= holidaybaseadjtimestotal) )
	{

		  return_state = return_success;

	}

//func_end:
	return return_state;
}
unsigned long holidays_class::SetHolidayAdjTimes(char name_str[holidayadjtimeslength])
{
	unsigned long return_state;
	return_state = return_success;

	dummy_size_t = strlen(name_str);

	if (dummy_size_t>=holidayadjtimeslength)
	{
		return_state = return_err_holiday_adj_times_too_big;
		return return_state;
	}
	else
	{
	  dummy_int = atoi(name_str);

	  if (current_adjust_direction == adjustdirection_exact)
	  {
		 if (dummy_int == 0)
		 {

			return_state = return_err_holiday_adj_times_blank;
			return return_state;

		 }
		 else
		 {
			current_holiday_adj_times = dummy_int;
//			strcpy(holiday_code,name_str);
		 }
	  }
	}

//func_end:
	return return_state;
}

unsigned long holidays_class::AddHoliday()
{

	unsigned long return_state;
	return_state = return_success;

	return_state = AddHolidayRec();

//func_end:
	return return_state;
}
unsigned long holidays_class::DelHoliday()
{

	unsigned long return_state;
	return_state = return_success;

	return_state = DelHolidayRec();

//func_end:
	return return_state;
}
unsigned long holidays_class::GetHoliday()
{

	return return_success;
}

unsigned long holidays_class::TestHoliday()
{
	unsigned long local_return;
//	int local_dummy_int;
	local_return = return_success;
/*

	for (dummy_int = 0; local_dummy_int = 1;dummy_size_t = holidaycodelength,
			((memcmp(holiday_code,holiday_date_array[holiday_date_count].code,dummy_size_t) != 0) &&
			 (holiday_code,holiday_date_array[holiday_date_count].centuries != (current_year / 100)) &&
			 (holiday_code,holiday_date_array[holiday_date_count].years != (current_year % 100)) &&
			 (holiday_code,holiday_date_array[holiday_date_count].months != current_month) &&
			 (holiday_code,holiday_date_array[holiday_date_count].days != current_day) &&
			 dummy_int <= holiday_date_count),
			 dummy_int++
		)
	{
	}
	  dummy_int--;

	  if (dummy_int < holiday_date_count)
	  {
		 memcpy(holiday_code,
				holiday_date_array[dummy_int].code,
				dummy_size_t);
		 current_year = (holiday_date_array[dummy_int].centuries * 100) +
		 holiday_date_array[dummy_int].years;
		 current_month = holiday_date_array[dummy_int].months;
		 current_day = holiday_date_array[dummy_int].days;
	  }
	  else
	  {
	  }
*/

//func_end:
	return local_return;
}

unsigned long holidays_class::settestdate(char test_date[date_string_size])
{
	unsigned long local_return;
	local_return = return_success;
//func_end:
	return local_return;
}


unsigned long holidays_class::GetDesignate(int element_count,
	char designate_name_str[designatelength])
{

	char *const designate_names[designatetotal] =
		{language_yes,language_no};
	unsigned long local_return;

	local_return = return_success;

	strcpy(designate_name_str, designate_names [element_count]);
	return local_return;
}
unsigned long holidays_class::GetDesignate(char *designate_parm)
{
	unsigned long local_return;

	local_return = return_success;
	*designate_parm = current_designate;
	return local_return;
}
unsigned long holidays_class::SetDesignate(char designate_str[designatelength])
{
	unsigned char designate_code;

	unsigned long return_state;
	return_state = return_success;

	return_state = CheckDesignate(designate_str, &designate_code);

	if (return_state != return_success)
	{
		return return_state;
	}
	else
	{
	  current_designate = designate_code;
	}

//func_end:
	return return_state;
}
unsigned long holidays_class::CheckDesignate(char designate_str[designatelength],
	unsigned char *designate_code)
{
	unsigned long return_state;
	char designate_hold[designatelength];
	unsigned long local_return;

	return_state = return_err_holiday_designation_invalid;

	for(*designate_code = 1;
		(*designate_code < designatetotal) && (return_state != return_success);
		*designate_code = *designate_code + 1)
	{
		local_return = holidays_class::GetDesignate(*designate_code, designate_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  return return_state;
		}
		dummy_int = strcmp(designate_str,designate_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

//func_end:
//	*designate_code = *designate_code - 1;
	return return_state;
}
/*
unsigned long holidays_class::SetDB(CDB * DB_parm)
{
	return_state = return_success;

	DB_holiday = DB_parm;

//	DB_holiday->GetStatementHandle(&holidayhandles);

//	db_type = db_odbc_type;
//func_end:
	return return_state;

}
*/

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
