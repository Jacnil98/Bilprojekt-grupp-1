#include "header.h"

static void init_ports();
static void init_timer();
static void init_serial();
static void init_interrupts();

void setup()
{
    required_interrupts = 0x00;
    executed_interrupts = 0x00;
    servo_enabled = false;
    init_ports();
    init_timer();
    init_interrupts();
    init_serial();
    return;
}

static void init_ports()
{

    return;
}

static void init_timer()
{
    asm("sei");
    TCCR1B = (1 << CS10) | (1 << WGM12);
    OCR1A = 255;
    //Starta timern direkt? TIMSK1 = (1 << OCIE1A);
    return;
}

static void init_serial()
{

    return;
}

static void init_interrupts()
{
    asm("SEI");
    PCICR |= ((1<<PCIE0) | (1 << PCIE2));
    PCMSK2 |= (1<<PCINT5);
    PCMSK0 |= (1 << PCINT1);
    return;
}