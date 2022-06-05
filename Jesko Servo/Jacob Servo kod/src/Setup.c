#include "Header.h"

static void init_ports();
static void init_interrupts();
static void init_ADC();
static void init_timer();
static void init_serial();

void setup()
{
    init_ports();
    init_interrupts();
    init_ADC();
    init_timer();
    init_serial();
}

static void init_ports()
{
    DDRD |= (1<<SERVO_PIN);
    PORTB |= (1 << CONNECTION);
    return;
}

static void init_interrupts()
{
    asm("SEI");
    PCICR |= ((1<<PCIE0) | (1 << PCIE2)); 
    //PCMSK0 |= (1 << BUTTON); 
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
    TCCR1B = ((0 << CS12) | (1 << CS11) | (0 << CS10) | (1 << WGM12));
    TIMSK1 = (1 << OCIE1A);
	OCR1A = 255;
    return;
}

static void init_serial()
{
	UCSR0B = (1 << TXEN0); //ENABLE_SERIAL_TRANSFER;
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));//SET_TRANSMISSION_SIZE;
	UBRR0 = 103;//SET_BAUD_RATE_9600_KBPS;
	return;
}