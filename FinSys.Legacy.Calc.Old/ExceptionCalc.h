// ExceptionCalc.h: interface for the ExceptionCalc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCEPTIONCALC_H__7195AB83_F28C_11D5_905F_1C9BE9000000__INCLUDED_)
#define AFX_EXCEPTIONCALC_H__7195AB83_F28C_11D5_905F_1C9BE9000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "Calc.h"
#include <string>

using namespace std;


class CALC_API ExceptionCalc{
public:
	ExceptionCalc(string DefaultMsg = "Error in Calculator.") 
		: ErrorMsg(DefaultMsg) {};
	string GetError() { return ErrorMsg;};
	void SetError(string InputMsg) { ErrorMsg.assign(InputMsg);};
	virtual ~ExceptionCalc();
protected:
	string ErrorMsg;
};	

#endif // !defined(AFX_EXCEPTIONCALC_H__7195AB83_F28C_11D5_905F_1C9BE9000000__INCLUDED_)
