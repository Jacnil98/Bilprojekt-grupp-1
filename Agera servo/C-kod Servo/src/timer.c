#include "header.h"

static volatile uint16_t required_interrupts = PERIOD / INTERRUPT_TIME;
static volatile uint16_t executed_interrupts;

/**************************************************************************
 * timer on startar timer 1
**************************************************************************/
void timer_on()
{
    TCCR1B = (1 << CS10) | (1 << WGM12); 
    timer_enabled = true;
    serial_print("timer enabled\n");
    return;
}

/**************************************************************************
 * timer disable stänger av timer 1
**************************************************************************/
void timer_disable()
{
    serial_print("timer disabled\n");
    TCCR1B = 0x00;
    timer_enabled = false;
    return;
}
/**************************************************************************
 * timer elapsed räknar period tiden för servot och nollställer räknaren 
 * när executed interrupts är högre eller lika högt som 
 * required interrupts.
**************************************************************************/
bool timer_elapsed()
{	
	if (++executed_interrupts >= required_interrupts)
	{
        executed_interrupts = 0x00;

		return true;
	}
	return false;
}

/**************************************************************************
 * duty cycle elapsed räknar ON tiden för servot som bestämmer position, 
 * värdet jämförs med output som är utsignalen från pid regleringen.
**************************************************************************/
bool duty_cycle_elapsed()
{
    
    if (++executed_interrupts >= output) 
	{
		return true;
	}
	return false;
}