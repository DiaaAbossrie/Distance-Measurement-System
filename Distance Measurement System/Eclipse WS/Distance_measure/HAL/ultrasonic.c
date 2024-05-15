/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the Ultrasonic Sensor driver
 *
 * Author: Diaa Abossrie
 *
 ******************************************************************************/

#include "ultrasonic.h"
#include "../MCAL/icu.h"  // Include header file for ICU module
#include "../MCAL/gpio.h"  // Include header file for GPIO module
#include "util/delay.h"  // Include header file for delay functions

// Global variables for edge counter and timer value
uint8 edge_counter = 0;
uint16 timer_value = 0;

void Ultrasonic_init(void){
    // Configure the ICU module for edge detection
	ICU_ConfigType Ultrasonic_config={F_CPU_8,RAISING};

	// Initialize the ICU module with the specified configuration
	ICU_init(&Ultrasonic_config);

	ICU_setCallBack(Ultrasonic_edgeProcessing);

	// Setup trigger pin as output
	GPIO_setupPinDirection(TRIGGER_PORT_ID,TRIGGER_PIN_ID,PIN_OUTPUT);
}


void Ultrasonic_Trigger(void){
    // Generate a pulse to trigger the ultrasonic sensor
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_HIGH);

	_delay_us(50);

	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){
    // Trigger the ultrasonic sensor
	Ultrasonic_Trigger();

    // Wait for both rising and falling edges to be captured
	while(edge_counter<2);

	// Reset edge counter
	edge_counter=0;

	// Calculate and return the distance in centimeters
	return (timer_value/58)+1 ;
}


void Ultrasonic_edgeProcessing(void){

	// Increment edge counter
	edge_counter++;

	switch(edge_counter){
	case 1:
		// On the first edge, clear the timer value and set for falling edge detection
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
		break;
	case 2:
		// On the second edge, get the timer value and set for rising edge detection
		timer_value = ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING);
		ICU_clearTimerValue();
		break;
	}
}
