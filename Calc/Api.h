#pragma once
#include "Pyfront.h"

const int noValue = 99999;//Passed in a numeric field to indicate no value has been passed.

//MAPS - mapping integer arguments to descriptions
//
//INSTRUMENTCLASSMAP
//0=German Bund
//1=Japan Gov
//2=Eurobond
//3=UK Gilt
//4=UK CD
//5=UK Discount
//6=US CD
//7=US Discount
//8=US TBond
//9=Commercial Paper
//10=Finanzierungsschatz
//11=U-Schatz
//
//DAYCOUNTMAP
//0=30e/360
//1=30/360
//2=act/360
//3=act/365
//4=act/365cd
//5=act/act
//6=act/365L
//7=act/actISDA
//8=30/360german
//9=NL/365
//10=30eplus/360
//11=30/360US
//12=act/365a
//13=act/366
//14=act/360cd
//
//FREQUENCYMAP
//1-=monthly
//3=quarterly
//6=semiannually
//12=annually
//
//DATEADJUSTMAP
//0=Marching
//1=Next
//2=NextInMonth
//3=Previous
//4=Previous-Next
//5=Same(no adjustment)
//
//YIELDMETHODMAP
//0=ISMA
//1=MM Discount
//2=MM Yield
//3=Simple YtM
//4=Compound YtM
//5=Simple (Japan)
//6=Current Yield
//7=Greenwell Montagu
//8=Muni
//9=Corporate
//10=US TBond
//11=Moosmueller
//12=Braess/Fangmeyer
//13=True Yield
//
//INTERPOLATIONMAP
//0=Linear

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
	int					instrumentClass;//see INSTRUMENTCLASSMAP
	int					intDayCount; //see DAYCOUNTMAP
	int					intPayFreq;//see FREQUENCYMAP
	DateStruct			*maturityDate;
	DateStruct			*issueDate;
	DateStruct			*firstPayDate;
	DateStruct			*nextToLastPayDate;
	bool				endOfMonthPay;//If true, indicates payment is on the last day of the month.
	double				interestRate;
	int					holidayAdjust;//see DATEADJUSTMAP
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
	bool isExCoup;//If true, negative accrued interest will be calculated back from next pay date.
	int exCoupDays;
	double serviceFee;
	int prepayModel;
	bool calculatePrice;
	int yieldDayCount;//see DAYCOUNTMAP
	int yieldFreq;//see FREQUENCYMAP
	int yieldMethod;//see YIELDMETHODMAP
	double modifiedDuration;
	double pvbpConvexityAdjusted;
	bool tradeFlat;//If true, accrued interest will not be included.
	int	payDateAdjust;//see DATEADJUSTMAP
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

//Returns a list of instrument class descriptions.
extern "C" CDECLEXPORT char**  getclassdescriptions(int& size);

//Returns a list of non business date adjustment rules.
extern "C" CDECLEXPORT char**  getHolidayAdjust(int& size);

//Returns a list of rules for determining number of days between two dates.
extern "C" CDECLEXPORT char**  getdaycounts(int& size);

//Returns a list of valid payment frequencies
extern "C" CDECLEXPORT char**  getpayfreqs(int& size);

//Returns a list of valid yield methods.
extern "C" CDECLEXPORT char**  getyieldmethods(int& size);

//
//For the following functions, if the return value is not 0, calling getStatusText
//will return a string of the warning or error.
//

//Populates the InstrumentStruct with defaults for the chosen instrumentclass.
extern "C" CDECLEXPORT int  getInstrumentDefaults(InstrumentStruct &instrument);

//Populates the InstrumentStruct and CalculationsStruct with defaults for the chosen instrumentclass.
extern "C" CDECLEXPORT int  getInstrumentDefaultsAndData(InstrumentStruct &instrument, CalculationsStruct &calculations);

//Returns the text for a status from a previous function call.
extern "C" CDECLEXPORT int  getStatusText(int status, char* text, int &textSize);

//Populates InstrumentStruct and CalculationsStruct with defaults and dates adjusted for the holiday schedule.
extern "C" CDECLEXPORT int  getDefaultDatesAndData(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays);

