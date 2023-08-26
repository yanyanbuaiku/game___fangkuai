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
//�жϷ�����ײ�ĺ���
//���������ĺ���,ע��Ӧ�ڹ̶��󱻵���
//�����ƶ�����



#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<crtdbg.h>


//���Ͻ�Ϊ00�������ұ�ˮƽ�����ٻع����ϲ�,[x][y]��x�ǲ�ߣ�y�ǲ��
struct Square_matrix
{								              //ż��Ϊ����
	int zhixian[4] = { 1,2,1,1 },             //ֱ�ߵڶ���Ϊ����[1]
		zuol[2][3] = { 3,0,0,4,3,3 },
		youl[2][3] = { 0,0,5,5,5,6 },         //�˶�ΪL�ͷ��飬���������º�����[1][0]�Լ�[1][2]
		fang[2][2] = { 7,7,7,8 },             //��Ϊ���飬���������½�[1][1]
		zxguai[2][3] = { 0,9,9,9,10,0 },
		yxguai[2][3] = { 11,11,0,0,12,11 },   //�˶�Ϊ��s�ͣ����Ķ���[1][1]
		daot[2][3] = { 0,13,0,13,14,13 };     //��Ϊ��T��������[1][1]
}matrix;


int g_random7();
void gudingmap(int(*map)[10]);
int* g_scan_map(int(*map)[LENGTH]);
int** sort_55(int* oldmap);
void putmatrix(int(*map)[LENGTH]);
int* xyoffset(int x, int y, int Be_countedx, int  Be_countedy);
int** newmap(int(*oldmap)[10], int(*map55)[5]);
void menu(int(*map)[10]);
void getcolor(int square);
void if_del(int(*map)[10]);
void atuo_move_down(int(*map)[10]);
int** move_g(const char* mode, int(*map)[10]);
void copy_array(int** src_array, int(*dest_array)[10], int row, int col);
void array_copyint(int dest[], int src[], int len);
int g_random7_a = 0;//g_random7�����ľɷ���ֵ
static time_t first, end;//atuo_move_down��������1s�Ĳ���
static time_t then, next;//menu��������ӳٵ�
static int if_next = 0;//��¼�Ƿ�map�п��ƶ���0Ϊ�޿��ƶ���1Ϊ�п��ƶ�
static int atuo_move_down_n = 0, FPS = 0;


