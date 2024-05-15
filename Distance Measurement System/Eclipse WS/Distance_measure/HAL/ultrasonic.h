/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the Ultrasonic Sensor driver
 *
 * Author: Diaa Abossrie
 *
 ******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

// Including necessary header files
#include "../LIB/std_types.h"

// Define pin configurations for trigger and echo pins
#define TRIGGER_PORT_ID PORTB_ID
#define TRIGGER_PIN_ID PIN5_ID

#define ECHO_PORT_ID PORTD_ID
#define ECHO_PIN_ID PIN6_ID

// Function prototypes
void Ultrasonic_init(void);  // Initializes ultrasonic sensor
void Ultrasonic_Trigger(void);  // Triggers the ultrasonic sensor
uint16 Ultrasonic_readDistance(void);  // Reads distance from the sensor
void Ultrasonic_edgeProcessing(void);  // Handles edge detection for capturing time

#endif /* ULTRASONIC_H_ */
