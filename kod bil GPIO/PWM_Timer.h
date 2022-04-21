
#ifndef PWM_TIMER_H_
#define PWM_TIMER_H_

#include "definitions.h"
#include "Timer.h"
#include "GPIO.h"

class PWM_Timer : public Timer
{
protected:
	volatile uint32_t total_amount_of_interrupts = 0x00;
	double period = 0x00;
	PWM_Period pwm_period = PWM_Period::Off;
	PWM_Period servo_period = PWM_Period::Off;
	Analog analog;
public:
	PWM_Timer(void) { }
	PWM_Timer(const TimerSelection timerSelection, const double period, const uint8_t pot_PIN);
	PWM_Timer(const TimerSelection timerSelection, const double period);
	~PWM_Timer(void) { }
	void switch_mode(void);
	void switch_servo_mode(const double output);
};


#endif /* PWM_TIMER_H_ */