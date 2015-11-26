#ifndef _CALC_H
#define _CALC_H
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CALC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CALC_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CALC_EXPORTS
#define CALC_API __declspec(dllexport)
#else
#define CALC_API __declspec(dllimport)
#endif

// This class is exported from the Calc.dll
class CALC_API CCalc {
public:
	CCalc(void);
	// TODO: add your methods here.
};

extern CALC_API int nCalc;

CALC_API int fnCalc(void);
#endif
