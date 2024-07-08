#include "header.h"

extern int flag;
extern CAN1 data;
 

																	 
void can2_rx_handler()__irq
{
	flag=1;
	data.id=C2RID;
	data.dlc=(C2RFS>>16)&0XF;
	data.rtr=(C2RFS>>30)&1;	
	if(data.rtr==0)
	{
		data.byteA=C2RDA;
		data.byteB=C2RDB;
	}
	C2CMR=(1<<2);
	VICVectAddr=0;
}

void config_vic(void)
{
	VICIntSelect=0;
	VICVectCntl0=(1<<5)|27;
	VICVectAddr0=(int)can2_rx_handler;
	VICIntEnable=(1<<27);
}

void en_can2_intrpt(void)
{
	 C2IER=0x1;
}

/*void config_eint()
{
PINSEL1=0x1;
EXTMODE=0X1;
EXTPOLAR=0;
IODIR0=1<<17;
} */

//void uart0_handler()__irq
//{
//char ch;
//while((U0IIR&4)==0);
//ch=uart_rx();
//uart_string_tx("irq");
//VICVectAddr=0;
//delay_ms(1000);
//}

