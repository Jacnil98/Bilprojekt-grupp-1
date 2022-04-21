#include "header.h"

ISR (PCINT0_vect)
{
	
	if (button.is_pressed()) 
	{
		Serial::print("\n Button is pressed: ");
		motor.toggle();
		servo.enable();
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
	if(servo.elapsed())
	{
		servo.switch_servo_mode();
		sensor.set_input(const double left_sensor, const double right_sensor);
		sensor.regulate();
		servo.toggle_PWM();
	}
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