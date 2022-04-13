#include "GPIO.h"

Motor motor;
Servo servo;
Button button;
Sensor sensor;
Sensor right_sensor;
Sensor left_sensor;
PWM_Timer pwm_timer, servo_timer;
PID_Controller pid_controller;

void init_GPIO()
{
	asm("SEI");
	INIT_TIMER0;
	INIT_TIMER1;
	OCR1A = 256;
	pid_controller = PID_Controller();
	button = start_Button(9);
	button.enable_interrupt();
	motor = pwm_motor(5);
	servo = pwm_servo(6);
	pwm_timer = PWM_Timer(TimerSelection::TIMER1, 10, 5);
	servo_timer = PWM_Timer(TimerSelection::TIMER0, 20, 6);
	sensor = new_Sensor(1);
	right_sensor = new_right_Sensor(0);
	left_sensor = new_left_Sensor(2);
	DDRD |= ((1<<IN1)|(1<<IN2));
	init_serial();
	return;
}

Button start_Button(const uint8_t PIN)
{
	Button self(PIN);
	return self;
}

Motor pwm_motor(const uint8_t PIN)
{
	Motor self(PIN);
	return self;
}
Servo pwm_servo(const uint8_t PIN)
{
	Servo self(PIN);
	return self;
}

Sensor new_Sensor(const uint8_t PIN)
{
	Sensor self(PIN);
	return self;
}

Sensor new_right_Sensor(const uint8_t PIN)
{
	Sensor self(PIN);
	return self;
}

Sensor new_left_Sensor(const uint8_t PIN)
{
	Sensor self(PIN);
	return self;
}