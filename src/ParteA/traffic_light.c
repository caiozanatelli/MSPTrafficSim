/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                      ESCOLA DE VERÃO EM COMPUTAÇÃO                         *
 ******************************************************************************/
#include "msp430g2553.h"
#include <stdio.h>

volatile uint8_t seconds    = 0;
volatile uint8_t sw_pressed = 0;

void main(void) {
 
  WDTCTL = WDTPW + WDTHOLD;       // Turn off Watchdog timer
  P1DIR = 0x01 + 0x40;            // Define pins 1.0 and 1.6 as output   (0100 0001)
  P1REN = 0x08;                   // Enable pullup/pulldown from pin 1.3 (0000 1000)
  P1OUT = 0x08;                   // Define pullup for the pin 1.3       (0000 1000)

  P1IE  |= 0x08;                  // Enable interruption from the pin 1.3     (00001000)
  P1IFG  = 0x00;                   // Set the port 1 interruption flag as zero (00000000)

  CCTL0 = CCIE;                   // Enable timer A comparison interruption
  TACTL = TASSEL_2 + MC_3 + ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz    (8 us)      
  CCR0 =  62500;                  // Mode up/down: get to the value and then restart
                                  // to zero, therefore each interruption occurs
                                  // 2 * 62500 * 8 us = 1 second
  _BIS_SR(CPUOFF + GIE);

  while(1);             
} 

// Timer A0 interrupt service routine 
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {   
  
  // Represents the Red light in the traffic light
  if ((seconds == 11) | (seconds == 0)) {
    P1OUT  |= 0x01; // Turn the Red LED on
    P1OUT  &= 0xbf; // Turn the Green LED off
    seconds = 0;
    sw_pressed = 0;
  }

  // Represents the Green light in the traffic light
  if (seconds == 2) {
    P1OUT |= 0x40;  // Turn the Green LED on
    P1OUT &= 0xfe;  // Turn the Red LED off
  }

  // Represents the Red light in the traffic light
  if (seconds == 10) {
    P1OUT |= 0x01;  // Turn the Red LED on
    P1OUT |= 0x40;  // Turn the Green LED on
  }

  seconds++;
  
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
  if (!sw_pressed && seconds >= 2 && seconds < 10) {
    seconds += (seconds >= 7) ? 0 : 5;
    sw_pressed = 1;
  }

  P1IFG = 0x00;   // Set the value zero for the port 1 flag interruption  (00000000)
}