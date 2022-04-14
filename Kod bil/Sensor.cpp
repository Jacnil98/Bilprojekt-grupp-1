#include "GPIO.h"

Sensor::Sensor(const uint8_t PIN)
{
	this->PIN = PIN;
}

void Sensor::map(void)
{
	this->mapped_left_sensor_input = this->left_sensor_input / SENSOR_MAX * TARGET;
	this->mapped_right_sensor_input = this->right_sensor_input / SENSOR_MAX * TARGET;
}

double Sensor::check_sensor_input(const double sensor_input)
{
	if (sensor_input < SENSOR_MIN) return SENSOR_MIN;
	else if (sensor_input > SENSOR_MAX) return SENSOR_MAX;
	return sensor_input;
}

Sensor::Sensor(const uint8_t PIN,const double target, const double Kp, const double Ki, const double Kd)
{
	this->PIN = PIN;
	this->target = target;
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	this->output_min = OUTPUT_MIN;
	this->output_max = OUTPUT_MAX;
	return;
}

void Sensor::set_input(const uint8_t left_PIN, const uint8_t right_PIN)
{
	this->left_sensor_input = GPIO::ADC_read(left_PIN);
	this->right_sensor_input = GPIO::ADC_read(right_PIN);
	this->map();
	this->actual_value = this->target + this->mapped_left_sensor_input - this->mapped_right_sensor_input;
	return ;
}
/*
void Sensor::set_input(void)
{
	
	return;
}

void Sensor::print();
{
	return;
}*/

uint16_t Sensor::calculate()
{
	//uint16_t distance = distance_in_cm * 12;
	//float in_signal = GPIO::ADC_read(this->PIN)*0.0048828125;
	float in_signal1 = GPIO::ADC_read(this->PIN);
	float in_signal = in_signal1 * 0.0048828125;
	uint16_t distance_in_cm = 29.988*(pow(in_signal,-1.173)); //13*(1/insignal) för 4-30 cm elr 13*pow(in_signal, -1)
	uint16_t distance = distance_in_cm * 12;
	if (distance >=800) distance = 800;
	else if (distance <=100) distance = 100;
	return distance;
}
/*
uint16_t Sensor::servo_position()
{
	//input värde mellan 0-180 för att här göras om till en frekvens mellan 1000-2000
	uint16_t right_distance = this->get_sensor_input(const uint8_t servo.right_sensor_PIN);
	uint16_t left_distance = this->get_sensor_input(const uint8_t servo.left_sensor_PIN);
	int16_t savox_position = (left_distance - right_distance);
	// Mappa värdena så att det blir lämpligt för grader.
	// actual_value = target - mapped_savox_position.
	// Reglerra med PID.
	return savox_position;
}

uint16_t Sensor::get_sensor_input(const uint8_t PIN)
{
	float in_signal_right = GPIO::ADC_read(const uint8_t PIN);
	float in_signal = in_signal_right * 0.0048828125;
	uint16_t distance = 13*(1/in_signal);
	return distance;
}
*/