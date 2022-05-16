#include "Header.h"

static void check_output();

double output1;

double regulate()
{
    double error = TARGET - actual_value;
    
    intergral +=  error;
    double derivative = error - last_error;
    output1 = TARGET + Kp * error + Ki * intergral + Kd * derivative;
    check_output();
   if(intergral >= 2000)
   {
       intergral = 2000;
   }

   if(intergral <= -2000)
   {
       intergral = -2000;
   }
    last_error = error;
    output = output1 + 80;
    if (output >= 250) output = 250;
    else if (output <= 90) output = 90;
    return output;
}

static void check_output()
{
    if(output1 >= OUTPUT_MAX)
        output1 = OUTPUT_MAX;
    else if(output1 <= OUTPUT_MIN)
        output1 = OUTPUT_MIN;
    return;
}
/*
void PID_print()
{
    serial_print("-------------------------\n");
    serial_print_int("TActual: %d\n", actual_value);
    serial_print_int("Output: %d\n", output);
    serial_print_int("Last error: %d\n", last_error);
    serial_print("-------------------------\n");

    return;
}
*/