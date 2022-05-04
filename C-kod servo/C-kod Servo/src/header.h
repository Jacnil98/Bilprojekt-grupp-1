#ifndef _HEADER_H_
#define _HEADER_H_

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

#define SERVO_PIN 
#define TOTAL_INTERRUPTS 90 //Vad ska denna vara?

void setup();

void servo_enable();
void servo_disable();
void switch_servo_mode();
bool servo_enabled;

typedef enum {ON = 0, OFF = 1} period;
period servo_period;

uint16_t required_interrupts;
volatile uint16_t executed_interrupts;


#endif /* HEADER_H_ */