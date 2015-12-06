// PatCalc.cpp: implementation of the PatCalc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PatCalc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PatCalc::PatCalc()
: _instrumentclass(CLASSNOTSET)
,_yieldmeth(_YIELDMETHNOTSET)
{

	unsigned long _return_code = return_success;
	_return_code = py.init_screen();
	if (_return_code != return_success)
		throw new ExceptionCalc("Error Py_Front.init_screen().");

}

PatCalc::~PatCalc()
{

}
void	PatCalc::setClass(_INSTRUMENTCLASS instrumentclass)
{
	_instrumentclass = CLASSNOTSET;
	unsigned long _return_code = return_success;
	switch (instrumentclass)
	{
		case GERMANBUND:
			_return_code =  py.setclassdesc(instr_bund_class_desc);
			break;
		case GOVOFJAPAN:
			_return_code =  py.setclassdesc(instr_goj_class_desc);
			break;
		case EURO:
			_return_code =  py.setclassdesc(instr_euro_class_desc);
			break;
		case UKGILT:
			_return_code =  py.setclassdesc(instr_gilt_class_desc);
			break;
		case UKCD:
			_return_code =  py.setclassdesc(instr_ukcd_class_desc);
			break;
		case UKDSC:
			_return_code =  py.setclassdesc(instr_ukdsc_class_desc);
			break;
		case USCD:
			_return_code =  py.setclassdesc(instr_uscd_class_desc);
			break;
		case USDSC:
			_return_code =  py.setclassdesc(instr_usdsc_class_desc);
			break;
		case USTBOND:
			_return_code =  py.setclassdesc(instr_ustbo_class_desc);
			break;
		case CP:
			_return_code =  py.setclassdesc(instr_cp_class_desc);
			break;
		case FINANZSCHATZ:
			_return_code =  py.setclassdesc(instr_fschatz_class_desc);
			break;
		case USCHATZ:
			_return_code =  py.setclassdesc(instr_uschatz_class_desc);
			break;
		case USCHATZBUBA:
			_return_code =  py.setclassdesc(instr_uschatz_buba_class_desc);
			break;
		case SCHULDSCHEIN:
			_return_code =  py.setclassdesc(instr_ssd_class_desc);
			break;
		case MBS:
			_return_code =  py.setclassdesc(instr_mbs_class_desc);
			break;
/*
		case FLOAT:
			_return_code =  py.setclassdesc(instr_float_class_desc);
			break;
		case CASHFLOW:
			_return_code =  py.setclassdesc(instr_cashflow_class_desc);
			break;
*/

		default:
			throw new ExceptionCalc("Invalid Instrument Class.");
	}

	if (_return_code != return_success)
		throw new ExceptionCalc("Error in Py_Front.setclassdesc().");

	_return_code =  py.proc_class_desc();

	if (_return_code != return_success)
		throw new ExceptionCalc("Error in Py_Front.proc_class_desc().");

	_instrumentclass = instrumentclass;
}
long PatCalc::tenor (const string &startdate,const string &enddate, FinCalc::_CALENDARBASIS  caltype)
{
	long _tenor = 0;
	char _caltype;

	switch (caltype)
	{
	case DATEACTCAL:
		_caltype = date_act_cal;
		break;
	case DATE30CAL:
		_caltype = date_30_cal;
		break;
	case DATE30GERMANCAL:
		_caltype = date_30german_cal;
		break;
	case DATE30ECAL:
		_caltype = date_30e_cal;
		break;
	case DATE30USCAL:
		_caltype = date_30US_cal;
		break;
	case DATE30EPLUSCAL:
		_caltype = date_30eplus_cal;
		break;
	default:
			throw new ExceptionCalc("Invalid Day Count Basis.");
	}

	Date_Funcs::date_union _startdate;
	Date_Funcs::date_union _enddate;
	unsigned long _return_code = return_success;

	_startdate.date.centuries = atoi(startdate.substr(0,2).c_str());
	_startdate.date.years = atoi(startdate.substr(2,2).c_str());
	_startdate.date.months = atoi(startdate.substr(4,2).c_str());
	_startdate.date.days = atoi(startdate.substr(6,2).c_str());

	_return_code = Date_Funcs::CheckDate(((_startdate.date.centuries*100)+_startdate.date.years), 
							_startdate.date.months, _startdate.date.days);
	if (_return_code != return_success)
		throw new ExceptionCalc("Invalid Start Date.");

	_enddate.date.centuries = atoi(enddate.substr(0,2).c_str());
	_enddate.date.years = atoi(enddate.substr(2,2).c_str());
	_enddate.date.months = atoi(enddate.substr(4,2).c_str());
	_enddate.date.days = atoi(enddate.substr(6,2).c_str());

	_return_code = Date_Funcs::CheckDate(((_enddate.date.centuries*100)+_enddate.date.years), 
							_enddate.date.months, _enddate.date.days);
	if (_return_code != return_success)
		throw new ExceptionCalc("Invalid End Date.");
	_return_code = Date_Funcs::tenor(_startdate,_enddate,_caltype,&_tenor);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error in forecast.");

	return _tenor;
}
string PatCalc::forecast (const string &date,int months,long days, FinCalc::_CALENDARBASIS caltype)
{
	string _outdate;
	char _caltype;
	//int buffSize = 100;

	switch (caltype)
	{
	case DATEACTCAL:
		_caltype = date_act_cal;
		break;
	case DATE30CAL:
		_caltype = date_30_cal;
		break;
	case DATE30GERMANCAL:
		_caltype = date_30german_cal;
		break;
	case DATE30ECAL:
		_caltype = date_30e_cal;
		break;
	case DATE30EPLUSCAL:
		_caltype = date_30eplus_cal;
		break;
	default:
			throw new ExceptionCalc("Invalid Day Count Basis.");
	}

	Date_Funcs::date_union _day;
	Date_Funcs::date_union _returndate;
	_day.date.centuries = atoi(date.substr(0,2).c_str());
	_day.date.years = atoi(date.substr(2,2).c_str());
	_day.date.months = atoi(date.substr(4,2).c_str());
	_day.date.days = atoi(date.substr(6,2).c_str());

	unsigned long _return_code = return_success;

	_return_code = Date_Funcs::CheckDate(((_day.date.centuries*100)+_day.date.years), 
							_day.date.months, _day.date.days);
	if (_return_code != return_success)
		throw new ExceptionCalc("Invalid Date.");
	_return_code = Date_Funcs::forecast(_day,months,days,_caltype,&_returndate);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error in forecast.");

	//char datepiece[2];
	//_itoa(_returndate.date.centuries,datepiece,buffSize);
	if (_returndate.date.centuries < 10) 
		_outdate.assign("0");
	else
		_outdate.assign("");
	string c = to_string(_returndate.date.centuries);
	_outdate.append(c);
	//_outdate.append(datepiece);
	//_itoa(_returndate.date.years,datepiece,buffSize);
	if (_returndate.date.years < 10) _outdate.append("0");
	//_outdate.append(datepiece);
	//_itoa(_returndate.date.months,datepiece,buffSize);
	string y = to_string(_returndate.date.years);
	_outdate.append(y);
	if (_returndate.date.months < 10) _outdate.append("0");
	//_outdate.append(datepiece);
	//_itoa(_returndate.date.days,datepiece,buffSize);
	string m = to_string(_returndate.date.months);
	_outdate.append(m);
	if (_returndate.date.days < 10) _outdate.append("0");
	//_outdate.append(datepiece);
	string d = to_string(_returndate.date.days);
	_outdate.append(d);

	return _outdate;
}

