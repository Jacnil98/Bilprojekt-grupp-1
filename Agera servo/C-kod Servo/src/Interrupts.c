#include "header.h"

/**************************************************************************
 * Timer 1 styr PWM funktionen för servot, där timer elapsed räknar 
 * periodtiden och dutycycle elapsed beräknar ON tiden för att styra 
 * positionen för servot där 1.5ms är rakt fram, 0.7ms är 90 grader vänster
 * och 2.3ms är 90 grader höger. periodtiden är 4ms vilket ger en 
 * frekvens på 250Hz
**************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	if(timer_elapsed())
    {
        SERVO_ON;
    }
    
    if(duty_cycle_elapsed())
    {
        SERVO_OFF;
    }

	return;
}
