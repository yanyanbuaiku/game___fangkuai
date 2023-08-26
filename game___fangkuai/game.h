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


//记录未完成的函数
//判断方块碰撞的函数
//计算消除的函数,注：应在固定后被调用
//计算移动函数



#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<crtdbg.h>


//左上角为00，先向右边水平递增再回归左上层,[x][y]中x是层高，y是层宽
struct Square_matrix
{								              //偶数为核心
	int zhixian[4] = { 1,2,1,1 },             //直线第二个为核心[1]
		zuol[2][3] = { 3,0,0,4,3,3 },
		youl[2][3] = { 0,0,5,5,5,6 },         //此二为L型方块，核心在左下和右下[1][0]以及[1][2]
		fang[2][2] = { 7,7,7,8 },             //此为方块，核心在右下角[1][1]
		zxguai[2][3] = { 0,9,9,9,10,0 },
		yxguai[2][3] = { 11,11,0,0,12,11 },   //此二为半s型，核心都在[1][1]
		daot[2][3] = { 0,13,0,13,14,13 };     //此为倒T，核心在[1][1]
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
int g_random7_a = 0;//g_random7函数的旧返回值
static time_t first, end;//atuo_move_down函数计算1s的参数
static time_t then, next;//menu计算操作延迟的
static int if_next = 0;//记录是否map有可移动，0为无可移动，1为有可移动
static int atuo_move_down_n = 0, FPS = 0;


//绘制主界面
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
	/*fillrectangle(0, 0, 30, 30);方块代码*/
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
			int map_h = 0, map_l = 0, whether__up = 0, yes__up = 1;//map_h map_l分别记录中心点高和长左上角为中心 ,whether__up为0时证明未找到可旋转坐标，为1表示找到,yes_up为0表示与边缘或者方块有碰撞无法旋转
			for (int i = 0; i < 20; i++)//遍历地图寻找中心点
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
				copy_array(newmap, map, 20, 10);//将map复制到newmap防止错误更改原地图
				for (size_t i = 0; i < HIGH; i++)
				{
					for (int j = 0; j < LENGTH; j++)
					{
						if (newmap[i][j] > 14)
						{
							newmap[i][j] = 0;//将newmap中的可移动方块剔除
						}
					}
				}
				reg_scan_map = g_scan_map(map);
				int setlinshimap[10] = { 0 };
				array_copyint(setlinshimap, reg_scan_map, 10);
				remap = sort_55(setlinshimap);
				/*map[map_h][map_l] = remap[2][2];*/
				int* xy = (int*)calloc(2, sizeof(int));//xy是接受xyoffset返回值的参数，0为水平差，1为竖直差
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (remap[i][j] > 0)
						{
							xy = xyoffset(i, j, 2, 2);
							if (map_h + xy[1] < HIGH && map_l + xy[0] < LENGTH && map_h + xy[1] >= 0 && map_l + xy[0] >= 0)//旋转后不越界
							{
								printf("%d旋转后不越边界\n", __LINE__);
								if (newmap[map_h + xy[1]][map_l + xy[0]] == 0)//newmap此处为空
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
								yes__up = 0;//不可以旋转
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
	//绘制地图
	atuo_move_down(map);
	next = clock();
	FPS++;
}


//获取1到7的随机值，返回值为int
int g_random7()//待改写————————————————————————改成7个为一组的随机顺序
{
	int a;
	srand((unsigned)time(NULL));
	a = rand();
	return (a % 7 + 1);
}



//扫描当前地图中应移动的方块   0到7为xy坐标x对应h,y对应l，8元素表示核心的位置,9元素表示这一块的颜色
int* g_scan_map(int(*map)[LENGTH])

{

	//返回的总结地图，包含4个xy坐标，1个核心的位置（相对于4个xy），1个当前颜色
	int* remap = (int*)calloc(10, sizeof(int));
	int remap_int = 0;//remap的下标，方便写入
	int recolor = 0;//返回的颜色代码
	for (int i = 0; i < HIGH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			if (map[i][j] > 14)
			{
				int decide_color = 0;//除于15是为了判断原颜色
				decide_color = map[i][j] / 15;
				if ((decide_color == 1 || decide_color == 2))//判断当前颜色并写入recolor
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
					remap[8] = remap_int / 2;//有0123
				}
				remap_int = remap_int + 2;
			}
		}
	}
	remap[9] = recolor;//当前色块颜色
	return remap;
}



