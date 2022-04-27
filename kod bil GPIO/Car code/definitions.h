#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

enum class IO_port { B, C, D, None };
enum class TimerSelection { Timer0, Timer1, Timer2, None };
enum class PWM_Period { On, Off };
enum class MotorDirection { Forward, Backward };

#endif /* DEFINITIONS_H_ */