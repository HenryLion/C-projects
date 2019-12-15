/* 本程序的目的是应用栈来做迷宫的求解，方法采用的是回溯法 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


#define MAZE_SIZE 50 /* 迷宫地图的尺寸 */

#define MAZE_BEG_I 1 /* 起始x坐标 */
#define MAZE_BEG_J 1 /* 起始y坐标 */

#define MAZE_END_I (MAZE_SIZE-2) /* 终点x坐标 */
#define MAZE_END_J (MAZE_SIZE-2) /* 终点y坐标 */

#define PATH_NODE_NUM 1000  /* 存储探索路径的数组大小 */

/* 节点之间的方位关系定义 */
typedef enum dir
{
	NONE,
	EAST,
	SOUTH,
	WEST,
	NORTH,
	INVALID,
} Dir;

typedef struct path_node
{
	int x;
	int y;
} Path_node;

typedef struct path_info
{
	int num;
	Path_node paths[PATH_NODE_NUM];
} Path_info;

/* 探索到某个节点需要保存的节点信息 */
typedef struct maze_node 
{
	int i; // 迷宫行坐标
	int j; // 迷宫列坐标
	Dir to_dir; // 此节点上一次的试探方向,当后续回溯到此节点时，就只需要往to_dir的下一个方向试探
	Dir from_dir; // 此节点上一个节点的方位，回溯时上一个节点的方位也按照不通来处理
} Maze_node;


/* global variable defination */
int maze_map[MAZE_SIZE][MAZE_SIZE] = {0};
Path_info paths_info = {0};

/****************************************************
 * function: 建立迷宫地图
 * author: herbert
 * date: 2019-12-13
 ****************************************************/
void create_maze_map ()
{
	srand (time(NULL));
	int map_block_num = ( (MAZE_SIZE-1)*(MAZE_SIZE-1)*30 ) / 100; // map中除了墙之外的砖块数其数值取总数的30%
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
	maze_map[MAZE_END_I][MAZE_END_J] = 0;
}

/****************************************************
 * function: 打印出迷宫地图
 * author: herbert
 * date: 2019-12-13
 ****************************************************/
void print_map ()
{
	int i,j;
	int num = 0;
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
			else if (maze_map[i][j] == 0)
				printf (". ");
			else
			{
				++num;
				printf ("@ ");
			}
		}
		printf ("\n");
	}
	printf ("stack is: %d\n", num);
}

/****************************************************
 * function: 查看参数代表的坐标是否在试探过的路径上
 * author: herbert
 * date: 2019-12-14
 * common: 
 ****************************************************/
BOOL is_node_in_paths (int i, int j)
{
	int idx = 0;
	for (idx = 0; idx < paths_info.num; ++idx)
	{
		if ( (i == paths_info.paths[idx].x) && (j == paths_info.paths[idx].y) )
			return TRUE;
	}
	return FALSE;
}


/****************************************************
 * function:获得当前节点的下一个试探节点方向 
 * author: herbert
 * date: 2019-12-13
 * common: 根据当前节点的坐标获取下一个试探节点的方向,按照东南西北的方向探测
 ****************************************************/
Dir get_probe_dir_for_this_node (Maze_node node)
{
	int i = node.i;
	int j = node.j;

	if (node.to_dir == NONE)
		goto NONE;
	else if (node.to_dir == EAST)
		goto EAST;
	else if (node.to_dir == SOUTH)
		goto SOUTH;
	else if (node.to_dir == WEST)
		goto WEST;
	else
		goto OVER;

NONE: // 表示此节点还未探测过其他方向
	if ( (maze_map[i][j+1] == 0) && !is_node_in_paths (i, j+1) && (node.from_dir != EAST) )
	{
		// 如果此节点东边的节点为0且其东边的节点不在栈中的路径上且此节点不是从东边过来的则返回EAST
		return  EAST;
	}
EAST: // 表示此节点上次探测的是EAST方向
	if ( (maze_map[i+1][j] == 0) && !is_node_in_paths (i+1, j) && (node.from_dir != SOUTH) )
	{
		return SOUTH;
	}
SOUTH: // 表示此节点上次探测的是SOUTH方向
	if ( (maze_map[i][j-1] == 0) && !is_node_in_paths (i, j-1) && (node.from_dir != WEST) )
	{
		return  WEST;
	}
WEST: // 表示此节点上次探测的是WEST方向
	if ( (maze_map[i-1][j] == 0) && !is_node_in_paths (i-1, j) && (node.from_dir != NORTH) )
	{
		return NORTH;
	}
OVER:
	return INVALID;
}

