#include "Header.h"

void servo_enable()
{
    //serial_print("servo enabled\n");
    servo_enabled = true;
    timer_on();
    return;
}

void Servo_disable()
{
    //serial_print("motor disabled\n");
    servo_enabled = false;
    timer_disable();
    return;
}