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
char** getHolidayAdjust(int& size)
{
	size = event_sched_last_holiday_adj;
	return (char**)holiday_adj_names;
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
//int  getDefaultDates(InstrumentStruct &instrument, DateStruct &valueDate)
//{
//	Py_Front pyfront;
//	int result = pyfront.init_screen();
//	if (result != return_success)
//	{
//		return result;
//	}
//	result = pyfront.setclassdesc(instr_class_descs[instrument.instrumentClass]);
//	if (result != return_success)
//	{
//		return result;
//	}
//	result = pyfront.proc_class_desc();
//	if (result != return_success)
//	{
//		return result;
//	}
//
//	Date_Funcs::date_union matDate;
//	matDate.date.centuries = instrument.maturityDate->year / 100;
//	matDate.date.years = instrument.maturityDate->year % 100;
//	matDate.date.months = instrument.maturityDate->month;
//	matDate.date.days = instrument.maturityDate->day % 100;
//	result = pyfront.setmatdate(matDate);
//	if (result != return_success)
//	{
//		return result;
//	}
//
//	Date_Funcs::date_union valDate;
//	valDate.date.centuries = valueDate.year / 100;
//	valDate.date.years = valueDate.year % 100;
//	valDate.date.months = valueDate.month;
//	valDate.date.days = valueDate.day % 100;
//	result = pyfront.setvaldate(valDate);
//	if (result != return_success)
//	{
//		return result;
//	}
//
//
//	result = pyfront.setdaycount(day_count_names[instrument.intDayCount]);
//	if (result != return_success)
//	{
//		return result;
//	}
//	result = pyfront.proc_day_count();
//	if (result != return_success)
//	{
//		return result;
//	}
//
//	result = pyfront.setpayfreq(freq_names[instrument.intPayFreq]);
//	if (result != return_success)
//	{
//		return result;
//	}
//	result = pyfront.proc_pay_freq();
//	if (result != return_success)
//	{
//		return result;
//	}
//
//
//	result = pyfront.proc_def_dates();
//	if (result != return_success)
//	{
//		return result;
//	}
//
//	Date_Funcs::date_union matDateOut;
//
//	result = pyfront.getmatdate(matDateOut);
//	if (result != return_success)
//	{
//		return result;
//	}
//	instrument.maturityDate->day = matDateOut.date.days;
//	instrument.maturityDate->month = matDateOut.date.months;
//	instrument.maturityDate->year = matDateOut.date.centuries * 100 + matDateOut.date.years;
//
//	Date_Funcs::date_union issDateOut;
//
//	result = pyfront.getissdate(issDateOut);
//	if (result != return_success)
//	{
//		return result;
//	}
//	instrument.issueDate->day = issDateOut.date.days;
//	instrument.issueDate->month = issDateOut.date.months;
//	instrument.issueDate->year = issDateOut.date.centuries * 100 + issDateOut.date.years;
//
//	Date_Funcs::date_union firstDateOut;
//
//	result = pyfront.getfirstdate(firstDateOut);
//	if (result != return_success)
//	{
//		return result;
//	}
//	instrument.firstPayDate->day = firstDateOut.date.days;
//	instrument.firstPayDate->month = firstDateOut.date.months;
//	instrument.firstPayDate->year = firstDateOut.date.centuries * 100 + firstDateOut.date.years;
//
//	Date_Funcs::date_union penultDateOut;
//
//	result = pyfront.getpenultdate(penultDateOut);
//	if (result != return_success)
//	{
//		return result;
//	}
//	instrument.nextToLastPayDate->day = penultDateOut.date.days;
//	instrument.nextToLastPayDate->month = penultDateOut.date.months;
//	instrument.nextToLastPayDate->year = penultDateOut.date.centuries * 100 + penultDateOut.date.years;
//
//
//	return return_success;
//}
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

	int tradeflat = trade_flat_no;
	if (calculations.tradeFlat)
	{
		tradeflat = trade_flat_yes;
	}
	result = pyfront.settradeflat(tradeflat_names[tradeflat]);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.proc_tradeflat();
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

	if (instrument.holidayAdjust != noValue)
	{
		result = pyfront.setholidayadj(holiday_adj_names[instrument.holidayAdjust]);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_holi_py();
		if (result != return_success)
		{
			return result;
		}
	}
	//if (instrument.intDayCount != date_last_day_count)
	if (instrument.intDayCount != noValue)
	{
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
	}
	//if (instrument.intPayFreq != freq_count)
	if (instrument.intPayFreq != noValue)
	{
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
		//if (calculations.yieldDayCount != freq_count)
		if (calculations.yieldDayCount != noValue)
		{
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
	}
		//if (calculations.yieldFreq != freq_count)
		if (calculations.yieldFreq != noValue)
		{
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
	}
	//if (calculations.yieldMethod != py_last_yield_meth)
	if (calculations.yieldMethod != noValue)
		{
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
	//if (instrument.holidayAdjust != event_sched_no_holiday_adj)
	if (instrument.holidayAdjust != noValue)
	{
		result = pyfront.setholidayadj(instrument.holidayAdjust);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_holi();
		if (result != return_success)
		{
			return result;
		}
	}
	return return_success;
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

	char tradeflatOut = 0;
	result = pyfront.gettradeflat(tradeflatOut);
	if (result != return_success)
	{
		return result;
	}
	calculations.tradeFlat = tradeflatOut;
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
	calculations.priceIn = doubleHold;
	result = pyfront.getconvexity(&doubleHold);
	if (result != return_success)
	{
		return result;
	}
	calculations.convexity = doubleHold*100;
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
	//result = pyfront.getclassnumber(&charArg);
	//if (result != return_success)
	//{
	//	return result;
	//}
	//instrument.instrumentClass = (int)charArg;
	//if (instrument.intDayCount == date_last_day_count)
	if (instrument.intDayCount == noValue)
	{
		result = pyfront.getdaycount(&intArg);
		if (result != return_success)
		{
			return result;
		}

		instrument.intDayCount = intArg;
	}
	else
	{
		result = pyfront.setdaycount(instrument.intDayCount);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_day_count();
		if (result != return_success)
		{
			return result;
		}

	}
	if (instrument.holidayAdjust == noValue)
	{
		result = pyfront.getholidayadj(&intArg);
		if (result != return_success)
		{
			return result;
		}

		instrument.holidayAdjust = intArg;
	}
	else
	{
		result = pyfront.setholidayadj(instrument.holidayAdjust);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_holi_py();
		if (result != return_success)
		{
			return result;
		}

	}
	//if (instrument.intPayFreq != freq_count)
		if (instrument.intPayFreq == noValue)
		{
		result = pyfront.getpayfreq(&intArg);
		if (result != return_success)
		{
			return result;
		}
		instrument.intPayFreq = intArg;
	}
	else
	{
		result = pyfront.setpayfreq(instrument.intPayFreq);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_pay_freq();
		if (result != return_success)
		{
			return result;
		}

	}
		//if (calculations.yieldFreq != freq_count)
		if (calculations.yieldFreq == noValue)
		{
		result = pyfront.getyieldfreq(&intArg);
		if (result != return_success)
		{
			return result;
		}
		calculations.yieldFreq = intArg;
	}
	else
	{
		result = pyfront.setyieldfreq(calculations.yieldFreq);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_yield_freq();
		if (result != return_success)
		{
			return result;
		}

	}
		//if (calculations.yieldDayCount != freq_count)
		if (calculations.yieldDayCount == noValue)
		{
		result = pyfront.getyielddays(&intArg);
		if (result != return_success)
		{
			return result;
		}
		calculations.yieldDayCount = intArg;
	}
	else
	{
		result = pyfront.setyielddays(calculations.yieldDayCount);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_yield_days();
		if (result != return_success)
		{
			return result;
		}

	}
	//if (calculations.yieldMethod == py_last_yield_meth)
	if (calculations.yieldMethod == noValue)
		{
		result = pyfront.getyieldmeth(&intArg);
		if (result != return_success)
		{
			return result;
		}
		calculations.yieldMethod = intArg;
	}
	else
	{
		result = pyfront.setyieldmeth(calculations.yieldMethod);
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
	return return_success;
}
int  getDefaultDatesAndData(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays)
{
	Py_Front pyfront;
	int result = preProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}
	Py_Front::HOLIDAY pyHolidays[100];
	for (int i = 0; i < holidays.size && i < 100; i++)
	{
		Py_Front::HOLIDAY hol;
		hol.day = holidays.dates[i].day;
		hol.month = holidays.dates[i].month;
		hol.year = holidays.dates[i].year;
		pyHolidays[i] = hol;
	}

	pyfront.setHolidays(pyHolidays, holidays.size);
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
double RateFromCurve(DateStruct baseDate, RateCurveStruct curve,int interpolationMethod, int dayCount)
{
	Date_Funcs::date_union calcDate;
	calcDate.date.days = baseDate.day;
	calcDate.date.months = baseDate.month;
	calcDate.date.years = baseDate.year%100;
	calcDate.date.centuries = baseDate.year / 100;
	//find boundaries
	RateStruct lowRate = curve.rates[0];
	RateStruct highRate = curve.rates[0];
	double rate = 0;
	int calcLowCmp = -1;
	int calcHighCmp = 1;
	for (int i = 0; calcLowCmp < 0 && calcHighCmp >0 && i < curve.size;i++)
	{
		RateStruct thisRate = curve.rates[i];
		Date_Funcs::date_union thisDate;
		thisDate.date.days = thisRate.day;
		thisDate.date.months = thisRate.month;
		thisDate.date.years = thisRate.year%100;
		thisDate.date.centuries = thisRate.year / 100;
		Date_Funcs::date_union lowDate;
		lowDate.date.days = lowRate.day;
		lowDate.date.months = lowRate.month;
		lowDate.date.years = lowRate.year % 100;
		lowDate.date.centuries = lowRate.year / 100;
		Date_Funcs::date_union highDate;
		highDate.date.days = highRate.day;
		highDate.date.months = highRate.month;
		highDate.date.years = highRate.year % 100;
		highDate.date.centuries = highRate.year / 100;

		int thisLowCmp = Date_Funcs::datecmp(thisDate.date_string, lowDate.date_string);
		int calcLowCmp = Date_Funcs::datecmp(calcDate.date_string, lowDate.date_string);
		int calcThisCmp = Date_Funcs::datecmp(calcDate.date_string,thisDate.date_string);

		if (calcLowCmp >= 0)
		{
			if (calcThisCmp >= 0)
			{
				if (thisLowCmp >= 0)
				{
					lowRate = thisRate;
					lowDate = thisDate;
				}
			}
		}
		int highLowCmp = Date_Funcs::datecmp(highDate.date_string, lowDate.date_string);
		if (highLowCmp < 0)
		{
			highDate = lowDate;
			highRate = lowRate;
		}
		int thisHighCmp = Date_Funcs::datecmp(thisDate.date_string, highDate.date_string);
		int calcHighCmp = Date_Funcs::datecmp(calcDate.date_string, highDate.date_string);
		if (calcHighCmp <= 0)
		{
			if (calcThisCmp <= 0)
			{
				if (thisHighCmp <= 0)
				{
					highDate = thisDate;
					highRate = thisRate;
				}
			}
		}
		else
		{
			highDate = thisDate;
			highRate = thisRate;
		}
	}
	Date_Funcs::date_union startDate;
	startDate.date.centuries = lowRate.year / 100;
	startDate.date.years = lowRate.year % 100;
	startDate.date.months = lowRate.month;
	startDate.date.days = lowRate.day;
	Date_Funcs::date_union endDate;
	endDate.date.centuries = highRate.year / 100;
	endDate.date.years = highRate.year % 100;
	endDate.date.months = highRate.month;
	endDate.date.days = highRate.day;

	int startCalcCmp = Date_Funcs::datecmp(startDate.date_string, calcDate.date_string);
	int endCalcCmp = Date_Funcs::datecmp(endDate.date_string, calcDate.date_string);
	int endStartCmp = Date_Funcs::datecmp(endDate.date_string, startDate.date_string);

	if (startCalcCmp == 0 || endStartCmp == 0)
	{
		rate = lowRate.rate;
	}
	else if (endCalcCmp == 0)
	{
		rate = highRate.rate;
	}
	else
	{
		long wholeDays = 0;
		Py_Front::tenor(startDate, endDate, dayCount, &wholeDays);
		long partDays = 0;
		Py_Front::tenor(startDate, calcDate, dayCount, &partDays);
		if (interpolationMethod == Linear)
		{
			double perFact = (double)partDays / wholeDays;
			rate = lowRate.rate + (highRate.rate - lowRate.rate)*perFact;
		}
	}
	return rate;
}
int  priceCashFlows(CashFlowsStruct &cashFlowsStruct,
	int yieldMth,
	int frequency,
	int dayCount,
	DateStruct &valueDate,
	RateCurveStruct &rateCurve,
	int interpolation
	)
{
	for (int i = 0; i < cashFlowsStruct.size; i++)
	{
		InstrumentStruct *instr = new InstrumentStruct();
		CalculationsStruct *calcs = new CalculationsStruct();
		instr->endOfMonthPay = true;
		instr->maturityDate = new DateStruct();
		instr->maturityDate->day = cashFlowsStruct.cashFlows[i].adjustedDay;
		instr->maturityDate->year = cashFlowsStruct.cashFlows[i].adjustedYear;
		instr->maturityDate->month = cashFlowsStruct.cashFlows[i].adjustedMonth;
		instr->intDayCount = dayCount;
		instr->intPayFreq = frequency;
		instr->interestRate = 0;
		instr->firstPayDate = new DateStruct();
		instr->holidayAdjust = 0;
		instr->issueDate = new DateStruct();
		instr->nextToLastPayDate = new DateStruct;
		instr->instrumentClass = instr_bund_class;
		calcs->valueDate = new DateStruct();
		calcs->valueDate->day = valueDate.day;
		calcs->valueDate->month = valueDate.month;
		calcs->valueDate->year = valueDate.year;
		calcs->yieldDayCount = dayCount;
		calcs->yieldFreq = frequency;
		calcs->yieldMethod = yieldMth;
		double rate = cashFlowsStruct.cashFlows[i].discountRate;
		if (rateCurve.size > 0)
		{
			rate = RateFromCurve(*instr->maturityDate, rateCurve, interpolation,dayCount);
			cashFlowsStruct.cashFlows[i].discountRate = rate;
		}
		calcs->yieldIn = rate;
		calcs->calculatePrice = py_price_from_yield_calc_what;
		calcs->convexity = 0;
		calcs->duration = 0;
		calcs->exCoupDays = 0;
		calcs->interest = 0;
		calcs->interestDays = 0;
		calcs->tradeFlat = trade_flat_no;
		calcs->isExCoup = ex_coup_no;
		calcs->exCoupDays = 0;
		calcs->modifiedDuration = 0;
		calcs->nextPayDate = new DateStruct();
		calcs->prepayModel = 0;
		calcs->previousPayDate = new DateStruct();
		calcs->priceIn = 0;
		calcs->priceOut = 0;
		calcs->pvbp = 0;
		calcs->pvbpConvexityAdjusted = 0;
		calcs->serviceFee = 0;
		calcs->yieldOut = 0;
		int result = getInstrumentDefaultsAndData(*instr, *calcs);
		if (result != return_success)
		{
			return result;
		}
		instr->endOfMonthPay = true;
		instr->maturityDate = new DateStruct();
		instr->maturityDate->day = cashFlowsStruct.cashFlows[i].adjustedDay;
		instr->maturityDate->year = cashFlowsStruct.cashFlows[i].adjustedYear;
		instr->maturityDate->month = cashFlowsStruct.cashFlows[i].adjustedMonth;
		instr->intDayCount = dayCount;
		instr->intPayFreq = frequency;
		instr->interestRate = 0;
		instr->firstPayDate = new DateStruct();
		instr->holidayAdjust = 0;
		instr->issueDate = new DateStruct();
		instr->nextToLastPayDate = new DateStruct;
		instr->instrumentClass = instr_bund_class;
		calcs->valueDate = new DateStruct();
		calcs->valueDate->day = valueDate.day;
		calcs->valueDate->month = valueDate.month;
		calcs->valueDate->year = valueDate.year;
		calcs->yieldDayCount = dayCount;
		calcs->yieldFreq = frequency;
		calcs->yieldMethod = yieldMth;
		calcs->yieldIn = cashFlowsStruct.cashFlows[i].discountRate;
		calcs->calculatePrice = py_price_from_yield_calc_what;
		calcs->convexity = 0;
		calcs->duration = 0;
		calcs->exCoupDays = 0;
		calcs->interest = 0;
		calcs->interestDays = 0;
		calcs->tradeFlat = trade_flat_no;
		calcs->isExCoup = ex_coup_no;
		calcs->exCoupDays = 0;
		calcs->modifiedDuration = 0;
		calcs->nextPayDate = new DateStruct();
		calcs->prepayModel = 0;
		calcs->previousPayDate = new DateStruct();
		calcs->priceIn = 0;
		calcs->priceOut = 0;
		calcs->pvbp = 0;
		calcs->pvbpConvexityAdjusted = 0;
		calcs->serviceFee = 0;
		calcs->yieldOut = 0;
		DatesStruct holidays;
		result = getDefaultDatesAndData(*instr, *calcs,holidays);
		if (result != return_success)
		{
			return result;
		}
		instr->firstPayDate = instr->maturityDate;
		instr->issueDate->day = valueDate.day;
		instr->issueDate->month = valueDate.month;
		instr->issueDate->year = valueDate.year;
		instr->nextToLastPayDate = instr->issueDate;
		result = calculate(*instr, *calcs, holidays);
		if (result != return_success)
		{
			return result;
		}
		cashFlowsStruct.cashFlows[i].presentValue = cashFlowsStruct.cashFlows[i].amount*calcs->priceOut;
		delete instr;
		delete calcs;
	}
	return return_success;
}
int  calculateWithCashFlows(InstrumentStruct &instrument, CalculationsStruct &calculations,CashFlowsStruct &cashFlowsStruct, int adjustRule, DatesStruct &holidays)
{
	Py_Front pyfront;
	int result = preProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}
	Py_Front::HOLIDAY pyHolidays[100];
	for (int i = 0; i < holidays.size && i < 100; i++)
	{
		Py_Front::HOLIDAY hol;
		hol.day = holidays.dates[i].day;
		hol.month = holidays.dates[i].month;
		hol.year = holidays.dates[i].year;
		pyHolidays[i] = hol;
	}

	pyfront.setHolidays(pyHolidays, holidays.size);

	if (result != return_success)
	{
		return result;
	}
	set<string> holiSet;
	pyfront.getHolidays(holiSet);

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

	if (!calculations.tradeFlat)
	{
		result = pyfront.calc_int();
		if (result != return_success)
		{
			return result;
		}
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
	if (calculations.calculatePrice == 1)
	{
		calculations.pvbpConvexityAdjusted =
			calculations.pvbp - calculations.convexity*0.05*(calculations.priceOut+calculations.interest)/100000;
	}
	else
	{
		calculations.pvbpConvexityAdjusted =
			calculations.pvbp - calculations.convexity*0.05*(calculations.priceIn + calculations.interest)/100000;
	}
	calculations.pvbp *= 100;
	calculations.pvbpConvexityAdjusted *= 100;
	//Buld cashflows
	result = pyfront.forceSlowCalc_py(true);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.justCoupsCalc_py(true);
	if (result != return_success)
	{
		return result;
	}
	result = pyfront.calc_py();
	if (result != return_success)
	{
		return result;
	}
	vector<Instrument::pay_struc> cashFlows;
	result = pyfront.getcashFlows(cashFlows);
	if (result != return_success)
	{
		return result;
	}
	vector<Instrument::pay_struc>::iterator _it_vector_pay_struc;
	CashFlowStruct *cf = new CashFlowStruct[max_coups];
	cashFlowsStruct.cashFlows = cf;
	int year = 2000;
	int i = 0;
	for (_it_vector_pay_struc = cashFlows.begin();
	_it_vector_pay_struc < cashFlows.end();
		_it_vector_pay_struc++ )
	{
		if (_it_vector_pay_struc->payment == 0)
		{
			continue;
		}
		CashFlowStruct *cfs = new CashFlowStruct();
			cf[i] = *cfs;
			cf[i].amount = _it_vector_pay_struc->payment;
			cf[i].presentValue = _it_vector_pay_struc->pv_factor;
			cf[i].year = _it_vector_pay_struc->pay_date.date.centuries*100 + _it_vector_pay_struc->pay_date.date.years;
			cf[i].month = _it_vector_pay_struc->pay_date.date.months;
			cf[i].day = _it_vector_pay_struc->pay_date.date.days;
			Date_Funcs::date_union date_hold = _it_vector_pay_struc->pay_date;
			int holi_chan = 0;
			result = Date_Funcs::adj_date(&date_hold,
					adj_date_non_to_bus,
					adjustRule,
					adj_date_yes_we,
					adj_date_yes_hol,
					//				in_instr->holiday_code,
					holi_chan
					//				,holi_parm
					, holiSet
					);

			if (result != return_success)
			{

				return result;

			}


			cf[i].adjustedYear = date_hold.date.centuries*100 + date_hold.date.years;
			cf[i].adjustedMonth = date_hold.date.months;
			cf[i].adjustedDay = date_hold.date.days;
			if (calculations.calculatePrice)
			{
				cf[i].discountRate = calculations.yieldIn;
			}
			else
			{
				cf[i].discountRate = calculations.yieldOut;
			}
			i++;
	}
	cashFlowsStruct.size = i;

	return return_success;
}
int  USTBillCalcFromPrice(DateStruct &valueDate, DateStruct &maturityDate,
	double price, double &discount, double &mmYield, double &beYield)
{
	InstrumentStruct instrument; 
	CalculationsStruct calculations;
	instrument.intDayCount = noValue;
	instrument.firstPayDate = null;
	instrument.interestRate = 0;
	instrument.intPayFreq = noValue;
	instrument.issueDate = null;
	instrument.nextToLastPayDate = null;
	instrument.maturityDate = new DateStruct();
	instrument.maturityDate->day = maturityDate.day;
	instrument.maturityDate->month = maturityDate.month;
	instrument.maturityDate->year = maturityDate.year;
	calculations.valueDate = new DateStruct();
	calculations.valueDate->day = valueDate.day;
	calculations.valueDate->month = valueDate.month;
	calculations.valueDate->year = valueDate.year;
	instrument.instrumentClass = instr_usdsc_class;
	instrument.holidayAdjust = event_sched_same_holiday_adj;
	calculations.calculatePrice = py_yield_from_price_calc_what;
	calculations.previousPayDate = null;
	calculations.nextPayDate = null;
	calculations.priceIn = price;
	calculations.yieldDayCount = noValue;
	calculations.yieldFreq = noValue;
	calculations.yieldMethod = noValue;
	int result = getInstrumentDefaultsAndData(instrument, calculations);
	if (result != return_success)
	{
		return result;
	}
	instrument.maturityDate = new DateStruct();
	instrument.maturityDate->day = maturityDate.day;
	instrument.maturityDate->month = maturityDate.month;
	instrument.maturityDate->year = maturityDate.year;
	calculations.valueDate = new DateStruct();
	calculations.valueDate->day = valueDate.day;
	calculations.valueDate->month = valueDate.month;
	calculations.valueDate->year = valueDate.year;

	DatesStruct holidays;
	holidays.size = 0;
	result = getDefaultDatesAndData(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	calculations.priceIn = price;
	calculations.calculatePrice = 0;
	calculations.yieldMethod = py_mmdisc_yield_meth;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	discount = calculations.yieldOut;
	calculations.yieldMethod = py_mm_yield_meth;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	mmYield = calculations.yieldOut;

	Date_Funcs::date_union date1;
	date1.date.centuries =valueDate.year / 100;
	date1.date.years = valueDate.year % 100;
	date1.date.months = valueDate.month;
	date1.date.days = valueDate.day;
	Date_Funcs::date_union date2;
	date2.date.centuries = maturityDate.year / 100;
	date2.date.years = maturityDate.year % 100;
	date2.date.months = maturityDate.month;
	date2.date.days = maturityDate.day;
	long days = 0;
	result = Py_Front::tenor(date1, date2, date_act_cal, &days);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldMethod = py_mm_yield_meth;
	calculations.yieldDayCount = date_NL_365_day_count;
	calculations.yieldFreq = frequency_semiannually_idx;
	if (days <= 182)
	{
		calculations.yieldMethod = py_ustr_yield_meth;
		calculations.yieldDayCount = date_act_365_day_count;
		calculations.yieldFreq = frequency_annually_idx;

	}
		result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	beYield = calculations.yieldOut;


	return return_success;
}
int  USTBillCalcFromBEYield(DateStruct &valueDate, DateStruct &maturityDate,
	double beYield, double &price, double &mmYield, double &discount)
{
	InstrumentStruct instrument;
	CalculationsStruct calculations;
	instrument.intDayCount = noValue;
	instrument.firstPayDate = null;
	instrument.interestRate = 0;
	instrument.intPayFreq = noValue;
	instrument.issueDate = null;
	instrument.nextToLastPayDate = null;
	instrument.maturityDate = new DateStruct();
	instrument.maturityDate->day = maturityDate.day;
	instrument.maturityDate->month = maturityDate.month;
	instrument.maturityDate->year = maturityDate.year;
	calculations.valueDate = new DateStruct();
	calculations.valueDate->day = valueDate.day;
	calculations.valueDate->month = valueDate.month;
	calculations.valueDate->year = valueDate.year;
	instrument.instrumentClass = instr_usdsc_class;
	instrument.holidayAdjust = event_sched_same_holiday_adj;
	calculations.calculatePrice = py_yield_from_price_calc_what;
	calculations.previousPayDate = null;
	calculations.nextPayDate = null;
	calculations.yieldIn = beYield;
	calculations.yieldDayCount = noValue;
	calculations.yieldFreq = noValue;
	calculations.yieldMethod = noValue;
	int result = getInstrumentDefaultsAndData(instrument, calculations);
	if (result != return_success)
	{
		return result;
	}
	instrument.maturityDate = new DateStruct();
	instrument.maturityDate->day = maturityDate.day;
	instrument.maturityDate->month = maturityDate.month;
	instrument.maturityDate->year = maturityDate.year;
	calculations.valueDate = new DateStruct();
	calculations.valueDate->day = valueDate.day;
	calculations.valueDate->month = valueDate.month;
	calculations.valueDate->year = valueDate.year;

	DatesStruct holidays;
	holidays.size = 0;
	result = getDefaultDatesAndData(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}

	Date_Funcs::date_union date1;
	date1.date.centuries = valueDate.year / 100;
	date1.date.years = valueDate.year % 100;
	date1.date.months = valueDate.month;
	date1.date.days = valueDate.day;
	Date_Funcs::date_union date2;
	date2.date.centuries = maturityDate.year / 100;
	date2.date.years = maturityDate.year % 100;
	date2.date.months = maturityDate.month;
	date2.date.days = maturityDate.day;
	long days = 0;
	result = Py_Front::tenor(date1, date2, date_act_cal, &days);
	if (result != return_success)
	{
		return result;
	}
	int yieldDayCountHold = calculations.yieldDayCount;
	int yieldFreqHold = calculations.yieldFreq;
	calculations.yieldMethod = py_mm_yield_meth;
	calculations.yieldDayCount = date_NL_365_day_count;
	calculations.yieldFreq = frequency_semiannually_idx;
	if (days <= 182)
	{
		calculations.yieldMethod = py_ustr_yield_meth;
		calculations.yieldDayCount = date_act_365_day_count;
		calculations.yieldFreq = frequency_annually_idx;

	}
	calculations.yieldIn = beYield;
	calculations.calculatePrice = 1;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	price = calculations.priceOut;
	calculations.yieldDayCount = yieldDayCountHold;
	calculations.yieldFreq = yieldFreqHold;
	calculations.priceIn = price;
	calculations.calculatePrice = 0;
	calculations.yieldMethod = py_mm_yield_meth;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	mmYield = calculations.yieldOut;

	calculations.yieldMethod = py_mmdisc_yield_meth;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	discount = calculations.yieldOut;

	return return_success;
}

int  USTBillCalcFromDiscount(DateStruct &valueDate, DateStruct &maturityDate,
	double discount, double &price, double &mmYield, double &beYield)
{
	InstrumentStruct instrument;
	CalculationsStruct calculations;
	instrument.intDayCount = noValue;
	instrument.firstPayDate = null;
	instrument.interestRate = 0;
	instrument.intPayFreq = noValue;
	instrument.issueDate = null;
	instrument.nextToLastPayDate = null;
	instrument.maturityDate = new DateStruct();
	instrument.maturityDate->day = maturityDate.day;
	instrument.maturityDate->month = maturityDate.month;
	instrument.maturityDate->year = maturityDate.year;
	calculations.valueDate = new DateStruct();
	calculations.valueDate->day = valueDate.day;
	calculations.valueDate->month = valueDate.month;
	calculations.valueDate->year = valueDate.year;
	instrument.instrumentClass = instr_usdsc_class;
	instrument.holidayAdjust = event_sched_same_holiday_adj;
	calculations.calculatePrice = py_yield_from_price_calc_what;
	calculations.previousPayDate = null;
	calculations.nextPayDate = null;
	calculations.yieldIn = discount;
	calculations.yieldDayCount = noValue;
	calculations.yieldFreq = noValue;
	calculations.yieldMethod = noValue;
	int result = getInstrumentDefaultsAndData(instrument, calculations);
	if (result != return_success)
	{
		return result;
	}
	instrument.maturityDate = new DateStruct();
	instrument.maturityDate->day = maturityDate.day;
	instrument.maturityDate->month = maturityDate.month;
	instrument.maturityDate->year = maturityDate.year;
	calculations.valueDate = new DateStruct();
	calculations.valueDate->day = valueDate.day;
	calculations.valueDate->month = valueDate.month;
	calculations.valueDate->year = valueDate.year;

	DatesStruct holidays;
	holidays.size = 0;
	result = getDefaultDatesAndData(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldIn = discount;
	calculations.calculatePrice = 1;
	calculations.yieldMethod = py_mmdisc_yield_meth;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	price = calculations.priceOut;
	calculations.priceIn = price;
	calculations.calculatePrice = 0;
	calculations.yieldMethod = py_mm_yield_meth;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	mmYield = calculations.yieldOut;

	Date_Funcs::date_union date1;
	date1.date.centuries = valueDate.year / 100;
	date1.date.years = valueDate.year % 100;
	date1.date.months = valueDate.month;
	date1.date.days = valueDate.day;
	Date_Funcs::date_union date2;
	date2.date.centuries = maturityDate.year / 100;
	date2.date.years = maturityDate.year % 100;
	date2.date.months = maturityDate.month;
	date2.date.days = maturityDate.day;
	long days = 0;
	result = Py_Front::tenor(date1, date2, date_act_cal, &days);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldMethod = py_mm_yield_meth;
	calculations.yieldDayCount = date_NL_365_day_count;
	calculations.yieldFreq = frequency_semiannually_idx;
	if (days <= 182)
	{
		calculations.yieldMethod = py_ustr_yield_meth;
		calculations.yieldDayCount = date_act_365_day_count;
		calculations.yieldFreq = frequency_annually_idx;

	}
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	beYield = calculations.yieldOut;


	return return_success;

}

int  USTBillCalcFromMMYield(DateStruct &valueDate, DateStruct &maturityDate,
	double mmYield, double &price, double &discount, double &beYield)
{
	InstrumentStruct instrument;
	CalculationsStruct calculations;
	instrument.intDayCount = noValue;
	instrument.firstPayDate = null;
	instrument.interestRate = 0;
	instrument.intPayFreq = noValue;
	instrument.issueDate = null;
	instrument.nextToLastPayDate = null;
	instrument.maturityDate = new DateStruct();
	instrument.maturityDate->day = maturityDate.day;
	instrument.maturityDate->month = maturityDate.month;
	instrument.maturityDate->year = maturityDate.year;
	calculations.valueDate = new DateStruct();
	calculations.valueDate->day = valueDate.day;
	calculations.valueDate->month = valueDate.month;
	calculations.valueDate->year = valueDate.year;
	instrument.instrumentClass = instr_usdsc_class;
	instrument.holidayAdjust = event_sched_same_holiday_adj;
	calculations.calculatePrice = py_yield_from_price_calc_what;
	calculations.previousPayDate = null;
	calculations.nextPayDate = null;
	calculations.yieldIn = mmYield;
	calculations.yieldDayCount = noValue;
	calculations.yieldFreq = noValue;
	calculations.yieldMethod = noValue;
	int result = getInstrumentDefaultsAndData(instrument, calculations);
	if (result != return_success)
	{
		return result;
	}
	instrument.maturityDate = new DateStruct();
	instrument.maturityDate->day = maturityDate.day;
	instrument.maturityDate->month = maturityDate.month;
	instrument.maturityDate->year = maturityDate.year;
	calculations.valueDate = new DateStruct();
	calculations.valueDate->day = valueDate.day;
	calculations.valueDate->month = valueDate.month;
	calculations.valueDate->year = valueDate.year;

	DatesStruct holidays;
	holidays.size = 0;
	result = getDefaultDatesAndData(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldIn = mmYield;
	calculations.calculatePrice = 1;
	calculations.yieldMethod = py_mm_yield_meth;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	price = calculations.priceOut;
	calculations.priceIn = price;
	calculations.calculatePrice = 0;
	calculations.yieldMethod = py_mmdisc_yield_meth;
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	discount = calculations.yieldOut;

	Date_Funcs::date_union date1;
	date1.date.centuries = valueDate.year / 100;
	date1.date.years = valueDate.year % 100;
	date1.date.months = valueDate.month;
	date1.date.days = valueDate.day;
	Date_Funcs::date_union date2;
	date2.date.centuries = maturityDate.year / 100;
	date2.date.years = maturityDate.year % 100;
	date2.date.months = maturityDate.month;
	date2.date.days = maturityDate.day;
	long days = 0;
	result = Py_Front::tenor(date1, date2, date_act_cal, &days);
	if (result != return_success)
	{
		return result;
	}
	calculations.yieldMethod = py_mm_yield_meth;
	calculations.yieldDayCount = date_NL_365_day_count;
	calculations.yieldFreq = frequency_semiannually_idx;
	if (days <= 182)
	{
		calculations.yieldMethod = py_ustr_yield_meth;
		calculations.yieldDayCount = date_act_365_day_count;
		calculations.yieldFreq = frequency_annually_idx;

	}
	result = calculate(instrument, calculations, holidays);
	if (result != return_success)
	{
		return result;
	}
	beYield = calculations.yieldOut;


	return return_success;
}


int  calculate(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays)
{
	Py_Front pyfront;
	int result = preProc(instrument, calculations, pyfront);
	if (result != return_success)
	{
		return result;
	}
	Py_Front::HOLIDAY pyHolidays[100];
	for (int i = 0; i < holidays.size && i < 100; i++)
	{
		Py_Front::HOLIDAY hol;
		hol.day = holidays.dates[i].day;
		hol.month = holidays.dates[i].month;
		hol.year = holidays.dates[i].year;
		pyHolidays[i] = hol;
	}

	pyfront.setHolidays(pyHolidays, holidays.size);

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
	if (!calculations.tradeFlat)
	{
		result = pyfront.calc_int();
		if (result != return_success)
		{
			return result;
		}
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
	if (calculations.calculatePrice == 1)
	{
		calculations.pvbpConvexityAdjusted =
			calculations.pvbp - calculations.convexity*0.05*(calculations.priceOut + calculations.interest) / 100000;
	}
	else
	{
		calculations.pvbpConvexityAdjusted =
			calculations.pvbp - calculations.convexity*0.05*(calculations.priceIn + calculations.interest) / 100000;
	}
	calculations.pvbp *= 100;
	calculations.pvbpConvexityAdjusted *= 100;
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
	int  getCashFlows(CashFlowsStruct &cashFlowsStruct, int adjustRule)
	{
		for (int i = 0; i < cashFlowsStruct.size; i++)
		{
			cashFlowsStruct.cashFlows[i].year += 1;
			cashFlowsStruct.cashFlows[i].amount += 1;
		}
		return return_success;
	}
	int  getNewCashFlows(CashFlowsStruct &cashFlowStruct, int adjustRule)
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
	int  intCalc(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &days, double &dayCountFraction)
	{
		Py_Front pyfront;
		Date_Funcs::date_union fromDate;
		fromDate.date.centuries = startDate.year / 100;
		fromDate.date.years = startDate.year % 100;
		fromDate.date.months = startDate.month;
		fromDate.date.days = startDate.day;
		Date_Funcs::date_union toDate;
		toDate.date.centuries = endDate.year / 100;
		toDate.date.years = endDate.year % 100;
		toDate.date.months = endDate.month;
		toDate.date.days = endDate.day;
		int result = return_success;
		result = pyfront.init_screen();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setclassdesc(instr_euro_class_desc);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_class_desc();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setdaycount(dayCountRule);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_day_count();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setvaldate(toDate);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_val_date_py();
		if (result != return_success)
		{
			return result;
		}
		Date_Funcs::date_union firstPayDate;
		result = pyfront.forecast(toDate, 0, 1, date_act_cal, &firstPayDate);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setfirstdate(firstPayDate);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_first_date_py();
		if (result != return_success)
		{
			return result;
		}
		Date_Funcs::date_union penultDate;
		result = pyfront.forecast(firstPayDate, 12, 0, date_act_cal, &penultDate);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setpenultdate(penultDate);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_penult_date_py();
		if (result != return_success)
		{
			return result;
		}
		Date_Funcs::date_union matDate;
		result = pyfront.forecast(penultDate, 12, 0, date_act_cal, &matDate);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setmatdate(matDate);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_mat_date_py();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setissuedate(fromDate);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_iss_date_py();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_all_dates_py();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setintrate(0.1);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_int_py();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setinprice(1);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_price_py();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.setmonthend(monthend_yes);
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.proc_monthend();
		if (result != return_success)
		{
			return result;
		}
		result = pyfront.calc_int();
		if (result != return_success)
		{
			return result;
		}
		long double interest = 0;
		result = pyfront.getinterest(&interest);
		if (result != return_success)
		{
			return result;
		}
		dayCountFraction = interest;
		long intDays = 0;
		result = pyfront.getintdays(&intDays);
		if (result != return_success)
		{
			return result;
		}
		days = intDays;
		return return_success;
	}
	int  forecast(
		DateStruct &startDate, 
		DateStruct &endDate, 
		int dayCountRule, 
		int months, 
		int days)
	{
		Date_Funcs::date_union date1;
		date1.date.centuries = startDate.year / 100;
		date1.date.years = startDate.year % 100;
		date1.date.months = startDate.month;
		date1.date.days = startDate.day;
		Date_Funcs::date_union date2;

		int result = Py_Front::forecast(date1, months, days, dayCountRule, &date2);
		if (result != return_success)
		{
			return result;
		}

		endDate.day = date2.date.days;
		endDate.month = date2.date.months;
		endDate.year = date2.date.centuries * 100 + date2.date.years;

		return return_success;
	}

	int  tenor(DateStruct startDate, DateStruct endDate, int dayCountRule, int &tenor)
	{
		Date_Funcs::date_union date1;
		date1.date.centuries = startDate.year / 100;
		date1.date.years = startDate.year % 100;
		date1.date.months = startDate.month;
		date1.date.days = startDate.day;
		Date_Funcs::date_union date2;
		date2.date.centuries = endDate.year / 100;
		date2.date.years = endDate.year % 100;
		date2.date.months = endDate.month;
		date2.date.days = endDate.day;
		long days = tenor;
		int result = Py_Front::tenor(date1, date2, dayCountRule, &days);
		if (result != return_success)
		{
			return result;
		}
		tenor = (int)days;

		return return_success;

	}


