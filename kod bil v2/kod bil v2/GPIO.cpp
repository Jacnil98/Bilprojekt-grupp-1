#include "GPIO.h"

Motor motor;
Button button;
Sensor sensor;
PWM_Timer pwm_timer;

void init_GPIO()
{
	button = start_Button(9);
	button.enable_interrupt();
	motor = pwm_motor(5);
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