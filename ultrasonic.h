/*
 * ultrasonic.h
 *
 * Created: 2024-05-08 오전 10:55:09
 *  Author: HARMAN-09
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU 16000000UL
#include <avr/io.h>   // PORTA DDRA 등의 symbol이 정의 되어 있다.'
#include <util/delay.h>   // _delay_ms 등의 함수가 들어 있다.
#include <avr/interrupt.h>

/*========== LEFT ultrasonic =========*/
#define US_TCNT_LEFT TCNT3 // timer3번 counter
#define TRIG_LEFT 0 // left의 trig핀이 0번임
#define TRIG_DDR_LEFT	DDRA
#define TRIG_PORT_LEFT  PORTA
// hardware external interrupt INT4 : PE4
#define ECHO_LEFT 4
#define ECHO_DDR_LEFT DDRE
#define ECHO_PIN_LEFT PINE //INT4

/*========== CNETER ultrasonic =========*/
#define US_TCNT_CENTER TCNT3 // timer3번 counter
#define TRIG_CENTER 1 // left의 trig핀이 0번임
#define TRIG_DDR_CENTER	DDRA
#define TRIG_PORT_CENTER  PORTA
// hardware external interrupt INT5 : PE5
#define ECHO_CENTER 5
#define ECHO_DDR_CENTER DDRE
#define ECHO_PIN_CENTER PINE //INT5

/*========== RIGHT ultrasonic =========*/
#define US_TCNT_RIGHT TCNT3 // timer3번 counter
#define TRIG_RIGHT 2 // left의 trig핀이 0번임
#define TRIG_DDR_RIGHT	DDRA
#define TRIG_PORT_RIGHT  PORTA
// hardware external interrupt INT6 : PE6
#define ECHO_RIGHT 6
#define ECHO_DDR_RIGHT DDRE
#define ECHO_PIN_RIGHT PINE //INT5
// =============== END ====================

volatile int ultrasonic_left_distance;
volatile int ultrasonic_center_distance;
volatile int ultrasonic_right_distance;

void init_ulatrsonic();
void ultrasonic_trigger();
void ultrasonic_distance_check();

#endif /* ULTRASONIC_H_ */