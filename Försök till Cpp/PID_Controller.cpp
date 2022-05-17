#include "GPIO.h"

void PID_Controller::check_output(void)
{
	if (this->output_min == this->output_max) return;
	if (this->output > output_max)
		this->output = this->output_max;
	else if (this->output < this->output_min)
		this->output = this->output_min;
	return;
}

PID_Controller::PID_Controller(const double targett, const double Kp, const double Ki, const double Kd)
{
	this->targett = targett;
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	return;
}

PID_Controller::PID_Controller(const double targett, const double Kp, const double Ki, const double Kd, const double output_min, const double output_max)
{
	this->targett = targett;
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
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
	this->current_error = TARGET - this->actual_value; //this->current_error = this->target - this->actual_value;
	this->integral = this->current_error;
	this->derivative = this->current_error - this->last_error;
	this->output = TARGET + this->Kp * this->current_error + this->Ki * this->integral + this->Kd * this->derivative; //this->output = this->target + this->Kp * this->current_error + this->Ki
	serial_print("\n-----------------------------------------------\n");
	serial_print("secound function\n");
	serial_print_int(TARGET);
	serial_print_int(actual_value);
	serial_print_int(integral);
	serial_print_int(derivative);
	serial_print_int(output);
	
	serial_print("\n-----------------------------------------------\n\n");
	this->check_output();
	this->last_error = this->current_error;
	return;
}