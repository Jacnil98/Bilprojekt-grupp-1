#include "GPIO.h"

Motor motor;
<<<<<<< HEAD
Button button;
=======
Sensor sensor;
>>>>>>> 282972ae78f3b3024595f3273302eddf98d9fb35

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
