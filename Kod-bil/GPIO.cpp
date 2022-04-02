#include "GPIO.h"

Sensor sensor;
Motor motor;
Button button;

void init_GPIO() 
{ 
	 button = start_Button(13); 
	 button.enable_interrupt();
	 motor = pwm_motor(5);
	 sensor = new_Sensor(0);
	 motor.enable_interrupt();
	 DDRD |= ((1<<IN1)|(1<<IN2));
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

USART_Timer new_USART_Timer(const uint16_t delay) 
{ 
	USART_Timer self(delay); 
	return self; 
}

Sensor new_Sensor(const uint8_t PIN)
{
	Sensor self(PIN);
	return self;
}