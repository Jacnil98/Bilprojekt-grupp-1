#include "header.h"
// för motor, lägg till bit ADPS0 i Analog för ADC
//Output output(4);  //oanvÃ¤nd
Button button(9);
Motor motor(7, 8, 5, TimerSelection::Timer2, 10, 1);
Servo servo(6, 2, 0, TimerSelection::Timer1, 10);

int main(void)
{
	//Serial::init();
	button.enable_interrupt();
	servo.enable(); //kommentera bort för koden för motorn
	while (true)
	{
	}
	
	return 0;
}

