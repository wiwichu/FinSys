#pragma once

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
} CalculationsStruct;

extern "C" __declspec(dllexport) char**  getclassdescriptions(int& size);
extern "C" __declspec(dllexport) char**  getdaycounts(int& size);
extern "C" __declspec(dllexport) char**  getpayfreqs(int& size);
extern "C" __declspec(dllexport) int  getInstrumentDefaults(InstrumentStruct &instrument);
extern "C" __declspec(dllexport) int  getStatusText(int status, char* text, int &textSize);
extern "C" __declspec(dllexport) int  getDefaultDates(InstrumentStruct &instrument, DateStruct &valueDate);
extern "C" __declspec(dllexport) int  getDefaultDatesAndData(InstrumentStruct &instrument, CalculationsStruct &calculations);
extern "C" __declspec(dllexport) char**  getyieldmethods(int& size);
extern "C" __declspec(dllexport) int  calculate(InstrumentStruct &instrument, CalculationsStruct &calculations);

int preProc(InstrumentStruct &instrument, CalculationsStruct &calculations,Py_Front &pyfront);
int postProc(InstrumentStruct &instrument, CalculationsStruct &calculations, Py_Front &pyfront);
