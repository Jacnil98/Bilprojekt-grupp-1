/*************************************************************
Här startar header filen och använder "include guards" för
att ingenting i programmet ska dubbel defineras.
*************************************************************/
#ifndef HEADERH_H_
#define HEADERH_H_

//Klockfrekvensen sätts till 16MHZ
#define F_CPU 20000000UL

//Inkludererar de biblotek som ska användas
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Definerar lysdiodern
#define IN1 7 //Kopplad till Pin10/ 
#define IN2 0 //Kopplad till Pin11/ PORTB2
#define IN1_ON PORTD |= (1 << IN1) //Använder bitvis skiftning för att tända diodern.
#define IN1_OFF PORTD &= ~(1 << IN1) //Bitvis multiplikation med negation för att släcka diodern.++
#define IN2_ON PORTB |= (1 << IN2) //Använder bitvis skiftning för att tända diodern.
#define IN2_OFF PORTB &= ~(1 << IN2) //Bitvis multiplikation med negation för att släcka diodern.

//Definerar potetiometern
#define DIRECTION 0 //A0 /PORTC0
#define SPEED 1 // A1 / PORTC1

//Definerar DC motorn
#define MOTOR 5 //Pin 5/ PORTD5
#define MOTOR_ON PORTD |= (1 << MOTOR) //Bitvis skiftning för att sätta igång motorn.
#define MOTOR_OFF PORTD &= ~(1 << MOTOR) //Bitvis multiplikation med negation för stänga av motorn.

//Makron för att hjälpa med AD omvandlingen
#define ADC_MAX 1023
#define PERIOD 10

/*************************************************************
Skapas två enumerationer som ska användas i programmet.
Förstå skapas en "bool" variabel vilket är en variabel som
antingen är sann(true) eller falsk(false). State variabeln
är till för de olika statusarna programmet kan vara i.
*************************************************************/
typedef enum {true = 1, false = 0} bool;

//De två globala funktionerna som ska användas i programmet skapas.
void setup();
void PWM();

#endif /* HEADERH_H_ */