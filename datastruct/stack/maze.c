/* 本程序的目的是应用栈来做迷宫的求解，方法采用的是回溯法 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_SIZE 15

int maze_map[MAZE_SIZE][MAZE_SIZE] = {0};

void create_maze_map ()
{
	srand (time(NULL));
	int map_block_num = ( (MAZE_SIZE-1)*(MAZE_SIZE-1)*30 ) / 100; // map中除了墙之外的砖块数其数值取总数的40%
	memset (maze_map, 0, sizeof (maze_map));
	int i,j;
	int x, y;
	// 生成墙
	for (i = 0; i < MAZE_SIZE; ++i)
	{
		for (j = 0; j < MAZE_SIZE; ++j)
		{
			if ( (i == 0) || (i == MAZE_SIZE - 1) || (j == 0) || (j == MAZE_SIZE-1) )
				maze_map[i][j] = 1;
			else
				maze_map[i][j] = 0;
		}
	}

	// 生产墙内的砖块
	for (i = 0; i < map_block_num; ++i)
	{
		x = rand () % (MAZE_SIZE - 2) + 1;
		y = rand () % (MAZE_SIZE - 2) + 1;
		maze_map[x][y] = 1;
	}

	// 出入口两个位置不能为砖块
	maze_map[1][1] = 0;
	maze_map[MAZE_SIZE-2][MAZE_SIZE-2] = 0;
}

void print_map ()
{
	int i,j;
	// 打印列标
	printf ("   ");
	for (i = 1; i <= MAZE_SIZE; ++i)
		printf ("%d ", i%10);
	printf ("\n");
	for (i = 0; i < MAZE_SIZE; ++i)
	{
		printf ("%2d ", i+1); // 打印行标
		for (j = 0; j < MAZE_SIZE; ++j)
		{
			if (maze_map[i][j] == 1)
				printf ("# ");
			else
				printf (". ");
		}
		printf ("\n");
	}
}




int main (void)
{
	create_maze_map ();
	print_map ();
	return 0;
}
