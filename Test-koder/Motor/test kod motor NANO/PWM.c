#include "header.h" //Inkluderar egen headerfil

//Skapar de statiska funktioner som behövs för att få programmet att fungera.
static uint16_t ADC_read(const uint8_t PIN);
static void delay(const uint16_t delay_time);

/*************************************************************
Funktionen PMW används för att kontrollera hastigheten på
motorn samt styrkan på lysdioden. Det börjar med att kontrollera
om varken led_enabled eller motor_enabled är true så retuneras
funktionen.
Om en elle båda komponenterna är aktiverade så börjar det med
att läsa ac potentiometern som omvandlas till ett värde mellan
0-1023.
Med detta så beräknas sedan duty-cycle som är ett flytal mellan
0-1, vilket används för att beräkna on_time och off_time.
Perioden ligger på 10ms. Reultatet vid beräkningen av
on_time adderas med 0.5 för att avrunda talet till
närmsta heltal.

Med hjälp av de framberäknade värdena vilket gör att komponenten
är igång under on_time samt avstängd under off_time. Detta
gör att de kan justeras.
*************************************************************/


void PWM()
{
	const uint16_t direction = ADC_read(DIRECTION);
	
	if (direction < 400)
	{
		IN1_OFF; // Stänger av IN1.
		IN2_ON;
	}
	
	else if (direction >= 400 && direction <= 600)
	{
		
		IN1_OFF;
		IN2_OFF;
	}
	
	else if (direction > 600)
	{
		IN1_ON;
		IN2_OFF;
	}
	
	const uint16_t speed = ADC_read(SPEED);
	const float duty_cycle = (float)speed / (ADC_MAX); // *5 kan behövas korrigeras, även vid test av servo
	const uint8_t on_time = (uint8_t )(duty_cycle * PERIOD + 0.5);
	const uint8_t off_time = PERIOD - on_time;
	
	MOTOR_ON;
	delay(on_time);
	MOTOR_OFF;
	delay(off_time);
	return;
}

/*************************************************************
Funktionen ADC_read används för att läsa in siganlen från
potentiometern och omvandla den till heltal mellan 0-1023.
Detta sker på en så hög prescale bit som möjligt (ADPS*)
vilket ger en frekvens på 125KHZ detta gör att omvandlingen
blir så korrekt som möjligt.
När AD-omvandligen är slutförd så ettställs biten ADIF. Sedan
retuneras resultatet från omvandlingen.
*************************************************************/
static uint16_t	ADC_read(const uint8_t PIN)
{
	ADMUX = ((1 << REFS0) | PIN);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}
/*************************************************************
För att skapa en fördröjning skapas funktionen delay. En for
sats används för att räkna fördröjningen i millisekunder.
*************************************************************/

static void delay(const uint16_t delay_time)
{
	for (uint16_t i = 0; i < delay_time; i++)
	_delay_ms(1);
	return;
}