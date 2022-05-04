#include "header.h"

ISR(PCINT0_vect) //denna får vi dubbelkolla
{
    serial_print("button is pressed\n");
    if(BUTTON_IS_PRESSED) 
    {
        serial_print("button is pressed\n");
        motor_toggle(); //gör något gött
    }
    return;
}


ISR (TIMER2_COMPA_vect)
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