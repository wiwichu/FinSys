// RateCurve.cpp: implementation of the CRateCurve class.
//
//////////////////////////////////////////////////////////////////////

//#include "gencalcmfc.h"
#include "stdafx.h"
#include "RateCurve.h"
#include "errdecs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifndef _ANSIC

_RATECURVE CRateCurve()
{
	char dummy_char;
	char RateInstrText[rc_max_instr] [RateInstrTextSize];
	Source_State = enabled_yes;
	Type_State = enabled_yes;
	Term1_State = enabled_yes;
	Term2_State = enabled_yes;
	Unit_State = enabled_yes;
	Frequency_State = enabled_yes;
	DayCount_State = enabled_yes;
	EOM_State = enabled_yes;
	Rate_State = enabled_yes;
	SetRCTypeDefaults(rc_mm_type);
	SetRCSource(RateInstrText,rc_custom_source_name,&dummy_char);

//	InstrArray = (RateInstr *) malloc(sizeof(RateInstr));
	InstrCount = 0;
	BootCount = 0;

	rc_date_format = date_format_1;
}

_RATECURVE ~CRateCurve()
{

	free(InstrArray);

}

#endif

unsigned long _RATECURVE InitTypeNames(char parm_list [ rc_type_count ] [ rc_type_name_size ])
{
unsigned long return_state = return_success;
int element_count;

	for (element_count = 0; element_count <
		rc_type_count; ++element_count)
	{

	  strcpy_s(parm_list[element_count],
		 rc_type_names[element_count]);
	}


return return_state;

}

unsigned long  _RATECURVE InitSourceNames(char parm_list [ rc_source_count ] [ rc_source_name_size ])
{
unsigned long return_state = return_success;
int element_count;

	for (element_count = 0; element_count <
		rc_source_count; ++element_count)
	{

	  strcpy_s(parm_list[element_count],
		 rc_source_names[element_count]);
	}


return return_state;
}

unsigned long  _RATECURVE InitUnitNames(char parm_list [ rc_unit_count ] [ rc_unit_name_size ])
{
unsigned long return_state = return_success;
int element_count;

	for (element_count = 0; element_count <
		rc_unit_count; ++element_count)
	{

	  strcpy(parm_list[element_count],
		 rc_unit_names[element_count]);
	}


return return_state;
}

unsigned long  _RATECURVE InitFreqNames(char parm_list [ freq_count ] [ freq_names_len ])
{
unsigned long return_state = return_success;
int element_count;

	for (element_count = 0; element_count <
		freq_count; ++element_count)
	{

	  strcpy(parm_list[element_count],
		 freq_names[element_count]);
	}


return return_state;
}

unsigned long  _RATECURVE InitDayCountNames(char parm_list [ date_last_day_count ] [ day_count_names_len ])
{
unsigned long return_state = return_success;
int element_count;

	for (element_count = 0; element_count <
		date_last_day_count; ++element_count)
	{

	  strcpy(parm_list[element_count],
		 day_count_names[element_count]);
	}


return return_state;
}

unsigned long  _RATECURVE InitEOMNames(char parm_list [ monthend_count ] [ monthend_names_len ])
{
unsigned long return_state = return_success;
int element_count;

	for (element_count = 0; element_count <
		monthend_count; ++element_count)
	{

	  strcpy(parm_list[element_count],
		 monthend_names[element_count]);
	}


return return_state;
}

unsigned long  _RATECURVE InitDayAdjustNames(char parm_list [ rc_dayadjust_count ] [holiday_adj_names_len ])
{
unsigned long return_state = return_success;
int element_count;

	for (element_count = 0; element_count <
		rc_dayadjust_count; ++element_count)
	{

	  strcpy(parm_list[element_count],
		 rc_dayadjust_names[element_count]);
	}


return return_state;
}

