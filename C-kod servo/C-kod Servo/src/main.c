#include "header.h"


int main(void)
{
  setup();
  servo_enable();
  while(true)
  {
    set_input();
    regulate();

    //serial_print_int("Connection active value: %d\n", (PINB & (1 << 1)));
    //serial_print_int("%d", duty_cycle);
    //PID_print();
    
  }

  return 0;
}