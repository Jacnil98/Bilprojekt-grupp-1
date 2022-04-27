#include "PID_Controller.h"

void PID_Controller::check_output(void)
{
	if (this->output_min == this->output_max) return;
	if (this->output > this->output_max)
		this->output = this->output_max;
	else if (this->output < this->output_min)
		this->output = this->output_min;
	return;
}

PID_Controller::PID_Controller(const double target, const double Kp, const double Ki, const double Kd)
{
	this->set_target(target);
	this->set_parameters(Kp, Ki, Kd);
	return;
}

PID_Controller::PID_Controller(const double target, const double Kp, const double Ki, const double Kd,
const double output_min, const double output_max)
{
	this->set_target(target);
	this->set_parameters(Kp, Ki, Kd);
	this->set_output_limits(output_min, output_max);
	return;
}

void PID_Controller::set_output_limits(const double output_min, const double output_max)
{
	this->output_min = output_min;
	this->output_max = output_max;
	return;
}

void PID_Controller::set_parameters(const double Kp, const double Ki, const double Kd)
{
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	return;
}

void PID_Controller::regulate(void)
{
	const double error = this->target - this->actual_value;
	this->integral += error;
	const double derivative = error - this->last_error;
	this->output = this->target + this->Kp * error + this->Ki * this->integral + this->Kd * derivative;
	this->check_output();
	this->last_error = error;
	return;
}

void PID_Controller::print(void)
{
	Serial::init();
	Serial::print("--------------------------------------------------------------------------------------\n");
	Serial::print("Target: "); Serial::print(this->target); 
	Serial::print("\nActual value: "); Serial::print(this->actual_value);
	Serial::print("\nOutput: "); Serial::print(this->output);
	Serial::print("\nError: "); Serial::print(this->last_error);
	Serial::print("\n--------------------------------------------------------------------------------------\n\n");
	return;
}