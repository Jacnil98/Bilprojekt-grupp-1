#include "Servo.h"
#include "Serial.h"

Servo::Servo(const uint8_t servo_PIN, const uint8_t left_PIN, const uint8_t right_PIN, 
	const TimerSelection timerSelection, const double period)
{
	this->servo = Output(servo_PIN);
	this->servo_timer = PWM_Timer(timerSelection, period);
	this->sensor = Sensor(left_PIN, right_PIN, 90, 3.5, 0.01, 0.3, 50, 110);
	return;
}

void Servo::on(void)
{
	this->servo_enabled = true;
	this->servo.on();
	return;
}

void Servo::off(void)
{
	this->servo_enabled = false;
	this->servo.off();
	return;
}

void Servo::toggle_PWM(void)
{
	if (this->servo_enabled)
		this->off();
	else
		this->on();
	return;
}

void Servo::enable(void)
{
	this->enabled = true;
	this->servo_timer.on();
	//Serial::print("Servo timer now on!\n");
	return;
}

void Servo::disable(void)
{
	this->enabled = false;
	this->servo_timer.off();
	//Serial::print("Servo timer now off!\n");
	return;
}

void Servo::toggle(void)
{
	if (this->enabled)
	{
		
		this->disable();
		//Serial::print("The Servo is now disabled!\n");
	}
	else
	{
		this->enable();
		//Serial::print("The Servo is now enabled!\n");
	}
	return;
}

Servo::~Servo(void)
{
	//Serial::print("\n Timer destructor called!\n");
	return;
}

void Servo::regulate(void) 
{
	this->sensor.read();
	this->sensor.regulate();
	return;
}