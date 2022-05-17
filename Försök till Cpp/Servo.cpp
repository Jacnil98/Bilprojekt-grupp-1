#include "GPIO.h"

Servo::Servo(const uint8_t PIN)
{
	if(PIN >=0 && PIN <=7)
	{
		this->io_port = IO_port::D;
		this->PIN = PIN;
		DDRD |= (1<< this->PIN);
	}
	else if (PIN <= 8 && PIN <= 13)
	{
		this->io_port = IO_port::B;
		this->PIN = PIN - 8;
		DDRB |= (1<< this->PIN);
	}
	this->left_sensor_PIN = 0;
	this->right_sensor_PIN = 2;
	this->left_sensor_io_port =IO_port::C;
	this->right_sensor_io_port = IO_port::C;
}

/******************************************************************************
* Servo on används för att starta servot. Detta görs genom att ettställa
* biten som PIN sitter på i respektive Port register
******************************************************************************/
void Servo::on(void)
{
	if(this->io_port == IO_port::B)
		PORTB |= (1<< this->PIN);
	else if(this->io_port == IO_port::D)
		PORTD |= (1<< this->PIN);
	this->servo_enabled = true;
	return;
}

/******************************************************************************
* Servo off används för att stänga av servot. Detta görs genom att nollställa
* biten som PIN sitter på i respektive Port register
******************************************************************************/
void Servo::off(void)
{
	if(this->io_port == IO_port::B)
		PORTB &= !(1 << this->PIN);
	if(this->io_port ==IO_port::D)
		PORTD &= !(1 << this->PIN);
	this->servo_enabled = false;
	return;
}

/******************************************************************************
* Servo toggle används för att toggla ifall servot ska vara enablat eller 
* disableat.
******************************************************************************/
void Servo::toggle(void)
{
	if(this->servo_enabled) this->disabled();
	else this->enabled();
}

/******************************************************************************
* Servo enabled enablar servot genom att sätta på PWM samt timer 0.
******************************************************************************/
void Servo::enabled()
{
	this->PWM_enabled = true;
	ENABLE_TIMER0;
	servo_timer.enabled = true; 
	this->servo_enabled = true;
}

/******************************************************************************
* 
******************************************************************************/
void Servo::disabled()
{
	this->PWM_enabled = false;
	DISABLE_TIMER0;
	servo_timer.enabled = false; 
	this->servo_enabled = false;
	this->off();
	return;
}

/******************************************************************************
* 
******************************************************************************/
bool Servo::is_enabled()
{
	return this->servo_enabled;
}