#if !defined(AFX_HOLIDAYS_H__EB260CE1_6CA8_11D1_8F5B_444553540000__INCLUDED_)
#define AFX_HOLIDAYS_H__EB260CE1_6CA8_11D1_8F5B_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//#include "holihead.h"
#include "datdec.h"
#include "guidecs.h"
//#include "db.h"
// Holidays.h : header file
//
const int ID_Holiday_Code	=	400;
const int ID_Holiday_Base	=	401;
const int ID_Holiday_Base_Month	=	402;
const int ID_Holiday_Base_Day	=	403;
const int ID_Holiday_Base_Year	=	404;
const int ID_Holiday_Base_Adjust	=	405;
const int ID_Holiday_Base_Adjust_Times	=	406;
const int ID_Holiday_Adjust_Times	=	407;
const int ID_Holiday_Day	=	408;
const int ID_Holiday_Adjust_Direction	=	409;
const int ID_Holiday_Day_Adjust_Times	=	410;
const int ID_Holiday_Base_Weekday	=	411;
const int ID_Holiday_Add	=	412;
const int ID_Holiday_Delete	=	413;
const int ID_Holiday_Test_Date	=	414;
const int ID_Holiday_Test	=	415;
const int ID_Holiday_Designate	=	416;

// Begin Holidays


  const int holiday_code_prompt_x = col_one_left;
  const int holiday_code_prompt_y = row_one_top + standard_prompt_adjust;
  const int holiday_code_prompt_w = col_one_width;
  const int holiday_code_prompt_h = col_one_height;
  const int holiday_code_prompt_len = standard_prompt_len;

  const int holiday_code_x = col_two_left;
  const int holiday_code_y = row_one_top;
  const int holiday_code_w = col_two_width;
  const int holiday_code_h = col_two_height;
  const int holiday_code_len = standard_prompt_len;

  const int holiday_base_prompt_x = col_one_left;
  const int holiday_base_prompt_y = row_two_top + standard_prompt_adjust;
  const int holiday_base_prompt_w = col_one_width;
  const int holiday_base_prompt_h = col_one_height;
  const int holiday_base_prompt_len = standard_prompt_len;

  const int holiday_base_x = col_two_left;
  const int holiday_base_y = row_two_top;
  const int holiday_base_w = col_two_width;
  const int holiday_base_h = col_two_scr_height;
  const int holiday_base_d = col_two_height;

  const int holiday_base_month_prompt_x = col_one_left;
  const int holiday_base_month_prompt_y = row_three_top + standard_prompt_adjust;
  const int holiday_base_month_prompt_w = col_one_width;
  const int holiday_base_month_prompt_h = col_one_height;
  const int holiday_base_month_prompt_len = standard_prompt_len;

  const int holiday_base_month_x = col_two_left;
  const int holiday_base_month_y = row_three_top;
  const int holiday_base_month_w = col_two_width;
  const int holiday_base_month_h = col_two_scr_height;
  const int holiday_base_month_d = col_two_height;

  const int holiday_base_day_prompt_x = col_one_left;
  const int holiday_base_day_prompt_y = row_four_top + standard_prompt_adjust;
  const int holiday_base_day_prompt_w = col_one_width;
  const int holiday_base_day_prompt_h = col_one_height;
  const int holiday_base_day_prompt_len = standard_prompt_len;

  const int holiday_base_day_x = col_two_left;
  const int holiday_base_day_y = row_four_top;
  const int holiday_base_day_w = col_two_width;
  const int holiday_base_day_h = col_two_scr_height;
  const int holiday_base_day_d = col_two_height;

  const int holiday_base_year_prompt_x = col_one_left;
  const int holiday_base_year_prompt_y = row_five_top + standard_prompt_adjust;
  const int holiday_base_year_prompt_w = col_one_width;
  const int holiday_base_year_prompt_h = col_one_height;
  const int holiday_base_year_prompt_len = standard_prompt_len;

  const int holiday_base_year_x = col_two_left;
  const int holiday_base_year_y = row_five_top;
  const int holiday_base_year_w = col_two_width;
  const int holiday_base_year_h = col_two_height;
  const int holiday_base_year_len = standard_prompt_len;

  const int holiday_base_adjust_prompt_x = col_one_left;
  const int holiday_base_adjust_prompt_y = row_six_top + standard_prompt_adjust;
  const int holiday_base_adjust_prompt_w = col_one_width;
  const int holiday_base_adjust_prompt_h = col_one_height;
  const int holiday_base_adjust_prompt_len = standard_prompt_len;

  const int holiday_base_adjust_x = col_two_left;
  const int holiday_base_adjust_y = row_six_top;
  const int holiday_base_adjust_w = col_two_width;
  const int holiday_base_adjust_h = col_two_scr_height;
  const int holiday_base_adjust_d = col_two_height;

  const int holiday_base_adjust_times_prompt_x = col_one_left;
  const int holiday_base_adjust_times_prompt_y = row_seven_top + standard_prompt_adjust;
  const int holiday_base_adjust_times_prompt_w = col_one_width;
  const int holiday_base_adjust_times_prompt_h = col_one_height;
  const int holiday_base_adjust_times_prompt_len = standard_prompt_len;

  const int holiday_base_adjust_times_x = col_two_left;
  const int holiday_base_adjust_times_y = row_seven_top;
  const int holiday_base_adjust_times_w = col_two_width;
  const int holiday_base_adjust_times_h = col_two_scr_height;
  const int holiday_base_adjust_times_d = col_two_height;

  const int holiday_adjust_times_prompt_x = col_three_left;
  const int holiday_adjust_times_prompt_y = row_one_top + standard_prompt_adjust;
  const int holiday_adjust_times_prompt_w = col_three_width;
  const int holiday_adjust_times_prompt_h = col_three_height;
  const int holiday_adjust_times_prompt_len = standard_prompt_len;

  const int holiday_adjust_times_x = col_four_left;
  const int holiday_adjust_times_y = row_one_top;
  const int holiday_adjust_times_w = col_four_width;
  const int holiday_adjust_times_h = col_four_height;
  const int holiday_adjust_times_len = standard_prompt_len;

  const int holiday_day_prompt_x = col_three_left;
  const int holiday_day_prompt_y = row_two_top + standard_prompt_adjust;
  const int holiday_day_prompt_w = col_three_width;
  const int holiday_day_prompt_h = col_three_height;
  const int holiday_day_prompt_len = standard_prompt_len;

  const int holiday_day_x = col_four_left;
  const int holiday_day_y = row_two_top;
  const int holiday_day_w = col_four_width;
  const int holiday_day_h = col_four_scr_height;
  const int holiday_day_d = col_four_height;

  const int holiday_adjust_direction_prompt_x = col_three_left;
  const int holiday_adjust_direction_prompt_y = row_three_top + standard_prompt_adjust;
  const int holiday_adjust_direction_prompt_w = col_three_width;
  const int holiday_adjust_direction_prompt_h = col_three_height;
  const int holiday_adjust_direction_prompt_len = standard_prompt_len;

  const int holiday_adjust_direction_x = col_four_left;
  const int holiday_adjust_direction_y = row_three_top;
  const int holiday_adjust_direction_w = col_four_width;
  const int holiday_adjust_direction_h = col_four_scr_height;
  const int holiday_adjust_direction_d = col_four_height;

  const int holiday_day_adjust_times_prompt_x = col_three_left;
  const int holiday_day_adjust_times_prompt_y = row_four_top + standard_prompt_adjust;
  const int holiday_day_adjust_times_prompt_w = col_three_width;
  const int holiday_day_adjust_times_prompt_h = col_three_height;
  const int holiday_day_adjust_times_prompt_len = standard_prompt_len;

  const int holiday_day_adjust_times_x = col_four_left;
  const int holiday_day_adjust_times_y = row_four_top;
  const int holiday_day_adjust_times_w = col_four_width;
  const int holiday_day_adjust_times_h = col_four_scr_height;
  const int holiday_day_adjust_times_d = col_four_height;

  const int holiday_base_weekday_prompt_x = col_three_left;
  const int holiday_base_weekday_prompt_y = row_five_top + standard_prompt_adjust;
  const int holiday_base_weekday_prompt_w = col_three_width;
  const int holiday_base_weekday_prompt_h = col_three_height;
  const int holiday_base_weekday_prompt_len = standard_prompt_len;

  const int holiday_base_weekday_x = col_four_left;
  const int holiday_base_weekday_y = row_five_top;
  const int holiday_base_weekday_w = col_four_width;
  const int holiday_base_weekday_h = col_four_scr_height;
  const int holiday_base_weekday_d = col_four_height;

  const int holiday_designate_prompt_x = col_three_left;
  const int holiday_designate_prompt_y = row_six_top + standard_prompt_adjust;
  const int holiday_designate_prompt_w = col_three_width;
  const int holiday_designate_prompt_h = col_three_height;
  const int holiday_designate_prompt_len = standard_prompt_len;

  const int holiday_designate_x = col_four_left;
  const int holiday_designate_y = row_six_top;
  const int holiday_designate_w = col_four_width;
  const int holiday_designate_h = col_four_scr_height;
  const int holiday_designate_d = col_four_height;

  const int holiday_add_x = col_five_left + 5;
  const int holiday_add_y = row_one_top;
  const int holiday_add_w = col_five_width - 5;
  const int holiday_add_h = col_five_height;
  const int holiday_add_d = col_five_height;
  const int holiday_add_len = standard_prompt_len;

  const int holiday_delete_x = col_five_left + 5;
  const int holiday_delete_y = row_two_top;
  const int holiday_delete_w = col_five_width - 5;
  const int holiday_delete_h = col_five_height;
  const int holiday_delete_d = col_five_height;
  const int holiday_delete_len = standard_prompt_len;

  const int holiday_test_date_prompt_x = col_three_left;
  const int holiday_test_date_prompt_y = row_seven_top + standard_prompt_adjust;
  const int holiday_test_date_prompt_w = col_three_width;
  const int holiday_test_date_prompt_h = col_three_height;
  const int holiday_test_date_prompt_len = standard_prompt_len;

  const int holiday_test_date_x = col_four_left;
  const int holiday_test_date_y = row_seven_top;
  const int holiday_test_date_w = col_four_width;
  const int holiday_test_date_h = col_four_height;
  const int holiday_test_date_len = standard_prompt_len;

  const int holiday_test_x = col_five_left + 5;
  const int holiday_test_y = row_seven_top;
  const int holiday_test_w = col_five_width - 5;
  const int holiday_test_h = col_five_height;
  const int holiday_test_d = col_five_height;
  const int holiday_test_len = standard_prompt_len;

