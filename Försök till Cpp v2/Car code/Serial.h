
#ifndef SERIAL_H_
#define SERIAL_H_

#include "definitions.h"

namespace Serial
{
	void init(void);
	void print(const char* s);
	void print(const char c);
	void print(const int32_t number);
	void print(const uint32_t number);
	void print(const double number);
}

#endif /* SERIAL_H_ */