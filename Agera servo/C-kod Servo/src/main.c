#include "header.h"

/**************************************************************************
 * I main anropas en setup funktion för alla initieringsrutiner och 
 * avläsning av AD omvandlaren för PID-reglering görs kontinuerligt.
**************************************************************************/
int main(void)
{
  setup();
  while(true)
  {
    set_input();
    duty_cycle = regulate();
    
  }

  return 0;
}