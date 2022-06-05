#include "GPIO.h"

Motor::Motor(const uint8_t PIN)
{
	if(PIN >=0 && PIN <= 7)
	{
		this->io_port = IO_port::D;
		this->PIN = PIN;
		DDRD |= (1<< this->PIN);
	}
	else if (PIN >= 8 && PIN <= 13)
	{
		this->io_port = IO_port::B;
		this->PIN = PIN - 8;
		DDRB |= (1<< this->PIN);
	}
	this->sensor_PIN = 1;
	this->sensor_io_port = IO_port::C;
}

/******************************************************************************
* Motor on anv�nds f�r att starta motorn. Detta g�rs genom att ettst�lla
* biten som PIN sitter p� i respektive Port register
******************************************************************************/
void Motor::on(void)
{
	if (this->io_port == IO_port::B)
		PORTB |= (1<< this->PIN);
	else if(this->io_port == IO_port::D)
		PORTD |= (1<< this->PIN);
	this->read_direction();
	this->motor_enabled = true;
	return;
}

/******************************************************************************
* Motor on anv�nds f�r att starta motorn. Detta g�rs genom att nollst�lla
* biten som PIN sitter p� i respektive Port register
******************************************************************************/
void Motor::off(void)
{
	if (this->io_port == IO_port::B)
		PORTB &= !(1 << this->PIN);
	else if(this->io_port == IO_port::D)
		PORTD &= !(1 << this->PIN);
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

/******************************************************************************
* Funktionen read_direktion l�ser av om bilen ska �ka fram�t eller bak�t och 
*  ettst�ller antingen IN1 eller IN2 p� H bryggan f�r att best�mma riktning.
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

/******************************************************************************
* enable ska aktivera PWM_Timer f�r motorn samt starta motorn via funktionen on.
******************************************************************************/
void Motor::enabled()
{
	this->PWM_enabled = true;
	ENABLE_TIMER0;
	ENABLE_TIMER1;
	pwm_timer.enabled = true;
	this->motor_enabled = true;
	
	
}

/******************************************************************************
* enable ska avaktivera PWM_Timer f�r motorn samt st�nga motorn via funktionen off.
******************************************************************************/
void Motor::disabled()
{
	this->PWM_enabled = false;
	DISABLE_TIMER1;
	DISABLE_TIMER0;
	pwm_timer.enabled = false;
	this->motor_enabled = false;
	this->off();
	return;
	
}

/******************************************************************************
*
******************************************************************************/
bool Motor::is_enabled()
{
	return this->motor_enabled;
}

/******************************************************************************
* Forward direction �ndrar riktningen p� motorn fram�t genom att ettst�lla 
* biten IN1 samt nollst�lla bit IN2 i registret PORTD
******************************************************************************/
void Motor::forward_direction()
{
	PORTD |= (1<<IN1);
	PORTD &= ~(1<<IN2);
}

/******************************************************************************
* Reverse direction �ndrar riktningen p� motorn bak�t genom att ettst�lla
* biten IN2 samt nollst�lla bit IN1 i registret PORTD
******************************************************************************/
void Motor::reverse_direction()
{
	PORTD |= (1<<IN2);
	PORTD &= ~(1<<IN1);
}
