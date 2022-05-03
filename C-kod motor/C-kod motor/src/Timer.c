#include "header.h"

void timer_enable()
{
    TIMSK1 = (1 << OCIE1A);
    timer_enabled = true;
    return;
}

void timer_disable()
{
    TIMSK1 = 0x00;
    timer_enabled = false;
    return;
}

bool timer_elapsed()
{	
    executed_interrupts++;
	if (executed_interrupts >= required_interrupts)
	{
		return true;
	}
	return false;
}

void switch_servo_mode()
{
     if(current_period == ON)
        {
            required_interrupts = TOTAL_INTERRUPTS - executed_interrupts;
            current_period = OFF;
            executed_interrupts = 0x00;
        }
        
        else
        {
            required_interrupts = Calculate_distance();
            current_period = ON;
            executed_interrupts = 0x00;
        }
    return;
}