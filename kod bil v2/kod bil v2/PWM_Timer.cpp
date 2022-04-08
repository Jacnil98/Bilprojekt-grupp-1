#include "GPIO.h"
#include "header.h"
static inline uint32_t get_interrupts(const double period);

PWM_Timer::PWM_Timer(const TimerSelection timerSelection, const double period, const uint8_t PIN)
{
	this->timerSelection = timerSelection;
	this->PIN = PIN;
	this->total_interrupts = get_interrupts(period);
	this->init();
	serial_print("PERIOD: ");
	serial_print_int(period);
	serial_print("\nPIN: ");
	serial_print_int(PIN);
	serial_print("\ntotal_interrupts: ");
	serial_print_int(total_interrupts);
	serial_print("\n ");
	return;
}

void PWM_Timer::init(void)
{
	asm("SEI");
	
	if (this->timerSelection == TimerSelection::TIMER0)
		TCCR0B = (1 << CS00);
	
	else if (this->timerSelection == TimerSelection::TIMER1)
	{
		TCCR1B = (1 << CS10) | (1 << WGM12);
		OCR1A = 256;
	}
	
	else if (this->timerSelection == TimerSelection::TIMER2)
		TCCR2B = (1 << CS20);
	return;
}


/******************************************************************************
* 
******************************************************************************/
void PWM_Timer::update()
{
	if (!this->enabled)	 return;
	const uint16_t ADC_result = GPIO::ADC_read(motor.get_sensor_PIN());
	serial_print("ADC value: ");
	serial_print_int(ADC_result);
	serial_print("\n");
	this->required_interrupts = (uint32_t)(ADC_result / ADC_MAX * this->total_interrupts + 0.5); // On-time, avrundat till närmaste heltal.
	serial_print("Required interrupts during on time: ");
	serial_print_int(this->required_interrupts);
	serial_print("of 625 in total!\n");
	this->pwm_period = PWM_Period::ON;
	this->executed_interrupts = 0x00;
	motor.on();
	return;
}

// Byter Mode. Om aktuell Mode än ON, så beräknas off-tiden i interrupts.
// Annrars så beräknas en ny on- och off-tid via anrop av metoden update.
void PWM_Timer::switch_mode(void)
{
		
	if (this->pwm_period == PWM_Period::ON)
	{
		this->pwm_period = PWM_Period::OFF;
		this->required_interrupts = this->total_interrupts - this->required_interrupts; // Beräknar off-tid ur periodtid samt on-tid (men med interrupts).
		serial_print("Required interrupts during off time: ");
		serial_print_int(this->required_interrupts);
		serial_print("of 625 in total!\n");
		this->executed_interrupts = 0x00;
		motor.off();
		
	}
	
	else
		this->update();
	return;
}

bool PWM_Timer::elapsed(void)
{
	if (this->executed_interrupts >= this->required_interrupts) 
	{
		this->switch_mode();
		return true;
	}
	
	return false;
}

void PWM_Timer::count_interrupts()
{
	if (this->enabled) 
	{
		this->executed_interrupts++;
	}
	
	else 
	{
		this->executed_interrupts = 0x00;
	}
	

	
}

void PWM_Timer::PWM_function()
{
	if(this->pwm_period == PWM_Period::ON) 
	{
		// serial_print_int(1);
		motor.on();
	}
	if(this->pwm_period == PWM_Period::OFF)
	{
		// serial_print_int(2);
		motor.off();
	}
}

static inline uint32_t get_interrupts(const double period)
{
	serial_print("Number of interrupts: ");
	serial_print_int((uint32_t)(period / 0.016f + 0.5));
	serial_print("\n");
	return (uint32_t)(period / 0.016f + 0.5);
}