#include "header.h"


ISR (TIMER0_OVF_vect)
{
	servo_timer.count_interrupts();
	if (servo_timer.servo_elapsed())
		servo_timer.servo_update();//fixa utr�kning och inst�llningar f�r timer 0
	return;
}

/******************************************************************************
* Timer 1 anv�nds f�r PWM till motorn, Update l�ser av fr�mre sensron via 
* funktonen ADC_read, s�tter period till ON samt nollst�ller executed_interrupts
*
* Count interrupts ittererar executed_interrupts on PWM_timer �r enabled=true.
*
* elapsed j�mf�r executed_interrupts med required_interrupts och n�r executed �r
* st�rre eller lika med required s� s�tts period till off och en ny uppr�kning 
* f�r off tiden startar.
******************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	pwm_timer.count_interrupts();
	if (pwm_timer.elapsed())
		pwm_timer.update();
	return;
}

/******************************************************************************
* avbrottsrutin som ska anv�ndas vid start av t�vling.
* PCICR = (1<<PCINT1);   PCICR = 0x00; PIN 9
******************************************************************************/
ISR (PCINT0_vect)
{
	if (button.is_pressed()) motor.toggle();
	return;
}