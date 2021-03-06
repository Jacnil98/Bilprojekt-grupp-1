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

Sensor::Sensor(const uint8_t PIN,const double targett, const double Kp, const double Ki, const double Kd)
{
	this->PIN = PIN;
	this->targett = targett;
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	this->output_min = OUTPUT_MIN;
	this->output_max = OUTPUT_MAX;
	return;
}

void Sensor::set_input(const uint8_t left_PIN, const uint8_t right_PIN)
{
	uint16_t left_sensor_in = GPIO::ADC_read(left_PIN);
	float in_signal_left = left_sensor_in * 0.0048828125;
	uint16_t left_distance_in_cm = 29.988*(pow(in_signal_left,-1.173));
	this->left_sensor_input = left_distance_in_cm;
	if(left_sensor_input > SENSOR_MAX) left_sensor_input = 80;
	
	uint16_t right_sensor_in = GPIO::ADC_read(right_PIN);
	float in_signal_right = right_sensor_in * 0.0048828125;
	uint16_t right_distance_in_cm = 29.988*(pow(in_signal_right,-1.173));
	this->right_sensor_input = right_distance_in_cm;
	if(right_sensor_input > SENSOR_MAX) right_sensor_input = 80;
	
	this->map();
	this->actual_value = this->targett + this->mapped_left_sensor_input - this->mapped_right_sensor_input; //this->actual_value = this->target + this->mapped_left_sensor_input - this->mapped_right_sensor_input;
	serial_print("-----------------------------------\n");
	serial_print("first function\n");
	serial_print_int(mapped_right_sensor_input);
	serial_print_int(mapped_left_sensor_input);
	serial_print_int(targett);
	serial_print_int(actual_value);
	serial_print("\n-----------------------------------\n\n");
	return ;
}

/*
void Sensor::set_input(const uint8_t left_PIN, const uint8_t right_PIN)
{
	this->left_sensor_input = GPIO::ADC_read(left_PIN);
	this->right_sensor_input = GPIO::ADC_read(right_PIN);
	serial_print_int(right_PIN);
	serial_print_int(left_PIN);
	this->map();
	this->actual_value = this->target + this->mapped_left_sensor_input - this->mapped_right_sensor_input;
	
	return ;
}
*/

uint16_t Sensor::calculate()
{
	//uint16_t distance = distance_in_cm * 12;
	//float in_signal = GPIO::ADC_read(this->PIN)*0.0048828125;
	float in_signal1 = GPIO::ADC_read(this->PIN);
	float in_signal = in_signal1 * 0.0048828125;
	uint16_t distance_in_cm = 29.988*(pow(in_signal,-1.173)); //13*(1/insignal) f?r 4-30 cm elr 13*pow(in_signal, -1)
	uint16_t distance = distance_in_cm * 12;
	if (distance >=800) distance = 800;
	else if (distance <=100) distance = 100;
	return distance;
}
/*
uint16_t Sensor::servo_position()
{
	//input v?rde mellan 0-180 f?r att h?r g?ras om till en frekvens mellan 1000-2000
	uint16_t right_distance = this->get_sensor_input(const uint8_t servo.right_sensor_PIN);
	uint16_t left_distance = this->get_sensor_input(const uint8_t servo.left_sensor_PIN);
	int16_t savox_position = (left_distance - right_distance);
	// Mappa v?rdena s? att det blir l?mpligt f?r grader.
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