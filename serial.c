//串行口中断
#include<reg52.h>

typedef unsigned char un8;
typedef unsigned int un16;

main()
{
	void serialPortInterruptOn(void);

	serialPortInterruptOn();
	while (1);
}

void serialPortInterruptOn(void)
{
	EA = ES = REN = 1;
	PCON |= 0x80;

	//工作方式1
	SM0 = 0;
	SM1 = 1;

	//设置定时器
	TMOD = 0x20;//工作方式：2 
	TH1 = TL1 = 0xf9;
	TR1 = 1;//定时器1开始工作
}

void serialInterrupt(void) interrupt 4
{
	un8 receive;
	receive = SBUF;
	RI = 0;
	SBUF = receive - 1;
	while (!TI);
	TI = 0;
}
