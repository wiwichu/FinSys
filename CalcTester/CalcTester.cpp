// CalcTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <PatCalc.h>
#include <ExceptionCalc.h>

using namespace std;

class forecastdata
{
public:
	void setDate(const string &date) {_date = date;};
	void setMonths(int months) {_months = months;};
	void setDays(int days) {_days = days;};
	void setCaltype(FinCalc::_CALENDARBASIS caltype) {_caltype = caltype;};
	string getDate() {return _date;};
	int getMonths() {return _months;};
	int getDays() {return _days;};
	FinCalc::_CALENDARBASIS getCaltype() {return _caltype;};
private:
	string _date;
	int _months;
	int _days;
	FinCalc::_CALENDARBASIS _caltype;
};

class tenordata
{
public:
	void setStartdate(const string &date) {_startdate = date;};
	void setEnddate(const string &date) {_enddate = date;};
	void setCaltype(FinCalc::_CALENDARBASIS caltype) {_caltype = caltype;};
	string getStartdate() {return _startdate;};
	string getEnddate() {return _enddate;};
	FinCalc::_CALENDARBASIS getCaltype() {return _caltype;};
private:
	string _startdate;
	string _enddate;
	FinCalc::_CALENDARBASIS _caltype;
};


int main(int argc, char* argv[])
{

				FinCalc::_WEEKDAY _dayofweek;
				FinCalc *_pCalc;
				char _itoapiece[5];
				string reportFile("./CalcTest");
				reportFile.append(".");
				reportFile.append("txt");
				ofstream *CalcTestFile = new ofstream(reportFile.c_str(), ios_base::out);
				if (!CalcTestFile){
					printf("Error opening output.");
					return 1;
				}

				string reportLine("Output of the Calculator Test");
				reportLine.append("\t");

				*CalcTestFile << reportLine.c_str();
				*CalcTestFile << endl ;
				*CalcTestFile << endl ;


				try 
				{
	
					_pCalc = new PatCalc();
/////////////////////////////////////////////////////////////////////////////////////////////////
					reportLine.assign("Test the findday method:");
					reportLine.append("\t");

					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					vector<string> _testdates;
					vector<string>::iterator _it_vector_string;
					string _testdate("20011222");
					_testdates.push_back(_testdate);
					_testdate.assign("20011223");
					_testdates.push_back(_testdate);
					_testdate.assign("20011224");
					_testdates.push_back(_testdate);
					_testdate.assign("20011225");
					_testdates.push_back(_testdate);
					_testdate.assign("20011226");
					_testdates.push_back(_testdate);
					_testdate.assign("20011227");
					_testdates.push_back(_testdate);
					_testdate.assign("20011228");
					_testdates.push_back(_testdate);
					_testdate.assign("20011229");
					_testdates.push_back(_testdate);
					_testdate.assign("20000229");
					_testdates.push_back(_testdate);
					_testdate.assign("20010229");
					_testdates.push_back(_testdate);
					_testdate.assign("20010630");
					_testdates.push_back(_testdate);
					_testdate.assign("20010631");
					_testdates.push_back(_testdate);
					_testdate.assign("20060123");
					_testdates.push_back(_testdate);

					for (_it_vector_string=_testdates.begin();
						_it_vector_string<_testdates.end();
						_it_vector_string++)
					{
						reportLine.assign(*_it_vector_string);
						reportLine.append(" is a ");
						FinCalc::_WEEKDAY _dayofweek = _pCalc->findday(*_it_vector_string);
						switch (_dayofweek)
						{
						case FinCalc::_MONDAY:
							reportLine.append("Monday");
							break;
						case FinCalc::_TUESDAY:
							reportLine.append("Tuesday");
							break;
						case FinCalc::_WEDNESDAY:
							reportLine.append("Wednesday");
							break;
						case FinCalc::_THURSDAY:
							reportLine.append("Thursday");
							break;
						case FinCalc::_FRIDAY:
							reportLine.append("Friday");
							break;
						case FinCalc::_SATURDAY:
							reportLine.append("Saturday");
							break;
						case FinCalc::_SUNDAY:
							reportLine.append("Sunday");
							break;
						default:
							reportLine.append("Bad day");
							break;
						}
						*CalcTestFile << reportLine.c_str();
						*CalcTestFile << endl ;
					}
						
					*CalcTestFile << endl ;

/////////////////////////////////////////////////////////////////////////////////////////////////
					reportLine.assign("Now test the forecast method:");
					reportLine.append("\t");
	
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					string _resultdate;

					vector<forecastdata> _vfd;
					vector<forecastdata>::iterator _it_vfd;
					forecastdata _fd;

					_fd.setDate("20010101");_fd.setMonths(1);_fd.setDays(0);
					_fd.setCaltype(FinCalc::DATEACTCAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010101");_fd.setMonths(1);_fd.setDays(0);
					_fd.setCaltype(FinCalc::DATE30CAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010101");_fd.setMonths(1);_fd.setDays(0);
					_fd.setCaltype(FinCalc::DATE30ECAL);
					_vfd.push_back(_fd);

					_fd.setDate("20010101");_fd.setMonths(-1);_fd.setDays(0);
					_fd.setCaltype(FinCalc::DATEACTCAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010101");_fd.setMonths(-1);_fd.setDays(0);
					_fd.setCaltype(FinCalc::DATE30CAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010101");_fd.setMonths(-1);_fd.setDays(0);
					_fd.setCaltype(FinCalc::DATE30ECAL);
					_vfd.push_back(_fd);

					_fd.setDate("20010101");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATEACTCAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010101");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATE30CAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010101");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATE30ECAL);
					_vfd.push_back(_fd);

					_fd.setDate("20010130");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATEACTCAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010130");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATE30CAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010130");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATE30ECAL);
					_vfd.push_back(_fd);

					_fd.setDate("20000130");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATEACTCAL);
					_vfd.push_back(_fd);
					_fd.setDate("20000130");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATE30CAL);
					_vfd.push_back(_fd);
					_fd.setDate("20000130");_fd.setMonths(0);_fd.setDays(30);
					_fd.setCaltype(FinCalc::DATE30ECAL);
					_vfd.push_back(_fd);

					_fd.setDate("20010130");_fd.setMonths(0);_fd.setDays(1);
					_fd.setCaltype(FinCalc::DATEACTCAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010130");_fd.setMonths(0);_fd.setDays(1);
					_fd.setCaltype(FinCalc::DATE30CAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010130");_fd.setMonths(0);_fd.setDays(1);
					_fd.setCaltype(FinCalc::DATE30ECAL);
					_vfd.push_back(_fd);

					_fd.setDate("20010201");_fd.setMonths(0);_fd.setDays(-61);
					_fd.setCaltype(FinCalc::DATEACTCAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010201");_fd.setMonths(0);_fd.setDays(-61);
					_fd.setCaltype(FinCalc::DATE30CAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010201");_fd.setMonths(0);_fd.setDays(-61);
					_fd.setCaltype(FinCalc::DATE30ECAL);
					_vfd.push_back(_fd);

					_fd.setDate("20010115");_fd.setMonths(0);_fd.setDays(1);
					_fd.setCaltype(FinCalc::DATEACTCAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010115");_fd.setMonths(0);_fd.setDays(1);
					_fd.setCaltype(FinCalc::DATE30CAL);
					_vfd.push_back(_fd);
					_fd.setDate("20010115");_fd.setMonths(0);_fd.setDays(1);
					_fd.setCaltype(FinCalc::DATE30ECAL);
					_vfd.push_back(_fd);

					for (_it_vfd=_vfd.begin();
						_it_vfd<_vfd.end();
						_it_vfd++)
					{
						_resultdate.assign(_pCalc->forecast(	_it_vfd->getDate(),
														_it_vfd->getMonths(),
														_it_vfd->getDays(),
														_it_vfd->getCaltype())
											);

						reportLine.assign(_it_vfd->getDate());
						reportLine.append(" plus ");
						itoa(_it_vfd->getMonths(),_itoapiece,10);
						reportLine.append(_itoapiece);
						reportLine.append(" months ");
						reportLine.append(" plus ");
						itoa(_it_vfd->getDays(),_itoapiece,10);
						reportLine.append(_itoapiece);
						reportLine.append(" days using ");
						reportLine.append(FinCalc::getCALENDARBASIS_Text(_it_vfd->getCaltype()));
						reportLine.append(" is ");
						reportLine.append(_resultdate);

						*CalcTestFile << reportLine.c_str();
						*CalcTestFile << endl ;
					}
					*CalcTestFile << endl ;

/////////////////////////////////////////////////////////////////////////////////////////////////
					reportLine.assign("Now test the tenor method:");
					reportLine.append("\t");
	
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					long _tenorresult;

					vector<tenordata> _vtd;
					vector<tenordata>::iterator _it_vtd;
					tenordata _td;

					_td.setStartdate("20010101");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010101");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010101");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010131");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010131");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010131");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010130");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010130");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010130");_td.setEnddate("20010201");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010130");_td.setEnddate("20010131");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010130");_td.setEnddate("20010131");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010130");_td.setEnddate("20010131");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010129");_td.setEnddate("20010130");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010129");_td.setEnddate("20010130");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010129");_td.setEnddate("20010130");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010129");_td.setEnddate("20010131");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010129");_td.setEnddate("20010131");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010129");_td.setEnddate("20010131");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010530");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010530");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010530");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010531");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010531");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010531");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010601");
					_td.setCaltype(FinCalc::DATEACTCAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010601");
					_td.setCaltype(FinCalc::DATE30CAL);
					_vtd.push_back(_td);
					_td.setStartdate("20010501");_td.setEnddate("20010601");
					_td.setCaltype(FinCalc::DATE30ECAL);
					_vtd.push_back(_td);

					for (_it_vtd=_vtd.begin();
						_it_vtd<_vtd.end();
						_it_vtd++)
					{
						_tenorresult = _pCalc->tenor(	_it_vtd->getStartdate(),
														_it_vtd->getEnddate(),
														_it_vtd->getCaltype());

						reportLine.assign(_it_vtd->getStartdate());
						reportLine.append(" to ");
						reportLine.append(_it_vtd->getEnddate());
						reportLine.append(" is ");
						itoa(_tenorresult,_itoapiece,10);
						reportLine.append(_itoapiece);
						reportLine.append(" days using ");
						reportLine.append(FinCalc::getCALENDARBASIS_Text(_it_vtd->getCaltype()));

						*CalcTestFile << reportLine.c_str();
						*CalcTestFile << endl ;
					}
					*CalcTestFile << endl ;
/////////////////////////////////////////////////////////////////////////////////////////////////
					reportLine.assign("Test setting different instrument classes:");
					reportLine.append("\t");
	
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					vector<FinCalc::_INSTRUMENTCLASS> _vic;
					vector<FinCalc::_INSTRUMENTCLASS>::iterator _it_vic;
					for (int ic = FinCalc::GERMANBUND;
						ic <= FinCalc::MBS; ic++)
						_vic.push_back((FinCalc::_INSTRUMENTCLASS) ic);

					for (_it_vic=_vic.begin();
						_it_vic<_vic.end();
						++_it_vic)
					{
						reportLine.assign(" Setting class ");
						FinCalc::_INSTRUMENTCLASS icHold =*_it_vic;
						reportLine.append(FinCalc::getINSTRUMENTCLASS_Text(icHold));
						_pCalc->setClass(*_it_vic);

						*CalcTestFile << reportLine.c_str();
						*CalcTestFile << endl ;

						reportLine.assign("\t Day Count is ");
						reportLine.append(FinCalc::getDAYCOUNT_Text(_pCalc->getDaycount()));
						*CalcTestFile << reportLine.c_str();
						*CalcTestFile << endl ;

						reportLine.assign("\t Pay Frequency is ");
						itoa(_pCalc->getPayfreqlength(),_itoapiece,10);
						reportLine.append(_itoapiece);
						reportLine.append(" ");
						reportLine.append(FinCalc::getPERIOD_Text(_pCalc->getPayfreqperiod()));
						*CalcTestFile << reportLine.c_str();
						*CalcTestFile << endl ;

						reportLine.assign("\t Yield Day Count is ");
						reportLine.append(FinCalc::getDAYCOUNT_Text(_pCalc->getDaycountYield()));
						*CalcTestFile << reportLine.c_str();
						*CalcTestFile << endl ;

						reportLine.assign("\t Yield Frequency is ");
						itoa(_pCalc->getPayfreqlength(),_itoapiece,10);
						reportLine.append(_itoapiece);
						reportLine.append(" ");
						reportLine.append(FinCalc::getPERIOD_Text(_pCalc->getPayfreqperiodYield()));
						*CalcTestFile << reportLine.c_str();
						*CalcTestFile << endl ;
					}
						*CalcTestFile << endl ;
/////////////////////////////////////////////////////////////////////////////////////////////////
					reportLine.assign("Test different price/yield examples:");
					reportLine.append("\t");
	
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					string _date;
					string _issuedate;
					string _valuedate;
					string _maturitydate;
					string _firstdate;
					string _penultpaydate;
					char work_str[33];
					int price_places = 15;
					long double _interest_rate;
					double work_double;

					reportLine.assign(" Setting class ");
					reportLine.append(FinCalc::getINSTRUMENTCLASS_Text(FinCalc::USDSC));
					_pCalc->setClass(FinCalc::USDSC);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
/*
					_date.assign("19860220");
					_pCalc->setValueDate(_date);
					reportLine.assign(" Value Date is ");
					reportLine.append(_pCalc->getValueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					_date.assign("19860313");
					_pCalc->setMaturityDate(_date);
					reportLine.assign(" Maturity Date is ");
					reportLine.append(_pCalc->getMaturityDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
*/
					_valuedate.assign("19860220");
					_maturitydate.assign("19860313");
					_pCalc->setDates(_valuedate,_maturitydate);

					reportLine.assign(" Value Date is ");
					reportLine.append(_pCalc->getValueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Maturity Date is ");
					reportLine.append(_pCalc->getMaturityDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					_pCalc->setPrice(0.99592);
					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->getPrice();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Discount Rate is ");
				    work_double = (double)_pCalc->calcYieldandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Set Discount Rate to ");
					_pCalc->setYield(0.07);
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Price Result is ");
				    work_double = (double)_pCalc->calcPriceandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					_pCalc->setPrice(work_double);
					reportLine.assign(" Discount Rate from this price is ");
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					_pCalc->setYieldMethod(FinCalc::_MM);
					reportLine.assign(" MM Yield is ");
				    work_double = (double)_pCalc->calcYieldandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					_pCalc->setYieldMethod(FinCalc::_BE);
					reportLine.assign(" Bond Equivalent Yield is ");
				    work_double = (double)_pCalc->calcYieldandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Calculate Price from this BE yield ");
					_pCalc->setYield(work_double);
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Price Result is ");
				    work_double = (double)_pCalc->calcPriceandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					_valuedate.assign("19860104");
					_maturitydate.assign("19861217");
					_pCalc->setDates(_valuedate,_maturitydate);

					reportLine.assign(" Value Date is ");
					reportLine.append(_pCalc->getValueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Maturity Date is ");
					reportLine.append(_pCalc->getMaturityDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					_pCalc->setPrice(0.942167);
					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->getPrice();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" BE Yield is ");
				    work_double = (double)_pCalc->calcYieldandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Calculate Price from this BE yield ");
					_pCalc->setYield(work_double);
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Price Result is ");
				    work_double = (double)_pCalc->calcPriceandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

				
					_valuedate.assign("20010606");
					_maturitydate.assign("20011031");
					_pCalc->setDates(_valuedate,_maturitydate);

					reportLine.assign(" Maturity Date is ");
					reportLine.append(_pCalc->getMaturityDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Bought on ");
					reportLine.append(_pCalc->getValueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" at a Discount Rate of ");
					_pCalc->setYield(0.06);
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Price Result is ");
				    work_double = (double)_pCalc->calcPriceandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Sold on ");
					_valuedate.assign("20011225");
					reportLine.append(_pCalc->getValueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" at a Discount Rate of ");
					_pCalc->setYield(0.0585);
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					reportLine.assign(" Price Result is ");
				    work_double = (double)_pCalc->calcPriceandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;


					reportLine.assign(" Setting class ");
					reportLine.append(FinCalc::getINSTRUMENTCLASS_Text(FinCalc::USCD));
					_pCalc->setClass(FinCalc::USCD);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					_issuedate.assign("19860101");
					_valuedate.assign("19860516");
					_maturitydate.assign("19860630");
					_firstdate.assign("19860630");;
					_penultpaydate.assign("19860101");;
					_interest_rate = 0.08;
					_pCalc->setInterestRate(_interest_rate);
					_pCalc->setDates(_valuedate,
						_maturitydate,
						_issuedate,
						_firstdate,
						_penultpaydate);
					_pCalc->setYield(0.0775);

					reportLine.assign(" Value Date is ");
					reportLine.append(_pCalc->getValueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Issue Date is ");
					reportLine.append(_pCalc->getIssueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" First Pay Date is ");
					reportLine.append(_pCalc->getFirstPayDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Next to Last Pay Date is ");
					reportLine.append(_pCalc->getNextToLastPayDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Maturity Date is ");
					reportLine.append(_pCalc->getMaturityDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
 
					reportLine.assign(" Interest Rate is ");
				    work_double = (double)_pCalc->getInterestRate();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Yield is ");
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->calcPriceandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Interest is ");
				    work_double = (double)_pCalc->getInterest();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					_pCalc->setPrice(1.000022);
					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->getPrice();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Yield is ");
				    work_double = (double)_pCalc->calcYieldandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Interest is ");
				    work_double = (double)_pCalc->getInterest();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					_issuedate.assign("19860408");
					_valuedate.assign("19860824");
					_maturitydate.assign("19871008");
					_firstdate.assign("19861008");;
					_penultpaydate.assign("19870408");;
					_interest_rate = 0.08;
					_pCalc->setInterestRate(_interest_rate);
					_pCalc->setDates(_valuedate,
						_maturitydate,
						_issuedate,
						_firstdate,
						_penultpaydate);
					_pCalc->setYield(0.0775);

					reportLine.assign(" Value Date is ");
					reportLine.append(_pCalc->getValueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Issue Date is ");
					reportLine.append(_pCalc->getIssueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" First Pay Date is ");
					reportLine.append(_pCalc->getFirstPayDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Next to Last Pay Date is ");
					reportLine.append(_pCalc->getNextToLastPayDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Maturity Date is ");
					reportLine.append(_pCalc->getMaturityDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
 
					reportLine.assign(" Interest Rate is ");
				    work_double = (double)_pCalc->getInterestRate();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Yield is ");
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->calcPriceandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Interest is ");
				    work_double = (double)_pCalc->getInterest();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					_pCalc->setPrice(1.002385);
					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->getPrice();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Yield is ");
				    work_double = (double)_pCalc->calcYieldandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					_pCalc->setYieldMethod(FinCalc::_CURRENT);
					_pCalc->setPrice(0.96);
					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->getPrice();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Yield is ");
				    work_double = (double)_pCalc->calcYieldandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Interest is ");
				    work_double = (double)_pCalc->getInterest();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					_pCalc->setYield(0.0833);
					reportLine.assign(" Yield is ");
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->calcPriceandInt();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Interest is ");
				    work_double = (double)_pCalc->getInterest();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					_pCalc->setClass(FinCalc::GOVOFJAPAN);
					_issuedate.assign("20020101");
					_valuedate.assign("20020101");
					_maturitydate.assign("20070101");
					_firstdate.assign("20030101");;
					_penultpaydate.assign("20060101");;
					_interest_rate = 0.08;
					_pCalc->setInterestRate(_interest_rate);
					_pCalc->setDates(_valuedate,
						_maturitydate,
						_issuedate,
						_firstdate,
						_penultpaydate);
					_pCalc->setPrice(0.96);
					_pCalc->setYieldMethod(FinCalc::_SIMPJAP);

					reportLine.assign(" Value Date is ");
					reportLine.append(_pCalc->getValueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Issue Date is ");
					reportLine.append(_pCalc->getIssueDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" First Pay Date is ");
					reportLine.append(_pCalc->getFirstPayDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Next to Last Pay Date is ");
					reportLine.append(_pCalc->getNextToLastPayDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Maturity Date is ");
					reportLine.append(_pCalc->getMaturityDate());
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
 
					reportLine.assign(" Interest Rate is ");
				    work_double = (double)_pCalc->getInterestRate();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Price is ");
				    work_double = (double)_pCalc->getPrice();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Yield is ");
				    work_double = (double)_pCalc->calcYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;

					_pCalc->setYield(0.0917);
					reportLine.assign(" Yield is ");
				    work_double = (double)_pCalc->getYield();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;

					reportLine.assign(" Price is ");
					work_double = (double)_pCalc->calcPrice();
				    work_double = (double)_pCalc->getPrice();
				    gcvt(work_double, price_places, work_str);
					reportLine.append(work_str);
					*CalcTestFile << reportLine.c_str();
					*CalcTestFile << endl ;
					*CalcTestFile << endl ;
}
				catch (ExceptionCalc *ec)
				{
					printf(ec->GetError().c_str());
					return 1;
				}
				catch (...)
				{
					printf("Catch All Exception.");
					return 1;
				}

				delete _pCalc;
				return 0;
}

/*
Compute the Price and Accrued Interest for a Certificate of Deposit
This example shows how to compute the price and the accrued interest due on the settlement date, given a certificate of deposit with the following characteristics.

Yield           =  0.0525;
CouponRate      =  0.05;
Settle          =  '02-Jan-02';
Maturity        =  '31-Mar-02';
IssueDate       =  '1-Oct-01';

[Price, AccruedInt] = cdprice(Yield, CouponRate, Settle, ...
Maturity, IssueDate)
Price =

99.9233


AccruedInt =

1.2917


//////////////////////////////////
Accrued Interest on conventional gilts (standard dividend period)
ORB identifiers
Name: Treasury 5% 2025
TIDM: TR25
ISIN: GB0030880693
Coupon dates: 7 March and 7 September
Annual Coupon: 5%
Trade Date: 13 April 2015 (T+1 settlement on 14 April 2015)
Clean Price: 129.21
Accrued = 38 (period between 7 Mar 2015 and 14 Apr 2015) x 5
Interest 184 (period between 7 Mar and 7 Sep 2015) 2
= 0.5163
Dirty price = 129.7263 (clean price + accrued interest)
//////////////////////////////////////////////

Convert the Discount Rate on Treasury Bills
This example shows how to convert the discount rate on Treasury bills into their respective money-market or bond-equivalent yields, given a Treasury bill with the following characteristics.

Discount = 0.0497;
Settle = '01-Oct-02';
Maturity = '31-Mar-03';

[BEYield MMYield] = tbilldisc2yield(Discount, Settle, Maturity)
BEYield =

0.0517 (USE MM YIELD)


MMYield =

0.0510 (MAKE YIELD DAYS ACT/ACT AND YIELD FREQUENCY SEMI-ANNUAL AND USE COMPOUND YTM)



///////////////////////////////////////////////////////


Accrual Method List
Accrual Method
Description
Actual/365 (fixed)
The number of accrued days is equal to the actual number of days between the effective date and the terminating date.  The accrual factor is the number of accrued days divided by 365.
Actual/360
The number of accrued days is equal to the actual number of days between the effective date and the terminating date.  The accrual factor is the number of accrued days divided by 360.
Actual/365 (actual)
The number of accrued days is equal to the actual number of days between the effective date and the terminating date.  Calculation of the accrual factor assumes the year basis to be 365 days for non-leap years and 366 for leap years.  If a short stub period (< 1 year) contains a leap day, the number of days is divided by 366; otherwise, the number of days is divided by 365.
30/360 (ISDA)
(same as U.S. Muni – 30/360)
The number of accrued days is calculated on the basis of a year of 360 days with 12 30-day months, subject to the following rules:
1.       If the first date of the accrual period falls on the 31st of the month, the date will be changed to the 30th.
2.       If the first date of the accrual period falls on the 30th of the month after applying (1) above, and the last date of the accrual period falls on the 31st of the month, the last date will be changed to the 30th.
The accrual factor is calculated as the number of accrued days divided by 360.
30E/360 (30/360 ISMA)
The number of accrued days is calculated on the basis of a year of 360 days with 12 30-day months, subject to the following rules:
1.       If either the first date or last date of the accrual period falls on the 31st of a month, that date will be changed to the 30th.
2.       If the last day of the accrual period falls on the last day of February, the month of February will not be extended to a 30-day month.  Rather, the actual number of days in February will be used.
The accrual factor is calculated as the number of accrued days divided by 360.
30E+/360
The number of accrued days is calculated on the basis of a year of 360 days with 12 30-day months, subject to the following rules:
1.       If the first date of the accrual period falls on the 31st of a month, it will be changed to the 30th of that month.
2.       If the last date of the accrual period falls on the 31st of a month, it will be changed to the 1st of the next month.
The accrual factor is calculated as the number of accrued days divided by 360.
Actual/Actual (ISMA-99)
This accrual method is primarily related to bonds.  In the context of accrual factors, the time in years is calculated as follows: if the period is less than one year the accrual factor is equal to the actual number of days between the effective date (d_e) and the terminating date (d_t) divided by the number of days in the period from (d_t – 1 year) to d_t (either 365 or 366).  If the period is greater than one year, the accrual factor is equal to the number of whole years plus the accrual of a stub period calculated as above.  In the context of bonds, there are two ISMA-99 methods: Normal and Ultimo.  The methods differ only in the assumption made regarding coupon dates.  The ISMA-99 Normal method assumes that regular coupons fall on the same day of the month (non end-of-month), and the ISMA-99 Ultimo method assumes that regular coupons fall on the last day of the month (end-of-month).  The ISMA-99 methods make a distinction between regular and irregular interest periods.  Regular interest periods are always an exact multiple of a number of months long, whereas irregular interest periods require that notional interest periods be generated.  The accrual factor for a period is the number of accrued days falling in that period divided by the actual number of days in the period.  The overall accrual factor is then the sum of the individual interest period accrual factors, multiplied by the year fraction of a regular interest period.  For more details, see Reference [1].
Actual/Actual (ISDA)
The number of accrued days is equal to the actual number of days between the effective date and the terminating date.  The accrual factor is the sum of the accrued days falling in a non-leap year divided by 365 and the accrued days falling in a leap year divided by 366.
30/360 (Old)
This method is old and should not be used.  This method used to be labeled 30/360 (ISDA).
30E/360 (Old)
This method is old and should not be used.  This method used to be labeled 30E/360 (ISDA).
30/360 (SIA)
The number of accrued days is calculated on the basis of a year of 360 days with 12 30-day months, subject to the following rules:
1.       If the last date of the accrual period is the last day of February and the first date of the period is the last day of February, then the last date of the period will be changed to the 30th.
2.       If the first date of the accrual period falls on the 31st of a month or is the last day of February, that date will be changed to the 30th of the month.
3.       If the first date of the accrual period falls on the 30th of a month after applying (2) above, and the last date of the period falls on the 31st of a month, the last date will be changed to the 30th of the month.
The accrual factor is calculated as the number of accrued days divided by 360.  Note that these rules assume that the security follows the end-of-month rule. (see the Date Generation Functions FINCAD Math Reference document.) If the security does not follow the end-of-month rule, then 30/360 (ISDA) should be used.
30/360 (BMA)
The number of accrued days is calculated on the basis of a year of 360 days with 12 30-day months, subject to the following rules:
1.       If the first date of the accrual period falls on the 31st of a month or is the last day of February, the date will be changed to the 30th.
2.       If the first date of the accrual period falls on the 30th of the month after applying 1) above, and the last date of the accrual period falls on the 31st of the month, the last date will be changed to the 30th.
The accrual factor is calculated as the number of accrued days divided by 360.  Note that prior to 1997, the BMA was known as the PSA, and this method was referred to as 30/360 (PSA).
30/360 (German)
The number of accrued days is calculated on the basis of a year of 360 days with 12 30-day months, subject to the following rules:
1.       If either the first date or last date of the accrual period falls on the 31st of a month, that date will be changed to the 30th.
2.       If either the first date or last date of the accrual period is the last day of February, that date will be changed to the 30th.
The accrual factor is calculated as the number of accrued days divided by 360.
Bus/252
The number of accrued days is calculated as the number of market days in the accrual period.  The accrual factor is calculated as the number of accrued (market) days divided by 252.
Actual/365L
The number of accrued days is calculated as the actual number of days between the effective date and the terminating date.  This number is divided by 366 if the terminating date falls in a leap year and 365 otherwise.
NL365
The number of days is calculated as the actual number of days between the effective date and the terminating date without including any occurrences of the leap day, February 29th.  This number is divided by 365.
The main differences between the various 30/360 methods is the treatment of dates landing on the 31st of a month, or the end of February.  The ISMA, ISDA, and 30E+/360 methods make adjustments for dates landing on the 31st of a month, but not for dates landing on the last day of February.  The SIA, BMA, and German methods make adjustments for dates landing on the 31st of a month, as well as for dates landing on the last day of February.

///////////////////////////////////////

Below are few of the examples chosen to highlight the differences between the stated conventions
Example 1

Let us assume D1.M1.Y1 = 28/12/2007 and D2.M2.Y2 = 28/2/2008 (Remember Y2 is Leap).
Table 3: DCF calculations (1/4)
Convention	Calculation	DCF
Act/Act	4/365+58/366	0.16942884946478
Act/365F	62/365	0.16986301369863
Act/360	62/360	0.172222222222222
Act/365A	62/365	0.16986301369863
Act/365L	62/366	0.169398907103825
NL/365	62/365	0.16986301369863
30/360 ISDA	60/360	0.166666666666667
30E/360	60/360	0.166666666666667
30E+/360	60/360	0.166666666666667
30/360 German	60/360	0.166666666666667
30/360 US	60/360	0.166666666666667
Example 2

Now let us suppose D1.M1.Y1 = 28/12/2007 and D2.M2.Y2 = 29/2/2008 (Remember Y2 is Leap).
Table 4: DCF calculations (2/4)
Convention	Calculation	DCF
Act/Act	4/365+59/366	0.172161089901939
Act/365F	63/365	0.172602739726027
Act/360	63/360	0.175
Act/365A	63/366	0.172131147540984
Act/365L	63/366	0.172131147540984
NL/365	62/365	0.16986301369863
30/360 ISDA	61/360	0.169444444444444
30E/360	61/360	0.169444444444444
30E+/360	61/360	0.169444444444444
30/360 German	62/360	0.172222222222222
30/360 US	61/360	0.169444444444444
Example 3

Now let us suppose D1.M1.Y1 = 31/10/2007 and D2.M2.Y2 = 30/11/2008 (Remember Y2 is Leap).
Table 5: DCF calculations (3/4)
Convention	Calculation	DCF
Act/Act	62/365+334/366	1.08243131970956
Act/365F	396/365	1.08493150684932
Act/360	396/360	1.1000000000000
Act/365A	396/366	1.08196721311475
Act/365L	396/366	1.08196721311475
NL/365	395/365	1.08219178082192
30/360 ISDA	390/360	1.08333333333333
30E/360	390/360	1.08333333333333
30E+/360	390/360	1.08333333333333
30/360 German	390/360	1.08333333333333
30/360 US	390/360	1.08333333333333
Example 4

Let's take one last example. D1.M1.Y1 = 2/1/2008 and D2.M2.Y2 = 5/31/2009
Table 6: DCF calculations (4/4)
Convention	Calculation	DCF
Act/Act	335/366+150/365	1.32625945055768
Act/365F	485/365	1.32876712328767
Act/360	485/360	1.34722222222222
Act/365A	485/366	1.32513661202186
Act/365L	485/365	1.32876712328767
NL/365	484/365	1.32602739726027
30/360 ISDA	480/360	1.33333333333333
30E/360	479/360	1.33055555555556
30E+/360	480/360	1.33333333333333
30/360 German	479/360	1.33055555555556
30/360 US	480/360	1.33333333333333


/////

LINK:

http://knowpapa.com/dcc/
http://www.iso15022.org/uhb/uhb/mt569-48-field-22f.htm
http://www.deltaquants.com/day-count-conventions
http://www.isda.org/c_and_a/pdf/ACT-ACT-ISDA-1999.pdf
http://docs.fincad.com/support/developerfunc/mathref/Daycount.htm
http://educ.jmu.edu/~drakepp/FIN250/readings/duration.pdf
http://www.mathworks.com/help/finance/computing-treasury-bill-price-and-yield.html#bt2fpqg-5
*/

