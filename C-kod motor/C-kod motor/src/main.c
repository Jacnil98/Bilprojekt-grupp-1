#include "header.h"
/**************************************************************************
 * I main anropas en setup funktion för alla initieringsrutiner och 
**************************************************************************/
int main(void)
{
  setup();
  
  while(true)
  {
      heck_start_button();
  }
  return 0;
}


