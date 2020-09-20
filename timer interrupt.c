//中断系统
//定时器中断
//LED亮1秒，熄灭1秒
#include<reg52.h>

typedef unsigned char un8;
typedef unsigned int un16;

char led0;//sbit led0 = P2 ^ 0;

main()
{
	void timer0InterruptOn(void);

	timer0InterruptOn();
	while (1);
}


void timer0InterruptOn(void)//打开定时器中断
{
	EA = 1;//总中断允许
	ET0 = 1;//定时器中断允许

	TMOD = 0x01;// 0000 0001 定时器0低四位；gate=0，工作方式：0 定时， 工作方式：01 方式一 16位计数

	TH0 = 0xd8;
	TL0 = 0xf0;//初值0xD8F0，计时10ms

	TR0 = 1;//定时器0开始工作
}

void timer0interrupt(void)// interrupt 1
{
	static un16 time = 0;
	TH0 = 0xd8;
	TL0 = 0xf0;//初值0xD8F0，计时10ms
	if (++time == 100)//累计100个10ms，即1s
	{
		led0 = ~led0;
		time = 0;
	}
}
