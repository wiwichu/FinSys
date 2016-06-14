#ifndef __fradecs_H
#define __fradecs_H
#ifndef __datedec_H
#include <datedec.h>
#endif

const	unsigned char	fraterm_min = 1;
/*{fraterm_min is the smallest value for the fra start month.}*/

const	unsigned char	fraterm_max = 12;
/*{fraterm_max is the highest value for the fra start month.}*/

const	unsigned char	fra_spot = mm_spot;
/*{fra_spot is the default spot days for an FRA.}*/

const	unsigned char	fra_holi_adj = mm_holi_adj;
/*{fra_holi_adj is the default holiday adjust for an FRA.}*/

const	unsigned char	fra_entered_rate_source = 0;
/*{fra_entered_rate_source means the FRA rate is manually entered.}*/

const	unsigned char	fra_cash_rate_source = 1;
/*{fra_cash_rate_source means the FRA rate is derived from cash.}*/

const	unsigned char	fra_futures_rate_source = 2;
/*{fra_futures_rate_source means the FRA rate is derived from futures.}*/

const	unsigned char	fra_last_rate_source = 3;
/*{fra_last_rate_source means the last rate source possibility.}*/

char *const rate_source_names[fra_last_rate_source] =
	    {"Entered","Cash","Futures"};

const	int	rate_source_names_len = 8;

const	unsigned char	fra_bid_ask_bid = 0;
/*{fra_bid_ask_bid means bid price.}*/

const	unsigned char	fra_bid_ask_ask = 1;
/*{fra_bid_ask_ask means ask price.}*/

const	unsigned char	fra_last_bid_ask = 2;
/*{fra_last_bid_ask means the last bid_ask possibility.}*/

char *const fra_bid_ask_names[fra_last_bid_ask] =
	    {"Bid","Ask"};

const	int	fra_bid_ask_names_len = 4;

const	unsigned char	fra_interpolation_exponential = 0;
/*{fra_interpolation_exponential means exponential interpolation.}*/

const	unsigned char	fra_interpolation_linear = 1;
/*{fra_interpolation_linear.}*/

const	unsigned char	fra_last_interpolation = 2;
/*{fra_last_interpolation means the last interpolation possibility.}*/

char *const fra_interpolation_names[fra_last_interpolation] =
	    {"Exponential","Linear"};

const	int	fra_interpolation_names_len = 12;

//const	unsigned char	fra_max_rates = 36;
const	unsigned char	fra_max_rates = 39;
/*{fra_max_futures means the rates possible.}*/

const	unsigned char	fra_max_cash = 30;
/*{fra_max_cash means the cash rates possible.}*/

const	unsigned char	fra_max_futures = 20;
/*{fra_max_futures means the futures rates possible.}*/

const	unsigned char	fra_cash_with_futures = 4;
/*{fra_cash_with_futures means the number of cash loaded with
futures rates.}*/

const	unsigned char	fra_currency_usd = 0;
/*{fra_currency_usd means USD.}*/

const	unsigned char	fra_currency_dem = 1;
/*{fra_currency_dem means DEM.}*/

const	unsigned char	fra_currency_gbp = 2;
/*{fra_currency_gbp means GBP.}*/

const	unsigned char	fra_currency_jpy = 3;
/*{fra_currency_jpy means JPY.}*/

const	unsigned char	fra_last_currency = 4;
/*{fra_last_currency means the last currency possibility.}*/

char *const fra_currency_names[fra_last_currency] =
	    {"USD","DEM","GBP","JPY"};

const	int	fra_currency_names_len = 4;


typedef struct fra_term
	{
	char start;
	char end;
	}
        fra_term;

typedef struct fraproc_parm
	{
	char start;
	char end;
	}
	fraproc_oarm;

