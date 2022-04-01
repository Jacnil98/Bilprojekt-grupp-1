#include "GPIO.h"

Button button;
Motor motor;
Sensor sensor;

void init_GPIO() 
{ 
	 button = start_Button(13); 
	 motor = pwm_motor(5);
	 sensor = new_sensor(1); // A0
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

Sensor new_sensor(const uint8_t PIN)
{
	Sensor self(PIN);
	return self;
}
