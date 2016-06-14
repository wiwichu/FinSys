#ifndef __posproc_H
#ifndef __datedec_H
#include <datedec.h>
#endif


/*
The following declarations are used in positions processing (posproc).

*/

const	char	pp_add_all_proc_what = 0;
/*{ pp_add_all_proc_what adds all the passed data.}*/
const	char	pp_void_all_proc_what = 1;
/*{ pp_void_all_proc_what voids all the passed data.}*/
const	char	pp_add_all_trade_proc_what = 2;
/*{ pp_add_all_trade_proc_what adds all the passed trades.}*/
const	char	pp_void_all_trade_proc_what = 3;
/*{ pp_void_all_trade_proc_what voids all the passed trades.}*/
const	char	pp_add_all_events_proc_what = 4;
/*{ pp_add_all_events_proc_what adds all the passed security events.}*/
const	char	pp_void_all_events_proc_what = 5;
/*{ pp_void_all_events_proc_what voids all the passed security events.}*/
const	char	pp_add_all_pool_proc_what = 6;
/*{ pp_add_all_pool_proc_what adds all the passed pool factors.}*/
const	char	pp_void_all_pool_proc_what = 7;
/*{ pp_void_all_pool_proc_what voids all the passed pool factors.}*/
const	char	pp_add_all_rerate_proc_what = 8;
/*{ pp_add_all_rerate_proc_what adds all the passed rerates.}*/
const	char	pp_void_all_rerate_proc_what = 9;
/*{ pp_void_all_rerate_proc_what voids all the passed rerates.}*/
const	char	pp_add_spec_trade_proc_what = 10;
/*{ pp_add_spec_trade_proc_what adds the specified trade.}*/
const	char	pp_void_spec_trade_proc_what = 11;
/*{ pp_void_spec_trade_proc_what voids the specified trade.}*/
const	char	pp_add_spec_pool_proc_what = 12;
/*{ pp_add_spec_pool_proc_what adds the specified pool factor.}*/
const	char	pp_void_spec_pool_proc_what = 13;
/*{ pp_void_spec_pool_proc_what voids the specified pool factor.}*/
const	char	pp_add_spec_rerate_proc_what = 14;
/*{ pp_add_spec_rerate_proc_what adds the specified rerate.}*/
const	char	pp_void_spec_rerate_proc_what = 15;
/*{ pp_void_spec_rerate_proc_what voids the specified rerate.}*/
const	char	pp_mm_proc_what = 16;
/*{ pp_mm_proc_what marks the passed position to market by reversing old market price and using new one.}*/
const	char	pp_void_mm_proc_what = 17;
/*{ pp_void_mm_proc_what voids the passed position's mark to market.}*/
const	char	pp_add_accr_amort_proc_what = 18;
/*{ pp_add_accr_amort_proc_what adds accruals and amortizations on the position
from the start date to the end date.}*/
const	char	pp_void_accr_amort_proc_what = 19;
/*{ pp_void_accr_amort_proc_what voids accruals and amortizations on the position
from the start date to the end date.}*/
const	char	pp_add_accr_proc_what = 20;
/*{ pp_add_accr_proc_what adds accruals on the position
from the start date to the end date.}*/
const	char	pp_void_accr_proc_what = 21;
/*{ pp_void_accr_proc_what voids accruals on the position
from the start date to the end date.}*/
const	char	pp_add_amort_proc_what = 22;
/*{ pp_add_amort_proc_what adds amortizations on the position
from the start date to the end date.}*/
const	char	pp_void_amort_proc_what = 23;
/*{ pp_void_amort_proc_what voids amortizations on the position
from the start date to the end date.}*/

const	char	pp_val_val_trade = 0;
/*{ pp_val_val_trade indicates value dated accounting.}*/
const	char	pp_trade_val_trade = 1;
/*{ pp_val_val_trade indicates trade dated accounting.}*/

const	char	pp_wat_pl = 0;
/*{ pp_wat_pl indicates P & L is determined by weighted average trade order.}*/
const	char	pp_was_pl = 1;
/*{ pp_was_pl indicates P & L is determined by weighted average trade summary.}*/
const	char	pp_pair_pl = 2;
/*{ pp_pair_pl indicates P & L is determined by pairing trades.}*/

const	char	pp_noamort_reval = 0;
/*{ pp_noamort_reval indicates no amortization occurs.}*/
const	char	pp_amort_reval = 1;
/*{ pp_noamort_reval indicates amortization occurs.}*/
const	char	pp_mm_reval = 2;
/*{ pp_mm_reval indicates mark to market revaluation occurs.}*/

const	char	pp_pur_trade_type = 0;
/*{ pp_pur_trade_type indicates a purchase.}*/
const	char	pp_sal_trade_type = 1;
/*{ pp_sal_trade_type indicates a sale.}*/

const	char	pp_yes_flat = 0;
/*{ pp_yes_flat indicates a flat trade.}*/
const	char	pp_no_flat = 1;
/*{ pp_no_flat indicates not a flat trade.}*/

typedef struct trade_pos{ date_union 	value_date;
                       /* value date for this trade, or for a position, today's date.*/
		       unsigned long 	trade_num;
                       /* number for this trade, or for a position represents the number of trades in the array. */
		       char		trade_type;
		       /* must be one of the pp_xxx_trade_type symbols. */
		       long double	nominal;
		       /* nominal for this trade, or nominal of the position. */
		       long double	int_nominal;
		       /* interest nominal for this position. */
		       long double	price;
		       /* price of this trade, or price of the position. */
		       char		flat;
                       /* indicates whether this is a flat trade. Must be one of the pp_xxx_flat symbols. */
		       long double	accr_int;
                       /* accrued interest on the trade */
		       long double	net;
		       /* net amount for trade (principal plus accrued interest).*/
		       long double	tr_pl;
		       /* trading P & L from trade.*/
		       long double	pre_nominal;
		       /* nominal amount before this trade.*/
		       long double	pre_int_nominal;
		       /* interest nominal amount before this trade.*/
		       long double	pre_price;
		       /* position price before this trade.*/
		       long double	pre_tr_pl;
		       /* P & L before this trade.*/
		       }
	       trade_pos;	

typedef struct pp_rules{ char		proc_what;
			 date_union 	start_date;
			 date_union 	end_date;
		       }
	       pp_rules;	

typedef struct acc_book{
			long double cash;
			long double sec_asset;
			long double sec_liab;
			long double prem_disc;
			long double prem_disc_pl;
			long double prem_disc_short;
			long double prem_disc_pl_short;
			long double int_inc;
			long double int_inc_flat;
			long double int_rec;
			long double int_exp;
			long double int_exp_flat;
			long double int_pay;
			long double trade_pl;
			long double redemp_pl;
			long double unreal_pl;
			long double counter_unreal_pl;
			long double unreal_pl_short;
			long double counter_unreal_pl_short;
			long double forw_debit;
			long double forw_credit;
			long double contingent;
			long double counter_contingent;
			long double contingent_short;
			long double counter_contingent_short;
		       }
	       acc_book;	


unsigned long posproc(  instr,
			trade_pos [],
			pp_rules,
			holidays_struct [],
			acc_book *,
			insevent_struct [],
			insevent_struct [],
			insevent_struct [],
			insevent_struct [],
			insevent_struct [],
			insevent_struct [],
			insevent_struct [],
			insevent_struct [] 
			);

#endif