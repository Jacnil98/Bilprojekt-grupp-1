#include "header.h"

ISR (TIMER1_COMPA_vect)
{
	if(timer_elapsed())
    {
        // serial_print("on\n");
        SERVO_ON;
    }
    
    if(duty_cycle_elapsed())
    {
        //serial_print("off\n");
        SERVO_OFF;
    }

	return;
}
