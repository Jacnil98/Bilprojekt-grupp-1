#include "header.h"

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
    motor_reverse = false;
    CONNECTION_OFF;
    serial_print("connection off");
    PORTD |= (1<<MOTOR_DIRECTION1);
    PORTB &= ~(1<<MOTOR_DIRECTION2);
    return;
}
void motor_backwards()
{
    motor_reverse = true;
    CONNECTION_ON;
    serial_print("connection on");
    PORTD &= ~(1<<MOTOR_DIRECTION1);
    PORTB |= (1<<MOTOR_DIRECTION2);
    return;
}


void motor_enable()
{
    //serial_print("motor enabled\n");
    motor_enabled = true;
    timer_on();
    return;
}

void motor_disable()
{
    //serial_print("motor disabled\n");
    motor_enabled = false;
    timer_disable();
    MOTOR_OFF;
    return;
}

void check_start_button()
{
    if(BUTTON_IS_PRESSED)
        {
            motor_enable();
        }
    else
        motor_disable();
    return;
}