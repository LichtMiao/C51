//键盘函数
#ifndef Key_H_ //防止头文件的重复包含和编译
#define Key_H_
/*****************************
键盘程序
*******************************/

char keypad_scan(void)			 //键盘扫描
{
char key,i;
P1=0xf0;
do
if (P1!=0xf0){
 for(i=0;i<=3;i++){
  P1=ksp[i];
  if(P1!=ksp[i]){
    delay(5);
    key=P1;
    if(key!=ksp[i]){
     delay(255);delay(255);	 
	 return (key);
    }
  }
}

}while(1); 
}
/***************获得键值*************/
char gotkey()
{
char temp,i;
temp=keypad_scan();
for(i=0;i<=15;i++)
{
if(temp==key_code[i])
return(i);
}
return (16);
 }
#endif