FinCalc::_WEEKDAY PatCalc::findday(const string & date)
{
	FinCalc::_WEEKDAY _weekday = FinCalc::_WEEKDAYNOTSET;

	Date_Funcs::date_union _day;
	_day.date.centuries = atoi(date.substr(0,2).c_str());
	_day.date.years = atoi(date.substr(2,2).c_str());
	_day.date.months = atoi(date.substr(4,2).c_str());
	_day.date.days = atoi(date.substr(6,2).c_str());

	char _chday = 0;
	unsigned long _return_code = return_success;

	_return_code = Date_Funcs::CheckDate(((_day.date.centuries*100)+_day.date.years), 
							_day.date.months, _day.date.days);
	if (_return_code != return_success)
		return FinCalc::_BADDAY;
	_return_code = Date_Funcs::findday(_day,&_chday);
	if (_return_code != return_success)
		return FinCalc::_BADDAY;


	switch (_chday)
	{
		case 0:
		{
			_weekday = FinCalc::_SUNDAY;
			break;
		}
		case 1:
		{
			_weekday = FinCalc::_MONDAY;
			break;
		}
		case 2:
		{
			_weekday = FinCalc::_TUESDAY;
			break;
		}
		case 3:
		{
			_weekday = FinCalc::_WEDNESDAY;
			break;
		}
		case 4:
		{
			_weekday = FinCalc::_THURSDAY;
			break;
		}
		case 5:
		{
			_weekday = FinCalc::_FRIDAY;
			break;
		}
		case 6:
		{
			_weekday = FinCalc::_SATURDAY;
			break;
		}
		default:
		{
			throw new ExceptionCalc("Invalid Day of Week returned.");
		}

	}

	return _weekday;
}

