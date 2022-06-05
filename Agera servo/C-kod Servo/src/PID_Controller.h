#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

#include <stdio.h>

#define SENSOR_MAX 1023.0
#define SENSOR_MIN 0.0

#define OUTPUT_MIN 0
#define OUTPUT_MAX 180
#define TARGET 90
#define Kp 0.7
#define Ki 0.00001
#define Kd 0.6

typedef enum { MOTOR_DIRECTION_FORWARDS, MOTOR_DIRECTION_BACKWARDS } motor_direction_t; 

double output;
double actual_value;
double duty_cycle;
double last_error;
double intergral;
motor_direction_t motor_direction;

void regulate();
void set_input();
void init_pid_controller();

#endif /* PID_CONTROLLER_H_ */