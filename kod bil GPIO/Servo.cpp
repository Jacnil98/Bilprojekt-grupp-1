#include "Servo.h"
#include "Serial.h"

Servo::Servo(const uint8_t servo_PIN, const TimerSelection timerSelection, const double period)
{
	this->servo = Output(servo_PIN);
	this->servo_timer = PWM_Timer(timerSelection, period);
	return;
}

void on(void)
{
	
	return;
}
void off(void)
{
	return;
}