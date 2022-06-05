#include "header.h"

static volatile uint16_t required_interrupts = PERIOD / INTERRUPT_TIME;
static volatile uint16_t executed_interrupts;


void timer_on()
{
    TCCR1B = (1 << CS10) | (1 << WGM12); 
    timer_enabled = true;
    serial_print("timer enabled\n");
    return;
}

void timer_disable()
{
    serial_print("timer disabled\n");
    TCCR1B = 0x00;
    timer_enabled = false;
    return;
}

bool timer_elapsed()
{	
	if (++executed_interrupts >= required_interrupts)
	{
        executed_interrupts = 0x00;

		return true;
	}
	return false;
}

bool duty_cycle_elapsed()
{
    
    if (++executed_interrupts >= output) 
	{
		return true;
	}
	return false;
}