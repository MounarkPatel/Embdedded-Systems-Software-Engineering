#include  "macros.h"
#include  "functions.h"
#include  "msp430.h"

extern char display_line[DISPLAY_HEIGHT][DISPLAY_LENGTH];
extern char *display[DISP_PTR];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=COUNT_INIT;i<DISPLAY_LENGTH;i++){
    display_line[DISP_ENTRY_1][i] = RESET_STATE;
    display_line[DISP_ENTRY_2][i] = RESET_STATE;
    display_line[DISP_ENTRY_3][i] = RESET_STATE;
    display_line[DISP_ENTRY_4][i] = RESET_STATE;
  }
  display_line[DISP_ENTRY_1][DISP_LENGTH_END] = RESET_STATE;
  display_line[DISP_ENTRY_2][DISP_LENGTH_END] = RESET_STATE;
  display_line[DISP_ENTRY_3][DISP_LENGTH_END] = RESET_STATE;
  display_line[DISP_ENTRY_4][DISP_LENGTH_END] = RESET_STATE;

  display[DISP_ENTRY_1] = &display_line[DISP_ENTRY_1][DISP_ENTRY_START];
  display[DISP_ENTRY_2] = &display_line[DISP_ENTRY_2][DISP_ENTRY_START];
  display[DISP_ENTRY_3] = &display_line[DISP_ENTRY_3][DISP_ENTRY_START];
  display[DISP_ENTRY_4] = &display_line[DISP_ENTRY_4][DISP_ENTRY_START];
  update_display = RESET_STATE;
  update_display_count = RESET_STATE;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}