#include "Header.h"

ISR(PCINT2_vect) //denna får vi dubbelkolla
{
    if(BUTTON_IS_PRESSED) 
    {
        motor_forward();
        motor_toggle(); //gör något gött
    }
    return;
}


ISR (TIMER1_COMPA_vect)
{
	if(timer1_elapsed())
    {
        // serial_print("on\n");
        MOTOR_ON;
    }
    
    if(duty_cycle_elapsed1())
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