//����������
void menu(int(*map)[10])
{
	if (next - then > 1000)
	{
		then = clock();
		//printf("FPS=%d\n", FPS);
		//FPS = 0;
	}
	if (atuo_move_down_n == 0)
	{
		then = clock();
		first = clock();
		atuo_move_down_n++;
	}end = clock();
	if (!if_next)
	{
		putmatrix(map);
	}
	setfillcolor(RGB(40, 44, 52));
	fillrectangle(300, 0, 475, 680);
	/*fillrectangle(0, 0, 30, 30);�������*/
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			getcolor(map[i][j]);
			fillrectangle(30 * j, 30 * i, 30 * (j + 1), 30 * (i + 1));
		}
	}
	if (difftime(end, first) > 100)
	{
		int caozuo = 0;
		if (GetAsyncKeyState(VK_UP))
		{
			int map_h = 0, map_l = 0, whether__up = 0, yes__up = 1;//map_h map_l�ֱ��¼���ĵ�ߺͳ����Ͻ�Ϊ���� ,whether__upΪ0ʱ֤��δ�ҵ�����ת���꣬Ϊ1��ʾ�ҵ�,yes_upΪ0��ʾ���Ե���߷�������ײ�޷���ת
			for (int i = 0; i < 20; i++)//������ͼѰ�����ĵ�
			{
				for (int j = 0; j < 10; j++)
				{
					if (map[i][j] > 14 && map[i][j] % 2 == 0)
					{
						map_h = i;
						map_l = j;
						whether__up = 1;
						break;
					}
				}
				if (whether__up == 1)
				{
					break;
				}
			}
			if (whether__up == 1)
			{
				int** remap = NULL, ** newmap = NULL;

				int* reg_scan_map = NULL;
				/*if (!reg_scan_map)
				{
					printf("%d", __LINE__); exit(-1);
				}*/
				newmap = (int**)calloc(20, sizeof(int*));
				for (size_t i = 0; i < 20; i++)
				{
					newmap[i] = (int*)calloc(10, sizeof(int));
				}
				copy_array(newmap, map, 20, 10);//��map���Ƶ�newmap��ֹ�������ԭ��ͼ
				for (size_t i = 0; i < HIGH; i++)
				{
					for (int j = 0; j < LENGTH; j++)
					{
						if (newmap[i][j] > 14)
						{
							newmap[i][j] = 0;//��newmap�еĿ��ƶ������޳�
						}
					}
				}
				reg_scan_map = g_scan_map(map);
				int setlinshimap[10] = { 0 };
				array_copyint(setlinshimap, reg_scan_map, 10);
				remap = sort_55(setlinshimap);
				/*map[map_h][map_l] = remap[2][2];*/
				int* xy = (int*)calloc(2, sizeof(int));//xy�ǽ���xyoffset����ֵ�Ĳ�����0Ϊˮƽ�1Ϊ��ֱ��
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (remap[i][j] > 0)
						{
							xy = xyoffset(i, j, 2, 2);
							if (map_h + xy[1] < HIGH && map_l + xy[0] < LENGTH && map_h + xy[1] >= 0 && map_l + xy[0] >= 0)//��ת��Խ��
							{
								printf("%d��ת��Խ�߽�\n", __LINE__);
								if (newmap[map_h + xy[1]][map_l + xy[0]] == 0)//newmap�˴�Ϊ��
								{
									newmap[map_h + xy[1]][map_l + xy[0]] = remap[i][j] * 15;
									printf("%d h____%d l____%d\n", __LINE__, map_h + xy[1], map_l + xy[0]);
								}
								else
								{
									yes__up = 0;
								}
							}
							else
							{
								printf("%dyes__up = 0\n\n", __LINE__);
								yes__up = 0;//��������ת
							}
						}
						if (yes__up == 0)
						{
							printf("%dyes__up = 0\n", __LINE__);
							break;
						}
					}
					if (yes__up == 0)
					{
						printf("%dyes__up = 0\n", __LINE__);
						break;
					}
				}
				if (yes__up == 1)
				{
					for (int i = 0; i < 20; i++)
					{
						for (size_t j = 0; j < 10; j++)
						{
							if (map[i][j] > 14)
							{
								map[i][j] = 0;
							}
						}
					}
					for (int i = 0; i < 20; i++)
					{
						for (size_t j = 0; j < 10; j++)
						{
							if (newmap[i][j] > 14)
							{
								map[i][j] = newmap[i][j];
							}
						}
					}
				}
				//printf("%d    %d",_CrtCheckMemory(),__LINE__);
				free(reg_scan_map);
				free(xy);
				for (size_t i = 0; i < 5; i++)
				{
					free(remap[i]);
				}
				free(remap);
				for (size_t i = 0; i < 20; i++)
				{
					free(newmap[i]);
				}

				free(newmap);
				first = clock();
				//caozuo++;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			int** newmap = NULL;
			first = clock();
			newmap = move_g("xiajiang", map);
			if (newmap[0][0] == -1)
			{
				//map = map;
				for (size_t i = 0; i < 20; i++)
				{
					free(newmap[i]);
				}
			}
			else for (size_t i = 0; i < 20; i++)
			{
				for (size_t j = 0; j < 10; j++)
				{
					map[i][j] = newmap[i][j];
				}
				free(newmap[i]);
			}
			free(newmap);
			Sleep(150);
			first = clock();
			caozuo++;
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{

			int** newmap = NULL;
			newmap = move_g("LEFT", map);
			if (newmap[0][0] == -1)
			{
				map = map;
				for (size_t i = 0; i < 20; i++)
				{
					free(newmap[i]);
				}
			}
			else for (size_t i = 0; i < 20; i++)
			{
				for (size_t j = 0; j < 10; j++)
				{
					map[i][j] = newmap[i][j];
				}
				free(newmap[i]);
			}

			free(newmap);
			Sleep(150);
			first = clock();
			caozuo++;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			int** newmap = NULL;
			newmap = move_g("RIGHT", map);
			if (newmap[0][0] == -1)
			{
				map = map;
				for (size_t i = 0; i < 20; i++)
				{
					free(newmap[i]);
				}
			}
			else for (size_t i = 0; i < 20; i++)
			{
				for (size_t j = 0; j < 10; j++)
				{
					map[i][j] = newmap[i][j];
				}
				free(newmap[i]);
			}
			free(newmap);
			Sleep(150);
			first = clock();
			caozuo++;
		}
	}
	//���Ƶ�ͼ
	atuo_move_down(map);
	next = clock();
	FPS++;
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
				int decide_color = 0;//����15��Ϊ���ж�ԭ��ɫ
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



