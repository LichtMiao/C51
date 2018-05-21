#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp,numdu,shi,ge;
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
	
	/***定时器T0初始化***/
	TMOD=0x01; //定时器T0工作在方式1：01
	TH0=(65536-50000)/256;//以2s为一次循环，50ms产生一次中断
	TL0=(65536-50000)%256;
	EA=1;//开总中断
	ET0=1;//开定时器0中断
	TR0=1;//启动定时器
	
	temp=12;
	numdu=0;
	while(1)
	{
	  shi=temp/10;
	  ge=temp%10;
	  dula=1;
	  P0=table[shi];
	  dula=0;
	  wela=1;
	  P0=0xfe;
	  wela=0;
	  delay(5);
	  
	  dula=1;
	  P0=table[ge];
	  dula=0;
	  wela=1;
	  P0=0xfd;
	  wela=0;
	  delay(5);
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
