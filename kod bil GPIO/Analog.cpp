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

double Analog::duty_cycle(void)
{
	double in_signal = read();
	double calculated_value = in_signal * 0.0048828125;
	double distance_in_cm = 29.988*(pow(calculated_value, -1.173));
	if(distance_in_cm > MAX_SPEED) distance_in_cm = MAX_SPEED;
	else if (distance_in_cm < MIN_SPEED) distance_in_cm = MIN_SPEED;
	double distance = (distance_in_cm * SPEED_SCALE) / ADC_MAX; // Tolv kan variera f�r att f� �nskat v�rde.
	//Serial::print(distance);
	//Serial::print("\n");
	return distance;
}