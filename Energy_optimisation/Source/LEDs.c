/*----------------------------------------------------------------------------
Copyright (C) 2019 Aniruddha Kanhere

This Source code can be cloned, modified and used as required. But the owner/author
does not take any responsibily for damage/distruction of property or any such material
caused by the use of this code. The user shall be responsible for any such incident
 *----------------------------------------------------------------------------*/
 
 #include <MKL25Z4.H>
#include "LEDs.h"
#include "gpio_defs.h"
#include "delay.h"

void Init_RGB_LEDs(void) {
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;;
	
	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);          
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);          
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);          
	
	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
	
	Control_RGB_LEDs(1, 1, 1);
	Delay(10);
	Control_RGB_LEDs(0, 0, 0);
}

void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on) {
	if (red_on) {
			PTB->PCOR = MASK(RED_LED_POS);
	} else {
			PTB->PSOR = MASK(RED_LED_POS); 
	}
	if (green_on) {
			PTB->PCOR = MASK(GREEN_LED_POS);
	}	else {
			PTB->PSOR = MASK(GREEN_LED_POS); 
	} 
	if (blue_on) {
			PTD->PCOR = MASK(BLUE_LED_POS);
	}	else {
			PTD->PSOR = MASK(BLUE_LED_POS); 
	}
}	

void Light_LEDs(float v) {
	if (v > V_BLUE) // blue
			Control_RGB_LEDs(0, 0, 1);
	else if (v > V_MAGENTA) // magenta
			Control_RGB_LEDs(1, 0, 1);
	else if (v > V_GREEN) // green
			Control_RGB_LEDs(0, 1, 0);
	else if (v > V_RED) // red
			Control_RGB_LEDs(1, 0, 0);
}
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
