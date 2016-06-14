#ifndef __guiconst_H
#define __guiconst_H

  const int standard_input_scr_height = 320;
  const int standard_input_width = 140;

  const int standard_row_height = 26;
  const int standard_row_space = 5;

  const int standard_col_space = 10;

  const int standard_prompt_len = 40;
  const int standard_prompt_adjust = 5;
  const int standard_prompt_width = 130;

  const int col_one_left = 20;
  const int col_one_width = standard_prompt_width;
  const int col_one_right = col_one_left + col_one_width;
  const int col_one_height = standard_row_height - standard_prompt_adjust;

  const int col_two_left = col_one_right + standard_col_space;
  const int col_two_width = standard_input_width;
  const int col_two_right = col_two_left + col_two_width;
  const int col_two_height = standard_row_height;
  const int col_two_scr_height = standard_input_scr_height;

  const int col_three_left = col_two_right + standard_col_space;
  const int col_three_width = standard_prompt_width;
  const int col_three_right = col_three_left + col_three_width;
  const int col_three_height = standard_row_height - standard_prompt_adjust;

  const int col_four_left = col_three_right + standard_col_space;
  const int col_four_width = standard_input_width;
  const int col_four_right = col_four_left + col_four_width;
  const int col_four_height = standard_row_height;
  const int col_four_scr_height = standard_input_scr_height;

  const int col_five_left = col_four_right + standard_col_space;
  const int col_five_width = standard_input_width;
  const int col_five_right = col_five_left + col_five_width;
  const int col_five_height = standard_row_height;
  const int col_five_scr_height = standard_input_scr_height;

  const int row_one_top = 20;
  const int row_one_bot = row_one_top + standard_row_height;

  const int row_two_top = row_one_bot + standard_row_space;
  const int row_two_bot = row_two_top + standard_row_height;

  const int row_three_top = row_two_bot + standard_row_space;
  const int row_three_bot = row_three_top + standard_row_height;

  const int row_four_top = row_three_bot + standard_row_space;
  const int row_four_bot = row_four_top + standard_row_height;

  const int row_five_top = row_four_bot + standard_row_space;
  const int row_five_bot = row_five_top + standard_row_height;

  const int row_six_top = row_five_bot + standard_row_space;
  const int row_six_bot = row_six_top + standard_row_height;

  const int row_seven_top = row_six_bot + standard_row_space;
  const int row_seven_bot = row_seven_top + standard_row_height;

  const int row_eight_top = row_seven_bot + standard_row_space;
  const int row_eight_bot = row_eight_top + standard_row_height;

  const int row_nine_top = row_eight_bot + standard_row_space;
  const int row_nine_bot = row_nine_top + standard_row_height;

  const int row_ten_top = row_nine_bot + standard_row_space;
  const int row_ten_bot = row_ten_top + standard_row_height;

  const int row_eleven_top = row_ten_bot + standard_row_space;
  const int row_eleven_bot = row_eleven_top + standard_row_height;

  const int row_twelve_top = row_eleven_bot + standard_row_space;
  const int row_twelve_bot = row_twelve_top + standard_row_height;

  const int row_thirteen_top = row_twelve_bot + standard_row_space;
  const int row_thirteen_bot = row_thirteen_top + standard_row_height;

  const int row_fourteen_top = row_thirteen_bot + standard_row_space;
  const int row_fourteen_bot = row_fourteen_top + standard_row_height;

  const int row_fifteen_top = row_fourteen_bot + standard_row_space;
  const int row_fifteen_bot = row_fifteen_top + standard_row_height;

  const int row_sixteen_top = row_fifteen_bot + standard_row_space;
  const int row_sixteen_bot = row_sixteen_top + standard_row_height;

  const int whole_row_adjust = standard_row_space + standard_row_height;

  const DWORD prompt_style = SS_LEFT | WS_CHILD | WS_VISIBLE | WS_TABSTOP;
  const DWORD combo_style = CBS_DROPDOWNLIST| WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL;
  const DWORD edit_style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER;
  const DWORD button_style = WS_CHILD | WS_VISIBLE | WS_TABSTOP;
  const DWORD group_box_style = BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_TABSTOP; 
  const DWORD radiobutton_style = BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP ; 

#endif