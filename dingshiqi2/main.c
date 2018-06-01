/*
**利用动态扫描和定时器1在数码管上显示出从765432开始以1/10秒的速度往下递减，直至765398并保持显示此数，
**与此同时利用定时器0以500ms速度进行流水灯从上至下移动，当数码管上数减到停止时，实验板上流水灯也停止,
**然后全部开始闪烁，3s后（用定时器0）流水灯全部关闭、数码管上显示“HELLO”并保持住。
*/
#include <reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar temp, t0, t1, bai, shi, ge, flag, flag1; //流水灯循环移位temp，对P1口赋值
uint val;//char型只能装255，所以此处用int型装432。将765和432分开装。
sbit dula=P1^6; //控制显示什么数
sbit wela=P1^7; //控制哪一个数码管亮
uchar code table[]={  //code是编码表
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71,
	0x76,0x79,0x38,0x3f,0}; //HELLO的编码HELO
void init();
void display(uchar aa,uchar bb,uchar cc,uchar bai,uchar shi,uchar ge);
void delay(uint z) //z=1则延时1ms
{
	uint x,y;
	for(x=z;x>0;x--)
	{
		for(y=110;y>0;y--);
	}
}

//先写流水灯的程序
void main()
{
	init();
	while(1)
	{
		if(flag1!=1)
		{
			display(7,6,5,bai,shi,ge);
		}
		else
		{
			display(16,17,18,18,19,20); //编码表中第几个元素，最后一个数码管不显示，即为0
		}
	}
}
//初始化temp、定时器
void init()
{
	val=432;
	temp=0xfe; //初始化发光二极管,共阴极，低位有效
	P1=temp; //并让第一个发光二极管亮
	//初始化定时器T0、T1
	TMOD=0x11; //将两个定时器设置为工作方式1
	TH0=(65536-50000)/256; //定时器0装初值
	TL0=(65536-50000)%256;
	TH1=(65536-50000)/256; //定时器1装初值
	TL1=(65536-50000)%256;
	EA=1; //开总中断
	ET0=1;//开定时器0中断
	ET1=1;//开定时器1中断
	TR0=1;//启动定时器0中断
	TR1=1;//启动定时器1中断
}
//定时器0中断函数
void timer0() interrupt 1
{
	TH0=(65536-50000)/256; //装初值，现在是50ms
	TL0=(65536-50000)%256;
	t0++;
	if(flag!=1)
	{
		if(t0==10) //让流水灯以500ms速度往下流动
		{
			t0=1; // 清零
			temp=_crol_(temp,1);//发光二极管左移一位
			P1=temp; //让发光二极管亮
		}
	}
	else //如果flag==1
	{
		if(t0%4==0) //每200ms闪烁一次，对4求余为0
		{
			P1=~P1; //这之前所有灯是灭的，对所有流水灯取反，让所有灯亮
		}
		if(t0==60) //闪烁30ms后关闭流水灯
		{
			TR0=0; //关闭控制流水灯的程序，关定时中断0
			P1=0xff; //关闭所有的流水灯
			flag1=1; //一旦流水灯停止，对数码管进行HELLO显示操作
		}
	}
	
}
//定时器1中断函数。数的减和分离
void timer1() interrupt 3
{
	TH1=(65536-50000)/256; //装初值，现在是50ms
	TL1=(65536-50000)%256;
	t1++;
	if(t1==2) //100ms，对里面的数减1
	{
		t1=1;
		val--;
		bai=val/100;
		shi=val%100/10;
		ge=bai%10;
		if(val==398)
		{
			TR0=0; //关闭控制流水灯的程序，关定时中断0，此时TH0和TL0中依然存着随机数
			TH0=(65536-50000)/256; //还原定时器0
			TL0=(65536-50000)%256;
			TR0=0;//重新启动定时器0，定时3s
			flag=1; //设置标志位，防止定时器0开启时，流水灯继续流动
			t0=0; //t0之前存了数据了，需要清零，重新开始加1
			
			P1=0xff; //关闭所有的流水灯，然后用T0定时全部开始闪烁
			TR1=0; //关闭控制数码管的程序，关定时中断1
		}
	}
}
//数码管显示子程序
void display(uchar aa,uchar bb,uchar cc,uchar bai,uchar shi,uchar ge)
{
	dula=1; //段选，控制显示什么数
	P0=table[aa];
	dula=0;
	P0=0xff; //关闭所有的流水灯
	wela=1; //位选，控制哪一个数码管亮
	P0=0xfe; //低位有效，第一个数码管亮
	wela=0;
	delay(1);
	
	dula=1;
	P0=table[bb];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd; //第二个数码管亮
	wela=0;
	delay(1);
	
	dula=1;
	P0=table[cc];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfb;
	wela=0;
	delay(1);
	
	dula=1;
	P0=table[bai];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xf7;
	wela=0;
	delay(1);
	
	dula=1;
	P0=table[shi];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xef;
	wela=0;
	delay(1);
	
	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xdf;
	wela=0;
	delay(1);
}
	

