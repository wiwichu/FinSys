#ifndef __shrtdecs_H
#define __shrtdecs_H
#ifndef __datedec_H
#include "datedec.h"
#endif
#ifndef __errdecs_H
#include "errdecs.h"
#endif


#define EXPORT
//#define FAR

/*

#define EXPORT _export
#define FAR far
*/
enum booleans {isfalse, istrue}; /*{ isfalse = 0, istrue = 1. }*/
/*
const int isfalse = 0;
const int  istrue = 1;
*/
const   char	null = 0; /*{Define null for string delimination.}*/

const char mm_spot = 2;
/*{mm_spot is the number of spot days for MM deals.}*/
const char mm_holi_adj = event_sched_next_holiday_adj;
/*{mm_holi_adj is the holiday_adjustment for MM deals.}*/
#endif

