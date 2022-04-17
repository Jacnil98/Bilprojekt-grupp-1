
#ifndef PWM_TIMER_H_
#define PWM_TIMER_H_

#include "definitions.h"
#include "Timer.h"
#include "Pot.h"

class PWM_Timer : public Timer
{
protected:
	volatile uint32_t total_amount_of_interrupts = 0x00;
	double period = 0x00;
	PWM_Period pwm_period = PWM_Period::On;
	Pot pot;
public:
	PWM_Timer(void) { }
	PWM_Timer(const TimerSelection timerSelection, const double period, const uint8_t pot_PIN);
	~PWM_Timer(void) { }
	void switch_mode(void);
};


#endif /* PWM_TIMER_H_ */