#include "stdafx.h"
#include "holidays.h"
#include "stdlib.h"

holidays_class::holidays_class()
{
/*
	holiday_date_base	= 0;
	holiday_month_base	= 1;
	holiday_easter_base	= 2;
	holidaybasetotal = 3;
	holidaybaselength = 7;
	holidaybasedaytotal = 31;
	holidaybasedaylength = 3;
	holidaybaseadjtotal = 3;
	holidaybaseadjlength = holiday_adj_names_len;

*/
//	holiday_base_names[holidaybasetotal] = {"Date","Month","Easter"};
	return_state = HolidayInit();

}

unsigned long holidays_class::HolidayInit()
{
	return_state = return_success;

	current_base = 0;
	current_month = month_title;
	current_day = 0;
	current_year = 0;
	current_base_adj = 0;
	current_base_adj_times = 0;
	current_holiday_weekday = 8;
	current_adjust_direction = 0;
	current_day_adjust = 0;
	current_base_weekday = 7;
	current_holiday_adj_times = 0;
	holiday_date_count = 0;
	return return_state;

}
unsigned long holidays_class::HolidayCheckAll()
{
  return_state = return_success;

  switch (current_base)
  {
	 case holiday_date_base:
	 {

		return_state = CheckMonth(current_month);

		if (return_state != return_success)
		{
		  goto func_end;
		}

		return_state = CheckYear(current_year);

		if (return_state != return_success)
		{
		  goto func_end;
		}

		return_state = CheckMonthDay(current_day);

		if (return_state != return_success)
		{
		  goto func_end;
		}

		return_state = CheckDate(current_year, current_month, current_day);

		if (return_state != return_success)
		{
		  goto func_end;
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
			 goto func_end;

		  }
		  else
		  {

			 return_state = return_success;
			 goto func_end;

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
			 goto func_end;

		  }
		 }
		}
		else
		{
		  goto func_end;
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
		goto func_end;
		break;
	 }
  }

func_end:
	return return_state;
}
unsigned long holidays_class::HolidayFind()
{
  return_state = return_success;

func_end:
	return return_state;
}
unsigned long holidays_class::HolidayAdd()
{
  return_state = return_success;

func_end:
	return return_state;
}
unsigned long holidays_class::HolidayDelete()
{
  return_state = return_success;

func_end:
	return return_state;
}

unsigned long holidays_class::GetHolidayBaseTotal(int *array_total)
{
	return_state = return_success;
	*array_total = holidaybasetotal;
	return return_state;

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

	return_state = return_success;
	*month_parm = current_month;
	return return_state;
}

unsigned long holidays_class::GetHolidayBaseDay(int element_count,
	char day_number_str[holidaybasedaylength])
{

	return_state = return_success;
	if (element_count == 0)
	{
	  strcpy(day_number_str, language_pick_day);
	}
	else
	{
	  _itoa((element_count ),day_number_str,10);
	}
	return return_state;
}

unsigned long holidays_class::GetCurrentBaseDay(	char *day_parm)
{

	return_state = return_success;
	*day_parm = current_day;
	return return_state;
}

unsigned long holidays_class::GetBaseAdjTotal(int *array_total)
{
	return_state = return_success;
	*array_total = holidaybaseadjtotal;
	return return_state;

}

unsigned long holidays_class::GetBaseAdj(int element_count,char name_str[holidaybaseadjlength])
{

	char *const holiday_base_adj_names[holidaybaseadjtotal] =
		{holiday_adj_names[event_sched_same_holiday_adj],
		holiday_adj_names[event_sched_next_holiday_adj],
		holiday_adj_names[event_sched_prev_holiday_adj]};

	return_state = return_success;

	strcpy(name_str, holiday_base_adj_names [element_count]);
	return return_state;
}
unsigned long holidays_class::GetBaseAdj(char *adj_parm)
{

	return_state = return_success;
	*adj_parm = current_base_adj;
	return return_state;
}

unsigned long holidays_class::GetBaseAdjTimesTotal(int *array_total)
{
	return_state = return_success;
	*array_total = holidaybaseadjtimestotal;
	return return_state;

}

