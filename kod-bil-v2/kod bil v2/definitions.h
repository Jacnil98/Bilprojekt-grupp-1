#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

enum class IO_port {NONE, B, C, D};
enum class TimerSelection { TIMER0, TIMER1, TIMER2, NONE };

#define ASSIGN(REGISTER, BIT) REGISTER = (1<<BIT)
#define SET(REGISTER, BIT) REGISTER |= (1<< BIT)
#define CLEAR(REGISTER, BIT) REGISTER &= !(1<<BIT)
#define READ(REGISTER, BIT) (REGISTER & (1<<BIT))


#endif /* DEFINITIONS_H_ */