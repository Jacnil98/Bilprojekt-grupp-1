#include "GPIO.h"

Servo::Servo(const uint8_t PIN)
{
	if(PIN >=0 && PIN <=7)
	{
		this->io_port = IO_port::D;
		this->PIN = PIN;
		SET(DDRD, this->PIN);
	}
	else if (PIN <= 8 && PIN <= 13)
	{
		this->io_port = IO_port::B;
		this->PIN = PIN - 8;
		SET(DDRB, this->PIN);
	}
	this->left_sensor_PIN = 0;
	this->right_sensor_PIN = 2;
	this->left_sensor_io_port =IO_port::C;
	this->right_sensor_io_port = IO_port::C;
}

void Servo::on(void)
{
	if(this->io_port == IO_port::B)
		SET(PORTB, this->PIN);
	else if(this->io_port == IO_port::D)
		SET(PORTD, this->PIN);
	this->servo_enabled = true;
	return;
}

void Servo::off(void)
{
	if(this->io_port == IO_port::B)
		CLEAR(PORTB, this->PIN);
	if(this->io_port ==IO_port::D)
		CLEAR(PORTD, this->PIN);
	this->servo_enabled = false;
	return;
}

void Servo::toggle(void)
{
	if(this->servo_enabled) this->disabled();
	else this->enabled();
}

void Servo::enabled()
{
	this->PWM_enabled = true;
	ENABLE_TIMER0;
	servo_timer.enabled = true; 
	this->servo_enabled = true;
}

void Servo::disabled()
{
	this->PWM_enabled = false;
	DISABLE_TIMER0;
	servo_timer.enabled = false; 
	this->servo_enabled = false;
	this->off();
	return;
}

bool Servo::is_enabled()
{
	return this->servo_enabled;
}