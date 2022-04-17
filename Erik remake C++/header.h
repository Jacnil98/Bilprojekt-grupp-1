

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

static Led led(9);
static Button button(13);
static Timer timer0(TimerSelection::Timer0, 300);
static Timer timer1(TimerSelection::Timer1, 500);
static PWM_Timer pwm_timer(TimerSelection::Timer2, 1, 0);

#endif /* HEADER_H_ */