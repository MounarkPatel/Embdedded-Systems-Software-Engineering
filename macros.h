#define RED_LED_ON      (P1OUT |= RED_LED)
#define RED_LED_OFF    (P1OUT &= ~RED_LED)
#define GREEN_LED_ON    (P6OUT |= GRN_LED)
#define GREEN_LED_OFF  (P6OUT &= ~GRN_LED)
#define ALWAYS                         (1)
#define RESET_STATE                    (0)
#define RED_LED                     (0x01) // RED LED 0
#define GRN_LED                     (0x40) // GREEN LED 1

//LCD Display
#define R_1 (0)
#define R_2 (1)
#define R_3 (2)


#define ALL_ONES                (0xFF)
#define ALL_ZEROS               (0x00)  
#define DISPLAY_HEIGHT          (0x04)
#define DISPLAY_LENGTH          (0x0B)
#define DISP_PTR                (0X04) 

#define DISP_ENTRY_1            (0x00)
#define DISP_ENTRY_2            (0x01)
#define DISP_ENTRY_3            (0x02)
#define DISP_ENTRY_4            (0x03)
#define DISP_ENTRY_5            (0x04)
#define DISP_ENTRY_6            (0x05)
#define DISP_ENTRY_7            (0x06)
#define DISP_ENTRY_8            (0x07)
#define DISP_ENTRY_9            (0x08)
#define DISP_ENTRY_10           (0x09)
#define DISP_ENTRY_11           (10)

#define CASE_COND_1             (250)
#define CASE_COND_2             (200)
#define CASE_COND_3             (150)
#define CASE_COND_4             (100)
#define CASE_COND_5             (50)
#define DISP_CHANGE_ON          (0x01)
#define CASE_BREAK              (0x00)
#define COUNT_INIT              (0x00)
#define DISP_LENGTH_END         (10)
#define DISP_ENTRY_START        (0x00)

#define USE_GPIO (0x00)
#define USE_SMCLK (0x01)

#define DIVS (0x0030)
#define DIVS_L (0x0030)
#define DIVS0 (0x0010)
#define DIVS0_L (0x0010)
#define DIVS1 (0x0020)
#define DIVS1_L (0x0020)
#define DIVS_0 (0x0000) // /1
#define DIVS_1 (0x0010) // /2
#define DIVS_1_L (0x0010)
#define DIVS_2 (0x0020) // /4
#define DIVS_2_L (0x0020)
#define DIVS_3 (0x0030) // /8
#define DIVS_3_L (0x0030)
#define DIVS__1 (0x0000) // /1
#define DIVS__2 (0x0010) // /2
#define DIVS__2_L (0x0010)
#define DIVS__4 (0x0020) // /4
#define DIVS__4_L (0x0020)
#define DIVS__8 (0x0030) // /8
#define DIVS__8_L (0x0030)

// Port 1 Pins
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2 V_DETECT_L
#define V_DETECT_R (0x08) // 3 V_DETECT_R
#define V_BAT (0x10) // 4 V_BAT
#define V_THUMB (0x20) // 5 V_THUMB
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define P2_0 (0x01) // 0
#define P2_1 (0x02) // 1
#define P2_2 (0x04) // 2
#define SW2 (0x08) // 3 SW2
#define P2_4 (0x10) // 4
#define P2_5 (0x20) // 5
#define LFXOUT (0x40) // XOUTR
#define LFXIN (0x80) // XINR

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define OA20 (0x02) // 1 Photodiode Circuit
#define OA2N (0x04) // 2 Photodiode Circuit
#define OA2P (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT (0x10) // 4 SMCLK
#define P3_5 (0x20) // 5
#define IOT_LINK (0x40) // 6 IOT_LINK
#define P3_7 (0x80) // 7
#define USE_GPIO (0x00)
#define USE_SMCLK (0x01)

// Port 4 Pins
#define RESET_LCD (0x01) // 0 LCD Reset
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output?UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

// Port 5 Pins
#define IOT_RESET (0x01) // 0 IOT Reset
#define IR_LED (0x02) // 1 
#define IOT_PROG_SEL (0x04) // 2
#define IOT_PROG_MODE (0x08) // 3
#define CHECK_BAT (0x10) // 4 Battery Check

// Port 6 Pins 
#define R_FORWARD (0X01) // 0 Right Wheel Forward
#define L_FORWARD (0X02) // 1 Left Wheel Forward
#define R_REVERSE (0X04) // 2 Right Wheel Reverse
#define L_REVERSE (0X08) // 3 Left Wheel Reverse
#define LCD_BACKLITE (0X10) // 4
#define P6_5 (0X20) // 5

//Debouncing Switches 
#define TB0CCR0_INTERVAL (2500)
#define TB0CCR1_INTERVAL  (450000) //900ms
#define TB0CCR2_INTERVAL  (450000) //900ms
#define BACK_OFF (P6OUT &= ~LCD_BACKLITE)
#define BACK_ON (P6OUT |= LCD_BACKLITE)
#define SW_1_P (2)
#define SW_2_P (4)
#define OVER (14)

//PWM, States and Speeds
#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define LEFT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)

#define WHEEL_OFF (0)
#define WHEEL_PERIOD (1000)

#define RIGHT_S (620)
#define LEFT_S (660)
#define RIGHT_R (920)
#define LEFT_R (955)

#define CLOCK (999)
#define F_PAUSE (1)
#define F_FORWARD (201)
#define S_PAUSE (401)
#define F_REVERSE (601)
#define T_PAUSE (1001)
#define S_FORWARD (1201)
#define FOURTH_PAUSE (1401)
#define COUNTER (1601)
#define FIFTH_PAUSE (2201)
#define CLOCKWISE (2401)
#define FINAL_PAUSE (3001)
#define MS_200 (40)

//Project 6
#define PAUSE ('P')
#define TURN ('T')
#define CIRCLE ('C')
#define BACK ('B')
#define Pause_T (200)
#define ON (250)
#define CHAR_0 (0)
#define CHAR_1 (1)
#define CHAR_2 (2)
#define CHAR_3 (3)
#define CHAR_4 (4)
#define CHAR_5 (5)
#define CHAR_6 (6)
#define CHAR_7 (7)
#define CHAR_8 (8)
#define WAIT_T1 (600)
#define WAIT_T2 (350)

//Homework 8
#define BEGINNING (0)
#define P_BUFF_SIZE (10)
#define SMALL_RING_SIZE (12)
#define LARGE_RING_SIZE (70)
#define SMALL_BOD_BRW (4) //115200
#define SMALL_BOD_MCTLW (0x5551) //115200
#define LARGE_BOD_BRW (1) //460800
#define LARGE_BOD_MCTLW (0x4A11) //460800

#define FOURHANDO (400)
#define BS (0X08) 
#define ZERO (0)
#define ONE (1)
#define TWO (2)
#define THREE (3)
#define FOUR (4)
#define FIVE (5)
#define SIX (6)
#define SEVEN (7)
#define EIGHT (8)
#define NINE (9)
#define TEN (10)
#define ELEVEN (11)
#define BALLIN1 (0x0D)
#define BALLIN2 (0x0A)

#define START ('1')
#define BOD ('2')
#define PARSE ('P')
#define FORWARD ('F')
#define BACKWARDS ('B')
#define LEFT ('L')
#define RIGHT ('R')
#define DELAY ('D')








