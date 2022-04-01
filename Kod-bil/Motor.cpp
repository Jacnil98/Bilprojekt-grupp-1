#include "GPIO.h"

Motor::Motor(const uint8_t PIN)
{
	if(PIN >=0 && PIN <= 7)
	{
		this->io_port = IO_port::D;
		this->PIN = PIN;
		SET(DDRD, this->PIN);
	}
	else if (PIN >= 8 && PIN <= 13)
	{
		this->io_port = IO_port::B;
		this->PIN = PIN - 8;
		SET (DDRB, this->PIN);
	}
	this->sensor_PIN = 1;
	this->sensor_PCINT = this->sensor_PIN + 8;
	this->sensor_io_port = IO_port::C;
}

void Motor::on(void)
{
	if (this->io_port == IO_port::B)
	SET(PORTB, this->PIN);
	else if(this->io_port == IO_port::D)
	SET(PORTD, this->PIN);
	this->motor_enabled = true;
	this->read_direction();
	return;
}

void Motor::off(void)
{
	if (this->io_port == IO_port::B)
	CLEAR(PORTB, this->PIN);
	else if(this->io_port == IO_port::D)
	CLEAR(PORTD, this->PIN);
	this->motor_enabled = false;
	return;
}

void Motor::read_direction(void)
{
	if (forward_enabled)
	{
		PORTD |= (1<<7);
		PORTD &= ~(1<<8);
	}
	else if (!forward_enabled)
	{
		PORTD |= (1<<8);
		PORTD &= ~(1<<7);
	}
}

/*
void Motor::enable_interrupt()
{
	PCMSK1 |= (1 << this->sensor_PCINT);
	this->interrupt_enabled = true;
}

void Motor::disable_interrupt()
{
	PCMSK1 &= ~(1 << this->sensor_PCINT);
	this->interrupt_enabled = false;
}
*/

void Motor::enabled()
{
	
}

void Motor::disabled()
{
	
}


void Motor::PWM()
{
	
}