int	PatCalc::getPayfreqlength()
{
	int _payfreq;

	unsigned long _return_code = return_success;
	_return_code =  py.getpayfreqlength(&_payfreq);
	if (_return_code != return_success)
		throw new ExceptionCalc("Payment Frequency not set.");

	return _payfreq;

}

FinCalc::_PERIOD PatCalc::getPayfreqperiod()
{
	FinCalc::_PERIOD _period = FinCalc::_PERIODNOTSET;
	int _payfreq;

	unsigned long _return_code = return_success;
	_return_code =  py.getpayfreqperiod(&_payfreq);
	if (_return_code != return_success)
		throw new ExceptionCalc("Payment Frequency not set.");

	_period = convertPayfreqperiod(_payfreq);

	return _period;

}
int	PatCalc::getPayfreqlengthYield()
{
	int _payfreq;

	unsigned long _return_code = return_success;
	_return_code =  py.getpayfreqlengthyield(&_payfreq);
	if (_return_code != return_success)
		throw new ExceptionCalc("Payment Frequency not set.");

	return _payfreq;

}
FinCalc::_PERIOD	PatCalc::getPayfreqperiodYield()
{
	FinCalc::_PERIOD _period = FinCalc::_PERIODNOTSET;
	int _payfreq;

	unsigned long _return_code = return_success;
	_return_code =  py.getpayfreqperiodyield(&_payfreq);
	if (_return_code != return_success)
		throw new ExceptionCalc("Payment Frequency not set.");

	_period = convertPayfreqperiod(_payfreq);

	return _period;

}

FinCalc::_PERIOD PatCalc::convertPayfreqperiod(int rawPayfreq)
{
	FinCalc::_PERIOD _period = FinCalc::_PERIODNOTSET;

	switch (rawPayfreq)
	{
		case event_sched_day_period:
		{
			_period = FinCalc::_DAYS;
			break;
		}
		case event_sched_month_period:
		{
			_period = FinCalc::_MONTHS;
			break;
		}
		default:
		{
			throw new ExceptionCalc("Payment Frequency not set.");
		}

	}

	return _period;

}

FinCalc::_DAYCOUNT	PatCalc::getDaycount()
{
	FinCalc::_DAYCOUNT _daycount = FinCalc::_DAYCOUNTNOTSET;

	int _daycountnumber;

	unsigned long _return_code = return_success;
	_return_code =  py.getdaycount(&_daycountnumber);
	if (_return_code != return_success)
		throw new ExceptionCalc("Day Count not set.");

	_daycount = convertDaycount(_daycountnumber);

	return _daycount;
}

FinCalc::_DAYCOUNT	PatCalc::getDaycountYield()
{
	FinCalc::_DAYCOUNT _daycount = FinCalc::_DAYCOUNTNOTSET;

	int _daycountnumber;

	unsigned long _return_code = return_success;
	_return_code =  py.getyielddays(&_daycountnumber);
	if (_return_code != return_success)
		throw new ExceptionCalc("Day Count not set.");

	_daycount = convertDaycount(_daycountnumber);

	return _daycount;
}

FinCalc::_DAYCOUNT	PatCalc::convertDaycount(int rawDaycount)
{
	FinCalc::_DAYCOUNT _daycount = FinCalc::_DAYCOUNTNOTSET;

	switch (rawDaycount)
	{
	
		case date_30e_360_day_count:
		{
			_daycount = FinCalc::_30E_360;
			break;
		}
		case date_30eplus_360_day_count:
		{
			_daycount = FinCalc::_30EPLUS_360;
			break;
		}
		case date_30_360_day_count:
		{
			_daycount = FinCalc::_30_360;
			break;
		}
		case date_30_360US_day_count:
		{
			_daycount = FinCalc::_30_360US;
			break;
		}
		case date_30_360german_day_count:
		{
			_daycount = FinCalc::_30_360GERMAN;
			break;
		}
		case date_act_360_day_count:
		{
			_daycount = FinCalc::_ACT_360;
			break;
		}
		case date_act_365_day_count:
		{
			_daycount = FinCalc::_ACT_365;
			break;
		}
		case date_NL_365_day_count:
		{
			_daycount = FinCalc::_NL_365;
			break;
		}
		case date_act_365cd_day_count:
		{
			_daycount = FinCalc::_ACT_365CD;
			break;
		}
		case date_act_act_day_count:
		{
			_daycount = FinCalc::_ACT_ACT;
			break;
		}
		case date_act_365L_day_count:
		{
			_daycount = FinCalc::_ACT_365L;
			break;
		}
		case date_act_365A_day_count:
		{
			_daycount = FinCalc::_ACT_365A;
			break;
		}
		case date_act_366_day_count:
		{
			_daycount = FinCalc::_ACT_366;
			break;
		}
		case date_act_actISDA_day_count:
		{
			_daycount = FinCalc::_ACT_ISDA;
			break;
		}
		default:
		{
			throw new ExceptionCalc("Day Count not set or invalid.");
		}

	}
	return _daycount;
}

