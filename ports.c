#include  "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include  <string.h>

void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_Port5();
  Init_Port6(); 
}

void Init_Port1(void)
{
  //-------------------------------------------------------
  // RED_LED (0x01) // 0 RED LED 0
  // A1_SEEED (0x02) // 1 A1_SEEED
  // V_DETECT_L (0x04) // 2 A2
  // V_DETECT_R (0x08) // 3 A3
  // V_BAT (0x10) // 4 A4
  // V_THUMB (0x20) // 5 A5
  // UCA0TXD (0x40) // 6 Back Channel UCA0TXD
  // UCA0RXD (0x80) // 7 Back Channel UCA0RXD
  //-------------------------------------------------------
  P1DIR = 0xFF; // Set P1 direction to output
  P1OUT = 0x00; // P1 set Low
  
  P1SEL0 &= ~RED_LED; // Set RED_LED as GP I/O
  P1SEL1 &= ~RED_LED; // Set RED_LED as GP I/O
  P1OUT |= RED_LED; // Set Red LED On
  P1DIR |= RED_LED; // Set Red LED to output
  
  P1SEL0 |= A1_SEEED; // ADC input for A1_SEEED
  P1SEL1 |= A1_SEEED; // ADC input for A1_SEEED
  
  P1SEL0 |= V_DETECT_L; // ADC input for V_DETECT_L
  P1SEL1 |= V_DETECT_L; // ADC input for V_DETECT_L
  
  P1SEL0 |= V_DETECT_R; // ADC input for V_DETECT_R
  P1SEL1 |= V_DETECT_R; // ADC input for V_DETECT_R
  
  P1SEL0 |= V_BAT; // ADC input for V_BAT
  P1SEL1 |= V_BAT; // ADC input for V_BAT
  
  P1SEL0 |= V_THUMB; // ADC input for V_THUMB
  P1SEL1 |= V_THUMB; // ADC input for V_THUMB
  
  P1SEL0 |= UCA0RXD; // UCA0RXD pin
  P1SEL1 &= ~UCA0RXD; // UCA0RXD pin
  
  P1SEL0 |= UCA0TXD; // UCA0TXD pin
  P1SEL1 &= ~UCA0TXD; // UCA0TXD pin
  //----------------------------------------------------
}

void Init_Port2(void){
  //------------------------------------------------------------------------------
  // Configure PORT 2
  P2DIR = 0xFF; // Set P2 direction to output
  P2OUT = 0x00; // P2 set Low
  
  P2SEL0 &= ~P2_0; // P2_0 GPIO operation
  P2SEL1 &= ~P2_0; // P2_0 GPIO operation
  P2DIR &= ~P2_0; // Direction = input
  
  P2SEL0 &= ~P2_1; // P2_1 GPIO operation
  P2SEL1 &= ~P2_1; // P2_1 GPIO operation
  P2DIR &= ~P2_1; // Direction = input
  
  P2SEL0 &= ~P2_2; // P2_2 GPIO operation
  P2SEL1 &= ~P2_2; // P2_2 GPIO operation
  P2DIR &= ~P2_2; // Direction = input
  
  P2SEL0 &= ~SW2; // SW2 Operation
  P2SEL1 &= ~SW2; // SW2 Operation
  P2DIR &= ~SW2; // Direction = input
  P2OUT |= SW2; // Configure pullup resistor
  P2REN |= SW2; // Enable pullup resistor
  
  P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
  P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
  P2IE |= SW2; // P2.6 interrupt enabled
  
  P2SEL0 &= ~P2_4; // P2_4 GPIO operation
  P2SEL1 &= ~P2_4; // P2_4 GPIO operation
  P2DIR &= ~P2_4; // Direction = input
  
  P2SEL0 &= ~P2_5; // P2_5 GPIO operation
  P2SEL1 &= ~P2_5; // P2_5 GPIO operation
  P2DIR &= ~P2_5; // Direction = input
  
  P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
  P2SEL1 |= LFXOUT; // LFXOUT Clock operation
  
  P2SEL0 &= ~LFXIN; // LFXIN Clock operation
  P2SEL1 |= LFXIN; // LFXIN Clock operation
  //------------------------------------------------------------------------------
}

void Init_Port3(void){
  // Configure PORT 3
  P3DIR = 0xFF; // Set P3 direction to output
  P3OUT = 0x00; // P3 set Low
  
  P3SEL0 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
  P3SEL1 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
  P3DIR &= ~TEST_PROBE; // Direction = input
  
  P3SEL0 |= OA20; // OA20 operation
  P3SEL1 |= OA20; // OA20 operation
  
  P3SEL0 |= OA2N; // OA2N operation
  P3SEL1 |= OA2N; // OA2N operation
  
  P3SEL0 |= OA2P; // OA2P operation
  P3SEL1 |= OA2P; // OA2P operation
  
  P3SEL0 &= ~SMCLK_OUT; // P3_4 GPIO operation
  P3SEL1 &= ~SMCLK_OUT; // P3_4 GPIO operation
  P3DIR &= ~SMCLK_OUT; // Direction = input
  
  P3SEL0 &= ~P3_5; // P3_5 GPIO operation
  P3SEL1 &= ~P3_5; // P3_5 GPIO operation
  P3DIR &= ~P3_5; // Direction = input
  
  P3SEL0 &= ~IOT_LINK; // IOT_LINK operation
  P3SEL1 &= ~IOT_LINK; // IOT_LINK GPIO operation
  P3DIR &= ~IOT_LINK; // Direction = input
  
  
  P3SEL0 &= ~P3_7; // P3_7 GPIO operation
  P3SEL1 &= ~P3_7; // P3_7 GPIO operation
  P3DIR &= ~P3_7; // Direction = input
}

