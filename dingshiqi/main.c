#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit d1=P1^0;//控制第一个LED
uchar num,tt;
uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71};//code是编码表
void delay(uint z);
void main()
{
	num=0;
	tt=0;
	TMOD=0x01; //定时器T0工作在方式1：01
	TH0=(65536-50000)/256;//计算初值 高八位
	TL0=(65536-50000)%256; //低八位
	//将外部中断0设置为电平触发 IT0=0;
	//单片机打开默认是电平触发
	EA=1; //打开总中断
	ET0=1;//打开定时器0中断
	TR0=1;//启动定时器0
	wela=1; //一开始打开所有的位选
	P0=0xea; //1110 1010
  wela=0;	
	dula=1;
	P0=0x3f; //段选为0，不然进入循环时会出错，因为没定义段选，是随机的
	//过1s选1
	dula=0;
	//改变要显示的数据
	while(1)
	{
		if(tt==20) //进入20次中断
		{
			tt=0;
			num++;
			if(num==16)
				num=0;
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

//定时器中断0的服务程序
//进入中断后要重新装一次初值
void exter0() interrupt 1
{
	TH0=(65536-50000)/256;//计算初值 高八位
	TL0=(65536-50000)%256; //低八位
	tt++;
}