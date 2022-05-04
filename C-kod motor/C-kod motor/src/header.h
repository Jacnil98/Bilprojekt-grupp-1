#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define BUTTON 1 
#define BUTTON_IS_PRESSED (PINB & (1<<BUTTON))

#define MOTOR 5
#define MOTOR_ON PORTD |= (1<<MOTOR) //port d pin 5
#define MOTOR_OFF PORTD &= ~(1<<MOTOR)

#define MOTOR_DIRECTION1 7
#define MOTOR_DIRECTION2 8

#define SENSOR 1

#define MAX_DISTANCE 80.0
#define MIN_DISTANCE 10.0

#define ADC_MAX 1023
#define TOTAL_INTERRUPTS 625
#define PERIOD 4
#define INTERRUPT_TIME 0.009f

void setup();
uint32_t ADC_read();
uint16_t Calculate_distance();

void timer_on();
void timer_disable();
bool timer_elapsed();
bool duty_cycle_elapsed();
//void timer_count();

void motor_toggle();
void motor_forward();
void motor_backwards();
void switch_pwm_mode();

void serial_print(const char* s); // Funktion för seriell överföring.
void serial_print_int(const char* s, const int number);

bool motor_enabled = false;
bool timer_enabled = false;

typedef enum {ON = 1, OFF = 0} period;




//motor
#endif /* HEADER_H_ */