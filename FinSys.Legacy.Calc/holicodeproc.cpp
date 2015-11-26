//#include "stdafx.h"
#include "stdafx.h"
#include "holicodeproc.h"
#include "stdlib.h"

cholicodeproc::cholicodeproc()
{

}
/*
cholicodeproc::cholicodeproc(CDB * DB_parm)
{

	DB_local = DB_parm;

//	DB_local->InitDB();

//	DB_local->GetStatementHandle(&localhandles);

}
*/
cholicodeproc::~cholicodeproc()
{


//	DB_local->EndDB();

//	DB_local->GetStatementHandle(&localhandles);

}

unsigned long cholicodeproc::Setholicodearray(int * TotalCodes)
{
//	int arraycount;
	return_state = return_success;

//	DB_local->loadholicodearray(TotalCodes, &return_state, localhandles);

//func_end:
	
	return return_state;
 
}
/*
unsigned long cholicodeproc::GetHoliCode(CDB::holiday_code_rec * holidaycode,
		unsigned int ThisCode)
{

//	return DB_local->GetHolidayCodeRec(holidaycode, ThisCode);
return 0;
}
*/
/*
unsigned long cholicodeproc::GetHoliCode(char code [holidaycodelength],
		unsigned int ThisCode)
{

	return_state = return_success;
	return return_state;

}
*/
/*
unsigned long cholicodeproc::GetHoliCode(CDB::holiday_code_rec * holidaycode,
		char code [holidaycodelength])
{

//	BOOL BOOL_return;
	return_state = return_success;

	strcpy(holidaycode->code, code);

//	BOOL_return = DB_local->GetHolidayCodeRec(holidaycode, &return_state, localhandles);

	return return_state;

}
*/
/*
unsigned long cholicodeproc::GetHoliDescription(char code [holidaycodelength], 
		char desc [holidaycodelength])
{
	return_state = return_success;
	
	return return_state;

}
*/
/*
	unsigned long cholicodeproc::SetHoliCode(CDB::holiday_code_rec holicode)
{

	return_state = return_success;

//	return_state = DB_local->SetHolidayCodeRec(holicode,localhandles);
	
	return return_state;

}
*/
/*
	unsigned long cholicodeproc::DeleteHoliCode(CDB::holiday_code_rec holicode)
{
//	BOOL BOOL_return;

	return_state = return_success;

//	BOOL_return =	DB_local->DelHolidayCodeRec(holicode, &return_state, localhandles);
	
	return return_state;

}
*/