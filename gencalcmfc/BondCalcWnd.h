#if !defined(AFX_BONDCALCWND_H__F25D7041_5A6D_11D1_8F5B_444553540000__INCLUDED_)
#define AFX_BONDCALCWND_H__F25D7041_5A6D_11D1_8F5B_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BondCalcWnd.h : header file
//
#include "guidecs.h"
#include <pyfront.h>

  const int ID_prompt  = -1;
  const int ID_instr_class  = 111;
  const int ID_interest_rate  = 112;
  const int ID_maturity_date  = 113 ;
  const int ID_value_date  = 114;
  const int ID_clean_price  = 117;
  const int ID_accrued_interest  = 118;
  const int ID_dirty_price  = 119;
  const int ID_yield_discount  = 120;
  const int ID_day_count  = 121;
  const int ID_pay_freq  = 123;
  const int ID_issue_date  = 124;
  const int ID_first_pay  = 125;
  const int ID_penult_pay  = 126;
  const int ID_duration  = 127;
  const int ID_mod_duration  = 128;
  const int ID_convexity  = 129;
  const int ID_yield_meth  = 130;
  const int ID_ex_coup  = 131;
  const int ID_calc_choice  = 132;
  const int ID_y_from_p  = 133;
  const int ID_p_from_y  = 134;
  const int ID_int_days  = 135;
  const int ID_def_date  = 136;
  const int ID_calculate  = 137;
  const int ID_pvbp  = 138;
  const int ID_yield_days  = 141;
  const int ID_yield_freq  = 142;
  const int ID_monthend = 144;
  const int ID_excoup = 145; 

  const int instr_class_prompt_x = col_one_left;
  const int instr_class_prompt_y = row_one_top + standard_prompt_adjust;
  const int instr_class_prompt_w = col_one_width;
  const int instr_class_prompt_h = col_one_height;
  const int instr_class_prompt_len = standard_prompt_len;

  const int instr_class_x = col_two_left;
  const int instr_class_y = row_one_top;
  const int instr_class_w = col_two_width;
  const int instr_class_h = col_two_scr_height;
  const int instr_class_d = col_two_height;

  const int holiday_prompt_x = col_one_left;
  const int holiday_prompt_y = row_two_top + standard_prompt_adjust;
  const int holiday_prompt_w = col_one_width;
  const int holiday_prompt_h = col_one_height;
  const int holiday_prompt_len = standard_prompt_len;

  const int holiday_x = col_two_left;
  const int holiday_y = row_two_top;
  const int holiday_w = col_two_width;
  const int holiday_h = col_two_scr_height;
  const int holiday_d = col_two_height;
  const int holiday_len = standard_prompt_len;

  const int interest_rate_prompt_x = col_one_left;
  const int interest_rate_prompt_y = row_three_top + standard_prompt_adjust;
  const int interest_rate_prompt_w = col_one_width;
  const int interest_rate_prompt_h = col_one_height;
  const int interest_rate_prompt_len = standard_prompt_len;

  const int interest_rate_x = col_two_left;
  const int interest_rate_y = row_three_top;
  const int interest_rate_w = col_two_width;
  const int interest_rate_h = col_two_height;
  const int interest_rate_len = standard_prompt_len;

  const int value_date_prompt_x = col_one_left;
  const int value_date_prompt_y = row_four_top + standard_prompt_adjust;
  const int value_date_prompt_w = col_one_width;
  const int value_date_prompt_h = col_one_height;
  const int value_date_prompt_len = standard_prompt_len;

  const int value_date_x = col_two_left;
  const int value_date_y = row_four_top;
  const int value_date_w = col_two_width;
  const int value_date_h = col_two_height;
  const int value_date_len = standard_prompt_len;

  const int previous_coup_prompt_x = col_one_left;
  const int previous_coup_prompt_y = row_five_top + standard_prompt_adjust;
  const int previous_coup_prompt_w = col_one_width;
  const int previous_coup_prompt_h = col_one_height;
  const int previous_coup_prompt_len = standard_prompt_len;

  const int previous_coup_x = col_two_left;
  const int previous_coup_y = row_five_top + standard_prompt_adjust;
  const int previous_coup_w = col_two_width;
  const int previous_coup_h = col_two_height;
  const int previous_coup_len = standard_prompt_len;

  const int next_coup_prompt_x = col_one_left;
  const int next_coup_prompt_y = row_six_top + standard_prompt_adjust;
  const int next_coup_prompt_w = col_one_width;
  const int next_coup_prompt_h = col_one_height;
  const int next_coup_prompt_len = standard_prompt_len;

  const int next_coup_x = col_two_left;
  const int next_coup_y = row_six_top + standard_prompt_adjust;
  const int next_coup_w = col_two_width;
  const int next_coup_h = col_two_height;
  const int next_coup_len = standard_prompt_len;

  const int clean_price_prompt_x = col_one_left;
  const int clean_price_prompt_y = row_seven_top + standard_prompt_adjust;
  const int clean_price_prompt_w = col_one_width;
  const int clean_price_prompt_h = col_one_height;
  const int clean_price_prompt_len = standard_prompt_len;

  const int clean_price_x = col_two_left;
  const int clean_price_y = row_seven_top;
  const int clean_price_w = col_two_width;
  const int clean_price_h = col_two_height;
  const int clean_price_len = standard_prompt_len;

  const int accrued_interest_prompt_x = col_one_left;
  const int accrued_interest_prompt_y = row_eight_top + standard_prompt_adjust;
  const int accrued_interest_prompt_w = col_one_width;
  const int accrued_interest_prompt_h = col_one_height;
  const int accrued_interest_prompt_len = standard_prompt_len;

  const int accrued_interest_x = col_two_left;
  const int accrued_interest_y = row_eight_top + standard_prompt_adjust;
  const int accrued_interest_w = col_two_width;
  const int accrued_interest_h = col_two_height;
  const int accrued_interest_len = standard_prompt_len;

  const int dirty_price_prompt_x = col_one_left;
  const int dirty_price_prompt_y = row_nine_top + standard_prompt_adjust;
  const int dirty_price_prompt_w = col_one_width;
  const int dirty_price_prompt_h = col_one_height;
  const int dirty_price_prompt_len = standard_prompt_len;

  const int dirty_price_x = col_two_left;
  const int dirty_price_y = row_nine_top + standard_prompt_adjust;
  const int dirty_price_w = col_two_width;
  const int dirty_price_h = col_two_height;
  const int dirty_price_len = standard_prompt_len;

  const int yield_discount_prompt_x = col_one_left;
  const int yield_discount_prompt_y = row_ten_top + standard_prompt_adjust;
  const int yield_discount_prompt_w = col_one_width;
  const int yield_discount_prompt_h = col_one_height;
  const int yield_discount_prompt_len = standard_prompt_len;

  const int yield_discount_x = col_two_left;
  const int yield_discount_y = row_ten_top;
  const int yield_discount_w = col_two_width;
  const int yield_discount_h = col_two_height;
  const int yield_discount_len = standard_prompt_len;

  const int yield_days_prompt_x = col_one_left;
  const int yield_days_prompt_y = row_eleven_top + standard_prompt_adjust;
  const int yield_days_prompt_w = col_one_width;
  const int yield_days_prompt_h = col_one_height;
  const int yield_days_prompt_len = standard_prompt_len;

  const int yield_days_x = col_two_left;
  const int yield_days_y = row_eleven_top;
  const int yield_days_w = col_two_width;
  const int yield_days_h = col_two_scr_height;
  const int yield_days_d = col_two_height;
  const int yield_days_len = standard_prompt_len;

  const int yield_freq_prompt_x = col_one_left;
  const int yield_freq_prompt_y = row_twelve_top + standard_prompt_adjust;
  const int yield_freq_prompt_w = col_one_width;
  const int yield_freq_prompt_h = col_one_height;
  const int yield_freq_prompt_len = standard_prompt_len;

  const int yield_freq_x = col_two_left;
  const int yield_freq_y = row_twelve_top;
  const int yield_freq_w = col_two_width;
  const int yield_freq_h = col_two_scr_height;
  const int yield_freq_d = col_two_height;
  const int yield_freq_len = standard_prompt_len;

  const int duration_prompt_x = col_one_left;
  const int duration_prompt_y = row_thirteen_top + standard_prompt_adjust;
  const int duration_prompt_w = col_one_width;
  const int duration_prompt_h = col_one_height;
  const int duration_prompt_len = standard_prompt_len;

  const int duration_x = col_two_left;
  const int duration_y = row_thirteen_top + standard_prompt_adjust;
  const int duration_w = col_two_width;
  const int duration_h = col_two_height;
  const int duration_len = standard_prompt_len;

  const int mod_duration_prompt_x = col_one_left;
  const int mod_duration_prompt_y = row_fourteen_top + standard_prompt_adjust;
  const int mod_duration_prompt_w = col_one_width;
  const int mod_duration_prompt_h = col_one_height;
  const int mod_duration_prompt_len = standard_prompt_len;

  const int mod_duration_x = col_two_left;
  const int mod_duration_y = row_fourteen_top + standard_prompt_adjust;
  const int mod_duration_w = col_two_width;
  const int mod_duration_h = col_two_height;
  const int mod_duration_len = standard_prompt_len;

  const int convexity_prompt_x = col_one_left;
  const int convexity_prompt_y = row_fifteen_top + standard_prompt_adjust;
  const int convexity_prompt_w = col_one_width;
  const int convexity_prompt_h = col_one_height;
  const int convexity_prompt_len = standard_prompt_len;

  const int convexity_x = col_two_left;
  const int convexity_y = row_fifteen_top + standard_prompt_adjust;
  const int convexity_w = col_two_width;
  const int convexity_h = col_two_height;
  const int convexity_len = standard_prompt_len;

  const int pvbp_prompt_x = col_one_left;
  const int pvbp_prompt_y = row_sixteen_top + standard_prompt_adjust;
  const int pvbp_prompt_w = col_one_width;
  const int pvbp_prompt_h = col_one_height;
  const int pvbp_prompt_len = standard_prompt_len;

  const int pvbp_x = col_two_left;
  const int pvbp_y = row_sixteen_top + standard_prompt_adjust;
  const int pvbp_w = col_two_width;
  const int pvbp_h = col_two_height;
  const int pvbp_len = standard_prompt_len;

  const int sm_duration_prompt_x = col_one_left;
  const int sm_duration_prompt_y = row_one_top + standard_prompt_adjust;
  const int sm_duration_prompt_w = col_one_width;
  const int sm_duration_prompt_h = col_one_height;
  const int sm_duration_prompt_len = standard_prompt_len;

  const int sm_duration_x = col_two_left;
  const int sm_duration_y = row_one_top + standard_prompt_adjust;
  const int sm_duration_w = col_two_width;
  const int sm_duration_h = col_two_height;
  const int sm_duration_len = standard_prompt_len;

  const int sm_mod_duration_prompt_x = col_one_left;
  const int sm_mod_duration_prompt_y = row_two_top + standard_prompt_adjust;
  const int sm_mod_duration_prompt_w = col_one_width;
  const int sm_mod_duration_prompt_h = col_one_height;
  const int sm_mod_duration_prompt_len = standard_prompt_len;

  const int sm_mod_duration_x = col_two_left;
  const int sm_mod_duration_y = row_two_top + standard_prompt_adjust;
  const int sm_mod_duration_w = col_two_width;
  const int sm_mod_duration_h = col_two_height;
  const int sm_mod_duration_len = standard_prompt_len;

  const int sm_convexity_prompt_x = col_one_left;
  const int sm_convexity_prompt_y = row_three_top + standard_prompt_adjust;
  const int sm_convexity_prompt_w = col_one_width;
  const int sm_convexity_prompt_h = col_one_height;
  const int sm_convexity_prompt_len = standard_prompt_len;

  const int sm_convexity_x = col_two_left;
  const int sm_convexity_y = row_three_top + standard_prompt_adjust;
  const int sm_convexity_w = col_two_width;
  const int sm_convexity_h = col_two_height;
  const int sm_convexity_len = standard_prompt_len;

  const int sm_pvbp_prompt_x = col_one_left;
  const int sm_pvbp_prompt_y = row_four_top + standard_prompt_adjust;
  const int sm_pvbp_prompt_w = col_one_width;
  const int sm_pvbp_prompt_h = col_one_height;
  const int sm_pvbp_prompt_len = standard_prompt_len;

  const int sm_pvbp_x = col_two_left;
  const int sm_pvbp_y = row_four_top + standard_prompt_adjust;
  const int sm_pvbp_w = col_two_width;
  const int sm_pvbp_h = col_two_height;
  const int sm_pvbp_len = standard_prompt_len;

  const int maturity_date_prompt_x = col_three_left;
  const int maturity_date_prompt_y = row_one_top + standard_prompt_adjust;
  const int maturity_date_prompt_w = col_three_width;
  const int maturity_date_prompt_h = col_three_height;
  const int maturity_date_prompt_len = standard_prompt_len;

  const int maturity_date_x = col_four_left;
  const int maturity_date_y = row_one_top;
  const int maturity_date_w = col_four_width;
  const int maturity_date_h = col_four_height;
  const int maturity_date_len = standard_prompt_len;

  const int day_count_prompt_x = col_three_left;
  const int day_count_prompt_y = row_two_top + standard_prompt_adjust;
  const int day_count_prompt_w = col_three_width;
  const int day_count_prompt_h = col_three_height;
  const int day_count_prompt_len = standard_prompt_len;

  const int day_count_x = col_four_left;
  const int day_count_y = row_two_top;
  const int day_count_w = col_four_width;
  const int day_count_h = col_four_scr_height;
  const int day_count_d = col_four_height;
  const int day_count_len = standard_prompt_len;

  const int pay_freq_prompt_x = col_three_left;
  const int pay_freq_prompt_y = row_three_top + standard_prompt_adjust;
  const int pay_freq_prompt_w = col_three_width;
  const int pay_freq_prompt_h = col_three_height;
  const int pay_freq_prompt_len = standard_prompt_len;

  const int pay_freq_x = col_four_left;
  const int pay_freq_y = row_three_top;
  const int pay_freq_w = col_four_width;
  const int pay_freq_h = col_four_scr_height;
  const int pay_freq_d = col_four_height;
  const int pay_freq_len = standard_prompt_len;

  const int date_format_prompt_x = col_three_left;
  const int date_format_prompt_y = row_four_top + standard_prompt_adjust;
  const int date_format_prompt_w = col_three_width;
  const int date_format_prompt_h = col_three_height;
  const int date_format_prompt_len = standard_prompt_len;

  const int def_date_x = col_four_left;
  const int def_date_y = row_four_top;
  const int def_date_w = col_four_width;
  const int def_date_h = col_four_height;
  const int def_date_d = col_four_height;
  const int def_date_len = standard_prompt_len;

  const int issue_date_prompt_x = col_three_left;
  const int issue_date_prompt_y = row_five_top + standard_prompt_adjust;
  const int issue_date_prompt_w = col_three_width;
  const int issue_date_prompt_h = col_three_height;
  const int issue_date_prompt_len = standard_prompt_len;

  const int issue_date_x = col_four_left;
  const int issue_date_y = row_five_top;
  const int issue_date_w = col_four_width;
  const int issue_date_h = col_four_height;
  const int issue_date_d = col_four_height;
  const int issue_date_len = standard_prompt_len;

  const int first_pay_prompt_x = col_three_left;
  const int first_pay_prompt_y = row_six_top + standard_prompt_adjust;
  const int first_pay_prompt_w = col_three_width;
  const int first_pay_prompt_h = col_three_height;
  const int first_pay_prompt_len = standard_prompt_len;

  const int first_pay_x = col_four_left;
  const int first_pay_y = row_six_top;
  const int first_pay_w = col_four_width;
  const int first_pay_h = col_four_height;
  const int first_pay_d = col_four_height;
  const int first_pay_len = standard_prompt_len;

  const int penult_pay_prompt_x = col_three_left;
  const int penult_pay_prompt_y = row_seven_top + standard_prompt_adjust;
  const int penult_pay_prompt_w = col_three_width;
  const int penult_pay_prompt_h = col_three_height;
  const int penult_pay_prompt_len = standard_prompt_len;

  const int penult_pay_x = col_four_left;
  const int penult_pay_y = row_seven_top + standard_prompt_adjust;
  const int penult_pay_w = col_four_width;
  const int penult_pay_h = col_four_height;
  const int penult_pay_d = col_four_height;
  const int penult_pay_len = standard_prompt_len;

  const int ex_coup_prompt_x = col_three_left;
  const int ex_coup_prompt_y = row_eight_top + standard_prompt_adjust;
  const int ex_coup_prompt_w = col_three_width;
  const int ex_coup_prompt_h = col_three_height;
  const int ex_coup_prompt_len = standard_prompt_len;

  const int ex_coup_x = col_four_left;
  const int ex_coup_y = row_eight_top + standard_prompt_adjust;
  const int ex_coup_w = col_four_width;
  const int ex_coup_h = col_four_height;
  const int ex_coup_d = col_four_height;
  const int ex_coup_len = standard_prompt_len;

  const int int_days_prompt_x = col_three_left;
  const int int_days_prompt_y = row_nine_top + standard_prompt_adjust;
  const int int_days_prompt_w = col_three_width;
  const int int_days_prompt_h = col_three_height;
  const int int_days_prompt_len = standard_prompt_len;

  const int int_days_x = col_four_left;
  const int int_days_y = row_nine_top + standard_prompt_adjust;
  const int int_days_w = col_four_width;
  const int int_days_h = col_four_height;
  const int int_days_d = col_four_height;
  const int int_days_len = standard_prompt_len;

  const int yield_meth_prompt_x = col_three_left;
  const int yield_meth_prompt_y = row_ten_top + standard_prompt_adjust;
  const int yield_meth_prompt_w = col_three_width;
  const int yield_meth_prompt_h = col_three_height;
  const int yield_meth_prompt_len = standard_prompt_len;

  const int yield_meth_x = col_four_left;
  const int yield_meth_y = row_ten_top;
  const int yield_meth_w = col_four_width;
  const int yield_meth_h = col_four_scr_height;
  const int yield_meth_d = col_four_height;
  const int yield_meth_len = standard_prompt_len;

  const int monthend_prompt_x = col_five_left;
  const int monthend_prompt_y = row_one_top + standard_prompt_adjust;
  const int monthend_prompt_w = col_five_width/2;
  const int monthend_prompt_h = col_five_height;
  const int monthend_prompt_len = standard_prompt_len;

  const int monthend_x = col_five_left + (col_five_width/2);
  const int monthend_y = row_one_top;
  const int monthend_w = col_five_width/2;
  const int monthend_h = col_five_scr_height;
  const int monthend_d = col_five_height;
  const int monthend_len = standard_prompt_len;

  const int excoup_prompt_x = col_five_left;
  const int excoup_prompt_y = row_eight_top + standard_prompt_adjust;
  const int excoup_prompt_w = col_five_width/2;
  const int excoup_prompt_h = col_five_height;
  const int excoup_prompt_len = standard_prompt_len;

  const int excoup_x = col_five_left + (col_five_width/2);
  const int excoup_y = row_eight_top;
  const int excoup_w = col_five_width/2;
  const int excoup_h = col_five_scr_height;
  const int excoup_d = col_five_height;
  const int excoup_len = standard_prompt_len;

  const int calc_choice_x = col_three_left;
  const int calc_choice_y = row_eleven_top;
  const int calc_choice_w = col_four_left - col_three_left;
  const int calc_choice_h = (col_three_height * 4);

  const int y_from_p_x = col_three_left + 5;
  const int y_from_p_y = row_twelve_top;
  const int y_from_p_w = col_three_width;
  const int y_from_p_h = col_three_height;

  const int p_from_y_x = col_three_left + 5;
  const int p_from_y_y = row_thirteen_top;
  const int p_from_y_w = col_three_width;
  const int p_from_y_h = col_three_height;

  const int customize_x = col_four_left + 5;
  const int customize_y = row_eleven_top;
  const int customize_w = col_four_width - 5;
  const int customize_h = col_four_height;
  const int customize_d = col_four_height;
  const int customize_len = standard_prompt_len;

  const int calculate_x = col_four_left + 5;
  const int calculate_y = row_thirteen_top;
  const int calculate_w = col_four_width - 5;
  const int calculate_h = col_four_height;
  const int calculate_d = col_four_height;
  const int calculate_len = standard_prompt_len;

  const int inquiries_x = col_four_left + 5;
  const int inquiries_y = row_thirteen_top;
  const int inquiries_w = col_four_width - 5;
  const int inquiries_h = col_four_height;
  const int inquiries_d = col_four_height;
  const int inquiries_len = standard_prompt_len;

  const int calc_x = instr_class_x + instr_class_w + 20;
  const int calc_y = 20;
  const int calc_w = 60;
  const int calc_h = 30;
  const int calc_d = 40;

  const int canc_x = calc_x + calc_w + 2;
  const int canc_y = 20;
  const int canc_w = 60;
  const int canc_h = 30;
  const int canc_d = 40;

