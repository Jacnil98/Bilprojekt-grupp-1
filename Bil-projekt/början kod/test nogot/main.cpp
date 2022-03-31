
#include "header.h"

Button button;
Motor motor;
int main(void)
{
    button = Button(13);
	motor = Motor(5);
    while (1) 
    {
		if (button.is_pressed())
			Motor.on();
		else
			Motor.off();
    }
}

