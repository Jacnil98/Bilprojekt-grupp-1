#include "header.h"

int main(void)
{
	Serial::init();
	
	//TCCR2B = (1<<CS20);
	
    button.enable_interrupt();
	
	// Sensor sensor(0, 2, 90, 1, 0.01, 0.1, 30, 150);
	/*for (double i = sensor.min(); i <= sensor.max(); i += 100)
	{
		sensor.set_input(i, sensor.max() - i);
		sensor.regulate();
		sensor.print();
	}
	*/
    while (true) 
    {
	
    }
	
	return 0;
}

