#include "header.h"

void timer_enable()
{
    TIMSK1 = (1 << OCIE1A);
    timer_enabled = TRUE;
    return;
}

void timer_disable()
{
    TIMSK1 = 0x00;
    timer_enabled = FALSE;
    return;
}