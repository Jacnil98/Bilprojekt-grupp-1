#ifndef GPIO_H_
#define GPIO_H_

#include "definitions.h"
#include "Serial.h"

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

class Output : public GPIO
{
protected:
	bool enabled = false;
public:
	Output(void) { }
	Output(const uint8_t PIN);
	~Output(void);
	bool is_enabled(void) { return this->enabled; }
	void on(void);
	void off(void);
	void toggle(void);
	void blink(const size_t delay_time);
};

class Analog
{
protected:
	uint8_t PIN = 0x00;
	static constexpr double MAX_DISTANCE = 80.0; // max 80, lägre sänker max fart
	static constexpr double MIN_DISTANCE = 10.0; // min 0, högre höjer lägsta hastighet
	static constexpr double DISTANCE_SCALE = 13; // utväxling 12.7 = 1023 vid MAX= 80
	static constexpr double SENSOR_CONSTANT = 0.0048828125;
	static constexpr double ADC_MIN = 0.0;
	static constexpr double ADC_MAX = 1023.0;
	static void init(void);
public:
	Analog(void) { }
	Analog(const uint8_t PIN);
	~Analog(void) { }
	static constexpr double output_min(void) { return Analog::ADC_MIN; }
	static constexpr double output_max(void) { return Analog::ADC_MAX; }
	uint16_t read(void);
	uint16_t calculate(void);
	double duty_cycle(void);
	
	//double duty_cycle(void) { return this->read() / ADC_MAX; }
	double on_time(const double period) { return this->duty_cycle() * period; }
	double off_time(const double period) { return period - this->on_time(period); }
	
	 uint32_t get_interrupts_on_time(const uint32_t total_amount_of_interrupts)
	{ return (uint32_t)(total_amount_of_interrupts * this->duty_cycle() + 0.5);}
	
	uint32_t get_interrupts_off_time(const uint32_t total_amount_of_interrupts)
	{ return (uint32_t)(total_amount_of_interrupts - this->get_interrupts_on_time(total_amount_of_interrupts)); }
};
#endif /* BUTTON_H_ */