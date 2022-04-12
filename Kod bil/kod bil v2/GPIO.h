#ifndef GPIO_H_
#define GPIO_H_
#include "definitions.h"

#define ADC_MAX 1023.0f
#define PERIOD 10
#define FWD_SENSOR 1
#define IN1 7
#define IN2 8
#define INTERRUPT_TIME 0.016f // 0.016 ms mellan timeravbrott,
#define INTERRUPTS_FOR_10MS 625 // Det krävs 625 timeravbrott för 10 ms.

#define MOTOR 5
#define BUTTON 1 //PB1 på uno, D9 på nano
#define BUTTON_IS_PRESSED (PINB & (1<<BUTTON))

#define INIT_TIMER0 TCCR0B = (1 << CS00)
#define INIT_TIMER1 TCCR1B = (1 << CS10) | (1 << WGM12)
#define INIT_TIMER2 TCCR2B = (1 << CS20)

#define ENABLE_TIMER0 TIMSK0 = (1 << TOIE0)
#define ENABLE_TIMER1 TIMSK1 = (1 << OCIE1A)
#define ENABLE_TIMER2 TIMSK2 = (1 << TOIE2)

#define DISABLE_TIMER0 TIMSK0 = 0x00
#define DISABLE_TIMER1 TIMSK1 = 0x00
#define DISABLE_TIMER2 TIMSK2 = 0x00

enum class PWM_Period { ON, OFF };

class GPIO
{
	protected:
	uint8_t PIN = 0x00;
	IO_port io_port = IO_port::NONE;
	
	public:
	static uint16_t ADC_read(const uint8_t PIN)
	{
		ADMUX = ((1 << REFS0) | PIN);
		ADCSRA = ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
		while ((ADCSRA & (1 << ADIF)) == 0) ;
		ADCSRA = (1 << ADIF);		
		return ADC;
	}
};

class Servo : public GPIO
{
private:
	bool PWM_enabled = false;
	bool servo_enabled = false;
	bool interrupt_enabled = false;
	uint8_t left_sensor_PIN;
	uint8_t right_sensor_PIN;
	IO_port left_sensor_io_port;
	IO_port right_sensor_io_port;
	uint16_t ADC_read();
public:
	Servo(void) {}
	Servo(const uint8_t PIN);
	void on(void);
	void off();
	void toggle();
	void enabled();
	void disabled();
	bool is_enabled();
	
	
	
	uint8_t get_left_sensor_PIN() {return this->left_sensor_PIN; }
	uint8_t get_right_sensor_PIN() {return this->right_sensor_PIN; }
};


class Motor : public GPIO
{
private:
	bool PWM_enabled = false;
	bool motor_enabled = false;
	bool interrupt_enabled = false;
	uint8_t sensor_PIN;
	IO_port sensor_io_port;
	uint16_t ADC_read();
public:
	bool forward_enabled = true;
	Motor(void) {}
	Motor(const uint8_t PIN);
	void on(void);
	void off(void);
	void toggle(void);
	void read_direction(void);
	void enable_interrupt();
	void disable_interrupt();
	void enabled();
	void disabled();
	bool is_enabled();
	void forward_direction();
	void reverse_direction();
	void count_motor_PWM_interrupts();
	uint8_t get_sensor_PIN(void) { return this->sensor_PIN; }
};

class Sensor : public GPIO
{
private:
	uint8_t sensor_PIN;
	uint16_t target = 90;
	uint16_t actual_value = 0;
	uint16_t ADC_read();
public:
	Sensor(void){}
	Sensor(const uint8_t PIN);
	uint16_t calculate();
	uint16_t servo_position();
	uint16_t get_left_sensor();
	uint16_t get_right_sensor();
	uint16_t get_sensor_input(const uint8_t PIN);
	
};

class Button : public GPIO
{
private:
	bool interrupt_enabled = false;
public:
	
	Button(void) {}
	Button(const uint8_t PIN);
	bool is_pressed(void);
	void enable_interrupt();
	void disable_interrupt(void);
	bool interrupt_is_enabled(void) {return this->interrupt_enabled; }
};

class PWM_Timer : public GPIO
{
private:
	TimerSelection timerSelection = TimerSelection::NONE;
	volatile uint32_t executed_interrupts = 0x00;
	volatile uint32_t required_interrupts = 0x00;
	PWM_Period pwm_period = PWM_Period::ON;
	PWM_Period servo_period = PWM_Period::ON;
	uint8_t PIN = 0x00;
	uint32_t total_interrupts = 0x00;
	void init(void);
public:
	bool enabled;
	inline PWM_Timer(void) { }
	PWM_Timer(const TimerSelection timerSelection, const double period, const uint8_t PIN);
	void update(void);
	void switch_mode(void);
	void switch_servo_mode();
	bool elapsed(void);
	bool servo_elapsed();
	void servo_update();
	void count_interrupts();
	void PWM_function();
	
};

extern Motor motor;
extern Servo servo;
extern Button button;
extern Sensor sensor;
extern PWM_Timer pwm_timer, servo_timer;


void init_GPIO();
Motor pwm_motor(const uint8_t PIN);
Servo pwm_servo(const uint8_t PIN);
Button start_Button(const uint8_t PIN);
Sensor new_Sensor(const uint8_t PIN);
PWM_Timer new_PWM_Timer(const double period, const uint8_t PIN);

void serial_print(const char* s); // Funktion för seriell överföring.
void serial_print_int(const uint32_t number);
void init_serial();

#endif /* BUTTON_H_ */