//����Ϊnew[x][y]    xΪ��h��yΪ��l��������22,ȫ��д��55����ϵ��.8Ԫ�ر�ʾ���ĵ�λ��(��0��ʼ����),9Ԫ�ر�ʾ��һ�����ɫ
//ͬʱ������˳ʱ����תһ�ε�����
int** sort_55(int* oldmap)
{
	int** newmap = NULL;
	newmap = (int**)calloc(5, sizeof(int*));
	for (int i = 0; i < 5; i++)
	{
		newmap[i] = (int*)calloc(5, sizeof(int));
		if (!newmap[i]) exit(-1);
	}
	newmap[2][2] = oldmap[9] + 1;//��¼��ɫ��һ��ż��Ϊ����
	int hexin[2] = { 0 };//��¼oldmap����ĺ�������
	hexin[0] = oldmap[oldmap[8] * 2];//x
	hexin[1] = oldmap[oldmap[8] * 2 + 1];//y,����������꣬¼�뵽newmap����
	int* xy_re = (int*)calloc(2, sizeof(int));
	for (int i = 0; i < 8; i = i + 2)//ѭ��4��
	{

		xy_re = xyoffset(oldmap[i], oldmap[i + 1], hexin[0], hexin[1]);
		newmap[2 + xy_re[0]][2 - xy_re[1]] = oldmap[9];

	}
	free(xy_re);
	if (newmap[2][2] % 2 != 0) newmap[2][2]++;
	return newmap;
}


//xyΪ��Ҫ����������꣬Be_counted��ƫ�ƵĲ��յ�(ͨ��Ϊ��������)������ֵ��һ������ˮƽ�0Ԫ�أ��ʹ�ֱ�1Ԫ�أ���ָ�룬�����Ͻ�Ϊ�������½�Ϊ��
int* xyoffset(int x, int y, int Be_countedx, int  Be_countedy)
{
	int* re = (int*)calloc(2, sizeof(int));
	if (re)
	{
		re[1] = x - Be_countedx;//��ֱ
		re[0] = y - Be_countedy;//ˮƽ
	}
	else
	{
		printf("%d", __LINE__);
		exit(-1);
	}
	return re;
}


//��55ͼ��ĵ�ַת�Ƶ��������У�ע���ų����ƶ����������ٻ��ƴ����꣬����룬�ٽ�����ײ�ж�
//����ֵӦ�Ƚ���-1�жϣ�ȷ���Ƿ����eת�ƣ����Ϊ-1�򱣳�ԭ״
int** newmap(int(*oldmap)[10], int(*map55)[5])
{
	int** newmap = NULL;
	newmap = (int**)calloc(5, sizeof(int*));
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
				if (newmap[i][j])
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

void if_del(int(*map)[10])
{
	int del = -1;//-1Ϊ��ɾ�����У������л��п�ȱ��ȫ�ǹ̶�����
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] < 15 && map[i][j] != 0)//�ų����ƶ�����Ϳհ׸�
			{
				del = i;
			}
			else {
				del = -1;
			}
			if (del == -1)//����б���һ����������ֱ��ɨ����һ��
			{
				break;
			}
		}
		if (del != -1)//delΪ0��20�κ���ʱ��ʼɾ����j��
		{
			for (size_t i = 0; i < 10; i++)
			{
				map[del][i] = 0;
			}
			for (int k = del; k > 0; k--)//k_lim==1
			{
				//if (k == 0) { exit(-1); printf("%d %d", __LINE__, del); }
				for (size_t i = 0; i < 10; i++)
				{
					if (map[k - 1][i] < 15)
					{
						map[k][i] = map[k - 1][i];
					}

				}
				if (k == 1)//��һ�б��ƶ����ڶ���֮��
				{
					for (size_t i = 0; i < 10; i++)
					{

						map[0][i] < 15 ? map[0][i] = 0 : map[0][i];
					}
				}
			}
		}
	}
}

