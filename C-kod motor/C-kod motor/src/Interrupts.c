#include "header.h"

ISR (PCINT0_vect)
{
    if(BUTTON_IS_PRESSED) 
    {
        motor_toggle(); //gör något gött
    }
    return;
}

ISR (TIMER1_COMPA_vect)
{
	
	return;
}