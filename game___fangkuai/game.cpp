#define LENGTH 10
#define HIGH 20
#define _CRT_SECURE_NO_WARNINGS 1

#include<easyx.h>
#include<stdio.h>
#include<game.h>


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


int main()
{
	
	int map_square[HIGH][LENGTH] = { 1,0,3,5 };//第一个数字为行数，第二个为列数，起点为左上角0，0
	initgraph(475, 600, EX_SHOWCONSOLE);
	while (true)
	{
		FlushBatchDraw();
		menu(map_square);
		
	}
	






	
	closegraph();
	return 0;
}