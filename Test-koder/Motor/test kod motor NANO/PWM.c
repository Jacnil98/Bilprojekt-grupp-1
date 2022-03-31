#include "header.h" //Inkluderar egen headerfil

//Skapar de statiska funktioner som beh�vs f�r att f� programmet att fungera.
static uint16_t ADC_read(const uint8_t PIN);
static void delay(const uint16_t delay_time);

/*************************************************************
Funktionen PMW anv�nds f�r att kontrollera hastigheten p�
motorn samt styrkan p� lysdioden. Det b�rjar med att kontrollera
om varken led_enabled eller motor_enabled �r true s� retuneras
funktionen.
Om en elle b�da komponenterna �r aktiverade s� b�rjar det med
att l�sa ac potentiometern som omvandlas till ett v�rde mellan
0-1023.
Med detta s� ber�knas sedan duty-cycle som �r ett flytal mellan
0-1, vilket anv�nds f�r att ber�kna on_time och off_time.
Perioden ligger p� 10ms. Reultatet vid ber�kningen av
on_time adderas med 0.5 f�r att avrunda talet till
n�rmsta heltal.

Med hj�lp av de framber�knade v�rdena vilket g�r att komponenten
�r ig�ng under on_time samt avst�ngd under off_time. Detta
g�r att de kan justeras.
*************************************************************/


void PWM()
{
	const uint16_t direction = ADC_read(DIRECTION);
	
	if (direction < 400)
	{
		IN1_OFF; // St�nger av IN1.
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
	const float duty_cycle = (float)speed / (ADC_MAX); // *5 kan beh�vas korrigeras, �ven vid test av servo
	const uint8_t on_time = (uint8_t )(duty_cycle * PERIOD + 0.5);
	const uint8_t off_time = PERIOD - on_time;
	
	MOTOR_ON;
	delay(on_time);
	MOTOR_OFF;
	delay(off_time);
	return;
}

/*************************************************************
Funktionen ADC_read anv�nds f�r att l�sa in siganlen fr�n
potentiometern och omvandla den till heltal mellan 0-1023.
Detta sker p� en s� h�g prescale bit som m�jligt (ADPS*)
vilket ger en frekvens p� 125KHZ detta g�r att omvandlingen
blir s� korrekt som m�jligt.
N�r AD-omvandligen �r slutf�rd s� ettst�lls biten ADIF. Sedan
retuneras resultatet fr�n omvandlingen.
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
F�r att skapa en f�rdr�jning skapas funktionen delay. En for
sats anv�nds f�r att r�kna f�rdr�jningen i millisekunder.
*************************************************************/

static void delay(const uint16_t delay_time)
{
	for (uint16_t i = 0; i < delay_time; i++)
	_delay_ms(1);
	return;
}