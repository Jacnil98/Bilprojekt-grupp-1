#include "PWM_Timer.h"
#include "Motor.h"
#include "Serial.h"

PWM_Timer::PWM_Timer(const TimerSelection timerSelection, const double period, const uint8_t pot_PIN)
{
	Serial::init();
	this->timerSelection = timerSelection;
	this->total_amount_of_interrupts = this->get_required_interrupts(period);
	this->analog = Analog(pot_PIN);
	this->init(this->timerSelection);
	this->enabled = false;
	this->executed_interrupts = 0x00;
	this->required_interrupts = this->analog.get_interrupts_on_time(this->total_amount_of_interrupts);
	Serial::print("\nRequired interrutps (construct): "); Serial::print(this->required_interrupts);
	return;
}

void PWM_Timer::switch_mode(void)
{
	if (this->pwm_period == PWM_Period::On)
	{
		this->required_interrupts = this->total_amount_of_interrupts - this->executed_interrupts;
		this->pwm_period = PWM_Period::Off;
		//Serial::print("\n switched pwm mode to off: ");
	}
	
	else
	{
		this->required_interrupts = analog.get_interrupts_on_time(this->total_amount_of_interrupts);
		this->pwm_period = PWM_Period::On;
		//Serial::print("\n switched pwm mode to on: ");
	}
	
	return;
}