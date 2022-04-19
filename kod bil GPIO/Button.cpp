
#include "GPIO.h"
#include "Serial.h"

Button::Button(const uint8_t PIN)
{
	if(PIN >= 0 && PIN <=7)
	{
		this->io_port = IO_port::D;
		this->PIN = PIN;
		PORTD |= (1 << this->PIN);
	}
	
	else if (PIN >= 8 && PIN <= 13)
	{
		this->io_port = IO_port::B;
		this->PIN = PIN - 8;
		PORTB |= (1 << this->PIN);
		
	}
	
	else if (PIN >= 14 && PIN <= 19)
	{
		this->io_port = IO_port::C;
		this->PIN = PIN - 14;
		PORTC |= (1 << this->PIN);
	}
	
	return;
}

bool Button::is_pressed(void)
{
	if (this->io_port == IO_port::B)
		return (PINB & (1 << this->PIN));
	else if (this->io_port == IO_port::C)
		return (PINC & (1 << this->PIN));
	else if (this->io_port == IO_port::D)
		return (PIND & (1 << this->PIN));
	return false;
}

void Button::enable_interrupt()
{
	asm("SEI");
	
	if (this->io_port == IO_port::B)
	{
		PCICR |= (1 << PCIE0);
		PCMSK0 |= (1 << this->PIN);
	}
	
	if (this->io_port == IO_port::C)
	{
		PCICR |= (1 << PCIE1);
		PCMSK1 |= (1 << this->PIN);
	}
	
	else if (this->io_port == IO_port::D)
	{
		PCICR |= (1 << PCIE2);
		PCMSK2 |= (1 << this->PIN);
	}
	
	this->interrupt_enabled = true;
	return;
}

void Button::disable_interrupt(void)
{
	if (this->io_port== IO_port::B)
		PCMSK0 &= ~(1 << this->PIN);
	else if (this->io_port == IO_port::C)
		PCMSK1 &= ~(1 << this->PIN);
	else if (this->io_port == IO_port::D)
		PCMSK2 &= ~(1 << this->PIN);
	this->interrupt_enabled = false;
	return;
}