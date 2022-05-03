#include "header.h"

static void motor_enable();
static void motor_disable();
static void motor_on();
static void motor_off();

void motor_toggle()
{
    if(motor_enabled)
        motor_disable();
    else
        motor_enable();
    return;
}

void motor_forward()
{
    PORTB |= (1<<MOTOR_DIRECTION1);
    PORTB &= ~(1<<MOTOR_DIRECTION2);
    return;
}
void motor_backwards()
{
    PORTB &= ~(1<<MOTOR_DIRECTION1);
    PORTB |= (1<<MOTOR_DIRECTION2);
    return;
}

static void motor_enable()
{
    motor_enabled = true;
    timer_enable();
    motor_on();
    return;
}

static void motor_disable()
{
    motor_enabled = false;
    timer_disable();
    motor_off();
    return;
}

static void motor_on()
{
    MOTOR_ON;
    return;
}

static void motor_off()
{
    MOTOR_OFF;
    return;
}