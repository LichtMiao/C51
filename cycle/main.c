#include<reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp; //设置全局变量给P1口赋值。P1是8位寄存器，定义成8位char型
sbit D1 = P1^0;
//void delay();
void delay(uint);//可以写参数z，也可直接写类型
void main()
{
	temp=0xfe; //点亮第一个灯
	P1=temp;
	while(1)
	{
		temp=_crol_(temp,1); //循环左移函数
		delay(600); //点亮第一个灯的延时
		P1=temp;//点亮第二个灯
	}
}
//带参子函数
void delay(uint z)
{
	uint x,y;
	for(x=100;x>0;x--)
	{
		for(y=z;y>0;y--);
	}
}