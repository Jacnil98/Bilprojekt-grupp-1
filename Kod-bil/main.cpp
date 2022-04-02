#include "header.h"


int main(void)
{
    init_GPIO();
	
    while (1) 
    {
		if (button.is_pressed())
			motor.off();
		else
			motor.on();	
			
			
    }
}

