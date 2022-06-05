#include "header.h"
/**************************************************************************
 * ADC-read läser av främre sensorn på bilen och återger ett värde mellan 
 * 0-5v som omvandlas till ett digitalt värde mellan 0-1023.
**************************************************************************/
uint32_t ADC_read()
{
	ADMUX = ((1 << REFS0) | SENSOR);
	ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
	while ((ADCSRA & (1 << ADIF)) == 0) ;
	ADCSRA = (1 << ADIF);
	return ADC;
}

/**************************************************************************
 * calculate distance omvandlar värdet från ADC read och med en bneräkning
 * lämnar ett värde mellan 10 och 80cm, en if sats läser av ifall avstaåndet 
 * är under 20cm, då startar en timer som om den löper ut efter 3 sekunder
 * gör att bilen börjar backa.
 * En annan IF sats läser av ifall värdet understiger eller överstiger 
 * bestämnda parametrar, är värdet över 65 ges värdet MAX_DISTANCE vilket 
 * är 80, om det understiger MIN_DISTANCE vilket är 50 begränsas det till
 * 50 för att inte bilen ska köra långsammare än önskat.
 * Detta multipliceras sedan med 7 för att kunna användas med PWM timern
**************************************************************************/
uint16_t Calculate_distance()
{
    float in_signal = ADC_read() * 0.0048828125;
    double distance_in_cm = 29.988*(pow(in_signal, -1.173));
    
    if(distance_in_cm <= 20)
    {
        if(!reverse_timer_enabled)
        {
        reverse_timer_on();
        }
    }
    else 
    {
        if(reverse_timer_enabled)
        {
            reverse_timer_off();
        }
        if(motor_reverse)
        {
            motor_forward();
        }
    }

    if(distance_in_cm >= 65)
    { 
        distance_in_cm = MAX_DISTANCE;
    }

    if(distance_in_cm <= MIN_DISTANCE)
    {
        distance_in_cm = MIN_DISTANCE;
    }
    uint16_t on_time_interrupts = distance_in_cm * 7;
    return on_time_interrupts;
}

