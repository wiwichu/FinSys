#pragma once

class FinSys_Mobile_Calc {
public:
    static char * getTemplateInfo();
	static char**  getclassdescriptions_internal(int& size);
	static char**  getdaycounts_internal(int& size);
	FinSys_Mobile_Calc();
    ~FinSys_Mobile_Calc();
};
