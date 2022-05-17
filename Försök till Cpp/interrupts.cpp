#include "header.h"


ISR (TIMER0_OVF_vect)
{
	servo_timer.count_interrupts();
	if (servo_timer.servo_elapsed())
		servo_timer.servo_update();//fixa uträkning och inställningar för timer 0
	return;
}

/******************************************************************************
* Timer 1 används för PWM till motorn, Update läser av främre sensron via 
* funktonen ADC_read, sätter period till ON samt nollställer executed_interrupts
*
* Count interrupts ittererar executed_interrupts on PWM_timer är enabled=true.
*
* elapsed jämför executed_interrupts med required_interrupts och när executed är
* större eller lika med required så sätts period till off och en ny uppräkning 
* för off tiden startar.
******************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	pwm_timer.count_interrupts();
	if (pwm_timer.elapsed())
		pwm_timer.update();
	return;
}

/******************************************************************************
* avbrottsrutin som ska användas vid start av tävling.
* PCICR = (1<<PCINT1);   PCICR = 0x00; PIN 9
******************************************************************************/
ISR (PCINT0_vect)
{
	if (button.is_pressed()) motor.toggle();
	return;
}