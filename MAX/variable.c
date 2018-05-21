//变量
#ifndef variable_H_
#define variable_H_
#define uchar unsigned char
#define uint unsigned int
#define firstbyte  0xf8
uchar tick_ratio;		   //占空比设定 键盘按下次数
uchar tick_rate;    	   //频率设定 键盘按下次数
uchar rate_num[7];			//频率 设定数组
uchar ratio_num[2];			//占空比   设定数组
uchar *p_shape;
uchar *p_rate;
uchar *p_ratio;
 long DA;
unsigned long sum=0;
float voltage_fre,rtp;
uint tys;
code uchar key_code[]={0x7b,0xe7,0xeb,0xed,0xd7,0xdb,0xdd,0xb7,0xbb,0xbd,0xee,0xde,0xbe,0x77,0x7d,0x7e};
code uchar ksp[]={0x7f,0xbf,0xdf,0xef};
code uchar Str1[]="波形发生器";
code uchar Str2[]="波形";
code uchar Str3[]="频率";
code uchar Str4[]="占空比";
code uchar Str1_set[]="设置";
code uchar shape2[]="1 sin";
code uchar shape3[]="2 squ";			
code uchar shape4[]="3 tri";
code uchar shape2_[]="sin";
code uchar shape3_[]="squ";			
code uchar shape4_[]="tri";
code uchar number[]="0123456789";

bit SET;	  	   //设置
bit ratio;	       //占空比
bit rate;	   	   //频率
bit shape; 
bit first;		  //是否设置过

#endif