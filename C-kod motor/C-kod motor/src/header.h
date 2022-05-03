#ifndef HEADER_H_
#define HEADER_H_
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdio.h>
#define BUTTON 9

typedef enum {TRUE = 1, FALSE = 0} boolean; 

uint32_t ADC_read();


#endif /* HEADER_H_ */