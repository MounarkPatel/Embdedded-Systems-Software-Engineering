#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"
#include <stdlib.h>
#include <stdio.h>



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

char enter = START;

extern volatile int UCA0_index;
extern volatile int UCA1_index;

extern volatile char IOT_Char_Rx[LARGE_RING_SIZE]; //Recive Buffer 
extern volatile char test_iot[P_BUFF_SIZE]; //Process Buffer
extern volatile char IOT_Char_Tx[P_BUFF_SIZE]; //Transmit Buffer

extern volatile int iot_rx_ring_rd; //Read Recive Ptr
extern volatile unsigned int iot_rx_ring_wr; //Write Recive Ptr

extern volatile int p1;
extern volatile int p2;
extern volatile int wait_2s;
extern volatile int delay;

extern volatile int w_F;
extern volatile int w_B;
extern volatile int w_R;
extern volatile int w_L;

int start = RESET_STATE;
int end = RESET_STATE;
int done = RESET_STATE;
int pptr = RESET_STATE; 
char numtime[4];

char keep_connection[] = "AT+WSYNCINTRL=63325\r";
char connect_to_port[] = "AT+NSTCP=2229,1\r";
char get_IP[] = "AT+NSTAT=?\r";

volatile int done_c = 0;
volatile int done_p = 0;
volatile int done_i = 0;
extern volatile int wait_c;
extern volatile int wait_p;
extern volatile int wait_i;
int waited_start = 0;
extern volatile char IP[16];
//char gang;
//int ready;


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
  strcpy(display_line[DISP_ENTRY_1], "          ");
  update_string(display_line[DISP_ENTRY_1], DISP_ENTRY_1);
  strcpy(display_line[DISP_ENTRY_2], "          ");
  update_string(display_line[DISP_ENTRY_2], DISP_ENTRY_2);
  strcpy(display_line[DISP_ENTRY_3], "          ");
  update_string(display_line[DISP_ENTRY_3], DISP_ENTRY_3);
  strcpy(display_line[DISP_ENTRY_4], "ARR      0");
  update_string(display_line[DISP_ENTRY_4], DISP_ENTRY_4);
  enable_display_update();
  display_changed = ALWAYS;
  
  
  char forward[] = "FORWARD";
  char backwards[] = "BACKWARDS";
  char left[] = "LEFT";
  char right[] = "RIGHT";
  char one[] = "1";
  char two[] = "2";
  char three[] = "3";
  char four[] = "4";
  char five[] = "5";
  char six[] = "6";
  char seven[] = "7";
  char eight[] = "8";
  
  int value;
  int done;
  int counter = 0;
  char tS;
  
  Init_Serial_UCA0(SMALL_BOD_BRW, SMALL_BOD_MCTLW);
  Init_Serial_UCA1(SMALL_BOD_BRW, SMALL_BOD_MCTLW);


  while(ALWAYS) 
  {    
    Display_Process();
    
    //Set both USB and IOT to communicate at 115,200 Baud
    switch(enter)
    {
        case START:
            if(waited_start == 0)
            {
                if(wait_2s == 400)
                {
                    P5OUT |= IOT_RESET;
                }
                else if(wait_2s == 800)
                {
                    waited_start = 1;
                    UCA0IE |= UCTXIE;
                }
            }
            else if(waited_start == 1)
            {
                if(done_c == 1 && done_p == 1 && done_i == 1)
                {
                    UCA0IE &= ~UCTXIE;
                    if(wait_i >= 100)
                    {
                        enter = BOD;
                        done_c = 0;
                        done_p = 0;
                        done_i = 0;
                        for(int i = 0; i < 8; i++)
                        {
                            display_line[DISP_ENTRY_2][i] = IP[i];
                            display_line[DISP_ENTRY_3][i] = IP[i + 8];
                        }
                        display_changed = ALWAYS;
                    }
                }
                else if(done_c == 1 && done_p == 0 && done_i == 0)
                {
                    if(wait_c < 100)
                    {
                        UCA0IE &= ~UCTXIE;
                    }
                    else if(wait_c >= 100)
                    {
                        UCA0IE |=  UCTXIE;
                    }
                }
                else if(done_c == 1 && done_p == 1 && done_i == 0)
                {
                    if(wait_p < 100)
                    {
                        UCA0IE &= ~UCTXIE;
                    }
                    else if(wait_p >= 100)
                    {
                        UCA0IE |=  UCTXIE;
                    }
                }
            }
            break;
        case BOD:
            //The '@' will be the start command
            if(IOT_Char_Rx[iot_rx_ring_rd] == '@')
            {
                counter++;
                start = ALWAYS;
                test_iot[pptr] = IOT_Char_Rx[iot_rx_ring_rd];
                pptr++; 
                iot_rx_ring_rd++;
                enter = PARSE;
            }
            else
            {
                if(iot_rx_ring_rd != iot_rx_ring_wr)
                {
                    iot_rx_ring_rd++;
                    if (iot_rx_ring_rd >= (sizeof(IOT_Char_Rx)))
                    {
                        iot_rx_ring_rd = BEGINNING; // Circular buffer back to beginning
                    }
                }
            }
            break;
        case PARSE:
            //As long as pointers are different continue getting the letters for the command
            if(iot_rx_ring_rd != iot_rx_ring_wr)
            {
                //End has not been found yet
                if(end == RESET_STATE)
                {
                    //Once '\r' is found we are done
                    if((counter == 10))
                    {
                        //Got to set end to 1, done to 1, pptr needs to go back to 0
                        counter = 0;
                        end = ALWAYS;
                        done = ALWAYS;
                        pptr = RESET_STATE;
                    }
                    else
                    {
                        //continue incrementing pptr and the rd pointer
                        test_iot[pptr] = IOT_Char_Rx[iot_rx_ring_rd];
                        pptr++;
                        iot_rx_ring_rd++;
                        counter++;
                    }
                }
            }
            
            
            //set done = 0, end = 0, start = 0 and do the array copy thing
            if(done == ALWAYS)
            {
                done = RESET_STATE;
                end = RESET_STATE;
                start = RESET_STATE;
                
                if (iot_rx_ring_rd >= (sizeof(IOT_Char_Rx)))
                {
                    iot_rx_ring_rd = BEGINNING; // Circular buffer back to beginning
                }
              
                
                for(int i = RESET_STATE; i < P_BUFF_SIZE; i++)
                {
                    IOT_Char_Tx[i] = test_iot[i];
                    if(i == 5)
                    {
                        tS = IOT_Char_Tx[i];
                        //gang = tS;
                    }
                    else if(i == 6)
                    {
                        numtime[0] = IOT_Char_Tx[i];
                    }
                    else if(i == 7)
                    {
                        numtime[1] = IOT_Char_Tx[i];
                    }
                    else if(i == 8)
                    {
                        numtime[2] = IOT_Char_Tx[i];
                    }
                    else if(i == 9)
                    {
                        numtime[3] = IOT_Char_Tx[i];
                    }
                }
                if(tS == 'F')
                {
                    for(int i = 0; i < 11; i++)
                    {
                        display_line[DISP_ENTRY_1][i] = forward[i];
                    }
                    display_changed = ALWAYS;
                    enter = FORWARD;
                }
                else if(tS == 'B')
                {
                    for(int i = 0; i < 11; i++)
                    {
                        display_line[DISP_ENTRY_1][i] = backwards[i];
                    }
                    display_changed = ALWAYS;
                    enter = BACKWARDS;
                }
                else if(tS == 'L')
                {
                    for(int i = 0; i < 11; i++)
                    {
                        display_line[DISP_ENTRY_1][i] = left[i];
                    }
                    display_changed = ALWAYS;
                    enter = LEFT;
                }
                else if(tS == 'R')
                {
                    for(int i = 0; i < 11; i++)
                    {
                        display_line[DISP_ENTRY_1][i] = right[i];
                    }
                    display_changed = ALWAYS;
                    enter = RIGHT;
                }
                else if(tS == 'A')
                {
                    if(numtime[0] == '1')
                    {
                        display_line[DISP_ENTRY_4][9] = one[0];
                        display_changed = ALWAYS;
                        enter = DELAY;
                    }
                    else if(numtime[0] == '2')
                    {
                        display_line[DISP_ENTRY_4][9] = two[0];
                        display_changed = ALWAYS;
                        enter = DELAY;
                    }
                    else if(numtime[0] == '3')
                    {
                        display_line[DISP_ENTRY_4][9] = three[0];
                        display_changed = ALWAYS;
                        enter = DELAY;
                    }
                    else if(numtime[0] == '4')
                    {
                        display_line[DISP_ENTRY_4][9] = four[0];
                        display_changed = ALWAYS;
                        enter = DELAY;
                    }
                    else if(numtime[0] == '5')
                    {
                        display_line[DISP_ENTRY_4][9] = five[0];
                        display_changed = ALWAYS;
                        enter = DELAY;
                    }
                    else if(numtime[0] == '6')
                    {
                        display_line[DISP_ENTRY_4][9] = six[0];
                        display_changed = ALWAYS;
                        enter = DELAY;
                    }
                    else if(numtime[0] == '7')
                    {
                        display_line[DISP_ENTRY_4][9] = seven[0];
                        display_changed = ALWAYS;
                        enter = DELAY;
                    }
                    else
                    {
                        display_line[DISP_ENTRY_4][9] = eight[0];
                        display_changed = ALWAYS;
                        enter = DELAY;
                    }
                }
            }           
            break;
        case FORWARD:
            value = atoi(numtime);
            if(wait_2s < value)
            {
                RIGHT_FORWARD_SPEED = 930;
                LEFT_FORWARD_SPEED = 950;
                RIGHT_REVERSE_SPEED = WHEEL_OFF;
                LEFT_REVERSE_SPEED = WHEEL_OFF;
            }
            else
            {
                enter = DELAY;
            }
            break;
        case BACKWARDS:
            value = atoi(numtime);
            if(wait_2s < value)
            {
                RIGHT_FORWARD_SPEED = WHEEL_OFF;
                LEFT_FORWARD_SPEED = WHEEL_OFF;
                RIGHT_REVERSE_SPEED = 999;
                LEFT_REVERSE_SPEED = 999;
            }
            else
            {
                enter = DELAY;
            }
            break;
        case LEFT:
            value = atoi(numtime);
            if(wait_2s < value)
            {
                RIGHT_FORWARD_SPEED = 999;
                LEFT_FORWARD_SPEED = WHEEL_OFF;
                RIGHT_REVERSE_SPEED = WHEEL_OFF;
                LEFT_REVERSE_SPEED = 999;
            }
            else
            {
                enter = DELAY;
            }
            break;
        case RIGHT:
            value = atoi(numtime);
            if(wait_2s < value)
            {
                RIGHT_FORWARD_SPEED = WHEEL_OFF;
                LEFT_FORWARD_SPEED = 999;
                RIGHT_REVERSE_SPEED = 999;
                LEFT_REVERSE_SPEED = WHEEL_OFF;
            }
            else
            {
                enter = DELAY;
            }
            break; 
        case DELAY:
            if(delay < 50)
            {
                RIGHT_FORWARD_SPEED = WHEEL_OFF;
                LEFT_FORWARD_SPEED = WHEEL_OFF;
                RIGHT_REVERSE_SPEED = WHEEL_OFF;
                LEFT_REVERSE_SPEED = WHEEL_OFF;
            }
            else
            {
                enter = BOD;
            }
            break;
        default:
            break;
    }
  }
}