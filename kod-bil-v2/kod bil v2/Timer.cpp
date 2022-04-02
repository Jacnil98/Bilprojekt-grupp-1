#include "GPIO.h"

static inline uint32_t get_interrupts(const double period);

PWM_Timer::PWM_Timer(const TimerSelection timerSelection, const double period, const uint8_t PIN)
{
	this->timerSelection = timerSelection;
	this->PIN = FWD_SENSOR;
	this->total_interrupts = get_interrupts(period);
	
	this->init();
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
* Funktionen Timer_off används för att inaktivera en given timer. Ingående
* argument self utgör en pekare till ett timerobjekt, vars medlem
* timerSelection undersöks för att ta reda på vilken timerkrets som skall
* inaktiveras. Aktuell timerkrets inaktiveras, följt av att medlemmen enabled
* sätts till false för att indikera att timern i fråga nu är inaktiverad.
******************************************************************************/
void PWM_Timer::update()
{
	const uint16_t ADC_result = GPIO::ADC_read(this->PIN);
	this->required_interrupts = (uint32_t)(ADC_result / ADC_MAX * this->total_interrupts + 0.5); // On-time, avrundat till närmaste heltal.
	this->pwm_period = PWM_Period::ON;
	this->executed_interrupts = 0x00;
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
		this->executed_interrupts = 0x00;
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

static inline uint32_t get_interrupts(const double period)
{
	return (uint32_t)(period / 0.016f + 0.5);
}