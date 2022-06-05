#include "header.h"

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
    motor_disable();
    motor_enabled = false;
    CONNECTION_OFF;
}
/**************************************************************************
 * init ports initierar startknappen (BUTTON), motorn (MOTOR), 
 * motor riktningen (MOTOR_DIRECTION1-2) och anslutningen mellan de båda
 * korten för backfunktionen (CONNECTION)
**************************************************************************/
static void init_ports()
{
    DDRB |= (1<<MOTOR_DIRECTION2);
    DDRD |= ((1<<MOTOR) | (1 << MOTOR_DIRECTION1) | (1<<CONNECTION));
    PORTB |= (1<<BUTTON);
    return;
}

/**************************************************************************
 * init interrupts initierar interrupts på port B och port D
**************************************************************************/
static void init_interrupts()
{
    asm("SEI");
    PCICR |= ((1<<PCIE0) | (1 << PCIE2)); 
    PCMSK0 |= (1 << BUTTON); 
    return;
}

/**************************************************************************
 * en initiering av ADC görs för annars kan första värdet bli dåligt.
**************************************************************************/
static void init_ADC()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
    return;
}

/**************************************************************************
 * timer 1 och 2 initieras i CTC mode där timer 1 styr PWM funktionen 
 * och timer 2 styr backfunktionen, båda sätts till att räkna upp till 250,
 * men med olika prescalers
**************************************************************************/
static void init_timer()
{
    asm("sei");
    TCCR1B = ((0 << CS12) | (1 << CS11) | (0 << CS10) | (1 << WGM12));
    TIMSK1 = (1 << OCIE1A);
	OCR1A = 250;

    TCCR2B = ((1 << CS22) | (1 << CS21) | (1 << CS20));
	TCCR2A = (1 << WGM21);
	OCR2A = 250;
    return;
}

/**************************************************************************
 * init serial initierar utskrift för felsökning
**************************************************************************/
static void init_serial()
{
	UCSR0B = (1 << TXEN0); //ENABLE_SERIAL_TRANSFER;
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));//SET_TRANSMISSION_SIZE;
	UBRR0 = 103;//SET_BAUD_RATE_9600_KBPS;
	return;
}