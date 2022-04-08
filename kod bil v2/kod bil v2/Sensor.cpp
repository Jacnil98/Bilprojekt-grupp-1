#include "GPIO.h"

Sensor::Sensor(const uint8_t PIN)
{
	this->PIN = PIN;
}

uint16_t Sensor::calculate()
{
	//float in_signal = GPIO::ADC_read(this->PIN)*0.0048828125;
	float in_signal1 = GPIO::ADC_read(motor.get_sensor_PIN());
	float in_signal = in_signal1 * 0.0048828125;
	uint16_t distance_in_cm = 13*(1/in_signal);
	uint16_t distance = distance_in_cm * 30;
	if (distance >=900) distance = 900;
	else if (distance <=200) distance =200;
	return distance;
}