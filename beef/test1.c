#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp,aa,num;
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71};//数码管code
void delay(uint z);
void main()
{
	num=0; 
	aa=0;
  /***定时器T0初始化***/
	TMOD=0x01; //定时器T0工作在方式1：01
	TH0=(65536-50000)/256;//以2s为一次循环，50ms产生一次中断
	TL0=(65536-50000)%256;
	EA=1;//开总中断
	ET0=1;//开定时器0中断
	TR0=1;//启动定时器
	
	/***流水灯程序***/
	//点亮第一个LED
	temp=0xfe;
	P1=temp;
	/***刚开始时，需要让数码管亮0***/
	dula=1;
	P0=table[0];
	dula=0;
	wela=1;
	P0=0xc0; //所有数码管全部打开1100 0000
	wela=0;
	while(1)
	{
		delay(1000);
		temp=_crol_(temp,1);//循环左移
		P1=temp;
	}
}
//延时函数1ms
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
	{
		for(y=110;y>0;y--);
	}
}
/***定义定时器0中断***/
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;//以2s为一次循环，50ms产生一次中断
	TL0=(65536-50000)%256;
	aa++;
  /***检测是否到了2s***/
	if(aa==40) // 2s/50ms.aa为进入中断的次数，如果进入中断40次，即2s，进行操作
	{
		//aa==40说明2s到了，则
		aa=0; //aa清零，则数码管的值改变一次，需要位选和段选
		num++;//num每加一次，需要判断num是否到了16，到了16则清零
		if(num==16)
		{
			num=0;
		}
		//让数码管显示下一个数值
		dula=1;
		P0=table[num];
		dula=0;
	}
}