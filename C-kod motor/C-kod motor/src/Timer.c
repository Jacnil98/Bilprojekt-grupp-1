#include "header.h"

static volatile uint16_t required_interrupts = PERIOD / INTERRUPT_TIME;
static volatile uint16_t executed_interrupts;

//static uint16_t duty_cycle_interrupts;

void timer_on()
{
    TIMSK2 = (1 << OCIE2A); //här, 
    timer_enabled = true; //men varför kallar den på motor disabled?
    serial_print("timer enabled\n");
    return;
}

void timer_disable()
{
    serial_print("timer disabled\n");
    //TCCR2B = 0x00;
    TIMSK2 = 0x00;
    timer_enabled = false;
    return;
}

bool timer_elapsed()
{	
    //serial_print_int("%d\n", executed_interrupts);
	if (++executed_interrupts >= required_interrupts)
	{
        executed_interrupts = 0x00;
		return true;
	}
	return false;
}

bool duty_cycle_elapsed()
{
    if (++executed_interrupts >= Calculate_distance()) //)duty_cycle_interrupts
	{
		return true;
	}
	return false;
}
