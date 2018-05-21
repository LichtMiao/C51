#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit D1 = P1^0;
//void delay();
void delay(uint);//可以写参数z，也可直接写类型
void main()
{
	while(1)
	{
		D1=0;
		delay(600);
		D1=1;
		delay(600);
	}
}
/*
void delay()
{
	uint x,y;
	for(x=100;x>0;x--)
	{
		for(y=600;y>0;y--);
	}
}
*/
//带参子函数
void delay(uint z)
{
	uint x,y;
	for(x=100;x>0;x--)
	{
		for(y=z;y>0;y--);
	}
}