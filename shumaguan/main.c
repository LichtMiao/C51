#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit d1=P1^0;//控制第一个LED
uchar num;
uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71};//code是编码表
void delay(uint z);
void main()
{
	//将外部中断0设置为电平触发 IT0=0;
	//单片机打开默认是电平触发
	EA=1; //打开总中断
	EX0=1; //打开外部中断0
	IT0=1; //将外部中断0设置为电平触发
	//TCON=0x01;//直接对寄存器中的某一位进行操作
	//与上面一行的作用是相同的
	wela=1; //一开始打开所有的位选
	P0=0xc0; //让所有的数码管亮1100 0000
  wela=0;	
	//改变要显示的数据
	while(1)
	{
		for(num=0;num<16;num++)
		{
			dula=1;
			P0=table[num];
			dula=0;
			delay(1000);//延时1s
		}
	}	
}
//延时1ms
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
	{
		for(y=110;y>0;y--);
	}
}
//中断让第一个LED亮
//中断函数，中断程序不需要声明，没有返回值
void exter0() interrupt 0
{
	d1=0; //中断中若P2.2口为低电平则进入中断
}