/****************************************************
 * function: 解迷宫
 * author: herbert
 * date: 2019-12-13
 * common: 1,1坐标当作迷宫的起点，n-2,n-2坐标当作迷宫的终点
 ****************************************************/
int solve_maze ()
{
	Stack *stack = NULL;
	init_stack (&stack);
	
	int is_node_pop_from_stack = FALSE;
	Maze_node node,top_node;
	node.i = MAZE_BEG_I;
	node.j = MAZE_BEG_J;
	node.from_dir = INVALID;
	node.to_dir = NONE;
	do 
	{
		node.to_dir = get_probe_dir_for_this_node (node);

		if (!is_full (stack))
		{
			if (!is_node_pop_from_stack)
			{
				// printf ("push1: i = %d, j = %d, from_dir = %d, to_dir = %d\n", node.i, node.j, node.from_dir, node.to_dir);
				push (stack, &node, sizeof (Maze_node));
				// 往栈中push时需要把push的坐标记录下来,后续用来判断试探的节点是否在push的路径上
				paths_info.paths[paths_info.num].x = node.i;
				paths_info.paths[paths_info.num].y = node.j;
				paths_info.num++;
			}
			else
			{
				// 需要更新栈顶元素的to_dir
				pop (stack, NULL, sizeof (Maze_node));

				// printf ("push2: i = %d, j = %d, from_dir = %d, to_dir = %d\n", node.i, node.j, node.from_dir, node.to_dir);
				push (stack, &node, sizeof (Maze_node));
			}
		}
		else
		{
			printf ("error: stack full, top = %d\n", stack->top);
			return -1;
		}
		if (INVALID != node.to_dir) //如果此节点有通路
		{
			// 根据to_dir得出下一个节点的信息
			if (node.to_dir == EAST)
			{
				node.j += 1;
				node.from_dir = WEST;
			}
			else if (node.to_dir == SOUTH)
			{
				node.i += 1;
				node.from_dir = NORTH;
			}
			else if (node.to_dir == WEST)
			{
				node.j -= 1;
				node.from_dir = EAST;
			}
			else if (node.to_dir == NORTH)
			{
				node.i -= 1;
				node.from_dir = SOUTH;
			}

			// 一个新节点应当将它的to_dir置为NONE
			node.to_dir = NONE;
			is_node_pop_from_stack = FALSE;

			// 找到出口
			if ( node.i == (MAZE_END_I) && node.j ==  (MAZE_END_J) )
			{
				// 将栈中的所有元素对应的map中对应位设置为2
				while (!is_empty (stack))
				{
					pop (stack, &top_node, sizeof (Maze_node));
					maze_map[top_node.i][top_node.j] = 2;
				}
				clear_stack (stack);
				return 0;
			}
		}
		else // 如果此节点是死胡同
		{
			if (!is_empty (stack))
			{
				// 死胡同但栈不为空,则弹出栈顶元素继续计算
				pop (stack, &node, sizeof (Maze_node));
				if (!is_empty (stack))
				{
					get_top (stack, &node, sizeof (Maze_node));
					is_node_pop_from_stack = TRUE;
				}
				else
				{
					clear_stack (stack);
					return -1;
				}
			}
			else
			{
				// 死胡同且栈空说明没找到，清空栈并返回.
				clear_stack (stack);
				return -1;
			}
		}
	} while (!is_empty (stack));
}

int main (void)
{
	create_maze_map ();
	print_map ();
	solve_maze ();
	print_map ();
	return 0;
}
