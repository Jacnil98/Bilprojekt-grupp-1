#include "GPIO.h"
#include "Serial.h"
Analog::Analog(const uint8_t PIN)
{
	if (PIN >= 0 && PIN <= 5)
		this->PIN = PIN;
	else
		this->PIN = 0xFF;
	this->init();
	return;
}

void Analog::init(void)
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
	Serial::print("\n init ADC: ");
	return;
}

uint16_t Analog::read(void)
{
	ADMUX = (1 << REFS0) | this->PIN;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
	return ADC;
}

uint16_t Analog::calculate(void)
{
	float in_signal = read();
	float calculated_value = in_signal * 0.0048828125;
	uint16_t distance_in_cm = 29.988*(pow(calculated_value, -1.173));
	uint16_t distance = distance_in_cm * 12; // Tolv kan variera för att få önskat värde.
	return distance;
}