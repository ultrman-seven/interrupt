//���п��ж�
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

	//������ʽ1
	SM0 = 0;
	SM1 = 1;

	//���ö�ʱ��
	TMOD = 0x20;//������ʽ��2 
	TH1 = TL1 = 0xf9;
	TR1 = 1;//��ʱ��1��ʼ����
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