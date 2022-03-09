#include "header.h"

static uint32_t ADC_read();
static void delay( uint32_t delay_time);
static void init_ADC();

void Setup()
{
	DDRD = (1 << SERVO);
	init_ADC();
}

void PWM()
{
	const uint16_t ADC_result = ADC_read(POT);    // 1024
	const float duty_cycle = (float)ADC_result / (ADC_MAX); // 0-1024/1024 = värde mellan 0 och 1
	const uint32_t on_time = (float)((duty_cycle * PERIOD)* 100) / 100; // 0-1* 3= värde mellan 0-3
	const uint32_t off_time = PERIOD-on_time;
	
	SERVO_ON;
	delay(on_time);
	SERVO_OFF;
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

static void delay( uint32_t delay_time)
{
	if (delay_time < 70)
	{
		delay_time =  70;
	}
	else if (delay_time > 150)
	{
		delay_time=  150;
	}
	for (uint32_t i = 0; i < delay_time; i++)
	_delay_us(10);
	return;
}

static void init_ADC()
{
	ADMUX = (1 << REFS0);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return;
}
/*
const uint32_t ADC_result = ADC_read(POT);
const float duty_cycle = (float)ADC_result / ADC_MAX;
const float on_time = (roundf)((duty_cycle * PERIOD)* 100) / 100;
const float off_time = PERIOD - on_time;  */