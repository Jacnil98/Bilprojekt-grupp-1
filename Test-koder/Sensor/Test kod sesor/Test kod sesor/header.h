#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#include <math.h>

#define sensor 0

typedef enum {true = 1, false = 0} bool;

void serial_print(const char* s); // Funktion för seriell överföring.
uint32_t ADC_read();

#endif /* HEADER_H_ */