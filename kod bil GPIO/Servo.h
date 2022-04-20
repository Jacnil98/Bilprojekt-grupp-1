#ifndef SERVO_H_
#define SERVO_H_

#include "definitions.h"
#include "GPIO.h"
#include "PWM_Timer.h"

class Servo
{
protected:
	Output servo;
	PWM_Timer servo_timer;
	volatile bool enabled = false;
	bool servo_enabled = false;
public:
	Servo(void) { }
	Servo(const uint8_t servo_PIN, const TimerSelection timerSelection, const double period);
	~Servo(void);
	void on(void);
	void off(void);
	void toggle_PWM(void);
	void enable(void);
	void disable(void);
	void toggle(void);
	bool elapsed(void) {return this->servo_timer.elapsed(); }
	void switch_servo_mode(void) { this->servo_timer.switch_mode(); }
};

#endif /* SERVO_H_ */