
#ifndef MOTOR_H_
#define MOTOR_H_

#include "definitions.h"
#include "GPIO.h"
#include "PWM_Timer.h"

class Motor
{
protected:
	Output output1;
	Output output2;
	Output actuator;
	PWM_Timer pwm_timer;
	MotorDirection motorDirection = MotorDirection::Forward;
	volatile bool enabled = false;
	bool actuator_enabled = false;
	void toggle_PWM_mode(void);
public:
	
	Motor(void) { }
	Motor(const uint8_t output1_PIN, const uint8_t output2_PIN, const uint8_t motor_PIN, 
	const TimerSelection timerSelection, const double period, const uint8_t pot_PIN);
	~Motor(void) { }
	void on(void);
	void off(void);
	void toggle_PWM();
	void enable(void);
	void disable(void);
	void toggle(void);
	void drive_forward(void);
	void drive_backward(void);
	void change_direction(void);
	void run_PWM(void);
	void enable_direction_interrupt(void);
	void disable_direction_interrupt(void);
	bool elapsed(void) { return this->pwm_timer.elapsed(); }
	void switch_mode(void) { this->pwm_timer.switch_mode(); }
};

#endif /* MOTOR_H_ */