#include "header.h"
/**************************************************************************
 * PCINT0_vect läser av om startknappen trycks ner, då sätts körriktningen
 * till framåt och motorn togglas, denna funktion användes vid 
 * tillfällig startknapp.
**************************************************************************/
ISR(PCINT0_vect) 
{
    if(BUTTON_IS_PRESSED) 
    {
        motor_forward();
        motor_toggle(); 
    }
    return;
}

/**************************************************************************
 * Timer 1 styr PWM funktionen för motorn, där timer elapsed räknar 
 * periodtiden och dutycycle elapsed beräknar ON tiden för att stänga av
 * motorn när den löpt ut.
**************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	if(timer_elapsed())
    {
        MOTOR_ON;
    }
    
    if(duty_cycle_elapsed())
    {
        MOTOR_OFF;
    }

	return;
}

/**************************************************************************
 * Timer 2 styr backfunktionen där reverse timer elapsed räknar upp till
 * 6 sekunder, om timern fortfarande är igång efter 3 sekunder börjar 
 * bilen backa via funktionen start reversing. om avståndet överstiger 
 * MAX_DISTANCE eller om timern löper ut så börjar bilen köra framåt igen.
**************************************************************************/
ISR (TIMER2_COMPA_vect)
{
    
	if(reverse_timer_elapsed())
    {
        motor_forward();
    }

    if(start_reversing())
    {
        motor_backwards();
    }
	return;
}