#define LENGTH 10
#define HIGH 20
#define _CRT_SECURE_NO_WARNINGS 1

#include<easyx.h>
#include<stdio.h>
#include<game.h>


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


int main()
{
	
	int map_square[HIGH][LENGTH] = { 1,0,3,5 };//��һ������Ϊ�������ڶ���Ϊ���������Ϊ���Ͻ�0��0
	initgraph(475, 600, EX_SHOWCONSOLE);
	while (true)
	{
		FlushBatchDraw();
		menu(map_square);
		
	}
	






	
	closegraph();
	return 0;
}