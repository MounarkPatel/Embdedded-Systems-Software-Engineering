#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


volatile int wait_200 = RESET_STATE;
extern volatile unsigned char update_display;
extern unsigned volatile long int dcount_sw1;
extern unsigned volatile long int dcount_sw2;
extern volatile int sw1_p;
extern volatile int sw2_p;
volatile int display2 = RESET_STATE;
extern char enter;
//extern char gang;

volatile int wait_2s = RESET_STATE;
volatile int delay = RESET_STATE;
volatile int wait_c = RESET_STATE;
volatile int wait_p = RESET_STATE;
volatile int wait_i = RESET_STATE;

extern volatile int done_c;
extern volatile int done_p;
extern volatile int done_i;

volatile int w_F = RESET_STATE;
volatile int w_B = RESET_STATE;
volatile int w_R = RESET_STATE;
volatile int w_L = RESET_STATE;


//This is an inturrupt that increments wait_200 which increaments every 5ms
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)
{ 
    
  //If wait_200 has elapsed 200ms update_display has to be set to 1
  if(++wait_200%MS_200 == RESET_STATE)
  {
    display2++;
    update_display = ALWAYS;
  }
  
  if(enter == START)
  {
      if(done_c == 1)
      {
          wait_c++;
      }
      if(done_p == 1)
      {
          wait_p++;
      }
      if(done_i == 1)
      {
          wait_i++;
      }
  }
  else
  {
      wait_c = 0;
      wait_i = 0;
      wait_p = 0;
  }
     
  if((enter == START) || (enter == FORWARD) || (enter == BACKWARDS) || (enter == LEFT) || (enter == RIGHT))
  {
      wait_2s++;
  }
  else
  {
      wait_2s = RESET_STATE;
  }
  /*
  if(gang == 'F')
  {
      w_F++;
  }
  else
  {
      w_F = RESET_STATE;
  }
  
  if(gang == 'B')
  {
      w_B++;
  }
  else
  {
      w_B = RESET_STATE;
  }
  
  if(gang == 'R')
  {
      w_R++;
  }
  else
  {
      w_R = RESET_STATE;
  }
  
  if(gang == 'L')
  {
      w_L++;
  }
  else
  {
      w_L = RESET_STATE;
  }
  */
  if(enter == DELAY)
  {
      delay++;
  }
  else
  {
      delay = RESET_STATE;
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