//��¼ʱ�䣬��1s��������һ��
void atuo_move_down(int(*map)[10])
{


	end = clock();
	if (difftime(end, first) > 800)
	{
		int** newmap = NULL;
		newmap = move_g("DOWN", map);
		if (newmap[0][0] == -1)
		{
			map = map;
			for (size_t i = 0; i < 20; i++)
			{
				free(newmap[i]);
			}
		}
		else for (size_t i = 0; i < 20; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				map[i][j] = newmap[i][j];
			}
			free(newmap[i]);
		}
		free(newmap);
		first = clock();
	}
	return;
}

//����ֵΪ-1ʱӦ�����ƶ��ķ������15��Ϊ�̶�̬
int** move_g(const char* mode, int(*map)[10])
{
	int** newmap = NULL;
	newmap = (int**)calloc(20, sizeof(int*));
	if (!newmap) exit(-1);
	for (size_t i = 0; i < 20; i++)
	{
		newmap[i] = (int*)calloc(10, sizeof(int));
		if (!newmap[i]) exit(-1);
	}
	copy_array(newmap, map, 20, 10);//��map���Ƶ�newmap��ֹ�������ԭ��ͼ
	if (mode == "DOWN")
	{
		for (int i = 19; i >= 0; i--)
		{
			for (int j = 9; j >= 0; j--)
			{
				if (i == 19 && newmap[i][j] > 14)//���ڵײ�����ײ
				{
					printf("�ײ��߽���ײ\t%d\n", __LINE__);
					gudingmap(map);
					newmap[0][0] = -1;
					return newmap;
				}
				if (i < 19 && newmap[i][j]>14 && newmap[i + 1][j] == 0)//���ڷ������Ƶ��жϣ�����else���������з���
				{
					newmap[i + 1][j] = newmap[i][j];
					newmap[i][j] = 0;
				}
				else if (i < 19 && newmap[i][j]>14 && newmap[i + 1][j] != 0)
				{
					printf("�ײ���ײ\t%d\n", __LINE__);
					gudingmap(map);
					newmap[0][0] = -1;
					return newmap;
				}
			}
		}
	}
	else if (mode == "LEFT")//����ɨ��Ӧ��������ɨ��
	{
		for (int i = 19; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{
				if (j == 0 && newmap[i][j] > 14)
				{
					printf("���߽���ײ\t%d\n", __LINE__);
					newmap[0][0] = -1;
					return newmap;
				}
				if (j < 10 && j >= 0 && newmap[i][j] > 14 && newmap[i][j - 1] == 0)//���ڷ������Ƶ��жϣ�����else���������з���
				{
					newmap[i][j - 1] = newmap[i][j];
					newmap[i][j] = 0;
				}
				else if (j < 10 && j >= 0 && newmap[i][j] > 14 && newmap[i][j - 1] != 0)
				{
					printf("�����ײ\t%d\n", __LINE__);
					newmap[0][0] = -1;
					return newmap;
				}
			}
		}

	}
	else if (mode == "RIGHT")
	{
		for (int i = 19; i >= 0; i--)
		{
			for (int j = 9; j >= 0; j--)//������ɨ��
			{
				if (j == 9 && newmap[i][j] > 14)
				{
					printf("�Ҳ�߽���ײ\t%d\n", __LINE__);
					newmap[0][0] = -1;
					return newmap;
				}
				if (j < 10 && j >= 0 && newmap[i][j] > 14 && newmap[i][j + 1] == 0)//���ڷ������Ƶ��жϣ�����else���������з���
				{
					newmap[i][j + 1] = newmap[i][j];
					newmap[i][j] = 0;
				}
				else if (j < 10 && j >= 0 && newmap[i][j] > 14 && newmap[i][j + 1] != 0)
				{
					printf("�Ҳ���ײ\t%d\n", __LINE__);
					newmap[0][0] = -1;
					return newmap;
				}
			}
		}

	}
	else if (mode == "xiajiang")//����һ����ά����arry[4][2]4ֵ���������4������ͬʱ�泯���棬2�Ƿ����״̬��-1��1.-1�Ǳ�ʾδ���÷��飬1�������ñ��ж�ά����
	{
		int x = 0, arry_index = 0;//arry_index������һ��ʹ�õ���arryһ���±�
		int arry[4][3] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, };//�涨0Ϊ�Ƿ����ã�1Ϊ���ȣ�2Ϊ�߶�.ע��00Ϊ���Ͻ�����
		for (int j = 0; j < 10; j++)//��¼4��������Ͷ˸߶�
		{
			for (int i = 19; i > -1; i--)
			{
				if (newmap[i][j] > 14)
				{
					arry[arry_index][0] = 1, arry[arry_index][1] = j, arry[arry_index][2] = i;
					arry_index++;//ָ����һ����ʹ�õ�
					break;
				}
				//for (size_t m = 0; m < 4; m++)
				//{
				//	for (int l = 0; l < 4; l++)
				//	{
				//		if (arry[l][1] == j)//�����Ѿ�����¼��
				//		{
				//			ifline = 1;
				//		}
				//	}
				//	if (ifline == 0 && newmap[i][j] > 14)
				//	{
				//		arry[x][0] = 1;
				//		arry[x][1] = j;
				//		arry[x][2] = i;
				//		x++;
				//	}
				//	ifline = 0;//����ifline
				//}
			}//arry¼�����,��ʼѰ������ľ���ֵ
			if (arry_index == 4) break;
		}printf("arry���\t%d\n", __LINE__);
		int xia[4] = { -1,-1,-1,-1 };
		for (int i = 0; i < arry_index; i++)
		{
			for (int p = arry[i][2]; p < 20; p++)//�Ӽ�¼�������濪ʼ������
			{
				if (p == 19)
				{
					printf("%d�½�ͼ�����ڵײ�", __LINE__);
					return newmap;
				}
				if (newmap[p][arry[i][1]] < 15)
				{
					xia[i] = p - arry[i][2] - 1;//������Ը߶�-1Ϊ��Ҫ�ƶ��Ĵ���
					break;
				}
				else
				{
					xia[i] = 19 - arry[i][2];//������Ҫ�ƶ��Ĵ���
					break;
				}
			}
		}//xia���
		printf("xia���xia[0]Ϊ%d\t��%d��\n", xia[0], __LINE__);
		int min = xia[0];//��¼��С�ƶ�����
		for (int i = 1; i < 4; i++)
		{
			if (xia[i] == 0)
			{
				printf("minΪnull��%d�����(��Ϊ�������ϰ���)\n", __LINE__);
				return newmap;
			}  //�������Ҫ�ƶ���ֱ�ӷ���

			if (xia[i] != -1 && xia[i] < min)   min = xia[i];
		}
		printf("minΪ%d ��%d�����\n", min, __LINE__);
		int** newmap1 = NULL;
		
  		for (size_t i = 0; i < min; i++)
		{
			newmap = move_g("DOWN", map);
			if (newmap[0][0] == -1)  return newmap;

			for (size_t i = 0; i < 20; i++)
			{
				for (size_t j = 0; j < 10; j++)
				{
					map[i][j] = newmap[i][j];
				}
			}
			/*else
			{
				for (size_t p = 0; p < 20; p++)
				{
					for (int q = 0; q < 10; q++)
					{
						newmap[p][q] = newmap1[p][q];
					}
				}
			}*/
			printf("�½�����ִ�е�%d��\n", i);
		}
		printf("�½�����ִ�����");

		/*for (size_t i = 0; i < 20; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				newmap[i][j] = newmap1[i][j];
			}
			free(newmap1[i]);
		}free(newmap1);*/

		/*gudingmap(map);*/
	}
	return newmap;
}
//��dest_array�����ݸ��Ƹ�src_array��rowָ�߶ȣ�colָ���
void copy_array(int** src_array, int(*dest_array)[10], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		memcpy((void*)src_array[i], (void*)dest_array[i], sizeof(int) * col);
	}
}

