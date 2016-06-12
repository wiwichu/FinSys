//#include "FinSys.Mobile.Calc.h"
#include "FinSys_Mobile_Calc.h"
char * AndroidInfo()
{
	return FinSys_Mobile_Calc::getTemplateInfo();
}

char**  getclassdescriptions(int& size)
{
	return FinSys_Mobile_Calc::getclassdescriptions_internal(size);
}