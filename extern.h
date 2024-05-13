/*
 * extern.h
 *
 * Created: 2024-04-29 오전 11:27:46
 *  Author: kccistc
 */ 


#ifndef EXTERN_H_
#define EXTERN_H_

extern void shift_left2right_keep_ledon();
extern void shift_right2left_keep_ledon();
extern void flower_on();
extern void flower_off();

extern int get_button(int button_pin, int button_num);
extern void led_all_on_off();

extern void init_uart0(void);
extern void UART0_transmit(uint8_t data);

extern void bt_command_processing(void);
extern void init_uart1(void);

extern volatile uint32_t shift_timer; 
extern volatile uint32_t ms_count;   // ms count
extern volatile uint32_t ultrasonic_trigger_timer;
extern volatile int ultrasonic_distance;
extern volatile int ultrasonic_left_distance;
extern volatile int ultrasonic_center_distance;
extern volatile int ultrasonic_right_distance;
extern volatile char scm[50];

extern void init_ulatrsonic();
extern void ultrasonic_trigger();
extern void ultrasonic_distance_check();
extern void ultrasonic_led_control();

extern void I2C_LCD_init(void);
extern void I2C_LCD_Test();

extern void make_pwm_led_control(void);
extern void init_led();
extern void auto_mode_check();

#endif /* EXTERN_H_ */