unsigned long _RATECURVE SetRCType(char RC_Type [rc_type_name_size])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(compare_result = 1; 
		(compare_result != 0) && (element_count < rc_type_count);
		++element_count)
	{

	  compare_result = strcmp(RC_Type,
		 rc_type_names[element_count]);
	}

	--element_count;

	if (compare_result == 0)
	{
		CurrentInstr.type = rc_types[element_count];
		return_state = SetRCTypeDefaults(CurrentInstr.type);
	}
	else
	{
		return_state = return_err_invalid_rc_type;
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCType(char RC_Type [rc_type_name_size])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(CurrentInstr.type != rc_types[element_count]) && 
			(element_count < rc_type_count);
		++element_count)
	{
	}

	if (element_count >= rc_type_count)
	{
		return_state = return_err_invalid_rc_type;
	}
	else
	{
		element_count;
		strcpy(RC_Type,rc_type_names[element_count]);
	
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCSource(char RateInstrTextParm[rc_max_instr] [RateInstrTextSize],
				char RC_Source[rc_source_name_size],char *TotalInstrParm)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(compare_result = 1; 
		(compare_result != 0) && (element_count < rc_source_count);
		++element_count)
	{

	  compare_result = strcmp(RC_Source,
		 rc_source_names[element_count]);
	}

	if (compare_result == 0)
	{
		return_state = return_success;
		--element_count;
		CurrentSource = rc_sources[element_count];
	}
	else
	{
		return_state = return_err_invalid_rc_source;
	}

	/* Load the Rate Curve for the hard coded examples.*/

	if (CurrentSource == rc_handle_source)
	{

		InstrArray[0].type = rc_mm_type;
   		InstrArray[0].term_1 = 1;
   		InstrArray[0].term_2 = 0;
   		InstrArray[0].unit = rc_days_unit;
   		InstrArray[0].frequency = frequency_annually;
   		InstrArray[0].day_count = date_act_360_day_count;
   		InstrArray[0].eom = monthend_no;
   		InstrArray[0].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[0].rate = .054;

		InstrArray[1].type = rc_mm_type;
   		InstrArray[1].term_1 = 1;
   		InstrArray[1].term_2 = 0;
   		InstrArray[1].unit = rc_weeks_unit;
   		InstrArray[1].frequency = frequency_annually;
   		InstrArray[1].day_count = date_act_360_day_count;
   		InstrArray[1].eom = monthend_no;
   		InstrArray[1].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[1].rate = .0556;

		InstrArray[2].type = rc_mm_type;
   		InstrArray[2].term_1 = 1;
   		InstrArray[2].term_2 = 0;
   		InstrArray[2].unit = rc_months_unit;
   		InstrArray[2].frequency = frequency_annually;
   		InstrArray[2].day_count = date_act_360_day_count;
   		InstrArray[2].eom = monthend_no;
   		InstrArray[2].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[2].rate = .05525;

		InstrArray[3].type = rc_mm_type;
   		InstrArray[3].term_1 = 2;
   		InstrArray[3].term_2 = 0;
   		InstrArray[3].unit = rc_months_unit;
   		InstrArray[3].frequency = frequency_annually;
   		InstrArray[3].day_count = date_act_360_day_count;
   		InstrArray[3].eom = monthend_no;
   		InstrArray[3].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[3].rate = .05525;

		InstrArray[4].type = rc_mm_type;
   		InstrArray[4].term_1 = 3;
   		InstrArray[4].term_2 = 0;
   		InstrArray[4].unit = rc_months_unit;
   		InstrArray[4].frequency = frequency_annually;
   		InstrArray[4].day_count = date_act_360_day_count;
   		InstrArray[4].eom = monthend_no;
   		InstrArray[4].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[4].rate = .05525;

		InstrArray[5].type = rc_mm_type;
   		InstrArray[5].term_1 = 6;
   		InstrArray[5].term_2 = 0;
   		InstrArray[5].unit = rc_months_unit;
   		InstrArray[5].frequency = frequency_annually;
   		InstrArray[5].day_count = date_act_360_day_count;
   		InstrArray[5].eom = monthend_no;
   		InstrArray[5].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[5].rate = .0556;

		InstrArray[6].type = rc_mm_type;
   		InstrArray[6].term_1 = 9;
   		InstrArray[6].term_2 = 0;
   		InstrArray[6].unit = rc_months_unit;
   		InstrArray[6].frequency = frequency_annually;
   		InstrArray[6].day_count = date_act_360_day_count;
   		InstrArray[6].eom = monthend_no;
   		InstrArray[6].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[6].rate = .0556;

		InstrArray[7].type = rc_mm_type;
   		InstrArray[7].term_1 = 12;
   		InstrArray[7].term_2 = 0;
   		InstrArray[7].unit = rc_months_unit;
   		InstrArray[7].frequency = frequency_annually;
   		InstrArray[7].day_count = date_act_360_day_count;
   		InstrArray[7].eom = monthend_no;
   		InstrArray[7].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[7].rate = .0559;

		InstrArray[8].type = rc_swap_type;
   		InstrArray[8].term_1 = 2;
   		InstrArray[8].term_2 = 0;
   		InstrArray[8].unit = rc_years_unit;
   		InstrArray[8].frequency = frequency_annually;
   		InstrArray[8].day_count = date_act_360_day_count;
   		InstrArray[8].eom = monthend_no;
   		InstrArray[8].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[8].rate = .05635;

		InstrArray[9].type = rc_swap_type;
   		InstrArray[9].term_1 = 3;
   		InstrArray[9].term_2 = 0;
   		InstrArray[9].unit = rc_years_unit;
   		InstrArray[9].frequency = frequency_annually;
   		InstrArray[9].day_count = date_act_360_day_count;
   		InstrArray[9].eom = monthend_no;
   		InstrArray[9].day_adjust = event_sched_np_holiday_adj;
   		InstrArray[9].rate = .05665;

		InstrCount = 10;
	}
	else
	{

		InstrCount = 0;
	}

	return_state = SetRCInstrText( InstrArray,
							RateInstrTextParm, 
							InstrCount);

	if (return_state != return_success)
	{

		goto end_func; 
	}

end_func:

	*TotalInstrParm = InstrCount;
	return return_state;

}

