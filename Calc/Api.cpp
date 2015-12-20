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

char**  getyieldmethods(int& size)
{
	size = py_last_yield_meth;
	return (char**)yield_meth_names;
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
/*
int  getDefaultDatesAndData(InstrumentStruct &instrument, CalculationsStruct &calculations)
{
	return getDefaultDates(instrument, calculations.valueDate);
}
*/
int  getDefaultDatesAndData(InstrumentStruct &instrument, CalculationsStruct &calculations)
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
	valDate.date.centuries = calculations.valueDate->year / 100;
	valDate.date.years = calculations.valueDate->year % 100;
	valDate.date.months = calculations.valueDate->month;
	valDate.date.days = calculations.valueDate->day % 100;
	result = pyfront.setvaldate(valDate);
	if (result != return_success)
	{
		return result;
	}
	int excoup = ex_coup_no;
	if (calculations.isExCoup)
	{
		excoup = ex_coup_yes;
	}
	result = pyfront.setexcoup(excoup_names[excoup]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_excoup();
	if (result != return_success)
	{
		return result;
	}
	int eom = monthend_no;
	if (instrument.endOfMonthPay)
	{
		eom = monthend_yes;
	}
	result = pyfront.setmonthend(monthend_names[eom]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_monthend();
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
/*
	Date_Funcs::date_union nxtDateOut;

	result = pyfront.getnextcoup(nxtDateOut);
	if (result != return_success)
	{
		return result;
	}
	calculations.nextPayDate->day = nxtDateOut.date.days;
	calculations.nextPayDate->month = nxtDateOut.date.months;
	calculations.nextPayDate->year = nxtDateOut.date.centuries * 100 + nxtDateOut.date.years;

	Date_Funcs::date_union prvDateOut;

	result = pyfront.getprevcoup(prvDateOut);
	if (result != return_success)
	{
		return result;
	}
	calculations.previousPayDate->day = prvDateOut.date.days;
	calculations.previousPayDate->month = prvDateOut.date.months;
	calculations.previousPayDate->year = prvDateOut.date.centuries * 100 + prvDateOut.date.years;
	*/
	
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

	char excoupOut = 0;
	result = pyfront.getexcoup(excoupOut);
	if (result != return_success)
	{
		return result;
	}
	int eomOut = 0;
	bool eomOutB = false;
	result = pyfront.getmonthend(&eomOut);
	if (result != return_success)
	{
		return result;
	}
	if (eomOut == monthend_yes)
	{
		eomOutB = true;
	}
	instrument.endOfMonthPay = eomOutB;

	pyfront.calc_np_py();

	Date_Funcs::date_union prevCoup;
	result = pyfront.getprevcoup(prevCoup);
	if (result != return_success)
	{
		return result;
	}
	calculations.previousPayDate->year = prevCoup.date.years;
	calculations.previousPayDate->month = prevCoup.date.months;
	calculations.previousPayDate->day = prevCoup.date.days;

	Date_Funcs::date_union nextCoup;
	result = pyfront.getnextcoup(nextCoup);
	if (result != return_success)
	{
		return result;
	}
	calculations.nextPayDate->year = nextCoup.date.years;
	calculations.nextPayDate->month = nextCoup.date.months;
	calculations.nextPayDate->day = nextCoup.date.days;

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
