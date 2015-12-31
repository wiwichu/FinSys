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
int preProc(InstrumentStruct &instrument, CalculationsStruct &calculations, Py_Front &pyfront)
{
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
	result = pyfront.proc_mat_date_py();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_val_date_py();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.check_val_vs_mat_py();
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
	result = pyfront.setintrate(instrument.interestRate);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_int_py();
	if (result != return_success)
	{
		return result;
	}
	char calcWhat = py_yield_from_price_calc_what;
	if (calculations.calculatePrice)
	{
		calcWhat = py_price_from_yield_calc_what;
		result = pyfront.setinprice(0);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setinyield(calculations.yieldIn);
		if (result != return_success)
		{
			return result;
		}
	}
	else
	{
		result = pyfront.setinprice(calculations.priceIn);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setinyield(0);
		if (result != return_success)
		{
			return result;
		}

	}
	result = pyfront.setcalcwhat(calcWhat);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_price_py();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.setyielddays(day_count_names[calculations.yieldDayCount]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_yield_days();
	if (result != return_success)
	{
		return result;
	}

	result = pyfront.setyieldfreq(freq_names[calculations.yieldFreq]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_yield_freq();
	if (result != return_success)
	{
		return result;
	}

	result = pyfront.setyieldmeth(yield_meth_names[calculations.yieldMethod]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_yield_meth();
	if (result != return_success)
	{
		return result;
	}

}
int postProc(InstrumentStruct &instrument, CalculationsStruct &calculations, Py_Front &pyfront)
{

	Date_Funcs::date_union matDateOut;
	DateStruct tmpDate;
	tmpDate.year = 1;
	tmpDate.month = 1;
	tmpDate.day = 1;

	int result = pyfront.getmatdate(matDateOut);
	if (result != return_success)
	{
		return result;
	}
	if (instrument.maturityDate == null)
	{
		instrument.maturityDate = new DateStruct(tmpDate);
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
	if (instrument.issueDate == null)
	{
		instrument.issueDate = new DateStruct(tmpDate);
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
	if (instrument.firstPayDate == null)
	{
		instrument.firstPayDate = new DateStruct(tmpDate);
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
	if (instrument.nextToLastPayDate == null)
	{
		instrument.nextToLastPayDate = new DateStruct(tmpDate);
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
	calculations.isExCoup = excoupOut;
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
	if (calculations.previousPayDate == null)
	{
		calculations.previousPayDate = new DateStruct(tmpDate);
	}

	calculations.previousPayDate->year = prevCoup.date.centuries*100 + prevCoup.date.years;
	calculations.previousPayDate->month = prevCoup.date.months;
	calculations.previousPayDate->day = prevCoup.date.days;

	Date_Funcs::date_union nextCoup;
	result = pyfront.getnextcoup(nextCoup);
	if (result != return_success)
	{
		return result;
	}
	if (calculations.nextPayDate == null)
	{
		calculations.nextPayDate = new DateStruct(tmpDate);
	}
	calculations.nextPayDate->year = nextCoup.date.centuries*100+ nextCoup.date.years;
	calculations.nextPayDate->month = nextCoup.date.months;
	calculations.nextPayDate->day = nextCoup.date.days;

	long double doubleHold = 0;
	result = pyfront.getinprice(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.calculatePrice = doubleHold;
	result = pyfront.getconvexity(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.convexity = doubleHold;
	result = pyfront.getduration(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.duration = doubleHold;
	result = pyfront.getmodduration(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.modifiedDuration = doubleHold;
	result = pyfront.getinterest(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.interest = doubleHold;
	result = pyfront.getoutprice(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.priceOut = doubleHold;
	result = pyfront.getpvbp(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.pvbp = doubleHold;
	result = pyfront.getoutyield(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldOut = doubleHold;

	long longHold = 0;
	result = pyfront.getintdays(&longHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.interestDays = longHold;
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
	result = pyfront.getyieldfreq(&intArg);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldFreq = intArg;
	result = pyfront.getyielddays(&intArg);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldDayCount = intArg;
	result = pyfront.getyieldmeth(&intArg);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldMethod = intArg;
	return return_success;
}
int  getDefaultDatesAndData(InstrumentStruct &instrument, CalculationsStruct &calculations)
{
	Py_Front pyfront;
	int result = preProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}

	result = pyfront.proc_def_dates();
	if (result != return_success)
	{
		return result;
	}
	result = postProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}

	return return_success;
}
int  calculate(InstrumentStruct &instrument, CalculationsStruct &calculations)
{
	Py_Front pyfront;
	int result = preProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_def_dates();
	if (result != return_success)
	{
		return result;
	}
	result = preProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}

	if (instrument.issueDate != null)
	{
		Date_Funcs::date_union issDate;
		issDate.date.centuries = instrument.issueDate->year / 100;
		issDate.date.years = instrument.issueDate->year % 100;
		issDate.date.months = instrument.issueDate->month;
		issDate.date.days = instrument.issueDate->day % 100;
		result = pyfront.setissuedate(issDate);
		if (result != return_success)
		{
			return result;
		}
	}
	if (instrument.firstPayDate != null)
	{
		Date_Funcs::date_union fpdDate;
		fpdDate.date.centuries = instrument.firstPayDate->year / 100;
		fpdDate.date.years = instrument.firstPayDate->year % 100;
		fpdDate.date.months = instrument.firstPayDate->month;
		fpdDate.date.days = instrument.firstPayDate->day % 100;
		//Date_Funcs::date_union holdDate;
		//result = pyfront.getfirstdate(holdDate);
		//if (
		//	!
		//	(
		//		fpdDate.date.centuries == holdDate.date.centuries &&
		//		fpdDate.date.years == holdDate.date.years &&
		//		fpdDate.date.months == holdDate.date.months &&
		//		fpdDate.date.days == holdDate.date.days
		//		)
		//	)
		//{
		//	pyfront.forceSlowCalc(true);
		//}
		result = pyfront.setfirstdate(fpdDate);
		if (result != return_success)
		{
			return result;
		}
	}
	if (instrument.nextToLastPayDate != null)
	{
		Date_Funcs::date_union ntlDate;
		ntlDate.date.centuries = instrument.nextToLastPayDate->year / 100;
		ntlDate.date.years = instrument.nextToLastPayDate->year % 100;
		ntlDate.date.months = instrument.nextToLastPayDate->month;
		ntlDate.date.days = instrument.nextToLastPayDate->day % 100;
		Date_Funcs::date_union holdDate;
		result = pyfront.getpenultdate(holdDate);
		if (
			!
			(
				ntlDate.date.centuries == holdDate.date.centuries &&
				ntlDate.date.years == holdDate.date.years &&
				ntlDate.date.months == holdDate.date.months &&
				ntlDate.date.days == holdDate.date.days
				)
			)
		{
			pyfront.forceSlowCalc(true);
		}
		result = pyfront.setpenultdate(ntlDate);
		if (result != return_success)
		{
			return result;
		}
	}
	result = pyfront.proc_iss_date_py();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_first_date_py();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_penult_date_py();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_all_dates_py();
	if (result != return_success)
	{
		return result;
	}

	result = pyfront.calc_int();
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.calc_py();
	if (result != return_success)
	{
		return result;
	}
	result = postProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}

	return return_success;
}
int  getInstrumentDefaultsAndData(InstrumentStruct &instrument, CalculationsStruct &calculations)
{
	int result = return_success;
	Py_Front pyfront;
	result = preProc(instrument, calculations, pyfront);
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
	result = postProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}

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
	int  getCashFlows(CashFlowsStruct &cashFlowsStruct)
	{
		for (int i = 0; i < cashFlowsStruct.size; i++)
		{
			cashFlowsStruct.cashFlows[i].year += 1;
			cashFlowsStruct.cashFlows[i].amount += 1;
		}
		return return_success;
	}
	int  getNewCashFlows(CashFlowsStruct &cashFlowStruct)
	{

		const int size = 1000;
		CashFlowStruct *cf = new CashFlowStruct[size];
		cashFlowStruct.cashFlows = cf;
		cashFlowStruct.size = size;
		int year = 2000;
		for (int i = 0; i < size; i++)
		{
			CashFlowStruct *cfs = new CashFlowStruct();
			cf[i] = *cfs;
			cf[i].year = year + i;
			cf[i].month = 6;
			cf[i].day = 1;

			cf[i].amount = 1000 + i*100;
		}
		return return_success;
	}


