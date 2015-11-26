// RateCurve.h: interface for the CRateCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RATECURVE_H__E72BFAA0_B1AE_11D1_8F5B_44455354616F__INCLUDED_)
#define AFX_RATECURVE_H__E72BFAA0_B1AE_11D1_8F5B_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _ANSIC
#define _RATECURVE CRateCurve::
#else
#define _RATECURVE
#endif

#include <stdlib.h>
#include <malloc.h>
#include "datedec.h"
#include "scrdec.h"
//#include "convutil.h"
#include "pydecs.h"

/* Define the valid Instrument types. */

const	char	rc_max_instr	= 20;	/*{rc_max_inst means maximum instruments in the rate curve.}*/
const	char	rc_max_boot_results	= rc_max_instr * 2;	/*{rc_max_boot_results is the maximum date-rates returned by the boot function.}*/
const	char	rc_date_len	= 11;	/*{rc_date_len is the length of the date string (dd/mm/yyyy plus null).}*/

const	char	rc_mm_type	= 0;	/*{rc_mm_type means money market type.}*/
const	char	rc_swap_type = 1;	/*{rc_swap_type means swap type.}*/
const	char	rc_bond_type = 2;	/*{rc_bond_type means bond type.}*/
const	char	rc_fra_type	= 3;	/*{rc_fra_type means forward rate agreement type.}*/
const	char	rc_irf_type	= 4;	/*{rc_irf_type means interest rate future type.}*/
const	char	rc_type_count = 5;

const	char 	rc_types[rc_type_count] = 
	{	rc_mm_type,
		rc_swap_type,
		rc_bond_type, 
		rc_fra_type,
		rc_irf_type
	};

char *const	rc_mm_type_name	= "MM";
char *const	rc_irf_type_name = "IRF";
char *const	rc_fra_type_name = "FRA";
char *const	rc_swap_type_name = "SWAP";
char *const	rc_bond_type_name = "BOND";
const	char rc_type_name_size = 5;

char *const	rc_type_names[rc_type_count] = 
	{	rc_mm_type_name,
		rc_swap_type_name,
		rc_bond_type_name,
		rc_fra_type_name,
		rc_irf_type_name
	};


/* Define the Rate Sources. */

const	char	rc_custom_source	= 0;	/*{rc_custom_source means cutomize the rates}*/
const	char	rc_handle_source	= 1;	/*{rc_handle_source means rates according to the handle sheet.}*/
const	char	rc_ratesheet_source	= 2;	/*{rc_rate_source means rates according to the rate sheet.}*/
const	char	rc_source_count = 3;

const char rc_sources[rc_source_count] = 
		{rc_custom_source,
		rc_handle_source,
		rc_ratesheet_source
		};

char *const	rc_custom_source_name	= "Custom";
char *const	rc_handle_source_name	= "Handle";
char *const	rc_ratesheet_source_name	= "Ratesheet";
const	char rc_source_name_size = 10;

char *const	rc_source_names[rc_source_count] = 
		{rc_custom_source_name,
		rc_handle_source_name,
		rc_ratesheet_source_name
		};



/* Define the Term Units. */
/*
const char term_size = 5;
const char rate_size = 10;
(*/
const	char	rc_days_unit	= 0;	/*{rc_days_unit means days.}*/
const	char	rc_weeks_unit	= 1;	/*{rc_weeks_unit means weeks.}*/
const	char	rc_months_unit = 2;	/*{rc_months_unit means months.}*/
const	char	rc_years_unit	= 3;	/*{rc_years_unit means years.}*/
const	char	rc_unit_count = 4;

const char	rc_units[rc_unit_count] = 
		{rc_days_unit,
		rc_weeks_unit,
		rc_months_unit,
		rc_years_unit
		};

char *const	rc_days_unit_name	= "Days";
char *const	rc_weeks_unit_name	= "Weeks";
char *const	rc_months_unit_name	= "Months";
char *const	rc_years_unit_name	= "Years";
const	char rc_unit_name_size = 7;


char *const	rc_unit_names[rc_unit_count] = 
		{rc_days_unit_name,
		rc_weeks_unit_name,
		rc_months_unit_name,
		rc_years_unit_name
		};

const	char	rc_dayadjust_count = 5;

const char rc_dayadjusts[rc_dayadjust_count] = 
		{
		event_sched_same_holiday_adj
		,event_sched_next_holiday_adj
		,event_sched_np_holiday_adj
		,event_sched_nextIMM_holiday_adj
		,event_sched_nearIMM_holiday_adj
		};

