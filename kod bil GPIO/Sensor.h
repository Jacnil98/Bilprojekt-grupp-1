#ifndef SENSOR_H_
#define SENSOR_H_

#include "definitions.h"
#include "PID_Controller.h"
#include "Pot.h"
#include "Serial.h"

class Sensor : public PID_Controller
{
protected:
	Analog left_sensor;
	Analog right_sensor;
	double left_input = 0x00;
	double right_input = 0x00;
	double mapped_left_input = 0x00;
	double mapped_right_input = 0x00;
	double map_value = 0x00;
	static constexpr double SENSOR_MIN = Analog::output_min();
	static constexpr double SENSOR_MAX = Analog::output_max();
	//void init()
	double check_input(const double input);
	void map(void);
public:
	Sensor(void) { }
	Sensor(const uint8_t left_PIN, const uint8_t right_PIN, const double target, 
		const double Kp, const double Ki, const double Kd);
	Sensor(const uint8_t left_PIN, const uint8_t right_PIN, const double target, 
		const double Kp, const double Ki, const double Kd, const double output_min, const double output_max);
	~Sensor(void);
	static double min(void) { return Sensor::SENSOR_MIN; }
	static double max(void) { return Sensor::SENSOR_MAX; }
	void set_map_value(const double new_map_value) { this->map_value = new_map_value; }
	void set_input(const double left_input, const double right_input);
	void read(void);
	void print(void);
};



#endif /* SENSOR_H_ */