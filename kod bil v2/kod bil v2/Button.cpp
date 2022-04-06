#include "GPIO.h"

Button::Button(const uint8_t PIN)
{
	if(PIN >= 0 && PIN <=7)
	{
		this->io_port = IO_port::D;
		this->PIN=PIN;
		SET(PORTD, this->PIN);
	}
	else if (PIN >= 8 && PIN <= 13);
	{
		this->io_port = IO_port::B;
		this->PIN = PIN - 8;
		SET(PORTB, this->PIN);
	}
	
	return;
}

bool Button::is_pressed(void)
{
	if (this->io_port ==IO_port::B)
	return READ(PINB, this->PIN);
	else if (this->io_port == IO_port::D)
	return READ(PIND, this->PIN);
	return false;
}

void Button::enable_interrupt()
{
	asm("SEI");
	if (this->io_port == IO_port::B)
	{
		SET(PCICR, PCIE0);
		SET(PCMSK0, this->PIN);
	}
	else if (this->io_port == IO_port::D)
	{
		SET(PCICR, PCIE2);
		SET(PCMSK2, this->PIN);
	}
	this->interrupt_enabled = true;
}
void Button::disable_interrupt(void)
{
	if (this->io_port== IO_port::B)
		CLEAR(PCMSK0, this->PIN);
	else if (this->io_port == IO_port::D)
		CLEAR(PCMSK2, this->PIN);
	this->interrupt_enabled = false;
	return;
}