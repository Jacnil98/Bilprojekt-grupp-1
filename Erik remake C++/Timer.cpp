#include "Timer.h"

void Timer::init(const TimerSelection timerSelection)
{
	asm("SEI");
	
	if (timerSelection == TimerSelection::Timer0)
	{
		TCCR0B = (1 << CS00);
	}
	
	else if (timerSelection == TimerSelection::Timer1)
	{
		TCCR1B = (1 << CS10) | (1 << WGM12);
		OCR1A = 256;
	}
	
	else if (timerSelection == TimerSelection::Timer2)
	{
		TCCR2B = (1 << CS20);
	}
	
	return;
}

void Timer::disable(const TimerSelection timerSelection)
{
	if (timerSelection == TimerSelection::Timer0)
		TCCR0B = 0x00;
	else if (timerSelection == TimerSelection::Timer1)
		TCCR1B = 0x00;
	else if (timerSelection == TimerSelection::Timer2)
		TCCR2B = 0x00;
	return;
}

Timer::Timer(const TimerSelection timerSelection, const double delay_time)
{
	this->timerSelection = timerSelection;
	this->required_interrupts = this->get_required_interrupts(delay_time);
	this->init(this->timerSelection);
	this->enabled = false;
	return;
}

Timer::~Timer(void)
{
	this->reset();
	this->disable(this->timerSelection);
	return;
}

void Timer::on(void)
{
	if (this->timerSelection == TimerSelection::Timer0)
		TIMSK0 = (1 << TOIE0);
	else if (this->timerSelection == TimerSelection::Timer1)
		TIMSK1 = (1 << OCIE1A);
	else if (this->timerSelection == TimerSelection::Timer2)
		TIMSK2 = (1 << TOIE2);
	this->enabled = true;
	return;
}

void Timer::off(void)
{
	if (this->timerSelection == TimerSelection::Timer0)
		TIMSK0 = 0x00;
	else if (this->timerSelection == TimerSelection::Timer1)
		TIMSK1 = 0x00;
	else if (this->timerSelection == TimerSelection::Timer2)
		TIMSK2 = 0x00;
	this->enabled = false;
	return;
}

void Timer::toggle(void)
{
	if (this->enabled)
		this->off();
	else
		this->on();
	return;
}

bool Timer::elapsed(void)
{
	if (!this->required_interrupts)
		return false;
		
	if (++this->executed_interrupts >= this->required_interrupts)
	{
		this->executed_interrupts = 0x00;
		return true;
	}
	
	return false;
}

void Timer::reset(void)
{
	this->off();
	this->executed_interrupts = 0x00;
	return;
}