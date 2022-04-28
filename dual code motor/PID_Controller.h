
#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

#include "definitions.h"
#include "Serial.h"

class PID_Controller
{
protected:
	double output = 0x00;
	double target = 0x00;
	double actual_value = 0x00;
	double Kp = 0x00;
	double Ki = 0x00;
	double Kd = 0x00;
	double last_error = 0x00;
	double integral = 0x00;
	double output_min = 0x00;
	double output_max = 0x00;
	void check_output(void);
public:
	PID_Controller(void) { }
	PID_Controller(const double target, const double Kp, const double Ki, const double Kd);
	PID_Controller(const double target, const double Kp, const double Ki, const double Kd, 
		const double output_min, const double output_max);
	~PID_Controller(void) {}
	double get_output(void) { return this->output; }
	double get_output_min(void) { return this->output_min; }
	double get_output_max(void) { return this->output_max; }
	void set_output_limits(const double output_min, const double output_max);
	void set_parameters(const double Kp, const double Ki, const double Kd);
	void set_target(const double new_target) { this->target = new_target; }
	void set_actual_value(const double new_actual_value) { this->actual_value = new_actual_value; }
	void regulate(void);
	void print(void);
};



#endif /* PID_CONTROLLER_H_ */