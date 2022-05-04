#include "header.h"

ISR(TIMER1_COMPA_vect)
{
    if(servo_elapsed())
    {
        switch_servo_mode();
    }
    return;
}