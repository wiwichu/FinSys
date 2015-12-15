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
} InstrumnentStruct;

extern "C" __declspec(dllexport) char**  getclassdescriptions(int& size);
extern "C" __declspec(dllexport) char**  getdaycounts(int& size);
extern "C" __declspec(dllexport) char**  getpayfreqs(int& size);
extern "C" __declspec(dllexport) int  getInstrumentDefaults(InstrumentStruct &instrument);
extern "C" __declspec(dllexport) int  getStatusText(int status, char* text, int&textSize);

