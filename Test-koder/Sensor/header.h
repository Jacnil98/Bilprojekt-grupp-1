#ifndef HEADER_H_
#define HEADER_H_

#define F_CPU 20000000UL

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>

#define SENSOR 0 // 2= A2

typedef enum {true = 1, false = 0} bool;

void serial_print(const char* s); // Funktion för seriell överföring.
void serial_print_int(const int number);
void init_serial();

uint32_t ADC_read();

#endif /* HEADER_H_ */