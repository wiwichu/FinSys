// FinCalc.cpp: implementation of the FinCalc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FinCalc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FinCalc::FinCalc()
{

}

FinCalc::~FinCalc()
{

}

string FinCalc::getINSTRUMENTCLASS_Text(_INSTRUMENTCLASS instrumentclass)
{
	string _INSTRUMENTCLASS_Text;
	
	switch (instrumentclass)
	{
	case GERMANBUND:
		_INSTRUMENTCLASS_Text.assign("GERMANBUND");
		break;
	case GOVOFJAPAN:
		_INSTRUMENTCLASS_Text.assign("GOVOFJAPAN");
		break;
	case EURO:
		_INSTRUMENTCLASS_Text.assign("EURO");
		break;
	case UKGILT:
		_INSTRUMENTCLASS_Text.assign("UKGILT");
		break;
	case UKCD:
		_INSTRUMENTCLASS_Text.assign("UKCD");
		break;
	case UKDSC:
		_INSTRUMENTCLASS_Text.assign("UKDSC");
		break;
	case USCD:
		_INSTRUMENTCLASS_Text.assign("USCD");
		break;
	case USDSC:
		_INSTRUMENTCLASS_Text.assign("USDSC");
		break;
	case USTBOND:
		_INSTRUMENTCLASS_Text.assign("USTBOND");
		break;
	case CP:
		_INSTRUMENTCLASS_Text.assign("CP");
		break;
	case FINANZSCHATZ:
		_INSTRUMENTCLASS_Text.assign("FINANZSCHATZ");
		break;
	case USCHATZ:
		_INSTRUMENTCLASS_Text.assign("USCHATZ");
		break;
	case USCHATZBUBA:
		_INSTRUMENTCLASS_Text.assign("USCHATZBUBA");
		break;
	case SCHULDSCHEIN:
		_INSTRUMENTCLASS_Text.assign("SCHULDSCHEIN");
		break;
	case MBS:
		_INSTRUMENTCLASS_Text.assign("MBS");
		break;
/*
	case FLOAT:
		_INSTRUMENTCLASS_Text.assign("FLOAT");
		break;
	case CASHFLOW:
		_INSTRUMENTCLASS_Text.assign("CASHFLOW");
		break;
*/
	default:
		_INSTRUMENTCLASS_Text.assign("BADINSTRUMENTCLASS");
		break;
	};

	return _INSTRUMENTCLASS_Text;
}
string FinCalc::getWEEKDAY_Text(_WEEKDAY weekday)
{
	string _WEEKDAY_Text;
	
	switch (weekday)
	{
	case _MONDAY:
		_WEEKDAY_Text.assign("MONDAY");
		break;
	case _TUESDAY:
		_WEEKDAY_Text.assign("TUESDAY");
		break;
	case _WEDNESDAY:
		_WEEKDAY_Text.assign("WEDNESDAY");
		break;
	case _THURSDAY:
		_WEEKDAY_Text.assign("THURSDAY");
		break;
	case _FRIDAY:
		_WEEKDAY_Text.assign("FRIDAY");
		break;
	case _SATURDAY:
		_WEEKDAY_Text.assign("SATURDAY");
		break;
	case _SUNDAY:
		_WEEKDAY_Text.assign("SUNDAY");
		break;
	default:
		_WEEKDAY_Text.assign("BADWEEKDAY");
		break;
	}
	return _WEEKDAY_Text;
}
string FinCalc::getCALENDARBASIS_Text(_CALENDARBASIS calendarbasis)
{
	string _CALENDARBASIS_Text;
	
	switch (calendarbasis)
	{
	case DATEACTCAL:
		_CALENDARBASIS_Text.assign("DATEACTCAL");
		break;
	case DATE30CAL:
		_CALENDARBASIS_Text.assign("DATE30CAL");
		break;
	case DATE30ECAL:
		_CALENDARBASIS_Text.assign("DATE30ECAL");
		break;
	default:
		_CALENDARBASIS_Text.assign("BADBASIS");
		break;
	}

	return _CALENDARBASIS_Text;
}

