#include "GPIO.h"

static void serial_write_byte(const char data);

void init_serial(void)
{
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	UBRR0 = 103;
	UDR0 = '\r';
}

void serial_print(const char* s)
{
	for (size_t i = 0; s[i]; i++)
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

void serial_print_int(const int number)
{
	char text[50];
	text[0] = '\0';
	sprintf(text, "%d ", number);
	serial_print(text);
	return;
}