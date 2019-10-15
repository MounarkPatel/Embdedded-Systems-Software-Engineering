#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


extern char display_line[DISPLAY_HEIGHT][DISPLAY_LENGTH];
extern char *display[DISP_PTR];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
volatile int wait_200 = RESET_STATE;
extern unsigned volatile long int dcount_sw1;
extern unsigned volatile long int dcount_sw2;
extern int sw1_p;
extern int sw2_p;
int wait_ten = RESET_STATE ;
int one = RESET_STATE;

//This is an inturrupt that increments wait_200 which increaments every 5ms
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{ 
  //If wait_200 has elapsed 200ms update_display has to be set to 1
  if(++wait_200%MS_200 == RESET_STATE)
  {
    update_display = ALWAYS;
  }
  TB0CCR0 += TB0CCR0_INTERVAL;
}

//This interrupt is there for debouncing the switches on both sides of the car
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)
{
  switch(__even_in_range(TB0IV,OVER))
  {
    case RESET_STATE: break; // No interrupt
    case SW_1_P: // SW1 
      TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
      dcount_sw2++;
      if(dcount_sw2 >= DISP_LENGTH_END)
      {
        TB0CCTL2 |= CCIE;
        TB0CCTL0 |= CCIE;
        P4IE |= SW2;
        dcount_sw2 = RESET_STATE;
        sw2_p = RESET_STATE;
      }
      break;
    case (SW_2_P): // SW2 
      TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
      dcount_sw1++;
      if(dcount_sw1 >= DISP_LENGTH_END)
      {
        TB0CCTL1 |= CCIE;
        TB0CCTL0 |= CCIE;
        P4IE |= SW1;
        dcount_sw1 = RESET_STATE;
        sw1_p = RESET_STATE;
      }
      break;
    case OVER: // overflow
      break;
    default: break;
  }
}