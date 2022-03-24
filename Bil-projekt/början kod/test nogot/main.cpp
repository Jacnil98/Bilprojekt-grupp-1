
#include "header.h"

Button button;
Motor Motor;
int main(void)
{
    button = Button(13);
	Motor = Motor(5);
    while (1) 
    {
		if (button.is_pressed())
			Motor.on();
		else
			Motor.off();
    }
}

