/*************************************************************
H�r startar header filen och anv�nder "include guards" f�r
att ingenting i programmet ska dubbel defineras.
*************************************************************/
#ifndef HEADERH_H_
#define HEADERH_H_

//Klockfrekvensen s�tts till 16MHZ
#define F_CPU 20000000UL

//Inkludererar de biblotek som ska anv�ndas
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Definerar lysdiodern
#define IN1 7 //Kopplad till Pin10/ 
#define IN2 0 //Kopplad till Pin11/ PORTB2
#define IN1_ON PORTD |= (1 << IN1) //Anv�nder bitvis skiftning f�r att t�nda diodern.
#define IN1_OFF PORTD &= ~(1 << IN1) //Bitvis multiplikation med negation f�r att sl�cka diodern.++
#define IN2_ON PORTB |= (1 << IN2) //Anv�nder bitvis skiftning f�r att t�nda diodern.
#define IN2_OFF PORTB &= ~(1 << IN2) //Bitvis multiplikation med negation f�r att sl�cka diodern.

//Definerar potetiometern
#define DIRECTION 0 //A0 /PORTC0
#define SPEED 1 // A1 / PORTC1

//Definerar DC motorn
#define MOTOR 5 //Pin 5/ PORTD5
#define MOTOR_ON PORTD |= (1 << MOTOR) //Bitvis skiftning f�r att s�tta ig�ng motorn.
#define MOTOR_OFF PORTD &= ~(1 << MOTOR) //Bitvis multiplikation med negation f�r st�nga av motorn.

//Makron f�r att hj�lpa med AD omvandlingen
#define ADC_MAX 1023
#define PERIOD 10

/*************************************************************
Skapas tv� enumerationer som ska anv�ndas i programmet.
F�rst� skapas en "bool" variabel vilket �r en variabel som
antingen �r sann(true) eller falsk(false). State variabeln
�r till f�r de olika statusarna programmet kan vara i.
*************************************************************/
typedef enum {true = 1, false = 0} bool;

//De tv� globala funktionerna som ska anv�ndas i programmet skapas.
void setup();
void PWM();

#endif /* HEADERH_H_ */