#include "header.h"

/**************************************************************************
 * motor toggle läser av om motorn är enabled eller inte och togglar motorn
 * till motsatta värde.
**************************************************************************/
void motor_toggle()
{
    if(motor_enabled)
        motor_disable();
    else
        motor_enable();
    return;
}

/**************************************************************************
 * motor forward/backward sätter 2 siognaler till H bryggan som beroende 
 * på vilken som är hög och låg gör att motorn backar eller kör framåt.
**************************************************************************/
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

/**************************************************************************
 * motor enable/disable sätter motorn enable till true eller false, vid 
 * enable så sätts motor enable till true och timer 1 startar.
 * vid disable så stängs timer 1 av och motor enable sätts till false 
 * och motorn stängs av.
**************************************************************************/
void motor_enable()
{
    motor_enabled = true;
    timer_on();
    return;
}

void motor_disable()
{
    motor_enabled = false;
    timer_disable();
    MOTOR_OFF;
    return;
}

/**************************************************************************
 * check start button läser av om startknappen vid tävling är aktiv och 
 * håller då motor enable true tills signalen försvinner.
**************************************************************************/
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