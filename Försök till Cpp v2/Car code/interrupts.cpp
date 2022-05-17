#include "header.h"

ISR (PCINT0_vect)
{
	
	if (button.is_pressed()) 
	{
		motor.toggle();
		Serial::print("\n Button is pressed: ");
	}
	
	return;
}



ISR (TIMER1_COMPA_vect)
{
	if(servo.elapsed())
	{
		Serial::print("see this");
		servo.regulate(); // REGLERING SKER INNAN VI BYTER SERVO MODE!
		servo.switch_servo_mode();
		servo.toggle_PWM();
	}
	return;
}

ISR (TIMER2_OVF_vect)
{
	/*
	//Serial::print("\n interrupt OVF Timer 2: ");
	if (motor.elapsed())
	{
		//Serial::print("\n interrupts OVF elapsed Timer 2: ");
		motor.switch_mode();
		motor.toggle_PWM();
	}
	*/
	return;
}