#include "GPIO.h"

Button button;
Motor motor;

void init_GPIO() 
{ 
	 button = start_Button(13); 
	 motor = pwm_motor(5);
	 return;
}

Button start_Button(const uint8_t PIN)
{ 
	Button self(PIN); 
	return self; 
}

Motor pwm_motor(const uint8_t PIN)
{
	Motor self(PIN);
	return self;
}