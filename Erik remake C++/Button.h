
#ifndef BUTTON_H_
#define BUTTON_H_

#include "definitions.h"
#include "GPIO.h"

class Button : public GPIO
{
protected:
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