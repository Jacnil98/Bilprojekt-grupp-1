#include "header.h"

static void init_ports();
static void init_interrupts();
static void init_ADC();
static void init_timer();

void setup()
{
    required_interrupts = 0x00;
    executed_interrupts = 0x00;
    init_ports();
    init_interrupts();
    init_ADC();
    init_timer();
}

static void init_ports()
{
    DDRD |= ((1<<MOTOR) | (1 << MOTOR_DIRECTION1) | (1 << MOTOR_DIRECTION2));
    PORTB |= (1<<(BUTTON - 8));
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

static void init_ADC()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
    return;
}

static void init_timer()
{
    asm("sei");
    TCCR1B = (1 << CS10) | (1 << WGM12);
    OCR1A = 255;
    return;
}