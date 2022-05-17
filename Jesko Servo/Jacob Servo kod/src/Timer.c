#include "Header.h"

static volatile uint16_t required_interrupts = PERIOD / INTERRUPT_TIME;
static volatile uint16_t executed_interrupts;

//static uint16_t duty_cycle_interrupts;

void timer_on()
{
    TCCR1B = (1 << CS10) | (1 << WGM12); 
    timer_enabled = true;
    //serial_print("timer enabled\n");
    return;
}

void timer_disable()
{
    //serial_print("timer disabled\n");
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
        
        //get_new_duty_cycle();
        
		return true;
	}
	return false;
}

bool duty_cycle_elapsed()
{
    
    if (++executed_interrupts >= output) //beehöver ett värde snabbt)duty_cycle_interruptsCalculate_distance()
	{
        //serial_print_int("%d\n", output);
        //serial_print_int("%d\n", Calculate_distance);
		return true;
	}
	return false;
}