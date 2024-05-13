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

#define TRIG_DDR DDRG
#define TRIG_PORT PORTG
#define TRIG 4

#define ECHO_DDR DDRE
#define ECHO_PIN PINE //INT4
#define ECHO 4

void init_ulatrsonic();
void ultrasonic_trigger();
void ultrasonic_distance_check();

#endif /* ULTRASONIC_H_ */