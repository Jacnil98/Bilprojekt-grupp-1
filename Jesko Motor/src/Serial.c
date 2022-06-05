#include "Header.h"

static void serial_write_byte(const char data);

void serial_print(const char* s)
{
	for (register size_t i = 0; s[i]; i++)
	{
		serial_write_byte(s[i]);
		if (s[i] == '\n') 
			serial_write_byte('\r');
	}
	
	serial_write_byte('\0');
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