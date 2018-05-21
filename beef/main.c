/**
*让6个数码管每一个显示一个数，显示1到6
**/
#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp,aa,numdu,numwe;
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71};//数码管段选code
uchar code tablewe[]={
  0xfe,0xfd,0xfb,0xf7,
	0xef,0xdf};//数码管位选code,一共6个数码管

void main()
{
	numdu=0;
	numwe=0;	
	aa=0;
  /***定时器T0初始化***/
	TMOD=0x01; //定时器T0工作在方式1：01
	TH0=(65536-50000)/256;//以2s为一次循环，50ms产生一次中断
	TL0=(65536-50000)%256;
	EA=1;//开总中断
	ET0=1;//开定时器0中断
	TR0=1;//启动定时器
	
	/***刚开始时，需要让所有数码管不亮***/
	
	while(1)
	{
		if(aa==20)
		{
			aa=0;
			//送段码
			numdu++;
			if(numdu==7) //只显示1到6之间的变化
				numdu=1;
			dula=1;
			P0=table[numdu];
			dula=0;
			//送位码
			wela=1;
			P0=tablewe[numwe];
			wela=0;
			numwe++;
			if(numwe==6) //只用6个数码管，限定不超过6
				numwe=0;
		}
	}
}

/***定义定时器0中断***/
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;//以2s为一次循环，50ms产生一次中断
	TL0=(65536-50000)%256;
	aa++;
	//主函数中没有别的程序，则不需要把对它的操作放在这个中断程序里面
}