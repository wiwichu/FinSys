#include "calc.h"
#ifndef __errdecs_H
#if defined (WIN32)
	#define _HUGE_
#else
	#define _HUGE_ __huge
#endif

const int error_text_len = 200;


const 	unsigned long	return_success	=	0;
/*{ return_success means no errors.}*/

/*{Messages ending in 0 are informational.}*/

const 	unsigned long	return_info_max_mat_exc	= 10;
/*{ return_info_max_mat_exc means maximum maturity is exceeded.}*/
const 	unsigned long	return_info_date_is_holiday	= 20;
/*{ return_info_date_is_holiday means date is holiday.}*/

/*{Messages ending in 1 are errors}*/
const 	unsigned long	return_error	=	1;
/*{ return_error means error.}*/
const 	unsigned long	return_err_bad_base_date = 21;
/*{ return_err_bad_base_date means the date is outside the bounds of the
instrument.}*/
const 	unsigned long	return_err_invalid_period = 31;
/*{ return_err_invalid_period means the period is invalid.}*/
const 	unsigned long	return_err_invalid_pay_sched = 41;
/*{ return_err_invalid_pay_sched means the pay schedule is invalid.}*/
const 	unsigned long	return_err_np_uncalc = 51;
/*{ return_err_np_uncalc means next previous dates are uncalculable.}*/
const 	unsigned long	return_err_loop = 61;
/*{ return_err_loop means loop detected.}*/
const 	unsigned long	return_err_invalid_holiday_adj = 71;
/*{ return_err_invalid_holiday_adj means that holiday_adj did not contain
a valid value.}*/
const 	unsigned long	return_err_holiday_month = 81;
/*{ return_err_holiday_month means entire month is set to holidays.}*/
const 	unsigned long	return_err_rr_pay_mis = 91;
/*{ return_err_rr_pay_mis means a mismatch was detected between the rerate and payment schedule.}*/
const 	unsigned long	return_err_py_incomp = 101;
/*{ return_err_py_incomp means that the instrument is incompatible with the py parameters.}*/
const 	unsigned long	return_err_ill_hol_rule = 111;
/*{ return_ill_hol_rule means that an illegal holiday rule was detected.}*/
const 	unsigned long	return_err_date_form_inv = 121;
/*{ return_date_form_inv means that the date format is invalid.}*/
const 	unsigned long	return_err_date_conv_dir_inv = 131;
/*{ return_err_date_conv_dir_inv means that the conversion direction is invalid.}*/
const 	unsigned long	return_err_date_form_bad = 141;
/*{ return_date_form_bad means that the date is in a bad format.}*/
const 	unsigned long	return_err_date_bad = 151;
/*{ return_date_form_bad means that the date is bad.}*/
const 	unsigned long	return_err_ins_mem = 161;
/*{ return_date_ins_mem means insufficient memory.}*/
const 	unsigned long	return_err_inv_act = 171;
/*{ return_date_inv_act means invalid action.}*/
const 	unsigned long	return_err_hol_inv_rule_spec = 181;
/*{ return_err_hol_inv_rule_spec means invalid holiday rule or specification.}*/
const 	unsigned long	return_err_invalid_pay_freq = 191;
/*{ return_err_invalid_pay_freq means invalid pay frequency.}*/
const 	unsigned long	return_err_invalid_class_desc = 201;
/*{ return_err_invalid_class_desc means invalid class description.}*/
const 	unsigned long	return_err_mat_date_bad = 211;
/*{ return_err_mat_date_bad means invalid maturity date.}*/
const 	unsigned long	return_err_val_date_bad = 221;
/*{ return_err_val_date_bad means invalid value date.}*/
const 	unsigned long	return_err_val_gt_mat = 231;
/*{ return_err_val_gt_mat means value date is greater than maturity date.}*/
const 	unsigned long	return_err_iss_date_bad = 241;
/*{ return_err_iss_date_bad means invalid issue date.}*/
const 	unsigned long	return_err_penult_date_bad = 251;
/*{ return_err_penult_date_bad means invalid penultimate date.}*/
const 	unsigned long	return_err_first_date_bad = 261;
/*{ return_err_first_date_bad means invalid first pay date.}*/
const 	unsigned long	return_err_invalid_month = 271;
/*{ return_err_invalid_month means invalid month in date.}*/
const 	unsigned long	return_err_iss_gt_val = 281;
/*{ return_err_iss_gt_val means issue date is greater than value date.}*/
const 	unsigned long	return_err_iss_gt_mat = 291;
/*{ return_err_iss_gt_mat means issue date is greater than maturity date.}*/
const 	unsigned long	return_err_first_gt_mat = 301;
/*{ return_err_first_gt_mat means first pay date is greater than maturity date.}*/
const 	unsigned long	return_err_iss_ge_first = 311;
/*{ return_err_iss_ge_first means issue date is greater than or equal to
first pay date.}*/
const 	unsigned long	return_err_penult_ge_mat = 321;
/*{ return_err_penult_ge_mat means penultimate pay date is greater than
or equal to maturity date.}*/
const 	unsigned long	return_err_iss_gt_penult = 331;
/*{ return_err_iss_gt_penult means issue date is greater than
penultimate pay date.}*/
const 	unsigned long	return_err_dates_out_synch = 341;
/*{ return_err_dates_out_synch means instrument dates are out of synch.}*/
const 	unsigned long	return_err_non_zero_disc = 351;
/*{ return_err_non_zero_disc means discount instrument with non zero rate.}*/
const 	unsigned long	return_err_neg_int = 361;
/*{ return_err_neg_int means negative interest.}*/
const 	unsigned long	return_err_int_too_high = 371;
/*{ return_err_int_too_high means interest rate is too high.}*/
const 	unsigned long	return_err_yield_meth_inv = 381;
/*{ return_err_yield_meth_inv means yield method is invalid.}*/
const 	unsigned long	return_err_calc_what_inv = 391;
/*{ return_err_calc_what_inv means calculation choice is invalid.}*/
const 	unsigned long	return_err_price_le_zero = 401;
/*{ return_err_price_le_zero means price is less than or equal to zero.}*/
const 	unsigned long	return_err_cpr_out_range = 411;
/*{ return_err_cpr_out_range means the cpr rate is out of range.}*/
const 	unsigned long	return_err_lag_out_range = 421;
/*{ return_err_lag_out_range means the lag is out of range.}*/
const 	unsigned long	return_err_max_coups = 431;
/*{ return_err_max_coups means the number of coupons exceeds the maximum for this calculation.}*/
const 	unsigned long	return_err_event_date_bad = 441;
/*{ return_err_bad_event_date means the event date is invalid.}*/
const 	unsigned long	return_inv_array_size = 451;
/*{ return_inv_aray_size means invalid array size.}*/
const 	unsigned long	return_err_start_less_first = 461;
/*{ return_err_start_less_first means start date is less than first date.}*/
const 	unsigned long	return_err_invalid_holiday = 471;
/*{ return_err_invalid_holiday means holiday rule is invalid.}*/
const 	unsigned long	return_err_fraterm_start_bad = 481;
/*{ return_err_fraterm_start_bad means the start month for the fra is bad.}*/
const 	unsigned long	return_err_fraterm_end_bad = 491;
/*{ return_err_fraterm_end_bad means the start month for the fra is bad.}*/
const 	unsigned long	return_err_deal_date_bad = 501;
/*{ return_err_deal_date_bad means the deal date is bad.}*/
const 	unsigned long	return_err_sett_date_bad = 511;
/*{ return_err_sett_date_bad means the settlement date is bad.}*/
const 	unsigned long	return_err_sett_gt_mat = 521;
/*{ return_err_sett_gt_mat means settlement date is greater than maturity date.}*/
const 	unsigned long	return_err_inv_day_count = 531;
/*{ return_err_inv_day_count means day count is invalid.}*/
const 	unsigned long	return_err_inv_rate_source = 541;
/*{ return_err_inv_rate_source means rate source is invalid.}*/
const 	unsigned long	return_err_inv_interpolation = 551;
/*{ return_err_inv_interpolation means interpolation rule is invalid.}*/
const 	unsigned long	return_err_inv_futstr_day = 561;
/*{ return_err_inv_futstr_day means futures strip day is invalid.}*/
const 	unsigned long	return_err_inv_futstr_period = 571;
/*{ return_err_inv_futstr_period means futures strip period is invalid.}*/
const 	unsigned long	return_err_inv_bid_ask = 581;
/*{ return_err_inv_bid_ask means bid_ask choice is invalid.}*/
const 	unsigned long	return_err_invalid_simp_comp = 591;
/*{ return_err_invalid_simp_comp means simple/compound choice is invalid.}*/
const 	unsigned long	return_err_nonasc_datelist = 601;
/*{ return_err_nonasc_datelist means non ascending date list.}*/
const 	unsigned long	return_err_val_ge_cf = 611;
/*{ return_err_val_ge_cf means value date is greater than first cashflow.}*/
const 	unsigned long	return_err_inval_monthend = 621;
/*{ return_err_inval_monthend means monthend choice is invalid.}*/
const 	unsigned long	return_err_cf_date_wo_flow = 631;
/*{ return_err_cf_date_wo_flow means a cashflow date was entered without a flow.}*/
const 	unsigned long	return_err_max_iter = 641;
/*{ return_err_max_iter means maximum iterations exceeded.}*/
const 	unsigned long	return_err_cashflow = 651;
/*{ return_err_cashflow means a cashflow processing error.}*/
const 	unsigned long	return_err_partpay_out_bounds = 661;
/*{ return_partpay_out_bounds means total partial payments is less than zero or
greater than the maximum.}*/
const 	unsigned long	return_err_partpay_bad_date = 671;
/*{ return_partpay_bad_date means a partial payment date is bad.}*/
const 	unsigned long	return_err_partpay_total_pay_bad = 681;
/*{ return_partpay_total_pay_bad means the total payments did not equal
the principal.}*/
const 	unsigned long	return_err_partpay_date_nonasc = 691;
/*{ return_partpay_date_nonasc means part pay dates are nonascending.}*/
const 	unsigned long return_err_partpay_date_out_bounds = 701;
/*{ return_partpay_date_out_bounds means part pay dates are out of instrument bounds.}*/
const 	unsigned long return_err_invalid_redemp_sched = 711;
/*{ return_err_invalid_pay_freq means redemption schedule.}*/
const 	unsigned long return_err_holiday_code_too_big = 721;
/*{ return_err_holiday_code_too_big means the entered holiday code is too big.}*/
const 	unsigned long return_err_holiday_code_blank = 731;
/*{ return_err_holiday_code_blank means the holiday code is blank.}*/
const 	unsigned long return_err_holiday_base_invalid = 741;
/*{ return_err_holiday_base_invalid means the holiday base is invalid.}*/
const 	unsigned long return_err_holiday_month_invalid = 751;
/*{ return_err_holiday_month_invalid means the holiday month is invalid.}*/
const 	unsigned long return_err_holiday_day_invalid = 761;
/*{ return_err_holiday_day_invalid means the holiday day is invalid.}*/
const 	unsigned long return_err_holiday_base_adj_invalid = 771;
/*{ return_err_holiday_base_adj_invalid means the base adjust is invalid.}*/
const 	unsigned long return_err_adj_times_invalid = 781;
/*{ return_err_adj_times_invalid means the base adjust times is invalid.}*/
const 	unsigned long return_err_holiday_adj_times_too_big = 791;
/*{ return_err_holiday_code_too_big means the entered holiday adjust times is too big.}*/
const 	unsigned long return_err_holiday_adj_times_blank = 801;
/*{ return_err_holiday_code_blank means the holiday adjust times is blank.}*/
const 	unsigned long return_err_holiday_weekday_invalid = 811;
/*{ return_err_holiday_weekday_invalid means the holiday weekday is invalid.}*/
const 	unsigned long return_err_adjust_direction_invalid = 821;
/*{ return_err_adjust_direction_invalid means the adjust direction is invalid.}*/
const 	unsigned long return_err_day_adjust_invalid = 831;
/*{ return_err_day_adjust_invalid means the day adjust is invalid.}*/
const 	unsigned long return_err_base_weekday_invalid = 841;
/*{ return_err_base_weekday_invalid means the base weekday is invalid.}*/
const 	unsigned long return_err_base_year_invalid = 851;
/*{ return_err_base_year_invalid means the base year is invalid.}*/
const 	unsigned long return_err_base_day_invalid = 861;
/*{ return_err_base_day_invalid means the base day is invalid.}*/
const 	unsigned long return_err_day_and_weekday = 871;
/*{ return_err_day_and_weekday means both a base day and a base weekday are chose.}*/
const 	unsigned long return_err_day_nor_weekday = 881;
/*{ return_err_day_nor_weekday means neither a base day nor a base weekday are chose.}*/
const 	unsigned long return_err_weekday_invalid = 891;
/*{ return_err_weekday_invalid means the weekday is invalid.}*/
const 	unsigned long return_err_inactive_choice = 901;
/*{ return_err_inactive_choice means the choice is inactive.}*/
const 	unsigned long return_err_holiday_designation_invalid = 911;
/*{ return_err_holiday_designation_invalid means the holiday designation choice is invalid.}*/
const 	unsigned long return_err_maxholirecs_exceeded = 921;
/*{ return_err_maxholirecs_exceeded means the maximum number of holiday records has been reached.}*/
const 	unsigned long return_err_no_rec = 931;
/*{ return_err_no_rec means no records.}*/
const 	unsigned long return_err_yes_rec = 941;
/*{ return_err_yes_rec means record(s).}*/
const 	unsigned long return_err_DB_invalid = 951;
/*{ return_err_DB_invalid.}*/
const 	unsigned long return_err_stored_message = 961;
/*{ return_err_stored_message means the error message is stored in the string stored_message.}*/
const 	unsigned long return_err_invalid_rc_type = 971;
/*{ return_err_invalid_rc_type means the Rate Curve Instrument Type is invalid.}*/
const 	unsigned long return_err_invalid_rc_source = 981;
/*{ return_err_invalid_rc_source means the Rate Curve Source is invalid.}*/
const 	unsigned long return_err_invalid_rc_unit = 991;
/*{ return_err_invalid_rc_unit means the Rate Curve Unit is invalid.}*/
const 	unsigned long return_err_not_supported = 1001;
/*{ return_err_not_supported means the choice is not supported.}*/
const 	unsigned long return_err_rc_max_instr  = 1011;
/*{ return_err_not_supported means maximum rate curve instruments reached.}*/
const 	unsigned long return_err_LB_ERR_no_select  = 1021;
/*{ return_err_LB_ERR_no_select means no current selection in listbox.}*/
const 	unsigned long return_err_rc_term1_le_zero  = 1031;
/*{ return_err_rc_term1_le_zero means term1 is less than or equal to zero.}*/
const 	unsigned long return_err_rc_rate_lt_zero  = 1041;
/*{ return_err_rc_rate_lt_zero means rate is less than zero.}*/
const 	unsigned long return_err_rc_duplicate_terms  = 1051;
/*{ return_err_rc_rate_duplicate_terms means two instruments with matching terms.}*/
const 	unsigned long return_err_non_ANSI  = 1061;
/*{ return_err_non_ANSI means Non ANSI Code called.}*/



