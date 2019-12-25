#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 10
#define COL 6

/* 本程序实现的是稀疏数组的有效表示方法 */
/* 稀疏矩阵需要考虑到存储空间的节省和计算时间的节约 */

/**********************************************
* function: 实现一个普通的矩阵转置运算
* author: Herbert
* date: 2019-12-25
**********************************************/
int* matrix_transpose (int *matrix[], int row, int col)
{
	int i,j;
	int *p = (int*)malloc (row * col * sizeof(int));
	if (NULL == p)
		return NULL;
	
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			p[j*row+i]  = matrix[i][j];
		}
	}

	return p;
}

/**********************************************
* function: 实现一个普通的矩阵转置运算
* author: Herbert
* date: 2019-12-25
**********************************************/
void print_two_dimensional_array (int (*arr)[COL], int row, int col)
{
	int i,j;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col;++j)
		{
			printf ("%d ", arr[i][j]);
		}
		printf ("\n");
	}
	return ;
}

int main (void)
{
	srand (time(NULL));

	int arr[ROW][COL] = {0};

	int i,j;
	for (i = 0; i < ROW; ++i)
		for (j = 0; j < COL; ++j)
		{
			arr[i][j] = rand () % 100;
		}
	
	print_two_dimensional_array (arr, ROW, COL);

	return 0;
}