/* Constants for the instrument characteristics.*/

  const int part_pays_x = col_five_left;
  const int part_pays_y = row_four_top;
  const int part_pays_w = col_five_width;
  const int part_pays_h = col_five_height;
  const int part_pays_d = col_five_height;
  const int part_pays_len = standard_prompt_len;

  const int sink_fund_x = col_five_left;
  const int sink_fund_y = row_five_top;
  const int sink_fund_w = col_five_width;
  const int sink_fund_h = col_five_height;
  const int sink_fund_len = standard_prompt_len;

  const int pool_fact_x = col_one_left;
  const int pool_fact_y = row_three_top;
  const int pool_fact_w = col_one_width;
  const int pool_fact_h = standard_row_height;
  const int pool_fact_len = standard_prompt_len;
/* Constants for Partial Payments. */

  const int part_pays_basis_prompt_x = col_one_left;
  const int part_pays_basis_prompt_y = row_one_top + standard_prompt_adjust;
  const int part_pays_basis_prompt_w = col_one_width;
  const int part_pays_basis_prompt_h = col_one_height;
  const int part_pays_basis_prompt_len = standard_prompt_len;

  const int part_pays_basis_x = col_two_left;
  const int part_pays_basis_y = row_one_top;
  const int part_pays_basis_w = col_two_width;
  const int part_pays_basis_h = col_two_height;
  const int part_pays_basis_len = standard_prompt_len;

  const int part_pays_dates_title_x = col_one_left;
  const int part_pays_dates_title_y = row_two_top;
  const int part_pays_dates_title_w = col_one_width;
  const int part_pays_dates_title_h = standard_row_height;
  const int part_pays_dates_title_d = col_one_height;
  const int part_pays_dates_title_len = standard_prompt_len;

  const int part_pays_price_title_x = col_two_left;
  const int part_pays_price_title_y = row_two_top;
  const int part_pays_price_title_w = col_two_width;
  const int part_pays_price_title_h = standard_row_height;
  const int part_pays_price_title_d = col_two_height;
  const int part_pays_price_title_len = standard_prompt_len;

  const int part_pays_dates_base_x = part_pays_dates_title_x;
  const int part_pays_dates_base_y = part_pays_dates_title_y + whole_row_adjust;
  const int part_pays_dates_base_w = part_pays_dates_title_w;
  const int part_pays_dates_base_h = part_pays_dates_title_h;
  const int part_pays_dates_base_d = part_pays_dates_title_d;
  const int part_pays_dates_base_len = part_pays_dates_title_len;

  const int part_pays_price_base_x = part_pays_price_title_x;
  const int part_pays_price_base_y = part_pays_price_title_y + whole_row_adjust;
  const int part_pays_price_base_w = part_pays_price_title_w;
  const int part_pays_price_base_h = part_pays_price_title_h;
  const int part_pays_price_base_d = part_pays_price_title_d;
  const int part_pays_price_base_len = part_pays_price_title_len;

  const int part_pays_dates_x[max_part_pays] = {col_one_left,
							col_one_left,
							col_one_left,
							col_one_left,
							col_one_left
							};
  const int part_pays_dates_y[max_part_pays] = {row_five_top,
							row_six_top,
							row_seven_top,
							row_eight_top,
							row_nine_top
							};
  const int part_pays_dates_w[max_part_pays] = {col_one_width,
							col_one_width,
							col_one_width,
							col_one_width,
							col_one_width
							};
  const int part_pays_dates_h[max_part_pays] = {standard_row_height,
							standard_row_height,
							standard_row_height,
							standard_row_height,
							standard_row_height
							};
  const int part_pays_dates_len[max_part_pays] = {standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len
						};

  const int part_pays_price_x[max_part_pays] = {col_two_left,
							col_two_left,
							col_two_left,
							col_two_left,
							col_two_left
							};
  const int part_pays_price_y[max_part_pays] = {row_five_top,
							row_six_top,
							row_seven_top,
							row_eight_top,
							row_nine_top
							};
  const int part_pays_price_w[max_part_pays] = {col_two_width,
							col_two_width,
							col_two_width,
							col_two_width,
							col_two_width
							};
  const int part_pays_price_h[max_part_pays] = {standard_row_height,
							standard_row_height,
							standard_row_height,
							standard_row_height,
					      standard_row_height
							};
  const int part_pays_price_len[max_part_pays] = {standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len
						};


  const int pp_accept_x = col_three_left;
  const int pp_accept_y = row_one_top;
  const int pp_accept_w = col_three_width;
  const int pp_accept_h = standard_row_height;
  const int pp_accept_d = col_three_height;
  const int pp_accept_len = standard_prompt_len;

  const int pp_clear_x = col_three_left;
  const int pp_clear_y = row_two_top;
  const int pp_clear_w = col_three_width;
  const int pp_clear_h = standard_row_height;
  const int pp_clear_d = col_three_height;
  const int pp_clear_len = standard_prompt_len;

  const int pp_close_x = col_three_left;
  const int pp_close_y = row_three_top;
  const int pp_close_w = col_three_width;
  const int pp_close_h = standard_row_height;
  const int pp_close_d = col_three_height;
  const int pp_close_len = standard_prompt_len;

