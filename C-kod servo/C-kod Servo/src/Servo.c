#include "header.h"

void servo_enable()
{
    servo_enabled = true;
    return;
}

void servo_disable()
{
    servo_enabled = false;
    return;
}

void switch_servo_mode()
{
    if(servo_period == ON)
    {
        required_interrupts = TOTAL_INTERRUPTS - executed_interrupts;
        servo_period = OFF;
    }
    else
    {
        required_interrupts = 0x00;//??
        servo_period = ON;
    }
return;
}

void servo_elapsed()
{
    if (!required_interrupts)
	{
		return false;
	}
    
    if (++executed_interrupts >= required_interrupts)
	{
		executed_interrupts = 0x00;
		return true;
	}
    return false;
}