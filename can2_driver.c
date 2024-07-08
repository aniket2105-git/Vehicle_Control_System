#include <LPC21xx.H>
#include"header.h"
#define select_tx_buf1 (1<<5)
#define start_tx (1<<0)
#define RBS (C2GSR&1)
#define RRB (1<<2)

 u32 *ptr=(u32 *)0xE0038000;
void can_init()
{
	PINSEL1|=0X14000;
	VPBDIV=1;
	C2MOD=0X1;
	/*..............INI script.................*/
	ptr[0]=0x20352037;
	ptr[1]=0x21232158;
	ptr[2]=0x23AB23FD;
	SFF_sa=0;
	SFF_GRP_sa=0XC;
	EFF_sa=0XC;
	EFF_GRP_sa=0XC;
	ENDofTable=0XC;

	/*................................*/
	C2BTR=0x001C001D;
	AFMR=0X2;
	C2MOD=0;
}

void can_rx(CAN1 *ptr)
{
	while(RBS==0);
	ptr->id=C2RID;
	ptr->dlc=(C2RFS>>16)&0xF;
	ptr->rtr=(C2RFS>>30)&1;
	
	if(ptr->rtr==0)
	{
		ptr->byteA=C2RDA;
		ptr->byteB=C2RDB;
	}
	C2CMR=RRB;
}


