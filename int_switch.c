#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


unsigned volatile long int dcount_sw1;
unsigned volatile long int dcount_sw2;
volatile int sw1_p = RESET_STATE;
volatile int sw2_p = RESET_STATE;

volatile int p1 = RESET_STATE;
volatile int p2 = RESET_STATE;
extern char enter;


//Code to control debounicing of switch one
#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void)
{
  // Switch 1
  if (P4IFG & SW1) 
  {
    dcount_sw1 = RESET_STATE;
    sw1_p = ALWAYS;
    P6OUT &= ~LCD_BACKLITE;
    P4IE &= ~SW1;
    P4IFG &= ~SW1;
    
    TB0CCTL1 |= CCIE;
    TB0CCTL0 &= ~CCIE;
    
    /*
    if(enter == BOD1)
    {
      p1 = 1;
    }
    else if(enter == RECEIVING)
    {
      p1 = 0;
    }
    else if(enter == TRANSMITTING)
    {
      p1 = 1;
    }
    else 
    {
      p1 = 0;
    }
    */
  }
  P4IFG = 0;
}


//Code to control debouncing of switch two
#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void)
{
  // Switch 2
  if (P2IFG & SW2) 
  {
    dcount_sw2 = RESET_STATE;
    sw2_p = ALWAYS;
    P6OUT &= ~LCD_BACKLITE;
    P2IES &= ~SW2; 
    P2IFG &= ~SW2;
    
    TB0CCTL2 |= CCIE;
    TB0CCTL0 &= ~CCIE;
    
    /*
    if(enter == BOD1)
    {
      p2 = 1;
    }
    else
    {
      p2 = 0;
    }
    */
  }
  P2IFG = 0;
}

