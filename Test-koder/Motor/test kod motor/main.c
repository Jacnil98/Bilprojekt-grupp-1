#include "header.h" //Inkluderar egen headerfil

//Funktionen main d�r programmet startar defineras.
int main()
{
	setup(); //Anroppar funktionen main f�r initiera mikrodatorn.
	while (true) //Skapar en while sats so ska exekverar tills att programmet st�ngs av.
	{
		PWM(); //I while satsen s� anropas PWM funktionen.
	}
	return 0; //Retunerar att programmet utf�rds korrekt.
}

