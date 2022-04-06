#include "GPIO.h"
#include "header.h"

Motor::Motor(const uint8_t PIN)
{
	if(PIN >=0 && PIN <= 7)
	{
		this->io_port = IO_port::D;
		this->PIN = PIN;
		SET(DDRD, this->PIN);
	}
	else if (PIN >= 8 && PIN <= 13)
	{
		this->io_port = IO_port::B;
		this->PIN = PIN - 8;
		SET (DDRB, this->PIN);
	}
	this->sensor_PIN = 1;
	this->sensor_PCINT = this->sensor_PIN + 8;
	this->sensor_io_port = IO_port::C;
}

void Motor::on(void)
{
	if (this->io_port == IO_port::B)
	SET(PORTB, this->PIN);
	else if(this->io_port == IO_port::D)
	SET(PORTD, this->PIN);
	this->read_direction();
	this->motor_enabled = true;
	return;
}

void Motor::off(void)
{
	if (this->io_port == IO_port::B)
	CLEAR(PORTB, this->PIN);
	else if(this->io_port == IO_port::D)
	CLEAR(PORTD, this->PIN);
	this->motor_enabled = false;
	return;
}

/******************************************************************************
* Funktionen start ska toggla mellan Motor enable och disable via startknappen
* på PORTB PIN 9
* motor_enable sätts av respektive på av funktionerna enabled/disabled.
******************************************************************************/
void Motor::toggle(void)
{
	if (this->motor_enabled) this->disabled();
	else this->enabled();
}

/******************************************************************************
* Funktionen read_direktion läser av om bilen ska åka framåt eller bakåt och 
* och ettställer antingen IN1 eller IN2 på H bryggan för att bestämma riktning.
******************************************************************************/
void Motor::read_direction(void)
{
	if (forward_enabled)
	{
		this->forward_direction();
	}
	else if (!forward_enabled)
	{
		this->reverse_direction();
	}
}


void Motor::enable_interrupt()
{
	PCMSK1 |= (1 << this->sensor_PCINT);
	this->interrupt_enabled = true;
}

void Motor::disable_interrupt()
{
	PCMSK1 &= ~(1 << this->sensor_PCINT);
	this->interrupt_enabled = false;
}

/******************************************************************************
* enable ska aktivera PWM_Timer för motorn samt starta motorn via funktionen on.
******************************************************************************/
void Motor::enabled()
{
	this->PWM_enabled = true;
	ENABLE_TIMER1;
	pwm_timer.enabled = true;
	this->on();
}
/******************************************************************************
* enable ska avaktivera PWM_Timer för motorn samt stänga motorn via funktionen off.
******************************************************************************/
void Motor::disabled()
{
	
	this->PWM_enabled = false;
	DISABLE_TIMER1;
	pwm_timer.enabled = false;
	this->off();
}


void Motor::PWM()
{
	
}

bool Motor::is_enabled()
{
	return this->motor_enabled;
}

void Motor::forward_direction()
{
	PORTD |= (1<<IN1);
	PORTD &= ~(1<<IN2);
}

void Motor::reverse_direction()
{
	PORTD |= (1<<IN2);
	PORTD &= ~(1<<IN1);
}
