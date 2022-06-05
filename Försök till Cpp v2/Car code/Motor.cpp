#include "Motor.h"
#include "Serial.h"
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

Motor::Motor(const uint8_t output1_PIN, const uint8_t output2_PIN, const uint8_t motor_PIN,
const TimerSelection timerSelection, const double period, const uint8_t pot_PIN)
{
	this->output1 = Output(output1_PIN);
	this->output2 = Output(output2_PIN);
	this->actuator = Output(motor_PIN);
	this->pwm_timer = PWM_Timer(timerSelection, period, pot_PIN);
	return;
}

void Motor::on(void)
{
	
	this->actuator_enabled = true;
	this->actuator.on();
	//Serial::print("\n Motor On: ");
	
	return;
}

void Motor::off(void)
{
	
	this->actuator_enabled = false;
	this->actuator.off();
	//Serial::print("\n Motor Off: ");
	
	return;
}

void Motor::toggle_PWM(void)
{
	//Serial::print("\n toggle_PWM ");
	if (this->actuator_enabled)
		this->off();
	else
		this->on();
	return;
}


void Motor::enable(void)
{
	this->enabled = true;
	this->pwm_timer.on();
	this->drive_forward();
	//Serial::print("Motor timer now on!\n");
	return;
}

void Motor::disable(void)
{
	this->enabled = false;
	this->pwm_timer.off();
	this->actuator.off();
	//Serial::print("Motor timer now off!\n");
	return;
}

void Motor::toggle(void)
{
	if (this->enabled)
	{
		
		this->disable();
		Serial::print("The motor is now disabled!\n");
	}
	else
	{
		this->enable();
		Serial::print("The motor is now enabled!\n");
	}
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

