// PatCalc.h: interface for the PatCalc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATCALC_H__B4284A12_ECAC_11D5_9055_E0CC6C000000__INCLUDED_)
#define AFX_PATCALC_H__B4284A12_ECAC_11D5_9055_E0CC6C000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FinCalc.h"
#include "Pyfront.h"
#include "Datedec.h"

class CALC_API PatCalc : public FinCalc  
{
public:
	PatCalc();
	FinCalc::_WEEKDAY findday(const string & date);
	string	forecast (const string &date,int months,long days, FinCalc::_CALENDARBASIS );
	long	tenor (const string &startdate,const string &enddate, FinCalc::_CALENDARBASIS );
	void	setClass(_INSTRUMENTCLASS instrumentclass);
	_DAYCOUNT	getDaycount();
	_DAYCOUNT	getDaycountYield();
	int	getPayfreqlength();
	_PERIOD	getPayfreqperiod();
	int	getPayfreqlengthYield();
	_PERIOD	getPayfreqperiodYield();

	void	setDaycount(_DAYCOUNT daycount);
	void	setDaycountYield(_DAYCOUNT daycount);
	void	setPayfreqlength(_FREQUENCY frequency);
//	void	setPayfreqperiod(_PERIOD pfperiod);
	void	setPayfreqlengthYield(_FREQUENCY frequency);
//	void	setPayfreqperiodYield(_PERIOD pfperiod);
	_YIELDMETH	getYieldMethod();
	void setYieldMethod(_YIELDMETH yieldmeth);
	void setInterestRate(long double interestrate);
	void setValueDate(string &date);
	string getValueDate();
	void setMaturityDate(string &date);
	string getMaturityDate();
	void setIssueDate(string &date);
	string getIssueDate();
	void setFirstPayDate(string &date);
	string getFirstPayDate();
	void setNextToLastPayDate(string &date);
	string getNextToLastPayDate();
	void setDates(string valueDate,
					string maturityDate,
					string issueDate="",
					string firstpayDate="",
					string nextToLastPayDate="");
	void setPrice(long double price);
	long double getPrice();
	long double getPriceResult();
	void setYield(long double yield);
	long double getYield();
	long double getYieldResult();
	long double calcYield();
	long double calcPrice();
	long double calcYieldandInt();
	long double calcPriceandInt();
	long double getInterestRate();
	long double getInterest();
	virtual ~PatCalc();

protected:

	void BEAdjust();

private:
	Py_Front py;
	_INSTRUMENTCLASS _instrumentclass;
	_YIELDMETH _yieldmeth;
	_DAYCOUNT	convertDaycount(int rawDaycount);
	int	convertDaycount(FinCalc::_DAYCOUNT rawDaycount);
	_PERIOD	convertPayfreqperiod(int rawPayfreq);
	int	convertFrequency(_FREQUENCY frequency);
};

#endif // !defined(AFX_PATCALC_H__B4284A12_ECAC_11D5_9055_E0CC6C000000__INCLUDED_)
