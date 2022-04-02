#include "GPIO.h"


ISR (TIMER0_OVF_vect)
{
	
	return;
}

/******************************************************************************
* avbrottsrutin som ska användas vid start av tävling.
* PCICR = (1<<PCINT1);   PCICR = 0x00; PIN 9
******************************************************************************/
ISR (PCINT1_vect)
{
	//if (button.is_pressed()) motor.toggle();
	return;
}