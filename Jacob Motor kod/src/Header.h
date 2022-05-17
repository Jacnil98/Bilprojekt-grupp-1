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

#define CONNECTION 6
#define CONNECTION_ON PORTD |= (1<<CONNECTION)
#define CONNECTION_OFF PORTD &= ~(1<<CONNECTION)

#define MOTOR_DIRECTION1 0
#define MOTOR_DIRECTION2 3

#define SENSOR 1

#define MAX_DISTANCE 80.0
#define MIN_DISTANCE 60.0

#define ADC_MAX 1023
#define TOTAL_INTERRUPTS 625
#define PERIOD 4
#define INTERRUPT_TIME 0.008

#define TOTAL_REVERSE_INTERRUPTS 400 //4.8s
#define INTERRUPTS_REQUIRED_FOR_REVERSE 150 //2.4s
#define REVERSE_INTERRUPT_TIME 0.016f

void setup();
uint32_t ADC_read();
uint16_t Calculate_distance();

void timer1_on();
void timer1_disable();
bool timer1_elapsed();
bool duty_cycle_elapsed1();
void get_new_duty_cycle1();
//void timer_count();

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
void switch_pwm_mode();
void check_start_button();

void serial_print(const char* s); // Funktion för seriell överföring.
void serial_print_int(const char* s, const int number);

bool motor_enabled;
bool timer1_enabled;
bool reverse_timer_enabled;
bool motor_reverse;

typedef enum {ON = 1, OFF = 0} period;

//motor
#endif /* HEADER_H_ */