//定义为new[x][y]    x为高h，y为长l，中心在22,全部写入55坐标系中.8元素表示核心的位置(从0开始算起),9元素表示这一块的颜色
//同时计算其顺时针旋转一次的坐标
int** sort_55(int* oldmap)
{
	int** newmap = NULL;
	newmap = (int**)calloc(5, sizeof(int*));
	for (int i = 0; i < 5; i++)
	{
		newmap[i] = (int*)calloc(5, sizeof(int));
		if (!newmap[i]) exit(-1);
	}
	newmap[2][2] = oldmap[9] + 1;//记录颜色加一，偶数为核心
	int hexin[2] = { 0 };//记录oldmap里面的核心坐标
	hexin[0] = oldmap[oldmap[8] * 2];//x
	hexin[1] = oldmap[oldmap[8] * 2 + 1];//y,计算相对坐标，录入到newmap里面
	int* xy_re = (int*)calloc(2, sizeof(int));
	for (int i = 0; i < 8; i = i + 2)//循环4次
	{

		xy_re = xyoffset(oldmap[i], oldmap[i + 1], hexin[0], hexin[1]);
		newmap[2 + xy_re[0]][2 - xy_re[1]] = oldmap[9];

	}
	free(xy_re);
	if (newmap[2][2] % 2 != 0) newmap[2][2]++;
	return newmap;
}


//xy为需要被计算的坐标，Be_counted是偏移的参照点(通常为中心坐标)，返回值是一个包含水平差（0元素）和垂直差（1元素）的指针，以左上角为负，右下角为正
int* xyoffset(int x, int y, int Be_countedx, int  Be_countedy)
{
	int* re = (int*)calloc(2, sizeof(int));
	if (re)
	{
		re[1] = x - Be_countedx;//垂直
		re[0] = y - Be_countedy;//水平
	}
	else
	{
		printf("%d", __LINE__);
		exit(-1);
	}
	return re;
}


//将55图像的地址转移到大坐标中，注意排除可移动方块自身再绘制大坐标，后放入，再进行碰撞判断
//返回值应先进行-1判断，确定是否可以e转移，如果为-1则保持原状
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
			if (oldmap[i][j] < 15)//表明他是以固定方块
			{
				if (newmap[i][j])
					newmap[i][j] = oldmap[i][j];
			}
		}
	}								//筛出的newmap是除开可移动的方块的地图
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			if (newmap[i][j + 3] == 0)//防止碰撞
			{
				newmap[i][j + 3] = map55[i][j];//把所有55坐标中的元素转移到newmap中
			}
			else
			{
				return (int**)-1;//如果当前坐标不为0，直接返回-1
			}
		}
	}
	return newmap;

}

//通过判断值来设置颜色
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
	int del = -1;//-1为不删除此行，即此行还有空缺或不全是固定方块
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] < 15 && map[i][j] != 0)//排除可移动方块和空白格
			{
				del = i;
			}
			else {
				del = -1;
			}
			if (del == -1)//如果有本行一个不符合则直接扫描下一行
			{
				break;
			}
		}
		if (del != -1)//del为0—20任何数时开始删除第j行
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
				if (k == 1)//第一行被移动到第二行之后
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

//记录时间，过1s以上下移一格
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