/*{ Messages in the 10000 series relate to IO }*/
const 	unsigned long	return_err_io_max_files = 10001;
/*{ return_err_io_max_files means maximum files exceeded.}*/

/*{ Messages in the 20000 series relate to Screen Management }*/
const 	unsigned long	return_err_inv_scr_meth = 20001;
/*{ return_err_inv_scr_meth means invalid screen method.}*/

/*{ Messages in the 30000 series relate to Databases }*/
const 	unsigned long	return_err_db_rec_nf = 30001;
/*{ return_err_db_rec_nf means record not found.}*/

//class CALC_API _HUGE_ _errtext
class _HUGE_ _errtext
{
public:


void errproc	(unsigned long,
		char [],
		char [],
		char [],
		char []);

/*{errproc accepts an error code, and the name of the calling module. It
processes the error, aborting processing if necessary, displaying the message
and writing it to the log file "err.log."

	Usage:  void	errproc(unsigned long err_code, char module_name[80],
			char opt_par1[80], char opt_par2[80],
			char opt_par3[80])

	where:  err_code =	Is an input parameter of type unsigned long
				which represents the code for the message
				being processed.

		module	 =	Input parameter of type string which
				indicates the calling module.

		opt_par1=	Input parameter of type string which provides
				for optional information to substitute
				err_code.

		opt_par2=	Input parameter of type string which provides
				for optional information to substitute
				err_code.

		opt_par3=	Input parameter of type string which provides
				for optional information to substitute
				err_code.

	 Called by:	<[]

}*/

 void errtext(unsigned long errnum, char error_text [error_text_len]);
void Setstoredmessage(char * error_text, int string_size );

private:

  static char stored_message[error_text_len];

};


#define __errdecs_H
#endif

