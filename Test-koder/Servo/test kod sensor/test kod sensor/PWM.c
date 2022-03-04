#include "header.h"

static uint32_t ADC_read();
static void delay(const uint32_t delay_time);

void Setup()
{
	DDRD = (1 << SERVO);
}

void PWM()
{
	const uint32_t ADC_result = ADC_read();
	const float duty_cycle = (float)ADC_result / ADC_MAX;
	const float on_time = (roundf)((duty_cycle * PERIOD)* 10) / 10;
	const float off_time = PERIOD - on_time;
	
	if(servo_enabled) SERVO_ON;
	delay(on_time);
	if(servo_enabled) SERVO_OFF;
	delay(off_time);
	return;
}

static uint32_t ADC_read()
{
	ADMUX = ((1 << REFS0) | POT);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}

static void delay(const uint32_t delay_time)
{
	for (int i = 0; i < delay_time; i++)
	_delay_ms(1);
	return;
}