//返回值为-1时应将可移动的方块除于15变为固定态
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
	copy_array(newmap, map, 20, 10);//将map复制到newmap防止错误更改原地图
	if (mode == "DOWN")
	{
		for (int i = 19; i >= 0; i--)
		{
			for (int j = 9; j >= 0; j--)
			{
				if (i == 19 && newmap[i][j] > 14)//对于底部的碰撞
				{
					printf("底部边界碰撞\t%d\n", __LINE__);
					gudingmap(map);
					newmap[0][0] = -1;
					return newmap;
				}
				if (i < 19 && newmap[i][j]>14 && newmap[i + 1][j] == 0)//对于方块下移的判断，进入else则是下面有方块
				{
					newmap[i + 1][j] = newmap[i][j];
					newmap[i][j] = 0;
				}
				else if (i < 19 && newmap[i][j]>14 && newmap[i + 1][j] != 0)
				{
					printf("底部碰撞\t%d\n", __LINE__);
					gudingmap(map);
					newmap[0][0] = -1;
					return newmap;
				}
			}
		}
	}
	else if (mode == "LEFT")//横向扫描应从左向右扫描
	{
		for (int i = 19; i >= 0; i--)
		{
			for (int j = 0; j < 10; j++)
			{
				if (j == 0 && newmap[i][j] > 14)
				{
					printf("左侧边界碰撞\t%d\n", __LINE__);
					newmap[0][0] = -1;
					return newmap;
				}
				if (j < 10 && j >= 0 && newmap[i][j] > 14 && newmap[i][j - 1] == 0)//对于方块左移的判断，进入else则是左面有方块
				{
					newmap[i][j - 1] = newmap[i][j];
					newmap[i][j] = 0;
				}
				else if (j < 10 && j >= 0 && newmap[i][j] > 14 && newmap[i][j - 1] != 0)
				{
					printf("左侧碰撞\t%d\n", __LINE__);
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
			for (int j = 9; j >= 0; j--)//右往左扫描
			{
				if (j == 9 && newmap[i][j] > 14)
				{
					printf("右侧边界碰撞\t%d\n", __LINE__);
					newmap[0][0] = -1;
					return newmap;
				}
				if (j < 10 && j >= 0 && newmap[i][j] > 14 && newmap[i][j + 1] == 0)//对于方块右移的判断，进入else则是右面有方块
				{
					newmap[i][j + 1] = newmap[i][j];
					newmap[i][j] = 0;
				}
				else if (j < 10 && j >= 0 && newmap[i][j] > 14 && newmap[i][j + 1] != 0)
				{
					printf("右侧碰撞\t%d\n", __LINE__);
					newmap[0][0] = -1;
					return newmap;
				}
			}
		}

	}
	else if (mode == "xiajiang")//加载一个二维数组arry[4][2]4值得是最多有4个方块同时面朝下面，2是方块的状态有-1，1.-1是表示未启用方块，1是已启用本列二维数组
	{
		int x = 0, arry_index = 0;//arry_index储存下一个使用到的arry一级下标
		int arry[4][3] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, };//规定0为是否启用，1为长度，2为高度.注：00为左上角坐标
		for (int j = 0; j < 10; j++)//记录4格宽的最靠近低端高度
		{
			for (int i = 19; i > -1; i--)
			{
				if (newmap[i][j] > 14)
				{
					arry[arry_index][0] = 1, arry[arry_index][1] = j, arry[arry_index][2] = i;
					arry_index++;//指向下一个待使用的
					break;
				}
				//for (size_t m = 0; m < 4; m++)
				//{
				//	for (int l = 0; l < 4; l++)
				//	{
				//		if (arry[l][1] == j)//本列已经被记录过
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
				//	ifline = 0;//重置ifline
				//}
			}//arry录入完毕,开始寻找最近的距离值
			if (arry_index == 4) break;
		}printf("arry完毕\t%d\n", __LINE__);
		int xia[4] = { -1,-1,-1,-1 };
		for (int i = 0; i < arry_index; i++)
		{
			for (int p = arry[i][2]; p < 20; p++)//从记录的最下面开始向下找
			{
				if (p == 19)
				{
					printf("%d下降图形已在底层", __LINE__);
					return newmap;
				}
				if (newmap[p][arry[i][1]] < 15)
				{
					xia[i] = p - arry[i][2] - 1;//计算相对高度-1为需要移动的次数
					break;
				}
				else
				{
					xia[i] = 19 - arry[i][2];//计算需要移动的次数
					break;
				}
			}
		}//xia完毕
		printf("xia完毕xia[0]为%d\t在%d行\n", xia[0], __LINE__);
		int min = xia[0];//记录最小移动次数
		for (int i = 1; i < 4; i++)
		{
			if (xia[i] == 0)
			{
				printf("min为null在%d行完成(因为已贴近障碍物)\n", __LINE__);
				return newmap;
			}  //最近不需要移动则直接返回

			if (xia[i] != -1 && xia[i] < min)   min = xia[i];
		}
		printf("min为%d 在%d行完成\n", min, __LINE__);
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
			printf("下降函数执行第%d次\n", i);
		}
		printf("下降函数执行完毕");

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
//将dest_array的内容复制给src_array，row指高度，col指宽度
void copy_array(int** src_array, int(*dest_array)[10], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		memcpy((void*)src_array[i], (void*)dest_array[i], sizeof(int) * col);
	}
}

//固定map中所有可移动的方块
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
	if_del(map);//寻找是否有可删除行
	if_next = 0;//设置地图状态，再放入一个可移动方块   putmatrix函数
}



void array_copyint(int dest[], int src[], int len) {
	for (int i = 0; i < len; i++) {
		dest[i] = src[i];
	}
}

//当if_next为0时进入，目的给map加一个随机的方块
void putmatrix(int(*map)[LENGTH])
{//matrix
	int rand = g_random7(), end = 0;//end为0表示无碰撞，为1则游戏结束记得返回前判断值
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