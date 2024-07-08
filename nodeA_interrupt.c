#include"header.h"

#define sw1 ((IOPIN0>>14)&1)
#define sw2	((IOPIN0>>15)&1)
#define sw3 ((IOPIN0>>16)&1)

extern CAN1 data;
//int flagLI=0,flagRI=0,flagHL=0;
extern int flagLI,flagRI,flagHL,flag;


//void eint0_sw3()__irq
//{
//delay_ms(20);
//	if(sw3==0)
//	{
//	//	while(sw3==0); 
//		data.byteA=0xAA;  
//		can_tx(data);
//	}	
//	EXTINT=(1<<0);
//	VICVectAddr=0; 
//}

void eint0_sw3()__irq
{
	flag=1;

	if(flagLI)
	flagLI=0;

	flagRI=(1^flagRI);
	if(flagRI)
	{
		uart_tx_string("RI ON - EE\r\n");
		data.byteA=0XEE;  
		can_tx(data);
	}
	else
	{
		uart_tx_string("RI OFF - FF\r\n");
	 	data.byteA=0XFF;  
	 	can_tx(data);
	}
	EXTINT=(1<<0);
	VICVectAddr=0; 
}


void eint1_sw1()__irq
{
	flag=1;
//uart_string_tx("In irq\r\n");
//delay_ms(100);
	if(flagRI)
		flagRI=0;

	flagLI=(1^flagLI);
	if(flagLI)
	{
		uart_tx_string("LI ON - CC\r\n");
		data.byteA=0XCC;  
		can_tx(data);
	}
	else
	{
		 uart_tx_string("LI OFF - DD\r\n");
		 data.byteA=0XDD;  
		 can_tx(data);
	}
	EXTINT=(1<<1);
	VICVectAddr=0; 	
}

void eint2_sw2()__irq
{
	flag=1;
	
	flagHL=(1^flagHL);
	if(flagHL)
	{
		uart_tx_string("HL ON - AA\r\n");
		data.byteA=0XAA;  
		can_tx(data);
	}
	else
	{
		uart_tx_string("HL OFF - BB\r\n");
	 	data.byteA=0XBB;  
	 	can_tx(data);
	}
	EXTINT=(1<<2);
	VICVectAddr=0; 	
}

 void config_vic(void)
{
	VICIntSelect=0;
	
	VICVectCntl0=(1<<5)|14;
	VICVectAddr0=(int)eint0_sw3;
	
	VICVectCntl1=(1<<5)|15;
	VICVectAddr1=(int)eint1_sw1;
	
	VICVectCntl2=(1<<5)|16;
	VICVectAddr2=(int)eint2_sw2;
	
	VICIntEnable=(7<<14);
}

void config_eint(void)
{
	PINSEL0|=0xa0000000;
	PINSEL1|=0X1;
	EXTMODE=0X7;
	EXTPOLAR=0X0;
}



