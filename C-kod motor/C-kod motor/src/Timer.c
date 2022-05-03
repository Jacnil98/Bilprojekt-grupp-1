#include "header.h"

static uint16_t required_interrupts;
static volatile uint16_t executed_interrupts;
static period current_period = ON;

void timer_enable()
{
    TIMSK1 = (1 << OCIE1A); //här, 
    timer_enabled = true; //men varför kallar den på motor disabled?
    serial_print("timer enabled\n");
    return;
}

void timer_disable()
{
    serial_print("timer disabled\n");
    TIMSK1 = 0x00;
    timer_enabled = false;
    return;
}

bool timer_elapsed()
{	
    //serial_print_int("%d\n", executed_interrupts);
	if (++executed_interrupts >= required_interrupts)
	{
		return true;
	}
	return false;
}

void switch_pwm_mode()
{
    if(current_period == ON)
        {
            required_interrupts = TOTAL_INTERRUPTS - executed_interrupts;
            current_period = OFF;
            
            executed_interrupts = 0x00;
            MOTOR_OFF;
        }
        
    else
    {
        required_interrupts = Calculate_distance();
        current_period = ON;
        //serial_print_int("%d\n", executed_interrupts);
        executed_interrupts = 0x00;
        MOTOR_ON;
    }
    return;
}