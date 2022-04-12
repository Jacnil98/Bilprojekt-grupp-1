#include "GPIO.h"

USART_Timer::USART_Timer(const uint16_t delay)
{
	this->delay = delay;
	this->enabled = false;
	this->required_interrupts = 0x00;
	this->executed_interrupts = 0x00;
	this->init_timer0();
}



void USART_Timer::init_timer0()
{
	asm("SEI");
	TCCR0B = ((1<<CS00)|(1<<CS02));
	TIMSK1 = 0;
}

void USART_Timer::count_interrupts()
{
	this->executed_interrupts++;
}

bool USART_Timer::elapsed()
{
	if (this->executed_interrupts >= this->required_interrupts)
	{
		this->executed_interrupts = 0x00;
		return true;
	}
	else
	return false;
}

void USART_Timer::set_delay(const uint16_t delay)
{
	this->delay = delay;
}

void USART_Timer::on()
{
	TIMSK0 = (1 << TOIE0);
	this->enabled = true;
}

void USART_Timer::off()
{
	TIMSK0 = 0x00;
	this->enabled = false;
}

void USART_Timer::toggle()
{
	if (this->enabled)
	this->off();
	else this->on();
}

bool USART_Timer::is_enabled()
{
	if (this->enabled)
	return true;
	else
	return false;
}