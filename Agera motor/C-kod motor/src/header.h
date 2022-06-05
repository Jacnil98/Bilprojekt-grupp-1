#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define BUTTON 1 //startknapp
#define BUTTON_IS_PRESSED (PINB & (1<<BUTTON)) //avläsning av startknapp

#define MOTOR 5
#define MOTOR_ON PORTD |= (1<<MOTOR)
#define MOTOR_OFF PORTD &= ~(1<<MOTOR)

#define CONNECTION 6 //koppling mellan båda arduinos för backfunktion
#define CONNECTION_ON PORTD |= (1<<CONNECTION)
#define CONNECTION_OFF PORTD &= ~(1<<CONNECTION)

#define MOTOR_DIRECTION1 7
#define MOTOR_DIRECTION2 0

#define SENSOR 1 

#define MAX_DISTANCE 80.0
#define MIN_DISTANCE 50.0

#define ADC_MAX 1023
#define TOTAL_INTERRUPTS 500
#define PERIOD 4
#define INTERRUPT_TIME 0.000125

#define TOTAL_REVERSE_INTERRUPTS 400 //4.8s
#define INTERRUPTS_REQUIRED_FOR_REVERSE 150 //2.4s
#define REVERSE_INTERRUPT_TIME 0.016f

void setup();
uint32_t ADC_read();
uint16_t Calculate_distance();

void timer_on();
void timer_disable();
bool timer_elapsed();
void reverse_timer_on();
void reverse_timer_off();
bool reverse_timer_elapsed();
bool start_reversing();
bool duty_cycle_elapsed();
void get_new_duty_cycle();
void reverse_timer_on();
void reverse_timer_off();

void motor_toggle();
void motor_forward();
void motor_backwards();
void motor_enable();
void motor_disable();

void switch_pwm_mode();
void check_start_button();

void serial_print(const char* s); // Funktion för seriell överföring.
void serial_print_int(const char* s, const int number);

bool motor_enabled;
bool timer_enabled;
bool reverse_timer_enabled;
bool motor_reverse;
typedef enum {ON = 1, OFF = 0} period;

#endif /* HEADER_H_ */