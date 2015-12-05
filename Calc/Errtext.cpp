#include "stdafx.h"
#include "shrtdecs.h"

char _errtext::stored_message[error_text_len];

void _errtext::Setstoredmessage(char * error_text, int string_length )

{

	if (string_length < error_text_len)
	{


	  memcpy(_errtext::stored_message, error_text, (size_t) string_length);
	  _errtext::stored_message[string_length] = NULL;
/*
	  memcpy(stored_message, error_text, (size_t) string_length);
	  stored_message[string_length] = NULL;
*/
	}
	else
	{
	  memcpy(_errtext::stored_message, error_text,(size_t) error_text_len);
	  _errtext::stored_message[error_text_len - 1] = NULL;
/*
	  memcpy(stored_message, error_text,(size_t) error_text_len);
	  stored_message[error_text_len - 1] = NULL;
*/

	}

}

void _errtext::errtext(unsigned long errnum, char error_text [error_text_len])

{

  switch (errnum)
  {
  case	return_success:
  { strcpy(error_text,
	  "Success");

  break;
  }

	case	return_info_max_mat_exc	:
	{ strcpy(error_text,
		"Maximum Maturity cannot be over fifty years after Issue Date.");

	  break;
	}
	case	return_error	:
	{ strcpy(error_text, "Error.");
	  break;
	}
	case	return_err_bad_base_date :
	{ strcpy(error_text, "The base date is outside the bounds of the instrument.");
		break;
	}
	case	return_err_invalid_period :
	{ strcpy(error_text, "The period is invalid.");
		break;
	}
	case	return_err_invalid_pay_sched :
	{ strcpy(error_text, "The pay schedule is invalid.");
		break;
	}
	case	return_err_np_uncalc :
	{ strcpy(error_text, "Next/Previous dates are uncalculable.");
		break;
	}
	case	return_err_loop :
	{ strcpy(error_text, "Loop detected.");
		break;
	}
	case	return_err_invalid_holiday_adj :
	{ strcpy(error_text, "Invalid Holiday adjustment.");
		break;
	}
	case	return_err_holiday_month :
	{ strcpy(error_text, "Entire month is set to holidays.");
		break;
	}
	case	return_err_rr_pay_mis :
	{ strcpy(error_text,
		"A mismatch was detected between the rerate and payment schedule.");
		break;
	}
	case	return_err_py_incomp :
	{ strcpy(error_text, "The instrument is incompatible with the py parameters.");
		break;
	}
	case	return_err_ill_hol_rule :
	{ strcpy(error_text, "An illegal holiday rule was detected.");
		break;
	}
	case	return_err_date_form_inv :
	{ strcpy(error_text, "The date format is invalid. Should be DD/MM/YYYY.");
		break;
	}
	case	return_err_date_conv_dir_inv :
	{ strcpy(error_text, "The conversion direction is invalid.");
		break;
	}
	case	return_err_date_form_bad :
	{ strcpy(error_text, "The date is in a bad format. Should be DD/MM/YYYY.");
		break;
	}
	case	return_err_date_bad :
	{ strcpy(error_text, "The date is bad.");
		break;
	}
	case	return_err_ins_mem :
	{ strcpy(error_text, "Insufficient memory.");
		break;
	}
	case	return_err_inv_act :
	{ strcpy(error_text, "Invalid action.");
		break;
	}
	case	return_err_hol_inv_rule_spec :
	{ strcpy(error_text, "Invalid holiday rule or specification.");
		break;
	}
	case	return_err_invalid_pay_freq :
	{ strcpy(error_text, "Invalid pay frequency.");
		break;
	}
	case	return_err_invalid_class_desc :
	{ strcpy(error_text, "Invalid class description.");
		break;
	}
	case	return_err_mat_date_bad :
	{ strcpy(error_text, "Invalid maturity date.");
		break;
	}
	case	return_err_val_date_bad :
	{ strcpy(error_text, "Invalid value date.");
		break;
	}
	case	return_err_val_gt_mat :
	{ strcpy(error_text, "Value date is greater than maturity date.");
		break;
	}
	case	return_err_iss_date_bad :
	{ strcpy(error_text, "Invalid issue date.");
		break;
	}
	case	return_err_penult_date_bad :
	{ strcpy(error_text, "Invalid penultimate date.");
		break;
	}
	case	return_err_first_date_bad :
	{ strcpy(error_text, "Invalid first pay date.");
		break;
	}
	case	return_err_invalid_month :
	{ strcpy(error_text, "Invalid month in date.");
		break;
	}
	case	return_err_iss_gt_val :
	{ strcpy(error_text, "Issue date is greater than value date.");
		break;
	}
	case	return_err_iss_gt_mat :
	{ strcpy(error_text, "Issue date is greater than maturity date.");
		break;
	}
	case	return_err_first_gt_mat :
	{ strcpy(error_text, "First pay date is greater than maturity date.");
		break;
	}
	case	return_err_iss_ge_first :
	{ strcpy(error_text,
		"Issue date is greater than or equal to first pay date.");
		break;
	}
	case	return_err_penult_ge_mat :
	{ strcpy(error_text,
		"Penultimate pay date is greater than or equal to maturity date.");
		break;
	}
	case	return_err_iss_gt_penult :
	{ strcpy(error_text, "Issue date is greater than penultimate pay date.");
		break;
	}
	case	return_err_dates_out_synch :
	{ strcpy(error_text, "Instrument dates are not synchronized.");
		break;
	}
	case	return_err_non_zero_disc :
	{ strcpy(error_text, "Discount instruments must have a zero rate.");
		break;
	}
	case	return_err_neg_int :
	{ strcpy(error_text, "Negative interest.");
		break;
	}
	case	return_err_int_too_high :
	{ strcpy(error_text, "Interest rate is too high.");
		break;
	}
	case	return_err_yield_meth_inv :
	{ strcpy(error_text, "Yield method is invalid.");
		break;
	}
	case	return_err_calc_what_inv :
	{ strcpy(error_text, "Calculation choice is invalid.");
		break;
	}
	case	return_err_price_le_zero :
	{ strcpy(error_text, "Price is less than or equal to zero.");
		break;
	}
	case	return_err_cpr_out_range :
	{ strcpy(error_text, "The cpr rate is out of range.");
		break;
	}
	case	return_err_lag_out_range :
	{ strcpy(error_text, "The lag is out of range.");
		break;
	}
	case	return_err_max_coups :
	{ strcpy(error_text, "Maximum coupons exceeded for this calculation.");
		break;
	}
	case	return_err_event_date_bad :
	{ strcpy(error_text, "The event date is invalid.");
		break;
	}
	case	return_inv_array_size :
	{ strcpy(error_text, "Invalid array size.");
		break;
	}
	case	return_err_start_less_first :
	{ strcpy(error_text, "Start date is less than first date.");
		break;
	}
	case	return_err_invalid_holiday :
	{ strcpy(error_text, "Holiday rule is invalid.");
		break;
	}
	case	return_err_fraterm_start_bad :
	{ strcpy(error_text, "The start month for the fra is bad.");
		break;
	}
	case	return_err_fraterm_end_bad :
	{ strcpy(error_text, "The start month for the fra is bad.");
		break;
	}
	case	return_err_deal_date_bad :
	{ strcpy(error_text, "The deal date is bad.");
		break;
	}
	case	return_err_sett_date_bad :
	{ strcpy(error_text, "The settlement date is bad.");
		break;
	}
	case	return_err_sett_gt_mat :
	{ strcpy(error_text, "Settlement date is greater than maturity date.");
		break;
	}
	case	return_err_inv_day_count :
	{ strcpy(error_text, "Day count is invalid.");
		break;
	}
	case	return_err_inv_rate_source :
	{ strcpy(error_text, "Rate source is invalid.");
		break;
	}
	case	return_err_inv_interpolation :
	{ strcpy(error_text, "Interpolation rule is invalid.");
		break;
	}
	case	return_err_inv_futstr_day :
	{ strcpy(error_text, "Futures strip day is invalid.");
		break;
	}
	case	return_err_inv_futstr_period :
	{ strcpy(error_text, "Futures strip period is invalid.");
		break;
	}
	case	return_err_inv_bid_ask :
	{ strcpy(error_text, "Bid/Ask choice is invalid.");
		break;
	}
	case	return_err_invalid_simp_comp :
	{ strcpy(error_text, "Simple/Compound choice is invalid.");
		break;
	}
	case	return_err_nonasc_datelist :
	{ strcpy(error_text, "Non ascending date list.");
		break;
	}
	case	return_err_val_ge_cf :
	{ strcpy(error_text, "Value date is greater than first cashflow.");
		break;
	}
	case	return_err_inval_monthend :
	{ strcpy(error_text, "Monthend choice is invalid.");
		break;
	}
	case	return_err_max_iter :
	{ strcpy(error_text, "Maximum iterations exceeded.");
		break;
	}
	case	return_err_io_max_files :
	{ strcpy(error_text, "Maximum files exceeded.");
		break;
	}
	case	return_err_inv_scr_meth :
	{ strcpy(error_text, "Invalid screen method.");
		break;
	}
	case	return_err_cf_date_wo_flow :
	{ strcpy(error_text, "Cashflow date has no flow.");
		break;
	}
	case	return_err_cashflow :
	{ strcpy(error_text, "Cashflow processing error.");
		break;
	}
	case	return_err_partpay_out_bounds :
	{ strcpy(error_text, "Total Partial Payments is less than zero or greater than the maximum.");
		break;
	}
	case	return_err_partpay_bad_date :
	{ strcpy(error_text, "A Partial Payment Date is bad.");
		break;
	}
	case	return_err_partpay_total_pay_bad :
	{ strcpy(error_text, "Total Partial Payments are not equal to the Principal.");
		break;
	}
	case	return_err_partpay_date_nonasc :
	{ strcpy(error_text, "Partial Payment dates are not ascending.");
		break;
	}
	case	return_err_partpay_date_out_bounds :
	{ strcpy(error_text, "Partial Payment dates are out of instrument bounds.");
		break;
	}
	case	return_err_invalid_redemp_sched :
	{ strcpy(error_text, "Invalid Redemption Schedule.");
		break;
	}
	case	return_err_holiday_code_too_big :
	{ strcpy(error_text, "The entered holiday code is too long.");
		break;
	}
	case	return_err_holiday_code_blank :
	{ strcpy(error_text, "The holiday code is blank.");
		break;
	}
	case	return_err_holiday_base_invalid :
	{ strcpy(error_text, "The holiday base is invalid.");
		break;
	}
	case	return_err_holiday_month_invalid :
	{ strcpy(error_text, "The holiday month is invalid.");
		break;
	}
	case	return_err_holiday_day_invalid :
	{ strcpy(error_text, "The holiday day is invalid.");
		break;
	}
	case	return_err_holiday_base_adj_invalid :
	{ strcpy(error_text, "The holiday base adjustment is invalid.");
		break;
	}
	case	return_err_adj_times_invalid :
	{ strcpy(error_text, "The holiday base adjustment times is invalid.");
		break;
	}
	case	return_err_holiday_adj_times_too_big :
	{ strcpy(error_text, "The entered holiday adjust times is too long.");
		break;
	}
	case	return_err_holiday_adj_times_blank :
	{ strcpy(error_text, "The holiday adjust times must be > 0 and < 1000.");
		break;
	}
	case	return_err_adjust_direction_invalid :
	{ strcpy(error_text, "The adjust direction is invalid.");
		break;
	}
	case	return_err_day_adjust_invalid :
	{ strcpy(error_text, "The day adjust is invalid.");
		break;
	}
	case	return_err_base_weekday_invalid :
	{ strcpy(error_text, "The base weekday is invalid.");
		break;
	}
	case	return_err_base_day_invalid :
	{ strcpy(error_text, "The base day is invalid.");
		break;
	}
	case	return_err_base_year_invalid :
	{ strcpy(error_text, "The base year is invalid.");
		break;
	}
	case	return_err_day_and_weekday :
	case	return_err_day_nor_weekday :
	{ strcpy(error_text, "Either Base Day or Base Weekday must be chosen.");
		break;
	}
	case	return_err_inactive_choice :
	{ strcpy(error_text, "Choice is inactive.");
		break;
	}
	case	return_err_holiday_designation_invalid :
	{ strcpy(error_text, "Invalid Designation.");
		break;
	}
	case	return_err_maxholirecs_exceeded :
	{ strcpy(error_text, "Maximum Holiday Records Exceeded.");
		break;
	}
	case	return_err_no_rec :
	{ strcpy(error_text, "No Records.");
		break;
	}
	case	return_err_yes_rec :
	{ strcpy(error_text, "Record Exists.");
		break;
	}
	case	return_err_DB_invalid :
	{ strcpy(error_text, "Invalid DB method.");
		break;
	}
	case	return_err_stored_message :
	{ 
		strcpy(error_text, _errtext::stored_message);
		break;
	}
	case	return_err_invalid_rc_type :
	{ 
		strcpy(error_text, "Invalid Rate Curve Instrument type.");
		break;
	}
	case	return_err_invalid_rc_source :
	{ 
		strcpy(error_text, "Invalid Rate Curve Source.");
		break;
	}
	case	return_err_invalid_rc_unit :
	{ 
		strcpy(error_text, "Invalid Rate Curve Unit.");
		break;
	}
	case	return_err_not_supported :
	{ 
		strcpy(error_text, "Not Supported.");
		break;
	}
	case	return_err_rc_max_instr :
	{ 
		strcpy(error_text, "Maximum Rate Curve Instruments reached.");
		break;
	}
	case	return_err_LB_ERR_no_select :
	{ 
		strcpy(error_text, "No current selection.");
		break;
	}
	case	return_err_rc_term1_le_zero :
	{ 
		strcpy(error_text, "Term1 must be greater than zero.");
		break;
	}
	case	return_err_rc_rate_lt_zero :
	{ 
		strcpy(error_text, "Rate must not be negative.");
		break;
	}
	case	return_err_rc_duplicate_terms:
	{ 
		strcpy(error_text, "Two Instruments have matching Type/Term/Unit.");
		break;
	}
	case	return_err_non_ANSI:
	{ 
		strcpy(error_text, "Non ANSI Call.");
		break;
	}
	case	return_err_db_rec_nf:
	{ 
		strcpy(error_text, "Record not found.");
		break;
	}
	case	return_info_date_is_holiday:
	{ 
		strcpy(error_text, "Date is a Holiday.");
		break;
	}
	default:
	{
	  strcpy (error_text, "Undefined Error");
		break;
	}

  }






}

/*
_errtext::_errtext()
{

}
*/

