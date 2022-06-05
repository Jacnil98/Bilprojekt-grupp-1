#include "Header.h"

static void check_output();
static void regulate_backwards();

double output1;

double regulate()
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
        last_error = error;
        output = output1 + 80;
    if (output >= 250) output = 250;
    else if (output <= 90) output = 90;
    }
    return 0;
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
    last_error = error;
    output = output1 + 80; 
    if (output >= 250) output = 250;
    else if (output <= 90) output = 90;
    if (output <= 170)
    {
        output = 250;
    }
    else 
    {
        output = 90;
    }
}
