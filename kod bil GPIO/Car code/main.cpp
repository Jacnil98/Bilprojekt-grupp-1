#include "header.h"

Output output(4);  //oanvänd
Button button(9);
Motor motor(7, 8, 5, TimerSelection::Timer2, 10, 1);
Servo servo(6, 2, 0, TimerSelection::Timer1, 2);

int main(void)
{
	Serial::init();
	button.enable_interrupt();
	
	while (true)
	{
	}
	
	return 0;
}

