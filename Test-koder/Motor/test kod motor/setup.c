#include "header.h" //Inkluderar egen headerfil.

//Skapar tre statiska funktioner som endast ska användas i setup filen.
static void init_ports();
static void init_ADC();

//Definerar setup funktionen.
void setup()
{
	init_ports();
	init_ADC();
	return;
}

/*************************************************************
Här defineras funktionen init_ports. Det börjar med att sätta
diodern och motorn med hjälp av DDR* (Data direction register
B/D). Sedan sätts de olika knapparna till inportar med hjälp
av registret PORT(B/D).
*************************************************************/
static void init_ports()
{
	DDRB = (1 << IN1);
	DDRB = (1 << IN2);
	DDRD = (1 << MOTOR);
	return;
}

/*************************************************************
Funktionen init_interrupts används för att aktivera PCI-avbrott
på PIN 11 - 13 samt avbrott externt på PIN 2 - 3. Först
aktiveras avbrott globalt via ettställning av biten "I" i
statusregistret SREG via en assemblerinstruktion som heter SEI.
Därefter aktiveras avbrottsvektorn för I/O port B,
PCINT0_vect, Detta görs genom att via ettställa biten PCIE0
(PIN Change Interrupt Enable 0) i kontrollregistret PCICR
(PIN Change Interrupt Control Register).
Därefter aktiveras PCI-avbrott PCINT5 på
PIN 13 via ettställning av motsvarande bitar i
maskregistret PCMSK0 (PIN Change Mask Register 0).

Sedan aktiveras externa avbrott INT0 PIN 2.
Först definieras flanken för respektive avbrott,
där avbrott sätts till att endast äga rum på stigande flank
via ettställning av bitern ISC-biten ISC01
i registret EICRA (External Interrupt Control Register A).
Tills sist så aktiveras avbrotten INT0 genom att ettställa
motsvarande bitar i maskregistret EIMSK
(External Interrupt Mask Register).
*************************************************************/

/*************************************************************
Funktionen init_ADC initierar AD-omvandlaren med en
testomvandling. Först i funktion väljs intern matningsspänning
genom att ettställa biten REFS0 i registret ADMUX. Sedan startas
AD-omvandlaren via ettställning av bitarna ADEN (ADC Enable),
ADSC (ADC Start Conversion) samt bitarna ADPS0, 1, 2 vilket
gör att omvandlaren har en divitionsfaktorn på 128.

Sedan så används en while sats vilket kontinuerligt körs
medans ADCSRA och ADIF är 0.

Till sist så ett ställfs biten ADIF(ADC Interrupt Flag) som
indikerar när AD-omvanldingen är slutförd.
*************************************************************/
static void init_ADC()
{
	ADMUX = (1 << REFS0);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return;
}