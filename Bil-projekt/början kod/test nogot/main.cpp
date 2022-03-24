
#include "header.h"

Button button;
Actuator actuator;
int main(void)
{
    button = Button(13);
	actuator = Actuator(5);
    while (1) 
    {
		if (button.is_pressed())
			actuator.on();
		else
			actuator.off();
    }
}

