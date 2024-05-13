/*
 * led.c
 *
 * Created: 2024-04-29 오전 10:58:08
 *  Author: HARMAN-09
 */ 

#include "def.h"
#include "led.h"
#include "extern.h"
void shift_left2right_keep_ledon();
void shift_right2left_keep_ledon();
void led_all_on_off();
void flower_on();
void flower_off();

void make_pwm_led_control(void);
void init_led();

void init_led()
{
	DDRG |= 1 << 3;
}

void led_all_on_off()
{
	static int led_toggle=0;
	if (ms_count >= 300)
	{
		ms_count=0;
		led_toggle = !led_toggle;
		if(led_toggle)
		PORTA=0xff;
		else PORTA=0x00;
	}
	
}


// void shift_left2right_keep_ledon()
// {
// 	
//  
// 	static int i=0;
// 	
// 	while(1)
// 	{
// 		if(shift_timer>=300) 
// 	    {
// 			shift_timer=0;
// 			if(i>=8)
// 			{
// 				i=0;
// 				PORTA = 0x00;
// 			 
// 				break;
// 			}
// 			else
// 			{
// 				PORTA |= 0b00000001 << i++; 
// 			}
// 		}
// 		
// 	}

// void shift_right2left_keep_ledon()
// 
// {
// 	static int i=0;
// 	
// 	while(1)
// 	{
// 		
// 		if(shift_timer>=300)
// 		{
// 			shift_timer=0;
// 			
// 			if(i>=8)
// 			{
// 				i=0;
// 				PORTA = 0x00;
// 				break;
// 					
// 			}
// 			else
// 			{
// 				PORTA |= 0b10000000 >> i++; // 1) PORTA |= 0b00000001 << i 2) i++
// 			}
// 
// 				
// 		}
// 	}
// 	
// }

// void flower_on()
// {
// 	uint8_t bit_value=0b00010000;
// 
// 	static int i=0;
// 
// 	while(1)
// 	{
// 		if(shift_timer>=300)
// 		{
// 			shift_timer=0;
// 			if(i>=4)
// 			{
// 				i=0;
// 				PORTA = 0x00;
// 				break;
// 			}
// 			else
// 			{
// 				PORTA |= bit_value << i | bit_value >> i+1 ;
// 				i++;
// 			}
// 
// 		}
// 	}
// 	
// 
// }
// 
// void flower_off()
// {
// 	uint8_t bit_value=0b01111111;
// 
// 
// 	static int i=0;
// 
// 	while(1)
// 	{
// 		if(shift_timer>=300)
// 		{
// 			shift_timer=0;
// 			PORTA = 0xff; // 이게 없으면 shift할게 없어서 작동이 안된다.
// 			if(i>=4)
// 			{
// 				i=0;
// 				PORTA = 0x00;
// 				
// 			}
// 			else
// 			{
// 				PORTA &= bit_value >> i & bit_value << i+1 ;
// 				i++;
// 			}
// 		}
// 	}
// 
// }

void make_pwm_led_control(void)
{
	int dim=0; //led 밝기 조절 변수
	int direction=1; //1:밝기 증가 모드 -1:밝기 감소 모드
	
	DDRA = 0xff;
	PORTA=0xff; //led all on
	
	// d --> b b--> d
	while(1)
	{
		led_on_pwm(dim);
		dim += direction;
		if(dim==255) 
		{
			direction=-1;
		}
		if(dim==0)
		{
			direction=1;
		}
	}
}

void led_on_pwm(int dim)
{
	PORTA=0xff;
	
	for(int i=0; i<256; i++)
	{
		if(i>dim)
		{
			PORTA=0x00; // duty cycle이 넘어가면 led all off
		}
		_delay_us(20);
	}
}
