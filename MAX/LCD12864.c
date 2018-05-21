//LCD12864液晶显示函数
#ifndef LCD_12864_H_
#define LCD_12864_H_
/*****************************
12864程序
*******************************/
#include"variable.h"
sbit CS=P2^0;
sbit SID=P2^1;
sbit SCLK=P2^2;


/*****************************/
void delay(uchar k){
int i,j;
for (i=0;i<=k;i++){
for (j=0;j<=32;j++);
}
}
/*******12864**写数据函数 *************/
void send(bit ID,uchar datas)	   /*ID为0：指令模式；ID为1：数据模式     */
{
 
uchar t=3,k,tempdata;
CS=0;
SCLK=0;
SID=0;
CS=1;
while(t--){
switch (t+1){
case 3: tempdata=firstbyte|(ID*2);break;
case 2: tempdata=datas&0xf0;break;
case 1: tempdata=(datas<<4)&0xf0; break;
}
for(k=1;k<=8;k++){
tempdata=tempdata<<1;
SCLK=0;
SID=CY;
SCLK=1;
}
delay(1);
}
CS=0;
}

/****************字符串显示函数********/
void send_str(char *str){
while(1){
if(*str=='\0')   break;
send(1,*str++);
}
}
/*********************************/
void num(){
char i;
send(0,0x93);
send_str(p_shape);		 //波形
send(0,0x8a); 
for (i=0;i<=tick_rate-1;i++){
send(1,*(number+*(p_rate+i)));	   //频率
}		
send(0,0x9b);
for (i=0;i<=tick_ratio-1;i++){
send(1,*(number+*(p_ratio+i)));	   	 //占空比
}
}

void num_Init(){
send(0,0x93);
send_str(shape2_);		 //波形
send(0,0x8a);
send(1,*(number));	//频率
send(0,0x9b);
send(1,*(number));	  //占空比
}
/**************************/
void LCM_display(){
send(0,0x01); 
if (SET==1){
send(0,0x83);
send_str(Str1_set);
}
else {
send(0,0x82);
send_str(Str1);
}
send(0,0x90);
send_str(Str2);
send(0,0x88);
send_str(Str3);
send(0,0x98);
send_str(Str4);
send(0,0x8e);
send_str("HZ");
send(0,0x9e);
send_str("%");

}

void LCM_display_shape(){
send(0,0x01);  		 //清除

send(0,0x83);
send_str(Str2);
send(0,0x90);
send_str(shape2);
send(0,0x88);
send_str(shape3);
send(0,0x98);
send_str(shape4);
}

void LCM_Init(){
send(0,0x30);  //指令集
send(0,0x0c);  //显示状态 
send(0,0x01);  //清除
send(0,0x06);  //点设定
}
#endif
