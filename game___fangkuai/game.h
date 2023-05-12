#pragma once
#define LENGTH 10
#define HIGH 20

#define g_QIANBLUE "0,240,240"
#define g_SHENBLUE "0,0,240"
#define g_SHENCHENG "240,160,0"
#define g_YELLOW "240,240,0"
#define g_GREEN "0,240,0"
#define g_VIOLET "160,0,240"
#define g_RED "240,0,0"
#define g_BLACK "0,0,0"
#define g_qb 1
#define g_sb 3
#define g_sc 5
#define g_y 7
#define g_g 9
#define g_v 13
#define g_r 11


//��¼δ��ɵĺ���
//
//�жϷ�����ײ�ĺ���
//�ƶ�����ĺ���
//���������ĺ���
//��Ӧ���̺���
//�����ƶ�����
//�Զ��½�����
//���ƶ�����̶��ĺ���

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int g_random7();
int* g_scan_map(int(*map)[LENGTH]);
int** sort_55(int* oldmap);
int* xyoffset(int x, int y, int Be_countedx, int  Be_countedy);
int** newmap(int(*oldmap)[10], int(*map55)[5]);
void menu(int(*map)[10]);
void getcolor(int square);
int** atuo_move_down(int(*map)[10]);
int** move_g(const char* mode, int(*map)[10]);

int g_random7_a = 0;//g_random7�����ľɷ���ֵ

//����������
void menu(int(*map)[10])
{
	setfillcolor(RGB(40, 44, 52));
	fillrectangle(300, 0, 475, 680);
	/*fillrectangle(0, 0, 30, 30);�������*/
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			getcolor(map[i][j]);
			fillrectangle(30 * j, 30 * i, 30 * (j + 1), 30 * (i + 1));
		}
	}			//���Ƶ�ͼ
}


//��ȡ1��7�����ֵ������ֵΪint
int g_random7()//����д�������������������������������������������������ĳ�7��Ϊһ������˳��
{
	int a;
	srand((unsigned)time(NULL));
	a = rand();
	return (a % 7 + 1);
}



//ɨ�赱ǰ��ͼ��Ӧ�ƶ��ķ���   0��7Ϊxy����x��Ӧh,y��Ӧl��8Ԫ�ر�ʾ���ĵ�λ��,9Ԫ�ر�ʾ��һ�����ɫ
int* g_scan_map(int(*map)[LENGTH])

{

	//���ص��ܽ��ͼ������4��xy���꣬1�����ĵ�λ�ã������4��xy����1����ǰ��ɫ
	int* remap = (int*)calloc(10, sizeof(int));
	int remap_int = 0;//remap���±꣬����д��
	int recolor = 0;//���ص���ɫ����
	for (int i = 0; i < HIGH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			if (map[i][j] > 14)
			{
				int decide_color = 0;//����11��Ϊ���ж�ԭ��ɫ
				decide_color = map[i][j] / 15;
				if ((decide_color == 1 || decide_color == 2))//�жϵ�ǰ��ɫ��д��recolor
				{
					recolor = g_qb;
				}
				else if ((decide_color == 3 || decide_color == 4))
				{
					recolor = g_sb;
				}
				else if ((decide_color == 5 || decide_color == 6))
				{
					recolor = g_sc;
				}
				else if ((decide_color == 7 || decide_color == 8))
				{
					recolor = g_y;
				}
				else if ((decide_color == 9 || decide_color == 10))
				{
					recolor = g_g;
				}
				else if ((decide_color == 11 || decide_color == 12))
				{
					recolor = g_r;
				}
				else if ((decide_color == 13 || decide_color == 14))
				{
					recolor = g_v;
				}

				remap[remap_int] = i;
				remap[remap_int + 1] = j;
				if ((map[i][j] % 2) == 0)
				{
					remap[8] = remap_int / 2;//��0123
				}
				remap_int = remap_int + 2;
			}
		}
	}
	remap[9] = recolor;//��ǰɫ����ɫ
	return remap;
}



//����Ϊnew[x][y]    xΪ��h��yΪ��l��������22,ȫ��д��55����ϵ��.8Ԫ�ر�ʾ���ĵ�λ��,9Ԫ�ر�ʾ��һ�����ɫ
//ͬʱ������˳ʱ����תһ�ε�����
int** sort_55(int* oldmap)
{
	/*int newmap[5][5] = { 0 };*/
	int** newmap = NULL;
	newmap = (int**)calloc(5, sizeof(int) * 5);
	for (int i = 0; i < 5; i++)
	{
		newmap[i] = (int*)calloc(5, sizeof(int));
	}
	newmap[2][2] = oldmap[9] + 1;
	int hexin[2] = { 0 };//��¼oldmap����ĺ�������
	hexin[0] = oldmap[oldmap[8]];//x
	hexin[1] = oldmap[oldmap[8] + 1];//y,����������꣬¼�뵽newmap����
	for (int i = 0; i < 8; i = i + 2)//ѭ��4��
	{
		if ((i / 2) == oldmap[8])
		{
			int* xy_re = (int*)calloc(2, sizeof(int));
			xy_re = xyoffset(oldmap[i], oldmap[i + 1], hexin[0], hexin[1]);
			newmap[2 + xy_re[0]][2 - xy_re[1]] = oldmap[9];
		}
	}
	return newmap;
}




