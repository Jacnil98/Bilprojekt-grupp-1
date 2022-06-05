#include "header.h"

static uint16_t left_sensor_input;
static uint16_t right_sensor_input;
static uint8_t mapped_left_sensor_input;
static uint8_t mapped_right_sensor_input;

void set_input(const double new_left_sensor_input, const double new_right_sensor_input);
static double check_sensor_input(const double sensor_input);
static void TOF_map();

void set_input(const double new_left_sensor_input, const double new_right_sensor_input)
{
    uint16_t ADC_Left = Calculate_distance(SENSOR_LEFT);
    left_sensor_input = check_sensor_input(ADC_Left);
    uint16_t ADC_Right = Calculate_distance(SENSOR_RIGHT);
    right_sensor_input = check_sensor_input(ADC_Right);
    TOF_map();
    actual_value = TARGET + mapped_left_sensor_input - mapped_right_sensor_input;
    return;
}

double check_sensor_input(const double sensor_input)
{
	if (sensor_input > SENSOR_MAX)
		return SENSOR_MAX;
	else if (sensor_input < SENSOR_MIN)
		return SENSOR_MIN;
	return sensor_input;
}

static void TOF_map()
{
    mapped_left_sensor_input = left_sensor_input / SENSOR_MAX * TARGET;
    mapped_right_sensor_input = right_sensor_input / SENSOR_MAX * TARGET;
    return;
}

