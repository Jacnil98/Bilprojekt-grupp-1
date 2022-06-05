#include "header.h"

static void check_output();
static void regulate_backwards();

static double output1 = 0;

void init_pid_controller()
{
    output = 0x00;
    actual_value = 0x00;
    last_error = 0x00;
    intergral = 0x00; 
    motor_direction = MOTOR_DIRECTION_FORWARDS;
}
/**************************************************************************
 * regulate regler värderna från set input för att genom en PID reglering
 * ge ett output som sen ska styra servot dör värdet från set input är 90
 * för rakt fram 0 för 90 grader vänster och 180 för 90 grader höger.
 * detta tas +80 för att få rätt antal interrupts för att matcha de tider
 * som servot behöver, dvs 0.7ms till 2.3ms, där 1.5 är rakt fram.
 * regulate backwards används om en signal från andra kortet kommer, då 
 * sätts ett värde för att bilen ska byta riktning mot vad den gör om bilen
 * kör framåt.
**************************************************************************/
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
        last_error = error;
        output = output1 + 80;
    if (output >= 250) output = 250;
    else if (output <= 90) output = 90;
    }
    return;
}
/**************************************************************************
 * check output har som syfte att begränsa väärden utanför de önskade 
 * värderna från set input.
**************************************************************************/
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
