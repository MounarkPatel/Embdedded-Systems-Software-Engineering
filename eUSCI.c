#include  "functions.h"
#include  "msp430.h"
#include  <string.h>
#include  "macros.h"

// global variables

volatile unsigned int usb_rx_ring_wr;
volatile unsigned int iot_rx_ring_wr;
extern volatile int iot_rx_ring_rd;

volatile char USB_Char_Rx[LARGE_RING_SIZE];
volatile char IOT_Char_Rx[LARGE_RING_SIZE];

volatile int UCA0_index = BEGINNING;
volatile int UCA1_index = BEGINNING;

//volatile char test_usb[SMALL_RING_SIZE];
volatile char test_iot[P_BUFF_SIZE];
volatile char IOT_Char_Tx[P_BUFF_SIZE];

volatile char IP[16];
extern char keep_connection[];
extern char connect_to_port[];
extern char get_IP[];
extern volatile int done_c;
extern volatile int done_p;
extern volatile int done_i;
extern volatile int wait_c;
extern volatile int wait_p;
volatile int counter_Parse = 0;
volatile int check1 = 0;
volatile int check2 = 0;
volatile int start_add = 0;
volatile int change_R = 0;
extern char enter;

//IOT Baud Rate = 115200
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void)
{  
    char temp;
    unsigned int t;
    
    switch(__even_in_range(UCA0IV, BS))
    {
        case RESET_STATE: // Vector 0 - no interrupt
            break;
        case TWO: // Vector 2 - RXIFG
            if(change_R == 0)
            {
                temp = UCA0RXBUF;
                if(check1 == 0 && check2 == 0)
                {
                    if(temp == 'r')
                    {
                        check1 = 1;
                    }
                }
                else if(check1 == 1 && check2 == 0)
                {
                    counter_Parse++;
                    if(counter_Parse == 1)
                    {
                        if(temp == '=')
                        {
                            check2 = 1;
                            counter_Parse = 0;
                        }
                    }
                    else
                    {
                        check1 = 0;
                        counter_Parse = 0;
                    }
                }
                else
                {
                    if(temp != ' ')
                    {
                        IP[start_add] = temp;
                        start_add++;
                    }
                    else if(temp == ' ')
                    {
                        IP[start_add] = '\0';
                        change_R = 1;
                    }
                }
                UCA1TXBUF = temp;
            }
            else
            {
                t = iot_rx_ring_wr++;
                IOT_Char_Rx[t] = UCA0RXBUF; // RX -> USB_Char_Rx character
                if (iot_rx_ring_wr >= (sizeof(IOT_Char_Rx)))
                {
                    iot_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
                }
                temp = UCA0RXBUF;
                UCA1TXBUF = temp;
            }
            break;
        case FOUR:
            if(done_c == 0)
            {
                UCA0TXBUF = keep_connection[UCA0_index];
                UCA0_index++;
                if(keep_connection[UCA0_index] == '\0')
                {
                    done_c = 1;
                    UCA0_index = 0;
                }
            }
            else if(done_c == 1 && done_p == 0 && done_i == 0)
            {
                 if(wait_c >= 100)
                 {
                     UCA0TXBUF = connect_to_port[UCA0_index];
                     UCA0_index++;
                     if(connect_to_port[UCA0_index] == '\0')
                     { 
                         done_p = 1;
                         UCA0_index = 0;
                     }   
                 }
            }
            else if(done_c == 1 && done_p == 1 && done_i == 0)
            {
                if(wait_p >= 100)
                {
                    UCA0TXBUF = get_IP[UCA0_index];
                    UCA0_index++;
                    if(get_IP[UCA0_index] == '\0')
                    { 
                        done_i = 1;
                        UCA0_index = 0;
                    }   
                }
            }
            break;      
    }
}



//USB Baud Rate = 115200
#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void)
{
    char temp;
    unsigned int t;
    switch(__even_in_range(UCA1IV,BS))
    {
        case RESET_STATE: // Vector 0 - no interrupt
            break;
        case TWO: // Reviver
            t = usb_rx_ring_wr++;
            USB_Char_Rx[t] = UCA1RXBUF; // RX -> USB_Char_Rx character
            if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx)))
            {
                usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
            }
            temp = UCA1RXBUF;
            UCA0TXBUF = temp;
            break;
        //Transmittor
        case FOUR:
            break;
    }
}
