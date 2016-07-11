#pragma once
#include "Pyfront.h"
const int noValue = 99999;

typedef struct CashFlowStruct
{
	int year;
	int month;
	int day;
	double amount;
	double presentValue;
	int adjustedYear;
	int adjustedMonth;
	int adjustedDay;
	double discountRate;
} CashFlowStruct;

typedef struct CashFlowsStruct
{
	CashFlowStruct *cashFlows;
	int size;
} CashFlowsStruct;

typedef struct RateStruct
{
	int year;
	int month;
	int day;
	double rate;

} RateStruct;
typedef struct RateCurveStruct
{
	RateStruct *rates;
	int size;
} RateCurveStruct;
typedef struct DateStruct
{
	int year;
	int month;
	int day;
} DateStruct;
typedef struct DatesStruct
{
	DateStruct *dates;
	int size;
} DatesStruct;
typedef struct InstrumentStruct
{
	int					instrumentClass;
	int					intDayCount; 
	int					intPayFreq;
	DateStruct			*maturityDate;
	DateStruct			*issueDate;
	DateStruct			*firstPayDate;
	DateStruct			*nextToLastPayDate;
	bool				endOfMonthPay;
	double				interestRate;
	int					holidayAdjust;
} InstrumentStruct;
typedef struct CalculationsStruct
{
	int interestDays;
	DateStruct *valueDate;
	DateStruct *previousPayDate;
	DateStruct *nextPayDate;
	double interest;
	double priceIn;
	double priceOut;
	double yieldIn;
	double yieldOut;
	double duration;
	double convexity;
	double pvbp;
	bool isExCoup;
	int exCoupDays;
	double serviceFee;
	int prepayModel;
	bool calculatePrice;
	int yieldDayCount;
	int yieldFreq;
	int yieldMethod;
	double modifiedDuration;
	double pvbpConvexityAdjusted;
	bool tradeFlat;
	int	payDateAdjust;
} CalculationsStruct;

enum CurveInterpolation
{
	Linear,
	Continuous
};

#ifdef _WIN32
#define CDECLEXPORT __declspec(dllexport)
#else
#define CDECLEXPORT
#endif

extern "C" CDECLEXPORT char**  getclassdescriptions(int& size);
extern "C" CDECLEXPORT char**  getHolidayAdjust(int& size);
extern "C" CDECLEXPORT char**  getdaycounts(int& size);
extern "C" CDECLEXPORT char**  getpayfreqs(int& size);
extern "C" CDECLEXPORT int  getInstrumentDefaults(InstrumentStruct &instrument);
extern "C" CDECLEXPORT int  getInstrumentDefaultsAndData(InstrumentStruct &instrument, CalculationsStruct &calculations);
extern "C" CDECLEXPORT int  getStatusText(int status, char* text, int &textSize);
//extern "C" __declspec(dllexport) int  getDefaultDates(InstrumentStruct &instrument, DateStruct &valueDate);
extern "C" CDECLEXPORT int  getDefaultDatesAndData(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays);
extern "C" CDECLEXPORT char**  getyieldmethods(int& size);
extern "C" CDECLEXPORT int  calculate(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays);
extern "C" CDECLEXPORT int  calculateWithCashFlows(InstrumentStruct &instrument, CalculationsStruct &calculations,CashFlowsStruct &cashFlowsStruct, 
	//int adjustRule, 
	DatesStruct &holidays);
extern "C" CDECLEXPORT int  getCashFlows(CashFlowsStruct &cashFlowsStruct, int adjustRule);
extern "C" CDECLEXPORT int  getNewCashFlows(CashFlowsStruct &cashFlowsStruct, int adjustRule);
extern "C" CDECLEXPORT int  tenor(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &tenor);
extern "C" CDECLEXPORT int  intCalc(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &days, double &dayCountFraction);
extern "C" CDECLEXPORT int  forecast(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int months, int days);
extern "C" CDECLEXPORT int  priceCashFlows(CashFlowsStruct &cashFlowsStruct, 
	int yieldMth,
	int frequency,
	int dayCount,
	DateStruct &valueDate,
	RateCurveStruct &rateCurve,
	int interpolation
	);


int preProc(InstrumentStruct &instrument, CalculationsStruct &calculations,Py_Front &pyfront);
int postProc(InstrumentStruct &instrument, CalculationsStruct &calculations, Py_Front &pyfront);
double RateFromCurve(DateStruct baseDate, RateCurveStruct curve,int interpolationMethod, int dayCount);
extern "C" CDECLEXPORT int  USTBillCalcFromPrice(DateStruct &valueDate, DateStruct &maturityDate, 
	double price,double &discount,double &mmYield,double &beYield);
extern "C" CDECLEXPORT int  USTBillCalcFromPriceWithCashFlows(DateStruct &valueDate, DateStruct &maturityDate,
	double price, double &discount, double &mmYield, double &beYield, CashFlowsStruct &cashFlowsStruct, int adjustRule, DatesStruct &holidays);
extern "C" CDECLEXPORT int  USTBillCalcFromMMYield(DateStruct &valueDate, DateStruct &maturityDate,
	double mmYield, double &price, double &discount, double &beYield,
	double &duration, double &modifiedDuration, double &convexity, double &pvbp, double &pvbpConvexityAdjusted);
extern "C" CDECLEXPORT int  USTBillCalcFromDiscount(DateStruct &valueDate, DateStruct &maturityDate,
	double discount, double &price, double &mmYield, double &beYield);
extern "C" CDECLEXPORT int  USTBillCalcFromBEYield(DateStruct &valueDate, DateStruct &maturityDate,
	double beYield, double &price, double &mmYield, double &discount);
