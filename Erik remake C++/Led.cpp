#include "Led.h"

Led::Led(const uint8_t PIN)
{
	this->enabled = false;
	
	if (PIN >= 0 && PIN <= 7)
	{
		this->io_port = IO_port::D;
		this->PIN = PIN;
		DDRD |= (1 << this->PIN);
	}
	
	else if (PIN >= 8 && PIN <= 13)
	{
		this->io_port = IO_port::B;
		this->PIN = PIN - 8;
		DDRB |= (1 << this->PIN);
	}
	
	else if (PIN >= 14 && PIN <= 19)
	{
		this->io_port = IO_port::C;
		this->PIN = PIN - 14;
		DDRC |= (1 << this->PIN);
	}
	
	return;
}

Led::~Led(void)
{
	this->off();
	if (this->io_port == IO_port::B)
		DDRB &= ~(1 << this->PIN);
	else if (this->io_port == IO_port::C)
		DDRC &= ~(1 << this->PIN);
	else if (this->io_port == IO_port::D)
		DDRD &= ~(1 << this->PIN);
	return;
}

void Led::on(void)
{
	if (this->io_port == IO_port::B)
		PORTB |= (1 << this->PIN);
	else if (this->io_port == IO_port::C)
		PORTC |= (1 << this->PIN);
	else if (this->io_port == IO_port::D)
		PORTD |= (1 << this->PIN);
	this->enabled = true;
	return;
}

void Led::off(void)
{
	if (this->io_port == IO_port::B)
		PORTB &= ~(1 << this->PIN);
	else if (this->io_port == IO_port::C)
		PORTC &= ~(1 << this->PIN);
	else if (this->io_port == IO_port::D)
		PORTD &= ~(1 << this->PIN);
	this->enabled = false;
	return;
}

void Led::toggle(void)
{
	if (this->enabled)
		this->off();
	else
		this->on();
	return;
}

void Led::blink(const size_t delay_time)
{
	this->toggle();
	this->delay(delay_time);
	return;
}