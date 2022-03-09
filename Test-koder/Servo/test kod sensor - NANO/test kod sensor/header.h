
#ifndef HEADER_H_
#define HEADER_H_

#define F_CPU 20000000UL

#include <avr/io.h>
#include <util/delay.h>

#define SERVO 6
#define SERVO_ON PORTD |= (1 << SERVO)
#define SERVO_OFF PORTD &= ~(1 << SERVO)
#define POT 1


#define ADC_MAX 1024
#define PERIOD 300

typedef enum {true = 1, false = 0} bool;

bool servo_enabled;

void PWM();
void Setup();

#endif /* HEADER_H_ */