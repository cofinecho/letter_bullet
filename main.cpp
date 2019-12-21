#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

#define  KLETTER_COUNT	10
#define  KSPEED	10

//定义子弹或者字符
typedef struct 
{
	int  x; //定义坐标
	int  y;
	char ch;//定义字符
	int isDisplay; //是否显示 0 不显示 否则显示
	int life; //定义声明周期
}LETTER;

//字母初始化
LETTER  letter[KLETTER_COUNT];

void init_letter(void)
{
	srand((unsigned)time(NULL));
	for(int i=0;i<KLETTER_COUNT;i++)
	{
		letter[i].ch = rand()%26 + 'A' ;
		letter[i].x = rand()%80;
		//printf("letter[%d].x = %d.\n",i,letter[i].x);
		letter[i].y = i*(-2);
		//printf("letter[%d].y= %d.\n",i,letter[i].y);
		letter[i].life = 1;
	}
}


//子弹初始化
LETTER bullet;
void init_bullet(int x)
{
	bullet.ch = 30;
	bullet.x = x;
	bullet.y = 25;
	bullet.life = 1;
}

//坐标切换
void  gotoxy(int x,int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE hout =  GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,pos);
}

//绘制字母
void draw_letter(char ch, int x,int y)
{
	gotoxy(x,y);
	printf("%c",ch);
}

//判断字母是否显示
void isLetterDisplay()
{
	for(int i=0;i<KLETTER_COUNT;i++)
	{
		if(0==letter[i].life)
		{
			letter[i].isDisplay=0;
		}
		else if(letter[i].y < 0  ||  letter[i].y>24)
		{
			letter[i].isDisplay = 0;
		}
		else 
		{
			letter[i].isDisplay = 1;
		}
	}
}

//让所有的字母下降
void  letterMov()
{
	isLetterDisplay(); //先更新所有字母的状态 
	for(int i=0;i<KLETTER_COUNT;i++) //所有的字母状态更新一遍
	{
		if(letter[i].y<25)
		{
			if(letter[i].isDisplay)
			{
				draw_letter(' ',letter[i].x,letter[i].y);
				draw_letter(letter[i].ch,letter[i].x,letter[i].y+1);
			}
			else
			{
				draw_letter(' ',letter[i].x,letter[i].y);
			}
			letter[i].y++;
		}
		else
		{
			draw_letter(' ',letter[i].x,letter[i].y);
		}
	}
}

//子弹向上
void bulletMov()
{
	if(bullet.life==1)
	{
		draw_letter(' ',bullet.x,bullet.y);
		draw_letter(bullet.ch,bullet.x,bullet.y-1);	
		bullet.y-- ;
	}
}

//动画
void  flash_ip()
{
	for(int j=0;j<20;j++)//总共打印20次
	{
		for(int i=0;i<10;i++) //全部打印一遍，每次打印
		{
			if(letter[i].y>=0)
			{
				gotoxy(letter[i].x,letter[i].y);//首先跳转到对应的位置
				printf(" ");// 打印该字符
				gotoxy(letter[i].x,letter[i].y+1);//首先跳转到对应的位置
				printf("%c",letter[i].ch);// 打印该字符
			}
			else
			{
				//打印空白行
				gotoxy(letter[i].x,letter[i].y);//首先跳转到对应的位置
				printf(" ");// 打印该字符
			}	
			letter[i].y++;
		}
		Sleep(500);//显示0.5s

	}
}

int main(void)
{
	int i=0;
	int flag = 0;
	int score = 0;
	init_letter(); //初始化 字母
	 char		user_l = ' ';

	 while(letter[KLETTER_COUNT-1].y<24)
	 {
		 letterMov(); //字母下降一行
		 if( _kbhit() )  //判断是否按键按下
		 {
			user_l = _getch()  - 32;;//'A'-'a';
			fflush(stdin); //清除键盘缓冲曲
			for(i=0;i<KLETTER_COUNT;i++) //遍历数组  寻找按下的按键是否和目前显示的字母有重一样的
			{
				if(user_l==letter[i].ch && letter[i].life==1 && letter[i].isDisplay==1)
				{
					init_bullet(letter[i].x);//例化子弹 //说明找到了
					flag=1;
					break;
				}
			}
				while(bullet.y>0 && flag==1) //说明找到了以后才将子弹发射出去
				{
					bulletMov();
					if(bullet.y==letter[i].y)//当子弹打到字母的时候
					{
						bullet.life=0; //销毁子弹
						letter[i].life = 0; //销毁字母
						draw_letter(' ',letter[i].x,letter[i].y);
						flag = 0;
						break; //跳出循环
					}
					Sleep(50);
				}
		 }
		  Sleep(300);	
	 }

	

	 system("CLS"); //清屏、
	 //统计分数
	 for(i=0;i<KSPEED;i++)
	 {
		 if(letter[i].life==1)		score++;
	 }

	 printf("一共%d个字母，你削掉了%d个字母，剩余%d个字母.\n",KSPEED,KSPEED-score,score);
	 //打印

	 getchar();
	//system("pause");
	return 0;
}