int	PatCalc::convertDaycount(FinCalc::_DAYCOUNT rawDaycount)
{

	int _daycount;	
	
	switch (rawDaycount)
	{
	
		case FinCalc::_30E_360:
		{
			_daycount = date_30e_360_day_count;
			break;
		}
		case FinCalc::_30EPLUS_360:
		{
			_daycount = date_30eplus_360_day_count;
			break;
		}
		case FinCalc::_30_360:
		{
			_daycount = date_30_360_day_count;
			break;
		}
		case FinCalc::_30_360US:
		{
			_daycount = date_30_360US_day_count;
			break;
		}
		case FinCalc::_30_360GERMAN:
		{
			_daycount = date_30_360german_day_count;
			break;
		}
		case FinCalc::_ACT_360:
		{
			_daycount = date_act_360_day_count;
			break;
		}
		case FinCalc::_ACT_365:
		{
			_daycount = date_act_365_day_count;
			break;
		}
		case FinCalc::_NL_365:
		{
			_daycount = date_NL_365_day_count;
			break;
		}
		case FinCalc::_ACT_365CD:
		{
			_daycount = date_act_365cd_day_count;
			break;
		}
		case FinCalc::_ACT_ACT:
		{
			_daycount = date_act_act_day_count;
			break;
		}
		case FinCalc::_ACT_365L:
		{
			_daycount = date_act_365L_day_count;
			break;
		}
		case FinCalc::_ACT_365A:
		{
			_daycount = date_act_365A_day_count;
			break;
		}
		case FinCalc::_ACT_366:
		{
			_daycount = date_act_366_day_count;
			break;
		}
		case FinCalc::_ACT_ISDA:
		{
			_daycount = date_act_actISDA_day_count;
			break;
		}
		default:
		{
			throw new ExceptionCalc("Day Count invalid.");
		}
	}
	return _daycount;
}
void PatCalc::setInterestRate(long double interestrate)
{

	unsigned long _return_code = return_success;
	_return_code =  py.setintrate(interestrate);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting interest rate.");
	return;
}
void PatCalc::setValueDate(string &date)
{


	Date_Funcs::date_union _valuedate;

	_valuedate.date.centuries = atoi(date.substr(0,2).c_str());
	_valuedate.date.years = atoi(date.substr(2,2).c_str());
	_valuedate.date.months = atoi(date.substr(4,2).c_str());
	_valuedate.date.days = atoi(date.substr(6,2).c_str());

	unsigned long _return_code = return_success;
	_return_code = py.setvaldate(_valuedate);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting value date.");
	return;

}
string PatCalc::getValueDate()
{
	int buffSize = 10;
	string _outdate;
	Date_Funcs::date_union _returndate;
	unsigned long _return_code = return_success;
	_return_code = py.getvaldate(_returndate);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting value date.");

	//char datepiece[2];
	//_itoa(_returndate.date.centuries,datepiece,buffSize);
	if (_returndate.date.centuries < 10) 
		_outdate.assign("0");
	else
		_outdate.assign("");
	string c = to_string(_returndate.date.centuries);
	_outdate.append(c);
	//_outdate.append(datepiece);
	//_itoa(_returndate.date.years,datepiece,buffSize);
	if (_returndate.date.years < 10) _outdate.append("0");
	string y = to_string(_returndate.date.years);
	_outdate.append(y);
	//_outdate.append(datepiece);
	//_itoa(_returndate.date.months,datepiece,buffSize);
	if (_returndate.date.months < 10) _outdate.append("0");
	string m = to_string(_returndate.date.months);
	_outdate.append(m);
	//_outdate.append(datepiece);
	//_itoa(_returndate.date.days,datepiece,buffSize);
	if (_returndate.date.days < 10) _outdate.append("0");
	//_outdate.append(datepiece);
	string d = to_string(_returndate.date.days);
	_outdate.append(d);

	return _outdate;

	
}
void PatCalc::setMaturityDate(string &date)
{

	Date_Funcs::date_union _date;

	_date.date.centuries = atoi(date.substr(0,2).c_str());
	_date.date.years = atoi(date.substr(2,2).c_str());
	_date.date.months = atoi(date.substr(4,2).c_str());
	_date.date.days = atoi(date.substr(6,2).c_str());

	unsigned long _return_code = return_success;
	_return_code = py.setmatdate(_date);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting maturity date.");
	return;

}
string PatCalc::getMaturityDate()
{

	//int buffSize = 10;
	string _outdate;
	Date_Funcs::date_union _returndate;
	unsigned long _return_code = return_success;
	_return_code = py.getmatdate(_returndate);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting maturity date.");

	//char datepiece[2];
	//_itoa(_returndate.date.centuries,datepiece,buffSize);
	if (_returndate.date.centuries < 10) 
		_outdate.assign("0");
	else
		_outdate.assign("");
	string c = to_string(_returndate.date.centuries);
	_outdate.append(c);
	//_itoa(_returndate.date.years,datepiece,buffSize);
	if (_returndate.date.years < 10) _outdate.append("0");
	//_outdate.append(datepiece);
	string y = to_string(_returndate.date.years);
	_outdate.append(y);

	//_itoa(_returndate.date.months,datepiece,buffSize);
	if (_returndate.date.months < 10) _outdate.append("0");
	string m = to_string(_returndate.date.months);
	_outdate.append(m);
	//_outdate.append(datepiece);
	//_itoa(_returndate.date.days,datepiece,buffSize);
	if (_returndate.date.days < 10) _outdate.append("0");
	string d = to_string(_returndate.date.days);
	_outdate.append(d);
	//_outdate.append(datepiece);

	return _outdate;

	
}
void PatCalc::setIssueDate(string &date)
{

	Date_Funcs::date_union _date;

	_date.date.centuries = atoi(date.substr(0,2).c_str());
	_date.date.years = atoi(date.substr(2,2).c_str());
	_date.date.months = atoi(date.substr(4,2).c_str());
	_date.date.days = atoi(date.substr(6,2).c_str());

	unsigned long _return_code = return_success;
	_return_code = py.setissuedate(_date);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting issue date.");
	return;
}
string PatCalc::getIssueDate()
{

	string _outdate;
	char _chardate[20];
//	Date_Funcs::date_union _returndate;
	unsigned long _return_code = return_success;
//	_return_code = py.getissuedate(_returndate);
	_return_code = py.getissuedate(_chardate);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting issue date.");
	_outdate.assign(_chardate);
	string _return_date(_outdate.substr(6,4) +
		_outdate.substr(0,2) +
		_outdate.substr(3,2));
	return _return_date;
}
void PatCalc::setFirstPayDate(string &date)
{

	Date_Funcs::date_union _date;

	_date.date.centuries = atoi(date.substr(0,2).c_str());
	_date.date.years = atoi(date.substr(2,2).c_str());
	_date.date.months = atoi(date.substr(4,2).c_str());
	_date.date.days = atoi(date.substr(6,2).c_str());

	unsigned long _return_code = return_success;
	_return_code = py.setfirstdate(_date);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting first pay date.");
	return;
}
string PatCalc::getFirstPayDate()
{

	string _outdate;
	char _chardate[20];
//	Date_Funcs::date_union _returndate;
	unsigned long _return_code = return_success;
//	_return_code = py.getissuedate(_returndate);
	_return_code = py.getfirstdate(_chardate);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting first pay date.");
/*
	char datepiece[2];
	_itoa(_returndate.date.centuries,datepiece,10);
	if (_returndate.date.centuries < 10) 
		_outdate.assign("0");
	else
		_outdate.assign("");
	_outdate.append(datepiece);
	_itoa(_returndate.date.years,datepiece,10);
	if (_returndate.date.years < 10) _outdate.append("0");
	_outdate.append(datepiece);
	_itoa(_returndate.date.months,datepiece,10);
	if (_returndate.date.months < 10) _outdate.append("0");
	_outdate.append(datepiece);
	_itoa(_returndate.date.days,datepiece,10);
	if (_returndate.date.days < 10) _outdate.append("0");
	_outdate.append(datepiece);
*/

	_outdate.assign(_chardate);
	string _return_date(_outdate.substr(6,4) +
		_outdate.substr(0,2) +
		_outdate.substr(3,2));
	return _return_date;
}
void PatCalc::setNextToLastPayDate(string &date)
{

	Date_Funcs::date_union _date;

	_date.date.centuries = atoi(date.substr(0,2).c_str());
	_date.date.years = atoi(date.substr(2,2).c_str());
	_date.date.months = atoi(date.substr(4,2).c_str());
	_date.date.days = atoi(date.substr(6,2).c_str());

	unsigned long _return_code = return_success;
	_return_code = py.setpenultdate(_date);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting next to last pay date.");
	return;
}
string PatCalc::getNextToLastPayDate()
{

	string _outdate;
	char _chardate[20];
//	Date_Funcs::date_union _returndate;
	unsigned long _return_code = return_success;
//	_return_code = py.getissuedate(_returndate);
	_return_code = py.getpenultdate(_chardate);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting next to last pay date.");

	_outdate.assign(_chardate);
	string _return_date(_outdate.substr(6,4) +
		_outdate.substr(0,2) +
		_outdate.substr(3,2));
	return _return_date;

}
void PatCalc::setDates(string valueDate,
					string maturityDate,
					string issueDate,
					string firstpayDate,
					string nextToLastPayDate)
{
	setValueDate(valueDate);
	setMaturityDate(maturityDate);
	unsigned long _return_code = return_success;
	_return_code =  py.proc_def_dates();
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting default dates.");

	if (!issueDate.empty()) setIssueDate(issueDate);
	if (!firstpayDate.empty()) setFirstPayDate(firstpayDate);
	if (!nextToLastPayDate.empty()) setNextToLastPayDate(nextToLastPayDate);
	return;
}
void PatCalc::setPrice(long double price)
{
	unsigned long _return_code = return_success;
	_return_code =  py.setinprice(price);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting price.");
}
long double PatCalc::getPrice()
{
	long double _price;
	unsigned long _return_code = return_success;
	_return_code =  py.getinprice(&_price);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting price.");
	return _price;
}
long double PatCalc::getInterestRate()
{
	long double _interest;
	unsigned long _return_code = return_success;
	_return_code =  py.getintrate(&_interest);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting interest rate.");
	return _interest;
}
long double PatCalc::getInterest()
{
	long double _interest;
	unsigned long _return_code = return_success;
	_return_code =  py.getinterest(&_interest);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting interest.");
	return _interest;
}
long double PatCalc::getPriceResult()
{
	long double _price;
	unsigned long _return_code = return_success;
	_return_code =  py.getoutprice(&_price);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting price.");
	return _price;
}
void PatCalc::setYield(long double yield)
{
	unsigned long _return_code = return_success;
	_return_code =  py.setinyield(yield);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting yield.");
}
long double PatCalc::getYield()
{
	long double _yield;
	unsigned long _return_code = return_success;
	_return_code =  py.getinyield(&_yield);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting yield.");
	return _yield;
}
long double PatCalc::getYieldResult()
{
	long double _yield;
	unsigned long _return_code = return_success;
	_return_code =  py.getoutyield(&_yield);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error getting yield.");
	return _yield;
}
long double PatCalc::calcYield()
{
	unsigned long _return_code = return_success;

	if (_BE == getYieldMethod())
		BEAdjust();

	_return_code = py.setcalcwhat(py_yield_from_price_calc_what);
	if (_return_code) throw new ExceptionCalc("set calc error.");

	_return_code =  py.proc_calc_what( );
	if (_return_code) throw new ExceptionCalc("proc calc error.");

	_return_code =  py.check_all_parms();
	if (_return_code) throw new ExceptionCalc("check parms error.");
/*
	_return_code =  py.calc_int();
	if (_return_code) throw new ExceptionCalc("Error calculating interest.");
*/
	_return_code =  py.calc_py();
	if (_return_code) throw new ExceptionCalc("calc error.");

	return getYieldResult();
}
long double PatCalc::calcPrice()
{
	unsigned long _return_code = return_success;

	if (_BE == getYieldMethod())
		BEAdjust();

	_return_code = py.setcalcwhat(py_price_from_yield_calc_what);
	if (_return_code) throw new ExceptionCalc("set calc error.");

	_return_code =  py.proc_calc_what( );
	if (_return_code) throw new ExceptionCalc("proc calc error.");

	_return_code =  py.check_all_parms();
	if (_return_code) throw new ExceptionCalc("check parms error.");
/*
	_return_code =  py.calc_int();
	if (_return_code) throw new ExceptionCalc("Error calculating interest.");
*/
	_return_code =  py.calc_py();
	if (_return_code) throw new ExceptionCalc("calc error.");

	return getPriceResult();
}

