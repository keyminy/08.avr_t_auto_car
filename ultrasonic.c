﻿/*
 * ultrasonic.c
 *
 * Created: 2024-05-08 오전 10:55:51
 *  Author: HARMAN-09
 */ 
#include "ultrasonic.h"
#include "extern.h"

volatile char scm[50];

void init_ulatrsonic() //_이용해서 나타내기
{
	/* =============== LEFT ultrasonic 설정!!================= */
	TRIG_DDR_LEFT |= 1 << TRIG_LEFT; //output mode로 설정 // TRIG_DDR_LEFT|= 0b0000_0001 계속 이렇게 안하게 하기 위해서임
	ECHO_DDR_LEFT &= ~(1 << ECHO_LEFT); //input mode로 설정 // ECHO_DDR_LEFT &= 0b1110_11111 계속 이렇게 안하게 하기 위해서임
	
	//289p. 표12-8
	// 0 1  : 상승 하강에지 둘다 INT를 띄우도록 설정한다
	// EICRA : INT 0~3사용
	// EICRB : INT 4~7사용
	// 0 1은 : 어떠한 신호의 변화가 있든지 INT요청한다(상승,하강에지 모두 INT발생시키게 함) <- Any logic change
	EICRB |= 0 << ISC41 | 1 << ISC40;
	
	//16bit timer 3번을 설정해서 사용한다.(1->3으로 변경됨)
	//16:65535
	//16MHz: clock
	//16MHz를 1024분주 16000000/1024=15625Hz=15.625KHz
	//1주기(1개의 펄스 길이) T=1/f=1/15625=0.000064sec=64us
	
	TCCR3B |= 1 << CS32 | 1 << CS30; //1024로 분주
	
	EIMSK |= 1 << INT4; // 외부 INT4(ECHO)사용
	
	/* =============== CENTER ultrasonic 설정!!================= */
	TRIG_DDR_CENTER |= 1 << TRIG_CENTER; //output mode로 설정 // TRIG_DDR_LEFT|= 0b0000_0001 계속 이렇게 안하게 하기 위해서임
	ECHO_DDR_CENTER &= ~(1 << ECHO_CENTER); //input mode로 설정 // ECHO_DDR_LEFT &= 0b1110_11111 계속 이렇게 안하게 하기 위해서임
		
	//289p. 표12-8
	// 0 1  : 상승 하강에지 둘다 INT를 띄우도록 설정한다
	// EICRA : INT 0~3사용
	// EICRB : INT 4~7사용
	// 0 1은 : 어떠한 신호의 변화가 있든지 INT요청한다(상승,하강에지 모두 INT발생시키게 함) <- Any logic change
	EICRB |= 0 << ISC51 | 1 << ISC50;
		
	//16bit timer 3번을 설정해서 사용한다.(1->3으로 변경됨)
	//16:65535
	//16MHz: clock
	//16MHz를 1024분주 16000000/1024=15625Hz=15.625KHz
	//1주기(1개의 펄스 길이) T=1/f=1/15625=0.000064sec=64us
	TCCR3B |= 1 << CS32 | 1 << CS30; //1024로 분주
		
	EIMSK |= 1 << INT5; // 외부 INT5(ECHO)사용
	
	/* =============== RIGHT ultrasonic 설정!!================= */
	TRIG_DDR_RIGHT |= 1 << TRIG_RIGHT; //output mode로 설정 // TRIG_DDR_LEFT|= 0b0000_0001 계속 이렇게 안하게 하기 위해서임
	ECHO_DDR_RIGHT &= ~(1 << ECHO_RIGHT); //input mode로 설정 // ECHO_DDR_LEFT &= 0b1110_11111 계속 이렇게 안하게 하기 위해서임
	
	//289p. 표12-8
	// 0 1  : 상승 하강에지 둘다 INT를 띄우도록 설정한다
	// EICRA : INT 0~3사용
	// EICRB : INT 4~7사용
	// 0 1은 : 어떠한 신호의 변화가 있든지 INT요청한다(상승,하강에지 모두 INT발생시키게 함) <- Any logic change
	EICRB |= 0 << ISC61 | 1 << ISC60;
	
	//16bit timer 3번을 설정해서 사용한다.(1->3으로 변경됨)
	//16:65535
	//16MHz: clock
	//16MHz를 1024분주 16000000/1024=15625Hz=15.625KHz
	//1주기(1개의 펄스 길이) T=1/f=1/15625=0.000064sec=64us
	TCCR3B |= 1 << CS32 | 1 << CS30; //1024로 분주
	
	EIMSK |= 1 << INT6; // 외부 INT6(ECHO)사용
}

