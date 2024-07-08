#include <LPC21xx.H>
#include<stdio.h>
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
typedef	unsigned short int u16;
typedef	signed short int s16;

#define sw1 ((IOPIN0>>14)&1)   //P0.14
#define sw2 ((IOPIN0>>15)&1)   //P0.15
#define sw3 ((IOPIN0>>16)&1)   //P0.16

extern void delay_ms(u32 ms);
extern void uart_init(u32 baud);
extern void uart_tx(u8 data);
extern u8 uart_rx(void);
extern void uart_tx_string(s8 *ptr);
extern void uart_tx_integer(s16 num);
extern void uart_tx_float(f32 f);
extern void uart_rx_str(s8 *ptr,u32 len);
//extern void uart_rx_string(s8 *ptr);
extern void uart_rx_string(s8 *p,s32 max_bytes);
extern void uart_rx_string1(s8 *ptr,u8 len);
extern void uart_hex(s32 num);
 
 typedef struct can2
 {
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
 }CAN1;

 extern void can_init(void);
 extern void can_tx(CAN1 v);
 extern void can_rx(CAN1 *ptr);
 extern void uart0_tx_hex(s32 num);
 extern void config_vic(void);
 extern void can2_rx_intr_en(void);

extern void lcd_data(u8 data);
extern void lcd_cmd(u8 cmd);
extern void lcd_init(void);
extern void lcd_string(s8 *ptr);

extern void config_eint(void);
extern void config_vic(void);