//Performs calculations on InstrumentStruct as indicated by CalculationsStruct and adjusted for passed holidays.
extern "C" CDECLEXPORT int  calculate(InstrumentStruct &instrument, CalculationsStruct &calculations, DatesStruct &holidays);

//Performs calculations on InstrumentStruct as indicated by CalculationsStruct and adjusted for passed holidays, also returning cashflows.
extern "C" CDECLEXPORT int  calculateWithCashFlows(InstrumentStruct &instrument, CalculationsStruct &calculations,CashFlowsStruct &cashFlowsStruct, 
	DatesStruct &holidays);

//Returns cashflows adjusted by the passed in non business adjust rule.
extern "C" CDECLEXPORT int  getCashFlows(CashFlowsStruct &cashFlowsStruct, 
	int adjustRule//see DATEADJUSTMAP
);

//Returns the number of days between 2 dates using the passed in daycount rule.
extern "C" CDECLEXPORT int  tenor(DateStruct &startDate, DateStruct &endDate, 
	int dayCountRule,//see  DAYCOUNTMAP
	int &tenor);

//Returns the number of days of interest between 2 dates and also the factor to multiply nominal by to arrive at actual accrued interest, using the passed daycount rule.
extern "C" CDECLEXPORT int  intCalc(DateStruct &startDate, DateStruct &endDate, 
	int dayCountRule, //see DAYCOUNTMAP
	int &days, double &dayCountFraction);

//Returns and end date when passed a start date, daycount rule, and number of months and days to add or substract(-).
extern "C" CDECLEXPORT int  forecast(DateStruct &startDate, DateStruct &endDate, 
	int dayCountRule, //see DAYCOUNTMAP
	int months, int days);

//Calculates present value of cashflows using the passed yield method, frequency and daycount rule for discounting, taking the rate for the specific date from the rate curve and interpolating as indicated.
extern "C" CDECLEXPORT int  priceCashFlows(CashFlowsStruct &cashFlowsStruct, 
	int yieldMth,//see YIELDMETHODMAP
	int frequency,//see FREQUENCYMAP
	int dayCount,//see DAYCOUNTMAP
	DateStruct &valueDate,
	RateCurveStruct &rateCurve,
	int interpolation
	);

//Calculates TBill values from price using passed value date and maturity date.
extern "C" CDECLEXPORT int  USTBillCalcFromPrice(DateStruct &valueDate, DateStruct &maturityDate, 
	double price,double &discount,double &mmYield,double &beYield);

//Calculates TBill values from price using passed value date and maturity date. Also returns cashflows adjusted by holiday rule.
extern "C" CDECLEXPORT int  USTBillCalcFromPriceWithCashFlows(DateStruct &valueDate, DateStruct &maturityDate,
	double price, double &discount, double &mmYield, double &beYield, CashFlowsStruct &cashFlowsStruct, int adjustRule, DatesStruct &holidays);

//Calculates TBill values from Money Market Yield using passed value date and maturity date.
extern "C" CDECLEXPORT int  USTBillCalcFromMMYield(DateStruct &valueDate, DateStruct &maturityDate,
	double mmYield, double &price, double &discount, double &beYield,
	double &duration, double &modifiedDuration, double &convexity, double &pvbp, double &pvbpConvexityAdjusted);

//Calculates TBill values from Discount using passed value date and maturity date.
extern "C" CDECLEXPORT int  USTBillCalcFromDiscount(DateStruct &valueDate, DateStruct &maturityDate,
	double discount, double &price, double &mmYield, double &beYield);

//Calculates TBill values from Bond Equivalent Yield using passed value date and maturity date.
extern "C" CDECLEXPORT int  USTBillCalcFromBEYield(DateStruct &valueDate, DateStruct &maturityDate,
	double beYield, double &price, double &mmYield, double &discount);

//INTERNAL METHODS
int preProc(InstrumentStruct &instrument, CalculationsStruct &calculations, Py_Front &pyfront);
int postProc(InstrumentStruct &instrument, CalculationsStruct &calculations, Py_Front &pyfront);
double RateFromCurve(DateStruct baseDate, RateCurveStruct curve, int interpolationMethod, int dayCount);

//DEPRECATED
extern "C" CDECLEXPORT int  getNewCashFlows(CashFlowsStruct &cashFlowsStruct, int adjustRule);
