#include<reg51.h>
#include"LCD12864.h"		//LCD 显示函数
#include"variable.h"	   //变量
#include"TLC5615.h"		   //5615 函数 用于调节 占空比 和 频率
#include"Key.h"			   //键盘函数

/*****************************
数组转换变量
unsigned long convert(uchar *str,uchar tick)

*******************************/
unsigned long convert(uchar *str,uchar tick){
uchar i,j;
unsigned long result;
sum=0;
for (i=0;i<tick;i++){
result=*(str+i);
for (j=tick-i;j>1;j--){
	result=result*10;
	}
sum=sum+result;
	}
return sum;

}


/*************************************
 主程序
*************************************/
void main()
{
uchar temp;

long Value_Duty = 0;
long Value_Fre = 0;

//uint a1,b1,c1,d1,e1,f1;
//A2=0;B2=0;C2=0;
SET=0;
ratio=0;
rate=0;
first=0;
tick_rate=0;
tick_ratio=0;
p_shape=shape2_;
p_rate=rate_num;
p_ratio=ratio_num;
LCM_Init();
LCM_display();
num_Init();
while(1){
  
temp=gotkey();
switch(temp){
 case 13:									  //设置
 	SET=1;ratio=0;ratio=0;shape=0;LCM_display();num();break;
 case 14:									  //占空比
 	if(SET==1){
		ratio=1;rate=0;shape=0;tick_ratio=0;send(0,0x0f);num();send(0,0x9b);send_str("   ");send(0,0x9b);}	//光标闪烁
	else {
		if (first==0){
			break;}
		LCM_display();num();}
	break;
 case 15:									  //频率
 	if(SET==1){
		rate=1;ratio=0;shape=0;tick_rate=0;send(0,0x0f);send(0,0x8a);send_str("       ");send(0,0x8a);}
	else {
	if (first==0){
		break;}
		LCM_display();num(); }
	break;
 case 12:									  //波形
 	if(SET==1){
		shape=1;ratio=0;rate=0;LCM_display_shape();send(0,0x0c);}
	else {
	if (first==0){
		break;}
		LCM_display();num();}
	break; 
 case 10:
 case 11: 									//确认键
	if ( ratio==1 || rate==1 ||shape==1 ||SET==1){
	SET=0;ratio=0;rate=0;shape=0;first=1;
	LCM_display();send(0,0x0c);			//光标不闪烁
	num();
	rtp=convert( rate_num, tick_rate);
	Value_Fre=set_fre(rtp);
	Value_Duty=set_duty(convert( ratio_num, tick_ratio));

	write_5615_duty(Value_Duty); 	//Value_Duty
	delay(10);									   
	write_5615_Fre(Value_Fre);//Value_Fre
	delay(10);
	   	
		}
	else {
	if (first==0){
		break;}
		LCM_display();num();}
	break;
 
	 case 0:
 case 1:
 case 2:
 case 3:
 case 4:
 case 5:
 case 6:
 case 7:
 case 8:
 case 9:
 	if(ratio==1) {							 //占空比
		if(tick_ratio>=2){break;}
		ratio_num[tick_ratio]=temp;
		send(1,*(number+temp));
		tick_ratio++;}	
	else if(rate==1) {
		if(tick_rate>=7){break;}
		rate_num[tick_rate]=temp;
		send(1,*(number+temp));
		tick_rate++;} 		     //频率
	else if(shape==1){
	LCM_display_shape();					     //波形				   
	switch(temp){
	case 1:p_shape=shape2_;A1=1;break;		     //正弦波
	case 2:p_shape=shape3_;A0=0;A1=0;break;		 //方波
	case 3:p_shape=shape4_;A0=1;A1=0;break;		 //三角波
	default :break;
	}
	LCM_display();
	num();
	}
	else {
	if (first==0){
		break;}
		LCM_display();num();}
	break; 
 default :break;
        }

}

}






