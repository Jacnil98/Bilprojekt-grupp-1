
#ifndef GPIO_H_
#define GPIO_H_
#include "definitions.h"

class GPIO
{
	protected:
	uint8_t PIN = 0x00;
	IO_port io_port = IO_port::NONE;
};

class Motor : public GPIO
{
private:
	bool enabled = false;
public:
	Motor(void) {}
	Motor(const uint8_t PIN);
	void on(void);
	void off(void);
	void toggle(void);
	bool is_enabled(void){return this->enabled; }
};


class Button : public GPIO
{
private:
	bool interrupt_enabled = false;
public:
	
	Button(void) {}
	Button(const uint8_t PIN);
	bool is_pressed(void);
	void enable_interrupt();
	void disable_interrupt(void);
	bool interrupt_is_enabled(void) {return this->interrupt_enabled; }
};


#endif /* BUTTON_H_ */