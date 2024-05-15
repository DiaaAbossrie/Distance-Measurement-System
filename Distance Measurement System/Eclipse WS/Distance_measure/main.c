/******************************************************************************
 *
 * Module: Main Application "Distance Measuring System"
 *
 * File Name: main.c
 *
 * Description: Source file for the main application
 *
 * Author: Diaa Abossrie
 *
 ******************************************************************************/

#include <avr/io.h>
#include "HAL/lcd.h"         // Include header file for LCD module
#include "HAL/ultrasonic.h"  // Include header file for ultrasonic sensor

uint16 distance = 0;

int main (void){

    // Enable global interrupts
	SREG |= (1<<7);

	// Initialize LCD module
	LCD_init();

	// Initialize ultrasonic sensor
	Ultrasonic_init();

	// Display initial message
	LCD_displayString("Distance= ");

	while(1){
		// Read distance from ultrasonic sensor
		distance = Ultrasonic_readDistance();

		// Display distance on LCD

		// Case 1: Distance less than 10 cm
		if(distance < 10 ){
			LCD_moveCursor(0,10);
			LCD_displayString("  ");   // Display two spaces
			LCD_intgerToString(distance); // Convert and display distance
		}
		// Case 2: Distance between 10 and 99 cm
		else if (distance < 100 && distance>=10){
			LCD_moveCursor(0,10);
			LCD_displayCharacter(' ');   // Display one space
			LCD_intgerToString(distance); // Convert and display distance
		}
		// Case 3: Distance 100 cm or more
		else{
			LCD_moveCursor(0,10);
			LCD_intgerToString(distance); // Convert and display distance
		}

		LCD_displayString("cm"); // Display "cm" unit

	}

	return 0;
}
