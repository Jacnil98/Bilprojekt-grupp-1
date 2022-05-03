#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define BUTTON 9
#define BUTTON_IS_PRESSED (PINB & (1<<BUTTON))

#define MOTOR 5
#define MOTOR_ON PORTB |= (1<<MOTOR) //port b pin 5
#define MOTOR_OFF PORTB &= ~(1<<MOTOR)

#define MOTOR_DIRECTION1 7
#define MOTOR_DIRECTION2 8

#define SENSOR 1

#define MAX_DISTANCE 80.0
#define MIN_DISTANCE 10.0

#define ADC_MAX 1023
#define PERIOD 10
#define INTERRUPT_TIME 0.016f

typedef enum {TRUE = 1, FALSE = 0} boolean;

void setup();
uint32_t ADC_read();
uint16_t Calculate_distance();

void timer_enable();
void timer_disable();

void motor_toggle();
void motor_forward();
void motor_backwards();

boolean timer_enabled;
boolean motor_enabled;
uint32_t required_interrupts; //Vad ska detta vara?

//motor
#endif /* HEADER_H_ */