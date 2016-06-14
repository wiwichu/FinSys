#include "FinSys_Mobile_Calc.h"
#include "../../Calc/Api.h"

#define PLATFORM_ANDROID 0
#define PLATFORM_IOS 1

char * FinSys_Mobile_Calc::getTemplateInfo()
{
#if PLATFORM == PLATFORM_IOS
	static char info[] = "Platform for iOS";
#elif PLATFORM == PLATFORM_ANDROID
	static char info[] = "Platform for Android";
#else
	static char info[] = "Undefined platform";
#endif

	return info;
}
char**  FinSys_Mobile_Calc::getclassdescriptions_internal(int& size)
{
	return  getclassdescriptions(size);
}
char**  FinSys_Mobile_Calc::getdaycounts_internal(int& size)
{
	return  getdaycounts(size);
}
char**  FinSys_Mobile_Calc::getHolidayAdjust_internal(int& size)
{
	return  getHolidayAdjust_internal(size);
}
char**  FinSys_Mobile_Calc::getpayfreqs_internal(int& size)
{
	return  getpayfreqs(size);
}
int  FinSys_Mobile_Calc::getInstrumentDefaults_internal(InstrumentStruct &instrument)
{
	return  getInstrumentDefaults(instrument);
}
int  FinSys_Mobile_Calc::getInstrumentDefaultsAndData_internal(InstrumentStruct &instrument, CalculationsStruct &calculations)
{
	return  getInstrumentDefaultsAndData( instrument, calculations);
}
int  FinSys_Mobile_Calc::getStatusText_internal(int status, char* text, int &textSize)
{
	return  getStatusText(status, text, textSize);
}
int  FinSys_Mobile_Calc::getDefaultDatesAndData_internal(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays)
{
	return  getDefaultDatesAndData(instrument, calculations, holidays);
}
char**  FinSys_Mobile_Calc::getyieldmethods_internal(int& size)
{
	return  getyieldmethods(size);
}
int  FinSys_Mobile_Calc::calculate_internal(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays)
{
	return  calculate(instrument, calculations, holidays);
}
int  FinSys_Mobile_Calc::calculateWithCashFlows_internal(InstrumentStruct &instrument, CalculationsStruct &calculations, CashFlowsStruct &cashFlowsStruct, DatesStruct &holidays)
{
	return  calculateWithCashFlows(instrument, calculations, cashFlowsStruct, holidays);
}
int  FinSys_Mobile_Calc::getCashFlows_internal(CashFlowsStruct &cashFlowsStruct, int adjustRule)
{
	return  getCashFlows(cashFlowsStruct, adjustRule);
}
int  FinSys_Mobile_Calc::getNewCashFlows_internal(CashFlowsStruct &cashFlowsStruct, int adjustRule)
{
	return  getNewCashFlows(cashFlowsStruct, adjustRule);
}
int  FinSys_Mobile_Calc::tenor_internal(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &tenorParm)
{
	return  tenor(startDate, endDate, dayCountRule, tenorParm);
}
int  FinSys_Mobile_Calc::intCalc_internal(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &days, double &dayCountFraction)
{
	return  intCalc(startDate, endDate, dayCountRule, days, dayCountFraction);
}
int  FinSys_Mobile_Calc::forecast_internal(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int months, int days)
{
	return  forecast(startDate, endDate, dayCountRule, months, days);
}
int  FinSys_Mobile_Calc::priceCashFlows_internal(CashFlowsStruct &cashFlowsStruct, int yieldMth, int frequency, int dayCount, DateStruct &valueDate, RateCurveStruct &rateCurve, int interpolation)
{
	return  priceCashFlows(cashFlowsStruct,yieldMth, frequency, dayCount, valueDate, rateCurve, interpolation);
}

FinSys_Mobile_Calc::FinSys_Mobile_Calc()
{
}

FinSys_Mobile_Calc::~FinSys_Mobile_Calc()
{
}
