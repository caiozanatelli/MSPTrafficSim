/******************************************************************************
 *                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     *
 *                         DCC008 - SOFTWARE BÁSICO                           *
 ******************************************************************************/

#include "msp430g2553.h"
#include <stdio.h>

#define BACKUP_REGS 12 // r4 to r15

#define STACK_SIZE  50
#define STACK_TOP   STACK_SIZE - 1   
#define TOTAL_TASKS 3

// Assembly code to load stack pointer
#define LOAD_STACK_POINTER(temp) \
    __asm__ volatile ("mov.w r1, %0 \n\t" \
            : "=r" (temp));

// Assembly code to save stack pointer
#define SAVE_STACK_POINTER(temp) \
    __asm__ volatile ("mov.w %0, r1  \n\t" \
            :  \
            : "r" (temp));

// Enable GIE in SR so that the WDT never stops when we go to user task
// Enable SCG0 for 25MHZ CPU execution
#define DEFAULT_SR  ((uint16_t)0x0048) 

// Assembly code to save context
#define SAVE_CONTEXT()           \
  asm volatile ( "push r4  \n\t" \
                 "push r5  \n\t" \
                 "push r6  \n\t" \
                 "push r7  \n\t" \
                 "push r8  \n\t" \
                 "push r9  \n\t" \
                 "push r10 \n\t" \
                 "push r11 \n\t" \
                 "push r12 \n\t" \
                 "push r13 \n\t" \
                 "push r14 \n\t" \
                 "push r15 \n\t" \
	);

// Assembly code to restore context
#define RESTORE_CONTEXT()       \
  asm volatile ( "pop r15 \n\t" \
                 "pop r14 \n\t" \
                 "pop r13 \n\t" \
                 "pop r12 \n\t" \
                 "pop r11 \n\t" \
                 "pop r10 \n\t" \
                 "pop r9  \n\t" \
                 "pop r8  \n\t" \
                 "pop r7  \n\t" \
                 "pop r6  \n\t" \
                 "pop r5  \n\t" \
                 "pop r4  \n\t" \
                 "reti    \n\t" \
	);


// Stack for each task - 1024*16 = 2KB RAM
uint16_t task1ram[STACK_SIZE];
uint16_t task2ram[STACK_SIZE];
uint16_t task3ram[STACK_SIZE];

// Definitions for the tasks
volatile uint8_t  task_id; /*has the current running task*/
volatile uint16_t *stack_pointer[TOTAL_TASKS]; /*address of stack pointer for each task*/

// Definitions for the LEDs to be scheduled
volatile uint8_t led2  = 0x01;
volatile uint8_t led10 = 0x40;
volatile uint8_t sw_pressed = 0;

// Blink the LED defined by the "led2" variable for 2 seconds
void task1(void) { 
  while (1) {
    // Generate delay of 2 seconds. Loops aren't used to avoid branches in asm code
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);

    // Blink "led1" LED for 2 seconds
    P1OUT ^= led2;
  }
}

// Blink the LED defined by the "led10" variable for 10 seconds
void task2(void) {  
  while (1) {
    // Generate delay of 10 seconds. Loops aren't used to avoid branches in asm code
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);
    __delay_cycles(33333);

    // Blink "led2" LED for 10 seconds
    P1OUT ^= led10;
  }
}

// Switch the blinking time for each LED by swapping the variables "led2" and "led10"
void task3(void) {
  uint8_t swap = 0;
  while (1) {
    if (sw_pressed) {
      swap  = led2;
      led2  = led10;
      led10 = swap;  

      sw_pressed = 0;
    }
  }
}


/*****************************************************/

/*
 * This function will initialise stack for each task. Following are filled into the stack
 * 1) Store the PC first since it has to be poped back and loaded at end 
 * 2) then store SR register. This determines the CPU condition at which your task should execute
 * 3) leave the space for the registers r4 to r15 since the scheduler will pop these when a task switching occurs
 * 3) return the address of stack which will contain all informations for the task to execute after task switching
 * 4) TODO: fill the end of stack with known values to detect buffer overflows.
 */
uint16_t *initialise_stack(void (* func)(void), uint16_t *stack_location) {
  uint8_t i;
  
  /*MSP430F5529 has a 20bit PC register*/
  *stack_location = (uint16_t)func; //last 16 bits will only stored. Pending 4bits will be stored with SR
  stack_location--;
  *stack_location = DEFAULT_SR;  

  /*leave space in stack for r4 to r15*/
  for(i = 0; i < BACKUP_REGS; i++) {
    stack_location--;
  }
  
  return stack_location;
}

 
volatile uint16_t *temp;


void main(void) {
  
  //Stop the watchdog timer until we configure our scheduler
  WDTCTL = WDTPW + WDTHOLD;
    
  /*initialize stack for each task*/
  stack_pointer[0] = initialise_stack(task1, &task1ram[STACK_TOP]); // initialize stack 0
  stack_pointer[1] = initialise_stack(task2, &task2ram[STACK_TOP]); // initialize stack 0
  stack_pointer[2] = initialise_stack(task3, &task3ram[STACK_TOP]); // initialize stack 0    

  // Definitions of ports, pins and interrpution modes
  P1DIR  = 0x01 + 0x40;            // Define pins 1.0 and 1.6 as output        (01000001)
  P1REN  = 0x08;                   // Enable pullup/pulldown from pin 1.3      (00001000)
  P1OUT  = 0x08;                   // Define pullup for the pin 1.3            (00001000)
  P1IE   = 0x08;                   // Enable interruption from the pin 1.3     (00001000)
  P1IFG  = 0x00;                   // Set the port 1 interruption flag as zero (00000000)

  CCTL0  = CCIE;                   // Enable timer A comparison interruption
  TACTL  = TASSEL_2 + MC_3 + ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz (8 us)      
  CCR0   = 20833;                  // Mode up/down: get to the defined value and then restart

  /*initialize to first task*/
  task_id = 0;
  temp = stack_pointer[task_id];

  SAVE_STACK_POINTER(temp);

  _BIS_SR(GIE);  

  RESTORE_CONTEXT(); // pop up the first - task - load context
}

// Routine to treat Port 1 interruption
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
  sw_pressed = 1; // Flag to verify if the sw has been pressed
  P1IFG = 0x00;   // Set the value zero for the port 1 flag interruption  (00000000)
}

// Routine to treat Timer interruption
// "naked" is used to not let the compiler insert/modify instructions made in this interruption
// Specifically, this is necessary because the gcc compiler insert a push instr for the r15 reg
#pragma vector=TIMER0_A0_VECTOR
__interrupt void __attribute__((naked)) Timer_A (void) {

  //0 -Save Context 
  SAVE_CONTEXT();

  //1-Load Stack Pointer
  LOAD_STACK_POINTER(temp);
  // Backup the Stack Pointer
  stack_pointer[task_id] = temp;
  
  //2-update the task id
  if (task_id < TOTAL_TASKS - 1) {
    task_id++;
  }
  else {
    task_id = 0;
  }

  //3-Save Stack pointer
  temp = stack_pointer[task_id]; 
  SAVE_STACK_POINTER(temp);

  //4-Load Context
  RESTORE_CONTEXT();
  
}
