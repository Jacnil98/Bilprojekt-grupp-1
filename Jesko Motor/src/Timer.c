#include "Header.h"

static volatile uint16_t required_interrupts = PERIOD / INTERRUPT_TIME;
static volatile uint16_t required_interrupts_on;
static volatile uint16_t executed_interrupts;

static volatile uint16_t reverse_executed_interrupts;
static uint16_t reverse_total_interrupts = TOTAL_REVERSE_INTERRUPTS;
static uint16_t required_interrupts_for_reverse = INTERRUPTS_REQUIRED_FOR_REVERSE;
//static uint16_t duty_cycle_interrupts;

void timer1_on()
{
    TCCR1B = (1 << CS10) | (1 << WGM12); //här, 
    timer1_enabled = true; //men varför kallar den på motor disabled?
    //serial_print("timer enabled\n");
    return;
}

void timer1_disable()
{
    //serial_print("timer disabled\n");
    //TCCR2B = 0x00;
    TCCR1B = 0x00;
    timer1_enabled = false;
    return;
}

bool timer1_elapsed()
{	
    //serial_print_int("%d\n", executed_interrupts);
	if (++executed_interrupts >= required_interrupts)
	{
        executed_interrupts = 0x00;
        get_new_duty_cycle1();
        //serial_print_int("%d\n", required_interrupts);
		return true;
	}
	return false;
}

bool duty_cycle_elapsed1()
{
    if (++executed_interrupts >= required_interrupts_on) //beehöver ett värde snabbt)duty_cycle_interruptsCalculate_distance()
	{
        //serial_print_int("%d\n", Calculate_distance);
		return true;
	}
	return false;
}

void get_new_duty_cycle1()
{
    required_interrupts_on = Calculate_distance();
    return;
}

void reverse_timer_on()
{
    TIMSK2 = (1 << OCIE2A); 
    reverse_timer_enabled = true; 
    //serial_print("timer2 enabled\n");
    return;
}

void reverse_timer_off()
{
    //serial_print("timer2 disabled\n");
    reverse_executed_interrupts = 0x00;
    TIMSK2 = 0x00;
    reverse_timer_enabled = false;
    return;
}

bool reverse_timer_elapsed()
{
    
    if (++reverse_executed_interrupts >= reverse_total_interrupts)
	{
        //serial_print("end reverse\n");
        
        reverse_executed_interrupts = 0x00;
        
      
		return true;
	}
    
	return false;
}

bool start_reversing()
{
    
    if (reverse_executed_interrupts == required_interrupts_for_reverse) 
	{
        //serial_print("start reverse\n");
        
		return true;
	}
	return false;
}
