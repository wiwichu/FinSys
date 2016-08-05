// FinCalc.h: interface for the FinCalc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINCALC_H__A88BA963_EBE3_11D5_9053_00105A1E6A31__INCLUDED_)
#define AFX_FINCALC_H__A88BA963_EBE3_11D5_9053_00105A1E6A31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "Calc.h"
#include <string>
#include <map>
#include "ExceptionCalc.h"

using namespace std;

class CALC_API FinCalc  
//class FinCalc  
{
public:
	static enum _WEEKDAY {	_WEEKDAYNOTSET=0,_MONDAY,_TUESDAY,_WEDNESDAY,_THURSDAY,
					_FRIDAY,_SATURDAY,_SUNDAY,_BADDAY};
	static enum _CALENDARBASIS {BASISNOTSET,DATEACTCAL,DATE30CAL,DATE30ECAL,_BADBASIS};
	static enum _INSTRUMENTCLASS {CLASSNOTSET,GERMANBUND,GOVOFJAPAN,EURO,UKGILT,UKCD,UKDSC,
				USCD,USDSC,USTBOND,CP,FINANZSCHATZ,USCHATZ,USCHATZBUBA,SCHULDSCHEIN,MBS,
//				FLOAT,CASHFLOW
				};
	static enum _DAYCOUNT {_DAYCOUNTNOTSET,
				_30E_360,_30_360,_ACT_360,_ACT_365,_ACT_365CD,_ACT_ACT,_ACT_366};
	static enum _PERIOD {_PERIODNOTSET,_DAYS,_MONTHS};
	static enum _FREQUENCY {_FREQUENCYNOTSET,_ANNUALLY,_SEMIANNUALLY,_QUARTERLY,_MONTHLY};
	static enum _YIELDMETH {_YIELDMETHNOTSET,_AIBD,_MMDISC,_MM,_YTMSIMP,_YTMCOMP,_SIMPJAP
						,_CURRENT,_GREENWELLMONTAGU,_MUNI,_CORP,_USTR,_MOOSMUELLER
						,_BRASSFANGMEYER,_TRUE,_MBS,_BE};


	
	
	static string getWEEKDAY_Text(_WEEKDAY weekday);
	static string getCALENDARBASIS_Text(_CALENDARBASIS calendarbasis);
	static string getINSTRUMENTCLASS_Text(_INSTRUMENTCLASS instrumentclass);
	static string getDAYCOUNT_Text(_DAYCOUNT daycount);
	static string getPERIOD_Text(_PERIOD period);
	static string getFREQUENCY_Text(_FREQUENCY frequency);
	static string getYIELDMETH_Text(_YIELDMETH yieldmeth);

	virtual _WEEKDAY findday(const string & date) = 0;

	virtual string	forecast (const string &date,int months,long days, FinCalc::_CALENDARBASIS ) = 0;
	virtual long	tenor (const string &startdate,const string &enddate, FinCalc::_CALENDARBASIS ) = 0;
	virtual void	setClass(_INSTRUMENTCLASS instrumentclass) = 0;
	virtual _DAYCOUNT	getDaycount() = 0;
	virtual _DAYCOUNT	getDaycountYield() = 0;
	virtual int	getPayfreqlength() = 0;
	virtual _PERIOD	getPayfreqperiod() = 0;
	virtual int	getPayfreqlengthYield() = 0;
	virtual _PERIOD	getPayfreqperiodYield() = 0;

	virtual void	setDaycount(_DAYCOUNT daycount) = 0;
	virtual void	setDaycountYield(_DAYCOUNT daycount) = 0;
	virtual void	setPayfreqlength(_FREQUENCY frequency) = 0;
//	virtual void	setPayfreqperiod(_PERIOD pfperiod) = 0;
	virtual void	setPayfreqlengthYield(_FREQUENCY frequency) = 0;
//	virtual void	setPayfreqperiodYield(_PERIOD pfperiod) = 0;
	virtual _YIELDMETH	getYieldMethod() = 0;
	virtual void setYieldMethod(_YIELDMETH yieldmeth) = 0;
	virtual void setInterestRate(long double interestrate) = 0;
	virtual void setValueDate(string &date) = 0;
	virtual string getValueDate() = 0;
	virtual void setMaturityDate(string &date) = 0;
	virtual string getMaturityDate() = 0;
	virtual void setIssueDate(string &date) = 0;
	virtual string getIssueDate() = 0;
	virtual void setFirstPayDate(string &date) = 0;
	virtual string getFirstPayDate() = 0;
	virtual void setNextToLastPayDate(string &date) = 0;
	virtual string getNextToLastPayDate() = 0;
	virtual void setDates(string valueDate,
						string maturityDate,
						string issueDate="",
						string firstpayDate="",
						string nextToLastPayDate="") = 0;
	virtual void setPrice(long double price) = 0;
	virtual long double getPrice() = 0;
	virtual long double getPriceResult() = 0;
	virtual void setYield(long double yield) = 0;
	virtual long double getYield() = 0;
	virtual long double getInterestRate() = 0;
	virtual long double getInterest() = 0;
	virtual long double getYieldResult() = 0;
	virtual long double calcYield() = 0;
	virtual long double calcPrice() = 0;
	virtual long double calcYieldandInt() = 0;
	virtual long double calcPriceandInt() = 0;
	virtual ~FinCalc();



protected:
	FinCalc();
};

#endif // !defined(AFX_FINCALC_H__A88BA963_EBE3_11D5_9053_00105A1E6A31__INCLUDED_)