string FinCalc::getDAYCOUNT_Text(FinCalc::_DAYCOUNT daycount)
{
	string _DAYCOUNT_Text;
	
	switch (daycount)
	{
	case FinCalc::_30E_360:
		_DAYCOUNT_Text.assign("30E/360");
		break;
	case FinCalc::_30_360:
		_DAYCOUNT_Text.assign("30/360");
		break;
	case FinCalc::_ACT_360:
		_DAYCOUNT_Text.assign("ACT/360");
		break;
	case FinCalc::_ACT_365:
		_DAYCOUNT_Text.assign("ACT/365");
		break;
	case FinCalc::_ACT_365CD:
		_DAYCOUNT_Text.assign("ACT/365CD");
		break;
	case FinCalc::_ACT_ACT:
		_DAYCOUNT_Text.assign("ACT/ACT");
		break;
	case FinCalc::_ACT_366:
		_DAYCOUNT_Text.assign("ACT/366");
		break;
	default:
		_DAYCOUNT_Text.assign("BADDAYCOUNT");
		break;
	}

	return _DAYCOUNT_Text;
}

string FinCalc::getPERIOD_Text(FinCalc::_PERIOD period)
{
	string _PERIOD_Text;
	
	switch (period)
	{
	case FinCalc::_DAYS:
		_PERIOD_Text.assign("DAYS");
		break;
	case FinCalc::_MONTHS:
		_PERIOD_Text.assign("MONTHS");
		break;
	default:
		_PERIOD_Text.assign("BADPERIOD");
		break;
	}

	return _PERIOD_Text;
}

string FinCalc::getFREQUENCY_Text(FinCalc::_FREQUENCY frequency)
{
	string _FREQUENCY_Text;
	
	switch (frequency)
	{
	case FinCalc::_ANNUALLY:
		_FREQUENCY_Text.assign("ANNUALLY");
		break;
	case FinCalc::_SEMIANNUALLY:
		_FREQUENCY_Text.assign("SEMIANNUALLY");
		break;
	case FinCalc::_QUARTERLY:
		_FREQUENCY_Text.assign("QUARTERLY");
		break;
	case FinCalc::_MONTHLY:
		_FREQUENCY_Text.assign("MONTHLY");
		break;
	default:
		_FREQUENCY_Text.assign("BADFREQUENCY");
		break;
	}

	return _FREQUENCY_Text;
}

string FinCalc::getYIELDMETH_Text(FinCalc::_YIELDMETH yieldmeth)
{
	string _YIELDMETH_Text;
	
	switch (yieldmeth)
	{
	case FinCalc::_AIBD:
		_YIELDMETH_Text.assign("AIBD");
		break;
	case FinCalc::_MMDISC:
		_YIELDMETH_Text.assign("MONEY MARKET DISCOUNT");
		break;
	case FinCalc::_MM:
		_YIELDMETH_Text.assign("MONEY MARKET");
		break;
	case FinCalc::_YTMSIMP:
		_YIELDMETH_Text.assign("SIMPLE YIELD TO MATURITY");
		break;
	case FinCalc::_YTMCOMP:
		_YIELDMETH_Text.assign("COMPOUND YIELD TO MATURITY");
		break;
	case FinCalc::_SIMPJAP:
		_YIELDMETH_Text.assign("SIMPLE JAPANESE");
		break;
	case FinCalc::_CURRENT:
		_YIELDMETH_Text.assign("CURRENT");
		break;
	case FinCalc::_GREENWELLMONTAGU:
		_YIELDMETH_Text.assign("GREENWELL MONTAGU");
		break;
	case FinCalc::_MUNI:
		_YIELDMETH_Text.assign("MUNICIPAL BONDS");
		break;
	case FinCalc::_CORP:
		_YIELDMETH_Text.assign("US CORPORATE");
		break;
	case FinCalc::_USTR:
		_YIELDMETH_Text.assign("US TREASURY");
		break;
	case FinCalc::_MOOSMUELLER:
		_YIELDMETH_Text.assign("MOOSMUELLER");
		break;
	case FinCalc::_BRASSFANGMEYER:
		_YIELDMETH_Text.assign("_BRAESS FANGMEYER");
		break;
	case FinCalc::_TRUE:
		_YIELDMETH_Text.assign("TRUE");
		break;
	case FinCalc::_MBS:
		_YIELDMETH_Text.assign("MBS");
		break;
	case FinCalc::_BE:
		_YIELDMETH_Text.assign("BOND EQUIVALENT");
		break;
	default:
		_YIELDMETH_Text.assign("BADYIELDMETH");
		break;
	}

	return _YIELDMETH_Text;
}