/* Constants for Sinkung Fund. */

  const int sink_fund_mat_prompt_x = col_one_left;
  const int sink_fund_mat_prompt_y = row_one_top + standard_prompt_adjust;
  const int sink_fund_mat_prompt_w = col_one_width;
  const int sink_fund_mat_prompt_h = col_one_height;
  const int sink_fund_mat_prompt_len = standard_prompt_len;

  const int sink_fund_mat_x = col_two_left;
  const int sink_fund_mat_y = row_one_top;
  const int sink_fund_mat_w = col_two_width;
  const int sink_fund_mat_h = col_two_scr_height;
  const int sink_fund_mat_d = col_two_height;
  const int sink_fund_mat_len = standard_prompt_len;

  const int sink_fund_base_prompt_x = col_three_left;
  const int sink_fund_base_prompt_y = row_two_top + standard_prompt_adjust;
  const int sink_fund_base_prompt_w = col_three_width;
  const int sink_fund_base_prompt_h = col_three_height;
  const int sink_fund_base_prompt_len = standard_prompt_len;

  const int sink_fund_base_x = col_four_left;
  const int sink_fund_base_y = row_two_top;
  const int sink_fund_base_w = col_four_width;
  const int sink_fund_base_h = col_four_height;
  const int sink_fund_base_len = standard_prompt_len;

  const int sink_fund_dates_title_x = col_one_left;
  const int sink_fund_dates_title_y = row_two_top;
  const int sink_fund_dates_title_w = col_one_width;
  const int sink_fund_dates_title_h = standard_row_height;
  const int sink_fund_dates_title_d = col_one_height;
  const int sink_fund_dates_title_len = standard_prompt_len;

  const int sink_fund_price_title_x = col_two_left;
  const int sink_fund_price_title_y = row_two_top;
  const int sink_fund_price_title_w = col_two_width;
  const int sink_fund_price_title_h = standard_row_height;
  const int sink_fund_price_title_d = col_two_height;
  const int sink_fund_price_title_len = standard_prompt_len;

  const int sink_fund_dates_base_x = sink_fund_dates_title_x;
  const int sink_fund_dates_base_y = sink_fund_dates_title_y + whole_row_adjust;
  const int sink_fund_dates_base_w = sink_fund_dates_title_w;
  const int sink_fund_dates_base_h = sink_fund_dates_title_h;
  const int sink_fund_dates_base_d = sink_fund_dates_title_d;
  const int sink_fund_dates_base_len = sink_fund_dates_title_len;

  const int sink_fund_price_base_x = sink_fund_price_title_x;
  const int sink_fund_price_base_y = sink_fund_price_title_y + whole_row_adjust;
  const int sink_fund_price_base_w = sink_fund_price_title_w;
  const int sink_fund_price_base_h = sink_fund_price_title_h;
  const int sink_fund_price_base_d = sink_fund_price_title_d;
  const int sink_fund_price_base_len = sink_fund_price_title_len;

  const int sink_fund_dates_x[max_sink_fund] = {col_one_left,
							col_one_left,
							col_one_left,
							col_one_left,
							col_one_left
							};
  const int sink_fund_dates_y[max_sink_fund] = {row_five_top,
							row_six_top,
							row_seven_top,
							row_eight_top,
							row_nine_top
							};
  const int sink_fund_dates_w[max_sink_fund] = {col_one_width,
							col_one_width,
							col_one_width,
							col_one_width,
							col_one_width
							};
  const int sink_fund_dates_h[max_sink_fund] = {standard_row_height,
							standard_row_height,
							standard_row_height,
							standard_row_height,
							standard_row_height
							};
  const int sink_fund_dates_len[max_sink_fund] = {standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len
						};

  const int sink_fund_price_x[max_sink_fund] = {col_two_left,
							col_two_left,
							col_two_left,
							col_two_left,
							col_two_left
							};
  const int sink_fund_price_y[max_sink_fund] = {row_five_top,
							row_six_top,
							row_seven_top,
							row_eight_top,
							row_nine_top
							};
  const int sink_fund_price_w[max_sink_fund] = {col_two_width,
							col_two_width,
							col_two_width,
							col_two_width,
							col_two_width
							};
  const int sink_fund_price_h[max_sink_fund] = {standard_row_height,
							standard_row_height,
							standard_row_height,
							standard_row_height,
					      standard_row_height
							};
  const int sink_fund_price_len[max_sink_fund] = {standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len,
						standard_prompt_len
						};


  const int sf_accept_x = col_three_left;
  const int sf_accept_y = row_one_top;
  const int sf_accept_w = col_three_width;
  const int sf_accept_h = standard_row_height;
  const int sf_accept_d = col_three_height;
  const int sf_accept_len = standard_prompt_len;

  const int sf_clear_x = col_three_left;
  const int sf_clear_y = row_two_top;
  const int sf_clear_w = col_three_width;
  const int sf_clear_h = standard_row_height;
  const int sf_clear_d = col_three_height;
  const int sf_clear_len = standard_prompt_len;

  const int sf_close_x = col_three_left;
  const int sf_close_y = row_three_top;
  const int sf_close_w = col_three_width;
  const int sf_close_h = standard_row_height;
  const int sf_close_d = col_three_height;
  const int sf_close_len = standard_prompt_len;
