#include "GPIO.h"

Motor motor;
Servo servo;
Button button;
Sensor sensor, right_sensor, left_sensor;
PWM_Timer pwm_timer, servo_timer;
PID_Controller pid_controller;

void init_GPIO()
{
	asm("SEI");
	INIT_TIMER0;
	INIT_TIMER1;
	OCR1A = 256;
	pid_controller = PID_Controller(90, 1, 0.01, 0.1);
	button = Button(9);
	button.enable_interrupt();
	motor = Motor(5);
	servo = Servo(6);
	pwm_timer = PWM_Timer(TimerSelection::TIMER1, 10, 5);
	servo_timer = PWM_Timer(TimerSelection::TIMER0, 20, 6);
	sensor = Sensor(1);
	right_sensor = Sensor(0);
	left_sensor = Sensor(2);
	DDRD |= ((1<<IN1)|(1<<IN2));
	init_serial();
	return;
}

