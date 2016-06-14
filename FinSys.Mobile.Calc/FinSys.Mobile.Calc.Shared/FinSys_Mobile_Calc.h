#pragma once

class InstrumentStruct;
class CalculationsStruct;
class DatesStruct;
class DateStruct;
class CashFlowsStruct;
class RateCurveStruct;

class FinSys_Mobile_Calc {
public:
    static char * getTemplateInfo();
	static char**  getclassdescriptions_internal(int& size);
	static char**  getdaycounts_internal(int& size);
	static  char**  getHolidayAdjust_internal(int& size);
	static  char**  getpayfreqs_internal(int& size);
	static  int  getInstrumentDefaults_internal(InstrumentStruct &instrument);
	static  int  getInstrumentDefaultsAndData_internal(InstrumentStruct &instrument, CalculationsStruct &calculations);
	static  int  getStatusText_internal(int status, char* text, int &textSize);
	static  int  getDefaultDatesAndData_internal(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays);
	static  char**  getyieldmethods_internal(int& size);
	static  int  calculate_internal(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays);
	static  int  calculateWithCashFlows_internal(InstrumentStruct &instrument, CalculationsStruct &calculations, CashFlowsStruct &cashFlowsStruct,DatesStruct &holidays);
	static  int  getCashFlows_internal(CashFlowsStruct &cashFlowsStruct, int adjustRule);
	static  int  getNewCashFlows_internal(CashFlowsStruct &cashFlowsStruct, int adjustRule);
	static  int  tenor_internal(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &tenor);
	static  int  intCalc_internal(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &days, double &dayCountFraction);
	static  int  forecast_internal(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int months, int days);
	static  int  priceCashFlows_internal(CashFlowsStruct &cashFlowsStruct,int yieldMth,int frequency,int dayCount,DateStruct &valueDate,RateCurveStruct &rateCurve,int interpolation);
	FinSys_Mobile_Calc();
    ~FinSys_Mobile_Calc();
};
