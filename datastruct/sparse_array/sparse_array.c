#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROW 6
#define COL 10
#define MAX_NONZERO_NODE_NUM 200  // 按照稀疏矩阵的定义,若有200个非零元则支持的最大总元素个数为200/(5/100) = 4000
#define MAX_NODE_VALUE 65535
/* 本程序实现的是稀疏数组的有效表示方法 */
/* 稀疏矩阵需要考虑到存储空间的节省和计算时间的节约 */

typedef struct matrix_node
{
	int r_idx; // 稀疏矩阵非零元的行标
	int c_idx; // 稀疏矩阵非零元的列标
	int value; // 稀疏矩阵非零元的值
} matrix_node_t;

typedef struct sparse_matrix
{
	int row;  // 稀疏矩阵行数
	int col;  // 稀疏矩阵列数
	int node_num; // 稀疏矩阵非零元个数
	matrix_node_t nodes[MAX_NONZERO_NODE_NUM]; // 存储非零元节点
} Sparse_matrix;


/**********************************************
* function: 生成一个稀疏矩阵
* author: Herbert
* date: 2019-12-26
**********************************************/
Sparse_matrix* create_sparse_matrix (Sparse_matrix **s_matrix)
{
	if (NULL == s_matrix)
		return NULL;
	*s_matrix = (Sparse_matrix*)malloc (sizeof (Sparse_matrix));
	if (*s_matrix == NULL)
		return NULL;

	memset (*s_matrix, 0, sizeof (Sparse_matrix));

	return *s_matrix;
}


/**********************************************
* function: 判断一个坐标在矩阵中是否已经存在
* author: Herbert
* date: 2019-12-26
**********************************************/
int is_matrix_node_exist (Sparse_matrix *s_matrix, int r_idx, int c_idx)
{
	if (NULL == s_matrix)
		return 0;
	int i;
	for (i = 0; i < s_matrix->node_num; ++i)
	{
		if ( (s_matrix->nodes[i].r_idx == r_idx) && (s_matrix->nodes[i].c_idx == c_idx) )
			return 1;
	}
	return 0;
}

/**********************************************
* function: 打印一个稀疏矩阵
* author: Herbert
* date: 2019-12-25
**********************************************/
void print_sparse_matrix (Sparse_matrix *s_matrix)
{
	if (NULL == s_matrix)
		return;
	int i;
	printf ("\nmatrix row = %d, col = %d, node_num = %d:\n", s_matrix->row, s_matrix->col, s_matrix->node_num);
	for (i = 0; i < s_matrix->node_num; ++i)
	{
		printf ("(%d,%d) = %d  ", s_matrix->nodes[i].r_idx, s_matrix->nodes[i].c_idx,s_matrix->nodes[i].value); 
		if ( (i+1) % 6 == 0)
			printf ("\n");
	}
	printf ("\n");
	return;
}

/**********************************************
* function: 实现一个普通的矩阵转置运算
* author: Herbert
* date: 2019-12-25
**********************************************/
int* matrix_transpose (int *matrix, int row, int col)
{
	int i,j;
	int *p = (int*)malloc (row * col * sizeof(int));
	if (NULL == p)
		return NULL;
	
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			p[j*row+i]  = matrix[i*col+j];
		}
	}

	return p;
}

/**********************************************
* function: 打印二维数组 用一维数组的形式表示二维数组，其实这也是二维数组的真实表示法
* author: Herbert
* date: 2019-12-25
**********************************************/
void print_two_dimensional_array (int *arr, int row, int col)
{
	int i;
	for (i = 0; i < row * col; ++i)
	{
		printf ("%2d ", arr[i]);
		if ((i+1) % col == 0)
			printf ("\n");
	}
	return ;
}

/**********************************************
* function: 初始化一个普通的二维数组(矩阵)
* author: Herbert
* date: 2019-12-26
**********************************************/
void init_two_dimensional_array (int *arr)
{
	if (NULL == arr)
		return ;
	int non_zero_num = (ROW*COL) / 20;
	int i;
	for (i = 0; i < non_zero_num; ++i)
	{
		arr[rand()%(ROW*COL)] = rand () % 100;
	}
	return ;
}

/**********************************************
* function: 从普通的二维数据表示得到稀疏矩阵的表示
* author: Herbert
* date: 2019-12-26
**********************************************/
void get_sparse_matrix_from_normal_matrix (int *arr, int row, int col, Sparse_matrix *s_matrix)
{
	if (NULL == arr || NULL == s_matrix)
		return;
	int i;

	s_matrix->row = row;
	s_matrix->col = col;
	int node_num = 0;
	for (i = 0; i < row * col; ++i)
	{
		if (arr[i] != 0)
		{
			s_matrix->nodes[node_num].r_idx = i / col;
			s_matrix->nodes[node_num].c_idx = i % col;
			s_matrix->nodes[node_num].value = arr[i];
			++node_num;
		}
	}
	s_matrix->node_num = node_num;
	return;
}



int main (void)
{
	srand (time(NULL));

	int arr[ROW*COL] = {0};

	init_two_dimensional_array (arr);

	printf ("\nsrc matrix is: \n");	
	print_two_dimensional_array (arr, ROW, COL);
	int *transpose_arr = matrix_transpose (arr, ROW, COL);
	printf ("\ntranspose matrix is:\n");
	print_two_dimensional_array (transpose_arr, COL, ROW);

	Sparse_matrix *s_matrix = NULL;
	create_sparse_matrix (&s_matrix);
	get_sparse_matrix_from_normal_matrix (arr, ROW, COL, s_matrix);
	print_sparse_matrix (s_matrix);

	return 0;
}
