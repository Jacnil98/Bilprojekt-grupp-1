#include "header.h"

uint32_t ADC_read()
{
	ADMUX = ((1 << REFS0) | SENSOR);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}

uint16_t Calculate_distance()
{
    float in_signal = ADC_read() * 0.0048828125;
    double distance_in_cm = 29.988*(pow(in_signal, -1.173));

    if(distance_in_cm >= MAX_DISTANCE)
    { 
        distance_in_cm = MAX_DISTANCE;
    }
    else if(distance_in_cm <= MIN_DISTANCE)
    {
        distance_in_cm = MIN_DISTANCE;
    }
    return distance_in_cm;
}