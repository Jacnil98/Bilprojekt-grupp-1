#include "header.h"

ISR(PCINT0_vect) //denna får vi dubbelkolla
{
    if(BUTTON_IS_PRESSED) 
    {
        serial_print("button is pressed\n");
        motor_forward();
        motor_toggle(); //gör något gött
        //motor_enable();
    }
    return;
}


ISR (TIMER1_COMPA_vect)
{
	if(timer_elapsed())
    {
        // serial_print("on\n");
        MOTOR_ON;
    }
    
    if(duty_cycle_elapsed())
    {
        //serial_print("off\n");
        MOTOR_OFF;
    }

	return;
}

ISR (TIMER2_OVF_vect)
{
	
	return;
}