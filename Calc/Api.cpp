#include "stdafx.h"
//#include "datedec.h"
//#include "insclass.h"
//#include "gendec.h"
//#include "scrdec.h"
//#include <math.h>
#include "pyfront.h"
//#include <strsafe.h>
#include "Api.h"


char** getclassdescriptions(int& size)
{
	size = instr_last_class;
	return (char**)instr_class_descs;
}
char** getdaycounts(int& size)
{
	size = date_last_day_count;
	return (char**)day_count_names;
}

char** getpayfreqs(int& size)
{
	size = freq_count;
	return (char**)freq_names;
}
int  getStatusText(int status, char* text, int&textSize)
{
	Py_Front pyfront;
	int result = return_success;
	pyfront.errtext(status, text);
	textSize = error_text_len;
	return result;
}
int  getDefaultDates(InstrumentStruct &instrument, DateStruct &valueDate)
{
	Py_Front pyfront;
	int result = pyfront.init_screen();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.setclassdesc(instr_class_descs[instrument.instrumentClass]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_class_desc();
	if (result != return_success)
	{
		return result;
	}

	Date_Funcs::date_union matDate;
	matDate.date.centuries = instrument.maturityDate->year / 100;
	matDate.date.years = instrument.maturityDate->year % 100;
	matDate.date.months = instrument.maturityDate->month;
	matDate.date.days = instrument.maturityDate->day % 100;
	result = pyfront.setmatdate(matDate);
	if (result != return_success)
	{
		return result;
	}

	Date_Funcs::date_union valDate;
	valDate.date.centuries = valueDate.year / 100;
	valDate.date.years = valueDate.year % 100;
	valDate.date.months = valueDate.month;
	valDate.date.days = valueDate.day % 100;
	result = pyfront.setvaldate(valDate);
	if (result != return_success)
	{
		return result;
	}


	result = pyfront.setdaycount(day_count_names[instrument.intDayCount]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_day_count();
	if (result != return_success)
	{
		return result;
	}

	result = pyfront.setpayfreq(freq_names[instrument.intPayFreq]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_pay_freq();
	if (result != return_success)
	{
		return result;
	}


	result = pyfront.proc_def_dates();
	if (result != return_success)
	{
		return result;
	}

	Date_Funcs::date_union matDateOut;

	result = pyfront.getmatdate(matDateOut);
	if (result != return_success)
	{
		return result;
	}
	instrument.maturityDate->day = matDateOut.date.days;
	instrument.maturityDate->month = matDateOut.date.months;
	instrument.maturityDate->year = matDateOut.date.centuries * 100 + matDateOut.date.years;

	Date_Funcs::date_union issDateOut;

	result = pyfront.getissdate(issDateOut);
	if (result != return_success)
	{
		return result;
	}
	instrument.issueDate->day = issDateOut.date.days;
	instrument.issueDate->month = issDateOut.date.months;
	instrument.issueDate->year = issDateOut.date.centuries * 100 + issDateOut.date.years;

	Date_Funcs::date_union firstDateOut;

	result = pyfront.getfirstdate(firstDateOut);
	if (result != return_success)
	{
		return result;
	}
	instrument.firstPayDate->day = firstDateOut.date.days;
	instrument.firstPayDate->month = firstDateOut.date.months;
	instrument.firstPayDate->year = firstDateOut.date.centuries * 100 + firstDateOut.date.years;

	Date_Funcs::date_union penultDateOut;

	result = pyfront.getpenultdate(penultDateOut);
	if (result != return_success)
	{
		return result;
	}
	instrument.nextToLastPayDate->day = penultDateOut.date.days;
	instrument.nextToLastPayDate->month = penultDateOut.date.months;
	instrument.nextToLastPayDate->year = penultDateOut.date.centuries * 100 + penultDateOut.date.years;


	return return_success;
}

int getInstrumentDefaults(InstrumentStruct &instrument)
{
	int result = return_success;
	Py_Front pyfront;
	result = pyfront.init_screen();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.setclassdesc(instr_class_descs[instrument.instrumentClass]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_class_desc();
	if (result != return_success)
	{
		return result;
	}
	char charArg = 0;
	int intArg = 0;
	result = pyfront.getclassnumber(&charArg);
	if (result != return_success)
	{
		return result;
	}
	instrument.instrumentClass = (int)charArg;
	result = pyfront.getdaycount(&intArg);
	if (result != return_success)
	{
		return result;
	}
	instrument.intDayCount = intArg;
	result = pyfront.getpayfreq(&intArg);
	if (result != return_success)
	{
		return result;
	}
	instrument.intPayFreq = intArg;
	Date_Funcs::date_union dateArg;
	return result;
}