// End Holidays

/////////////////////////////////////////////////////////////////////////////
// CHolidays frame

class CHolidays : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CHolidays)
public:
	CHolidays();           
//	CHolidays(CDB *);           

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHolidays)
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
//	Miscellaneous
	RECT	Rect1;
	Py_Front pyfront;
	holidays_class holidaysclass;
	int element_count;
	unsigned long return_status;
	char hold_msg[80];
	char date_hold[11];
	CDB * DB_1;
//	Elements for Controls
    char holidaybasehold [holidaybaselength];
    char currentbase;
	char monthhold [month_names_length];
	char currentmonth;
	char dayhold [holidaybasedaylength];
	char currentday;
	char baseadjhold [holidaybaseadjlength];
	char currentbaseadj;
	char baseadjtimeshold [holidaybaseadjtimeslength];
	char currentbaseadjtimes;
	char holidayweekdayhold [holidayweekdaylength];
	char currentholidayweekday;
	char adjustdirectionhold [adjustdirectionlength];
	char currentadjustdirection;
	char dayadjusthold [dayadjustlength];
	char currentdayadjust;
	char baseweekdayhold [baseweekdaylength];
	char currentbaseweekday;
	char currentdesignate;
	char dummy_char;
	char holiday_code_hold [holidaycodelength];
	char holiday_adj_times_hold [holidayadjtimeslength];
	char holiday_day_hold [holidayweekdaylength];
	char holiday_year_hold [holidayyearlength];
	char designate_hold [designatelength];
