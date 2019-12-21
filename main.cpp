#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

#define  KLETTER_COUNT	10
#define  KSPEED	10

//�����ӵ������ַ�
typedef struct 
{
	int  x; //��������
	int  y;
	char ch;//�����ַ�
	int isDisplay; //�Ƿ���ʾ 0 ����ʾ ������ʾ
	int life; //������������
}LETTER;

//��ĸ��ʼ��
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


//�ӵ���ʼ��
LETTER bullet;
void init_bullet(int x)
{
	bullet.ch = 30;
	bullet.x = x;
	bullet.y = 25;
	bullet.life = 1;
}

//�����л�
void  gotoxy(int x,int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE hout =  GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,pos);
}

//������ĸ
void draw_letter(char ch, int x,int y)
{
	gotoxy(x,y);
	printf("%c",ch);
}

//�ж���ĸ�Ƿ���ʾ
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

//�����е���ĸ�½�
void  letterMov()
{
	isLetterDisplay(); //�ȸ���������ĸ��״̬ 
	for(int i=0;i<KLETTER_COUNT;i++) //���е���ĸ״̬����һ��
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

//�ӵ�����
void bulletMov()
{
	if(bullet.life==1)
	{
		draw_letter(' ',bullet.x,bullet.y);
		draw_letter(bullet.ch,bullet.x,bullet.y-1);	
		bullet.y-- ;
	}
}

//����
void  flash_ip()
{
	for(int j=0;j<20;j++)//�ܹ���ӡ20��
	{
		for(int i=0;i<10;i++) //ȫ����ӡһ�飬ÿ�δ�ӡ
		{
			if(letter[i].y>=0)
			{
				gotoxy(letter[i].x,letter[i].y);//������ת����Ӧ��λ��
				printf(" ");// ��ӡ���ַ�
				gotoxy(letter[i].x,letter[i].y+1);//������ת����Ӧ��λ��
				printf("%c",letter[i].ch);// ��ӡ���ַ�
			}
			else
			{
				//��ӡ�հ���
				gotoxy(letter[i].x,letter[i].y);//������ת����Ӧ��λ��
				printf(" ");// ��ӡ���ַ�
			}	
			letter[i].y++;
		}
		Sleep(500);//��ʾ0.5s

	}
}

int main(void)
{
	int i=0;
	int flag = 0;
	int score = 0;
	init_letter(); //��ʼ�� ��ĸ
	 char		user_l = ' ';

	 while(letter[KLETTER_COUNT-1].y<24)
	 {
		 letterMov(); //��ĸ�½�һ��
		 if( _kbhit() )  //�ж��Ƿ񰴼�����
		 {
			user_l = _getch()  - 32;;//'A'-'a';
			fflush(stdin); //������̻�����
			for(i=0;i<KLETTER_COUNT;i++) //��������  Ѱ�Ұ��µİ����Ƿ��Ŀǰ��ʾ����ĸ����һ����
			{
				if(user_l==letter[i].ch && letter[i].life==1 && letter[i].isDisplay==1)
				{
					init_bullet(letter[i].x);//�����ӵ� //˵���ҵ���
					flag=1;
					break;
				}
			}
				while(bullet.y>0 && flag==1) //˵���ҵ����Ժ�Ž��ӵ������ȥ
				{
					bulletMov();
					if(bullet.y==letter[i].y)//���ӵ�����ĸ��ʱ��
					{
						bullet.life=0; //�����ӵ�
						letter[i].life = 0; //������ĸ
						draw_letter(' ',letter[i].x,letter[i].y);
						flag = 0;
						break; //����ѭ��
					}
					Sleep(50);
				}
		 }
		  Sleep(300);	
	 }

	

	 system("CLS"); //������
	 //ͳ�Ʒ���
	 for(i=0;i<KSPEED;i++)
	 {
		 if(letter[i].life==1)		score++;
	 }

	 printf("һ��%d����ĸ����������%d����ĸ��ʣ��%d����ĸ.\n",KSPEED,KSPEED-score,score);
	 //��ӡ

	 getchar();
	//system("pause");
	return 0;
}

