#include "header.h"

static volatile uint16_t required_interrupts = PERIOD / INTERRUPT_TIME;
static volatile uint16_t required_interrupts_on;
static volatile uint16_t executed_interrupts;

//static uint16_t duty_cycle_interrupts;

void timer_on()
{
    TCCR1B = (1 << CS10) | (1 << WGM12); //här, 
    timer_enabled = true; //men varför kallar den på motor disabled?
    serial_print("timer enabled\n");
    return;
}

void timer_disable()
{
    serial_print("timer disabled\n");
    //TCCR2B = 0x00;
    TCCR1B = 0x00;
    timer_enabled = false;
    return;
}

bool timer_elapsed()
{	
    //serial_print_int("%d\n", executed_interrupts);
	if (++executed_interrupts >= required_interrupts)
	{
        executed_interrupts = 0x00;
        get_new_duty_cycle();
        //serial_print_int("%d\n", required_interrupts);
		return true;
	}
	return false;
}

bool duty_cycle_elapsed()
{
    if (++executed_interrupts >= required_interrupts_on) //beehöver ett värde snabbt)duty_cycle_interruptsCalculate_distance()
	{
        //serial_print_int("%d\n", required_interrupts_on);
		return true;
	}
	return false;
}

void get_new_duty_cycle()
{
    required_interrupts_on = Calculate_distance();
    
    return;
}
