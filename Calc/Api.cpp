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
int getInstrumentDefaults(InstrumentStruct &instrument)
{
	Py_Front pyfront;
	pyfront.init_screen();
	pyfront.setclassdesc(instr_class_descs[instrument.instrumentClass]);
	pyfront.proc_class_desc();
	int result = return_success;
	//instrument.instrumentClass = 3;
	//instrument.intDayCount = 4;
	//instrument.maturityDate->day = 1;
	//instrument.maturityDate->month = 1;
	//instrument.maturityDate->year = 2001;
	char charArg = 0;
	int intArg = 0;
	pyfront.getclassnumber(&charArg);
	instrument.instrumentClass = (int)charArg;
	pyfront.getdaycount(&intArg);
	instrument.intDayCount = intArg;
	pyfront.getpayfreq(&intArg);
	instrument.intPayFreq = intArg;
	Date_Funcs::date_union dateArg;
	//Date_Funcs::date_union *datePoint = new Date_Funcs::date_union();
	//pyfront.getmatdate(dateArg);
	//instrument.maturityDate->day = (int)dateArg.date.days;
	//instrument.maturityDate->month = (int)dateArg.date.months;
	//instrument.maturityDate->year = (int)dateArg.date.years;
	return result;
}
