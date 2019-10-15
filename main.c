#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


// Global Variables
volatile char slow_input_down;
extern char display_line[DISPLAY_HEIGHT][DISPLAY_LENGTH];
extern char *display[DISP_PTR];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
volatile unsigned int Time_Sequence;
volatile char one_time;
extern unsigned int test_value;
char chosen_direction;
char change;
extern int sw1_p;
extern int sw2_p;
extern volatile int wait_200;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD

  //The first state is a pause state so the display needs to be set to pause
  strcpy(display_line[DISP_ENTRY_1], "   PAUSE   ");
  update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
  enable_display_update();
  display_changed = ALWAYS;

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {    
    Display_Process();
    //wait_200 is the variable incremented in Timer0_B0_ISR used to control what state the car is in
    switch(wait_200)
    {
      //First Pause
      case F_PAUSE: 
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
      //First Forward
      case F_FORWARD:
        RIGHT_FORWARD_SPEED = RIGHT_S;
        LEFT_FORWARD_SPEED = LEFT_S;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        strcpy(display_line[DISP_ENTRY_1], "     FOR   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      //Second Pause 
      case S_PAUSE:
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        strcpy(display_line[DISP_ENTRY_1], "   PAUSE   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      case F_REVERSE:
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = RIGHT_R;
        LEFT_REVERSE_SPEED = LEFT_R;
        strcpy(display_line[DISP_ENTRY_1], "     REV   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      case T_PAUSE:
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        strcpy(display_line[DISP_ENTRY_1], "   PAUSE   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      case S_FORWARD:
        RIGHT_FORWARD_SPEED = RIGHT_S;
        LEFT_FORWARD_SPEED = LEFT_S;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        strcpy(display_line[DISP_ENTRY_1], "   FOR   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      case FOURTH_PAUSE:
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        strcpy(display_line[DISP_ENTRY_1], "   PAUSE   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      case COUNTER:
        RIGHT_FORWARD_SPEED = CLOCK;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = CLOCK;
        strcpy(display_line[DISP_ENTRY_1], "  COUNTER  ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      case FIFTH_PAUSE:
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        strcpy(display_line[DISP_ENTRY_1], "   PAUSE   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      case CLOCKWISE:
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = CLOCK;
        RIGHT_REVERSE_SPEED = CLOCK;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        strcpy(display_line[DISP_ENTRY_1], "   CLOCK   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      case FINAL_PAUSE:
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        strcpy(display_line[DISP_ENTRY_1], "   PAUSE   ");
        update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
        display_changed = ALWAYS;
        break;
      default: 
        break;
    }
  }
}