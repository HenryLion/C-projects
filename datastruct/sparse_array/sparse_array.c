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
* function: 判断一个行列坐标元素在矩阵中是否已经存在
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
	int non_zero_num = (ROW*COL) / 20 + 5; 
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


/**********************************************
* function: 实现一个稀疏矩阵的转置运算
* author: Herbert
* date: 2019-12-27
**********************************************/
Sparse_matrix * sparse_matrix_transpose (Sparse_matrix * s_matrix)
{
	if (NULL == s_matrix)
		return NULL;
	Sparse_matrix *trans_matrix = (Sparse_matrix*) malloc (sizeof (Sparse_matrix));	
	if (NULL == trans_matrix)
		return NULL;
	trans_matrix->row = s_matrix->col;
	trans_matrix->col = s_matrix->row;
	trans_matrix->node_num = s_matrix->node_num;

	int i,j;
	int node_pos = 0;
	for (i = 0; i < s_matrix->node_num; ++i)
	{
		node_pos = 0;
		for (j = 0; j < s_matrix->node_num; ++j)
		{
			if (i == j)
				continue;
			if (s_matrix->nodes[i].c_idx > s_matrix->nodes[j].c_idx)
			{
				++node_pos;
			}
			else if (s_matrix->nodes[i].c_idx == s_matrix->nodes[j].c_idx)
			{
				if (s_matrix->nodes[i].r_idx > s_matrix->nodes[j].r_idx)
					++node_pos;
			}
			else
			{
				// do nothing;
			}
		}
		trans_matrix->nodes[node_pos].r_idx = s_matrix->nodes[i].c_idx;
		trans_matrix->nodes[node_pos].c_idx = s_matrix->nodes[i].r_idx;
		trans_matrix->nodes[node_pos].value = s_matrix->nodes[i].value;
	}
	return trans_matrix;
}

/**********************************************
* function: 实现一个稀疏矩阵的转置运算(优化方法)
* author: Herbert
* date: 2019-12-27 严蔚敏视频14前10分钟
**********************************************/
Sparse_matrix * optimize_sparse_matrix_transpose (Sparse_matrix *s_matrix)
{
	if (NULL == s_matrix)
		return NULL;
	Sparse_matrix *trans_matrix = (Sparse_matrix*) malloc (sizeof (Sparse_matrix));	
	if (NULL == trans_matrix)
		return NULL;
	trans_matrix->row = s_matrix->col;
	trans_matrix->col = s_matrix->row;
	trans_matrix->node_num = s_matrix->node_num;
	int i,node_pos;
	// 求原矩阵中每列元素个数并记录在数组中
	int *col_num = (int *)malloc (s_matrix->col * sizeof (int));
	if (col_num == NULL)
		return NULL;
	for (i = 0; i < s_matrix->node_num; ++i)
	{
		col_num[s_matrix->nodes[i].c_idx]++;
	}

	// 求原矩阵中每列首元素（对应转置矩阵每行首元素）在转置存储结构中的位置
	int *row_first_pos = (int*)malloc (s_matrix->col * sizeof (int));
	if (row_first_pos == NULL)
		return NULL;
	row_first_pos[0] = 0;
	for (i = 1; i < s_matrix->col; ++i)
	{
		row_first_pos[i] = row_first_pos[i-1] + col_num[i-1];
	}
	
	// 遍历原矩阵，将每个node放入转置矩阵的对应位置
	for (i = 0; i < s_matrix->node_num; ++i)
	{	
		node_pos = row_first_pos[s_matrix->nodes[i].c_idx];
		trans_matrix->nodes[node_pos].r_idx = s_matrix->nodes[i].c_idx;
		trans_matrix->nodes[node_pos].c_idx = s_matrix->nodes[i].r_idx;
		trans_matrix->nodes[node_pos].value = s_matrix->nodes[i].value;
		row_first_pos[s_matrix->nodes[i].c_idx]++;
	}

	free (col_num);
	free (row_first_pos);
	return trans_matrix;
}


int main (void)
{
	srand (time(NULL));

	int arr[ROW*COL] = {0};
	
	// 初始化二维数组元素值
	init_two_dimensional_array (arr);

	printf ("\nsrc matrix is: \n");	
	print_two_dimensional_array (arr, ROW, COL);

	// 使用普通方式计算matrix的转置
	int *transpose_arr = matrix_transpose (arr, ROW, COL);
	printf ("\ntranspose matrix is:\n");
	print_two_dimensional_array (transpose_arr, COL, ROW);

	Sparse_matrix *s_matrix = NULL;
	create_sparse_matrix (&s_matrix);

	// 从普通矩阵表示法得到稀疏矩阵表示结构
	get_sparse_matrix_from_normal_matrix (arr, ROW, COL, s_matrix);
	print_sparse_matrix (s_matrix);
	
	// 自己实现的稀疏矩阵转置
	Sparse_matrix *transpos_matrix = sparse_matrix_transpose (s_matrix);
	print_sparse_matrix (transpos_matrix);

	// 根据严蔚敏方法实现的稀疏矩阵转置运算
	Sparse_matrix *opti_transpose_matrix = optimize_sparse_matrix_transpose (s_matrix);
	print_sparse_matrix (opti_transpose_matrix);

	free (opti_transpose_matrix);
	free (transpos_matrix);
	free (s_matrix);
	return 0;
}