//�̶�map�����п��ƶ��ķ���
void gudingmap(int(*map)[10])
{
	for (size_t i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] > 14)
			{
				map[i][j] = (map[i][j] / 15);
			}
		}
	}
	if_del(map);//Ѱ���Ƿ��п�ɾ����
	if_next = 0;//���õ�ͼ״̬���ٷ���һ�����ƶ�����   putmatrix����
}



void array_copyint(int dest[], int src[], int len) {
	for (int i = 0; i < len; i++) {
		dest[i] = src[i];
	}
}

//��if_nextΪ0ʱ���룬Ŀ�ĸ�map��һ������ķ���
void putmatrix(int(*map)[LENGTH])
{//matrix
	int rand = g_random7(), end = 0;//endΪ0��ʾ����ײ��Ϊ1����Ϸ�����ǵ÷���ǰ�ж�ֵ
	switch (rand)
	{
	case 1:for (size_t i = 0; i < 4; i++)
	{
		if (map[0][i + 4] == 0) {}
		else
		{
			end = 1;
		}
	}
		  if (end)//1==end
		  {

		  }
		  else//put__map
		  {
			  if_next = 1;
			  for (int j = 0; j < 4; j++)
			  {
				  map[0][j + 4] = matrix.zhixian[j] * 15;
			  }
		  }
		  break;
	case 2:

		if (map[0][4] == 0 && map[1][4] == 0 && map[1][5] == 0 && map[1][6] == 0) {}
		else
		{
			end = 1;
		}

		if (end)//1==end
		{

		}
		else//put__map
		{
			if_next = 1;
			map[0][4] = matrix.zuol[0][0] * 15;
			map[1][4] = matrix.zuol[1][0] * 15;
			map[1][5] = matrix.zuol[1][1] * 15;
			map[1][6] = matrix.zuol[1][2] * 15;
		}
		break;
	case 3:

		if (map[1][4] == 0 && map[1][5] == 0 && map[1][6] == 0 && map[0][6] == 0) {}
		else
		{
			end = 1;
		}

		if (end)//1==end
		{

		}
		else//put__map
		{
			if_next = 1;
			map[1][4] = matrix.youl[1][0] * 15;
			map[1][5] = matrix.youl[1][1] * 15;
			map[1][6] = matrix.youl[1][2] * 15;
			map[0][6] = matrix.youl[0][2] * 15;
		}
		break;
	case 4:

		if (map[0][4] == 0 && map[0][5] == 0 && map[1][4] == 0 && map[1][5] == 0) {}
		else
		{
			end = 1;
		}

		if (end)//1==end
		{

		}
		else//put__map
		{
			if_next = 1;
			map[0][4] = matrix.fang[0][0] * 15;
			map[0][5] = matrix.fang[0][1] * 15;
			map[1][4] = matrix.fang[1][0] * 15;
			map[1][5] = matrix.fang[1][1] * 15;
		}
		break;
	case 5:
		if (map[1][4] == 0 && map[1][5] == 0 && map[0][5] == 0 && map[0][6] == 0) {}
		else
		{
			end = 1;
		}

		if (end)//1==end
		{

		}
		else//put__map
		{
			if_next = 1;
			map[1][4] = matrix.zxguai[1][0] * 15;
			map[1][5] = matrix.zxguai[1][1] * 15;
			map[0][5] = matrix.zxguai[0][1] * 15;
			map[0][6] = matrix.zxguai[0][2] * 15;
		}
		break;
	case 6:
		if (map[0][4] == 0 && map[0][5] == 0 && map[1][5] == 0 && map[1][6] == 0) {}
		else
		{
			end = 1;
		}

		if (end)//1==end
		{

		}
		else//put__map
		{
			if_next = 1;
			map[0][4] = matrix.yxguai[0][0] * 15;
			map[0][5] = matrix.yxguai[0][1] * 15;
			map[1][5] = matrix.yxguai[1][1] * 15;
			map[1][6] = matrix.yxguai[1][2] * 15;
		}
		break;
	case 7:

		if (map[1][4] == 0 && map[0][5] == 0 && map[1][5] == 0 && map[1][6] == 0) {}
		else
		{
			end = 1;
		}

		if (end)//1==end
		{

		}
		else//put__map
		{
			if_next = 1;
			map[1][4] = matrix.daot[1][0] * 15;
			map[0][5] = matrix.daot[0][1] * 15;
			map[1][5] = matrix.daot[1][1] * 15;
			map[1][6] = matrix.daot[1][2] * 15;
		}
		break;
	}
}