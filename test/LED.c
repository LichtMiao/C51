#include<reg52.h>
//位方式点亮第一个发光二极管
sbit D1 = P1^0;
unsigned int a;
void main()
{
	while(1)
	{
		a = 51000; //暂停500ms,通过调试模式设置断点，较精确地给出暂停时间
		D1 = 0;
		while(a--); //若表达式不为0，则为真，执行语句while(a--)；
		//否则跳出while语句，即不执行while(a--)，直接执行其后面的语句
		a = 51000;
		D1 = 1;
		while(a--);	//先判断a，再减1。当a=0,会退出while语句，但依然要减1，所以变成了0xFFFF.
	}
	//总线方式
	// P1 = 0xFD; //1111 1101将第二个灯点亮
}