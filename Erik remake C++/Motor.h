
#ifndef MOTOR_H_
#define MOTOR_H_

#include "definitions.h"
#include "Led.h"
#include "Button.h"
#include "PWM_Timer.h"

class Motor
{
protected:
	Led output1;
	Led output2;
	Button directionButton;
	PWM_Timer pwm_timer;
	MotorDirection motorDirection = MotorDirection::Forward;
	bool enabled = false;
	void toggle_PWM_mode(void);
public:
	Motor(void) { }
	Motor(const uint8_t output1_PIN, const uint8_t output2_PIN, const uint8_t direction_PIN, 
	const TimerSelection timerSelection, const double period, const uint8_t pot_PIN);
	~Motor(void) { }
	void on(void);
	void off(void);
	void toggle(void);
	void drive_forward(void);
	void drive_backward(void);
	void change_direction(void);
	void run_PWM(void);
	void enable_direction_interrupt(void);
	void disable_direction_interrupt(void);
};

#endif /* MOTOR_H_ */