unsigned int	fraproc	(char action,
	char day_count_choice [date_last_day_count] [day_count_names_len],
	char *current_day_count,
	char current_day_count_name [day_count_names_len],
	long double int_rate1,
	long double int_rate2,
	long double *settlement,
	long double nominal,
	date_union *mat_date_parm,
	date_union *sett_date_parm,
	instr *instr_parm,
	py_parms *pyparm,
	fra_term fraterm,
	date_union fra_deal_date,
	unsigned int holi_chan,
        holidays_struct holi_parm [],
	date_union *val_date_parm,
	date_union *fix_date_parm,
	char rate_source_choice [fra_last_rate_source] [rate_source_names_len],
	char *current_rate_source,
	char current_rate_source_name [rate_source_names_len],
	insevent_struct fw_rate_array [],
	insevent_struct fw_forward_array [],
	char fra_currency_choice [fra_last_currency] [fra_currency_names_len],
	char *current_currency,
	char current_currency_name [fra_currency_names_len],
	char fra_holiday_choice [fra_last_holiday] [fra_holiday_names_len],
	char *current_holiday,
	char current_holiday_name [fra_holiday_names_len],
	char fra_interpolation_choice [fra_last_interpolation] [fra_interpolation_names_len],
	char *current_interpolation,
	char current_interpolation_name [fra_interpolation_names_len],
	char fra_bid_ask_choice [fra_last_bid_ask] [fra_bid_ask_names_len],
	char *current_bid_ask,
	char current_bid_ask_name [fra_bid_ask_names_len],
        fraproc_parm extra_parms
	);

	const	unsigned char	rate_code_allcash_allfra = 0;
	/*{rate_code_allcash_allfra means all standard cash should be loaded
	and the standard FRA's calculated and loaded from cash.}*/

	const	unsigned char	rate_code_allfut_allfra = 1;
	/*{rate_code_allfut_allfra means all standard futures should be
	loaded and the standard FRA's calculated and loaded from cash.}*/

	const	unsigned char	rate_code_allcash = 2;
	/*{rate_code_allcash means all standard cash should be loaded.}*/

	const	unsigned char	rate_code_allfut = 3;
	/*{rate_code_allfut means all standard futures should be loaded.}*/

	const	unsigned char	rate_code_allfra_fromcash = 4;
	/*{rate_code_allfra_fromcash means all standard FRA's should be
	calculated from cash.}*/

	const	unsigned char	rate_code_allfra_fromfut = 5;
	/*{rate_code_allfra_fromfut means all standard FRA's should be
	calculated from futures.}*/

	const	unsigned char	rate_code_singlefra_fromcash = 6;
	/*{rate_code_singlefra_fromcash means a single FRA's should be
	calculated from cash.}*/

	const	unsigned char	rate_code_singlefra_fromfut = 7;
	/*{rate_code_singlefra_fromfut means a single FRA's should be
	calculated from futures.}*/

	unsigned long rateload(event_sched event_parm,
		insevent_struct sched_dates [],
		date_union start_date, date_union end_date,
		unsigned int holi_chan, holidays_struct holi_parm [],
		char pay_type, char rate_code, char rl_day_count,
		insevent_struct forward_dates [], char holiday_code[3],
		char interpolation_rule, char bid_ask_code);

	unsigned long ratetabl(event_sched event_parm, insevent_struct sched_dates [],
		date_union start_date, date_union end_date,
		unsigned int holi_chan, holidays_struct holi_parm [],
		char pay_type, char rate_code, char rl_day_count,
		insevent_struct forward_dates [], char holiday_code[3],
		char interpolation_rule);

	const	unsigned char	fut_base_month_usd = 3;
	/*{fut_base_month_usd means month base for USD futures.}*/

	const	unsigned char	fut_freq_usd = 3;
	/*{fut_freq_usd means frequency for USD futures.}*/

	const	unsigned char	fut_payday_usd = date_3wednes_day;
	/*{fut_payday_usd means payday for USD futures.}*/

/*
	unsigned long rateload2(event_sched event_parm, insevent_struct sched_dates [],
		date_union start_date, date_union end_date,
		unsigned int holi_chan, holidays_struct holi_parm [],
		char pay_type, char rate_code, char rl_day_count,
		insevent_struct forward_dates []);

*/
#endif