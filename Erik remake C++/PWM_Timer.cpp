#include "PWM_Timer.h"

PWM_Timer::PWM_Timer(const TimerSelection timerSelection, const double period, const uint8_t pot_PIN)
{
	this->timerSelection = timerSelection;
	this->total_amount_of_interrupts = this->get_required_interrupts(period);
	this->pot = Pot(pot_PIN);
	this->init(this->timerSelection);
	this->required_interrupts = this->pot.get_interrupts_on_time(this->total_amount_of_interrupts);
	
	return;
}

void PWM_Timer::switch_mode(void)
{
	if (this->pwm_period == PWM_Period::On)
	{
		this->required_interrupts = this->total_amount_of_interrupts - this->executed_interrupts;
		this->pwm_period = PWM_Period::Off;
	}
	
	else
	{
		this->required_interrupts = pot.get_interrupts_on_time(this->total_amount_of_interrupts);
		this->pwm_period = PWM_Period::On;
	}
	
	return;
}