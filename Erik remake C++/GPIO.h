#ifndef GPIO_H_
#define GPIO_H_

#include "definitions.h"

class GPIO
{
protected:
	uint8_t PIN = 0x00;
	IO_port io_port = IO_port::None;
	
public:	
	static void delay(const size_t delay_time)
	{
		for (size_t i = 0; i < delay_time; i++)
			_delay_ms(1);
		return;
	}
};

#endif /* BUTTON_H_ */