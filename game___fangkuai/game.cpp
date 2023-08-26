#define LENGTH 10
#define HIGH 20
#define _CRT_SECURE_NO_WARNINGS 1

#include<easyx.h>
#include<stdio.h>
#include"game.h"




int main()
{
	
	int map_square[HIGH][LENGTH] = {  };//第一个数字为行数，第二个为列数，起点为左上角0，0
	initgraph(475, 600, EX_SHOWCONSOLE);
	while (true)
	{
		FlushBatchDraw();
		menu(map_square);
		
	}
	



	closegraph();
	return 0;
}