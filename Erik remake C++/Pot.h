
#ifndef POT_H_
#define POT_H_

#include "definitions.h"

class Pot
{
protected:
	uint8_t PIN = 0x00;
	static constexpr double ADC_MIN = 0.0;
	static constexpr double ADC_MAX = 1023.0;
	static void init(void);
public:
	Pot(void) { }
	Pot(const uint8_t PIN);
	~Pot(void) { }
	static constexpr double output_min(void) { return Pot::ADC_MIN; }
	static constexpr double output_max(void) { return Pot::ADC_MAX; }
	uint16_t read(void);
	double duty_cycle(void) { return this->read() / ADC_MAX; }
	double on_time(const double period) { return this->duty_cycle() * period; }
	double off_time(const double period) { return period - this->on_time(period); }
	uint32_t get_interrupts_on_time(const uint32_t total_amount_of_interrupts) 
		{ return (uint32_t)(total_amount_of_interrupts * this->duty_cycle() + 0.5);}
	uint32_t get_interrupts_off_time(const uint32_t total_amount_of_interrupts)
		{ return (uint32_t)(total_amount_of_interrupts - this->get_interrupts_on_time(total_amount_of_interrupts)); }
};

#endif /* POT_H_ */