#include "header.h"

/**************************************************************************
 * ADC-read läser av de två sensorerna på sidan och återger ett värde mellan 
 * 0-5v som omvandlas till ett digitalt värde mellan 0-1023.
**************************************************************************/
uint32_t ADC_read(const uint8_t PIN)
{
	ADMUX = ((1 << REFS0) | PIN);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}

/**************************************************************************
 * calculate distance omvandlar värdet från ADC read och med en beräkning
 * lämnar ett värde mellan 10 och 80cm, detta multipliceras sedan med 13 för
 * att kunna användas med pwm timern. 
**************************************************************************/
uint16_t Calculate_distance(const uint8_t PIN)
{
    float in_signal = ADC_read(PIN) * 0.0048828125;
    uint16_t distance_in_cm = 29.988*(pow(in_signal, -1.173));
    uint16_t on_time_interrupts = distance_in_cm * 13;
    return on_time_interrupts;
}