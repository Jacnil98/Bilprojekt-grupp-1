#include "header.h"

static volatile uint16_t required_interrupts = PERIOD / INTERRUPT_TIME;
static volatile uint16_t required_interrupts_on;
static volatile uint16_t executed_interrupts;
static volatile uint32_t reverse_executed_interrupts;
static volatile uint32_t reverse_total_interrupts = TOTAL_REVERSE_PERIOD / REVERSE_INTERRUPT_TIME;
static volatile uint32_t required_interrupts_for_reverse = REQUIRED_FOR_REVERSE / REVERSE_INTERRUPT_TIME;
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
    if (++executed_interrupts >= required_interrupts_on)
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




void reverse_timer_on()
{
    TIMSK2 = (1 << OCIE2A); 
    timer2_enabled = true; 
    serial_print("timer2 enabled\n");
    return;
}

void reverse_timer_off()
{
    serial_print("timer2 disabled\n");
    reverse_executed_interrupts = 0x00;
    TIMSK2 = 0x00;
    timer2_enabled = false;
    return;
}

bool reverse_timer_elapsed()
{
    if (++reverse_executed_interrupts >= reverse_total_interrupts)
	{
        reverse_executed_interrupts = 0x00;
        reverse_timer_off();
		return true;
	}
    
	return false;
}

bool start_reversing()
{
    if (++reverse_executed_interrupts >= required_interrupts_for_reverse) 
	{
		return true;
	}
	return false;
}

