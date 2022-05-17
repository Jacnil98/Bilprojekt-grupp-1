#include "Header.h"

int main(void)
{
  setup();
  servo_enable();
  while(true)
  {
    set_input();
    duty_cycle = regulate();
    //serial_print_int("%d", duty_cycle);
    //PID_print();
    
  }

  return 0;
}