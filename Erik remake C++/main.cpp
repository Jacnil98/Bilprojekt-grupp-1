#include "header.h"

int main(void)
{
	Serial::init();
    // button.enable_interrupt();
	pwm_timer.on();
	
	Sensor sensor(0, 1, 90, 1, 0.01, 0.1, 30, 150);
	
	for (double i = sensor.min(); i <= sensor.max(); i += 100)
	{
		sensor.set_input(i, sensor.max() - i);
		sensor.regulate();
		sensor.print();
	}
	
    while (true) 
    {
	
    }
	
	return 0;
}

