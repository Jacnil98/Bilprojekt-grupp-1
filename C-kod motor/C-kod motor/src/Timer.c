#include "header.h"

static uint16_t required_interrupts = TOTAL_INTERRUPTS;
static uint16_t required_interrupts_on;
static volatile uint16_t executed_interrupts;
static volatile uint16_t reverse_executed_interrupts;
static uint16_t reverse_total_interrupts = TOTAL_REVERSE_INTERRUPTS;
static uint16_t required_interrupts_for_reverse = INTERRUPTS_REQUIRED_FOR_REVERSE;

/**************************************************************************
 * timer on startar timer 1
**************************************************************************/
void timer_on()
{
    TCCR1B = (1 << CS10) | (1 << WGM12); 
    timer_enabled = true; 
    return;
}

/**************************************************************************
 * timer disable stänger av timer 1
**************************************************************************/
void timer_disable()
{
    TCCR1B = 0x00;
    timer_enabled = false;
    return;
}

/**************************************************************************
 * timer elapsed räknar period tiden och hämtar värdet grån AD omvandligen 
 * via get new duty cycle. om executed interrupts överstiger 
 * required interrupts så returneras true och executed interrupts nollställs
**************************************************************************/
bool timer_elapsed()
{	
	if (++executed_interrupts >= required_interrupts)
	{
        executed_interrupts = 0x00;
        get_new_duty_cycle();
		return true;
	}
	return false;
}

/**************************************************************************
 * duty cycle elapsed räknar ON tiden, och returnerar true om 
 * executed interrupts överstiger required interrupts, då stängs motorn av.
**************************************************************************/
bool duty_cycle_elapsed()
{
    if (executed_interrupts >= required_interrupts_on) 
	{
		return true;
	}
	return false;
}

/**************************************************************************
 * get new duty cycle används för att hämta ett nytt värde från AD omvandligen.
**************************************************************************/
void get_new_duty_cycle()
{
    required_interrupts_on = Calculate_distance();
    
    return;
}

/**************************************************************************
 * reverse timer on startar timer 2 för backfunktionen.
**************************************************************************/
void reverse_timer_on()
{
    TIMSK2 = (1 << OCIE2A); 
    reverse_timer_enabled = true; 
    return;
}
/**************************************************************************
 * reverse timer off stänger av timer 2 för backfunktionen och nollställer
 * räknaren.
**************************************************************************/
void reverse_timer_off()
{
    reverse_executed_interrupts = 0x00;
    TIMSK2 = 0x00;
    reverse_timer_enabled = false;
    return;
}

/**************************************************************************
 * reverse timer elapsed räknar antaled avbrott och stänger av timer 2 
 * om timern löper ut
**************************************************************************/
bool reverse_timer_elapsed()
{
    
    if (++reverse_executed_interrupts >= reverse_total_interrupts)
	{
        reverse_executed_interrupts = 0x00;
		return true;
	}
    
	return false;
}

/**************************************************************************
 * start reversing läser av om timer 2 nått önskat antal interrupts för
 * att starta backfunktionen, när värdet är uppnått startar backen tills
 * timern löper ut.
**************************************************************************/
bool start_reversing()
{
    
    if (reverse_executed_interrupts == required_interrupts_for_reverse) 
	{
		return true;
	}
	return false;
}

