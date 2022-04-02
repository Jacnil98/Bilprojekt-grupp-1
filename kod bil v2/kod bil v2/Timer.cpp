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
* Funktionen Timer_off anv�nds f�r att inaktivera en given timer. Ing�ende
* argument self utg�r en pekare till ett timerobjekt, vars medlem
* timerSelection unders�ks f�r att ta reda p� vilken timerkrets som skall
* inaktiveras. Aktuell timerkrets inaktiveras, f�ljt av att medlemmen enabled
* s�tts till false f�r att indikera att timern i fr�ga nu �r inaktiverad.
******************************************************************************/
void PWM_Timer::update()
{
	const uint16_t ADC_result = GPIO::ADC_read(this->PIN);
	this->required_interrupts = (uint32_t)(ADC_result / ADC_MAX * this->total_interrupts + 0.5); // On-time, avrundat till n�rmaste heltal.
	this->pwm_period = PWM_Period::ON;
	this->executed_interrupts = 0x00;
	return;
}

// Byter Mode. Om aktuell Mode �n ON, s� ber�knas off-tiden i interrupts.
// Annrars s� ber�knas en ny on- och off-tid via anrop av metoden update.
void PWM_Timer::switch_mode(void)
{
	if (this->pwm_period == PWM_Period::ON)
	{
		this->pwm_period = PWM_Period::OFF;
		this->required_interrupts = this->total_interrupts - this->required_interrupts; // Ber�knar off-tid ur periodtid samt on-tid (men med interrupts).
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