unsigned long _RATECURVE GetRCSource(char RC_Source [rc_source_name_size])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(CurrentSource != rc_sources[element_count]) && 
			(element_count < rc_source_count);
		++element_count)
	{
	}

	if (element_count >= rc_source_count)
	{
		return_state = return_err_invalid_rc_source;
	}
	else
	{

		--element_count;
		strcpy(RC_Source,rc_source_names[element_count]);
	
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCUnit(char RC_Unit[rc_unit_name_size])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(compare_result = 1; 
		(compare_result != 0) && (element_count < rc_unit_count);
		element_count++)
	{

	  compare_result = strcmp(RC_Unit,
		 rc_unit_names[element_count]);
	}

	if (compare_result == 0)
	{
		return_state = return_success;
		--element_count;
		CurrentInstr.unit = rc_units[element_count];
	}
	else
	{
		return_state = return_err_invalid_rc_unit;
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCTerm1(unsigned short RC_Term1)
{

	unsigned long return_state = return_success;
	CurrentInstr.term_1 = RC_Term1;

//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCTerm2(unsigned short RC_Term2)
{

	unsigned long return_state = return_success;
	CurrentInstr.term_2 = RC_Term2;

//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCRate1(long double RC_Rate1)
{

	unsigned long return_state = return_success;
	CurrentInstr.rate = RC_Rate1/100;

//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCUnit(char RC_Unit [rc_unit_name_size])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(CurrentInstr.unit != rc_units[element_count]) && 
			(element_count < rc_unit_count);
		++element_count)
	{
	}

	if (element_count >= rc_unit_count)
	{
		return_state = return_err_invalid_rc_unit;
	}
	else
	{

		strcpy(RC_Unit,rc_unit_names[element_count]);
	
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCFrequency(char RC_Frequency [freq_names_len])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(CurrentInstr.frequency != frequency_list[element_count]) && 
			(element_count < freq_count);
		++element_count)
	{
	}

	if (element_count >= freq_count)
	{
		return_state = return_err_invalid_pay_freq;
	}
	else
	{

		strcpy(RC_Frequency,freq_names[element_count]);
	
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCDayAdjust(char RC_DayAdjust [holiday_adj_names_len])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(CurrentInstr.day_adjust != rc_dayadjusts[element_count]) && 
			(element_count < rc_dayadjust_count);
		++element_count)
	{
	}

	if (element_count >= rc_dayadjust_count)
	{
		return_state = return_err_invalid_pay_freq;
	}
	else
	{

		strcpy(RC_DayAdjust,rc_dayadjust_names[element_count]);
	
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCEOM(char RC_EOM [monthend_names_len])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(CurrentInstr.eom != monthends[element_count]) && 
			(element_count < monthend_count);
		++element_count)
	{
	}

	if (element_count >= monthend_count)
	{
		return_state = return_err_inval_monthend;
	}
	else
	{

		strcpy(RC_EOM,monthend_names[element_count]);
	
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCDayCount(char RC_DayCount [day_count_names_len])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	unsigned int element_count = 0;

	for(element_count = 0;
		(CurrentInstr.day_count != day_counts[element_count]) && 
			(element_count < date_last_day_count);
		++element_count)
	{
	}

	if (element_count >= date_last_day_count)
	{
		return_state = return_err_inv_day_count;
	}
	else
	{

		strcpy(RC_DayCount,day_count_names[element_count]);
	
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCDayCount(char RC_DayCount[day_count_names_len])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(compare_result = 1; 
		(compare_result != 0) && (element_count < date_last_day_count);
		++element_count)
	{

	  compare_result = strcmp(RC_DayCount,
		 day_count_names[element_count]);
	}

	if (compare_result == 0)
	{
		return_state = return_success;
		--element_count;
		CurrentInstr.day_count = day_counts[element_count];
	}
	else
	{
		return_state = return_err_inv_day_count;
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCEOM(char RC_EOM[monthend_names_len])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(compare_result = 1; 
		(compare_result != 0) && (element_count < monthend_count);
		++element_count)
	{

	  compare_result = strcmp(RC_EOM,
		 monthend_names[element_count]);
	}

	if (compare_result == 0)
	{
		return_state = return_success;
		--element_count;
		CurrentInstr.eom = monthends[element_count];
	}
	else
	{
		return_state = return_err_inval_monthend;
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCDayAdjust(char RC_DayAdjust[holiday_adj_names_len])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(compare_result = 1; 
		(compare_result != 0) && (element_count < rc_dayadjust_count);
		++element_count)
	{

	  compare_result = strcmp(RC_DayAdjust,
		 rc_dayadjust_names[element_count]);
	}

	if (compare_result == 0)
	{
		return_state = return_success;
		--element_count;
		CurrentInstr.day_adjust = rc_dayadjusts[element_count];
	}
	else
	{
		return_state = return_err_invalid_holiday_adj;
	}


//end_func:
	return return_state;

}

unsigned long _RATECURVE SetRCFrequency(char RC_Frequency[freq_names_len])
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(compare_result = 1; 
		(compare_result != 0) && (element_count < freq_count);
		++element_count)
	{

	  compare_result = strcmp(RC_Frequency,
		 freq_names[element_count]);
	}

	if (compare_result == 0)
	{
		return_state = return_success;
		--element_count;
		CurrentInstr.frequency = frequency_list[element_count];
	}
	else
	{
		return_state = return_err_invalid_pay_freq;
	}


//end_func:
	return return_state;

}



unsigned long _RATECURVE SetRCTypeDefaults(char Type_Parm)
{

	unsigned long return_state = return_success;

	return_state = SetRCTerm1(0);
	if (return_state)
	{
		goto func_end;
	}
	return_state = SetRCTerm2(0);

	if (return_state)
	{
		goto func_end;
	}
	
	switch(Type_Parm)
	{
		case rc_mm_type:
		{

			CurrentInstr.type = rc_mm_type;
			return_state = SetRCUnit(rc_days_unit_name);

			if (return_state)
			{
				goto func_end;

			}
			return_state = SetRCDayCount(date_act_360_day_count_name);

			if (return_state)
			{
				goto func_end;

			}
			return_state = SetRCEOM(monthend_no_name);

			if (return_state)
			{
				goto func_end;

			}
			return_state = SetRCDayAdjust(event_sched_np_holiday_adj_name);

			if (return_state)
			{
				goto func_end;

			}
			return_state = SetRCFrequency(frequency_annually_name);

			if (return_state)
			{
				goto func_end;

			}

			Term2_State = enabled_no;
			Frequency_State = enabled_no;

			break;
		}
		case rc_swap_type:
		{

			CurrentInstr.type = rc_swap_type;
			return_state = SetRCUnit(rc_years_unit_name);

			if (return_state)
			{
				goto func_end;

			}
			return_state = SetRCDayCount(date_act_360_day_count_name);

			if (return_state)
			{
				goto func_end;

			}
			return_state = SetRCEOM(monthend_no_name);

			if (return_state)
			{
				goto func_end;

			}
			return_state = SetRCDayAdjust(event_sched_np_holiday_adj_name);

			if (return_state)
			{
				goto func_end;

			}
			return_state = SetRCFrequency(frequency_annually_name);

			if (return_state)
			{
				goto func_end;

			}

			Term2_State = enabled_no;
			Frequency_State = enabled_yes;

			break;
		}
		case rc_fra_type:
		case rc_irf_type:
		case rc_bond_type:
		{

			Term2_State = enabled_yes;
			Frequency_State = enabled_yes;
			return_state = return_err_not_supported;

			break;
		}
		default:
		{
			return_state = return_err_invalid_rc_type;
			break;
		}

	}

func_end:

	return return_state;

}

unsigned long _RATECURVE GetRCTypeState(char *RC_TypeState)
{

	unsigned long return_state = return_success;

	*RC_TypeState = Type_State;

//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCTerm2State(char *RC_Term2State)
{

	unsigned long return_state = return_success;

	*RC_Term2State = Term2_State;

//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCFrequencyState(char *RC_FrequencyState)
{

	unsigned long return_state = return_success;

	*RC_FrequencyState = Frequency_State;

//end_func:
	return return_state;

}

unsigned long _RATECURVE  AddRCInstr(	char RateInstrTextParm[rc_max_instr] [RateInstrTextSize], char *TotalInstr)
{

	unsigned long return_state = return_success;
	int element_count = 0;

	char RateInstrTextArray[rc_max_instr][RateInstrTextSize];
/*
	InstrArray = (RateInstr *)realloc(InstrArray,(sizeof(RateInstr) * (InstrCount + 1)));

	if (InstrArray == NULL)
	{

		return_state = return_err_ins_mem;
	
	}
	else
	{
//		RateInstrTextArray =   calloc( size_t(InstrCount),size_t(RateInstrTextSize));



		if (RateInstrTextArray == NULL)
		{

			return_state = return_err_ins_mem;
	
		}
		else
		{
*/	

		if (InstrCount < rc_max_instr)
		{
			return_state = CheckRCInstr(CurrentInstr);

			if (return_state != return_success)
			{

				goto end_func; 
			}

			/*{Check that there is not another instrument with matching terms}*/

			for(element_count = 0; 
				(element_count < InstrCount) &&
				(	(CurrentInstr.type != InstrArray[element_count].type)
					||(CurrentInstr.term_1 != InstrArray[element_count].term_1)
					||(CurrentInstr.unit != InstrArray[element_count].unit)
				); 
				element_count++)
			{
			}

			if (element_count != InstrCount)
			{
				return_state = return_err_rc_duplicate_terms;
				goto end_func; 
			}

			++InstrCount;

			InstrArray[InstrCount - 1] = CurrentInstr;

			*TotalInstr = InstrCount;

			return_state = SetRCInstrText( InstrArray,
							RateInstrTextArray, 
							*TotalInstr);

			if (return_state != return_success)
			{

				goto end_func; 
			}

			for(element_count = 0; element_count < *TotalInstr; ++element_count)
			{
				strcpy(RateInstrTextParm[element_count],RateInstrTextArray[element_count]);	
			}
		}
		else
		{

			return_state = return_err_rc_max_instr;
			goto end_func;
		
		}
//		}
//	}

end_func:
	return return_state;
}

unsigned long  _RATECURVE  SetRCInstrText(RateInstr * InstrArrayParm,
							char RateInstrTextParm[rc_max_instr][RateInstrTextSize], 
							char TotalInstr)
{

	char RC_Type [rc_type_name_size];
	char RC_Unit [rc_unit_name_size];
	char RC_Term1 [rc_term_size];
	char RC_Term2 [rc_term_size];
	char RC_Freq [freq_names_len];
	char RC_DayCount [day_count_names_len];
	char RC_EOM [monthend_names_len];
	char RC_DayAdjust [holiday_adj_names_len];
	char RC_Rate1 [rc_rate_size];
	unsigned long return_state = return_success;
	int element_count = 0;


	for(element_count = 0; element_count < TotalInstr; ++element_count)
	{

		return_state = GetRCTypeLocal(RC_Type,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcpy(RateInstrTextParm[element_count],RC_Type);
		strcat(RateInstrTextParm[element_count]," ");

		return_state = GetRCTerm1Local(RC_Term1,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcat(RateInstrTextParm[element_count],RC_Term1);
		strcat(RateInstrTextParm[element_count]," ");

		return_state = GetRCTerm2Local(RC_Term2,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcat(RateInstrTextParm[element_count],RC_Term2);
		strcat(RateInstrTextParm[element_count]," ");

		return_state = GetRCUnitLocal(RC_Unit,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcat(RateInstrTextParm[element_count],RC_Unit);
		strcat(RateInstrTextParm[element_count]," ");

		return_state = GetRCFreqLocal(RC_Freq,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcat(RateInstrTextParm[element_count],RC_Freq);
		strcat(RateInstrTextParm[element_count]," ");

		return_state = GetRCDayCountLocal(RC_DayCount,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcat(RateInstrTextParm[element_count],RC_DayCount);
		strcat(RateInstrTextParm[element_count]," ");

 		return_state = GetRCEOMLocal(RC_EOM,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcat(RateInstrTextParm[element_count],RC_EOM);
		strcat(RateInstrTextParm[element_count]," ");

 		return_state = GetRCDayAdjustLocal(RC_DayAdjust,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcat(RateInstrTextParm[element_count],RC_DayAdjust);
		strcat(RateInstrTextParm[element_count]," ");

 		return_state = GetRCRate1Local(RC_Rate1,InstrArrayParm[element_count]);

		if (return_state)
		{
	
			goto end_func;	
	
		}
		
		strcat(RateInstrTextParm[element_count],RC_Rate1);
		strcat(RateInstrTextParm[element_count]," ");
	}
end_func:
	return return_state;

}

unsigned long  _RATECURVE   GetRCTypeLocal(char RC_Type [rc_type_name_size], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(LocalRateInstr.type != rc_types[element_count]) && 
			(element_count < rc_type_count);
		++element_count)
	{
	}

	if (element_count >= rc_type_count)
	{
		return_state = return_err_invalid_rc_type;
	}
	else
	{
		strcpy(RC_Type,rc_type_names[element_count]);
	
	}


//end_func:
	return return_state;
}

unsigned long  _RATECURVE   GetRCUnitLocal(char RC_Unit [rc_type_name_size], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(LocalRateInstr.unit != rc_units[element_count]) && 
			(element_count < rc_unit_count);
		++element_count)
	{
	}

	if (element_count >= rc_unit_count)
	{
		return_state = return_err_invalid_rc_type;
	}
	else
	{
		strcpy(RC_Unit,rc_unit_names[element_count]);
	
	}


//end_func:
	return return_state;
}

unsigned long  _RATECURVE   GetRCTerm1Local(char RC_Term1 [rc_term_size], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	_itoa( LocalRateInstr.term_1, RC_Term1, 10 );

//end_func:
	return return_state;
}




unsigned long  _RATECURVE   GetRCTerm2Local(char RC_Term2 [rc_term_size], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	_itoa( LocalRateInstr.term_2, RC_Term2, 10 );

//end_func:
	return return_state;
}

unsigned long  _RATECURVE   GetRCRate1Local(char RC_Rate1 [rc_rate_size], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;
//	int decimal_place;
//	int sign_int;

//	utilgcvt( (LocalRateInstr.rate * 100), rate_precision, RC_Rate1 );
	_gcvt( (LocalRateInstr.rate * 100), rate_precision, RC_Rate1 );

//end_func:
	return return_state;
}




unsigned long  _RATECURVE   GetRCFreqLocal(char RC_Freq [freq_names_len], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(LocalRateInstr.frequency != frequency_list[element_count]) && 
			(element_count < freq_count);
		++element_count)
	{
	}

	if (element_count >= freq_count)
	{
		return_state = return_err_invalid_pay_freq;
	}
	else
	{
		strcpy(RC_Freq,freq_names[element_count]);
	
	}


//end_func:
	return return_state;
}






unsigned long  _RATECURVE   GetRCDayCountLocal(char RC_DayCount [day_count_names_len], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(LocalRateInstr.day_count != day_counts[element_count]) && 
			(element_count < date_last_day_count);
		++element_count)
	{
	}

	if (element_count >= date_last_day_count)
	{
		return_state = return_err_inv_day_count;
	}
	else
	{
		strcpy(RC_DayCount,day_count_names[element_count]);
	
	}


//end_func:
	return return_state;
}

unsigned long  _RATECURVE   GetRCEOMLocal(char RC_EOM [monthend_names_len], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(LocalRateInstr.eom != monthends[element_count]) && 
			(element_count < monthend_count);
		++element_count)
	{
	}

	if (element_count >= rc_unit_count)
	{
		return_state = return_err_inval_monthend;
	}
	else
	{
		strcpy(RC_EOM,monthend_names[element_count]);
	
	}


//end_func:
	return return_state;
}

unsigned long   _RATECURVE GetRCDayAdjustLocal(char RC_DayAdjust [holiday_adj_names_len], RateInstr LocalRateInstr)
{

	unsigned long return_state = return_success;
	int compare_result = 1;
	int element_count = 0;

	for(element_count = 0;
		(LocalRateInstr.day_adjust != rc_dayadjusts[element_count]) && 
			(element_count < rc_dayadjust_count);
		++element_count)
	{
	}

	if (element_count >= rc_dayadjust_count)
	{
		return_state = return_err_invalid_holiday_adj;
	}
	else
	{
		strcpy(RC_DayAdjust,rc_dayadjust_names[element_count]);
	
	}


//end_func:
	return return_state;
}


unsigned long   _RATECURVE SelectRCInstr(int InstrParm)
{

	unsigned long return_state = return_success;

	if (InstrParm >= InstrCount)
	{
		return_state = return_err_rc_max_instr;
	}
	else
	{
		CurrentInstr = InstrArray[InstrParm];
		CurrentIndex = InstrParm;
	}

//end_func:
	return return_state;
}

unsigned long   _RATECURVE RemoveRCInstr(int InstrParm)
{

	unsigned long return_state = return_success;
	int element_count;

	if (InstrParm >= InstrCount)
	{
		return_state = return_err_rc_max_instr;
	}
	else
	{
		for (element_count = InstrParm;
		element_count < InstrCount;
		++element_count)
		{

			InstrArray[element_count] = 
				InstrArray[element_count + 1];

		}

		CurrentInstr = InstrArray[0];
		CurrentIndex = 0;
		InstrCount--;

	}

//end_func:
	return return_state;
}



unsigned long _RATECURVE GetRCTerm1(unsigned short *RC_Term1 )
{

	unsigned long return_state = return_success;
	*RC_Term1 = CurrentInstr.term_1;

//end_func:
	return return_state;

}

unsigned long _RATECURVE GetRCTerm2(unsigned short *RC_Term2 )
{

	unsigned long return_state = return_success;
	*RC_Term2 = CurrentInstr.term_2;

//end_func:
	return return_state;

}

unsigned long _RATECURVE  GetRCRate1(long double *RC_Rate1 )
{

	unsigned long return_state = return_success;
	*RC_Rate1 = CurrentInstr.rate;

//end_func:
	return return_state;

}

unsigned long _RATECURVE DeleteRCInstr(int Instr_Selection )
{

	int element_count;
	unsigned long return_state = return_success;

	if (Instr_Selection >= InstrCount)
	{
		return_state = return_err_rc_max_instr;
		goto end_func;
	}

	for (element_count = Instr_Selection + 1; 
		element_count < InstrCount;
		++element_count)
	{

		InstrArray[element_count - 1] = InstrArray[element_count];	

	}

	if (--InstrCount > 0)
	{
		CurrentInstr = InstrArray[InstrCount - 1];	
		CurrentIndex = InstrCount - 1;
	}

end_func:
	return return_state;
}

unsigned long  _RATECURVE GetRCInstrText(char RateInstrTextParm[rc_max_instr][RateInstrTextSize], char *TotalInstr)
{
		unsigned long return_state = return_success;

		return_state = SetRCInstrText( InstrArray,
							RateInstrTextParm, 
							InstrCount);

		if (return_state != return_success)
		{
			goto end_func; 
		}

		*TotalInstr = InstrCount;

end_func:
	return return_state;

}

unsigned long _RATECURVE CheckRCInstr(RateInstr InstrParm)
{
	unsigned long return_state = return_success;
	
	switch(InstrParm.type)
	{
		case rc_mm_type:
		case rc_swap_type:
		{

			if (InstrParm.term_1 <= 0)
			{
				return_state = return_err_rc_term1_le_zero;
				goto end_func;
			}
			
			return_state = CheckRCUnit(InstrParm.unit);
			if (return_state != return_success)
			{
				goto end_func;
			}
			
			return_state = CheckRCFreq(InstrParm.frequency);
			if (return_state != return_success)
			{
				goto end_func;
			}
			
			return_state = CheckRCDayCount(InstrParm.day_count);
			if (return_state != return_success)
			{
				goto end_func;
			}
			
			return_state = CheckRCEOM(InstrParm.eom);
			if (return_state != return_success)
			{
				goto end_func;
			}
			
			return_state = CheckRCDayAdjust(InstrParm.day_adjust);
			if (return_state != return_success)
			{
				goto end_func;
			}

			if (InstrParm.rate < 0)
			{
				return_state = return_err_rc_rate_lt_zero;
				goto end_func;
			}
			break;
		}
		case rc_fra_type:
		case rc_irf_type:
		case rc_bond_type:
		{

			return_state = return_err_not_supported;
			goto end_func;
			break;
		}
		default:
		{
			return_state = return_err_invalid_rc_type;
			goto end_func;
			break;
		}

	}

end_func:
	return return_state;

}

unsigned long _RATECURVE CheckRCUnit(char UnitParm)
{
		unsigned long return_state = return_success;
	
	switch(UnitParm)
	{
		case	rc_days_unit:
		case	rc_weeks_unit:
		case	rc_months_unit:
		case	rc_years_unit:
		{
			break;
		}
		default:
		{
			return_state = return_err_invalid_rc_unit;
			break;
		}

	}

//end_func:
	return return_state;

}

unsigned long _RATECURVE CheckRCFreq(char FreqParm)
{
	unsigned long return_state = return_success;
	int element_count;

	for(element_count = 0;
		(FreqParm != frequency_list[element_count]) && 
			(element_count < freq_count);
		++element_count)
	{
	}

	if (element_count >= freq_count)
	{
		return_state = return_err_invalid_pay_freq;
		goto end_func;
	
	}

end_func:
	return return_state;

}



unsigned long _RATECURVE CheckRCDayCount(unsigned char DayCountParm)
{
	unsigned long return_state = return_success;
	int element_count;

	for(element_count = 0;
		(DayCountParm != day_counts[element_count]) && 
			(element_count < date_last_day_count);
		++element_count)
	{
	}

	if (element_count >= date_last_day_count)
	{
		return_state = return_err_inv_day_count;
	}

//end_func:
	return return_state;

}



unsigned long _RATECURVE CheckRCEOM(char EOMParm)
{
	unsigned long return_state = return_success;
	int element_count;

	for(element_count = 0;
		(CurrentInstr.eom != monthends[element_count]) && 
			(element_count < monthend_count);
		++element_count)
	{
	}

	if (element_count >= monthend_count)
	{
		return_state = return_err_inval_monthend;
	}

//end_func:
	return return_state;

}




unsigned long _RATECURVE CheckRCDayAdjust(char DayAdjustParm)
{
	unsigned long return_state = return_success;
	int element_count;

	for(element_count = 0;
		(CurrentInstr.day_adjust != rc_dayadjusts[element_count]) && 
			(element_count < rc_dayadjust_count);
		++element_count)
	{
	}

	if (element_count >= rc_dayadjust_count)
	{
		return_state = return_err_invalid_pay_freq;
	}

//end_func:
	return return_state;

}



unsigned long _RATECURVE SetRCValDate(char ValDate[rc_date_len])
{
	unsigned long return_state = return_success;
	double work_double;

	return_state = dateconv(rc_date_format, dateconv_string_to_union,
		ValDate, &RCValDate, &work_double);

//end_func:
	return return_state;

}


unsigned long _RATECURVE  GetRCBootDiscText(char BootTextParm[rc_max_boot_results][BootTextSize],
											char *TotalBoot
											,const set<string> &holiSet
											)
{
	unsigned long return_state = return_success;
	char DateHold[rc_date_len];
	char BootFactor[rc_boot_factor_size];
	double work_double;
	int element_count;

	return_state = RCBootDisc(RCValDate,InstrArray,InstrCount, 
						 BootResultArray, 
						holiSet,
						 &BootCount);

	if (return_state != return_success)
	{
		goto end_func;
	}

	*TotalBoot = BootCount;

	for(element_count = 0; element_count < BootCount; ++element_count)
	{

		return_state = dateconv(rc_date_format, dateconv_union_to_string,
			DateHold, &BootResultArray[element_count].date, &work_double);

		if (return_state != return_success)
		{
			goto end_func;
		}
		
		strcpy(BootTextParm[element_count],DateHold);
		strcat(BootTextParm[element_count]," ");

//		utilgcvt( BootResultArray[element_count].factor, factor_precision, BootFactor);
		_gcvt( BootResultArray[element_count].factor, factor_precision, BootFactor);
		
		strcat(BootTextParm[element_count],BootFactor);
		strcat(BootTextParm[element_count]," ");

	}

end_func:
	return return_state;

}

unsigned long _RATECURVE  RCBootDisc(date_union ValueDate,
						 RateInstr * InstrArrayParm,
						 char TotalInstr, 
						 BootResult *BootArrayParm, 
						const set<string> &holiSet,
						 char *TotalBoot)
{
	unsigned long return_state = return_success;
	int element_count;
	int sub_count;
	int period_count;
	int comp_result;
	int months_local = 0;
	long days_local = 0;
	long dummy_long = 0;
	long double dummy_ld;
	long double factor_sum;
	long double period_factor;
	unsigned int dummy_ui;

//	char holiday_code[3];
	unsigned int holi_chan = 0;
//	holidays_struct holi_parm [1];
	instr in_instr_parm;
	py_parms py_parm_parm;
	redemps_struc redemps_array_parm[1];
	insevent_struct rate_array [1];
	pay_struc  pay_array_a[1];
	redemps_struc  part_pay_array_a[1];
	redemps_struc even_redemps[1];
	BootResult LowerInstr;
	BootResult UpperInstr;
	date_union hold_date;

	return_state = SortRCInstr(InstrArrayParm, TotalInstr, ValueDate,holiSet);
	if (return_state != return_success)
	{
		goto end_func;
	}

	datecpy(BootArrayParm[0].date.date_string, ValueDate.date_string);
	BootArrayParm[0].factor = 1;

	for(element_count = 0,
		*TotalBoot = 1,
		dummy_ld = 0,
		dummy_ui = 0,
		months_local = 0,
		days_local = 0;
	    element_count < TotalInstr;
		dummy_ld = 0,
		dummy_ui = 0,
		months_local = 0,
		days_local = 0,
		++element_count,
		++*TotalBoot)
	{
	  switch(InstrArrayParm[element_count].type)
	  {

		case rc_mm_type:
		case rc_swap_type:
		{

			if (InstrArrayParm[element_count].term_1 <= 0)
			{
				return_state = return_err_rc_term1_le_zero;
				goto end_func;
			}
			
			return_state = CheckRCUnit(InstrArrayParm[element_count].unit);
			if (return_state != return_success)
			{
				goto end_func;
			}
			
			return_state = CheckRCFreq(InstrArrayParm[element_count].frequency);
			if (return_state != return_success)
			{
				goto end_func;
			}
			
			return_state = CheckRCDayCount(InstrArrayParm[element_count].day_count);
			if (return_state != return_success)
			{
				goto end_func;
			}
			
			return_state = CheckRCEOM(InstrArrayParm[element_count].eom);
			if (return_state != return_success)
			{
				goto end_func;
			}
			
			return_state = CheckRCDayAdjust(InstrArrayParm[element_count].day_adjust);
			if (return_state != return_success)
			{
				goto end_func;
			}

			if (InstrArrayParm[element_count].rate < 0)
			{
				return_state = return_err_rc_rate_lt_zero;
				goto end_func;
			}

			switch(InstrArrayParm[element_count].unit)
			{

				case rc_days_unit:
				{
                   days_local = InstrArrayParm[element_count].term_1;
                   months_local = 0;
				   break;
				}
				case rc_weeks_unit:
				{
                   days_local = InstrArrayParm[element_count].term_1 * 7;
				   months_local = 0;
					break;
				}
				case rc_months_unit:
				{
                   months_local = InstrArrayParm[element_count].term_1;
				   days_local = 0;
					break;
				}
				case rc_years_unit:
				{
                   months_local = InstrArrayParm[element_count].term_1 * 12;
				   days_local = 0;
					break;
				}
				default:
				{
					return_state = return_err_invalid_rc_unit;
					goto end_func;
					break;
				}

			}

			return_state = forecast(ValueDate,
			  months_local,
			  days_local,
			  day_count_nums[InstrArrayParm[element_count].day_count],
			  &BootArrayParm[*TotalBoot].date);

			if (return_state)
			{
					
				goto end_func;

			}

			return_state = adj_date(&BootArrayParm[*TotalBoot].date,
				adj_date_non_to_bus,
				InstrArrayParm[element_count].day_adjust,
				adj_date_yes_we,
				adj_date_no_hol,
//				holiday_code,
				holi_chan
//				,holi_parm
				,holiSet
				);

			if (return_state != return_success)
			{

				goto end_func;

			}

			if (InstrArrayParm[element_count].type == rc_mm_type)
			{
    
				in_instr_parm.instr_class = instr_cp_class;

				return_state = classdef(&in_instr_parm);

				if (return_state != return_success) {

					goto end_func;

				}

				py_parm_parm.parm_use = py_no_parm_use;
				py_parm_parm.price_var = 0;
				py_parm_parm.frac_per = py_no_frac_per;
				py_parm_parm.pay_adj = event_sched_no_holiday_adj;
				py_parm_parm.comp_freq = 0;
				py_parm_parm.per_len = 0;
				py_parm_parm.date_cal_num = date_no_cal;
				py_parm_parm.date_cal_den = date_no_cal;
				py_parm_parm.yield_meth = in_instr_parm.yield_meth;
				py_parm_parm.calc_first = py_yes_calc_first;

				datecpy(in_instr_parm.issue_date.date_string,
					ValueDate.date_string);
				datecpy(in_instr_parm.accrue_date.date_string,
					ValueDate.date_string);
				datecpy(in_instr_parm.pre_last_pay.date_string,
					ValueDate.date_string);
				datecpy(in_instr_parm.mat_date.date_string,				
					BootArrayParm[*TotalBoot].date.date_string);
				datecpy(in_instr_parm.pay_freq.first_date.date_string,
					in_instr_parm.mat_date.date_string);
				in_instr_parm.pay_freq.month_day = in_instr_parm.mat_date.date.days;
    
				in_instr_parm.yield_meth	= py_aibd_yield_meth;
	
				return_state =  py_calc(in_instr_parm,
					ValueDate, 
					&dummy_ld,
					&BootArrayParm[*TotalBoot].factor, 
					&dummy_ld,
					&dummy_ld,
					&dummy_ld,
					&InstrArrayParm[element_count].rate,
					&dummy_ld,
					py_parm_parm,
					0, 
					dummy_ui, 
					dummy_ui,
					&dummy_ld,
					&dummy_ld,
//					holi_parm,
					holiSet,
					&dummy_ld,
					&dummy_ld,
					redemps_array_parm, 
					rate_array,
					pay_array_a,
					part_pay_array_a,
					even_redemps
				);

				if (return_state)
				{
					goto end_func;

				}
			}
			else
			{
    
				in_instr_parm.instr_class = instr_uscd_class;

				return_state = classdef(&in_instr_parm);

				if (return_state != return_success) {

					goto end_func;

				}

				in_instr_parm.rate_offset = .10;
				in_instr_parm.day_count	= InstrArrayParm[element_count].day_count;
				in_instr_parm.cal_num	= day_count_nums[InstrArrayParm[element_count].day_count];
				in_instr_parm.cal_den	= day_count_dens[InstrArrayParm[element_count].day_count];
			    in_instr_parm.pay_factor	= instr_no_pay_factor;
			    in_instr_parm.pay_type		= instr_fixed_pay_type;
			    in_instr_parm.pay_sched		= instr_str_pay_sched;
			    in_instr_parm.comp_freq.period	= event_sched_free_period;
			    in_instr_parm.neg_first		= instr_no_neg_first;
			    in_instr_parm.ex_coup_days	= 0;
			    in_instr_parm.part_pays		= 0;
			    in_instr_parm.redemps		= 0;
				in_instr_parm.issue_price	= 0;
				in_instr_parm.redemp_price	= 1;
			    in_instr_parm.pay_freq.holiday_adj = 
					InstrArrayParm[element_count].day_adjust;
			    in_instr_parm.yield_meth = py_mm_yield_meth;

				if (months_local == 0)
				{
				    in_instr_parm.pay_freq.period = 
						event_sched_day_period;
				    in_instr_parm.pay_freq.freq	= (unsigned char)days_local;
				}
				else
				{
				    in_instr_parm.pay_freq.period = 
						event_sched_month_period;
				    in_instr_parm.pay_freq.freq	= months_local;
				}

				datecpy(in_instr_parm.issue_date.date_string,
					ValueDate.date_string);
				datecpy(in_instr_parm.accrue_date.date_string,
					ValueDate.date_string);
				datecpy(in_instr_parm.mat_date.date_string,				
					BootArrayParm[*TotalBoot].date.date_string);
				in_instr_parm.pay_freq.month_day = 
					in_instr_parm.mat_date.date.days;

				for(datecpy(hold_date.date_string,
							ValueDate.date_string),
							factor_sum = 0,
							period_count = 0;
					0 > datecmp(&hold_date,
					&BootArrayParm[*TotalBoot].date);
					++period_count
					)
				{


					datecpy(in_instr_parm.issue_date.date_string,
						hold_date.date_string);
					datecpy(in_instr_parm.accrue_date.date_string,
						hold_date.date_string);
					datecpy(in_instr_parm.pre_last_pay.date_string,
							hold_date.date_string);
			
					return_state = forecast(ValueDate,
						period_count * (months_local/InstrArrayParm[element_count].term_1)
							* (12 / InstrArrayParm[element_count].frequency),
						period_count * days_local/InstrArrayParm[element_count].term_1,
						day_count_nums[InstrArrayParm[element_count].day_count],
						&hold_date);

					if (return_state)
					{
					
						goto end_func;

					}

					return_state = adj_date(&hold_date,
						adj_date_non_to_bus,
						InstrArrayParm[element_count].day_adjust,
						adj_date_yes_we,
						adj_date_no_hol,
//						holiday_code,
						holi_chan
//						,holi_parm
						,holiSet
						);

					if (return_state != return_success)
					{

						goto end_func;

					}

					datecpy(in_instr_parm.mat_date.date_string,				
						hold_date.date_string);
					datecpy(in_instr_parm.pay_freq.first_date.date_string,
						hold_date.date_string);
/*
					in_instr_parm.pay_freq.month_day = 
						in_instr_parm.mat_date.date.days;
*/
					return_state = intcalc(in_instr_parm, 
											hold_date, 
											&dummy_ld,
											&dummy_long, 
											dummy_ui, 
											isfalse,
											int_yes_total_per,
											&dummy_ld, 
											&dummy_ld, 
											int_no_redemp_adj,
											dummy_ui, 
//											holi_parm, 
											holiSet,
											rate_array,
											&period_factor);

					if (return_state != return_success)
					{

						goto end_func;
					}
/*
					datecpy(in_instr_parm.issue_date.date_string,
						hold_date.date_string);
					datecpy(in_instr_parm.accrue_date.date_string,
						hold_date.date_string);
*/					
					if (0 > datecmp(&hold_date,
						&BootArrayParm[*TotalBoot].date))
					{

						for(sub_count = 0,
							datecpy(LowerInstr.date.date_string,
							ValueDate.date_string),
							datecpy(UpperInstr.date.date_string,
							ValueDate.date_string);
						  (sub_count < *TotalBoot) 
							&& (0 > datecmp(&UpperInstr.date,
									&hold_date));
						  datecpy(LowerInstr.date.date_string,
							UpperInstr.date.date_string),
						  ++sub_count)
						
						{

							UpperInstr = BootArrayParm[sub_count];

							if (0 > datecmp(&UpperInstr.date,
									&hold_date))
							{

								datecpy(LowerInstr.date.date_string,
									UpperInstr.date.date_string);

							}



						}
			
						comp_result = datecmp(&UpperInstr.date,
									&hold_date);

						if (comp_result == 0)

						/* Use the upper rate*/
						{

							factor_sum = factor_sum + 
							UpperInstr.factor * period_factor;
					
						}
						else
						{
							if (comp_result > 0)
							/* Interpolate*/
							{
							}
							else
							/* Extrapolate*/
							{
							}


						}
						

					}
					else
					{
						BootArrayParm[*TotalBoot].factor = 
							(1 - (InstrArrayParm[element_count].rate) *
							factor_sum)/ 
							(1 + (InstrArrayParm[element_count].rate *
							period_factor));
					}

				}
			}

			break;
		}
		case rc_fra_type:
		case rc_irf_type:
		case rc_bond_type:
		{

			return_state = return_err_not_supported;
			goto end_func;
			break;
		}
		default:
		{
			return_state = return_err_invalid_rc_type;
			goto end_func;
			break;

		}
	  }

	}
	

end_func:
	return return_state;
}
unsigned long _RATECURVE SortRCInstr(RateInstr * InstrArrayParm, 
									 char TotalInstr,
									 date_union BaseDate
									 ,const set<string> &holiSet)
{
	unsigned long return_state = return_success;
	int months_local = 0;
	long days_local = 0;
	int unsorted = 1;
	int element_count;
	date_union date_hold1;
	date_union date_hold2;
	RateInstr InstrHold;
	int comp_result;
//	char holiday_code[3];
	unsigned int holi_chan = 0;
//	holidays_struct holi_parm [1];

	for (unsorted = 1;unsorted;)
	{

		unsorted = 0;
		for (element_count = 0, months_local = 0, days_local = 0; 
			(element_count + 1 ) < TotalInstr;
			++element_count, months_local = 0, days_local = 0)
		{
		  if (InstrArrayParm[element_count].type > 
					InstrArrayParm[element_count + 1].type)
		  {
			
				InstrHold = InstrArrayParm[element_count];
				InstrArrayParm[element_count] = InstrArrayParm[element_count + 1];
				InstrArrayParm[element_count + 1] = InstrHold;
				unsorted = 1;

		  }
		  else
		  {

			/* Get the date of the lower member */

			switch(InstrArrayParm[element_count].type)
			{

				case rc_mm_type:
				case rc_swap_type:
				{

				  switch(InstrArrayParm[element_count].unit)
				  {

					case rc_days_unit:
					{
						days_local = InstrArrayParm[element_count].term_1;
						months_local = 0;
						break;
					}
					case rc_weeks_unit:
					{
						days_local = InstrArrayParm[element_count].term_1 * 7;
						months_local = 0;
						break;
					}
					case rc_months_unit:
					{
						months_local = InstrArrayParm[element_count].term_1;
						days_local = 0;
						break;
					}
					case rc_years_unit:
					{
						months_local = InstrArrayParm[element_count].term_1 * 12;
						days_local = 0;
						break;
					}
					default:
					{
						return_state = return_err_invalid_rc_unit;
						goto end_func;
						break;
					}

				  }

				  return_state = forecast(BaseDate,
					months_local,
					days_local,
					day_count_nums[InstrArrayParm[element_count].day_count],
					&date_hold1);

				  if (return_state)
				  {
					
					goto end_func;

				  }

				  return_state = adj_date(&date_hold1,
					adj_date_non_to_bus,
					InstrArrayParm[element_count].day_adjust,
					adj_date_yes_we,
					adj_date_no_hol,
//					holiday_code,
					holi_chan
//					,holi_parm
					,holiSet
					);

				  if (return_state != return_success)
				  {

					goto end_func;

				  }

				  break;
				}
				case rc_fra_type:
				case rc_irf_type:
				case rc_bond_type:
				{

					return_state = return_err_not_supported;
					goto end_func;
					break;
				}
				default:
				{
					return_state = return_err_invalid_rc_type;
					goto end_func;
					break;

				}
			}

			/* Get the date of the higher member */

			switch(InstrArrayParm[element_count + 1].type)
			{

				case rc_mm_type:
				case rc_swap_type:
				{

				  switch(InstrArrayParm[element_count + 1].unit)
				  {

					case rc_days_unit:
					{
						days_local = InstrArrayParm[element_count + 1].term_1;
						months_local = 0;
						break;
					}
					case rc_weeks_unit:
					{
						days_local = InstrArrayParm[element_count + 1].term_1 * 7;
						months_local = 0;
						break;
					}
					case rc_months_unit:
					{
						months_local = InstrArrayParm[element_count + 1].term_1;
						days_local = 0;
						break;
					}
					case rc_years_unit:
					{
						months_local = InstrArrayParm[element_count + 1].term_1 * 12;
						days_local = 0;
						break;
					}
					default:
					{
						return_state = return_err_invalid_rc_unit;
						goto end_func;
						break;
					}

				  }

				  return_state = forecast(BaseDate,
					months_local,
					days_local,
					day_count_nums[InstrArrayParm[element_count + 1].day_count],
					&date_hold2);

				  if (return_state)
				  {
					
					goto end_func;

				  }

				  return_state = adj_date(&date_hold2,
					adj_date_non_to_bus,
					InstrArrayParm[element_count + 1].day_adjust,
					adj_date_yes_we,
					adj_date_no_hol,
//					holiday_code,
					holi_chan
//					,holi_parm
					,holiSet
					);

				  if (return_state != return_success)
				  {

					goto end_func;

				  }

				  break;
				}
				case rc_fra_type:
				case rc_irf_type:
				case rc_bond_type:
				{

					return_state = return_err_not_supported;
					goto end_func;
					break;
				}
				default:
				{
					return_state = return_err_invalid_rc_type;
					goto end_func;
					break;

				}
			}
			
			comp_result = datecmp(&date_hold1,&date_hold2);
			if (comp_result > 0)
			{
			
				InstrHold = InstrArrayParm[element_count];
				InstrArrayParm[element_count] = InstrArrayParm[element_count + 1];
				InstrArrayParm[element_count + 1] = InstrHold;
				unsorted = 1;

			}
			else
			{
				unsorted = 0;
			}

		  }
		}
	}

end_func:
	return return_state;
}