void PatCalc::BEAdjust()
{

	if (_BE == getYieldMethod())
	{
		string _valDate(getValueDate());
		string _matDate(getMaturityDate());
		long _tenor = tenor (_valDate,_matDate, DATEACTCAL);
		if (_tenor > 182)
		{
			setPayfreqlengthYield(_SEMIANNUALLY);
		}
		else
		{
			setPayfreqlengthYield(_ANNUALLY);
		}
	}
}

FinCalc::_YIELDMETH	PatCalc::getYieldMethod()
{
	int _yieldmeth;

	FinCalc::_YIELDMETH _yieldmethreturn;

	unsigned long _return_code = return_success;
	_return_code =  py.getyieldmeth(&_yieldmeth);
	if (_return_code != return_success)
		throw new ExceptionCalc("Yield Method not set.");
	
	switch (_yieldmeth)
	{
	case py_aibd_yield_meth:
		_yieldmethreturn = FinCalc::_AIBD;
		break;
	case py_mmdisc_yield_meth:
		_yieldmethreturn = FinCalc::_MMDISC;
		break;
	case py_mm_yield_meth:
		_yieldmethreturn = FinCalc::_MM;
		break;
	case py_ytm_simp_yield_meth:
		_yieldmethreturn = FinCalc::_YTMSIMP;
		break;
	case py_ytm_comp_yield_meth:
		_yieldmethreturn = FinCalc::_YTMCOMP;
		break;
	case py_simp_yield_meth:
		_yieldmethreturn = FinCalc::_SIMPJAP;
		break;
	case py_curr_yield_meth:
		_yieldmethreturn = FinCalc::_CURRENT;
		break;
	case py_gm_yield_meth:
		_yieldmethreturn = FinCalc::_GREENWELLMONTAGU;
		break;
	case py_muni_yield_meth:
		_yieldmethreturn = FinCalc::_MUNI;
		break;
	case py_corp_yield_meth:
		_yieldmethreturn = FinCalc::_CORP;
		break;
	case py_ustr_yield_meth:
		_yieldmethreturn = FinCalc::_USTR;
		break;
	case py_moos_yield_meth:
		_yieldmethreturn = FinCalc::_MOOSMUELLER;
		break;
	case py_bf_yield_meth:
		_yieldmethreturn = FinCalc::_BRASSFANGMEYER;
		break;
	case py_ty_yield_meth:
		_yieldmethreturn = FinCalc::_TRUE;
		break;
	case py_MBS_yield_meth:
		_yieldmethreturn = FinCalc::_MBS;
		break;
	default:
		throw new ExceptionCalc("Invalid Yield Method.");
		break;
	}

	return _yieldmethreturn;
}
void PatCalc::setYieldMethod(FinCalc::_YIELDMETH yieldmeth)
{
	char _chym;

	_yieldmeth = _YIELDMETHNOTSET;
	
	switch (yieldmeth)
	{
	case FinCalc::_AIBD:
		_chym = py_aibd_yield_meth;
		break;
	case FinCalc::_MMDISC:
		_chym = py_mmdisc_yield_meth;
		break;
	case FinCalc::_BE:
		setDaycountYield(_ACT_ACT);
	case FinCalc::_MM:
		_chym = py_mm_yield_meth;
		break;
	case FinCalc::_YTMSIMP:
		_chym = py_ytm_simp_yield_meth;
		break;
	case FinCalc::_YTMCOMP:
		_chym = py_ytm_comp_yield_meth;
		break;
	case FinCalc::_SIMPJAP:
		_chym = py_simp_yield_meth;
		break;
	case FinCalc::_CURRENT:
		_chym = py_curr_yield_meth;
		break;
	case FinCalc::_GREENWELLMONTAGU:
		_chym = py_gm_yield_meth;
		break;
	case FinCalc::_MUNI:
		_chym = py_muni_yield_meth;
		break;
	case FinCalc::_CORP:
		_chym = py_corp_yield_meth;
		break;
	case FinCalc::_USTR:
		_chym = py_ustr_yield_meth;
		break;
	case FinCalc::_MOOSMUELLER:
		_chym = py_moos_yield_meth;
		break;
	case FinCalc::_BRASSFANGMEYER:
		_chym = py_bf_yield_meth;
		break;
	case FinCalc::_TRUE:
		_chym = py_ty_yield_meth;
		break;
	case FinCalc::_MBS:
		_chym = py_MBS_yield_meth;
		break;
	default:
		throw new ExceptionCalc("Invalid Yield Method.");
		break;
	}

	unsigned long _return_code = return_success;
	_return_code =  py.setyieldmeth(_chym);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting yield method.");
	_return_code =  py.proc_yield_meth();
	if (_return_code != return_success)
		throw new ExceptionCalc("Error processing yield method.");

	_yieldmeth = yieldmeth;
}
void	PatCalc::setDaycount(FinCalc::_DAYCOUNT daycount)
{
	int _daycount = convertDaycount(daycount);

	unsigned long _return_code = return_success;
	_return_code =  py.setdaycount(_daycount);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting day count.");
	_return_code =  py.proc_day_count();
	if (_return_code != return_success)
		throw new ExceptionCalc("Error processing day count.");

}
void	PatCalc::setDaycountYield(FinCalc::_DAYCOUNT daycount)
{
	int _daycount = convertDaycount(daycount);

	unsigned long _return_code = return_success;
	_return_code =  py.setyielddays(_daycount);
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting yield day count.");
	_return_code =  py.proc_yield_days();
	if (_return_code != return_success)
		throw new ExceptionCalc("Error processing yield day count.");
}
void	PatCalc::setPayfreqlength(_FREQUENCY frequency)
{

	unsigned long _return_code = return_success;
	_return_code =  py.setpayfreq(convertFrequency(frequency));
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting payment frequency.");
	_return_code =  py.proc_pay_freq();
	if (_return_code != return_success)
		throw new ExceptionCalc("Error processing payment frequency.");
}
/*
void	PatCalc::setPayfreqperiod(FinCalc::_PERIOD pfperiod)
{
}
*/
void	PatCalc::setPayfreqlengthYield(_FREQUENCY frequency)
{

	unsigned long _return_code = return_success;
	_return_code =  py.setyieldfreq(convertFrequency(frequency));
	if (_return_code != return_success)
		throw new ExceptionCalc("Error setting yield frequency.");
	_return_code =  py.proc_yield_freq();
	if (_return_code != return_success)
		throw new ExceptionCalc("Error processing yield frequency.");
}

