#include<lpc21xx.h>
#include"header.h"
#define RS (1<<8)
#define RW (1<<9)
#define EN (1<<10)
void lcd_data(u8 data)
{
IOCLR0=0x7FF;
IOSET0=data;
IOSET0=RS;
IOCLR0=RW;
IOSET0=EN;
delay_ms(2);
IOCLR0=EN;
}
void lcd_cmd(u8 cmd)
{
IOCLR0=0x7FF;
IOSET0=cmd;
IOCLR0=RS;
IOCLR0=RW;
IOSET0=EN;
delay_ms(2);
IOCLR0=EN;
}
void lcd_init(void)
{
PINSEL0|=0;
 IODIR0|=0x7FF; 
 lcd_cmd(0x38);
 lcd_cmd(0x0E);
 lcd_cmd(0x01);
}
void lcd_string(s8 *ptr)
{
while(*ptr)
{
lcd_data(*ptr);
ptr++; 
}
}


void lcd_cgram(void)
{
u8 a[24]={0x4,0X02,0X1F,0X1F,0X02,0X04,0X00,0X00,0x0E,0x11,0x00,0x0E,0x1F,0x1F,0x1F,0x00,0x04,0x08,0x1F,0x1F,0x08,0x04,0x00,0x00};
u32 i=0;
lcd_cmd(0x40);
for(i=0;i<24;i++)
lcd_data(a[i]);
}
