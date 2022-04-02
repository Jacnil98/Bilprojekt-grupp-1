#include "GPIO.h"

Sensor::Sensor(const uint8_t PIN)
{
	this->PIN = PIN;
	uint8_t sensor_PIN = PIN;
}

uint16_t Sensor::calculate()
{
	float in_signal = GPIO::ADC_read(this->PIN)*(5/1023);
	uint16_t distance = 13*(1/in_signal);
	return distance;
}