char *const	rc_dayadjust_names[rc_dayadjust_count] = 
		{
		event_sched_same_holiday_adj_name
		,event_sched_next_holiday_adj_name
		,event_sched_np_holiday_adj_name
		,event_sched_nextIMM_holiday_adj_name
		,event_sched_nearIMM_holiday_adj_name
		};

const	char rc_term_size = 6;
const	char rc_rate_size = 10;
const	int rate_precision = 8;
const	int factor_precision = 13;

const char RateInstrTextSize = 
		(rc_type_name_size + 1)
		+ (rc_term_size + 1)
		+ (rc_term_size + 1)
		+ (rc_unit_name_size + 1)
		+ (freq_names_len + 1)
		+ (day_count_names_len + 1)
		+ (monthend_names_len + 1)
		+ (holiday_adj_names_len + 1)
		+ (rc_rate_size + 1)
		;

const	char rc_boot_date_size = 11;
const	char rc_boot_factor_size = 15;

const char BootTextSize = 
		(rc_boot_date_size + 1)
		+ (rc_boot_factor_size + 1)
		;

#ifndef _ANSIC

class CALC_API CRateCurve  : public Py_Funcs
{
public:

	CRateCurve();
	virtual ~CRateCurve();

#endif

	typedef struct RateInstr
	{

		char type; /*{Indicates type of instrument. Must be one of the rc_xxx_type symbols.}*/
   		unsigned short term_1; /*{Indicates first term (tenor).}*/
		unsigned short term_2; /*{Indicates first term, for instruments such as FRA's which require 2 terms.}*/
		char unit; /*{Indicates the unit in which the terms are denominated. Must be one of the rc_xxx_unit symbols.}*/
		char frequency; /*{Indicates the frequency in months of compounding for those instruments which require this.}*/
		unsigned char day_count; /*{Indicates the method for day calculations. Must be one of the date_xxx_xxx_day_count symbols.}*/
		char eom; /*{Indicates whether the scheduled date is always month end or is always the same day of the month. Must be one of the monthend_xxx symbols.}*/
		char day_adjust; /*{Indicates how a non-business day is adjusted for. Must be one of the event_sched_xxx_holiday_adj symbols.}*/
		long double rate; /*{indicates current rate for this instrument.}*/
	};

	typedef struct BootResult
	{

		date_union date; /*{Date for which the factor is effective.}*/
		long double factor; /*{Factor in effect on the date.}*/
	};

	char *RateInstrText[RateInstrTextSize]; 
	char *BootText[BootTextSize]; 


	typedef struct RateCurve
	{

		date_union date; /*{Date for which the result is valid.}*/
		long double result; /*{Result for the date.}*/
	};

