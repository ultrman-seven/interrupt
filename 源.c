//�ж�ϵͳ
//��ʱ���ж�
//LED��1�룬Ϩ��1��
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


void timer0InterruptOn(void)//�򿪶�ʱ���ж�
{
	EA = 1;//���ж�����
	ET0 = 1;//��ʱ���ж�����

	TMOD = 0x01;// 0000 0001 ��ʱ��0����λ��gate=0��������ʽ��0 ��ʱ�� ������ʽ��01 ��ʽһ 16λ����

	TH0 = 0xd8;
	TL0 = 0xf0;//��ֵ0xD8F0����ʱ10ms

	TR0 = 1;//��ʱ��0��ʼ����
}

void timer0interrupt(void)// interrupt 1
{
	static un16 time = 0;
	TH0 = 0xd8;
	TL0 = 0xf0;//��ֵ0xD8F0����ʱ10ms
	if (++time == 100)//�ۼ�100��10ms����1s
	{
		led0 = ~led0;
		time = 0;
	}
}