
#ifndef TIMER_H_
#define TIMER_H_

#include "definitions.h"

class Timer
{
protected:
	static constexpr auto INTERRUPT_TIME = 0.016;
	
	TimerSelection timerSelection = TimerSelection::None;
	volatile uint32_t executed_interrupts = 0x00;
	volatile uint32_t required_interrupts = 0x00;
	static void init(const TimerSelection timerSelection);
	static void disable(const TimerSelection timerSelection);
	static uint32_t get_required_interrupts(const double delay_time) { return (uint32_t)(delay_time / Timer::INTERRUPT_TIME + 0.5); }
public:
bool enabled = false;
	Timer(void) { }
	Timer(const TimerSelection timerSelection, const double delay_time);
	~Timer(void);
	double delay_time(void) { return (double)(this->required_interrupts * INTERRUPT_TIME); }
	bool is_enabled(void) { return this->enabled; }
	void on(void);
	void off(void);
	void toggle(void);
	bool elapsed(void);
	void clear(void) { this->executed_interrupts = 0x00; }
	void reset(void);
	void set(const double delay_time) { this->required_interrupts = this->get_required_interrupts(delay_time); }
};

#endif /* TIMER_H_ */