#include "GPIO.h"

static inline uint32_t get_interrupts(const double period);

PWM_Timer::PWM_Timer(const TimerSelection timerSelection, const double period, const uint8_t PIN)
{
	this->timerSelection = timerSelection;
	this->PIN = PIN;
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
* Funktionen update läser av främre sensorn (sensor_PIN) via funktionen 
* calculate och ger ett värde från 0-1023 som motsvarar 8 bitar, detta omvandlas
* till det ett värde mellan 0 och antalet interrupts som genereras av timer1 
* under en duty_cycle som är 625st för 10ms.
* Period sätts till ON och executed_interrupts nollställs och motorn sätts igång
* via funktionen on i motorclassen.
******************************************************************************/
void PWM_Timer::update()
{
	if (!this->enabled)	 return;
	const uint16_t ADC_result = sensor.calculate(); //GPIO::ADC_read(motor.get_sensor_PIN());
	serial_print_int(ADC_result);
	this->required_interrupts = (uint32_t)(ADC_result / ADC_MAX * this->total_interrupts + 0.5);
	this->pwm_period = PWM_Period::ON; 
	this->executed_interrupts = 0x00;
	motor.on(); 
	return;
}

void PWM_Timer::servo_update()
{
	//const uint8_t mapped_position = sensor.set_input(); // set_input förväntas skickas med 2 värden! vilka? //GPIO::ADC_read(motor.get_sensor_PIN());
	sensor.set_input(0, 2);
	pid_controller.regulate();
	//utvärde?
	//räkna om till HZ
	this->servo_period = PWM_Period::ON;
	this->executed_interrupts = 0x00;
	servo.on();
	return;
}

/******************************************************************************
* Funktionen switched mode kallas på så fort antalet timergenererade avbrott
* överstigit required interrupts i funktionen elapsed. 
* Den används för att beräkna required_interrupts för period OFF, om inte 
* tidigare vilkor var OFF, då kallas funktionen update och antalet interrupts
* för period ON beräknas.
******************************************************************************/
void PWM_Timer::switch_mode(void)
{
	if (this->pwm_period == PWM_Period::ON) 
	{
		this->pwm_period = PWM_Period::OFF; 
		this->required_interrupts = this->total_interrupts - this->required_interrupts; 
		this->executed_interrupts = 0x00;
		motor.off(); 
	}
	else
		this->update();
	return;
}

void PWM_Timer::switch_servo_mode()
{
	if (this->servo_period == PWM_Period::ON)
	{
		this->servo_period = PWM_Period::OFF;
		this->required_interrupts = this->total_interrupts;
		this->executed_interrupts = 0x00;
		servo.off();
	}
	else
	this->servo_update();
	return;
}

/******************************************************************************
* Funktionen elapsed kallar på funktionen switch mode för att sätta period till
* ON eller OFF beroende på tidigare tillstånd när executed interrupts blir
* lika eller högre än required_interrupts.
******************************************************************************/
bool PWM_Timer::elapsed(void)
{
	if (this->executed_interrupts >= this->required_interrupts) 
	{
		this->switch_mode();
		return true;
	}
	return false;
}

bool PWM_Timer::servo_elapsed()
{
	if (this->executed_interrupts >= this->required_interrupts)
	{
		this->switch_servo_mode();
	}
	return false;
}

/******************************************************************************
* Funktioonen count_interrupts anropas av Timer1 vid timergenererat avbrott,
* den börjar då räkna upp om vilkoret är uppfyllt.
******************************************************************************/
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

/******************************************************************************
* Funktioonen get_interrupts kallas på vid initiering för att beräkna antalet
* avbrott som krävs för en bestämd periodtid, som i detta fallet är 10ms och 
* ger 625 avbrott. som "ges" till variabeln total_interrupts.
******************************************************************************/
static inline uint32_t get_interrupts(const double period)
{
	return (uint32_t)(period / 0.016f + 0.5);
}