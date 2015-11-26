#ifndef __insevent_MAP
#define __insevent_MAP
#ifdef _ANSIC
#define _INSTEVENT
#else
#define _INSTEVENT Inst_Event::
#endif
#include "holihead.h"
#include "datedec.h"
/* {  The instrument event file, insevent describes events in instruments.
The fields are described below. } */

//static unsigned int inev_keys[5] = {
	/* First Integer is the record length. */
//	35,
	/* set up second integer as key definition. */
//	key_0 		/* This is key 0 */
//	|keys_1		/* There is one key. */
//	|segment_3	/* There are three segments to this key.*/
//	|changes_yes 	/* Changes are permitted. */
//	|dupl_no,        /* Duplicates are not permitted. */
	/* set up third integer as first segment of key 0. */
//	 seg_start_base * 0 /* This segment starts at position 0. */
//	|seg_length_base * 14, /* The segment length is 14. */
	/* set up fourth integer as second segment of key 0. */
//	 seg_start_base * 14 /* This segment starts at position 14. */
//	|seg_length_base * 1, /* The segment length is 1. */
	/* set up fifth integer as third segment of key 0. */
//	 seg_start_base * 15 /* This segment starts at position 15. */
//	|seg_length_base * 5, /* The segment length is 5. */
//};
/*
typedef struct  insevent_key_0{

			char		segment_1[14];
			char		segment_2;
			char		segment_3[5];

			}

		insevent_key_0;
*/
#ifndef _ANSIC
class CALC_API Inst_Event : public holidays_class {

public:
#endif
	
	Inst_Event();
//	Inst_Event(CDB * DB_parm);

  typedef struct 	insevent_struct{

			char 		instr_code[14];

			/*{ instr_code is a unique identifier for the
			instrument. It can be up to 14 characters in
			length. }*/

			char		event;

			/*{Event indicates what type of event it is. See
			the symbols insevent_xxxxx_event for choices.}*/

			date_union 	eff_end_date;

			/*{ eff_end_date is the effective end date of the event. }*/

			date_union 	eff_start_date;

			/*{ eff_start_date is the effective start date of the event. }*/

			date_union 	event_date;

			/*{ event_date is the date the event takes place. }*/

			unsigned char	curr;

			/*{ curr is the currency in which the
			event is denominated. It is validated
			against the currency file (curr) }*/

			float	rate;

			/*{ Rate indicates the amount for this event.}*/

			float	rate2;

			/*{ Rate2 is a second rate for this event.}*/

			char 		descr[50];

			/*{ descr is a description for this event. }*/

			}

		insevent_struct;
private:
//	CDB * DB_local;
//	CDB::DB_Handles localhandles;
#ifndef _ANSIC
};
#endif
#endif

