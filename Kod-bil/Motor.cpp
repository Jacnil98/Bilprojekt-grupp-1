#include "GPIO.h"


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
* p� PORTB PIN 9
* motor_enable s�tts av respektive p� av funktionerna enabled/disabled.
******************************************************************************/
void Motor::toggle(void)
{
	if (this->motor_enabled) this->disabled();
	else this->enabled();
}

void Motor::read_direction(void)
{
	if (forward_enabled)
	{
		PORTD |= (1<<IN1);
		PORTD &= ~(1<<IN2);
	}
	else if (!forward_enabled)
	{
		PORTD |= (1<<IN2);
		PORTD &= ~(1<<IN1);
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
* enable ska aktivera PWM_Timer f�r motorn samt starta motorn via funktionen on.
******************************************************************************/
void Motor::enabled()
{
	this->motor_enabled = true;
	ENABLE_TIMER1;
	this->on();
}
/******************************************************************************
* enable ska avaktivera PWM_Timer f�r motorn samt st�nga motorn via funktionen off.
******************************************************************************/
void Motor::disabled()
{
	this->motor_enabled = false;
	DISABLE_TIMER1; 
	this->off();
}


void Motor::PWM()
{
	
}

bool Motor::is_enabled()
{
	return this->motor_enabled;
}