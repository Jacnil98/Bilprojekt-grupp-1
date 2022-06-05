#include "header.h"

static void serial_write_byte(const char data);
/**************************************************************************
 * Serial funktionen användes främst för felsökning för att kunna läsa 
 * av vad som hände under programmets gång, vid tävling så togs all 
 * utskrift bort.
**************************************************************************/
void serial_print(const char* s)
{
	for (register size_t i = 0; s[i]; i++)
	{
		serial_write_byte(s[i]);
		if (s[i] == '\n') 
			serial_write_byte('\r');
	}
	return;
}

static void serial_write_byte(const char data)
{
	while ((UCSR0A & (1 << UDRE0)) == 0) ;
	UDR0 = data;
	return;
}

void serial_print_int(const char* s, const int number)
{
	char text[50];
	text[0] = '\0';
	sprintf(text, s, number);
	serial_print(text);
	return;
}