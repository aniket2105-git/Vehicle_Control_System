#include"header.h"
#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)
#define LED4 (1<<20)
CAN1 data;
int flag=0,f_LI=0,f_RI=0,f_HL=0;

main()
{
	lcd_init();
	lcd_cmd(0x0C);
	IODIR0|=LED1|LED2|LED3|LED4;
	IOSET0|=LED1|LED2|LED3|LED4;

	can_init();
	config_vic();
	en_can2_intrpt();
	//uart_init(9600);
	//uart_tx_string("Node B:\r\n");
	 lcd_cgram();
	 lcd_cmd(0x01);
	 lcd_cmd(0xC0);
	 lcd_string("Vehicle Control");
	while(1)
	{	
		if(flag==1)
		{
			//uart_hex(data.byteA);
			//uart_tx_string("\r\n");
			flag=0;
	
/**************************Left Indicator**************/

			if(data.byteA==0xCC)
			{
				if(f_RI)
					f_RI=0;
				f_LI=1;
			}
			else if(data.byteA==0xDD)
			f_LI=0; 
	
/***********************Right Indicator*****************/

			if(data.byteA==0xEE)
			{
				if(f_LI)
					f_LI=0;
				f_RI=1;
			}
			else if(data.byteA==0xFF)
			f_RI=0;
	
/**************************Head Light***************/

			if(data.byteA==0xAA)
			{
			f_HL=1;
			}
			else if(data.byteA==0xBB)
			{
			f_HL=0;	 
			}
	
			/***********HL-sw2-LED2*************/

		   	if(f_HL){
				IOCLR0=LED2;
				IOCLR0=LED4;
				lcd_cmd(0x83);
				lcd_data(1);   	
			 }
			else
			{
				IOSET0=LED2;
				IOSET0=LED4;
				lcd_cmd(0x83);
				lcd_data(' ');
			}
	
			/***********LI-sw1-LED3*************/
			if(f_LI)
			{
				lcd_cmd(0x80);
		     	lcd_data(2);
				lcd_cmd(0x86);
				lcd_data(' ');
				while(flag==0)
				{
				IOCLR0=LED3;
				delay_ms(700);
				IOSET0=LED3;
				delay_ms(700);
				}
			}
			else
			{
			IOSET0=LED3;
			lcd_cmd(0x80);
		    lcd_data(' ');
			}
	
			/***********RI-sw3-LED1*************/
		   	if(f_RI)
			{
			    lcd_cmd(0x86);
		     	lcd_data(0);
				lcd_cmd(0x80);
				lcd_data(' ');
				while(flag==0)
				{
				IOCLR0=LED1;
				delay_ms(700);
				IOSET0=LED1;
				delay_ms(700);
				}
			}
			else
			{
			IOSET0=LED1;
			lcd_cmd(0x86);
			lcd_data(' ');
			}
		}	
	}
}


