#include "header.h"

static void check_output();
static void regulate_backwards();

static double output1 = 0;

void init_pid_controller()
{
    output = 0x00;
    actual_value = 0x00;
    last_error = 0x00;
    intergral = 0x00; // Initiera samtliga globala PID-variabler.
    motor_direction = MOTOR_DIRECTION_FORWARDS;
}

void regulate()
{

    if (CONNECTION_ACTIVE)
    {
        regulate_backwards();
    }
    else
    {
        double error = TARGET - actual_value; 
        intergral +=  error;
        double derivative = error - last_error;
        output1 = TARGET + Kp * error + Ki * intergral + Kd * derivative;
        check_output();

        if(intergral >= 2000) intergral = 2000;
        if (intergral <= -2000) intergral = -2000;
        //serial_print_int("\n%d", intergral);
        last_error = error;
        output = output1 + 80;
    if (output >= 250) output = 250;
    else if (output <= 90) output = 90;
    }
    return;
}

static void check_output()
{
    if(output1 >= OUTPUT_MAX)
        output1 = OUTPUT_MAX;
    else if(output1 <= OUTPUT_MIN)
        output1 = OUTPUT_MIN;
    return;
}

static void regulate_backwards()
{
   double error = TARGET - actual_value; 
    intergral +=  error;
    double derivative = error - last_error;
     output1 = TARGET + Kp * error + Ki * intergral + Kd * derivative;
    check_output();

    if(intergral >= 2000) intergral = 2000;
    if (intergral <= -2000) intergral = -2000;
     //serial_print_int("\n%d", intergral);
    last_error = error;
    output = output1 + 80;  // centrum 170
    if (output >= 250) output = 250;
    else if (output <= 90) output = 90;
    if (output <= 170)
    {
        output = 230;
    }
    else 
    {
        output = 90;
    }
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