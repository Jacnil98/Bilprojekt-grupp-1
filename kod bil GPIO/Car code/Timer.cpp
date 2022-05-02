#include "Timer.h"
#include "Serial.h"
void Timer::init(const TimerSelection timerSelection)
{
	asm("SEI");
	//Serial::init();
	if (timerSelection == TimerSelection::Timer0)
	{
		TCCR0B = (1 << CS00); 
		//Serial::print("\n Timer 0 initiated ");
	}
	
	else if (timerSelection == TimerSelection::Timer1)
	{
		TCCR1B = (1 << CS10) | (1 << WGM12);
		OCR1A = 255;
		//Serial::print("\n Timer 1 initiated ");
/*
1/20M = 0.05us => 1.5ms/0.05us = 30k  => 30k/256 = 117 interrupts för rakt fram
                  1ms                    20k/256 = 78 interrupts för vänster  
	              2ms                    40k/256 = 156 interrupts för höger
				  
	                                     30k/333 = 90 interrupts   
										 
		                                 30k/166.6 = 180 interrupts    
*/                                  
	}
	
	else if (timerSelection == TimerSelection::Timer2)
	{
		TCCR2B = (1 << CS20);
		//Serial::print("\n Timer 2 initiated ");
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
	//Serial::print("\nTimer destructor called!\n");
	// this->reset();
	// this->disable(this->timerSelection);
	return;
}

void Timer::on(void)
{
	if (this->timerSelection == TimerSelection::Timer0)
		TIMSK0 = (1 << TOIE0);
	else if (this->timerSelection == TimerSelection::Timer1)
		TIMSK1 = (1 << OCIE1A);
	else if (this->timerSelection == TimerSelection::Timer2)
	{
		TIMSK2 = (1 << TOIE2);
		//Serial::print("\n Timer 2 on: ");
	}
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
	{
		TIMSK2 = 0x00;
		//Serial::print("\n Timer 2 off: ");
	}
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
	{
		return false;
	}
	
	if (++this->executed_interrupts >= this->required_interrupts)
	{
		//Serial::print("\n Required interrutps: "); Serial::print(this->required_interrupts);
		//Serial::print("\n req int true:(elapsed) ");
		this->executed_interrupts = 0x00;
		return true;
	}
	//Serial::print("\n executed interrupts: "); Serial::print(this->executed_interrupts);
	return false;
}

void Timer::reset(void)
{
	this->off();
	this->executed_interrupts = 0x00;
	return;
}