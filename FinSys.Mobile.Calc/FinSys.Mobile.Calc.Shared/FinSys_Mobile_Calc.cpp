#include "FinSys_Mobile_Calc.h"
#include "../../Calc/Api.h"

#define PLATFORM_ANDROID 0
#define PLATFORM_IOS 1

char * FinSys_Mobile_Calc::getTemplateInfo()
{
#if PLATFORM == PLATFORM_IOS
	static char info[] = "Platform for iOS";
#elif PLATFORM == PLATFORM_ANDROID
	static char info[] = "Platform for Android";
#else
	static char info[] = "Undefined platform";
#endif

	return info;
}
char**  FinSys_Mobile_Calc::getclassdescriptions_internal(int& size)
{
	return  getclassdescriptions(size);
}
char**  FinSys_Mobile_Calc::getdaycounts_internal(int& size)
{
	return  getdaycounts(size);
}
FinSys_Mobile_Calc::FinSys_Mobile_Calc()
{
}

FinSys_Mobile_Calc::~FinSys_Mobile_Calc()
{
}
