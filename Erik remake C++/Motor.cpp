#include "Motor.h"

void Motor::toggle_PWM_mode(void)
{
	if (!this->enabled) return;
	this->pwm_timer.switch_mode();
	
	if (this->motorDirection == MotorDirection::Forward)
		this->output1.toggle();
	else
		this->output2.toggle();
		return;
}

Motor::Motor(const uint8_t output1_PIN, const uint8_t output2_PIN, const uint8_t direction_PIN,
const TimerSelection timerSelection, const double period, const uint8_t pot_PIN)
{
	this->output1 = Led(output1_PIN);
	this->output2 = Led(output2_PIN);
	this->directionButton = Button(direction_PIN);
	this->pwm_timer = PWM_Timer(timerSelection, period, pot_PIN);
	return;
}

void Motor::on(void)
{
	this->pwm_timer.on();
	this->directionButton.enable_interrupt();
	this->enabled = true;
	return;
}

void Motor::off(void)
{
	this->pwm_timer.off();
	this->directionButton.disable_interrupt();
	this->enabled = false;
	return;
}

void Motor::toggle(void)
{
	if (this->enabled)
		this->off();
	else
		this->on();
	return;
}

void Motor::drive_forward(void)
{
	if (!this->enabled) return;
	this->output1.on();
	this->output2.off();
	this->motorDirection = MotorDirection::Forward;
	return;
}

void Motor::drive_backward(void)
{
	if (!this->enabled) return;
	this->output1.off();
	this->output2.on();
	this->motorDirection = MotorDirection::Backward;
	return;
}

void Motor::change_direction(void)
{
	if (this->motorDirection == MotorDirection::Forward)
		this->drive_backward();
	else
		this->drive_forward();
	return;
}

void Motor::run_PWM(void)
{
	if (!this->enabled) return;
	if (this->pwm_timer.elapsed())
		this->toggle_PWM_mode();
	return;
}

void Motor::enable_direction_interrupt(void)
{
	this->directionButton.enable_interrupt();
	return;	
}
	
void Motor::disable_direction_interrupt(void)
{
	this->directionButton.disable_interrupt();
	return;
}