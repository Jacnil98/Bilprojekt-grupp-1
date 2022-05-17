#include "Header.h"

static void motor_enable();
static void motor_disable();


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
    PORTB |= (1 << 0);
    PORTB &= ~(1 << 3);
    return;
}
void motor_backwards()
{
    motor_reverse = true;
    CONNECTION_ON;
    PORTB &= ~(1<< 0);
    PORTB |= (1<< 3);
    return;
}

static void motor_enable()
{
    //serial_print("motor enabled\n");
    motor_enabled = true;
    timer1_on();
    return;
}

static void motor_disable()
{
    //serial_print("motor disabled\n");
    motor_enabled = false;
    timer1_disable();
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
        {
            motor_disable();
        }
    return;
}