/*
**如果P3^4口按下，则发光二极管点亮，松手时发光二极管熄灭
*/
#include<reg52.h>
#define uchar unsigned char
sbit d1=P1^0;
sbit key1=P3^4;
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table[]={  //code是编码表
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71}; 
uchar num;	
void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void main()
{
	wela=1; //让第一个数码管亮
	P0=0xfe;
	wela=0;
	P3=0xff; //令P3口都为高电平，读取输入
	while(1)
	{
		if(key1==0) //如果按键按下，则点亮发光二极管，需要检测松手
		{
			delay(10);//一般案件按下去抖动5ms，使用延时函数10ms消抖
			if(key1==0) //延时函数之后，重新检测一下案件是否被按下去了，而不是抖动造成的
			{
				d1=0; //低位点亮
				num++;
				if(num==10)
				{
					num=0;
				}
			}
			/*****松手检测*****/
			while(!key1); //key1==0依然是按下去的，不退出这个if语句
						        //key1==1时，!key1为假，退出这个if循环
			delay(5); //松手消抖，防止抖动造成松手误判
			while(!key1);
		}
		else
		{
			d1=1;
		}
		dula=1; //每按一下，让数码管显示一次按的次数，按到9刷新
		P0=table[num];
		dula=0;
	}
}