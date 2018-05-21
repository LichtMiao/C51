//D/A转换 TLC5615是数模转换器
#ifndef TLC5615_H_
#define TLC5615_H_
#include"variable.h"
/*****************************
5615端口设置
*******************************/
sbit      A2 =     P3^2;       //CD4051 通道选择位 A
sbit      B2 =     P3^3;       // CD4051 通道选择位 B
sbit      C2 =     P3^4;       //CD4051 通道选择位 C

sbit      DIN =     P3^0;       //数据入口
sbit      CLK =     P3^1;       //时钟
sbit      CS1 =     P3^6;       //片选（占空比）
sbit      CS2 =     P3^7;       //片选 （频率）

sbit     A0= 	P2^3;		    //A0   max038波形选择
sbit     A1=     P2^4;		    //A1	   max038波形选择




/********************************************************************/
// 名称 : write_5615(uint date) TLC5615数模转换器
// 功能 :  DATLC5615写入数据
// 输入 : 数据date
// 输出 : ——	
// 备注 ：
/***********************************************************************/
void write_5615_duty(uint date){			  
   uint i;
   CLK=0;
   delay(5);
   CS1=0;						  /*片选拉低  准备写数据*/
   						  /**/
   date<<=5;					  /*数据左移四位 高四位虚拟位*/
   for(i=0;i<12;i++){			  /*数据循环12  其中最后两位是填充位 */
   DIN=(bit)(date&0x8000);		  /*读取 数据最高位*/
   CLK=1;						  /*时钟拉高*/
   delay(5);					   /*稍延时*/
   CLK=0;
   delay(5);						  /*时钟拉低*/
   date<<=1;					  /*数据左移一位 准备下一位数据写入*/
   }
   CS1=1;						  /*片选拉高*/
   
}
/********************************************************************/
// 名称 : write_5615(uint date)
// 功能 :  DATLC5615写入数据
// 输入 : 数据date
// 输出 : ——	
/***********************************************************************/
void write_5615_Fre(uint date){			  
   uint i;
   CLK=0;
   delay(5);
   CS2=0;						  /*片选拉低  准备写数据*/
   						  /**/
   date<<=5;					  /*数据左移四位 高四位虚拟位*/
   for(i=0;i<12;i++){			  /*数据循环12  其中最后两位是填充位 */
   DIN=(bit)(date&0x8000);		  /*读取 数据最高位*/
   CLK=1;						  /*时钟拉高*/
   delay(5);					   /*稍延时*/
   CLK=0;
   delay(5);						  /*时钟拉低*/
   date<<=1;					  /*数据左移一位 准备下一位数据写入*/
   }
   CS2=1;						  /*片选拉高*/
   
}

/***************占空比设定******************/
uint set_duty(float set_duty)
{
uint voltage_duty;
 voltage_duty=1024-(float)((set_duty-5)*1024/40);
 return voltage_duty;
}
/***************占空比设定完毕******************/

/***************频率设定******************/
float set_fre(float set_fre)
{
if((set_fre>=100)&&(set_fre<=2500))
{ 
A2=0;B2=0;C2=1;
voltage_fre=(float)(set_fre-200)/4.88;
//tys=voltage_fre;
}

else if((set_fre>=1000)&&(set_fre<=25000))
{ 
A2=0;B2=1;C2=1;
voltage_fre=(float)(set_fre-200)/48.93;
//tys=voltage_fre;
}

else if((set_fre>=10000)&&(set_fre<=250000))
{ 

A2=1;B2=1;C2=1;

voltage_fre=(float)(set_fre-200)/400.28;
//tys=voltage_fre;
}

else if((set_fre>=100000)&&(set_fre<=2500000))
{
A2=1;B2=0;C2=1;

voltage_fre=(float)(set_fre-200)/2700.0; 
//tys=voltage_fre;
}	
 return voltage_fre;
}
/***************频率设定完毕******************/

#endif