int	PatCalc::convertFrequency(_FREQUENCY frequency)
{

	int _frequency;	
	
	switch (frequency)
	{
	
		case FinCalc::_ANNUALLY:
		{
			_frequency = 0;
			break;
		}
		case FinCalc::_MONTHLY:
		{
			_frequency = 1;
			break;
		}
		case FinCalc::_QUARTERLY:
		{
			_frequency = 2;
			break;
		}
		case FinCalc::_SEMIANNUALLY:
		{
			_frequency = 3;
			break;
		}
		default:
		{
			throw new ExceptionCalc("Frequency invalid.");
		}
	}
	return _frequency;
}

long double PatCalc::calcYieldandInt()
{
	unsigned long _return_code = return_success;

	if (_BE == getYieldMethod())
		BEAdjust();

	_return_code = py.setcalcwhat(py_yield_from_price_calc_what);
	if (_return_code) throw new ExceptionCalc("set calc error.");

	_return_code =  py.proc_calc_what( );
	if (_return_code) throw new ExceptionCalc("proc calc error.");

	_return_code =  py.check_all_parms();
	if (_return_code) throw new ExceptionCalc("check parms error.");

	_return_code =  py.calc_int();
	if (_return_code) throw new ExceptionCalc("Error calculating interest.");

	_return_code =  py.calc_py();
	if (_return_code) throw new ExceptionCalc("calc error.");

	return getYieldResult();
}
long double PatCalc::calcPriceandInt()
{
	unsigned long _return_code = return_success;

	if (_BE == getYieldMethod())
		BEAdjust();

	_return_code = py.setcalcwhat(py_price_from_yield_calc_what);
	if (_return_code) throw new ExceptionCalc("set calc error.");

	_return_code =  py.proc_calc_what( );
	if (_return_code) throw new ExceptionCalc("proc calc error.");

	_return_code =  py.check_all_parms();
	if (_return_code) throw new ExceptionCalc("check parms error.");

	_return_code =  py.calc_int();
	if (_return_code) throw new ExceptionCalc("Error calculating interest.");

	_return_code =  py.calc_py();
	if (_return_code) throw new ExceptionCalc("calc error.");

	return getPriceResult();
}
/*
void	PatCalc::setPayfreqperiodYield(FinCalc::_PERIOD pfperiod)
{
}
*/