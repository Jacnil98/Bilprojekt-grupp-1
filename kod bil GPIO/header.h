
#ifndef HEADER_H_
#define HEADER_H_

#include "definitions.h"
#include "Led.h"
#include "Button.h"
#include "Timer.h"
#include "Serial.h"
#include "PWM_Timer.h"
#include "PID_Controller.h"
#include "Sensor.h"
#include "Motor.h"
#include "Servo.h"



static Output output(4); //oanv�nd
static Button button(9);
//static Timer timer0(TimerSelection::Timer0, 300);
//static Timer timer1(TimerSelection::Timer1, 500);
static Motor motor(7, 8, 5, TimerSelection::Timer2, 10, 1);
static Sensor sensor(0, 2, 90, 1, 0.01, 0.1, 30, 150);
static Servo servo(6, TimerSelection::Timer1, 20);
#endif /* HEADER_H_ */

//pin 3 anv�nds inte