unsigned long holidays_class::GetBaseAdjTimes(int element_count,
	char name_str[holidaybaseadjtimeslength])
{

	return_state = return_success;
	if (element_count == 0)
	{
	  strcpy(name_str, language_adjust_times);
	}
	else
	{
	  _itoa((element_count),name_str,10);
	}
	return return_state;
}
unsigned long holidays_class::GetBaseAdjTimes(char *adj_parm)
{

	return_state = return_success;
	*adj_parm = current_base_adj_times;
	return return_state;
}

unsigned long holidays_class::GetHolidayWeekdayTotal(int *array_total)
{
	return_state = return_success;
	*array_total = holidayweekdaytotal;
	return return_state;

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

	return_state = return_success;

	strcpy(name_str, holiday_weekday_names [element_count]);
	return return_state;
}
unsigned long holidays_class::GetHolidayWeekday(char *weekday_parm)
{

	return_state = return_success;
	*weekday_parm = current_holiday_weekday;
	return return_state;
}
unsigned long holidays_class::SetHolidayWeekday(char name_str[holidayweekdaylength])
{
	unsigned char weekday_code;

	return_state = return_success;

	return_state = CheckHolidayWeekday(name_str, &weekday_code);

	if (return_state != return_success)
	{
		goto func_end;
	}
	else
	{
	  current_holiday_weekday = weekday_code;
	}

func_end:
	return return_state;
}
unsigned long holidays_class::CheckHolidayWeekday(char name_str[holidayweekdaylength],
	unsigned char *weekday_code)
{
	char weekday_hold[holidayweekdaylength];
	unsigned long local_return;

	return_state = return_err_holiday_weekday_invalid;

	for(*weekday_code = 0;
		(*weekday_code < holidayweekdaytotal) && (return_state != return_success);
		*weekday_code = *weekday_code + 1)
	{
		local_return = holidays_class::GetHolidayWeekday(*weekday_code, weekday_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  goto func_end;
		}
		dummy_int = strcmp(name_str,weekday_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

func_end:
	return return_state;
}

unsigned long holidays_class::GetAdjustDirectionTotal(int *array_total)
{
	return_state = return_success;
	*array_total = adjustdirectiontotal;
	return return_state;

}

unsigned long holidays_class::GetAdjustDirection(int element_count,
	char name_str[adjustdirectionlength])
{

	char *const adjust_direction_names[adjustdirectiontotal] =
		{language_pick_direction,
		language_exact,
		language_after,
		language_before};

	return_state = return_success;

	strcpy(name_str, adjust_direction_names [element_count]);
	return return_state;
}
unsigned long holidays_class::GetAdjustDirection(char *direction_parm)
 {

	return_state = return_success;
	*direction_parm = current_adjust_direction;
	return return_state;
}
unsigned long holidays_class::SetAdjustDirection(char name_str[adjustdirectionlength])
{
	unsigned char direction_code;

	return_state = return_success;

	return_state = CheckAdjustDirection(name_str, &direction_code);

	if (return_state != return_success)
	{
		goto func_end;
	}
	else
	{
	  current_adjust_direction = direction_code;
	}

func_end:
	return return_state;
}
unsigned long holidays_class::CheckAdjustDirection(char name_str[adjustdirectionlength],
	unsigned char *direction_code)
{
	char direction_hold[adjustdirectionlength];
	unsigned long local_return;

	return_state = return_err_adjust_direction_invalid;

	for(*direction_code = 0;
		(*direction_code < adjustdirectiontotal) && (return_state != return_success);
		*direction_code = *direction_code + 1)
	{
		local_return = holidays_class::GetAdjustDirection(*direction_code, direction_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  goto func_end;
		}
		dummy_int = strcmp(name_str,direction_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

func_end:
	return return_state;
}

unsigned long holidays_class::GetDayAdjustTotal(int *array_total)
{
	return_state = return_success;
	*array_total = dayadjusttotal;
	return return_state;

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

	return_state = return_success;

	strcpy(name_str, day_adjust_names [element_count]);
	return return_state;
}
unsigned long holidays_class::GetDayAdjust(char *day_adjust_parm)
 {

	return_state = return_success;
	*day_adjust_parm = current_day_adjust;
	return return_state;
}
unsigned long holidays_class::SetDayAdjust(char name_str[dayadjustlength])
{
	unsigned char day_adjust_code;

	return_state = return_success;

	return_state = CheckDayAdjust(name_str, &day_adjust_code);

	if (return_state != return_success)
	{
		goto func_end;
	}
	else
	{
	  current_day_adjust = day_adjust_code;
	}

func_end:
	return return_state;
}
unsigned long holidays_class::CheckDayAdjust(char name_str[dayadjustlength],
	unsigned char *day_adjust_code)
{
	char day_adjust_hold[dayadjustlength];
	unsigned long local_return;

	return_state = return_err_day_adjust_invalid;

	for(*day_adjust_code = 0;
		(*day_adjust_code < dayadjusttotal) && (return_state != return_success);
		*day_adjust_code = *day_adjust_code + 1)
	{
		local_return = holidays_class::GetDayAdjust(*day_adjust_code, day_adjust_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  goto func_end;
		}
		dummy_int = strcmp(name_str,day_adjust_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

func_end:
	return return_state;
}

unsigned long holidays_class::GetBaseWeekdayTotal(int *array_total)
{
	return_state = return_success;
	*array_total = baseweekdaytotal;
	return return_state;

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

	return_state = return_success;

	strcpy(name_str, base_weekday_names [element_count]);
	return return_state;
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

	return_state = return_success;

	return_state = CheckBaseWeekday(name_str, &base_weekday_code);

	if (return_state != return_success)
	{
		goto func_end;
	}
	else
	{
	  current_base_weekday = base_weekday_code;
	}

func_end:
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
func_end:
	return return_state;
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
		  goto func_end;
		}
		dummy_int = strcmp(name_str,base_weekday_hold);
		if (dummy_int == 0)
		{

		  local_return = return_success;

		}
	}

func_end:
	return local_return;
}
unsigned long holidays_class::SetHolidayCode(char name_str[baseweekdaylength])
{
	return_state = return_success;

	dummy_size_t = strlen(name_str);

	if (dummy_size_t>=holidaycodelength)
	{
		return_state = return_err_holiday_code_too_big;
		goto func_end;
	}
	else
	{
	  dummy_int = strcmp(name_str,"");
	  if (dummy_int == 0)
	  {

		return_state = return_err_holiday_code_blank;
		goto func_end;

	  }
	  else
	  {
		 strcpy(holiday_code,name_str);
	  }
	}

func_end:
	return return_state;
}
unsigned long holidays_class::SetHolidayBase(char name_str[holidaybaselength])
{
	unsigned char base_code;

	return_state = return_success;

	return_state = CheckHolidayBase(name_str, &base_code);

	if (return_state != return_success)
	{
		goto func_end;
	}
	else
	{
	  current_base = base_code;
	}

func_end:
	return return_state;
}
unsigned long holidays_class::CheckHolidayBase(char name_str[holidaybaselength],
	unsigned char *base_code)
{
	char base_hold[holidaybaselength];
	unsigned long local_return;

	return_state = return_err_holiday_base_invalid;

	for(*base_code = 0;
		(*base_code < holidaybasetotal) && (return_state != return_success);
		*base_code = *base_code + 1)
	{
		local_return = holidays_class::GetHolidayBase(*base_code, base_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  goto func_end;
		}
		dummy_int = strcmp(name_str,base_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

func_end:
	*base_code = *base_code - 1;
	return return_state;
}
unsigned long holidays_class::SetHolidayMonth(char name_str[month_names_length])
{
	unsigned char month_code;

	return_state = return_success;

	return_state = CheckHolidayMonth(name_str, &month_code);

	if (return_state != return_success)
	{
		goto func_end;
	}
	else
	{
	  current_month = month_code;
	}

func_end:
	return return_state;
}
unsigned long holidays_class::CheckHolidayMonth(char name_str[month_names_length],
	unsigned char *month_code)
{
	char month_hold[month_names_length];
	unsigned long local_return;

	return_state = return_err_holiday_month_invalid;

	for(*month_code = 0;
		(*month_code < month_names_total) && (return_state != return_success);
		*month_code = *month_code + 1)
	{
		local_return = holidays_class::GetMonth(*month_code, month_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  goto func_end;
		}
		dummy_int = strcmp(name_str,month_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

func_end:
	*month_code = *month_code - 1;
	return return_state;
}
unsigned long holidays_class::SetHolidayYear(unsigned int base_year)
{

  return_state = CheckYear(base_year);

  if (return_state != return_success)
  {
	 goto func_end;
  }
  else
  {
	 current_year = base_year;
  }
func_end:
	return return_state;
}
unsigned long holidays_class::SetHolidayDay(char name_str[holidaybasedaylength])
{
	int day_code;

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
	 goto func_end;
	}
	 else
	{
	 current_day = day_code;
	}

func_end:
	return return_state;
}
unsigned long holidays_class::CheckHolidayDay(int day_code)
{

	return_state = return_err_holiday_day_invalid;

	if ((day_code > 0) && (day_code < 32) )
	{

		  return_state = return_success;

	}

func_end:
	return return_state;
}
unsigned long holidays_class::SetBaseAdj(char name_str[holidaybaseadjlength])
{
	unsigned char adj_code;

	return_state = return_success;

	return_state = CheckBaseAdj(name_str, &adj_code);

	if (return_state != return_success)
	{
		goto func_end;
	}
	else
	{
	  current_base_adj = adj_code;
	}

func_end:
	return return_state;
}
unsigned long holidays_class::CheckBaseAdj(char name_str[holidaybaseadjlength],
	unsigned char *adj_code)
{
	char adj_hold[holidaybaseadjlength];
	unsigned long local_return;

	return_state = return_err_holiday_base_adj_invalid;

	for(*adj_code = 0;
		(*adj_code < holidaybaseadjtotal) && (return_state != return_success);
		*adj_code = *adj_code + 1)
	{
		local_return = holidays_class::GetBaseAdj(*adj_code, adj_hold);
		if (local_return != return_success)
		{
		  return_state = local_return;
		  goto func_end;
		}
		dummy_int = strcmp(name_str,adj_hold);
		if (dummy_int == 0)
		{

		  return_state = return_success;

		}
	}

func_end:
	return return_state;
}
unsigned long holidays_class::SetBaseAdjTimes(char name_str[holidaybaseadjtimeslength])
{
	int adj_times_code;

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
		goto func_end;
	}
	else
	{
	  current_base_adj_times = adj_times_code;
	}

func_end:
	return return_state;
}
unsigned long holidays_class::CheckBaseAdjTimes(int adj_times_code)
{

	return_state = return_err_adj_times_invalid;

	if ((adj_times_code >= 0) && (adj_times_code <= holidaybaseadjtimestotal) )
	{

		  return_state = return_success;

	}

func_end:
	return return_state;
}
unsigned long holidays_class::SetHolidayAdjTimes(char name_str[holidayadjtimeslength])
{
	return_state = return_success;

	dummy_size_t = strlen(name_str);

	if (dummy_size_t>=holidayadjtimeslength)
	{
		return_state = return_err_holiday_adj_times_too_big;
		goto func_end;
	}
	else
	{
	  dummy_int = atoi(name_str);

	  if (current_adjust_direction == adjustdirection_exact)
	  {
		 if (dummy_int == 0)
		 {

			return_state = return_err_holiday_adj_times_blank;
			goto func_end;

		 }
		 else
		 {
			current_holiday_adj_times = dummy_int;
			strcpy(holiday_code,name_str);
		 }
	  }
	}

func_end:
	return return_state;
}

unsigned long holidays_class::AddHoliday()
{
	unsigned long local_return;
	local_return = return_success;

	if ((holiday_date_count + 1) > (holiday_date_max))
	{
	}
	else
	{

	  dummy_size_t = holidaycodelength;
	  memcpy(holiday_date_array[holiday_date_count].code,
				holiday_code,
				dummy_size_t);
	  holiday_date_array[holiday_date_count].centuries = current_year / 100;
	  holiday_date_array[holiday_date_count].years = current_year % 100;
	  holiday_date_array[holiday_date_count].months = current_month;
	  holiday_date_array[holiday_date_count].days = current_day;
	  holiday_date_count++;

	}

func_end:
	return local_return;
}
unsigned long holidays_class::TestHoliday()
{
	unsigned long local_return;
	int local_dummy_int;
	local_return = return_success;

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
func_end:
	return local_return;
}

unsigned long holidays_class::settestdate(char test_date[date_string_size])
{
	unsigned long local_return;
	local_return = return_success;
func_end:
	return local_return;
}







