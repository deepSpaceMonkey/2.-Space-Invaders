#include "../inc/tm4c123gh6pm.h"
// dac.c
// PE0-2 are connected to positive logic buttons
// PB0 outputs to 12kohm resistor
// PB1 outputs to 6kohm resistor
// PB2 outputs to 3kohm resistor
// PB3 outputs to 1.5kohm resistor
// Port B resistors lead to a common Vout rail which is connected
// to a 3.5 mm headphone jack

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	SYSCTL_RCGCGPIO_R	&= ~0x02;		// enable port B clock
  SYSCTL_RCGCGPIO_R |= 0x02;
	__nop();
	__nop();
	GPIO_PORTB_DIR_R &= ~0x0F;		// set PB0-3 to output
	GPIO_PORTB_DIR_R |= 0x0F;
	GPIO_PORTB_AFSEL_R &= ~0x07;  // disable alt funct on PB2-0
	GPIO_PORTB_DEN_R &= ~0x0F;		// enable GPIO for PB0-3
	GPIO_PORTB_DEN_R |= 0x0F;
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R = data;			// output data to DAC on PORTB
}
