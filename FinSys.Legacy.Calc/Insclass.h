#ifndef __insclass_H
#define __insclass_H
#ifndef __datedec_H
#include "datedec.h"
#endif
/* Constants for the class fields. */


const	char	instr_bund_class	= 0;	/*{instr_bund_class is
						German Bunds.}*/

const	char	instr_goj_class		= 1;	/*{instr_goj_class is
						Government of Japan.}*/

const	char	instr_euro_class	= 2;	/*{instr_euro_class is
						Eurobonds.}*/

const	char	instr_gilt_class	= 3;	/*{instr_gilt_class is
						UK Gilts.}*/

const	char	instr_ukcd_class	= 4;	/*{instr_ukcd_class is
						UK CD's.}*/

const	char	instr_ukdsc_class	= 5;	/*{instr_ukdsc_class is
						UK Discounts.}*/

const	char	instr_uscd_class	= 6;	/*{instr_uscd_class is
						US CD's.}*/

const	char	instr_usdsc_class	= 7;	/*{instr_usdsc_class is
						US Discounts.}*/

const	char	instr_ustbo_class	= 8;	/*{instr_ustbo_class is
						US Treasury Bonds.}*/

const	char	instr_cp_class		= 9;	/*{instr_cp_class is
						Commercial Paper.}*/

const	char	instr_fschatz_class	= 10;	/*{instr_fschatz_class is
						German Finanzierungsschatz.}*/

const	char	instr_uschatz_class	= 11;	/*{instr_uschatz_class is
						German unverzinsliche Schatzanweisung.*/

const	char	instr_uschatz_buba_class	= 12;	/*{instr_uschatz_buba_class is
						German unverzinsliche Schatzanweisung,
						Bundesbank method.}*/

const	char	instr_ssd_class	= 13;	/*{instr_ssd_class is
						German Schuldscheindarlehen.}*/

const	char	instr_mbs_class		= 14;	/*{instr__class is Mortgage Backed Instruments.}*/

const	char	instr_float_class	= 15;	/*{instr_float_class is floaters.}*/

const	char	instr_cashflow_class	= 100;	/*{instr_cashflow_class is a freely defined cashflow.}*/

const	char	instr_last_class		= 15;	/*{instr_last_class is
						the total classes.}*/

const	char	instr_cust_class	= 99;	/*{instr_cust_class is
						for customizing instruments.}*/

char	*const	instr_goj_class_name	= "GOJ";

char	*const	instr_ustbo_class_name	= "USTBO";

char	*const	instr_usdsc_class_name	= "USDSC";

char	*const	instr_gilt_class_name	= "UKGLT";

char	*const	instr_mbs_class_name	= "MBS";

char	*const	instr_euro_class_name	= "EURO";

char	*const	instr_uscd_class_name	= "USCD";

char	*const	instr_ukcd_class_name	= "UKCD";

char	*const	instr_bund_class_name	= "BUND";

char	*const	instr_ukdsc_class_name	= "UKDSC";

char	*const	instr_float_class_name	= "FRN";

char	*const	instr_cashflow_class_name	= "CASHFLOW";

char	*const	instr_cp_class_name	= "CP";

char	*const	instr_fschatz_class_name	= "F-SCHATZ";

char	*const	instr_uschatz_class_name	= "U-SCHATZ";

char	*const	instr_uschatz_buba_class_name	= "U-SCHATZ BUBA";

char	*const	instr_ssd_class_name	= "SSD";

char	*const	instr_goj_class_desc	= "Japan Gov";

char	*const	instr_ustbo_class_desc	= "US TBond";

char	*const	instr_usdsc_class_desc	= "US Discount ";

char	*const	instr_gilt_class_desc	= "UK Gilt";

char	*const	instr_mbs_class_desc	= "MBS";

char	*const	instr_euro_class_desc	= "Eurobond";

char	*const	instr_uscd_class_desc	= "US CD";

char	*const	instr_ukcd_class_desc	= "UK CD";
                                
char	*const	instr_bund_class_desc	= "German Bund";

char	*const	instr_ukdsc_class_desc	= "UK Discount";

char	*const	instr_float_class_desc	= "Floater";

char	*const	instr_cashflow_class_desc	= "Cash Flow";

char	*const	instr_cp_class_desc	= "Commercial Paper";

char	*const	instr_fschatz_class_desc	= "Finanzierungsschatz";

char	*const	instr_uschatz_class_desc	= "U-Schatz";

char	*const	instr_uschatz_buba_class_desc	= "U-Schatz, Buba Method";

char	*const	instr_ssd_class_desc	= "Schuldscheindarlehen";

char 	*const  instr_class_descs[instr_last_class] =
			{
			instr_bund_class_desc,
			instr_goj_class_desc,
			instr_euro_class_desc,
			instr_gilt_class_desc,
			instr_ukcd_class_desc,
			instr_ukdsc_class_desc,
			instr_uscd_class_desc,
			instr_usdsc_class_desc,
			instr_ustbo_class_desc,
			instr_cp_class_desc,
			instr_fschatz_class_desc,
			instr_uschatz_class_desc,
			instr_uschatz_buba_class_desc,
			instr_ssd_class_desc,
			instr_mbs_class_desc/*,
			instr_float_class_desc,
			instr_cashflow_class_desc*/
			};


#endif