/////////////////////////////////////////////////////////////////////////////
// CBondCalcWnd frame

class CBondCalcWnd : public CMDIChildWnd,							
							public	Py_Front 
{
	DECLARE_DYNCREATE(CBondCalcWnd)
public:
	CBondCalcWnd();        
//	virtual BOOL OnCreate();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBondCalcWnd)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
//	Miscellaneous
	int active_type;
	int Calc_type;
	int FRN_type;
	int BS_CHECKED;
	int BS_UNCHECKED;
	int element_count;
	char current_calc_what;
	unsigned int return_status;
	Py_Front pyfront;	
	RECT	Rect1;
	int dummy_int;
	long double	dummy_long_double;
	char date_hold[11];
	char date_msg[80];
	size_t dummy_size_t;
	char *str_ptr;
	char pay_type_control;
	long interest_days_parm;
	long double interest_parm;
	double interest_double;
	int price_places;
	long double	dirt_price;
	long double	nominal_adj_parm;
//	Indices for the list boxes
	char class_number;
	int day_count_number;
	int pay_freq_number;
	int yield_days_number;
	int yield_freq_number;
	int yield_meth_number;
	int month_end_number;
	int excoup_number;
//	String holders for the list boxes
	char class_desc_hold [instr_class_desc_len];
	char day_count_hold [day_count_names_len];
	char pay_freq_hold [freq_names_len];
	char yielddays_name_hold [day_count_names_len];
	char yieldmeth_name_hold [yield_names_len];
	char yieldfreq_name_hold [freq_names_len];
	char month_end_hold [monthend_names_len];
	char excoup_name_hold[excoup_name_length];
	char work_str[33];
//	Controls
	CStatic	instr_class_prompt;
    CComboBox instr_class;
	CStatic interest_rate_prompt;
	CEdit interest_rate;
	CStatic value_date_prompt;
	CEdit value_date;
	CStatic previous_coup_prompt;
	CStatic previous_coup;
	CStatic next_coup_prompt;
	CStatic next_coup;
	CStatic clean_price_prompt;
	CEdit clean_price;
    CStatic accrued_interest_prompt;	
	CStatic accrued_interest;	
	CStatic dirty_price_prompt;
	CStatic dirty_price;
	CStatic yield_discount_prompt;
	CEdit yield_discount;
	CStatic maturity_date_prompt;
	CEdit maturity_date;
	CStatic issue_date_prompt;
	CEdit issue_date;
	CStatic first_pay_prompt;
	CEdit first_pay;	
	CStatic penult_pay_prompt;
	CEdit penult_pay;
	CStatic ex_coup_prompt;
	CStatic ex_coup;
	CStatic int_days_prompt;
	CStatic int_days;
 	CStatic	yield_meth_prompt;
    CComboBox yield_meth;
	CStatic date_format_prompt;	
	CButton def_date;
	CStatic yield_days_prompt;
    CComboBox yield_days;
	CStatic yield_freq_prompt;
    CComboBox yield_freq;
	CStatic duration_prompt;
	CStatic duration;
	CStatic mod_duration_prompt;
	CStatic mod_duration;
	CStatic convexity_prompt;
	CStatic convexity;
	CStatic pvbp_prompt;
	CStatic pvbp;
	CStatic day_count_prompt;
	CComboBox day_count;
    CStatic pay_freq_prompt;
	CComboBox pay_freq;
    CStatic monthend_prompt;
	CComboBox monthend;
    CStatic excoup_prompt;
	CComboBox excoup;
    CButton calc_choice;
    CButton y_from_p;
    CButton p_from_y;
    CButton calculate;
//	Member Functions
	void InitInstrClass();
    void InitInterestRate();
    void InitValueDate();
    void InitPreviousCoup();
    void InitNextCoup();
    void InitCleanPrice();
    void InitAccruedInterest();
    void InitDirtyPrice();
    void InitYieldDiscount();
    void InitMaturityDate();
    void InitDefDate();    
	void InitIssueDate();	
	void InitFirstPay();
	void InitPenultPay();
	void InitExCoup();
	void InitIntDays();	
	void InitYieldMeth();
	void InitCalcChoice();
	void InitCalculate();
    void InitYieldDays();
    void InitYieldFreq();
    void InitDuration();
    void InitModDuration();
    void InitConvexity();
    void InitPVBP();
    void InitDayCount();
    void InitPayFreq();
    void InitMonthEnd();
    void InitExcoup();
    virtual ~CBondCalcWnd();
	void HandleInstrClass( );
	void HandlePayFreq( );
	void HandleDayCount( );
	void HandleYieldFreq( );
	void HandleYieldDays( );
	void HandleYieldMeth( );	
	void HandleCalcBox( );
	void HandleCalculate( );
	void HandleMonthEnd( );
	void HandleExcoup( );
	void HandleDefDates( );
    void InitDateHold(char *, int);
	unsigned long CheckDates(  );
	// Generated message map functions
	//{{AFX_MSG(CBondCalcWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BONDCALCWND_H__F25D7041_5A6D_11D1_8F5B_444553540000__INCLUDED_)
