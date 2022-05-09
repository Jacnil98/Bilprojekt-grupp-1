#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define BUTTON 5
#define BUTTON_IS_PRESSED (PIND & (1<<BUTTON))

#define MOTOR 1
#define MOTOR_ON PORTB |= (1<<MOTOR) //port d pin 5
#define MOTOR_OFF PORTB &= ~(1<<MOTOR)

#define MOTOR_DIRECTION1 0
#define MOTOR_DIRECTION2 3 

#define SENSOR 1

#define MAX_DISTANCE 80.0
#define MIN_DISTANCE 10.0

#define ADC_MAX 1023
#define TOTAL_INTERRUPTS 625
#define PERIOD 4
#define INTERRUPT_TIME 0.008f

void setup();
uint32_t ADC_read();
uint16_t Calculate_distance();

void timer_on();
void timer_disable();
bool timer_elapsed();
bool duty_cycle_elapsed();
void get_new_duty_cycle();
//void timer_count();

void motor_toggle();
void motor_forward();
void motor_backwards();
void switch_pwm_mode();

void serial_print(const char* s); // Funktion för seriell överföring.
void serial_print_int(const char* s, const int number);

bool motor_enabled;
bool timer_enabled;

typedef enum {ON = 1, OFF = 0} period;


//motor
#endif /* HEADER_H_ */