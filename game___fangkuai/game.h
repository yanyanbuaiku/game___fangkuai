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
//
//判断方块碰撞的函数
//移动方块的函数
//计算消除的函数
//响应键盘函数
//计算移动函数
//自动下降函数
//将移动方块固定的函数

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

int g_random7_a = 0;//g_random7函数的旧返回值

//绘制主界面
void menu(int(*map)[10])
{
	setfillcolor(RGB(40, 44, 52));
	fillrectangle(300, 0, 475, 680);
	/*fillrectangle(0, 0, 30, 30);方块代码*/
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			getcolor(map[i][j]);
			fillrectangle(30 * j, 30 * i, 30 * (j + 1), 30 * (i + 1));
		}
	}			//绘制地图
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
				int decide_color = 0;//除于11是为了判断原颜色
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



//定义为new[x][y]    x为高h，y为长l，中心在22,全部写入55坐标系中.8元素表示核心的位置,9元素表示这一块的颜色
//同时计算其顺时针旋转一次的坐标
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
	int hexin[2] = { 0 };//记录oldmap里面的核心坐标
	hexin[0] = oldmap[oldmap[8]];//x
	hexin[1] = oldmap[oldmap[8] + 1];//y,计算相对坐标，录入到newmap里面
	for (int i = 0; i < 8; i = i + 2)//循环4次
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




//xy为需要被计算的坐标，Be_counted是偏移的参照点(通常为中心坐标)，返回值是一个包含水平差和垂直差的指针，以左上角为小，右下角为大
int* xyoffset(int x, int y, int Be_countedx, int  Be_countedy)
{
	int* re = (int*)calloc(2, sizeof(int));
	re[1] = x - Be_countedx;//垂直
	re[0] = y - Be_countedy;//水平
	return re;
}


//将55图像的地址转移到大坐标中，注意排除可移动方块自身再绘制大坐标，后放入，再进行碰撞判断
//返回值应先进行-1判断，确定是否可以转移，如果为-1则保持原状
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
			if (oldmap[i][j] < 15)//表明他是以固定方块
			{
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

//记录时间，过1s以上下移一格
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
