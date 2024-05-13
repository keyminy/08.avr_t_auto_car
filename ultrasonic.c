/*
 * ultrasonic.c
 *
 * Created: 2024-05-08 오전 10:55:51
 *  Author: HARMAN-09
 */ 
#include "ultrasonic.h"
#include "extern.h"


volatile int ultrasonic_distance=0;
volatile char scm[50];


void init_ulatrsonic() //_이용해서 나타내기
{
	TRIG_DDR |= 1 << TRIG; //output mode로 설정
	ECHO_DDR &= ~(1 << ECHO); //input mode로 설정
	
	//289p. 표12-8
	// 0 1  : 상승 하강에지 둘다 INT를 띄우도록 설정한다
	
	EICRB |= 0 << ISC41 | 1 << ISC40;
	
	//16bit timer 1번을 설정해서 사용한다.
	//16:65535
	//16MHz: clock
	//16MHz를 1024분주 16000000/1024=15625Hz=15.625KHz
	//1주기(1개의 펄스 길이) T=1/f=1/15625=0.000064sec=64us
	
	TCCR3B |= 1 << CS32 | 1 << CS30; //1024로 분주
	
	EIMSK= 1 << INT4; // 외부 INT4(ECHO)사용
}

//PE4: 외부 INT4 초음파센서 상승, 하강 에지 둘다 이곳으로 들어온다.
//결국은 상승 에지에서 1번, 하강 에지에서 1번 2번 들어 온다.
ISR(INT4_vect)
{
	//1.상승 에지 일때
	if(ECHO_PIN &(1<<ECHO))
	{
		TCNT1=0;
	}
	//2.하강 에지 일때
	else
	{
		//에코핀에 들어 오는 펄스 길이를 us단위로 환산
		ultrasonic_distance=1000000.0*TCNT1*1024/F_CPU;
		//예) TCNT1에 10이 들어있다고 가정
		//15.625KHz의 1주기가 64us이다.
		//0.000064*10: 0.00064sec(640us)
		//640/58=11cm
		//1cm ; 58us 소요
		sprintf(scm,"dis: %4dcm",ultrasonic_distance/58);
	}
}
void ultrasonic_trigger()
{
	TRIG_PORT &= ~(1 << TRIG); //low
	_delay_us(1);
	TRIG_PORT |= 1 << TRIG; //high
	_delay_us(15);
	TRIG_PORT &= ~(1 << TRIG); //low
}

void ultrasonic_distance_check()
{
	if(ultrasonic_trigger_timer>=1000) //1초
	{
		ultrasonic_trigger_timer=0;
		printf("%s",scm);
		ultrasonic_trigger();
	}
}

void ultrasonic_led_control()
{
	int i=ultrasonic_distance/58;
	if(i <=1)
	{
		PORTA=0b10000000;
	}
	else if(i <=2)
	{
		PORTA=0b11000000;
	}
	else if(i <=3)
	{
		PORTA=0b11100000;
	}
	else if(i <=4)
	{
		PORTA=0b11110000;
	}
	else if(i <=5)
	{
		PORTA=0b11111000;
	}
	else
	{
		PORTA=0b11111100;
	}
}