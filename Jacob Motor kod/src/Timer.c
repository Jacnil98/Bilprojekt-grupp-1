#include "Header.h"

static volatile uint16_t required_interrupts = PERIOD / INTERRUPT_TIME;
static volatile uint16_t required_interrupts_on;
static volatile uint16_t executed_interrupts;

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

void timer2_on()
{

    return;
}

void timer2_disable()
{

    return;
}

bool timer2_elapsed()
{

    return;
}

bool duty_cycle_elapsed2()
{

    return;
}

void get_new_duty_cycle2()
{

    return;
}
