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
	uint16_t distance = distance_in_cm * 12;
	if (distance >=800) distance = 800;
	else if (distance <=100) distance =100;
	return distance;
}

uint16_t Sensor::servo_position()
{
	uint16_t right_distance = this->get_sensor_input(const uint8_t servo.right_sensor_PIN);
	uint16_t left_distance = this->get_sensor_input(const uint8_t servo.left_sensor_PIN);
	int16_t savox_position = (left_distance - right_distance);
	// Mappa värdena så att det blir lämpligt för grader.
	// actual_value = target - mapped_savox_position.
	// Reglerra med PID.
	
}


uint16_t Sensor::get_sensor_input(const uint8_t PIN)
{
	float in_signal_right = GPIO::ADC_read(const uint8_t PIN);
	float in_signal = in_signal_right * 0.0048828125;
	uint16_t distance = 13*(1/in_signal);
	return distance;
}