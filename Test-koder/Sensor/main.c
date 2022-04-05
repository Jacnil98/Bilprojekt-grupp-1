#include "header.h"

int main()
{
	init_serial();
    while (true) 
    {
		_delay_ms(200);
		float in_signal = ADC_read(SENSOR)*0.0048828125; // = 5/1023
		//float in_signal = ADC_read(SENSOR)*(5.0/1023); //viktigt med 5.0 annars så blir det int division.
		int distance = 13*(1/in_signal); //13*pow(in_signal, -1) läst från datablad 13/in_signal; 
		//int distance = 13*pow(in_signal, -1); //13*pow(in_signal, -1) läst från datablad 13/in_signal; alt 13*(1/in_signal)

		serial_print_int(distance);
		serial_print_int(in_signal);
		/*
		if (distance >= 10 && <= 30)
			{
				serial_print_int(distance)
			}
		if (distance >= 35)
			{	
				fault_code = true;
			}
		if (distance <= 10)
			{
				close_to_wall = true;
			}
		*/
		
	}
	return 0;
}

uint32_t ADC_read()
{
	ADMUX = ((1 << REFS0) | SENSOR);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}

void init_serial()
{
	UCSR0B = (1 << TXEN0); //ENABLE_SERIAL_TRANSFER;
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));//SET_TRANSMISSION_SIZE;
	UBRR0 = 103;//SET_BAUD_RATE_9600_KBPS;
	return;
}