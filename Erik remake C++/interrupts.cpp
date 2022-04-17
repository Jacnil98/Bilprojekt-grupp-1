#include "header.h"

ISR (PCINT0_vect)
{
	button.disable_interrupt();
	timer0.on();
	
	if (button.is_pressed())
	{
		timer1.toggle();
		
		if (!timer1.is_enabled())
			led.off();
	}
	return;
}

ISR (TIMER0_OVF_vect)
{
	if (timer1.elapsed())
	{
		timer0.off();
		button.enable_interrupt();
	}
	
	return;
}

ISR (TIMER1_COMPA_vect)
{
	if (timer1.elapsed())
		led.toggle();
	return;
}

ISR (TIMER2_OVF_vect)
{
	if (pwm_timer.elapsed())
	{
		pwm_timer.switch_mode();
		led.toggle();
	}
	
	return;
}