#include "Pot.h"

Pot::Pot(const uint8_t PIN)
{
	if (PIN >= 0 && PIN <= 5)
		this->PIN = PIN;
	else
		this->PIN = 0xFF;
	this->init();
	return;
}

void Pot::init(void)
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
	return;
}

uint16_t Pot::read(void)
{
	ADMUX = (1 << REFS0) | this->PIN;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
	return ADC;
}