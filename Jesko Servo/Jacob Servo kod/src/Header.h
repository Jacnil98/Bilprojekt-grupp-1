#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "PID_Controller.h"

#define SENSOR_RIGHT 0 //Byt pin
#define SENSOR_LEFT 1 //Byt pin

#define SERVO_PIN 6 //Vilken pin
#define SERVO_ON PORTD |= (1 << SERVO_PIN)
#define SERVO_OFF PORTD &= ~(1 << SERVO_PIN)

#define MAX_DISTANCE 80.0
#define MIN_DISTANCE 10.0

#define CONNECTION 1 
#define CONNECTION_ACTIVE (PINB & (1 << 1))

#define ADC_MAX 1023
#define PERIOD 4
#define INTERRUPT_TIME 0.008f

void setup();
uint32_t ADC_read(const uint8_t PIN);
uint16_t Calculate_distance(const uint8_t PIN);

void serial_print(const char* s);
void serial_print_int(const char* s, const int number);

void servo_enable();
void motor_disable();

void timer_on();
void timer_disable();
bool timer_elapsed();
bool duty_cycle_elapsed();

void PID_print();

bool servo_enabled;
bool timer_enabled;

#endif /* HEADER_H_ */