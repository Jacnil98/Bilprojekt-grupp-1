#include "header.h"
/**************************************************************************
 * servo enable startar timmer 1 för pwm funktionen.
**************************************************************************/
void servo_enable()
{
    servo_enabled = true;
    timer_on();
    return;
}

/**************************************************************************
 * servo enable startar timmer 1 för pwm funktionen.
**************************************************************************/
void Servo_disable()
{
    servo_enabled = false;
    timer_disable();
    return;
}