//	Members for the controls
	CStatic holiday_code_prompt;
	CEdit holiday_code;
	CStatic holiday_base_adjust_times_prompt;
	CComboBox holiday_base_adjust_times;
	CStatic holiday_base_prompt;
	CComboBox holiday_base;
	CStatic holiday_base_month_prompt;
	CComboBox holiday_base_month;
	CStatic holiday_base_day_prompt;
	CComboBox holiday_base_day;
	CStatic holiday_base_year_prompt;
	CEdit holiday_base_year;
	CStatic holiday_base_adjust_prompt;
	CComboBox holiday_base_adjust;
	CStatic holiday_adjust_times_prompt;
	CEdit holiday_adjust_times;
	CStatic holiday_day_prompt;
	CComboBox holiday_day;
	CStatic holiday_adjust_direction_prompt;
	CComboBox holiday_adjust_direction;
	CStatic holiday_day_adjust_times_prompt;
	CComboBox holiday_day_adjust_times;
	CStatic holiday_base_weekday_prompt;
	CComboBox holiday_base_weekday;
	CStatic holiday_designate_prompt;
	CComboBox holiday_designate;
	CStatic holiday_test_date_prompt;
	CEdit holiday_test_date;
    CButton holiday_add;
    CButton holiday_delete;
    CButton holiday_test;
 	void InitDB();
	void InitHolidayCode();
	void InitHolidayBase();
	void InitHolidayBaseMonth();
	void InitHolidayBaseDay();
	void InitHolidayBaseYear();
	void InitHolidayBaseAdjust();
	void InitHolidayBaseAdjustTimes();
	void InitHolidayAdjustTimes();
	void InitHolidayDay();
	void InitHolidayAdjustDirection();
	void InitDayAdjust();
	void InitBaseWeekday();
	void InitDesignate();
	void InitTestDate();
	void InitAdd();
	void InitDelete();
	void InitTest();
	virtual ~CHolidays();

	void HandleHolidayBase(  );
	void HandleHolidayBaseMonth(  );
	void HandleHolidayBaseDay(  );
	void HandleHolidayBaseAdjust(  );
	void HandleHolidayBaseAdjustTimes(  );
	void HandleHolidayAdjustTimes(  );
	void HandleHolidayWeekday(  );
	void HandleHolidayAdjustDirection(  );
	void HandleHolidayDayAdjustTimes(  );
	void HandleHolidayBaseWeekday(  );
	void HandleDesignate(  );
	void HandleHolidayAdd(  );
	void HandleHolidayDelete(  );
	void HandleHolidayTest(  );

	// Generated message map functions
	//{{AFX_MSG(CHolidays)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOLIDAYS_H__EB260CE1_6CA8_11D1_8F5B_444553540000__INCLUDED_)
