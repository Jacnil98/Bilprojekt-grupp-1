#include "Sensor.h"
#include "Serial.h"

double Sensor::check_input(const double input)
{
	if (input > this->SENSOR_MAX)
		return this->SENSOR_MAX;
	else if (input < this->SENSOR_MIN)
		return this->SENSOR_MIN;
	return input;
}

void Sensor::map(void)
{
	this->mapped_left_input = this->left_input * (this->map_value / this->SENSOR_MAX);
	this->mapped_right_input = this->right_input * (this->map_value / this->SENSOR_MAX);
	return;
}

Sensor::Sensor(const uint8_t left_PIN, const uint8_t right_PIN, const double target,
	const double Kp, const double Ki, const double Kd)
{
	this->left_sensor = Analog(left_PIN);
	this->right_sensor = Analog(right_PIN);
	this->set_target(target);
	this->set_parameters(Kp, Ki, Kd);
	return;
}

Sensor::Sensor(const uint8_t left_PIN, const uint8_t right_PIN, const double target,
	const double Kp, const double Ki, const double Kd, const double output_min, const double output_max)
{
	this->left_sensor = Analog(left_PIN);
	this->right_sensor = Analog(right_PIN);
	this->set_target(target);
	this->set_parameters(Kp, Ki, Kd);
	this->set_output_limits(output_min, output_max);
	this->set_map_value((output_max - output_min) / 2.0);
	return;
}
	
void Sensor::set_input(const double left_sensor, const double right_sensor)
{
	this->left_input = this->check_input(left_sensor);
	this->right_input = this->check_input(right_sensor);
	this->map();
	this->actual_value = this->target + this->mapped_left_input - this->mapped_right_input;
	return;
}

void Sensor::read(void)
{
	if (++this->read_counter >= this->counter_max)
	{
		this->read_counter = 0x00;
		this->set_input(this->left_sensor.read(), this->right_sensor.read());
	}
	return;
}

void Sensor::print(void)
{
	Serial::init();
	Serial::print("--------------------------------------------------------------------------------------\n");
	Serial::print("Target: "); Serial::print(this->target);
	Serial::print("\nActual value: "); Serial::print(this->actual_value);
	Serial::print("\nOutput: "); Serial::print(this->output);
	Serial::print("\nError: "); Serial::print(this->last_error);
	Serial::print("\n--------------------------------------------------------------------------------------\n\n");
	
	if (this->output > this->target)
	{
		Serial::print("Unit driving "); 
		Serial::print(this->output - this->target); 
		Serial::print(" degrees to the right!\n\n");
	}
	
	else if (this->output < this->target)
	{
		Serial::print("Unit driving "); 
		Serial::print(this->target - this->output); 
		Serial::print(" degrees to the left!\n\n");
	}
	
	else
	{
		Serial::print("Car driving straight forward!\n\n");
	}
	
	return;
}

Sensor::~Sensor(void)
{
	Serial::print("\n Sensor destructor called!\n");
	return;
}