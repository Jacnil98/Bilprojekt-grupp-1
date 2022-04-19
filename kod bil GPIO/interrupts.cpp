#include "header.h"

ISR (PCINT0_vect)
{
	
	if (button.is_pressed()) 
	{
		Serial::print("\n Button is pressed: ");
		motor.toggle();
	}
	
	return;
}

ISR (TIMER0_OVF_vect)
{
	/*if (timer1.elapsed())
	{
		Serial::print("\ninterrupts elapsed    0: ");
		button.enable_interrupt();
	}
	*/
	return;
}

ISR (TIMER1_COMPA_vect)
{
	/*
	if (timer1.elapsed())
	Serial::print("\n interrupts elapsed   1: ");
		output.toggle();
		*/
	return;
}

ISR (TIMER2_OVF_vect)
{
	//Serial::print("\n interrupt OVF Timer 2: ");
	if (motor.elapsed())
	{
		//Serial::print("\n interrupts OVF elapsed Timer 2: ");
		motor.switch_mode();
		motor.toggle_PWM();
	}
	
	return;
}