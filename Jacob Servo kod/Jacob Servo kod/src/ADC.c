#include "Header.h"

uint32_t ADC_read(const uint8_t PIN)
{
	ADMUX = ((1 << REFS0) | PIN);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}

uint16_t Calculate_distance(const uint8_t PIN)
{
    float in_signal = ADC_read(PIN) * 0.0048828125;
    uint16_t distance_in_cm = 29.988*(pow(in_signal, -1.173));
    uint16_t on_time_interrupts = distance_in_cm * 13;
    //serial_print_int("%d\n", distance_in_cm);
    //serial_print("ADC");
    //serial_print_int("%d\n", on_time_interrupts);
    return on_time_interrupts;
}