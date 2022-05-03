#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define BUTTON 9
#define BUTTON_IS_PRESSED (PINB & (1<<BUTTON))

#define MOTOR 5
#define MOTOR_ON PORTB |= (1<<MOTOR) //port b pin 5
#define MOTOR_OFF PORTB &= ~(1<<MOTOR)

#define MOTOR_DIRECTION1 7
#define MOTOR_DIRECTION2 8

#define SENSOR 1

#define MAX_DISTANCE 625.0
#define MIN_DISTANCE 10.0

#define ADC_MAX 1023
#define TOTAL_INTERRUPTS 625
#define PERIOD 10
#define INTERRUPT_TIME 0.016f

void setup();
uint32_t ADC_read();
uint16_t Calculate_distance();

void timer_enable();
void timer_disable();
bool timer_elapsed();

void motor_toggle();
void motor_forward();
void motor_backwards();
void switch_servo_mode();

bool motor_enabled;
bool timer_enabled;

typedef enum {ON = 0, OFF = 1} period;
period current_period;
uint16_t required_interrupts;
volatile uint16_t executed_interrupts;

//motor
#endif /* HEADER_H_ */