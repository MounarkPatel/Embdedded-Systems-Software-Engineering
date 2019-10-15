#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include  <string.h>

void Switches_Process(void)
{
 if (!(P4IN & SW1))
 {
   Init_Port3(USE_SMCLK);
 }
 if (!(P2IN & SW2)) 
 {
   Init_Port3(USE_GPIO);
 }

}