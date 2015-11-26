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

