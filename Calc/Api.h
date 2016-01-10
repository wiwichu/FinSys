#pragma once

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
} CashFlowStruct;
typedef struct CashFlowsStruct
{
	CashFlowStruct *cashFlows;
	int size;
} CashFlowsStruct;
typedef struct DateStruct
{
	int year;
	int month;
	int day;
} DateStruct;

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
} CalculationsStruct;

extern "C" __declspec(dllexport) char**  getclassdescriptions(int& size);
extern "C" __declspec(dllexport) char**  getHolidayAdjust(int& size);
extern "C" __declspec(dllexport) char**  getdaycounts(int& size);
extern "C" __declspec(dllexport) char**  getpayfreqs(int& size);
extern "C" __declspec(dllexport) int  getInstrumentDefaults(InstrumentStruct &instrument);
extern "C" __declspec(dllexport) int  getInstrumentDefaultsAndData(InstrumentStruct &instrument, CalculationsStruct &calculations);
extern "C" __declspec(dllexport) int  getStatusText(int status, char* text, int &textSize);
extern "C" __declspec(dllexport) int  getDefaultDates(InstrumentStruct &instrument, DateStruct &valueDate);
extern "C" __declspec(dllexport) int  getDefaultDatesAndData(InstrumentStruct &instrument, CalculationsStruct &calculations);
extern "C" __declspec(dllexport) char**  getyieldmethods(int& size);
extern "C" __declspec(dllexport) int  calculate(InstrumentStruct &instrument, CalculationsStruct &calculations);
extern "C" __declspec(dllexport) int  calculateWithCashFlows(InstrumentStruct &instrument, CalculationsStruct &calculations,CashFlowsStruct &cashFlowsStruct, int adjustRule);
extern "C" __declspec(dllexport) int  getCashFlows(CashFlowsStruct &cashFlowsStruct, int adjustRule);
extern "C" __declspec(dllexport) int  getNewCashFlows(CashFlowsStruct &cashFlowsStruct, int adjustRule);
extern "C" __declspec(dllexport) int  tenor(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &tenor);
extern "C" __declspec(dllexport) int  intCalc(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int &days, double &dayCountFraction);
extern "C" __declspec(dllexport) int  forecast(DateStruct &startDate, DateStruct &endDate, int dayCountRule, int months, int days);


int preProc(InstrumentStruct &instrument, CalculationsStruct &calculations,Py_Front &pyfront);
int postProc(InstrumentStruct &instrument, CalculationsStruct &calculations, Py_Front &pyfront);
