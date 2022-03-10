#include "header.h" //Inkluderar egen headerfil.

//Skapar tre statiska funktioner som endast ska anv�ndas i setup filen.
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
H�r defineras funktionen init_ports. Det b�rjar med att s�tta
diodern och motorn med hj�lp av DDR* (Data direction register
B/D). Sedan s�tts de olika knapparna till inportar med hj�lp
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
Funktionen init_interrupts anv�nds f�r att aktivera PCI-avbrott
p� PIN 11 - 13 samt avbrott externt p� PIN 2 - 3. F�rst
aktiveras avbrott globalt via ettst�llning av biten "I" i
statusregistret SREG via en assemblerinstruktion som heter SEI.
D�refter aktiveras avbrottsvektorn f�r I/O port B,
PCINT0_vect, Detta g�rs genom att via ettst�lla biten PCIE0
(PIN Change Interrupt Enable 0) i kontrollregistret PCICR
(PIN Change Interrupt Control Register).
D�refter aktiveras PCI-avbrott PCINT5 p�
PIN 13 via ettst�llning av motsvarande bitar i
maskregistret PCMSK0 (PIN Change Mask Register 0).

Sedan aktiveras externa avbrott INT0 PIN 2.
F�rst definieras flanken f�r respektive avbrott,
d�r avbrott s�tts till att endast �ga rum p� stigande flank
via ettst�llning av bitern ISC-biten ISC01
i registret EICRA (External Interrupt Control Register A).
Tills sist s� aktiveras avbrotten INT0 genom att ettst�lla
motsvarande bitar i maskregistret EIMSK
(External Interrupt Mask Register).
*************************************************************/

/*************************************************************
Funktionen init_ADC initierar AD-omvandlaren med en
testomvandling. F�rst i funktion v�ljs intern matningssp�nning
genom att ettst�lla biten REFS0 i registret ADMUX. Sedan startas
AD-omvandlaren via ettst�llning av bitarna ADEN (ADC Enable),
ADSC (ADC Start Conversion) samt bitarna ADPS0, 1, 2 vilket
g�r att omvandlaren har en divitionsfaktorn p� 128.

Sedan s� anv�nds en while sats vilket kontinuerligt k�rs
medans ADCSRA och ADIF �r 0.

Till sist s� ett st�llfs biten ADIF(ADC Interrupt Flag) som
indikerar n�r AD-omvanldingen �r slutf�rd.
*************************************************************/
static void init_ADC()
{
	ADMUX = (1 << REFS0);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return;
}