void Init_Port4(void){
  //------------------------------------------------------------------------------
  // Configure PORT 4
  P4DIR = 0xFF; // Set P4 direction to output
  P4OUT = 0x00; // P4 set Low
  
  P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
  P4OUT |= RESET_LCD; // Set RESET_LCD Off [High]
  
  P4SEL0 &= ~SW1; // SW1 GPIO operation
  P4SEL1 &= ~SW1; // SW1 GPIO operation
  P4DIR &= ~SW1; // Direction = input
  P4OUT |= SW1; // Configure pullup resistor
  P4REN |= SW1; // Enable pullup resistor
  
  P4IES |= SW1; // P2.0 Hi/Lo edge interrupt
  P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
  P4IE |= SW1; // P2.6 interrupt enabled
  
  P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
  
  P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
  
  P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
  P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
  
  P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
  P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
  
  P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
  P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
  
  P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
  P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
  //------------------------------------------------------------------------------
}

void Init_Port5(void){
  // Configure PORT 5
  P5DIR = 0xFF; // Set P5 direction to output
  P5OUT = 0x00; // P5 set Low
  
  P5SEL0 &= ~IOT_RESET; // IOT_RESET GPIO operation
  P5SEL1 &= ~IOT_RESET; // IOT_RESET GPIO operation
  P5DIR |= IOT_RESET; 
  P5OUT &= ~IOT_RESET;
  
  P5SEL0 &= ~IR_LED; // IR_LED GPIO operation
  P5SEL1 &= ~IR_LED; // IR_LED GPIO operation
  P5DIR |= IR_LED; // Direction = input 
  P5OUT |= IR_LED;
  
  P5SEL0 &= ~IOT_PROG_SEL; // IOT_PROG_SEL GPIO operation
  P5SEL1 &= ~IOT_PROG_SEL; // IOT_PROG_SEL GPIO operation
  P5DIR &= ~IOT_PROG_SEL; // Direction = input
  
  P5SEL0 &= ~IOT_PROG_MODE; // IOT_PROG_MODE GPIO operation
  P5SEL1 &= ~IOT_PROG_MODE; // IOT_PROG_MODE GPIO operation
  P5DIR &= ~IOT_PROG_MODE; // Direction = input
  
  P5SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
  P5SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
  P5DIR &= ~CHECK_BAT; // Direction = input
}

void Init_Port6(void){
  // Configure PORT 6
  P6DIR = 0xFF; // Set P6 direction to output
  P6OUT = 0x00; // P6 set Low
  
  P6SEL0 |= R_FORWARD; 
  P6SEL1 &= ~R_FORWARD; 
  P6DIR |= R_FORWARD; 
  //P6OUT &= ~R_FORWARD; 
  
  P6SEL0 |= L_FORWARD; 
  P6SEL1 &= ~L_FORWARD; 
  P6DIR |= L_FORWARD; 
  //P6OUT &= ~L_FORWARD; 
  
  P6SEL0 |= R_REVERSE; 
  P6SEL1 &= ~R_REVERSE; 
  P6DIR |= R_REVERSE; 
  //P6OUT &= ~R_REVERSE;  
  
  P6SEL0 |= L_REVERSE; 
  P6SEL1 &= ~L_REVERSE; 
  P6DIR |= L_REVERSE; 
  //P6OUT &= ~L_REVERSE; 
  
  P6SEL0 &= ~LCD_BACKLITE; // LCD_BACKLITE GPIO operation
  P6SEL1 &= ~LCD_BACKLITE; // LCD_BACKLITE GPIO operation
  P6DIR |= LCD_BACKLITE; // Set LCD_BACKLITE direction to output
  P6OUT |= LCD_BACKLITE; // Set LCD_BACKLITE On [High]
  
  P6SEL0 &= ~P6_5; //  GPIO operation
  P6SEL1 &= ~P6_5; // P2_5 GPIO operation
  P6DIR &= ~P6_5; // Direction = input
  
  P6SEL0 &= ~GRN_LED; // GRN_LED GPIO operation
  P6SEL1 &= ~GRN_LED; // GRN_LED GPIO operation
  P6DIR |= GRN_LED; // Set GRN_LED direction to output
  P6OUT |= GRN_LED; // Set GRN_LED Off [High]
}