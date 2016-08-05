
#ifndef __holicodeproc_H
#if defined (BUILDING_YOUR_DLL)
	#define _EX_IN_CLASS __export
	#define _EX_IN_FUNC //_export
	#define _FAR_CLASS  //FAR
	#define _FAR_FUNC   //FAR
	#define _EXTERN  extern
#elif defined(USING_YOUR_DLL)
	#define _EX_IN_CLASS __import
	#define _EX_IN_FUNC
	#define _FAR_CLASS
	#define _FAR_FUNC
	#define _EXTERN
#else
	#define _EX_IN_CLASS
	#define _EX_IN_FUNC
	#define _FAR_CLASS
	#define _FAR_FUNC
	#define _EXTERN
#endif
//

#define __holicodeproc_H
#include <string.h>
#include "errdecs.h"
#include "datedec.h"
#include "wordsymb.h"
//#include "db.h"
#include "shrtdecs.h"
//#include "iodec.h"

class CALC_API _EX_IN_CLASS cholicodeproc : virtual public _errtext
//class _EX_IN_CLASS cholicodeproc : virtual public _errtext
{


private:
//	CDB * DB_local;
//	CDB::DB_Handles localhandles;
//	CDB::holiday_code_rec * holicodearray;
	BOOL BOOL_return;
	unsigned long return_state;

public:
	cholicodeproc();
	~cholicodeproc();
//	cholicodeproc(CDB * DB_parm);
	unsigned long cholicodeproc::Setholicodearray(int * TotalCodes);
//	unsigned long SetHoliCode(CDB::holiday_code_rec holicode);
//	unsigned long GetHoliCode(CDB::holiday_code_rec * holicode,unsigned int ThisCode);
//	unsigned long GetHoliDescription(char code [holidaycodelength], char desc [holidaycodelength]);
//	unsigned long cholicodeproc::GetHoliCode(CDB::holiday_code_rec * holidaycode,	char code [holidaycodelength]);
//	unsigned long DeleteHoliCode(CDB::holiday_code_rec holicode);
//	unsigned long GetHoliCode(char code [holidaycodelength],unsigned int ThisCode);
};


#endif