	unsigned long InitTypeNames(char parm_list [rc_type_count] [rc_type_name_size]);
	unsigned long InitSourceNames(char parm_list [rc_source_count] [rc_source_name_size]);
	unsigned long InitUnitNames(char parm_list [rc_unit_count] [rc_unit_name_size]);
	unsigned long InitFreqNames(char parm_list [freq_count] [freq_names_len]);
	unsigned long InitDayCountNames(char parm_list [date_last_day_count] [day_count_names_len]);
	unsigned long InitEOMNames(char parm_list [monthend_count] [monthend_names_len]);
	unsigned long InitDayAdjustNames(char parm_list [rc_dayadjust_count] [holiday_adj_names_len]);
	unsigned long SetRCType(char RC_Type [rc_type_name_size]);
	unsigned long SetRCSource(	char RateInstrTextParm[rc_max_instr] [RateInstrTextSize],
		char RC_Source [rc_source_name_size],
		char *TotalInstr);
	unsigned long SetRCUnit(char RC_Unit [rc_unit_name_size]);
	unsigned long SetRCDayCount(char RC_DayCount [day_count_names_len]);
	unsigned long SetRCEOM(char RC_EOM [monthend_names_len]);
	unsigned long SetRCDayAdjust(char RC_DayAdjust [holiday_adj_names_len]);
	unsigned long SetRCFrequency(char RC_Frequency [freq_names_len]);
	unsigned long SetRCTerm1(unsigned short RC_Term1 );
	unsigned long SetRCTerm2(unsigned short RC_Term2 );
	unsigned long SetRCRate1(long double RC_Rate1 );
	unsigned long GetRCType(char RC_Type [rc_type_name_size]);
	unsigned long GetRCTypeLocal(char RC_Type [rc_type_name_size], RateInstr LocalRateInstr);
	unsigned long GetRCUnitLocal(char RC_Unit [rc_unit_name_size], RateInstr LocalRateInstr);
	unsigned long GetRCTerm1Local(char RC_Term1 [rc_term_size], RateInstr LocalRateInstr);
	unsigned long GetRCTerm2Local(char RC_Term2 [rc_term_size], RateInstr LocalRateInstr);
	unsigned long GetRCFreqLocal(char RC_Freq [freq_names_len], RateInstr LocalRateInstr);
	unsigned long GetRCDayCountLocal(char RC_DayCount [day_count_names_len], RateInstr LocalRateInstr);
	unsigned long GetRCEOMLocal(char RC_EOM [monthend_names_len], RateInstr LocalRateInstr);
	unsigned long GetRCDayAdjustLocal(char RC_DayAdjust [holiday_adj_names_len], RateInstr LocalRateInstr);
	unsigned long GetRCRate1Local(char RC_Rate1 [rc_rate_size], RateInstr LocalRateInstr);
	unsigned long GetRCSource(char RC_Source [rc_rate_size]);
	unsigned long GetRCUnit(char RC_Unit [rc_unit_name_size]);
	unsigned long GetRCDayCount(char RC_DayCount [day_count_names_len]);
	unsigned long GetRCEOM(char RC_EOM [monthend_names_len]);
	unsigned long GetRCDayAdjust(char RC_DayAdjust [holiday_adj_names_len]);
	unsigned long GetRCFrequency(char RC_Frequency [freq_names_len]);
	unsigned long GetRCTerm1(unsigned short *RC_Term1 );
	unsigned long GetRCTerm2(unsigned short *RC_Term2 );
	unsigned long GetRCRate1(long double *RC_Rate1 );
	unsigned long GetRCTypeState(char *RC_TypeState);
	unsigned long GetRCTerm2State(char *RC_Term2State);
	unsigned long GetRCFrequencyState(char *RC_FrequencyState);
	unsigned long AddRCInstr(char RateInstrTextParm[rc_max_instr][RateInstrTextSize], char *TotalInstr);
	unsigned long DeleteRCInstr(int Instr_Selection );
	unsigned long SetRCInstrText(RateInstr * InstrArrayParm,
							char RateInstrTextParm[rc_max_instr][RateInstrTextSize], 
							char TotalInstr);
	unsigned long GetRCInstrText(char RateInstrTextParm[rc_max_instr][RateInstrTextSize], char *TotalInstr);
	unsigned long SelectRCInstr(int InstrParm);
	unsigned long RemoveRCInstr(int InstrParm);
	unsigned long CheckRCInstr(RateInstr InstrParm);
	unsigned long CheckRCUnit(char UnitParm);
	unsigned long CheckRCFreq(char FreqParm);
	unsigned long CheckRCDayCount(unsigned char DayCountParm);
	unsigned long CheckRCEOM(char EOMParm);
	unsigned long CheckRCDayAdjust(char DayAdjustParm);
	unsigned long SetRCValDate(char ValDate[rc_date_len]);
	unsigned long GetRCBootDiscText(char BootTextParm[rc_max_boot_results][BootTextSize],
		char *TotalBoot
					,const set<string> &holiSet
				);
	unsigned long RCBootDisc(date_union ValueDate,
						 RateInstr * InstrArrayParm,
						 char TotalInstr, 
						 BootResult *BootArrayParm, 
						const set<string> &holiSet
						 ,char *TotalBoot);
	unsigned long SortRCInstr(RateInstr * InstrArrayParm, 
						char TotalInstr,
						date_union BaseDate
						,const set<string> &holiSet);

#ifndef _ANSIC

private:

#endif	

	unsigned long SetRCTypeDefaults(char Type_Parm);

	RateInstr CurrentInstr;
	RateInstr InstrArray[rc_max_instr];
	char InstrCount;
	char BootCount;
	char CurrentSource;
	int CurrentIndex;
	char rc_date_format;
	BootResult BootResultArray [rc_max_boot_results];

/*{	The state variables indicate whether particular objects are enabled. they must contain one of the enabled_xxx constants}*/
	
	char Source_State;
	char Type_State;
	char Term1_State;
	char Term2_State;
	char Unit_State;
	char Frequency_State;
	char DayCount_State;
	char EOM_State;
	char Rate_State;
	date_union RCValDate;

#ifndef _ANSIC

};

#endif

#endif // !defined(AFX_RATECURVE_H__E72BFAA0_B1AE_11D1_8F5B_44455354616F__INCLUDED_)


