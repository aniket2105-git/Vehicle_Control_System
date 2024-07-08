#include"header.h"

CAN1 data;
int flagLI=0,flagRI=0,flagHL=0,flag=0;

main()
{
	can_init();
	
	data.id=0XDF;
	data.rtr=0;
	data.dlc=8;
	data.byteA=0;
	data.byteB=0;
	
	config_vic();
	config_eint();
	uart_init(9600);
	uart_tx_string("Node A:\r\n");
	lcd_init();
	lcd_cmd(0x0c);
	
	while(1)
	{
		//uart_string_tx("In main\r\n");
		if(flag)
		{
			flag=0;
	    /************************************/
			if(flagLI)
			{
				while(flagLI)
				{
					lcd_cmd(0x83);
					lcd_data('L');
					delay_ms(500);
					lcd_cmd(0x01);
					if(flagHL)
					{
						lcd_cmd(0x87);
						lcd_string("HL");
					}
					delay_ms(500);
				}
			}
			else
			lcd_cmd(0x01);
		
		/****************************************/	
			if(flagRI)
			{
				while(flagRI)
				{
					lcd_cmd(0x89+3);
					lcd_data('R');
					delay_ms(500);
					lcd_cmd(0x01);
					if(flagHL)
					{
						lcd_cmd(0x87);
						lcd_string("HL");
					}
					delay_ms(500);
				}
			}
			else
			lcd_cmd(0x01);

		/*******************************************/
		if(flagHL)
			{
				lcd_cmd(0x87);
				lcd_string("HL");
				while(flag==0);
			}
			else
				lcd_cmd(0x01);
		/*******************************************/
		}
	}
}

