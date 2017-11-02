/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                      ESCOLA DE VERÃO EM COMPUTAÇÃO                         *
 ******************************************************************************/
#include "msp430g2553.h"


short int led_control = 0;

void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;   // Turn off Watchdog timer
  P1DIR = 0x01 + 0x40;        // Define pins 1.0 and 1.6 as output   (0100 0001)
  P1REN = 0x08;               // Enable pullup/pulldown from pin 1.3 (0000 1000)
  P1OUT = 0x08;               // Define pullup for the pin 1.3       (0000 1000)

  CCTL0 = CCIE;               // Enable timer A comparison interruption
  TACTL = TASSEL_2+MC_3+ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz    (8 us)      
  CCR0 =  62500;              // Mode up/down: get to the value and then restart
                              // to zero, therefore each interruption occurs
                              // 2 * 62500 * 8 us = 1 second
  _BIS_SR(CPUOFF + GIE);                    
  while(1);             
} 

// Timer A0 interrupt service routine 
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {   
  
  // Turn the LED on for 1s and off for 2s
  if (led_control < 2) {
    P1OUT = P1OUT ^ 0x01;
    led_control++;
  }
  else {
    led_control = 0x00;
  }
  
} 