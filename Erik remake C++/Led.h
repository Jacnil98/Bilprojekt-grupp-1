
#ifndef LED_H_
#define LED_H_

#include "definitions.h"
#include "GPIO.h"

class Led : public GPIO
{
protected:
	bool enabled = false;
public:
	Led(void) { }
	Led(const uint8_t PIN);
	~Led(void);
	bool is_enabled(void) { return this->enabled; }
	void on(void);
	void off(void);
	void toggle(void);
	void blink(const size_t delay_time);
};


#endif /* LED_H_ */