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
	int result = return_success;
	instrument.instrumentClass = 3;
	instrument.intDayCount = 4;
	instrument.maturityDate->day = 1;
	instrument.maturityDate->month = 1;
	instrument.maturityDate->year = 2001;
	return result;
}
