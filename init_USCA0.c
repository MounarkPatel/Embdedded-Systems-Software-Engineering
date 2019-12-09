#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"

extern volatile char USB_Char_Rx[LARGE_RING_SIZE];
extern volatile char IOT_Char_Rx[LARGE_RING_SIZE];

char USB_Char_Tx[P_BUFF_SIZE];
extern volatile char IOT_Char_Tx[P_BUFF_SIZE];

volatile int usb_rx_ring_rd = BEGINNING;
volatile int iot_rx_ring_rd = BEGINNING;

extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int iot_rx_ring_wr;

volatile unsigned int usb_tx_ring_wr;
volatile unsigned int iot_tx_ring_wr;


//IOT Module Buad Right Now is 115200
void Init_Serial_UCA0(int BRW, int MCTLW)
{
  int i;
  for(i = 0; i < LARGE_RING_SIZE; i++)
  {
    IOT_Char_Rx[i] = 0x00; // USB Rx Buffer
  }
  
  iot_rx_ring_wr = BEGINNING;
  iot_rx_ring_rd = BEGINNING;
  for(i = 0; i < P_BUFF_SIZE; i++)
  { // May not use this
    IOT_Char_Tx[i] = 0x00; // USB Tx Buffer
  }
  /*
  iot_tx_ring_wr = BEGINNING;
  iot_tx_ring_rd = BEGINNING;
` */
  // Configure UART 0
  UCA0CTLW0 = 0; // Use word register
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK; 
  UCA0BRW = BRW;
  UCA0MCTLW = MCTLW; 
  UCA0CTLW0 &= ~UCSWRST;
  UCA0IE |= UCRXIE;
}


//Serial Port Buad Right Now is 115200
void Init_Serial_UCA1(int BRW, int MCTLW)
{
  int i;
  for(i = 0; i < LARGE_RING_SIZE; i++)
  {
    USB_Char_Rx[i] = 0x00; // USB Rx Buffer
  }
  
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;
  for(i = 0; i < P_BUFF_SIZE; i++)
  { // May not use this
    USB_Char_Tx[i] = 0x00; // USB Tx Buffer
  }
  /*
  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;
  */
  // Configure UART 0
  UCA1CTLW0 = 0; // Use word register
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK; 
  UCA1BRW = BRW;
  UCA1MCTLW = MCTLW; 
  UCA1CTLW0 &= ~UCSWRST;
  UCA1IE |= UCRXIE;
}
  