//xyΪ��Ҫ����������꣬Be_counted��ƫ�ƵĲ��յ�(ͨ��Ϊ��������)������ֵ��һ������ˮƽ��ʹ�ֱ���ָ�룬�����Ͻ�ΪС�����½�Ϊ��
int* xyoffset(int x, int y, int Be_countedx, int  Be_countedy)
{
	int* re = (int*)calloc(2, sizeof(int));
	re[1] = x - Be_countedx;//��ֱ
	re[0] = y - Be_countedy;//ˮƽ
	return re;
}


//��55ͼ��ĵ�ַת�Ƶ��������У�ע���ų����ƶ����������ٻ��ƴ����꣬����룬�ٽ�����ײ�ж�
//����ֵӦ�Ƚ���-1�жϣ�ȷ���Ƿ����ת�ƣ����Ϊ-1�򱣳�ԭ״
int** newmap(int(*oldmap)[10], int(*map55)[5])
{
	int** newmap = NULL;
	newmap = (int**)calloc(5, sizeof(int) * 5);
	for (int i = 0; i < 5; i++)
	{
		newmap[i] = (int*)calloc(5, sizeof(int));
	}
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (oldmap[i][j] < 15)//���������Թ̶�����
			{
				newmap[i][j] = oldmap[i][j];
			}
		}
	}								//ɸ����newmap�ǳ������ƶ��ķ���ĵ�ͼ
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			if (newmap[i][j + 3] == 0)//��ֹ��ײ
			{
				newmap[i][j + 3] = map55[i][j];//������55�����е�Ԫ��ת�Ƶ�newmap��
			}
			else
			{
				return (int**)-1;//�����ǰ���겻Ϊ0��ֱ�ӷ���-1
			}
		}
	}
	return newmap;

}

//ͨ���ж�ֵ��������ɫ
void getcolor(int square)
{
	if ((square == 0))
	{
		setfillcolor(RGB(0, 0, 0));
	}
	else if ((square == 1 || square == 2 || square == 15 || square == 30))
	{
		setfillcolor(RGB(0, 240, 240));
	}
	else if ((square == 3 || square == 4 || square == 45 || square == 60))
	{
		setfillcolor(RGB(0, 0, 240));
	}
	else if ((square == 5 || square == 6 || square == 75 || square == 90))
	{
		setfillcolor(RGB(240, 160, 0));
	}
	else if ((square == 7 || square == 8 || square == 105 || square == 120))
	{
		setfillcolor(RGB(240, 240, 0));
	}
	else if ((square == 9 || square == 10 || square == 135 || square == 150))
	{
		setfillcolor(RGB(0, 240, 0));
	}
	else if ((square == 11 || square == 12 || square == 165 || square == 180))
	{
		setfillcolor(RGB(240, 0, 0));
	}
	else if ((square == 13 || square == 14 || square == 195 || square == 210))
	{
		setfillcolor(RGB(160, 0, 240));
	}
	else
	{
		setfillcolor(RGB(255, 255, 255));
	}
	return;
}

//��¼ʱ�䣬��1s��������һ��
int** atuo_move_down(int(*map)[10])
{
	static time_t first, end;
	static int n = 0;
	if (n == 0)
	{
		first = time(NULL);
		n++;
	}
	end = time(NULL);
	if ((end - first) > 1)
	{
		move_g("DOWN", map);
		first = time(NULL);
	}
	return 0;
}


int** move_g(const char* mode, int(*map)[10])
{
	int** newmap = NULL;
	newmap = (int**)calloc(20, sizeof(int*));
	if (!newmap) exit(-1);
	for (size_t i = 0; i < 10; i++)
	{
		newmap[i] = (int*)calloc(10, sizeof(int));
		if (!newmap[i]) exit(-1);
	}
	if (mode == "DOWN")
	{
		for (size_t i = 20; i >0; i--)
		{
			for (size_t j = 10; j>0; j--)
			{
				if (map[i][j] != 0 &&)
				{

				}
			}
		}
	}
	else if (mode == "UP")
	{

	}
	else if (mode == "LEFT")
	{

	}
	else if (mode == "RIGHT")
	{

	}
	else
}
