	#include "header.h"

	int main(void)
	{
		Setup();
		//float f = 37.7777777;
		while (true) //Skapar en while sats so ska exekverar tills att programmet st�ngs av.
		{
			PWM(); //I while satsen s� anropas PWM funktionen.
		}
		//float rounded_down = roundf(f * 10) / 10;
		return 0;
	}

