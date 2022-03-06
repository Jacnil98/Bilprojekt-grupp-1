#include "header.h" //Inkluderar egen headerfil

//Funktionen main där programmet startar defineras.
int main()
{
	setup(); //Anroppar funktionen main för initiera mikrodatorn.
	while (true) //Skapar en while sats so ska exekverar tills att programmet stängs av.
	{
		PWM(); //I while satsen så anropas PWM funktionen.
	}
	return 0; //Retunerar att programmet utförds korrekt.
}

