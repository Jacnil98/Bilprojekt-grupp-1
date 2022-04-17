#include "Serial.h"

void Serial::init(void)
{
	static bool serial_initialized = false;
	if (serial_initialized) return;
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	UBRR0 = 103;
	UDR0 = '\r';
	serial_initialized = true;
	return;
}

void Serial::print(const char* s)
{
	for (size_t i = 0; s[i]; i++)
	{
		Serial::print(s[i]);
		if (s[i] == '\n')
		Serial::print('\r');
	}
	return;
}

void Serial::print(const char data)
{
	while ((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = data;
	return;
}

void Serial::print(const int32_t number)
{
	char text[50];
	text[0] = '\0';
	sprintf(text, "%ld", number);
	Serial::print(text);
	return;
}

void Serial::print(const uint32_t number)
{
	char text[50];
	text[0] = '\0';
	sprintf(text, "%lu", number);
	Serial::print(text);
	return;
}

void Serial::print(const double number)
{
	char text[50];
	text[0] = '\0';
	const int32_t integer = (int32_t)(number);
	int32_t decimal = (int32_t)((number - integer) * 100);
	if (decimal < 0) decimal *= -1;
	sprintf(text, "%ld.%ld", integer, decimal);
	Serial::print(text);
	return;
}