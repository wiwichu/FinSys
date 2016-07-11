// ExceptionCalc.h: interface for the ExceptionCalc class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "stdafx.h"
#include "Calc.h"
#include <string>

using namespace std;


class ExceptionCalc{
public:
	ExceptionCalc(string DefaultMsg = "Error in Calculator.") 
		: ErrorMsg(DefaultMsg) {};
	string GetError() { return ErrorMsg;};
	void SetError(string InputMsg) { ErrorMsg.assign(InputMsg);};
	virtual ~ExceptionCalc();
protected:
	string ErrorMsg;
};	
