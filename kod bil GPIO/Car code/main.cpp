#include "header.h"
// f�r motor, l�gg till bit ADPS0 i Analog f�r ADC
//Output output(4);  //oanvänd
Button button(9);
Motor motor(7, 8, 5, TimerSelection::Timer2, 10, 1);
Servo servo(6, 2, 0, TimerSelection::Timer1, 10);

int main(void)
{
	//Serial::init();
	button.enable_interrupt();
	servo.enable(); //kommentera bort f�r koden f�r motorn
	while (true)
	{
	}
	
	return 0;
}