/* ============== INT4 : LEFT ===============*/
//PE4: 외부 INT4 초음파센서 상승, 하강 에지 둘다 이곳으로 들어온다.
//결국은 상승 에지에서 1번, 하강 에지에서 1번 2번 들어 온다.
ISR(INT4_vect)
{
	//1.상승 에지 일때
	if(ECHO_PIN_LEFT &(1<<ECHO_LEFT))
	{
		TCNT3=0;  //Timer3번(1->3교체) 조심!!!
	}
	//2.하강 에지 일때
	else
	{
		//에코핀에 들어 오는 펄스 길이를 us단위로 환산
		ultrasonic_left_distance=(1000000.0*TCNT3*1024/F_CPU)/58;
		if(ultrasonic_left_distance <= CRITICAL_DISTANCE){
			isLeftBlocked = 1;
		}else{
			isLeftBlocked = 0;
		}
	}
}

/* ============== INT5 : CENETER ===============*/
//PE5: 외부 INT5 초음파센서 상승, 하강 에지 둘다 이곳으로 들어온다.
//결국은 상승 에지에서 1번, 하강 에지에서 1번 2번 들어 온다.
ISR(INT5_vect)
{
	//1.상승 에지 일때
	if(ECHO_PIN_CENTER &(1<<ECHO_CENTER))
	{
		TCNT3=0;  //Timer3번(1->3교체) 조심!!!
	}
	//2.하강 에지 일때
	else
	{
		//에코핀에 들어 오는 펄스 길이를 us단위로 환산
		ultrasonic_center_distance=(1000000.0*TCNT3*1024/F_CPU)/58;
		if(ultrasonic_center_distance <= CRITICAL_DISTANCE){
			isCenterBlocked = 1;
		}else{
			isCenterBlocked = 0;
		}
	}
}

/* ============== INT6 : RIGHT ===============*/
//PE6: 외부 INT6 초음파센서 상승, 하강 에지 둘다 이곳으로 들어온다.
//결국은 상승 에지에서 1번, 하강 에지에서 1번 2번 들어 온다.
ISR(INT6_vect)
{
	//1.상승 에지 일때
	if(ECHO_PIN_RIGHT &(1<<ECHO_RIGHT))
	{
		TCNT3=0;  //Timer3번(1->3교체) 조심!!!
	}
	//2.하강 에지 일때
	else
	{
		//에코핀에 들어 오는 펄스 길이를 us단위로 환산
		ultrasonic_right_distance=(1000000.0*TCNT3*1024/F_CPU)/58;
		if(ultrasonic_right_distance <= CRITICAL_DISTANCE){
			isRightBlocked = 1;
		}else{
			isRightBlocked = 0;
		}
	}
}

void ultrasonic_trigger()
{
	//======== LEFT ================
	TRIG_PORT_LEFT &= ~(1 << TRIG_LEFT); //low
	_delay_us(1);
	TRIG_PORT_LEFT |= 1 << TRIG_LEFT; //high
	_delay_us(15);
	TRIG_PORT_LEFT &= ~(1 << TRIG_LEFT); //low
	
	_delay_ms(50);  //주의사항 : 초음파 센서의 echo 응답시간 최대 38ms
	//delay_ms를 timer INT로 처리한다.    _delay_ms가 있어서는 안된다.
	// 현재 demo code는 _delay_ms를 썼지만, timer로 처리하기 바람.
	//======== CENTER ================
	TRIG_PORT_CENTER &= ~(1 << TRIG_CENTER); //low
	_delay_us(1);
	TRIG_PORT_CENTER |= 1 << TRIG_CENTER; //high
	_delay_us(15);
	TRIG_PORT_CENTER &= ~(1 << TRIG_CENTER); //low
	
	_delay_ms(50);  //주의사항 : 초음파 센서의 echo 응답시간 최대 38ms
	//delay_ms를 timer INT로 처리한다.    _delay_ms가 있어서는 안된다.
	// 현재 demo code는 _delay_ms를 썼지만, timer로 처리하기 바람.
	
	//======== RIGHT ================
	TRIG_PORT_RIGHT &= ~(1 << TRIG_RIGHT); //low
	_delay_us(1);
	TRIG_PORT_RIGHT |= 1 << TRIG_RIGHT; //high
	_delay_us(15);
	TRIG_PORT_RIGHT &= ~(1 << TRIG_RIGHT); //low
	
	_delay_ms(50);  //주의사항 : 초음파 센서의 echo 응답시간 최대 38ms
	//delay_ms를 timer INT로 처리한다.    _delay_ms가 있어서는 안된다.
	// 현재 demo code는 _delay_ms를 썼지만, timer로 처리하기 바람.
}

void ultrasonic_distance_check()
{
	ultrasonic_trigger(); // trigger 전송!
	//if(ultrasonic_trigger>=1000){
			//printf("L:%5dcm\n",ultrasonic_left_distance);
			//printf("C:%5dcm\n",ultrasonic_center_distance);
			//printf("R:%5dcm\n",ultrasonic_right_distance);
	//}

}