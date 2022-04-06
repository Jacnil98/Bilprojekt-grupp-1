#include "header.h"


int main(void)
{
	init_GPIO();
	
	while (1)
	{
		sensor.calculate();
				
	}
}

