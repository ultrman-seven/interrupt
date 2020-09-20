#include<reg52.h>
#include<intrins.h>

typedef unsigned char un8;
typedef unsigned short int un16;

sbit dataIn = P3 ^ 6;
sbit dataOut = P3 ^ 5;
sbit input = P3 ^ 4;

un8 code lowNum[8] = { 0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe };

un8 code character_ha[8] = { 0x38, 0x28, 0x38, 0x20, 0x57, 0x95, 0x57, 0x20 };
un8 code heart[8] = { 0x00,0x18,0x3C,0x3E,0x1F,0x3A,0x34,0x18 };
un8 code heartBig[8] = { 0x38,0x64,0x4A,0x35,0x2F,0x52,0x6C,0x38 };

void main()
{
	void setLed(un8 dataLow, un8 dataHigh);
	void externalInterrupt(void);

	un16 count;

	externalInterrupt();
	while (1)
	{
		count = 0xff;
		while (count--)
			setLed(lowNum[count % 8], heart[count % 8]);
		count = 0xff;
		while (count--)
			setLed(lowNum[count % 8], heartBig[count % 8]);
	}
}

void externalInterrupt(void)
{
	EA = EX0 = 1;
	IT0 = 0;
}

void exInterrupt(void) interrupt 0
{
	void setLed(un8 dataLow, un8 dataHigh);
	un8 countForLight = 0;//
	un8 countForFlow = 0;//控制移位
	un8 count;//每帧画面停留时间
	un8 time = 24;
	while (time--)
	{
		count = 5000;
		while (count--)
		{
			setLed(_crol_(lowNum[countForLight], countForFlow), character_ha[countForLight]);
			if (countForLight == 7)
				countForLight = 0;
			else
				countForLight++;
		}
		if (countForFlow == 7)
			countForFlow = 0;
		else
			countForFlow++;
	}
}

void setLed(un8 dataLow, un8 dataHigh)
{
	void hc595SendByte(un8);
	void delay(un16);

	hc595SendByte(dataHigh);
	P0 = dataLow;
	delay(100);
	P0 = 0xff;
}

void hc595SendByte(un8 dat)
{
	un8 count;
	for (count = 0; count < 8; count++)
	{
		input = dat >> 7;
		dat <<= 1;
		dataIn = 0;
		_nop_();
		dataIn = 1;
	}
	dataOut = 0;
	_nop_();
	dataOut = 1;
}

void delay(un16 n)
{
	while (n--);
}
