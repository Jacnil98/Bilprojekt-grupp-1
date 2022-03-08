#include "header.h"

int main()
{
    while (true) 
    {
		float volts = ADC*0.0048828125;
		int distance = 13*pow(volts, -1);
		serial_print_int(distance);
	}
	return;
}

uint32_t ADC_read()
{
	ADMUX = ((1 << REFS0) | sensor);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}

